#ifndef JOIN_ITERATOR_H_
#define JOIN_ITERATOR_H_

// TODO: rename to "Iterator"?

#include "status.h"

namespace uk_ac_ox_cs_c875114
{

template <typename T>
class IJoinIterator
{
    public:
        virtual ~IJoinIterator() { };

        virtual Status Init()                        = 0;
        virtual Status Key(T* out_key)               = 0;
        virtual Status Multiplicity(int* out_result) = 0;
        virtual Status Next()                        = 0;
        virtual bool   AtEnd()                       = 0;
};

}

#endif /* JOIN_ITERATOR_H_ */
