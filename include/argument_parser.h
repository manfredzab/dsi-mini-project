#ifndef ARGUMENT_PARSER_H_
#define ARGUMENT_PARSER_H_

#include "arguments.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

/**
 * Command line arguments parser. Reads the arguments from the command line argument string
 * array and populates the @see Arguments structure.
 */
class ArgumentParser
{
    public:
        static Status ParseArguments(int argc, char *argv[], Arguments* out_arguments);
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* ARGUMENT_PARSER_H_ */
