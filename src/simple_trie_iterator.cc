#include <string>

#include "../include/simple_trie_iterator.h"

SimpleTrieIterator::SimpleTrieIterator(const Relation& relation)// : SimpleIterator(relation)
{
    // Build the trie
    this->trie = new Trie(relation);
    this->current_node = &trie->root;
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

    this->at_end = false;
    this->current_node = this->current_node->parent;
    return kOK;
}


Status SimpleTrieIterator::Peek(int* result)
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


Status SimpleTrieIterator::Key(int* result)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *result = this->current_node->key;
    return kOK;
}


Status SimpleTrieIterator::Next()
{
    if (this->AtRoot() || this->AtEnd())
    {
        return kFail;
    }

    this->current_node->parent->current_child++;

    if (this->current_node->parent->current_child == this->current_node->parent->children.end())
    {
        this->at_end = true;
        return kFail;
    }
    else
    {
        this->current_node = *this->current_node->parent->current_child;
    }

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
