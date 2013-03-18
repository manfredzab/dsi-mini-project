#ifndef JOIN_H_
#define JOIN_H_

#include <map>
#include <string>
#include "relation.h"
#include "query.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

enum JoinAlgorithmType
{
    kSortMerge = 0,
    kSortMergeTrie,
    kLeapfrog
};

class IJoin
{
    public:
        virtual Status Join(const std::map<std::string, Relation*>& relations, const Query& query, Relation* result) = 0;
        virtual ~IJoin() { };
};

} // namespace uk_ac_ox_cs_c875114

#endif /* JOIN_H_ */
