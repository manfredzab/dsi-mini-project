#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include "../include/binary_sort_merge_join.h"
#include "../include/binary_sort_merge_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;
using std::string;

typedef BinarySortMergeJoinIterator::AttributeOrderDescriptor AttributeOrderDescriptor; // Shorten the name without polluting the namespaces

Relation* BinarySortMergeJoin::Join(Relation& outer_relation, Relation& inner_relation, const Query& query)
{
    // Build the result relation metadata
    Relation* result_relation = new Relation();

    // Concatenate the outer and inner relation names to produce a temporary result relation name
    result_relation->name = outer_relation.name + inner_relation.name;

    // Build the result relation's attribute name vector
    vector<AttributeOrderDescriptor> result_relation_tuple_order;

    std::vector<int> outer_relation_join_attribute_positions;
    std::vector<int> inner_relation_join_attribute_positions;

    // Find the common attributes of the relations and build the resulting relation's attribute name
    // vector (in the join order)
    for (unsigned i = 0; i < query.join_attributes.size(); i++)
    {
        string current_attribute = query.join_attributes[i];

        unsigned attribute_index_in_outer_relation = find(outer_relation.attribute_names.begin(), outer_relation.attribute_names.end(), current_attribute) - outer_relation.attribute_names.begin();
        unsigned attribute_index_in_inner_relation = find(inner_relation.attribute_names.begin(), inner_relation.attribute_names.end(), current_attribute) - inner_relation.attribute_names.begin();

        if (attribute_index_in_outer_relation < outer_relation.attribute_names.size() || attribute_index_in_inner_relation < inner_relation.attribute_names.size())
        {
            // Save the attribute name
            result_relation->attribute_names.push_back(current_attribute);

            // Create the attribute re-order descriptor which indicates in what order the join result tuple
            // should be constructed (in this case, join attributes in join order, followed by outer relation
            // attributes not participating in the join, then inner relation attributes; the latter two are
            // added further below).
            AttributeOrderDescriptor order_descriptor;
            order_descriptor.is_outer_relation = attribute_index_in_outer_relation < outer_relation.attribute_names.size();
            order_descriptor.relation_attribute_index = order_descriptor.is_outer_relation ? attribute_index_in_outer_relation : attribute_index_in_inner_relation;

            result_relation_tuple_order.push_back(order_descriptor);

        }

        // If the attribute is present in both relations, record its position
        if (attribute_index_in_outer_relation < outer_relation.attribute_names.size() && attribute_index_in_inner_relation < inner_relation.attribute_names.size())
        {
            outer_relation_join_attribute_positions.push_back(attribute_index_in_outer_relation);
            inner_relation_join_attribute_positions.push_back(attribute_index_in_inner_relation);
        }
    }

    // Add the remaining attributes from the inner and outer relations that do not participate
    // in the join to the attribute vector and the re-order descriptor, as described above.
    const vector<string>* relation_attributes[] = { &outer_relation.attribute_names, &inner_relation.attribute_names };
    for (int i = 0; i < 2; i++)
    {
        const vector<string>& attributes = *(relation_attributes[i]);
        int attributes_size = attributes.size();
        for (int j = 0; j < attributes_size; j++)
        {
            if (find(result_relation->attribute_names.begin(), result_relation->attribute_names.end(), attributes[j]) == result_relation->attribute_names.end())
            {
                result_relation->attribute_names.push_back(attributes[j]);

                AttributeOrderDescriptor order_decriptor = { attributes == outer_relation.attribute_names, j };
                result_relation_tuple_order.push_back(order_decriptor);
            }
        }
    }

    // Build the result relation's tuple data vector using a binary sort-merge join iterator on the outer and inner relations
    BinarySortMergeJoinIterator join_iterator(outer_relation, inner_relation, result_relation_tuple_order, outer_relation_join_attribute_positions, inner_relation_join_attribute_positions);
    JoinUsingIterator(join_iterator, result_relation);

    return result_relation;
}


void BinarySortMergeJoin::JoinUsingIterator(BinarySortMergeJoinIterator& join_iterator, Relation* out_result_relation)
{
    int result_relation_tuple_size = out_result_relation->attribute_names.size();

    join_iterator.Init();

    Tuple result_tuple;
    result_tuple.multiplicity = 1;

    int *result_key;
    do
    {
        // Get the result tuple
        result_tuple.key = new int[result_relation_tuple_size];
        join_iterator.Key(&result_key);
        memcpy(result_tuple.key, result_key, result_relation_tuple_size * sizeof(int));

        // Check if the current tuple is a duplicate of the previous tuple
        Tuple& previous_tuple = out_result_relation->data.back();
        if (!out_result_relation->data.empty() && Tuple::AreKeysEqual(result_tuple, previous_tuple, result_relation_tuple_size))
        {
            previous_tuple.multiplicity++;
            delete[] result_tuple.key;
        }
        else
        {
            out_result_relation->data.push_back(result_tuple);
        }
    }
    while (kOK == join_iterator.Next()); // Move to the next tuple
}

} /* namespace uk_ac_ox_cs_c875114 */
