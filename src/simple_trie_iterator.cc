#include <string>

#include "../include/simple_trie_iterator.h"

SimpleTrieIterator::SimpleTrieIterator(const Relation& relation)// : SimpleIterator(relation)
{
    // Build the trie
    this->trie = new Trie(relation);
    this->current_node = &trie->root;
    this->current_node_multiplicity = trie->root.multiplicity;
    this->at_end = false;
}

SimpleTrieIterator::~SimpleTrieIterator()
{
    delete this->trie;
}

Status SimpleTrieIterator::Open()
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


Status SimpleTrieIterator::Up()
{
    if (this->AtRoot())
    {
        return kFail;
    }

    // Reset the position between duplicates for the current node
    current_node->position_within_duplicates = 0;

    // Make the current node point to its parent
    this->current_node = this->current_node->parent;

    // Reset "at end" marker
    this->at_end = false;

    return kOK;
}


Status SimpleTrieIterator::Key(int* out_key)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *out_key = this->current_node->key;

    return kOK;
}


Status SimpleTrieIterator::Multiplicity(int* out_multiplicity)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *out_multiplicity = this->current_node->multiplicity;

    return kOK;
}


Status SimpleTrieIterator::Next()
{
    if (this->AtRoot() || this->AtEnd())
    {
        return kFail;
    }

    // Get the pointer to the sibling
    this->current_node->parent->current_child++;

    // If sibling is out of bounds of the parent's children list, indicate that we have reached the end
    // and DO NOT UPDATE the current node (otherwise all the pointers will be corrupted).
    if (this->current_node->parent->current_child == this->current_node->parent->children.end())
    {
        this->at_end = true;
        return kFail;
    }

    // We are not at the end, set the current node pointer to its right sibling.
    this->current_node = *this->current_node->parent->current_child;
    return kOK;
}


bool SimpleTrieIterator::AtEnd()
{
    return this->at_end;
}


bool SimpleTrieIterator::AtRoot()
{
    return (this->current_node == &trie->root);
}
