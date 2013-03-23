#ifndef CASCADING_SORT_MERGE_JOIN_H_
#define CASCADING_SORT_MERGE_JOIN_H_

#include <map>
#include <string>
#include "relation.h"
#include "query.h"

namespace c875114
{

/**
 * Multi-way cascading sort-merge join, based on the binary sort-merge join. If \f$n\f$ relations
 * are being joined, then this class executes \f$n - 1\f$ cascading binary sort-merge joins
 * (@see BinarySortMergeJoin).
 */
class CascadingSortMergeJoin
{
    public:
        static Relation* Join(std::map<std::string, Relation*>& relations, const Query& query);
};

} /* namespace c875114 */

#endif /* CASCADING_SORT_MERGE_JOIN_H_ */
