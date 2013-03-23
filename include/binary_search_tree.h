#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <vector>
#include "equality.h"

namespace c875114
{

/**
 * Holder of tuple's key and tuple's multiplicity (number of times this exact tuple
 * appears in a relation).
 */
struct KeyMultiplicityPair
{
    int* key;
    int  multiplicity;
};

/**
 * Internal binary search tree node.
 */
struct TreeNode
{
    TreeNode*           parent;
    KeyMultiplicityPair key_multiplicity_pair;
    TreeNode*           left_child;
    TreeNode*           right_child;
};

/**
 * Binary search tree data structure. For the tree to be balanced, the source relation has to be
 * sorted and must not contain duplicates.
 */
class BinarySearchTree
{
    public:
        BinarySearchTree(std::vector<int*> tuple_data, int tuple_size);
        virtual ~BinarySearchTree();

        /**
         * An inline tree node comparator, which compares tree nodes by keys using lexicographic
         * ordering on an integer < (less than) relation.
         * @param first First tree node to compare.
         * @param second Second tree node to compare.
         * @param tuple_size Tuple size.
         * @returns first < second, if kLessThan is returned,
         *          first > second, if kGreaterThan is returned,
         *          first = second, if kEqual is returned.
         */
        static Equality CompareTreeNodeKeys(TreeNode* first, TreeNode* second, int tuple_size)
        {
            for (int i = 0; i < tuple_size; i++)
            {
                if (first->key_multiplicity_pair.key[i] < second->key_multiplicity_pair.key[i])
                {
                    return kLessThan;
                }
                else if (first->key_multiplicity_pair.key[i] > second->key_multiplicity_pair.key[i])
                {
                    return kGreaterThan;
                }
            }

            return kEqual;
        }

        TreeNode* root; /**< Root of the binary search tree. */

    private:
        /**
         * Takes a sorted input vector of tuples and gathers duplicates.
         * @param tuple_data Sorted input vector of tuples.
         * @returns A vector of unique key/multiplicity pairs.
         */
        std::vector<KeyMultiplicityPair> CollectTupleMultiplicities(std::vector<int*>& tuple_data);

        /**
         * Takes a subsequence of a sorted key/multiplicity vector (between subtree_start and
         * subtree_end) and makes a binary search tree out of it.
         * @param tuple_data Sorted input vector of tuples.
         * @returns A pointer to the constructed balanced binary search tree.
         */
        TreeNode* InsertSubtree(TreeNode* parent, std::vector<KeyMultiplicityPair>::const_iterator subtree_start, std::vector<KeyMultiplicityPair>::const_iterator subtree_end);

        const int kTupleSize; /**< Tuple size. */
};

} /* namespace c875114 */

#endif /* BINARY_SEARCH_TREE_H_ */
