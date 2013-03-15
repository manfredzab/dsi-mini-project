// TODO:
// - Better file format handling (less attributes in one tuple than in the other, etc)
// - File headers (time, etc)
// - Comments
// - Release memory for Relation int*'s
// - Release memory for trie

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <vector>
#include <map>
#include <set>

//#include "SortedArrayIterator.h"
//#include "LeapfrogIterator.h"

#include "../include/data_parser.h"
#include "../include/relation.h"
#include "../include/query.h"
#include "../include/simple_iterator.h"
#include "../include/simple_trie_iterator.h"
#include "../include/join.h"
#include "../include/sort_merge_join_trie_iterator.h"
#include "../include/trie_iterator_printer.h"

int main()
{
    //std::map<std::string, Relation*>* relations = DataParser::ParseRelations("data/dataset1-uniform/scale1/databasefile");
    std::map<std::string, Relation*>* relations = DataParser::ParseRelations("tests/data/databasefile");
    Query* query = DataParser::ParseQuery("data/query3");

    std::set<std::string> result_schema;
    for (unsigned i = 0; i < query->relation_names.size(); i++)
    {
        Relation* current_relation = (*relations)[query->relation_names[i]];
        result_schema.insert(current_relation->attribute_names.begin(), current_relation->attribute_names.end());
    }

    SortMergeJoinTrieIterator* join_iterator = new SortMergeJoinTrieIterator(*relations, *query);

    TrieIteratorPrinter::Print(*join_iterator, result_schema.size(), std::cout);

    std::vector<int> stack;
    int current_command;
    do
    {
        std::cout << "[0] Exit, [1] Up, [2] Next, [3] Open, [4] Key" << std::endl;
        std::cin >> current_command;

        switch (current_command)
        {
            case 1:
            {
                if (join_iterator->Up() == kOK)
                {
                    stack.pop_back();
                    std::cout << "[";
                    for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); ++it)
                    {
                        std::cout << " " << *it;
                    }
                    std::cout << " ] SUCCESS" << std::endl;
                }
                else
                    std::cout << "FAIL" << std::endl;
                break;
            }
            case 2:
            {
                if (join_iterator->Next() == kOK)
                {
                    stack.pop_back();
                    int result;
                    join_iterator->Key(&result);
                    stack.push_back(result);

                    std::cout << "[";
                    for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); ++it)
                    {
                        std::cout << " " << *it;
                    }
                    std::cout << " ] SUCCESS" << std::endl;
                }
                else
                    std::cout << "FAIL" << std::endl;
                break;
            }
            case 3:
            {
                if (join_iterator->Open() == kOK)
                {
                    int result;
                    join_iterator->Key(&result);
                    stack.push_back(result);

                    std::cout << "[";
                    for (std::vector<int>::iterator it = stack.begin(); it != stack.end(); ++it)
                    {
                        std::cout << " " << *it;
                    }
                    std::cout << " ] SUCCESS" << std::endl;
                }
                else
                    std::cout << "FAIL" << std::endl;
                break;
            }
            case 4:
            {
                int result;
                if (join_iterator->Key(&result) == kOK)
                    std::cout << result << std::endl;
                else
                    std::cout << "FAIL" << std::endl;
                break;
            }
        }
    }
    while (current_command != 0);


    delete join_iterator;

    delete query;
    delete relations;
//    std::cout << "Relation names:" << std::endl;
//    for (typename std::vector<std::string>::iterator it = query->relation_names.begin(); it != query->relation_names.end(); ++it)
//    {
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl << "Join attributes:" << std::endl;
//    for (typename std::vector<std::string>::iterator it = query->join_attributes.begin(); it != query->join_attributes.end(); ++it)
//    {
//        std::cout << *it << " ";
//    }
//    std::cout << std::endl;
//
//
//    SimpleTrieIterator simple_trie_iterator(*((*db_relations)["W"]));
//


//    SimpleIterator simple_iterator(*((*db_relations)[0]));
//    simple_iterator.attribute_index = 0;
//
//    int current_key;
//    do
//    {
//        simple_iterator.Key(&current_key);
//        std::cout << current_key << std::endl;
//    }
//    while (!simple_iterator.Next());


//    std::vector<Relation*>& db_relations = DataParser::ParseDatabase("data/dataset1-uniform/scale1/databasefile");
//
//    for (std::vector<Relation*>::iterator it = db_relations.begin(); it != db_relations.end(); ++it)
//    {
//        std::cout << "Relation name: " << (*it)->name << std::endl;
//        std::cout << "Relation attr: ";
//        for (std::vector<std::string>::iterator a_it = (*it)->attribute_names.begin(); a_it != (*it)->attribute_names.end(); ++a_it)
//        {
//            std::cout << *a_it << " ";
//        }
//        std::cout << std::endl;
//        std::cout << "Relation size: " << (*it)->data.size() << std::endl;
//    }



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
