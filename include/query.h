#ifndef QUERY_H_
#define QUERY_H_

#include <vector>

namespace c875114
{

/**
 * Query detail holder: stores the join attribute order and the names of relations involved in the join.
 */
struct Query
{
    std::vector<std::string> relation_names;  /**< Relation name vector. */
    std::vector<std::string> join_attributes; /**< Join attribute name vector. */
};

} /* namespace c875114 */

#endif /* QUERY_H_ */
