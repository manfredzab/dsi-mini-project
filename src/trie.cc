#include <algorithm>
#include "../include/trie.h"
#include "../include/simple_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

/**
 * Constructs a trie for a given relation (in the relation's attribute order, i.e.
 * the leaf nodes of the trie correspond to the last attribute of the relation).
 * @param relation Relation for which the trie should be constructed.
 */
Trie::Trie(const Relation& relation)
{
    // Store the trie depth
    this->trie_depth = relation.attribute_names.size();

    // Initialize the root note
    this->root.parent = NULL;
    this->root.key = 0;
    this->root.multiplicity = 1;
    this->root.current_child = this->root.children.begin();

    // Build the trie by iterating through the relation and inserting tuples
    SimpleIterator relation_iterator(relation);

    int* current_tuple;
    while (!relation_iterator.AtEnd())
    {
        // Get next tuple
        relation_iterator.Key(&current_tuple);
        relation_iterator.Next();

        // Insert it into the trie
        this->Insert(current_tuple);
    }
}

/**
 * Releases the resources held by the trie (including all memory occupied by the
 * trie nodes).
 */
Trie::~Trie()
{
    // Release the memory occupied by the trie node by navigating the trie in the depth-first manner
    vector<TrieNode*> nodes_to_delete;

    // Insert all children of the root into the "to be deleted" vector
    nodes_to_delete.insert(nodes_to_delete.begin(), this->root.children.begin(), this->root.children.end());
    while (!nodes_to_delete.empty())
    {
        // Take the node that was inserted most recently
        TrieNode* current_node = nodes_to_delete.back();
        nodes_to_delete.pop_back();

        // Insert its children into "to be deleted" vector
        nodes_to_delete.insert(nodes_to_delete.end(), current_node->children.begin(), current_node->children.end());

        // Delete the most recently inserted node
        delete current_node;
    }
}

/**
 * Inserts a given tuple into the trie.
 * @param tuple A pointer to the tuple that should be inserted into the trie.
 */
void Trie::Insert(const int* tuple)
{
    TrieNode* currentNode = &this->root;
    for (int i = 0; i < this->trie_depth; i++)
    {
        // Find the entry to insert in the children list
        TrieNode* trie_node_to_insert = new TrieNode();
        trie_node_to_insert->key = tuple[i];

        vector<TrieNode*>::iterator insert_position_node = lower_bound(currentNode->children.begin(),
                                                                       currentNode->children.end(),
                                                                       trie_node_to_insert,
                                                                       CompareTrieNodeKeys);

        // If the node with this key is not present in the children list, finish initializing members
        // and insert it.
        if (insert_position_node == currentNode->children.end())
        {
            trie_node_to_insert->parent = currentNode;
            trie_node_to_insert->multiplicity = 1;
            trie_node_to_insert->current_child = trie_node_to_insert->children.begin();

            insert_position_node = currentNode->children.insert(insert_position_node, trie_node_to_insert);
        }
        else
        {
            // Node with this key already exists in the trie, and the new node is unnecessary
            delete trie_node_to_insert;

            // However, if we were at the leaf level, increase the leaf's multiplicity
            if (i == this->trie_depth - 1)
            {
                (*insert_position_node)->multiplicity++;
            }
        }

        currentNode = *insert_position_node;
    }
}

} /* namespace uk_ac_ox_cs_c875114 */
