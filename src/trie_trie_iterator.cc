#include <string>

#include "../include/trie_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

TrieTrieIterator::TrieTrieIterator(const Relation& relation)// : SimpleIterator(relation)
{
    // Build the trie
    this->trie = new Trie(relation);
    this->current_node = &trie->root;
    this->current_node_multiplicity = trie->root.multiplicity;
    this->at_end = false;
    this->depth = relation.attribute_names.size();
}

TrieTrieIterator::~TrieTrieIterator()
{
    delete this->trie;
}

Status TrieTrieIterator::Init()
{
    // Nothing to do
    return kOK;
}

Status TrieTrieIterator::Open()
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


Status TrieTrieIterator::Up()
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


Status TrieTrieIterator::Key(int* out_key)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *out_key = this->current_node->key;

    return kOK;
}


Status TrieTrieIterator::Multiplicity(int* out_multiplicity)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *out_multiplicity = this->current_node->multiplicity;

    return kOK;
}


Status TrieTrieIterator::Next()
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


bool TrieTrieIterator::AtEnd()
{
    return this->at_end;
}


bool TrieTrieIterator::AtRoot()
{
    return (this->current_node == &trie->root);
}

int TrieTrieIterator::Depth()
{
    return this->depth;
}

} // namespace uk_ac_ox_cs_c875114
