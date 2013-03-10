#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "data_parser.h"

std::vector<Relation*>& DataParser::ParseDatabase(const char* file_name)
{
    std::vector<Relation*>* result = new std::vector<Relation*>();

    std::ifstream database_file(file_name);

    std::string relation_line;
    if (database_file.is_open())
    {
        while (getline(database_file, relation_line))
        {
            Relation* parsed_relation = ParseRelation(file_name, relation_line);

            result->push_back(parsed_relation);
        }

        database_file.close();
    }
    else
    {
        std::cerr << "Fatal error: Could not open the database file " << file_name;
    }

    return *result;
}

Relation* DataParser::ParseRelation(const char* database_file_name, std::string relation_line)
{
    // Remove whitespace characters from relation_line
    relation_line.erase(remove_if(relation_line.begin(), relation_line.end(), ::isspace), relation_line.end());

    // Tokenize relation_line (splitting on commas)
    std::istringstream token_stream(relation_line);
    std::string token;

    std::vector<std::string> tokens;
    while (getline(token_stream, token, ','))
    {
        tokens.push_back(token);
    }

    // First token - file name (needs to be made relative to the database path)
    std::string file_name_string(database_file_name, 0, 1024); // Path length limit: 1023 characters.
    int last_slash_position = file_name_string.find_last_of("/\\");
    std::string file_path_prefix = file_name_string.substr(0, last_slash_position + 1);

    std::string file_name = file_path_prefix + tokens[0];

    // Second token - relation name
    std::string relation_name = tokens[1];

    // The rest of the tokens - attributes
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    return ParseRelation(file_name.c_str(), relation_name, tokens);
}


Relation* DataParser::ParseRelation(const char* file_name, std::string relation_name, std::vector<std::string>& attribute_names)
{
    Relation* result = new Relation();

    result->name = relation_name;
    result->attribute_names = attribute_names;

    // Read and parse the data
    int attribute_count = attribute_names.size();

    std::ifstream relation_file(file_name);
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
        std::cerr << "Fatal error: could not open the relation file " << file_name;
    }

    return result;
}


int* DataParser::ParseRelationTuple(std::string relation_tuple_line, int attribute_count)
{
    int* result = new int[attribute_count];

    std::stringstream line_stream(relation_tuple_line);
    for (int i = 0; i < attribute_count; i++)
    {
        line_stream >> result[i];

        if (line_stream.peek() == ',')
        {
            line_stream.ignore();
        }
    }

    return result;
}
