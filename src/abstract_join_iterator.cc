#include <algorithm>
#include "../include/abstract_multiway_sort_merge_join_iterator.h"
#include "../include/trie_trie_iterator.h"
#include "../include/binary_search_tree_trie_iterator.h"

namespace c875114
{

using std::vector;

/**
 * Constructs the basis for the multi-way sort-merge join iterator and initializes its state.
 * @param iterators Trie iterators which should be used by this join iterator when searching for
 *                  common elements.
 */
template <class TTrieIterator>
AbstractMultiwaySortMergeJoinIterator<TTrieIterator>::AbstractMultiwaySortMergeJoinIterator(vector<TTrieIterator*>& iterators) : iterators(iterators)
{
    // Initialize the state of the iterator
    this->at_end = false;
    this->current_iterator_index = 0;
    this->key = 0;
    this->min_key = 0;
    this->max_key = 0;
    this->key_multiplicity = 1;
}

/**
 * Initializes the iterator. This method must be called before calling any other method
 * of the iterator.
 * @returns kOK on success, failure otherwise.
 */
template <class TTrieIterator>
Status AbstractMultiwaySortMergeJoinIterator<TTrieIterator>::Init()
{
    // If any of the trie iterators is at the end, set the "at-end" flag
    at_end = false;
    for (unsigned int i = 0; i < iterators.size(); i++)
    {
        at_end |= iterators[i]->AtEnd();
    }

    if (!at_end)
    {
        // Sort the trie iterators by the keys at which the iterators are positioned
        std::sort(iterators.begin(), iterators.end(), TrieTrieIterator::CompareTrieIteratorsByKeys);
        current_iterator_index = 0;

        // Search for the next key in the trie iterator intersection
        Search();
    }

    return kOK;
}

/**
 * Positions all trie iterators at the next element of the iterator key intersection.
 */
template <class TTrieIterator>
void AbstractMultiwaySortMergeJoinIterator<TTrieIterator>::Search()
{
    int iterator_count = iterators.size();

    // Get the maximum key (of _any_ iterator)
    iterators[(current_iterator_index - 1 + iterator_count) % iterator_count]->Key(&max_key);

    while (true)
    {
        // Get the smallest key of any iterator
        iterators[current_iterator_index]->Key(&min_key);

        if (min_key == max_key)
        {
            // All iterators are at the same key
            key = min_key;

            // Get key multiplicity (product of all trie iterator key multiplicities)
            key_multiplicity = 1;
            for (int i = 0; i < iterator_count; i++)
            {
                int current_iterator_key_multiplicity;
                iterators[current_iterator_index]->Multiplicity(&current_iterator_key_multiplicity);

                key_multiplicity *= current_iterator_key_multiplicity;

                current_iterator_index = (current_iterator_index + 1) % iterator_count;
            }

            return;
        }

        // Not all iterators are at the same key; position the current iterator at the
        // max key (note that the actual positioning implementation depends on the instantiation
        // of this abstract class.
        PositionCurrentIteratorAtKey(max_key);

        // Return if the iterator is at the end
        if (iterators[current_iterator_index]->AtEnd())
        {
            at_end = true;
            return;
        }
        else
        {
            // Otherwise, keep looking for the key intersection
            iterators[current_iterator_index]->Key(&max_key);
            current_iterator_index = (current_iterator_index + 1) % iterator_count;
        }
    }
}

/**
 * Moves the join iterator to the next element in the trie iterator insersection.
 * @returns kOK on success, failure otherwise.
 */
template <class TTrieIterator>
Status AbstractMultiwaySortMergeJoinIterator<TTrieIterator>::Next()
{
    if (this->AtEnd())
    {
        return kFail;
    }

    // Move the current iterator (to avoid finding the same value by Search() below)
    iterators[current_iterator_index]->Next();
    if (iterators[current_iterator_index]->AtEnd())
    {
        at_end = true;
        return kFail;
    }

    // Get the next iterator
    current_iterator_index = (current_iterator_index + 1) % iterators.size();

    // Search for the next key in the trie iterator intersection
    Search();

    return (this->AtEnd()) ? kFail : kOK;
}

/**
 * Returns the key at a current position of the iterator.
 * @param out_key A pointer to the memory location where the key should be
 *                stored.
 * @returns kOK on success, failure otherwise.
 */
template <class TTrieIterator>
Status AbstractMultiwaySortMergeJoinIterator<TTrieIterator>::Key(int* out_key)
{
    *out_key = this->key;

    return kOK;
}

/**
 * Returns the multiplicity of the key at a current position of the iterator.
 * @param out_multiplicity A pointer to the memory location where the multiplicity
 *                         should be stored.
 * @returns kOK on success, failure otherwise.
 */
template <class TTrieIterator>
Status AbstractMultiwaySortMergeJoinIterator<TTrieIterator>::Multiplicity(int* out_multiplicity)
{
    *out_multiplicity = this->key_multiplicity;

    return kOK;
}

/**
 * Checks if the join iterator is positioned at the last element in the trie
 * iterator intersection.
 * @returns true if the iterator is at the last element, false otherwise.
 */
template <class TTrieIterator>
bool AbstractMultiwaySortMergeJoinIterator<TTrieIterator>::AtEnd()
{
    return this->at_end;
}

// Instantiate the template for multi-way sort merge and leapfrog join iterators.
template class AbstractMultiwaySortMergeJoinIterator<TrieTrieIterator>;
template class AbstractMultiwaySortMergeJoinIterator<BinarySearchTreeTrieIterator>;

} /* namespace c875114 */
