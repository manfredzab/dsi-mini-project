#ifndef ARGUMENT_PARSER_H_
#define ARGUMENT_PARSER_H_

#include "arguments.h"
#include "status.h"

namespace c875114
{

/**
 * Command line arguments parser. Reads the arguments from the command line argument string
 * array and populates the Arguments structure.
 */
class ArgumentParser
{
    public:
        static Status ParseArguments(int argc, char *argv[], Arguments* out_arguments);
};

} /* namespace c875114 */

#endif /* ARGUMENT_PARSER_H_ */
