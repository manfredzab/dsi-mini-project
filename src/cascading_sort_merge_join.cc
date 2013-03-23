#include <vector>
#include <string>
#include <algorithm>
#include "../include/cascading_sort_merge_join.h"
#include "../include/binary_sort_merge_join.h"

namespace c875114
{

using std::map;
using std::string;

/**
 * Performs a sequence of cascading sort-merge joins for the given relations and a given
 * query. This method invokes \f$n - 1\f$ binary sort-merge joins.
 * @param relations Relations to be joined.
 * @param query Join query.
 * @result A pointer to the joined relation.
 */
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

} /* namespace c875114 */
