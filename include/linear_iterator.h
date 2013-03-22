#ifndef LINEAR_ITERATOR_H_
#define LINEAR_ITERATOR_H_

#include "binary_search_tree.h"
#include "simple_iterator.h"
#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

class LinearIterator : public virtual SimpleIterator
{
    public:
        LinearIterator(Relation& relation);
        virtual ~LinearIterator() { };

        virtual Status Init();
        virtual Status Key(int** out_key);
        virtual Status Multiplicity(int* out_result);
        virtual Status Next();
        virtual bool   AtEnd();

        virtual Status Seek(int* seek_key);

    protected:
        BinarySearchTree search_tree;

    private:
        TreeNode* current_node;
        bool      at_end;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* LINEAR_ITERATOR_H_ */
