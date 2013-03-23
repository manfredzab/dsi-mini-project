#ifndef BINARY_SORT_MERGE_JOIN_H_
#define BINARY_SORT_MERGE_JOIN_H_

#include "relation.h"
#include "query.h"
#include "binary_sort_merge_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

/**
 * Binary sort merge join class. It takes two relations (outer and inner) and a query, and produces
 * the result relation after joining outer and inner relations using a binary sort merge join iterator.
 */
class BinarySortMergeJoin
{
    public:
        static Relation* Join(Relation& outer_relation, Relation& inner_relation, const Query& query);

    private:
        /***
         * Joins the outer and inner relations using a binary sort-merge join iterator.
         * @param join_iterator Binary sort-merge join iterator that is used to join the relations.
         * @param out_result_relation A pointer to the result relation, where the tuple data should
         *                            be stored.
         */
        static void JoinUsingIterator(BinarySortMergeJoinIterator& join_iterator, Relation* out_result_relation);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* BINARY_SORT_MERGE_JOIN_H_ */
