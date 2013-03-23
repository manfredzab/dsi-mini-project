#ifndef DATABASE_PARSER_H_
#define DATABASE_PARSER_H_

#include <map>
#include <string>

#include "query.h"
#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

/***
 * Database and query files parser (creates Relation and Query structures).
 */
class DataParser
{
    public:
        static std::map<std::string, Relation*>* ParseDatabase(std::string file_name);
        static Query*                            ParseQuery(std::string file_name);

    private:
        static Relation*                 ParseRelation(std::string database_file_name, std::string relation_line);
        static Relation*                 ParseRelation(std::string relation_file_name, std::string relation_name, const std::vector<std::string>& attribute_names);
        static int*                      ParseRelationTuple(std::string relation_tuple_line, int attribute_count);

        static void                      RemoveStringWhitespace(std::string& input_string);
        static std::vector<std::string>* TokenizeString(const std::string& input_string, const char character);
        static int                       ConvertStringToInt(const std::string& input_string);

        static std::string               GetFilePath(std::string file_name);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* DATABASE_PARSER_H_ */
