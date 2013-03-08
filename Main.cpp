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
        sampleElements[i] = rand() % 50;
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
        iterators.push_back(GenerateRelation(50 + (i + 1) * 5));
    }

    IIterator<int>* leapfrogIterator = new LeapfrogIterator<int>(iterators);

    int command = 0;
    do
    {
        std::cout << "Choose action: [1] Key, [2] Next, [3] Seek, [4] At end, [0] Exit" << std::endl << "> ";
        std::cin >> command;

        switch (command)
        {
            case 1:
                std::cout << leapfrogIterator->Key() << std::endl;
                break;
            case 2:
                leapfrogIterator->Next();
                break;
            case 3:
                std::cout << "Enter seek value: > ";

                int seekValue;
                std::cin >> seekValue;

                leapfrogIterator->Seek(seekValue);
                break;
            case 4:
                std::cout << leapfrogIterator->AtEnd() << std::endl;
                break;
        }
    }
    while (command != 0);

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
