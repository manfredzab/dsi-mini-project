#ifndef CASCADING_SORT_MERGE_JOIN_H_
#define CASCADING_SORT_MERGE_JOIN_H_

#include <map>
#include <string>
#include "relation.h"
#include "query.h"

namespace uk_ac_ox_cs_c875114
{

/**
 * A class to perform a multiway sort-merge join. If n relations are being joined, then
 * this class executes n - 1 cascading binary sort-merge joins (@see BinarySortMergeJoin).
 */
class CascadingSortMergeJoin
{
    public:
        /***
         * Performs a sequence of cascading sort-merge joins for the given relations and a given
         * query. This method invokes n - 1 binary sort-merge joins.
         * @param relations Relations to be joined.
         * @param query Join query.
         * @result A joined relation.
         */
        static Relation* Join(std::map<std::string, Relation*>& relations, const Query& query);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* CASCADING_SORT_MERGE_JOIN_H_ */
