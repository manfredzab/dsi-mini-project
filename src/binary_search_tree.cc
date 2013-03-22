#include <cstring>
#include <stack>
#include "../include/binary_search_tree.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;
using std::stack;

BinarySearchTree::BinarySearchTree(vector<int*> tuple_data, int tuple_size) : kTupleSize(tuple_size)
{
    // Remove duplicates from the tuple data by storing tuple multiplicities next to tuple keys
    const vector<KeyMultiplicityPair>& multiplicities = CollectTupleMultiplicities(tuple_data);

    // Set the iterator to the middle of multiplicities vector
    vector<KeyMultiplicityPair>::const_iterator middle_iterator = multiplicities.begin() + (multiplicities.size() >> 1);

    root = new TreeNode();
    root->parent = NULL;
    root->key_multiplicity_pair = *middle_iterator;
    root->left_child = InsertSubtree(root, multiplicities.begin(), middle_iterator);
    root->right_child = InsertSubtree(root, ++middle_iterator, multiplicities.end());
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
TreeNode* BinarySearchTree::InsertSubtree(TreeNode* parent, vector<KeyMultiplicityPair>::const_iterator subtree_start, vector<KeyMultiplicityPair>::const_iterator subtree_end)
{
    // Get the subtree size
    int subtree_size = subtree_end - subtree_start;

    // Nothing to do for empty subtrees
    if (0 == subtree_size)
    {
        return NULL;
    }

    // Subtree is non-empty; get the iterator to the middle of the subtree
    vector<KeyMultiplicityPair>::const_iterator middle_iterator = subtree_start + (subtree_size >> 1);

    // Create the result node
    TreeNode* result_node = new TreeNode();
    result_node->parent = parent;
    result_node->key_multiplicity_pair = *middle_iterator;

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


/**
 * Gathers duplicate tuples into records containing tuple key and multiplicity. It is done in
 * a linear swoop through the sorted input tuple data vector, gathering neighbouring duplicate
 * tuples.
 * @param tuple_data Sorted vector with input tuples.
 * @returns A vector of tuple keys and multiplicities (without duplicate tuples).
 */
vector<KeyMultiplicityPair> BinarySearchTree::CollectTupleMultiplicities(vector<int*>& tuple_data)
{
    vector<KeyMultiplicityPair> tuple_multiplicities;

    int* current_key = tuple_data[0];
    int current_multiplicity = 0;
    for (unsigned i = 0; i < tuple_data.size(); i++)
    {
        int* next_key = tuple_data[i];

        if (memcmp(current_key, next_key, kTupleSize * sizeof(int)) == 0)
        {
            current_multiplicity++;
        }
        else
        {
            KeyMultiplicityPair tuple = { current_key, current_multiplicity };
            tuple_multiplicities.push_back(tuple);

            current_key = next_key;
            current_multiplicity = 1;
        }
    }

    // Push the last tuple
    KeyMultiplicityPair tuple = { current_key, current_multiplicity };
    tuple_multiplicities.push_back(tuple);

    return tuple_multiplicities;
}

} /* namespace uk_ac_ox_cs_c875114 */
