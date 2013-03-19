#ifndef ARGUMENT_PARSER_H_
#define ARGUMENT_PARSER_H_

#include "arguments.h"
#include "status.h"

namespace uk_ac_ox_cs_c875114
{

class ArgumentParser
{
    public:
        static Status ParseArguments(int argc, char *argv[], Arguments* out_arguments);
};

} // namespace uk_ac_ox_cs_c875114

#endif /* ARGUMENT_PARSER_H_ */