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

        virtual Status Init();
        virtual Status Key(int** out_key);
        virtual Status Multiplicity(int* out_result);
        virtual Status Next();
        virtual bool   AtEnd();
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
