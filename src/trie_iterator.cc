#include <algorithm>
#include <vector>
#include <string>

#include "../include/trie_iterator.h"

TrieIterator::TrieIterator(const Relation& relation) : LinearIterator(relation)
{
    // Build the trie
    this->trie = new Trie(relation);
    this->current_node = &trie->root;
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

    this->at_end = false;
    this->current_node = this->current_node->parent;
    return kOK;
}


Status TrieIterator::Peek(int* result)
{
    bool last_child = (*(this->current_node->parent->children.end() - 1) == this->current_node);

    if (this->AtRoot() || this->AtEnd() || last_child)
    {
        return kFail;
    }

    std::vector<TrieNode*>::iterator next_node = this->current_node->parent->current_child + 1;
    *result = (*next_node)->key;

    return kOK;
}


Status TrieIterator::Key(int* result)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *result = this->current_node->key;
    return kOK;
}


Status TrieIterator::Seek(int seek_key)
{
    if (this->Next() == kFail)
    {
        return kFail;
    }

    // Binary search for the seek key in the parent's children vector
    TrieNode* seek_key_trie_node = new TrieNode();
    seek_key_trie_node->key = seek_key;

    std::vector<TrieNode*>::iterator seek_result_node = std::lower_bound(this->current_node->parent->current_child, this->current_node->parent->children.end(), seek_key_trie_node, CompareTrieNodeKeys);

    delete seek_key_trie_node;

    // If the sibling found is out of bounds of the parent's children list, indicate that we have reached the end
    // and DO NOT UPDATE the current node (otherwise all the pointers will be corrupted).
    if (seek_result_node == this->current_node->parent->children.end())
    {
        this->at_end = true;
        return kFail;
    }

    // We are not at the end, set the current node pointer to the seek result node
    this->current_node = *seek_result_node;
    return kOK;
}



Status TrieIterator::Next()
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


bool TrieIterator::AtEnd()
{
    return this->at_end;
}


bool TrieIterator::AtRoot()
{
    return (this->current_node == &trie->root);
}
