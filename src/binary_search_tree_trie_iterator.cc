#include <limits>
#include "../include/binary_search_tree_trie_iterator.h"

namespace uk_ac_ox_cs_c875114
{

BinarySearchTreeTrieIterator::BinarySearchTreeTrieIterator(Relation& relation):
    kArity(relation.attribute_names.size()),
    linear_iterator(relation)
{
    tuple_state = new int[kArity];
    depth = -1;
    at_end = false;
}


BinarySearchTreeTrieIterator::~BinarySearchTreeTrieIterator()
{
    delete[] tuple_state;
}


Status BinarySearchTreeTrieIterator::Init()
{
    return linear_iterator.Init();
}


Status BinarySearchTreeTrieIterator::Open()
{
    if (AtEnd() || (kArity - 1 == depth) || linear_iterator.AtEnd())
    {
        return kFail;
    }

    // Increase the depth
    depth++;

    // Save the linear iterator state
    tree_node_stack.push(linear_iterator.current_node);
    at_end_stack.push(linear_iterator.at_end);

    // Update the current trie iterator state
    UpdateState();

    return kOK;
}


Status BinarySearchTreeTrieIterator::Up()
{
    if (-1 == depth)
    {
        return kFail;
    }

    // Decrease depth
    depth--;

    // Clear "at end" flag
    at_end = false;

    // Reset the iterator state to what it was before opening the current trie level
    linear_iterator.current_node = tree_node_stack.top();
    linear_iterator.at_end = at_end_stack.top();

    tree_node_stack.pop();
    at_end_stack.pop();

    return kOK;
}


Status BinarySearchTreeTrieIterator::Key(int* out_key)
{
    if (AtEnd() || (-1 == depth))
    {
        return kFail;
    }

    *out_key = tuple_state[depth];
    return kOK;
}


Status BinarySearchTreeTrieIterator::Multiplicity(int* out_multiplicity)
{
    if (AtEnd() || (-1 == depth))
    {
        return kFail;
    }

    // If we are at the leaf level, return the multiplicity from the linear iterator
    if (depth == kArity - 1)
    {
        return linear_iterator.Multiplicity(out_multiplicity);
    }

    // In all other cases (i.e. for internal trie nodes), multiplicity is set to 1.
    *out_multiplicity = 1;
    return kOK;
}


Status BinarySearchTreeTrieIterator::Next()
{
    return Seek(tuple_state[depth] + 1);
}


Status BinarySearchTreeTrieIterator::Seek(int seek_key)
{
    if (AtEnd() || (-1 == depth))
    {
        return kFail;
    }

    // To seek the trie iterator to another next node at the same level, seek the linear iterator
    // to the LUB of the current path in the trie with the last argument set to the seek key and
    // the remaining arguments filled by -inf.
    // E.g. if the current position of the ternary trie (x, y, z) iterator is at x = 1, y = 3 and
    // the seek key is 9, the linear iterator seek tuple will be (1, 9, -inf).
    int* seek_tuple = new int[kArity];
    for (int i = 0; i < depth; i++)
    {
        seek_tuple[i] = tuple_state[i];
    }
    seek_tuple[depth] = seek_key;
    for (int i = depth + 1; i < kArity; i++)
    {
        seek_tuple[i] = std::numeric_limits<int>::min();
    }

    // Seek the linear iterator
    Status status = linear_iterator.Seek(seek_tuple);

    // Update the state
    UpdateState();

    // Release the memory
    delete[] seek_tuple;

    // If we hit the end return failure, otherwise return the status
    return AtEnd() ? kFail : status;
}


bool BinarySearchTreeTrieIterator::AtEnd()
{
    return at_end;
}



int BinarySearchTreeTrieIterator::Arity()
{
    return kArity;
}


void BinarySearchTreeTrieIterator::UpdateState()
{
    int* iterator_tuple;
    linear_iterator.Key(&iterator_tuple);

    if (linear_iterator.AtEnd() || (MatchDepth(iterator_tuple, tuple_state) < depth - 1))
    {
        at_end = true;
    }
    else
    {
        tuple_state[depth] = iterator_tuple[depth];
    }
}


int BinarySearchTreeTrieIterator::MatchDepth(int* first_tuple, int* second_tuple)
{
    for (int i = 0; i < kArity; i++)
    {
        if (first_tuple[i] != second_tuple[i])
        {
            return i - 1;
        }
    }

    return kArity - 1;
}

} /* namespace uk_ac_ox_cs_c875114 */
