#include <algorithm>
#include "../include/trie.h"
#include "../include/simple_iterator.h"

Trie::Trie(const Relation& relation)
{
    this->trie_depth = relation.attribute_names.size();

    this->root.parent = NULL;
    this->root.key = 0;
    this->root.current_child = this->root.children.begin();

    // Build the trie
    for (std::vector<int*>::const_iterator tuple_iterator = relation.data.begin(); tuple_iterator != relation.data.end(); ++tuple_iterator)
    {
        this->Insert(*tuple_iterator);
    }
}

Trie::~Trie()
{
    std::vector<TrieNode*> nodes_to_delete;

    nodes_to_delete.insert(nodes_to_delete.begin(), this->root.children.begin(), this->root.children.end());
    while (!nodes_to_delete.empty())
    {
        TrieNode* current_node = nodes_to_delete.back();
        nodes_to_delete.pop_back();

        nodes_to_delete.insert(nodes_to_delete.end(), current_node->children.begin(), current_node->children.end());

        delete current_node;
    }
}


// TODO: could be optimized
void Trie::Insert(const int* tuple)
{
    TrieNode* currentNode = &this->root;
    for (int i = 0; i < this->trie_depth; i++)
    {
        // Find the entry to insert in the children list
        TrieNode* trie_node_to_insert = new TrieNode();
        trie_node_to_insert->parent = currentNode;
        trie_node_to_insert->key = tuple[i];
        trie_node_to_insert->current_child = trie_node_to_insert->children.begin();

        std::vector<TrieNode*>::iterator insert_position = lower_bound(currentNode->children.begin(),
                                                                       currentNode->children.end(),
                                                                       trie_node_to_insert,
                                                                       CompareTrieNodeKeys);

        // If the node with this key is not present in the children list (and we are not at the leaf
        // level), insert it.
        if ((insert_position == currentNode->children.end()) || (i == this->trie_depth - 1))
        {
            insert_position = currentNode->children.insert(insert_position, trie_node_to_insert);
        }
        else
        {
            // Node with this key already exists in the trie, and the new node is unnecessary
            delete trie_node_to_insert;
        }

        currentNode = *insert_position;
    }
}

bool CompareTrieNodeKeys(TrieNode* first, TrieNode* second)
{
    return (first->key < second->key);
}
