#include <iostream>

#include <algorithm>
#include <vector>

#include "../include/sort_merge_join_trie_iterator.h"

SortMergeJoinTrieIterator::SortMergeJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query)
{
    // Create an iterator for each of the relations involved in the query
    for (unsigned i = 0; i < query.relation_names.size(); i++)
    {
        std::string relation_name = query.relation_names[i];
        const Relation* relation = relations.find(relation_name)->second;

        this->trie_iterator_for_relation[relation_name] = new SimpleTrieIterator(*relation);
    }

    // For each attribute x in the equi-join, create an array of pointers to the trie iterators of the
    // relations in which x occurs, and initialize the sort merge join instances with those trie iterators.
    for (unsigned attribute_depth = 0; attribute_depth < query.join_attributes.size(); attribute_depth++)
    {
        std::string attribute = query.join_attributes[attribute_depth];

        for (std::map<std::string, Relation*>::const_iterator it = relations.begin(); it != relations.end(); ++it)
        {
            Relation* current_db_relation = it->second;
            std::string current_relation_name = current_db_relation->name;

            // Check whether the current relation is in the list of relations in the query (i.e. whether an iterator was created for it),
            // and whether the current relation contains the attribute in question.
            if (trie_iterator_for_relation.find(current_relation_name) != trie_iterator_for_relation.end() &&
                find(current_db_relation->attribute_names.begin(), current_db_relation->attribute_names.end(), attribute) != current_db_relation->attribute_names.end())
            {
                trie_iterators_for_depth[attribute_depth].push_back(trie_iterator_for_relation[current_relation_name]);
            }
        }

        join_iterator_for_depth[attribute_depth] = new SortMergeJoinIterator(trie_iterators_for_depth[attribute_depth]);
    }

    // Initialize the current attribute depth
    depth = -1;
}


SortMergeJoinTrieIterator::~SortMergeJoinTrieIterator()
{
    for (std::map<std::string, SimpleTrieIterator*>::iterator it = trie_iterator_for_relation.begin(); it != trie_iterator_for_relation.end(); ++it)
    {
        delete it->second;
    }

    for (std::map<int, SortMergeJoinIterator*>::iterator it = join_iterator_for_depth.begin(); it != join_iterator_for_depth.end(); ++it)
    {
        delete it->second;
    }
}


Status SortMergeJoinTrieIterator::Open()
{
    Status status = kOK;

    depth++;

    for (unsigned i = 0; i < trie_iterators_for_depth[depth].size(); i++)
    {
        Status sub_status = trie_iterators_for_depth[depth][i]->Open();
        if (status == kOK)
        {
            status = sub_status;
        }
    }

    if (kOK == status)
    {
        join_iterator_for_depth[depth]->Init();

        if (AtEnd())
        {
            status = kFail;
            Up(); // Undo changes
        }
    }

    return status;
}


Status SortMergeJoinTrieIterator::Up()
{
    Status status = kOK;

    for (unsigned i = 0; i < trie_iterators_for_depth[depth].size(); i++)
    {
        Status sub_status = trie_iterators_for_depth[depth][i]->Up();
        if (status == kOK)
        {
            status = sub_status;
        }
    }

    depth--;

    return status;
}


Status SortMergeJoinTrieIterator::Key(int* result)
{
    if (AtRoot())
    {
        return kFail;
    }

    return join_iterator_for_depth[depth]->Key(result);
}


Status SortMergeJoinTrieIterator::Next()
{
    return join_iterator_for_depth[depth]->Next();
}


bool SortMergeJoinTrieIterator::AtEnd()
{
    return join_iterator_for_depth[depth]->AtEnd();
}


bool SortMergeJoinTrieIterator::AtRoot()
{
    return (-1 == depth);
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

