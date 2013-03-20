#include "../include/cascading_sort_merge_join.h"
#include "../include/binary_sort_merge_join.h"

namespace uk_ac_ox_cs_c875114
{

Relation* CascadingSortMergeJoin::Join(std::map<std::string, Relation*>& relations, const Query& query)
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

} // namespace uk_ac_ox_cs_c875114
