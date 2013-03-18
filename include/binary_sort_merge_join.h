#ifndef BINARY_SORT_MERGE_JOIN_H_
#define BINARY_SORT_MERGE_JOIN_H_

#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

class BinarySortMergeJoin
{
    public:
        BinarySortMergeJoin(const Relation& first, const Relation& second);
        virtual ~BinarySortMergeJoin();
};

} // namespace uk_ac_ox_cs_c875114

#endif /* BINARY_SORT_MERGE_JOIN_H_ */
