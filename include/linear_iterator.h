#ifndef LINEAR_ITERATOR_H_
#define LINEAR_ITERATOR_H_

#include "binary_search_tree.h"
#include "simple_iterator.h"
#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

/**
 * Linear iterator class based on the binary search tree. It extends the simple iterator (@see SimpleIterator)
 * by providing a Seek() method which finds a seek key in O(log N) time and O(1 + log N/m) amortized time, where
 * N is the number of nodes in the relation and m is the number of visits to keys in ascending order.
 */
class LinearIterator : public virtual SimpleIterator
{
    public:
        LinearIterator(const Relation& relation);
        virtual ~LinearIterator();

        /**
         * Initializes the iterator. This method must be called before calling any other method
         * of the iterator.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Init();

        /**
         * Returns the key at a current position of the iterator.
         * @param out_key A pointer to the memory location where the key should be
         *                stored.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Key(int** out_key);

        /**
         * Returns the multiplicity of the key at a current position of the iterator.
         * @param out_multiplicity A pointer to the memory location where the multiplicity
         *                         should be stored.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Multiplicity(int* out_result);

        /**
         * Moves the iterator to the next tuple in the relation.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Next();

        /**
         * Checks if the join iterator is positioned at the last element tuple in
         * the relation.
         * @returns true if the iterator is at the last tuple, false otherwise.
         */
        virtual bool AtEnd();

        /**
         * Moves the iterator to the least upper bound (LUB) of the seek key.
         * @param seek_key Seek key.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Seek(int* seek_key);

    protected:
        BinarySearchTree* search_tree; /**< Underlying binary search tree. */

    private:
        friend class BinarySearchTreeTrieIterator; /**< Needs access to private members of the
                                                        linear iterator for state saving. */

        TreeNode* current_node; /**< Current iterator position in the underlying search tree. */
        bool      at_end;       /**< "At-end" flag. */
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* LINEAR_ITERATOR_H_ */
