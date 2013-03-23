#include <cstring>
#include <limits>
#include "../include/binary_search_tree_trie_iterator.h"

namespace c875114
{

/**
 * Constructs the binary search tree-based trie iterator.
 * @param relation A reference to the relation for which the trie iterator
 *                 should be constructed.
 */
BinarySearchTreeTrieIterator::BinarySearchTreeTrieIterator(const Relation& relation):
    kArity(relation.attribute_names.size()),
    linear_iterator(relation)
{
    // Allocate memory for the current tuple
    tuple_state = new int[kArity];
    memset(tuple_state, 0, kArity * sizeof(int));

    // Initialize the state
    depth = -1;
    at_end = false;
}

/**
 * Releases resources held by the binary search tree iterator (but not the underlying
 * linear iterator's binary search tree).
 */
BinarySearchTreeTrieIterator::~BinarySearchTreeTrieIterator()
{
    delete[] tuple_state;
}

/**
 * Initializes the underlying linear iterator. This method must be called before calling any other
 * method of the iterator.
 * @returns kOK on success, failure otherwise.
 */
Status BinarySearchTreeTrieIterator::Init()
{
    return linear_iterator.Init();
}

/**
 * Positions the trie iterator at the first child of the current node.
 * @returns kOK on success, failure otherwise.
 */
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

/**
 * Positions the trie iterator at the parent node.
 * @returns kOK on success, failure otherwise.
 */
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

/**
 * Returns the key at a current position of the iterator.
 * @param out_key A pointer to the memory location where the key should be stored.
 * @returns kOK on success, failure otherwise.
 */
Status BinarySearchTreeTrieIterator::Key(int* out_key)
{
    if (AtEnd() || (-1 == depth))
    {
        return kFail;
    }

    *out_key = tuple_state[depth];
    return kOK;
}


/**
 * Returns the multiplicity of the key at a current position of the iterator.
 * @param out_multiplicity A pointer to the memory location where the multiplicity
 *                         should be stored.
 * @returns kOK on success, failure otherwise.
 */
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

/**
 * Moves the trie iterator to the next element in same level (belonging to the same parent).
 * @returns kOK on success, failure otherwise.
 */
Status BinarySearchTreeTrieIterator::Next()
{
    return Seek(tuple_state[depth] + 1);
}

/**
 * Moves the trie iterator to the element which is i) in the same level, ii) belongs to the
 * same parent, and iii) is a least upper bound (LUB) for the seek key.
 * @param seek_key Seek key.
 * @returns kOK on success, failure otherwise.
 */
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

/**
 * Checks if the trie iterator is positioned at the last child of the parent node.
 * @returns true if the iterator is positioned at the last element, false otherwise.
 */
bool BinarySearchTreeTrieIterator::AtEnd()
{
    return at_end;
}


/**
 * Returns the arity (maximum depth) of the trie.
 * @returns the arity (maximum depth) of the trie.
 */
int BinarySearchTreeTrieIterator::Arity()
{
    return kArity;
}

/**
 * Updates the state of the trie iterator (depth counter and "at end" flag).
 */
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

/**
 * Calculates the depth until which the tuples match completely (i.e. the longest
 * common prefix).
 * @param first_tuple Pointer to the first tuple.
 * @param second_tuple Pointer to the second tuple.
 * @returns Match depth (longest common prefix) for both tuples.
 */
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

} /* namespace c875114 */
