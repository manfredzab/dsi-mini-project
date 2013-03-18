#include <algorithm>
#include <vector>
#include <string>

#include "../include/linear_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;

Status LinearTrieIterator::Seek(int seek_key)
{
    if (this->Next() == kFail)
    {
        return kFail;
    }

    // Binary search for the seek key in the parent's children vector
    TrieNode* seek_key_trie_node = new TrieNode();
    seek_key_trie_node->key = seek_key;

    vector<TrieNode*>::iterator seek_result_node = lower_bound(this->current_node->parent->current_child, this->current_node->parent->children.end(), seek_key_trie_node, CompareTrieNodeKeys);

    delete seek_key_trie_node;

    // If the sibling found is out of bounds of the parent's children list, indicate that we have reached the end
    // and DO NOT UPDATE the current node (otherwise all the pointers will be corrupted).
    if (seek_result_node == this->current_node->parent->children.end())
    {
        this->at_end = true;
        return kFail;
    }

    // We are not at the end, set the current node pointer to the seek result node and update
    // the parent's current child pointer
    this->current_node = *seek_result_node;
    this->current_node->parent->current_child = seek_result_node;

    return kOK;
}

} // namespace uk_ac_ox_cs_c875114
