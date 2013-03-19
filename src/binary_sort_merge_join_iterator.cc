// TODO: remove
#include <iostream>

#include <cstring>
#include <algorithm>
#include "../include/binary_sort_merge_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::string;
using std::vector;
using std::list;

BinarySortMergeJoinIterator::BinarySortMergeJoinIterator(Relation& outer_relation,
                                                         Relation& inner_relation,
                                                         const vector<AttributeOrderDescriptor>& result_relation_tuple_order,
                                                         const vector<int>& outer_relation_join_attribute_positions,
                                                         const vector<int>& inner_relation_join_attribute_positions) :
    outer_relation(outer_relation),
    inner_relation(inner_relation),
    outer_relation_iterator(outer_relation),
    inner_relation_iterator(inner_relation),
    outer_relation_tuple_comparison_functor(outer_relation_join_attribute_positions),
    inner_relation_tuple_comparison_functor(inner_relation_join_attribute_positions),
    result_relation_tuple_order(result_relation_tuple_order),
    outer_relation_join_attribute_positions(outer_relation_join_attribute_positions),
    inner_relation_join_attribute_positions(inner_relation_join_attribute_positions)
{
    // Initialize iterator's state
    result_relation_attribute_count = result_relation_tuple_order.size();
    join_attribute_count = outer_relation_join_attribute_positions.size();
    at_end = false;

    // Allocate memory for the key
    key = new int[result_relation_attribute_count];

    // Print results
    /*
     for (vector<string>::iterator it = result_relation_attribute_names.begin(); it != result_relation_attribute_names.end(); ++it)
     {
     std::cout << *it << "\t";
     }
     std::cout << std::endl;

     for (vector<AttributeOrderDescriptor>::iterator it = result_relation_tuple_order.begin(); it != result_relation_tuple_order.end(); ++it)
     {
     std::cout << (it->is_outer_relation ? "Out" : "In") << "/" << it->relation_attribute_index << "\t";
     }
     std::cout << std::endl;

     std::cout << "Outer relation join attribute indices: ";
     for (unsigned i = 0; i < outer_relation_join_attribute_positions.size(); i++)
     {
     std::cout << outer_relation_join_attribute_positions[i] << " ";
     }
     std::cout << std::endl;

     std::cout << "Inner relation join attribute indices: ";
     for (unsigned i = 0; i < inner_relation_join_attribute_positions.size(); i++)
     {
     std::cout << inner_relation_join_attribute_positions[i] << " ";
     }
     std::cout << std::endl;
     */
}


BinarySortMergeJoinIterator::~BinarySortMergeJoinIterator()
{
    delete[] key;
}


Status BinarySortMergeJoinIterator::Init()
{
    /*
     std::cout << "Outer relation:" << std::endl;
     for (int i = 0; i < outer_relation.data.size(); i++)
     {
     for (int j = 0; j < outer_relation.attribute_names.size(); j++)
     {
     std::cout << outer_relation.data[i][j] << " ";
     }
     std::cout << std::endl;
     }

     std::cout << "Inner relation:" << std::endl;
     for (int i = 0; i < inner_relation.data.size(); i++)
     {
     for (int j = 0; j < inner_relation.attribute_names.size(); j++)
     {
     std::cout << inner_relation.data[i][j] << " ";
     }
     std::cout << std::endl;
     }

     int* tuple;

     std::cout << "Outer relation iterator:" << std::endl;
     outer_relation_iterator.Key(&tuple);
     for (int j = 0; j < outer_relation.attribute_names.size(); j++)
     {
     std::cout << tuple[j] << " ";
     }
     std::cout << std::endl;

     std::cout << "Inner relation iterator:" << std::endl;
     inner_relation_iterator.Key(&tuple);
     for (int j = 0; j < inner_relation.attribute_names.size(); j++)
     {
     std::cout << tuple[j] << " ";
     }
     std::cout << std::endl;
     */

    // Sort the relations
    sort(outer_relation.data.begin(), outer_relation.data.end(), outer_relation_tuple_comparison_functor);
    sort(inner_relation.data.begin(), inner_relation.data.end(), inner_relation_tuple_comparison_functor);

    // Position the iterator at the next match
    return Next();
}


