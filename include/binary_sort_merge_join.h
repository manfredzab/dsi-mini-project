#ifndef BINARY_SORT_MERGE_JOIN_H_
#define BINARY_SORT_MERGE_JOIN_H_

#include "relation.h"
#include "query.h"
#include "binary_sort_merge_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class BinarySortMergeJoin
{
    public:
        static Relation* Join(Relation& outer_relation, Relation& inner_relation, const Query& query);

    private:
        static void JoinUsingIterator(BinarySortMergeJoinIterator& join_iterator, Relation* out_result_relation);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* BINARY_SORT_MERGE_JOIN_H_ */
