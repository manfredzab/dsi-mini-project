// TODO: remove
#include <iostream>

#include <algorithm>
#include "../include/binary_sort_merge_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::string;
using std::vector;

BinarySortMergeJoinIterator::BinarySortMergeJoinIterator(Relation& outer_relation, Relation& inner_relation, const Query& query) :
        outer_relation(outer_relation),
        outer_relation_iterator(outer_relation),
        inner_relation(inner_relation),
        inner_relation_iterator(inner_relation)
{
    // Find the common attributes of the relations and build the resulting relation's attribute name
    // vector (in the join order)
    const vector<string>& outer_attributes = outer_relation.attribute_names;
    const vector<string>& inner_attributes = inner_relation.attribute_names;

    for (unsigned i = 0; i < query.join_attributes.size(); i++)
    {
        string current_attribute = query.join_attributes[i];

        unsigned attribute_index_in_outer_relation = find(outer_attributes.begin(), outer_attributes.end(), current_attribute) - outer_attributes.begin();
        unsigned attribute_index_in_inner_relation = find(inner_attributes.begin(), inner_attributes.end(), current_attribute) - inner_attributes.begin();

        if (attribute_index_in_outer_relation < outer_attributes.size() || attribute_index_in_inner_relation < inner_attributes.size())
        {
            // Save the attribute name
        result_relation_attribute_names.push_back(current_attribute);

            // Create the attribute re-order descriptor
            AttributeOrderDescriptor order_descriptor;
            order_descriptor.is_outer_relation = attribute_index_in_outer_relation < outer_attributes.size();
            order_descriptor.relation_attribute_index = order_descriptor.is_outer_relation ? attribute_index_in_outer_relation : attribute_index_in_inner_relation;

            result_relation_tuple_order.push_back(order_descriptor);

        }

        // If the attribute is present in both relations, record its position
        if (attribute_index_in_outer_relation < outer_attributes.size() && attribute_index_in_inner_relation < inner_attributes.size())
        {
            outer_relation_join_attribute_positions.push_back(attribute_index_in_outer_relation);
            inner_relation_join_attribute_positions.push_back(attribute_index_in_inner_relation);
        }
    }
    
    // Add the remaining attributes from the relations that do not appear in the sort order
    const vector<string>* relation_attributes[] = { &outer_attributes, &inner_attributes };
    for (int i = 0; i < 2; i++)
    {
        const vector<string>& attributes = *(relation_attributes[i]);
        int attributes_size = attributes.size();
        for (int j = 0; j < attributes_size; j++)
        {
            if (find(result_relation_attribute_names.begin(), result_relation_attribute_names.end(), attributes[j]) == result_relation_attribute_names.end())
            {
                result_relation_attribute_names.push_back(attributes[j]);

                AttributeOrderDescriptor order_decriptor = { attributes == outer_attributes, j };
                result_relation_tuple_order.push_back(order_decriptor);
            }
        }
    }


    // Print results
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
}


Status BinarySortMergeJoinIterator::Init()
{
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

    // Sort the relations
    TupleComparisonFunctor outer_relation_tuple_comparison_functor(outer_relation_join_attribute_positions);
    TupleComparisonFunctor inner_relation_tuple_comparison_functor(inner_relation_join_attribute_positions);

    sort(outer_relation.data.begin(), outer_relation.data.end(), outer_relation_tuple_comparison_functor);
    sort(inner_relation.data.begin(), inner_relation.data.end(), inner_relation_tuple_comparison_functor);

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

    return kOK;
}

Status BinarySortMergeJoinIterator::Key(int** out_key)
{
    return kFail;
}


Status BinarySortMergeJoinIterator::Multiplicity(int** out_result)
{
    return kFail;
}


Status BinarySortMergeJoinIterator::Next()
{
    return kFail;
}


bool BinarySortMergeJoinIterator::AtEnd()
{
    return false;
}

} /* namespace uk_ac_ox_cs_c875114 */
