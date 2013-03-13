#ifndef SIMPLEITERATOR_H_
#define SIMPLEITERATOR_H_

#include <vector>

#include "status.h"
#include "relation.h"

template <class T>
class SimpleIterator
{
    public:
        SimpleIterator(const std::vector<T>& data);
        virtual ~SimpleIterator() { };

        virtual Status Key(T result);
        virtual Status Next();
        virtual bool   AtEnd();

        int attribute_index;
    private:
        const std::vector<T>&                   tuple_data;
        typename std::vector<T>::const_iterator tuple_iterator;
};

#endif /* SIMPLEITERATOR_H_ */
