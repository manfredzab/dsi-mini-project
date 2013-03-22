#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <vector>
#include "equality.h"

namespace uk_ac_ox_cs_c875114
{

struct KeyMultiplicityPair
{
    int* key;
    int  multiplicity;
};

struct TreeNode
{
    TreeNode*           parent;
    KeyMultiplicityPair key_multiplicity_pair;
    TreeNode*           left_child;
    TreeNode*           right_child;
};

class BinarySearchTree
{
    public:
        BinarySearchTree(std::vector<int*> tuple_data, int tuple_size);
        virtual ~BinarySearchTree();

        static Equality CompareTreeNodeKeys(TreeNode* first, TreeNode* second, int tuple_size)
        {
            for (int i = 0; i < tuple_size; i++)
            {
                if (first->key_multiplicity_pair.key[i] > second->key_multiplicity_pair.key[i])
                {
                    return kGreaterThan;
                }
                else if (first->key_multiplicity_pair.key[i] < second->key_multiplicity_pair.key[i])
                {
                    return kLessThan;
                }
            }

            return kEqual;
        }

        TreeNode* root;

    private:
        std::vector<KeyMultiplicityPair> CollectTupleMultiplicities(std::vector<int*>& tuple_data);
        TreeNode*                        InsertSubtree(TreeNode* parent, std::vector<KeyMultiplicityPair>::const_iterator subtree_start, std::vector<KeyMultiplicityPair>::const_iterator subtree_end);

        const int kTupleSize;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* BINARY_SEARCH_TREE_H_ */
