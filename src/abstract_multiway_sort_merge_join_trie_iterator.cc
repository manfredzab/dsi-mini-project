#include <iostream>

#include <algorithm>
#include <vector>

#include "../include/abstract_multiway_sort_merge_join_trie_iterator.h"
#include "../include/trie_trie_iterator.h"
#include "../include/binary_search_tree_trie_iterator.h"
#include "../include/multiway_sort_merge_join_iterator.h"
#include "../include/leapfrog_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::string;
using std::vector;
using std::map;

template <class TTrieIterator, class TJoinIterator>
AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::AbstractMultiwaySortMergeJoinTrieIterator(const std::map<std::string, Relation*>& relations, const Query& query) :
    depth(0),
    number_of_join_attributes(0),
    number_of_result_attributes(0),
    relations(relations),
    query(query)
{
    // Nothing else to do.
};


template <class TTrieIterator, class TJoinIterator>
AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::~AbstractMultiwaySortMergeJoinTrieIterator()
{
    for (typename map<string, TTrieIterator*>::iterator it = trie_iterator_for_relation.begin(); it != trie_iterator_for_relation.end(); ++it)
    {
        delete it->second;
    }

    for (typename map<int, TJoinIterator*>::iterator it = join_iterator_for_depth.begin(); it != join_iterator_for_depth.end(); ++it)
    {
        delete it->second;
    }
}


template <class TTrieIterator, class TJoinIterator>
Status AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::Init()
{
    // Initialize the number of join attributes
    number_of_join_attributes = query.join_attributes.size();

    // Create and initialize a trie iterator for each of the relations involved in the query
    for (unsigned i = 0; i < query.relation_names.size(); i++)
    {
        string relation_name = query.relation_names[i];
        const Relation* relation = relations.find(relation_name)->second;

        this->trie_iterator_for_relation[relation_name] = CreateTrieIteratorForRelation(*relation);
        trie_iterator_for_relation[relation_name]->Init();
    }

    // For each attribute X in the equi-join, create an array of pointers to the trie iterators of the
    // relations in which X occurs, and initialize the sort-merge join instances with those trie iterators.
    for (int attribute_depth = 0; attribute_depth < number_of_join_attributes; attribute_depth++)
    {
        string attribute = query.join_attributes[attribute_depth];

        for (map<string, Relation*>::const_iterator it = relations.begin(); it != relations.end(); ++it)
        {
            Relation* current_db_relation = it->second;
            string current_relation_name = current_db_relation->name;

            // Check whether the current relation is in the list of relations in the query (i.e. whether an iterator was created for it),
            // and whether the current relation contains the attribute in question.
            if (trie_iterator_for_relation.find(current_relation_name) != trie_iterator_for_relation.end() &&
                find(current_db_relation->attribute_names.begin(), current_db_relation->attribute_names.end(), attribute) != current_db_relation->attribute_names.end())
            {
                trie_iterators_for_depth[attribute_depth].push_back(trie_iterator_for_relation[current_relation_name]);
            }
        }

        join_iterator_for_depth[attribute_depth] = CreateJoinIteratorForTrieIterators(trie_iterators_for_depth[attribute_depth]);
    }

    // For each of the attributes Y which are present in the original relations, but not in the equi-join, initialize
    // the trie iterators to their respective relations.
    int last_attribute = query.join_attributes.size();
    for (unsigned i = 0; i < query.relation_names.size(); i++)
    {
        Relation* current_db_relation = relations.find(query.relation_names[i])->second;
        for (unsigned j = 0; j < current_db_relation->attribute_names.size(); j++)
        {
            string attribute = current_db_relation->attribute_names[j];
            if (find(query.join_attributes.begin(), query.join_attributes.end(), attribute) == query.join_attributes.end())
            {
                trie_iterators_for_depth[last_attribute++].push_back(trie_iterator_for_relation[current_db_relation->name]);
            }
        }
    }

    // Initialize the current attribute depth and the total number of attributes in the result relation
    number_of_result_attributes = trie_iterators_for_depth.size();
    depth = -1;

    // Initialize the key multiplicity stack
    key_multiplicity_stack.push_back(1);

    return kOK;
}


