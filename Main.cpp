#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iterator>

#include "IIterator.h"
#include "SortedArrayIterator.h"
#include "LeapfrogIterator.h"

IIterator<int>* GenerateRelation(int n)
{
    int* sampleElements = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        sampleElements[i] = rand() % 100;
    }

    IIterator<int>* iterator = new SortedArrayIterator<int>(sampleElements, n);

    delete sampleElements;

    return iterator;
}


int main()
{
    srand(time(NULL));

    int k = 6;

    std::vector<IIterator<int>*> iterators;
    for (int i = 0; i < k; i++)
    {
        iterators.push_back(GenerateRelation((i + 1) * 5));
    }

    LeapfrogIterator<int>* leapfrogIterator = new LeapfrogIterator<int>(iterators);



//    int sampleElements[] = { 12, 4, 5, 2, 7, 7, 7, 8, 9, 11, 3, 6, 1, 10 };
//
//    IIterator<int>* iterator = new SortedArrayIterator<int>(sampleElements, 14);
//
//	std::cout << iterator->Key() << std::endl;
//	iterator->Next();
//	std::cout << iterator->Key() << std::endl;
//
//	iterator->Seek(7);
//	std::cout << iterator->Key() << std::endl;
//	std::cout << iterator->AtEnd() << std::endl;
//
//	iterator->Next();
//	std::cout << iterator->Key() << std::endl;
//
//	iterator->Next();
//	std::cout << iterator->Key() << std::endl;
//
//
//    iterator->Next();
//    std::cout << iterator->Key() << std::endl;
//
//	iterator->Seek(12);
//    std::cout << iterator->Key() << std::endl;
//    std::cout << iterator->AtEnd() << std::endl;
//
//    iterator->Next();
//    std::cout << iterator->Key() << std::endl;
//
//    iterator->Next();
//    std::cout << iterator->Key() << std::endl;
//
//	delete iterator;

	return 0;
}
