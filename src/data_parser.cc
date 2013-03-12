#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

#include "../include/data_parser.h"

Relation*                 ParseRelation(const char* database_file_name, std::string relation_line);
Relation*                 ParseRelation(const char* relation_file_name, std::string relation_name, const std::vector<std::string>& attribute_names);
int*                      ParseRelationTuple(std::string relation_tuple_line, int attribute_count);
std::vector<std::string>* TokenizeString(const std::string& input_string, const char character);
void                      RemoveStringWhitespace(std::string& input_string);
int                       StringToInt(const std::string& input_string);
std::string               GetFilePath(const char* file_name);


Query* DataParser::ParseQuery(const char* file_name)
{
    Query* result_query = NULL;

    std::ifstream query_file(file_name);

    if (query_file.is_open())
    {
        std::string relation_line, attribute_line;
        getline(query_file, relation_line);
        getline(query_file, attribute_line);

        RemoveStringWhitespace(relation_line);
        std::vector<std::string>* relations = TokenizeString(relation_line, ',');

        RemoveStringWhitespace(attribute_line);
        std::vector<std::string>* attributes = TokenizeString(attribute_line, ',');

        result_query = new Query();
        result_query->relation_names.insert(result_query->relation_names.begin(), relations->begin(), relations->end());
        result_query->join_attributes.insert(result_query->join_attributes.begin(), attributes->begin(), attributes->end());

        delete relations;
        delete attributes;

        query_file.close();
    }

    return result_query;
}


std::map<std::string, Relation*>* DataParser::ParseDatabase(const char* file_name)
{
    std::map<std::string, Relation*>* relation_map = new std::map<std::string, Relation*>();

    std::ifstream database_file(file_name);

    std::string relation_line;
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
        std::cerr << "Fatal error: Could not open the database file " << file_name;
    }

    return relation_map;
}


Relation* ParseRelation(const char* database_file_name, std::string relation_line)
{
    // Remove whitespace characters from relation_line
    RemoveStringWhitespace(relation_line);

    // Tokenize relation_line (splitting on commas)
    std::vector<std::string>* tokens = TokenizeString(relation_line, ',');

    // First token - file name (needs to be made relative to the database path)
    std::string file_path_prefix = GetFilePath(database_file_name);
    std::string file_name = file_path_prefix + (*tokens)[0];

    // Second token - relation name
    std::string relation_name = (*tokens)[1];

    // The rest of the tokens - attributes
    tokens->erase(tokens->begin(), tokens->begin() + 2);

    Relation* result_relation = ParseRelation(file_name.c_str(), relation_name, *tokens);

    delete tokens;
    return result_relation;
}


Relation* ParseRelation(const char* relation_file_name, std::string relation_name, const std::vector<std::string>& attribute_names)
{
    Relation* result = new Relation();

    result->name = relation_name;
    result->attribute_names.insert(result->attribute_names.begin(), attribute_names.begin(), attribute_names.end());

    // Read and parse the data
    int attribute_count = attribute_names.size();

    std::ifstream relation_file(relation_file_name);
    std::string line;
    if (relation_file.is_open())
    {
        while (getline(relation_file, line))
        {
            int* parsed_tuple = ParseRelationTuple(line, attribute_count);

            result->data.push_back(parsed_tuple);
        }

        relation_file.close();
    }
    else
    {
        std::cerr << "Fatal error: could not open the relation file " << relation_file_name;
    }

    return result;
}


int* ParseRelationTuple(std::string relation_tuple_line, int attribute_count)
{
    int* result = new int[attribute_count];

    RemoveStringWhitespace(relation_tuple_line);
    std::vector<std::string>* tokens = TokenizeString(relation_tuple_line, ',');

    for (int i = 0; i < attribute_count; i++)
    {
         result[i] = StringToInt((*tokens)[i]);
    }

    delete tokens;

    return result;
}


std::vector<std::string>* TokenizeString(const std::string& input_string, const char character)
{
    std::istringstream token_stream(input_string);
    std::string token;

    std::vector<std::string>* tokens = new std::vector<std::string>();
    while (getline(token_stream, token, character))
    {
        tokens->push_back(token);
    }

    return tokens;
}


void RemoveStringWhitespace(std::string& input_string)
{
    input_string.erase(remove_if(input_string.begin(), input_string.end(), ::isspace), input_string.end());
}


std::string GetFilePath(const char* file_name)
{
    std::string file_name_string(file_name, 0, 1024); // Path length limit: 1023 characters.

    int last_slash_position = file_name_string.find_last_of("/\\");

    return file_name_string.substr(0, last_slash_position + 1);
}


int StringToInt(const std::string& input_string)
{
    return atoi(input_string.c_str());
}
