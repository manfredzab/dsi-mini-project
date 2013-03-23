#ifndef DATABASE_PARSER_H_
#define DATABASE_PARSER_H_

#include <map>
#include <string>

#include "query.h"
#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

/***
 * This class parses the database and query files, creating Relation and Query structures.
 */
class DataParser
{
    public:
        /**
         * Parse the database from a given file.
         * @param file_name Database file name.
         * @returns A pointer to the dictionary of parsed relations, indexed by the relation's name.
         */
        static std::map<std::string, Relation*>* ParseDatabase(std::string file_name);

        /**
         * Parse the query from a given file.
         * @param file_name Query file name.
         * @returns A pointer to the populated Query data structure.
         */
        static Query* ParseQuery(std::string file_name);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* DATABASE_PARSER_H_ */
