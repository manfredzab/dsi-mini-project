#ifndef DATABASE_PARSER_H_
#define DATABASE_PARSER_H_

#include <map>
#include <string>

#include "query.h"
#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

class DataParser
{
    public:
        static std::map<std::string, Relation*>* ParseDatabase(std::string file_name);
        static Query*                            ParseQuery(std::string file_name);
};

} // namespace uk_ac_ox_cs_c875114

#endif /* DATABASE_PARSER_H_ */
