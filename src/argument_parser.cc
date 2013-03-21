#include <cstring>
#include <string>
#include "../include/argument_parser.h"

namespace uk_ac_ox_cs_c875114
{

using std::string;

Status ArgumentParser::ParseArguments(int argc, char *argv[], Arguments* out_arguments)
{
    if ((6 != argc) || (strcmp(argv[2], "-query") != 0) || (strcmp(argv[4], "-database") != 0))
    {
        if ((8 != argc) || (strcmp(argv[6], "-output") != 0)) // One last chance
        {
            return kFail;
        }
    }

    // Parse the join algorithm method
    JoinAlgorithmType join_algorithm_type;
    if (strcmp(argv[1], "sortmerge") == 0)
    {
        join_algorithm_type = kSortMerge;
    }
    else if (strcmp(argv[1], "sortmergetrie") == 0)
    {
        join_algorithm_type = kSortMergeTrie;
    }
    else if (strcmp(argv[1], "leapfrog") == 0)
    {
        join_algorithm_type = kLeapfrog;
    }
    else
    {
        return kFail;
    }

    // Parse query and database file strings
    string query_file(argv[3]);
    string database_file(argv[5]);

    // Parse the output type
    bool output_time = (8 == argc) && (strcmp(argv[7], "time") == 0);

    // Set the result
    out_arguments->join_algorithm_type = join_algorithm_type;
    out_arguments->query_file = query_file;
    out_arguments->database_file = database_file;
    out_arguments->output_time = output_time;

    return kOK;
}

} /* namespace uk_ac_ox_cs_c875114 */
