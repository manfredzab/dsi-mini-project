// TODO:
// - Better file format handling (less attributes in one tuple than in the other, etc)
// - File headers (time, etc)
// - Comments

#include <iostream>
#include <map>

#include "../include/arguments.h"
#include "../include/argument_parser.h"
#include "../include/data_parser.h"
#include "../include/join_algorithm_type.h"
#include "../include/relation.h"
#include "../include/query.h"
#include "../include/sort_merge_join_trie_iterator.h"
#include "../include/leapfrog_join_trie_iterator.h"
#include "../include/cascading_sort_merge_join.h"
#include "../include/printer.h"

using namespace uk_ac_ox_cs_c875114;

using std::map;
using std::string;

int main(int argc, char *argv[])
{

    // Parse the arguments
    Arguments arguments;
    Status status = ArgumentParser::ParseArguments(argc, argv, &arguments);

    if (kFail == status)
    {
        // TODO: proper error msg
        std::cerr << "Wrong argument format";
        return 1;
    }

    // Parse the given database and the query
    map<string, Relation*>* relations = DataParser::ParseDatabase(arguments.database_file);
    Query* query = DataParser::ParseQuery(arguments.query_file);

    // Execute the given join
    switch (arguments.join_algorithm_type)
    {
        case kSortMerge:
        {
            // Join the relations on the given query
            Relation* result_relation = CascadingSortMergeJoin::Join(*relations, *query);

            // Print the result relation
            Printer::PrintSorted(*result_relation);

            // Release the memory
            delete result_relation;

            break;
        }
        case kSortMergeTrie:
        case kLeapfrog:
        {
            ITrieIterator<int>* join_trie_iterator = (kSortMergeTrie == arguments.join_algorithm_type) ? new SortMergeJoinTrieIterator(*relations, *query) :
                                                                                                         new LeapfrogJoinTrieIterator(*relations, *query);
            // Initialize the join trie iterator
            join_trie_iterator->Init();

            // Print the result trie
            Printer::PrintSorted(*join_trie_iterator);

            // Release the memory
            delete join_trie_iterator;

            break;
        }
        default:
        {
            // TODO: Print error
            break;
        }
    }

    // Release the memory
    delete query;
    delete relations;

	return 0;
}
