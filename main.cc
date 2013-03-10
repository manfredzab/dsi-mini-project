#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <vector>

#include "SortedArrayIterator.h"
#include "LeapfrogIterator.h"

#include "data_parser.h"
#include "relation.h"

int main()
{
    std::vector<Relation*>& db_relations = DataParser::ParseDatabase("data/dataset1-uniform/scale1/databasefile");

    for (std::vector<Relation*>::iterator it = db_relations.begin(); it != db_relations.end(); ++it)
    {
        std::cout << "Relation name: " << (*it)->name << std::endl;
        std::cout << "Relation attr: ";
        for (std::vector<std::string>::iterator a_it = (*it)->attribute_names.begin(); a_it != (*it)->attribute_names.end(); ++a_it)
        {
            std::cout << *a_it << " ";
        }
        std::cout << std::endl;
        std::cout << "Relation size: " << (*it)->data.size() << std::endl;
    }

//    int k = 6;
//
//    std::vector<IIterator<int>*> iterators;
//    for (int i = 0; i < k; i++)
//    {
//        iterators.push_back(GenerateRelation(50 + (i + 1) * 5));
//    }
//
//    IIterator<int>* leapfrogIterator = new LeapfrogIterator<int>(iterators);
//
//    int command = 0;
//    do
//    {
//        std::cout << "Choose action: [1] Key, [2] Next, [3] Seek, [4] At end, [0] Exit" << std::endl << "> ";
//        std::cin >> command;
//
//        switch (command)
//        {
//            case 1:
//                std::cout << leapfrogIterator->Key() << std::endl;
//                break;
//            case 2:
//                leapfrogIterator->Next();
//                break;
//            case 3:
//                std::cout << "Enter seek value: > ";
//
//                int seekValue;
//                std::cin >> seekValue;
//
//                leapfrogIterator->Seek(seekValue);
//                break;
//            case 4:
//                std::cout << leapfrogIterator->AtEnd() << std::endl;
//                break;
//        }
//    }
//    while (command != 0);

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
