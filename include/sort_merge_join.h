#ifndef SORT_MERGE_JOIN_H_
#define SORT_MERGE_JOIN_H_

#include <map>
#include <string>
#include "join.h"
#include "relation.h"
#include "query.h"

class SortMergeJoin : public IJoin
{
    public:
        virtual Relation* Join(const std::map<std::string, Relation*>& relations, const Query& query);
        virtual ~SortMergeJoin() { };
};

#endif /* SORT_MERGE_JOIN_H_ */
