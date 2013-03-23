#include <cstring>
#include "../include/simple_iterator.h"

namespace c875114
{

/**
 * Constructs a simple iterator for a given relation.
 * @param relation Relation for which a simple iterator should be constructed.
 */
SimpleIterator::SimpleIterator(const Relation& relation) :
    kTupleSize(relation.attribute_names.size()),
    kRelation(relation)
{
    tuple_iterator = relation.data.begin();
}

/**
 * Returns the key at a current position of the iterator.
 * @param out_key A pointer to the memory location where the key should be
 *                stored.
 * @returns kOK on success, failure otherwise.
 */
Status SimpleIterator::Key(int** out_key)
{
    if (AtEnd())
    {
        return kFail;
    }

    *out_key = *tuple_iterator;
    return kOK;
}

/**
 * Moves the iterator to the next tuple in the relation.
 * @returns kOK on success, failure otherwise.
 */
Status SimpleIterator::Next()
{
    if (AtEnd())
    {
        return kFail;
    }

    tuple_iterator++;
    return kOK;
}

/**
 * Checks if the join iterator is positioned at the last tuple in the
 * relation.
 * @returns true if the iterator is at the last tuple, false otherwise.
 */
bool SimpleIterator::AtEnd()
{
    return (tuple_iterator == kRelation.data.end());
}

/**
 * Not implemented.
 */
Status SimpleIterator::Init()
{
    return kNotImplemented;
}

/**
 * Not implemented.
 */
Status SimpleIterator::Multiplicity(int* out_result)
{
    return kNotImplemented;
}

} /* namespace c875114 */
