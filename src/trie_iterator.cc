#include <string>

#include "../include/trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

TrieIterator::TrieIterator(const Relation& relation)// : SimpleIterator(relation)
{
    // Build the trie
    this->trie = new Trie(relation);
    this->current_node = &trie->root;
    this->current_node_multiplicity = trie->root.multiplicity;
    this->at_end = false;
}

TrieIterator::~TrieIterator()
{
    delete this->trie;
}

Status TrieIterator::Open()
{
    if (this->current_node->children.empty())
    {
        return kFail;
    }

    // Mark the first child as being opened
    this->current_node->current_child = this->current_node->children.begin();
    this->at_end = false;

    this->current_node = *(this->current_node->current_child);

    return kOK;
}


Status TrieIterator::Up()
{
    if (this->AtRoot())
    {
        return kFail;
    }

    // Reset the position between children and duplicates for the current node
    this->current_node->position_within_duplicates = 0;

    // Make the current node point to its parent
    this->current_node = this->current_node->parent;

    // Reset "at end" marker
    this->at_end = false;

    return kOK;
}


Status TrieIterator::Key(int* out_key)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *out_key = this->current_node->key;

    return kOK;
}


Status TrieIterator::Multiplicity(int* out_multiplicity)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *out_multiplicity = this->current_node->multiplicity;

    return kOK;
}


Status TrieIterator::Next()
{
    if (this->AtRoot() || this->AtEnd())
    {
        return kFail;
    }

    // Get the pointer to the sibling
    vector<TrieNode*>::iterator right_sibling = this->current_node->parent->current_child + 1;

    // If sibling is out of bounds of the parent's children list, indicate that we have reached the end
    // and DO NOT UPDATE the current node (otherwise all the pointers will be corrupted).
    if (right_sibling == this->current_node->parent->children.end())
    {
        this->at_end = true;
        return kFail;
    }

    // We are not at the end, set the current node pointer to its right sibling.
    this->current_node->parent->current_child = right_sibling;
    this->current_node = *right_sibling;
    return kOK;
}


bool TrieIterator::AtEnd()
{
    return this->at_end;
}


bool TrieIterator::AtRoot()
{
    return (this->current_node == &trie->root);
}

} // namespace uk_ac_ox_cs_c875114
