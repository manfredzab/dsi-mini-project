#ifndef LINEAR_ITERATOR_H_
#define LINEAR_ITERATOR_H_

#include "simple_iterator.h"
#include "status.h"

class LinearIterator : public SimpleIterator
{
    public:
        LinearIterator(const Relation& relation) : SimpleIterator(relation) { }
        virtual ~LinearIterator() { }

        virtual Status Seek(int* seek_key);
};

#endif /* LINEAR_ITERATOR_H_ */
