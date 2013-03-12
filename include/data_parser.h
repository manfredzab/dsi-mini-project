#ifndef DATABASE_PARSER_H_
#define DATA_PARSER_H_

#include <map>
#include <string>

#include "query.h"
#include "relation.h"

class DataParser
{
public:
    static std::map<std::string, Relation*>* ParseRelations(const char* file_name);
    static Query*                            ParseQuery(const char* file_name);
};

#endif /* DATABASE_PARSER_H_ */
