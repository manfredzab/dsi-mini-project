#include <cstring>
#include <stack>
#include "../include/binary_search_tree.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;
using std::stack;

BinarySearchTree::BinarySearchTree(vector<Tuple> tuple_data, int tuple_size) : kTupleSize(tuple_size)
{
    // Set the iterator to the middle of tuple data vector
    vector<Tuple>::const_iterator middle_iterator = tuple_data.begin() + (tuple_data.size() >> 1);

    root = new TreeNode();
    root->parent = NULL;
    root->tuple = *middle_iterator;
    root->left_child = InsertSubtree(root, tuple_data.begin(), middle_iterator);
    root->right_child = InsertSubtree(root, ++middle_iterator, tuple_data.end());
}


BinarySearchTree::~BinarySearchTree()
{
    stack<TreeNode*> nodes_to_delete;

    // Release the memory while traversing the binary search tree in post-order
    nodes_to_delete.push(root);
    while (!nodes_to_delete.empty())
    {
        TreeNode* top_node = nodes_to_delete.top();
        nodes_to_delete.pop();

        if (top_node->left_child != NULL)
        {
            nodes_to_delete.push(top_node->left_child);
        }

        if (top_node->right_child != NULL)
        {
            nodes_to_delete.push(top_node->right_child);
        }

        delete top_node;
    }

}

/**
 * Creates a binary tree subtree. This method needs the tuple key/multiplicity vector, sorted by tuple
 * keys.
 * @param parent Parent node of the subtree.
 * @param subtree_start An iterator to the beginning of the subtree.
 * @param subtree_end An iterator to the end of the subtree.
 * @returns A tree node to the root of the subtree.
 */
TreeNode* BinarySearchTree::InsertSubtree(TreeNode* parent, vector<Tuple>::const_iterator subtree_start, vector<Tuple>::const_iterator subtree_end)
{
    // Get the subtree size
    int subtree_size = subtree_end - subtree_start;

    // Nothing to do for empty subtrees
    if (0 == subtree_size)
    {
        return NULL;
    }

    // Subtree is non-empty; get the iterator to the middle of the subtree
    vector<Tuple>::const_iterator middle_iterator = subtree_start + (subtree_size >> 1);

    // Create the result node
    TreeNode* result_node = new TreeNode();
    result_node->parent = parent;
    result_node->tuple = *middle_iterator;

    // Populate children (recursively inserting subtrees if necessary)
    if (1 == subtree_size)
    {
        result_node->left_child = NULL;
        result_node->right_child = NULL;
    }
    else
    {
        result_node->left_child = InsertSubtree(result_node, subtree_start, middle_iterator);
        result_node->right_child = InsertSubtree(result_node, ++middle_iterator, subtree_end);
    }

    return result_node;
}

} /* namespace uk_ac_ox_cs_c875114 */
