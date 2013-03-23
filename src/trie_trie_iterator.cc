#include <string>

#include "../include/trie_trie_iterator.h"

namespace c875114
{

using std::vector;

/**
 * Constructs the materialized trie-based trie iterator.
 * @param relation A reference to the relation for which the
 *                 trie iterator should be constructed.
 */
TrieTrieIterator::TrieTrieIterator(const Relation& relation) :
    kArity(relation.attribute_names.size())
{
    // Build the trie
    this->trie = new Trie(relation);
    this->current_node = &trie->root;
    this->current_node_multiplicity = trie->root.multiplicity;
    this->at_end = false;
}

/**
 * Releases the resources held by the trie iterator.
 */
TrieTrieIterator::~TrieTrieIterator()
{
    delete this->trie;
}

/**
 * Positions the trie iterator at the first child of the current node.
 * @returns kOK on success, failure otherwise.
 */
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

/**
 * Positions the trie iterator at the parent node.
 * @returns kOK on success, failure otherwise.
 */
Status TrieTrieIterator::Up()
{
    if (this->AtRoot())
    {
        return kFail;
    }

    // Make the current node point to its parent
    this->current_node = this->current_node->parent;

    // Reset "at end" marker
    this->at_end = false;

    return kOK;
}

/**
 * Returns the key at a current position of the iterator.
 * @param out_key A pointer to the memory location where the key should be stored.
 * @returns kOK on success, failure otherwise.
 */
Status TrieTrieIterator::Key(int* out_key)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *out_key = this->current_node->key;

    return kOK;
}

/**
 * Returns the multiplicity of the key at a current position of the iterator.
 * @param out_multiplicity A pointer to the memory location where the multiplicity
 *                         should be stored.
 * @returns kOK on success, failure otherwise.
 */
Status TrieTrieIterator::Multiplicity(int* out_multiplicity)
{
    if (this->AtRoot())
    {
        return kFail;
    }

    *out_multiplicity = this->current_node->multiplicity;

    return kOK;
}

/**
 * Moves the trie iterator to the next element in same level (belonging to the same parent).
 * @returns kOK on success, failure otherwise.
 */
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

/**
 * Checks if the trie iterator is positioned at the last child of the parent node.
 * @returns true if the iterator is positioned at the last element, false otherwise.
 */
bool TrieTrieIterator::AtEnd()
{
    return this->at_end;
}

/**
 * Checks if the trie iterator is positioned at the root.
 * @returns true if the iterator is positioned at the root, false otherwise.
 */
bool TrieTrieIterator::AtRoot()
{
    return (this->current_node == &trie->root);
}


/**
 * Returns the arity (maximum depth) of the trie.
 * @returns the arity (maximum depth) of the trie.
 */
int TrieTrieIterator::Arity()
{
    return this->kArity;
}

/**
 * Initializes the trie iterator.
 * @returns kOK
 */
Status TrieTrieIterator::Init()
{
    // Nothing to do
    return kOK;
}

} /* namespace c875114 */
