//#include <iostream>
//
//#include <algorithm>
//
//#include "IIterator.h"
//#include "LeapfrogIterator.h"
//
//template LeapfrogIterator<int>::LeapfrogIterator(std::vector<IIterator<int>*>& iterators);
//
//template <typename T>
//bool CompareCurrentKeys(IIterator<T>* first, IIterator<T>* second)
//{
//    return (first->Key() < second->Key());
//}
//
//template <typename T>
//LeapfrogIterator<T>::LeapfrogIterator(std::vector<IIterator<T>*>& iterators) : iterators(iterators)
//{
//    this->k = iterators.size();
//
//    this->atEnd = false;
//
//    for (int i = 0; i < k; i++)
//    {
//        this->atEnd |= iterators[i]->AtEnd();
//    }
//
//    if (!this->AtEnd())
//    {
//        std::sort(iterators.begin(), iterators.end(), CompareCurrentKeys<T>);
//
////        for (int i = 0; i < k; i++)
////        {
////            std::cout << iterators[i]->Key() << "\n";
////        }
//
//        this->p = 0;
//
//        this->Search();
//    }
//}
//
//
//template <typename T>
//LeapfrogIterator<T>::~LeapfrogIterator()
//{
//    // TODO Auto-generated destructor stub
//}
//
//
//template <typename T>
//T LeapfrogIterator<T>::Key()
//{
//    return this->key;
//}
//
//
//template <typename T>
//void LeapfrogIterator<T>::Next()
//{
//    iterators[p]->Next();
//    if (iterators[p]->AtEnd())
//    {
//        atEnd = true;
//    }
//    else
//    {
//        p = (p + 1) % k;
//        this->Search();
//    }
//}
//
//
//template <typename T>
//void LeapfrogIterator<T>::Seek(T key)
//{
//    iterators[p]->Seek(key);
//    if (iterators[p]->AtEnd())
//    {
//        atEnd = true;
//    }
//    else
//    {
//        p = (p + 1) % k;
//        this->Search();
//    }
//}
//
//
//template <typename T>
//bool LeapfrogIterator<T>::AtEnd()
//{
//    return this->atEnd;
//}
//
//
//template <typename T>
//void LeapfrogIterator<T>::Search()
//{
//    T xMax = iterators[(k + p - 1) % k]->Key();
//
//    while (true)
//    {
//        T xMin = iterators[p]->Key();
//        if (xMin == xMax)
//        {
//            key = xMin;
//            return;
//        }
//        else
//        {
//            iterators[p]->Seek(xMax);
//
//            if (iterators[p]->AtEnd())
//            {
//                atEnd = true;
//                return;
//            }
//            else
//            {
//                xMax = iterators[p]->Key();
//                p = (p + 1) % k;
//            }
//        }
//    }
//}
