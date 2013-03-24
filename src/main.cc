/**
 * @mainpage Documentation of "dsi-mini-project" tool
 *
 * @section decription_sec Description
 *
 * The <i>dsi-mini-project</i> tool implements three multi-way join algorithms:
 * <ul>
 *   <li>Cascading sort-merge join, which uses \f$n - 1\f$ binary sort-merge joins to join \f$n\f$ relations,</li>
 *   <li>Trie-based sort-merge join, which joins all relations at the same time using trie representations
 *       of relations (but requires that relations would be pre-sorted in the join-order), and</li>
 *   <li>Leapfrog join, as described by Todd L Veldhuizen in "Leapfrog Triejoin: A Simple, Worst-Case Optimal Join
 *       Algorithm", LogicBlox Technical Report LB1201, December 2012.</li>
 * </ul>
 *
 * @section usage_sec Usage
 *
 *  This section describes how to:
 *  <ul>
 *    <li>@ref running_sec "run" the <i>dsi-mini-project</i> tool,</li>
 *    <li>@ref compiling_sec "compile" it from source files,</li>
 *    <li>@ref testing_sec "test" the results for correctness using <i>dsi-mini-project-tests</i> tool, and</li>
 *    <li>@ref timing_sec "measure the performance" of different sorting algorithms using <i>dsi-mini-project-timing</i> tool.</li>
 *  </ul>
 *
 * @subsection running_sec Running "dsi-mini-project" tool
 *
 * To join a set of relations using a particular join query and a particular join algorithm, execute the command:
 * <blockquote>
 *   <code>dsi-mini-project &lt;algorithm&gt; -query &lt;query file&gt; -database &lt;database file&gt; [-output &lt;output type&gt;]</code>, where
 * </blockquote>
 * <ul>
 *   <li><code>algorithm</code> \f$\in \{\f$ <code>sortmerge</code>, <code>sortmergetrie</code>, <code>leapfrog</code> \f$\}\f$, and
 *     <ul>
 *       <li><code>sortmerge</code> specifies the cascading sort-merge join algorithm,</li>
 *       <li><code>sortmergetrie</code> specifies the trie-based sort-merge join algorithm, and</li>
 *       <li><code>leapfrog</code> specifies the leapfrog join algorithm,</li>
 *     </ul>
 *   </li>
 *   <li><code>query file</code> specifies the file containing the join query to be executed,</li>
 *   <li><code>database file</code> specifies the file containing the filenames of the files containing the relations, and</li>
 *   <li><code>output type</code> \f$\in \{\f$ <code>tuples</code>, <code>time</code> \f$\}\f$, and
 *     <ul>
 *       <li><code>tuples</code> (default) specifies that the comma-separated tuples from the resulting join relation should be printed to STDOUT,</li>
 *       <li><code>time</code> specifies that the time (in fractions of a second) taken to produce the resulting relation should be printed to STDOUT.</li>
 *     </ul>
 *   </li>
 * </ul>
 *
 *
 * @subsection compiling_sec Compiling "dsi-mini-project" tool
 *
 * To compile the <i>dsi-mini-project</i> tool execute the following commands:
 * <blockquote>
 *  <code>cd bin</code><br/>
 *  <code>make</code>
 * </blockquote>
 *
 * The <code>dsi-mini-project</code> executable should be produced.
 *
 * @subsection testing_sec Testing "dsi-mini-project" tool
 *
 * To test the correctness of the relations produced by <i>dsi-mini-project</i>, <i>dsi-mini-project-tests</i> tool can be used.
 *
 * The <i>dsi-mini-project-tests</i> tool uses the embedded <a href="http://www.h2database.com">H2 RDBMS engine</a> (which supports a subset of SQL standard)
 * to execute given queries on given datasets, and then compares the resulting relations with the ones produced by the <i>dsi-mini-project</i> tool.
 *
 * @subsubsection testing_running_subsubsec Running "dsi-mini-project-tests" tool
 *
 * To run the tests on both datasets ("dataset1-uniform" and "dataset2-zipf"), all queries ("query1" to "query3"),
 * all scales ("scale1" to "scale6") and all algorithms ("sortmerge", "sortmergetrie", "leapfrog"), execute the command:
 * <blockquote>
 *   <code>java -jar dsi-mini-project-tests.jar &lt;path to the dataset&gt; &lt;path to dsi-mini-project executable&gt;</code>,
 * </blockquote>
 *
 * for example <code>java -jar dsi-mini-project-tests.jar ../../dsi-mini-project/data/ ../../dsi-mini-project/bin/dsi-mini-project</code>.
 *
 * An example output of <i>dsi-mini-project-tests</i> tool:
 * <pre>
 * +------------+-------------------+-----------+----------+----------------+
 * | RESULT     | DATASET           | SCALE     | QUERY    | ALGORITHM      |
 * +------------+-------------------+-----------+----------+----------------+
 * | [PASS]     | dataset1-uniform  | scale1    | query1   | sortmerge      |
 * | [PASS]     | dataset1-uniform  | scale1    | query1   | sortmergetrie  |
 * | [PASS]     | dataset1-uniform  | scale1    | query1   | leapfrog       |
 * | [PASS]     | dataset1-uniform  | scale1    | query2   | sortmerge      |
 * | [PASS]     | dataset1-uniform  | scale1    | query2   | sortmergetrie  |
 * | [PASS]     | dataset1-uniform  | scale1    | query2   | leapfrog       |
 * | [PASS]     | dataset1-uniform  | scale1    | query3   | sortmerge      |
 * | [PASS]     | dataset1-uniform  | scale1    | query3   | sortmergetrie  |
 * | [PASS]     | dataset1-uniform  | scale1    | query3   | leapfrog       |
 * | [PASS]     | dataset1-uniform  | scale2    | query1   | sortmerge      |
 * | [PASS]     | dataset1-uniform  | scale2    | query1   | sortmergetrie  |
 * | [PASS]     | dataset1-uniform  | scale2    | query1   | leapfrog       |
 * | [PASS]     | dataset1-uniform  | scale2    | query2   | sortmerge      |
 * ...
 * | [PASS]     | dataset2-zipf     | scale6    | query3   | leapfrog       |
 * +------------+-------------------+-----------+----------+----------------+
 * Overal result: PASS
 * Passed tests: 108, failed tests: 0, total tests: 108
 * </pre>
 *
 * @subsubsection testing_compiling_subsubsec Compiling "dsi-mini-project-tests" tool
 *
 * To compile the <i>dsi-mini-project-tests</i> tool execute the following commands:
 * <blockquote>
 *  <code>javac -d bin -sourcepath src -cp lib/h2-1.3.170.jar src/uk/ac/ox/cs/c875114/</code><code>*.java</code><br/>
 *  <code>cd bin</code><br/>
 *  <code>jar cfm dsi-mini-project-tests.jar manifest.txt uk/ac/ox/cs/c875114</code>
 * </blockquote>
 *
 * @subsection further_testing_subsec Further testing
 *
 * @subsubsection memory_subsubsec Memory management
 *
 * The <i>dsi-mini-project</i> tool has been tested using <a href="http://valgrind.org/info/tools.html#memcheck">Valgrind's Memcheck tool</a>, to ensure that it does not:
 * <ul>
 *  <li>access memory which it shouldn't (areas not yet allocated, areas that have been freed, areas past the end of heap blocks, inaccessible areas of the stack),</li>
 *  <li>use uninitialised values,</li>
 *  <li>leak memory,</li>
 *  <li>do bad frees of heap blocks (double frees, mismatched frees),</li>
 *  <li>pass overlapping source and destination memory blocks to memcpy() and related functions.</li>
 * </ul>
 *
 * @image html valgrind.png
 *
 * Memcheck tool reported no problems on all algorithms (cascading sort-merge join, trie-based sort-merge join and leapfrog join).
 *
 * @subsubsection call_timing_subsubsec Call timing
 *
 * The "hot-path" call graph analysis of the <i>dsi-mini-project</i> tool has been performend using
 * <a href="http://valgrind.org/info/tools.html#callgrind">Valgrind's Callgrind tool</a> and visualized using <a href="http://kcachegrind.sourceforge.net">KCacheGrind</a>
 * tool, to ensure that the implementation was not bottle-necked by I/O operations and the actual algorithm performance was being measured.
 *
 * @image html kcachegrind.png
 *
 * @subsection timing_sec Timing the performance of "dsi-mini-project" tool
 *
 *  The <i>dsi-mini-project-timing</i> tool can be used to compare the performance of all three
 *  multi-way join algorithms (cascading sort-merge join, trie-based sort-merge join and leapfrog join)
 *  on all datasets ("dataset1-uniform" and "dataset2-zipf"), all queries ("query1" to "query3") and all scales
 *  ("scale1" to "scale6").
 *
 *  For each algorithm, dataset, query and scale configuration, <i>dsi-mini-project-timing</i> tool
 *  reports an arithmetic average of elapsed time in three timing runs (running <i>dsi-mini-project</i> with "-output time" flag),
 *  in fractions of a second.
 *
 * @subsubsection timing_running_subsubsec Running "dsi-mini-project-timing" tool
 *
 * To gather the running time averages of all three algorithms on all datasets, queries and scales, execute the command:
 * <blockquote>
 *   <code>java -jar dsi-mini-project-timing.jar &lt;path to the dataset&gt; &lt;path to dsi-mini-project executable&gt;</code>,
 * </blockquote>
 * for example <code>java -jar dsi-mini-project-timing.jar ../../dsi-mini-project/data/ ../../dsi-mini-project/bin/dsi-mini-project</code>.
 *
 * An example output of <i>dsi-mini-project-timing</i> tool:
 * <pre>
 * dataset1-uniform        scale1  query1  sortmerge       0.000173
 * dataset1-uniform        scale1  query1  sortmergetrie   0.000120
 * dataset1-uniform        scale1  query1  leapfrog        0.000180
 * dataset1-uniform        scale1  query2  sortmerge       0.002718
 * dataset1-uniform        scale1  query2  sortmergetrie   0.002009
 * dataset1-uniform        scale1  query2  leapfrog        0.003261
 * dataset1-uniform        scale1  query3  sortmerge       0.003579
 * dataset1-uniform        scale1  query3  sortmergetrie   0.004395
 * dataset1-uniform        scale1  query3  leapfrog        0.004610
 * dataset1-uniform        scale2  query1  sortmerge       0.000305
 * ...
 * dataset2-zipf           scale6  query3  sortmergetrie   4607.070000
 * dataset2-zipf           scale6  query3  leapfrog        8962.096667
 * </pre>
 *
 * @subsubsection timing_compiling_subsubsec Compiling "dsi-mini-project-timing" tool
 *
 * To compile the <i>dsi-mini-project-timing</i> tool execute the following commands:
 * <blockquote>
 *  <code>javac -d bin -sourcepath src -cp src/uk/ac/ox/cs/c875114/</code><code>*.java</code><br/>
 *  <code>cd bin</code><br/>
 *  <code>jar cfm dsi-mini-project-timing.jar manifest.txt uk/ac/ox/cs/c875114</code>
 * </blockquote>
 */
#include <iostream>
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

using namespace c875114;

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

    // Set up the output stream: if "-output time" flag is specified, only the time measurement
    // will be written to STDOUT; otherwise the joined relation will be printed to STDOUT.
    std::ostream* output_stream = NULL;
    if (!arguments.output_time)
    {
        output_stream = &std::cout;
    }

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
            ITrieIterator<int>* join_trie_iterator = (kSortMergeTrie == arguments.join_algorithm_type) ? (ITrieIterator<int>*)new MultiwaySortMergeJoinTrieIterator(*relations, *query) :
                    (ITrieIterator<int>*)new LeapfrogJoinTrieIterator(*relations, *query);
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
    }

	return EXIT_SUCCESS;
}

void PrintUsageMessage()
{
    std::cerr << "Usage: \"dsi-mini-project <algorithm> -query <query file> -database <database file> [-output <output type>]\", where" << std::endl;
    std::cerr << " - <algorithm> is one of { \"sortmerge\", \"sortmergetrie\", \"leapfrog\" }, and" << std::endl;
    std::cerr << " - <output type> is one of { \"relation\", \"time\" }."<< std::endl;
}
