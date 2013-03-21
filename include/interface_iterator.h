#ifndef INTERFACE_ITERATOR_H_
#define INTERFACE_ITERATOR_H_

#include "status.h"

namespace uk_ac_ox_cs_c875114
{

template <typename T>
class IIterator
{
    public:
        virtual ~IIterator() { };

        virtual Status Init()                        = 0;
        virtual Status Key(T* out_key)               = 0;
        virtual Status Multiplicity(int* out_result) = 0;
        virtual Status Next()                        = 0;
        virtual bool   AtEnd()                       = 0;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* INTERFACE_ITERATOR_H_ */
