#include <iostream>

#include "IIterator.h"
#include "SortedArrayIterator.h"


int main()
{
    int sampleElements[] = { 12, 4, 5, 2, 7, 7, 7, 8, 9, 11, 3, 6, 1, 10 };

    IIterator<int>* iterator = new SortedArrayIterator<int>(sampleElements, 12);

	std::cout << iterator->Key() << std::endl;
	iterator->Next();
	std::cout << iterator->Key() << std::endl;

	iterator->Seek(7);
	std::cout << iterator->Key() << std::endl;
	std::cout << iterator->AtEnd() << std::endl;

	iterator->Seek(13);
    std::cout << iterator->Key() << std::endl;
    std::cout << iterator->AtEnd() << std::endl;


	delete iterator;

	return 0;
}
