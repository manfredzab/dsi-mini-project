#ifndef JOIN_H_
#define JOIN_H_

#include <map>
#include <string>
#include "relation.h"
#include "query.h"
#include "status.h"

class IJoin
{
    public:
        virtual Status Join(const std::map<std::string, Relation*>& relations, const Query& query, Relation* result) = 0;
        virtual ~IJoin() { };
};

#endif /* JOIN_H_ */