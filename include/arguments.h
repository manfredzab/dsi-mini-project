#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <string>
#include "join_algorithm_type.h"

namespace uk_ac_ox_cs_c875114
{

struct Arguments
{
    JoinAlgorithmType join_algorithm_type;
    std::string       query_file;
    std::string       database_file;
    bool              output_time;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* ARGUMENTS_H_ */
