#ifndef DATABASE_PARSER_H_
#define DATA_PARSER_H_

#include <vector>
#include <string>

#include "relation.h"

class DataParser
{
public:
    static std::vector<Relation*>& ParseDatabase(const char* file_name);
    static Relation* ParseRelation(const char* file_name, std::string relation_name, std::vector<std::string>& attribute_names);
private:
    static Relation* ParseRelation(const char* database_file_name, std::string relation_line);
    static int* ParseRelationTuple(std::string relation_tuple_line, int attribute_count);
};

#endif /* DATABASE_PARSER_H_ */
