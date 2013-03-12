#include <iostream>

#include <algorithm>
#include <vector>

#include "../include/sort_merge_join.h"
#include "../include/simple_trie_iterator.h"

Relation* SortMergeJoin::Join(const std::map<std::string, Relation*>& relations, const Query& query)
{
    // Create an iterator for each of the relations involved in the query
    std::map<std::string, SimpleTrieIterator*> relation_trie_iterators;
    for (unsigned int i = 0; i < query.relation_names.size(); i++)
    {
        std::string relation_name = query.relation_names[i];
        const Relation* relation = relations.find(relation_name)->second;

        relation_trie_iterators[relation_name] = new SimpleTrieIterator(*relation);
    }

    // For each of the attributes in the equi-join, identify in which relations they occur
    std::map<std::string, std::vector<std::string> > attribute_relations;
    for (unsigned int i = 0; i < query.join_attributes.size(); i++)
    {
        std::string attribute = query.join_attributes[i];

        for (std::map<std::string, Relation*>::const_iterator it = relations.begin(); it != relations.end(); ++it)
        {
            Relation* current_db_relation = it->second;

            // Check whether the current relation is in the list of relations in the query (i.e. whether an iterator was created for it),
            // and whether the current relation contains the attribute in question.
            if (relation_trie_iterators.find(current_db_relation->name) != relation_trie_iterators.end() &&
                find(current_db_relation->attribute_names.begin(), current_db_relation->attribute_names.end(), attribute) != current_db_relation->attribute_names.end())
            {
                attribute_relations[attribute].push_back(current_db_relation->name);
            }
        }
    }

//    for (int i = 0; i < query.join_attributes.size(); i++)
//    {
//        std::cout << "Attribute: " << query.join_attributes[i] << std::endl;
//
//        std::cout << "Associated relations:";
//        std::vector<std::string>& relations_for_attribute = attribute_relations[query.join_attributes[i]];
//        for (int j = 0; j < relations_for_attribute.size(); j++)
//        {
//            std::cout << " " << relations_for_attribute[j];
//        }
//        std::cout << std::endl;
//    }

    // Release memory
    for (std::map<std::string, SimpleTrieIterator*>::iterator it = relation_trie_iterators.begin(); it != relation_trie_iterators.end(); ++it)
    {
        delete it->second;
    }
}
