#include <cstring>
#include <algorithm>
#include "../include/binary_sort_merge_join_iterator.h"

namespace c875114
{

using std::string;
using std::vector;
using std::list;

/**
 * Constructs a binary sort-merge join iterator from the given outer and inner relations,
 * information on how to build the resulting relation tuple from two input relation tuples
 * and the join attribute positions in each relation.
 * @param outer_relation Outer relation.
 * @param inner_relation Inner relation.
 * @param result_relation_tuple_order A vector of attribute order descriptors which tells
 *                                    how the resulting tuple should be built from the two
 *                                    two input relation tuples.
 * @param outer_relation_join_attribute_positions Join attribute positions in the outer relation
 * @param inner_relation_join_attribute_positions Join attribute positions in the inner relation
 */
BinarySortMergeJoinIterator::BinarySortMergeJoinIterator(Relation& outer_relation,
                                                         Relation& inner_relation,
                                                         const vector<AttributeOrderDescriptor>& result_relation_tuple_order,
                                                         const vector<int>& outer_relation_join_attribute_positions,
                                                         const vector<int>& inner_relation_join_attribute_positions) :
    // Initialize the state
    outer_relation(outer_relation),
    inner_relation(inner_relation),
    outer_relation_tuple_comparison_functor(outer_relation_join_attribute_positions),
    inner_relation_tuple_comparison_functor(inner_relation_join_attribute_positions),
    result_relation_tuple_order(result_relation_tuple_order),
    outer_relation_join_attribute_positions(outer_relation_join_attribute_positions),
    inner_relation_join_attribute_positions(inner_relation_join_attribute_positions)
{
    // Initialize simple iterator pointers
    outer_relation_iterator = NULL;
    inner_relation_iterator = NULL;

    // Initialize iterator's state
    result_relation_attribute_count = result_relation_tuple_order.size();
    join_attribute_count = outer_relation_join_attribute_positions.size();
    at_end = false;

    // Allocate memory for the key
    key = new int[result_relation_attribute_count];
}

/**
 * Releases all resources occupied by the binary sort-merge join iterator.
 */
BinarySortMergeJoinIterator::~BinarySortMergeJoinIterator()
{

    delete[] key;

    if (outer_relation_iterator != NULL)
    {
        delete outer_relation_iterator;
    }

    if (inner_relation_iterator != NULL)
    {
        delete inner_relation_iterator;
    }
}

/**
 * Initializes the iterator. This method must be called before calling any other method
 * of the iterator.
 * @returns kOK on success, failure otherwise.
 */
Status BinarySortMergeJoinIterator::Init()
{
    // Sort the relations
    sort(outer_relation.data.begin(), outer_relation.data.end(), outer_relation_tuple_comparison_functor);
    sort(inner_relation.data.begin(), inner_relation.data.end(), inner_relation_tuple_comparison_functor);

    // Initialize relation iterators
    outer_relation_iterator = new SimpleIterator(outer_relation);
    inner_relation_iterator = new SimpleIterator(inner_relation);

    // Position the iterator at the next match
    return Next();
}

/**
 * Returns the tuple key at a current position of the iterator.
 * @param out_key A pointer to the memory location where the tuple should be
 *                stored.
 * @returns kOK on success, failure otherwise.
 */
Status BinarySortMergeJoinIterator::Key(int** out_key)
{
    memcpy(*out_key, key, result_relation_attribute_count * sizeof(int));

    return kOK;
}

/**
 * Checks if the join iterator is positioned at the last tuple in the join result.
 * @returns true if the iterator is positioned at the last tuple, false otherwise.
 */
bool BinarySortMergeJoinIterator::AtEnd()
{
    return at_end;
}

/**
 * Positions the join iterator at the next position in the join result.
 * @returns kOK on success, failure otherwise.
 */
Status BinarySortMergeJoinIterator::Next()
{
    int* outer_tuple;
    int* inner_tuple;

    // Before seeking to the next tuple, finish dealing with duplicates first
    if (!outer_relation_duplicates.empty()) // There are potential duplicates to be output before proceeding
    {
        // Prepare to output the next duplicate
        inner_relation_duplicates_position++;
        if (inner_relation_duplicates_position == inner_relation_duplicates.end())
        {
            outer_relation_duplicates.pop_front();
            inner_relation_duplicates_position = inner_relation_duplicates.begin();
        }

        // If there are more duplicates in the outer relation, set the key and return
        if (!outer_relation_duplicates.empty())
        {
            CreateResultTupleAsKey(outer_relation_duplicates.front(), *inner_relation_duplicates_position);
            return kOK;
        }
        else
        {
            // If there are no more duplicates in the outer relation, clear the inner relation duplicates
            // and proceed
            inner_relation_duplicates.clear();
        }
    }

    if (this->AtEnd())
    {
        return kFail;
    }

    // Scan outer and inner relations in lock-step fashion
    while (!outer_relation_iterator->AtEnd() && !inner_relation_iterator->AtEnd())
    {
        // Get the current keys
        outer_relation_iterator->Key(&outer_tuple);
        inner_relation_iterator->Key(&inner_tuple);

        if (kLessThan == CompareTuplesAtDifferentRelations(outer_tuple, inner_tuple))
        {
            // Outer key < inner key, move the outer relation forwards
            outer_relation_iterator->Next();
        }
        else if (kGreaterThan == CompareTuplesAtDifferentRelations(outer_tuple, inner_tuple))
        {
            // Inner key < outer key, move the inner relation forwards
            inner_relation_iterator->Next();
        }
        else // Outer and inner tuples are equal
        {
            // Set the key
            CreateResultTupleAsKey(outer_tuple, inner_tuple);

            // Gather the duplicates
            GatherSameKeyTuples(*outer_relation_iterator, outer_relation_tuple_comparison_functor, outer_relation_duplicates);
            GatherSameKeyTuples(*inner_relation_iterator, inner_relation_tuple_comparison_functor, inner_relation_duplicates);

            // Set the current position for the inner relation duplicates to the beginning
            inner_relation_duplicates_position = inner_relation_duplicates.begin();

            return kOK;
        }
    }

    // If we fell-through the previous loop, we must be at the end
    this->at_end = true;
    return kFail;
}

/**
 * Gathers tuples with the same key, starting at the current relation iterator position.
 * @param relation_iterator A reference to a simple relation iterator.
 * @param comparison_functor A reference to the tuple comparison functor (see SameRelationTupleComparisonFunctor).
 * @param out_same_key_result_tuples A reference to the list into which the same key tuples should be placed.
 */
inline void BinarySortMergeJoinIterator::GatherSameKeyTuples(SimpleIterator& relation_iterator, SameRelationTupleComparisonFunctor& comparison_functor, list<int*>& out_same_key_tuples)
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

/**
 * Lexicographically compares tuples from outer and inner relations based on the join attribute positions.
 * @param outer_relation_tuple Outer relation tuple.
 * @param inner_relation_tuple Inner relation tuple.
 * @returns Lexicographic comparison result.
 */
inline Equality BinarySortMergeJoinIterator::CompareTuplesAtDifferentRelations(int* outer_relation_tuple, int* inner_relation_tuple)
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

/**
 * Builds a resulting relation tuple from the two input relation tuples (from outer and inner relations).
 * The result is stored in the "key" member of the binary sort-merge join iterator.
 * @param outer_tuple Outer relation tuple.
 * @param inner_tuple Inner relation tuple.
 */
inline void BinarySortMergeJoinIterator::CreateResultTupleAsKey(int* outer_tuple, int* inner_tuple)
{
    for (int i = 0; i < result_relation_attribute_count; i++)
    {
        const AttributeOrderDescriptor& order_descriptor = result_relation_tuple_order[i];
        key[i] = (order_descriptor.is_outer_relation ? outer_tuple : inner_tuple)[order_descriptor.relation_attribute_index];
    }
}

/**
 * Not supported by the binary sort merge join iterator.
 * @returns kNotSupported
 */
Status BinarySortMergeJoinIterator::Multiplicity(int* out_key)
{
    return kNotImplemented;
}


} /* namespace c875114 */
