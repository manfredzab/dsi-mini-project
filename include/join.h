#ifndef JOIN_H_
#define JOIN_H_

#include <map>
#include <string>
#include "relation.h"
#include "query.h"

class IJoin
{
    public:
        virtual Relation* Join(const std::map<std::string, Relation*>& relations, const Query& query) = 0;
        virtual ~IJoin() { };
};

#endif /* JOIN_H_ */
