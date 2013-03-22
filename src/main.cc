// TODO:
// - Better file format handling (less attributes in one tuple than in the other, etc)
// - File headers (time, etc)
// - Comments

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>

#include "../include/arguments.h"
#include "../include/argument_parser.h"
#include "../include/data_parser.h"
#include "../include/join_algorithm_type.h"
#include "../include/relation.h"
#include "../include/query.h"
#include "../include/multiway_sort_merge_join_trie_iterator.h"
#include "../include/leapfrog_join_trie_iterator.h"
#include "../include/cascading_sort_merge_join.h"
#include "../include/printer.h"
#include "../include/timer.h"
#include "../include/binary_search_tree.h"
#include "../include/linear_iterator.h"

using namespace uk_ac_ox_cs_c875114;

using std::map;
using std::string;

void PrintUsageMessage();

int main(int argc, char *argv[])
{
    // Parse the arguments
    Arguments arguments;
    Status status = ArgumentParser::ParseArguments(argc, argv, &arguments);

    if (kFail == status)
    {
        PrintUsageMessage();
        return EXIT_FAILURE;
    }

    // Parse the given database and the query
    map<string, Relation*>* relations = DataParser::ParseDatabase(arguments.database_file);
    Query* query = DataParser::ParseQuery(arguments.query_file);

    //-----------------------------------------------------
    Relation* test_rel = (*relations)["R"];
    LinearIterator linear_iterator(*test_rel);
    linear_iterator.Init();

    int* tuple;
    int multiplicity;
    Status substatus;

    int command = -1;
    while (command != 0)
    {
        std::cout << "[0] Exit [1] Next [2] Key [3] Multiplicity [4] Seek [5] At end" << std::endl;
        std::cin >> command;

        switch (command)
        {
            case 1:
            {
                substatus = linear_iterator.Next();

                if (kOK == substatus)
                {
                    std::cout << "[OK]" << std::endl;
                }
                else
                {
                    std::cout << "[FAIL]" << std::endl;
                }

                break;
            }
            case 2:
            {
                substatus = linear_iterator.Key(&tuple);
                if (kOK == substatus)
                {
                    std::cout << "[OK] ";

                    for (unsigned i = 0; i < test_rel->attribute_names.size(); i++)
                    {
                        std::cout << tuple[i] << ",";
                    }
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << "[FAIL]" << std::endl;
                }
                break;
            }
            case 3:
            {
                substatus = linear_iterator.Multiplicity(&multiplicity);
                if (kOK == substatus)
                {
                    std::cout << "[OK] ";
                    std::cout << multiplicity << std::endl;
                }
                else
                {
                    std::cout << "[FAIL]" << std::endl;
                }
                break;
            }
            case 4:
            {
                int* buffer = new int[test_rel->attribute_names.size()];
                for (unsigned i = 0; i < test_rel->attribute_names.size(); i++)
                {
                    std::cin >> buffer[i];
                }

                substatus = linear_iterator.Seek(buffer);
                delete buffer;

                if (kOK == substatus)
                {
                    std::cout << "[OK]" << std::endl;
                }
                else
                {
                    std::cout << "[FAIL]" << std::endl;
                }
                break;
            }
            case 5:
            {
                std::cout << (linear_iterator.AtEnd() ? "TRUE" : "FALSE") << std::endl;
                break;
            }
        }
    }
//    for (map<string, Relation*>::iterator it = relations->begin(); it != relations->end(); ++it)
//    {
//        BinarySearchTree(it->second->data, it->second->attribute_names.size());
//    }


    return 1;
    //-----------------------------------------------------

    // Set up the output stream: if "-output time" flag is specified, the joined relation will
    // be written into "result.rel" file and the time measurement will be written to STDOUT;
    // otherwise the joined relation will be printed to STDOUT.
    std::ofstream file_output_stream;
    if (arguments.output_time)
    {
        file_output_stream.open("result.rel", std::ios::out | std::ios::trunc);
    }
    std::ostream& output_stream = arguments.output_time ? file_output_stream : std::cout;

    // Execute the given join measuring the time
    Timer timer;
    double join_elapsed_time_in_seconds;

    switch (arguments.join_algorithm_type)
    {
        case kSortMerge:
        {
            // Start measuring the time
            timer.Start();

            // Join the relations on the given query and print the result
            Relation* result_relation = CascadingSortMergeJoin::Join(*relations, *query);

            Printer::Print(*result_relation, output_stream);

            // Stop measuring the time
            join_elapsed_time_in_seconds = timer.Stop();

            // Release the memory
            delete result_relation;

            break;
        }
        case kSortMergeTrie:
        case kLeapfrog:
        {
            ITrieIterator<int>* join_trie_iterator = (kSortMergeTrie == arguments.join_algorithm_type) ? new MultiwaySortMergeJoinTrieIterator(*relations, *query) :
                                                                                                         new LeapfrogJoinTrieIterator(*relations, *query);
            // Initialize the join trie iterator
            join_trie_iterator->Init();

            // Start measuring the time (ignoring the time required to build the tries for relations)
            timer.Start();

            // Traverse the non-materialized result trie and print it
            Printer::Print(*join_trie_iterator, output_stream);

            // Stop measuring the time
            join_elapsed_time_in_seconds = timer.Stop();

            // Release the memory
            delete join_trie_iterator;

            break;
        }
        default:
        {
            PrintUsageMessage();
            return EXIT_FAILURE;
        }
    }

    // Release the memory
    delete query;
    for (map<string, Relation*>::iterator it = relations->begin(); it != relations->end(); ++it)
    {
        delete it->second;
    }
    delete relations;

    // If we were supposed to print the time, print it to the console and close the result relation file
    if (arguments.output_time)
    {
        std::cout << join_elapsed_time_in_seconds << std::endl;

        file_output_stream.close();
    }

	return EXIT_SUCCESS;
}


void PrintUsageMessage()
{
    std::cerr << "Usage: \"dsi-mini-project <algorithm> -query <query file> -database <database file> [-output <output type>]\", where" << std::endl;
    std::cerr << " - <algorithm> is one of { \"sortmerge\", \"sortmergetrie\", \"leapfrog\" }, and" << std::endl;
    std::cerr << " - <output type> is one of { \"relation\", \"time\" }."<< std::endl;
}
