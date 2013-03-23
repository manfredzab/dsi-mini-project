#ifndef QUERY_H_
#define QUERY_H_

#include <vector>

namespace uk_ac_ox_cs_c875114
{

/**
 * Holds query details (names of relations involved) and the join attribute order.
 */
struct Query
{
    std::vector<std::string> relation_names;  /**< Relation name vector. */
    std::vector<std::string> join_attributes; /**< Join attribute name vector. */
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* QUERY_H_ */
