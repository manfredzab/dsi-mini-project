#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "../include/data_parser.h"

namespace uk_ac_ox_cs_c875114
{

using std::string;
using std::vector;
using std::map;
using std::ifstream;
using std::istringstream;

/**
 * Parses the query from a given file.
 * @param file_name Query file name.
 * @returns A pointer to the populated Query data structure.
 */
Query* DataParser::ParseQuery(string file_name)
{
    Query* result_query = new Query();

    // Open the query file
    ifstream query_file(file_name.c_str());

    if (query_file.is_open())
    {
        // Read the first two lines
        string relation_line, attribute_line;
        getline(query_file, relation_line);
        getline(query_file, attribute_line);

        // The first line should be the comma-separated list of all relations used by the query;
        // remove whitespaces and break the string on commas to obtain an array of relation names.
        RemoveStringWhitespace(relation_line);
        vector<string>* relations = TokenizeString(relation_line, ',');

        // The second line should be the comma-separated list of all join attributes; remove
        // whitespaces and break the string on commas to obtain an array of join attribute names.
        RemoveStringWhitespace(attribute_line);
        vector<string>* attributes = TokenizeString(attribute_line, ',');

        // Create and populate the Query data structure
        result_query->relation_names.insert(result_query->relation_names.begin(), relations->begin(), relations->end());
        result_query->join_attributes.insert(result_query->join_attributes.begin(), attributes->begin(), attributes->end());

        // Delete the string arrays
        delete relations;
        delete attributes;

        // Close the query file
        query_file.close();
    }
    else
    {
        // If the file cannot be opened, print the error message and return an empty query
        std::cerr << "Fatal error: Could not open the query file " << file_name << std::endl;
    }

    return result_query;
}

/**
 * Parses the database from a given file.
 * @param file_name Database file name.
 * @returns A pointer to the dictionary of parsed relations, indexed by the relation's name.
 */
map<string, Relation*>* DataParser::ParseDatabase(string file_name)
{
    map<string, Relation*>* relation_map = new map<string, Relation*>();

    // Open the database file
    ifstream database_file(file_name.c_str());

    string relation_line;
    if (database_file.is_open())
    {
        // Read the relation line from the database file
        while (getline(database_file, relation_line))
        {
            // Parse the relation from the relation line and add it to the result dictionary
            // of parsed relations
            Relation* parsed_relation = ParseRelation(file_name, relation_line);
            (*relation_map)[parsed_relation->name] = parsed_relation;
        }

        // Close the database file
        database_file.close();
    }
    else
    {
        // If the file cannot be opened, print the error message and return an empty dictionary
        std::cerr << "Fatal error: Could not open the database file " << file_name << std::endl;
    }

    return relation_map;
}

/**
 * Parses the relation given the database file name and the formatted relation string
 * from the database file (comma-separated string consisting of relative location of relation on
 * disk, name of relation and relation attributes.
 * @param database_file_name Database file name.
 * @param relation_line Comma-separated string consisting of relative location of relation on
 *                      disk, name of relation and relation attributes.
 * @returns A pointer to the populated Relation structure.
 */
Relation* DataParser::ParseRelation(string database_file_name, string relation_line)
{
    // Remove whitespace characters from relation line
    RemoveStringWhitespace(relation_line);

    // Tokenize relation line (splitting on commas)
    vector<string>* tokens = TokenizeString(relation_line, ',');

    // First token must be the file name (needs to be made relative to the database path)
    string file_path_prefix = GetFilePath(database_file_name);
    string file_name = file_path_prefix + (*tokens)[0];

    // Second token must be the relation name
    string relation_name = (*tokens)[1];

    // The rest of the tokens must be attributes
    tokens->erase(tokens->begin(), tokens->begin() + 2);

    Relation* result_relation = ParseRelation(file_name.c_str(), relation_name, *tokens);

    delete tokens;
    return result_relation;
}

/**
 * Parses the relation given the relation file name, relation name and relation attributes.
 * @param relation_file_name Relation file name.
 * @param relation_name      Relation name.
 * @param attribute_names    Relation attributes.
 * @returns A pointer to the populated Relation structure.
 */
Relation* DataParser::ParseRelation(string relation_file_name, string relation_name, const vector<string>& attribute_names)
{
    Relation* result = new Relation();

    // Populate the relation's name and attributes
    result->name = relation_name;
    result->attribute_names.insert(result->attribute_names.begin(), attribute_names.begin(), attribute_names.end());

    // Read and parse the data
    int attribute_count = attribute_names.size();

    // Open the relation file
    ifstream relation_file(relation_file_name.c_str());
    string tuple_line;
    if (relation_file.is_open())
    {
        // Each line in the relation file should contain a tuple, formatted as a comma-separated
        // list of integers
        while (getline(relation_file, tuple_line))
        {
            // Parse the tuple from the tuple line
            int* parsed_tuple = ParseRelationTuple(tuple_line, attribute_count);

            result->data.push_back(parsed_tuple);
        }

        relation_file.close();
    }
    else
    {
        // If the relation file cannot be opened, print the error message
        std::cerr << "Fatal error: could not open the relation file " << relation_file_name << std::endl;
    }

    return result;
}

/**
 * Parses the tuple from a comma-separated string of integers.
 * @param relation_tuple_line Comma-separated string of integers.
 * @param attribute_count     Tuple size (number of attributes in the tuple).
 * @returns A pointer to the location of the memory where the tuple is stored as a
 *          sequence of integers.
 */
int* DataParser::ParseRelationTuple(string relation_tuple_line, int attribute_count)
{
    int* result = new int[attribute_count];

    RemoveStringWhitespace(relation_tuple_line);
    vector<string>* tokens = TokenizeString(relation_tuple_line, ',');

    for (int i = 0; i < attribute_count; i++)
    {
         result[i] = ConvertStringToInt((*tokens)[i]);
    }

    delete tokens;

    return result;
}

/**
 * Tokenizes the string based on a given separator character.
 * @param input_string String to be tokenized.
 * @param character    Separator character.
 * @returns An array of string tokens.
 */
vector<string>* DataParser::TokenizeString(const string& input_string, const char character)
{
    istringstream token_stream(input_string);
    string token;

    vector<string>* tokens = new vector<string>();
    while (getline(token_stream, token, character))
    {
        tokens->push_back(token);
    }

    return tokens;
}

/**
 * Removes whitespace from the string (in place).
 * @param input_string String from which the whitespace should be removed.
 */
void DataParser::RemoveStringWhitespace(string& input_string)
{
    input_string.erase(remove_if(input_string.begin(), input_string.end(), ::isspace), input_string.end());
}

/**
 * Gets the file path from a given file name.
 * @param file_name File name from which the file path should be extracted.
 * @returns File path extracted from a given file name.
 */
string DataParser::GetFilePath(string file_name)
{
    // Find the last position of a back- or forward-slash.
    int last_slash_position = file_name.find_last_of("/\\");

    // Return everything until then (including the slash).
    return file_name.substr(0, last_slash_position + 1);
}

/**
 * Converts a given string to integer.
 * @param input_string String to convert.
 * @returns Converted integer.
 */
int DataParser::ConvertStringToInt(const string& input_string)
{
    return atoi(input_string.c_str());
}


} /* namespace uk_ac_ox_cs_c875114 */