Status BinarySortMergeJoinIterator::Key(int** out_key)
{
    memcpy(*out_key, key, result_relation_attribute_count * sizeof(int));

    return kOK;
}


bool BinarySortMergeJoinIterator::AtEnd()
{
    return at_end;
}


Status BinarySortMergeJoinIterator::Next()
{
    int* outer_tuple;
    int* inner_tuple;

    // There are potential duplicates to be output before proceeding
    if (!outer_relation_duplicates.empty())
    {
        // Prepare to output the next duplicate
        inner_relation_duplicates_position++;
        if (inner_relation_duplicates_position == inner_relation_duplicates.end())
        {
            outer_relation_duplicates.pop_front();
            inner_relation_duplicates_position = inner_relation_duplicates.begin();
        }

        // If there are no more duplicates in the outer relation, clear the inner relation duplicates and search
        // for the new match (below), otherwise, set the key and return.
        if (!outer_relation_duplicates.empty())
        {
            CreateResultTupleAsKey(outer_relation_duplicates.front(), *inner_relation_duplicates_position);
            return kOK;
        }
        else
        {
            inner_relation_duplicates.clear();
        }
    }

    if (this->AtEnd())
    {
        return kFail;
    }

    while (!outer_relation_iterator.AtEnd() && !inner_relation_iterator.AtEnd())
    {
        outer_relation_iterator.Key(&outer_tuple);
        inner_relation_iterator.Key(&inner_tuple);

        if (kLessThan == CompareTuplesAtDifferentRelations(outer_tuple, inner_tuple))
        {
            outer_relation_iterator.Next();
        }
        else if (kGreaterThan == CompareTuplesAtDifferentRelations(outer_tuple, inner_tuple))
        {
            inner_relation_iterator.Next();
        }
        else // Outer and inner tuples are equal
        {
            // Set the key
            CreateResultTupleAsKey(outer_tuple, inner_tuple);

            // Gather the duplicates
            GatherSameKeyTuples(outer_relation_iterator, outer_relation_tuple_comparison_functor, outer_relation_duplicates);
            GatherSameKeyTuples(inner_relation_iterator, inner_relation_tuple_comparison_functor, inner_relation_duplicates);

            // Set the current position for the inner relation duplicates to the beginning
            inner_relation_duplicates_position = inner_relation_duplicates.begin();

            return kOK;
        }
    }

    this->at_end = true;
    return kFail;
}


inline void BinarySortMergeJoinIterator::GatherSameKeyTuples(SimpleRelationIterator& relation_iterator, SameRelationTupleComparisonFunctor& comparison_functor, list<int*>& out_same_key_tuples)
{
    int* current_tuple;
    relation_iterator.Key(&current_tuple);

    int* duplicate_tuple = current_tuple;
    while (!relation_iterator.AtEnd() && (kEqual == comparison_functor.CompareTuples(current_tuple, duplicate_tuple)))
    {
        out_same_key_tuples.push_back(duplicate_tuple);

        relation_iterator.Next();
        relation_iterator.Key(&duplicate_tuple);
    }

    if (relation_iterator.AtEnd())
    {
        at_end = true;
    }
}


inline BinarySortMergeJoinIterator::Equality BinarySortMergeJoinIterator::CompareTuplesAtDifferentRelations(int* outer_relation_tuple, int* inner_relation_tuple)
{
    for (int i = 0; i < join_attribute_count; i++)
    {
        if (outer_relation_tuple[outer_relation_join_attribute_positions[i]] > inner_relation_tuple[inner_relation_join_attribute_positions[i]])
        {
            return kGreaterThan;
        }
        else if (outer_relation_tuple[outer_relation_join_attribute_positions[i]] < inner_relation_tuple[inner_relation_join_attribute_positions[i]])
        {
            return kLessThan;
        }
    }

    return kEqual;
}


inline void BinarySortMergeJoinIterator::CreateResultTupleAsKey(int* outer_tuple, int* inner_tuple)
{
    for (int i = 0; i < result_relation_attribute_count; i++)
    {
        const AttributeOrderDescriptor& order_descriptor = result_relation_tuple_order[i];
        key[i] = (order_descriptor.is_outer_relation ? outer_tuple : inner_tuple)[order_descriptor.relation_attribute_index];
    }
}

} /* namespace uk_ac_ox_cs_c875114 */
