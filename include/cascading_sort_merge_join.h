#ifndef CASCADING_SORT_MERGE_JOIN_H_
#define CASCADING_SORT_MERGE_JOIN_H_

#include <map>
#include <string>
#include "relation.h"
#include "query.h"

namespace uk_ac_ox_cs_c875114
{

class CascadingSortMergeJoin
{
    public:
        static Relation* Join(std::map<std::string, Relation*>& relations, const Query& query);
//
//    private:
//        struct RelationComparisonBySizeFunctor
//        {
//            RelationComparisonBySizeFunctor(std::map<std::string, Relation*>& relations) : relations(relations) { }
//
//            std::map<std::string, Relation*>& relations;
//
//            bool operator()(std::string first, std::string second)
//            {
//                return relations[first]->data.size() < relations[second]->data.size();
//            }
//        };
};

} // namespace uk_ac_ox_cs_c875114
#endif /* CASCADING_SORT_MERGE_JOIN_H_ */
