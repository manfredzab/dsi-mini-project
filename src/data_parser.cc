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
using std::cerr;


Relation*       ParseRelation(string database_file_name, string relation_line);
Relation*       ParseRelation(string relation_file_name, string relation_name, const vector<string>& attribute_names);
int*            ParseRelationTupleKey(string relation_tuple_line, int attribute_count);
vector<string>* TokenizeString(const string& input_string, const char character);
void            RemoveStringWhitespace(string& input_string);
int             StringToInt(const string& input_string);
string          GetFilePath(string file_name);


Query* DataParser::ParseQuery(string file_name)
{
    Query* result_query = NULL;

    ifstream query_file(file_name.c_str());

    if (query_file.is_open())
    {
        string relation_line, attribute_line;
        getline(query_file, relation_line);
        getline(query_file, attribute_line);

        RemoveStringWhitespace(relation_line);
        vector<string>* relations = TokenizeString(relation_line, ',');

        RemoveStringWhitespace(attribute_line);
        vector<string>* attributes = TokenizeString(attribute_line, ',');

        result_query = new Query();
        result_query->relation_names.insert(result_query->relation_names.begin(), relations->begin(), relations->end());
        result_query->join_attributes.insert(result_query->join_attributes.begin(), attributes->begin(), attributes->end());

        delete relations;
        delete attributes;

        query_file.close();
    }

    return result_query;
}


map<string, Relation*>* DataParser::ParseDatabase(string file_name)
{
    map<string, Relation*>* relation_map = new map<string, Relation*>();

    ifstream database_file(file_name.c_str());

    string relation_line;
    if (database_file.is_open())
    {
        while (getline(database_file, relation_line))
        {
            Relation* parsed_relation = ParseRelation(file_name, relation_line);

            (*relation_map)[parsed_relation->name] = parsed_relation;
        }

        database_file.close();
    }
    else
    {
        cerr << "Fatal error: Could not open the database file " << file_name;
    }

    return relation_map;
}


Relation* ParseRelation(string database_file_name, string relation_line)
{
    // Remove whitespace characters from relation_line
    RemoveStringWhitespace(relation_line);

    // Tokenize relation_line (splitting on commas)
    vector<string>* tokens = TokenizeString(relation_line, ',');

    // First token - file name (needs to be made relative to the database path)
    string file_path_prefix = GetFilePath(database_file_name);
    string file_name = file_path_prefix + (*tokens)[0];

    // Second token - relation name
    string relation_name = (*tokens)[1];

    // The rest of the tokens - attributes
    tokens->erase(tokens->begin(), tokens->begin() + 2);

    Relation* result_relation = ParseRelation(file_name.c_str(), relation_name, *tokens);

    delete tokens;
    return result_relation;
}


Relation* ParseRelation(string relation_file_name, string relation_name, const vector<string>& attribute_names)
{
    Relation* result = new Relation();

    result->name = relation_name;
    result->attribute_names.insert(result->attribute_names.begin(), attribute_names.begin(), attribute_names.end());

    // Read and parse the data
    int attribute_count = attribute_names.size();

    ifstream relation_file(relation_file_name.c_str());
    string line;
    if (relation_file.is_open())
    {
        while (getline(relation_file, line))
        {
            Tuple parsed_tuple = { ParseRelationTupleKey(line, attribute_count), 1 };

            // Check if the current tuple is a duplicate of the previous tuple
            if (!result->data.empty() && Tuple::AreKeysEqual(parsed_tuple, result->data.back(), attribute_count))
            {
                result->data.back().multiplicity++;
                delete[] parsed_tuple.key;
            }
            else
            {
                result->data.push_back(parsed_tuple);
            }
        }

        relation_file.close();
    }
    else
    {
        cerr << "Fatal error: could not open the relation file " << relation_file_name;
    }

    return result;
}


int* ParseRelationTupleKey(string relation_tuple_line, int attribute_count)
{
    int* result_key = new int[attribute_count];

    RemoveStringWhitespace(relation_tuple_line);
    vector<string>* tokens = TokenizeString(relation_tuple_line, ',');

    for (int i = 0; i < attribute_count; i++)
    {
        result_key[i] = StringToInt((*tokens)[i]);
    }

    delete tokens;

    return result_key;
}


vector<string>* TokenizeString(const string& input_string, const char character)
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


void RemoveStringWhitespace(string& input_string)
{
    input_string.erase(remove_if(input_string.begin(), input_string.end(), ::isspace), input_string.end());
}


string GetFilePath(string file_name)
{
    int last_slash_position = file_name.find_last_of("/\\");

    return file_name.substr(0, last_slash_position + 1);
}


int StringToInt(const string& input_string)
{
    return atoi(input_string.c_str());
}

} /* namespace uk_ac_ox_cs_c875114 */
