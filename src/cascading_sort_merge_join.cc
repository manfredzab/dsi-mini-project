#include <vector>
#include <string>
#include <algorithm>
#include "../include/cascading_sort_merge_join.h"
#include "../include/binary_sort_merge_join.h"

namespace uk_ac_ox_cs_c875114
{

using std::map;
using std::string;

Relation* CascadingSortMergeJoin::Join(map<string, Relation*>& relations, const Query& query)
{
    // Join the first two relations appearing in the query
    Relation* current_join = BinarySortMergeJoin::Join(*relations[query.relation_names[0]], *relations[query.relation_names[1]], query);


    // Perform a cascading left-join with the remaining relations
    for (unsigned i = 2; i < query.relation_names.size(); i++)
    {
        Relation* new_join = BinarySortMergeJoin::Join(*current_join, *relations[query.relation_names[i]], query);

        // Release the memory for the old temporary relation
        delete current_join;

        current_join = new_join;
    }

    return current_join;
}

} /* namespace uk_ac_ox_cs_c875114 */

//RelationComparisonBySizeFunctor relation_comparison_by_size_functor(relations);
//    vector<string> relations_to_join(query.relation_names);
//
//    // Choose two smallest relations out of the ones appearing in the query
//    vector<string>::iterator first_relation_name = min_element(relations_to_join.begin(), relations_to_join.end(), relation_comparison_by_size_functor);
//    Relation* first_relation = relations[*first_relation_name];
//    relations_to_join.erase(first_relation_name);
//
//    vector<string>::iterator second_relation_name = min_element(relations_to_join.begin(), relations_to_join.end(), relation_comparison_by_size_functor);
//    Relation* second_relation = relations[*second_relation_name];
//    relations_to_join.erase(second_relation_name);
//
//    // Join the first two relations appearing in the query
//    std::cout << "Performing join between " << first_relation->name << " and " << second_relation->name << std::endl;
//    Relation* current_join = BinarySortMergeJoin::Join(*first_relation, *second_relation, query);
//
//    // Perform a cascading left-join with the remaining relations, always choosing the smallest
//    while (!relations_to_join.empty())
//    {
//        vector<string>::iterator next_relation_name = min_element(relations_to_join.begin(), relations_to_join.end(), relation_comparison_by_size_functor);
//        Relation* next_relation = relations[*next_relation_name];
//        relations_to_join.erase(next_relation_name);
//
//        std::cout << "Performing join with " << next_relation->name << std::endl;
//        Relation* new_join = BinarySortMergeJoin::Join(*current_join, *next_relation, query);
//
//        // Release the memory for the old temporary relation
//        delete current_join;
//
//        current_join = new_join;
//    }
//
//    return current_join;