template <class TTrieIterator, class TJoinIterator>
Status AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::Open()
{
    Status status = kOK;

    depth++;

    if (depth < number_of_join_attributes) // We are still merging join variables
    {
        for (unsigned i = 0; i < trie_iterators_for_depth[depth].size(); i++)
        {
            Status sub_status = trie_iterators_for_depth[depth][i]->Open();
            if (kOK == status)
            {
                status = sub_status;
            }
        }

        if (kOK == status)
        {
            join_iterator_for_depth[depth]->Init();

            int join_iterator_key_multiplicity;
            join_iterator_for_depth[depth]->Multiplicity(&join_iterator_key_multiplicity);

            key_multiplicity_stack.push_back(join_iterator_key_multiplicity);

            if (AtEnd())
            {
                status = kFail;
                Up(); // Undo changes
            }
        }
    }
    else // We are merging variables not involved in the join
    {
        if (depth < number_of_result_attributes)
        {
            // Only a single relation trie iterator can be associated with the variable
            // which is not involved in join.
            status = trie_iterators_for_depth[depth][0]->Open();
        }
        else
        {
            status = kFail;
            depth--;
        }

        if (kOK == status)
        {
            int current_trie_iterator_multiplicity;
            trie_iterators_for_depth[depth][0]->Multiplicity(&current_trie_iterator_multiplicity);

            key_multiplicity_stack.push_back(current_trie_iterator_multiplicity);
        }
    }

    return status;
}


template <class TTrieIterator, class TJoinIterator>
Status AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::Up()
{
    if (AtRoot())
    {
        return kFail;
    }

    Status status = kOK;

    if (depth < number_of_join_attributes)
    {
        for (unsigned i = 0; i < trie_iterators_for_depth[depth].size(); i++)
        {
            Status sub_status = trie_iterators_for_depth[depth][i]->Up();
            if (kOK == status)
            {
                status = sub_status;
            }
        }
    }
    else
    {
        status = trie_iterators_for_depth[depth][0]->Up();
    }

    if (kOK == status)
    {
        depth--;

        key_multiplicity_stack.pop_back();
    }

    return status;
}

template <class TTrieIterator, class TJoinIterator>
Status AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::Key(int* result)
{
    if (AtRoot())
    {
        return kFail;
    }

    if (depth < number_of_join_attributes)
    {
        return join_iterator_for_depth[depth]->Key(result);
    }
    else
    {
        return trie_iterators_for_depth[depth][0]->Key(result);
    }
}


template <class TTrieIterator, class TJoinIterator>
Status AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::Multiplicity(int* result)
{
    *result = this->key_multiplicity_stack.back();
    return kOK;
}


template <class TTrieIterator, class TJoinIterator>
Status AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::Next()
{
    if (AtRoot())
    {
        return kFail;
    }

    // If there is more than one key at this level, stay in place
    if (key_multiplicity_stack.back() > 1)
    {
        key_multiplicity_stack.back()--;
        return kOK;
    }

    // Move to the next key
    Status status = (depth < number_of_join_attributes) ? join_iterator_for_depth[depth]->Next() :
                                                          trie_iterators_for_depth[depth][0]->Next();

    // Update the key multiplicity stack
    if (kOK == status)
    {
        int current_iterator_multiplicity;
        if (depth < number_of_join_attributes)
        {
            join_iterator_for_depth[depth]->Multiplicity(&current_iterator_multiplicity);
        }
        else
        {
            trie_iterators_for_depth[depth][0]->Multiplicity(&current_iterator_multiplicity);
        }

        key_multiplicity_stack.pop_back();
        key_multiplicity_stack.push_back(current_iterator_multiplicity);
    }

    return status;
}


template <class TTrieIterator, class TJoinIterator>
bool AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::AtEnd()
{
    if (depth < number_of_join_attributes)
    {
        return join_iterator_for_depth[depth]->AtEnd();
    }
    else
    {
        return trie_iterators_for_depth[depth][0]->AtEnd();
    }
}


template <class TTrieIterator, class TJoinIterator>
bool AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::AtRoot()
{
    return (-1 == depth);
}


template <class TTrieIterator, class TJoinIterator>
int AbstractMultiwaySortMergeJoinTrieIterator<TTrieIterator, TJoinIterator>::Arity()
{
    return number_of_result_attributes;
}

template class AbstractMultiwaySortMergeJoinTrieIterator<TrieTrieIterator, MultiwaySortMergeJoinIterator>;
template class AbstractMultiwaySortMergeJoinTrieIterator<BinarySearchTreeTrieIterator, LeapfrogJoinIterator>;

} /* namespace uk_ac_ox_cs_c875114 */
