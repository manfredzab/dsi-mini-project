#include "../include/linear_iterator.h"

namespace uk_ac_ox_cs_c875114
{

LinearIterator::LinearIterator(Relation& relation) :
    SimpleIterator(relation),
    search_tree(relation.data, relation.attribute_names.size())
{
    current_node = NULL;
    at_end = false;
}

Status LinearIterator::Init()
{
    current_node = &search_tree.root;

    while (current_node->left_child != NULL)
    {
        // Descend all the way to the left of the binary search tree
        // to set the iterator's position to the minimum value
        current_node = current_node->left_child;
    }

    return kOK;
}


Status LinearIterator::Key(int** out_key)
{
    if (!AtEnd())
    {
        *out_key = current_node->key_multiplicity_pair.key;

        return kOK;
    }
    else
    {
        return kFail;
    }
}


Status LinearIterator::Multiplicity(int* out_multiplicity)
{
    if (!AtEnd())
    {
        *out_multiplicity = current_node->key_multiplicity_pair.multiplicity;

        return kOK;
    }
    else
    {
        return kFail;
    }
}


Status LinearIterator::Seek(int* seek_key)
{
    // Create a temporary tree search node for tree node key comparisons below
    TreeNode search_node;
    search_node.key_multiplicity_pair.key = seek_key;

    TreeNode* lub_node = NULL;

    while ((current_node->parent != NULL) &&
           (kLessThan == BinarySearchTree::CompareTreeNodeKeys(current_node, &search_node, kTupleSize)))
    {
        current_node = current_node->parent;
    }

    if (kLessThan != BinarySearchTree::CompareTreeNodeKeys(current_node, &search_node, kTupleSize))
    {
        // Current node is greater or equal to the seek key, i.e. we found the first
        // candidate LUB.
        lub_node = current_node;

        // Since we are guaranteed that the LUB is not on the right subtree of the current
        // node, look for LUB in the left subtree of the current node.
        current_node = current_node->left_child;
    }

    // Do a binary tree search in the tree below the current node searching for LUB.
    while (current_node != NULL)
    {
        switch (BinarySearchTree::CompareTreeNodeKeys(current_node, &search_node, kTupleSize))
        {
            case kEqual:
            {
                // Current node is set to the best possible LUB (since duplicates have been removed),
                // nothing else needs to be done.
                return kOK;
            }
            case kLessThan:
            {
                // Current node is less than LUB, search on the right subtree.
                current_node = current_node->right_child;
                break;
            }
            case kGreaterThan:
            {
                // Current node is greater than LUB; set the LUB and search on the left subtree.
                lub_node = current_node;
                current_node = current_node->left_child;
                break;
            }
        }
    }

    // Position the current node at the LUB for the seek key
    current_node = lub_node;

    // Update the state of the iterator
    if (NULL != lub_node)
    {
        return kOK;
    }
    else
    {
        at_end = true;

        return kFail;
    }
}


bool LinearIterator::AtEnd()
{
    return at_end;
}


} /* namespace uk_ac_ox_cs_c875114 */
