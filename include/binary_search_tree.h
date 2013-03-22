#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <vector>
#include "equality.h"
#include "relation.h"

namespace uk_ac_ox_cs_c875114
{

struct TreeNode
{
    TreeNode*  parent;
    Tuple      tuple;
    TreeNode*  left_child;
    TreeNode*  right_child;
};

class BinarySearchTree
{
    public:
        BinarySearchTree(std::vector<Tuple> tuple_data, int tuple_size);
        virtual ~BinarySearchTree();

        static Equality CompareTreeNodeKeys(TreeNode* first, TreeNode* second, int tuple_size)
        {
            for (int i = 0; i < tuple_size; i++)
            {
                if (first->tuple.key[i] > second->tuple.key[i])
                {
                    return kGreaterThan;
                }
                else if (first->tuple.key[i] < second->tuple.key[i])
                {
                    return kLessThan;
                }
            }

            return kEqual;
        }

        TreeNode* root;

    private:
        TreeNode* InsertSubtree(TreeNode* parent, std::vector<Tuple>::const_iterator subtree_start, std::vector<Tuple>::const_iterator subtree_end);

        const int kTupleSize;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* BINARY_SEARCH_TREE_H_ */
