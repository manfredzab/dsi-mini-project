#ifndef QUERY_H_
#define QUERY_H_

#include <vector>

namespace uk_ac_ox_cs_c875114
{

struct Query
{
    std::vector<std::string> relation_names;
    std::vector<std::string> join_attributes;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* QUERY_H_ */
