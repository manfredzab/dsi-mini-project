#include <cstring>
#include <string>
#include "../include/argument_parser.h"

namespace c875114
{

using std::string;

/**
 *  Reads the arguments from the command line argument string array and populates the
 *  @see Arguments structure.
 *  @param argc Argument count.
 *  @param argv A pointer to the command line argument string array.
 *  @param out_arguments Resulting @see Arguments structure.
 *  @return @see kOK if the arguments were parsed successfully, @see kFail otherwise.
 */
Status ArgumentParser::ParseArguments(int argc, char *argv[], Arguments* out_arguments)
{
    // Check the fixed parts of the command line argument
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

} /* namespace c875114 */
