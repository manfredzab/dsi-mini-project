#include <algorithm>
#include "../include/linear_iterator.h"

namespace uk_ac_ox_cs_c875114
{

// Functor for tuple comparison
struct TupleComparator
{
   TupleComparator(int tuple_size) : tuple_size(tuple_size) { }
   int tuple_size;

   bool operator()(int* first, int* second)
   {
       for (int i = 0; i < tuple_size; i++)
       {
           if (first[i] < second[i])      return true; // First tuple is smaller than the second
           else if (first[i] > second[i]) return false;  // First tuple is not smaller than the second (in fact, it is greater)
       }

       return false; // First tuple is not smaller than the second (in fact, they are equal)
   }
};


Status LinearIterator::Seek(int* seek_key)
{
    if (this->AtEnd())
    {
        return kFail;
    }

    this->tuple_iterator = lower_bound(this->tuple_iterator + 1, this->relation.data.end(), seek_key, TupleComparator(this->tuple_size));

    return kOK;
}

} // namespace uk_ac_ox_cs_c875114
