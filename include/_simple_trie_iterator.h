//#ifndef SIMPLE_TRIE_ITERATOR_H_
//#define SIMPLE_TRIE_ITERATOR_H_
//
//#include <vector>
//
//#include "trie_iterator_interface.h"
//#include "simple_iterator.h"
//#include "relation.h"
//
//class SimpleTrieIterator : public ITrieIterator // : public virtual SimpleIterator
//{
//    public:
//        SimpleTrieIterator(const Relation& relation);
//        virtual ~SimpleTrieIterator();
//
//        virtual Status Open();
//        virtual Status Up();
//        virtual Status Key(int* result);
//        virtual Status Next();
//        virtual Status Peek(int* result);
//        virtual bool   AtEnd();
//    private:
//        bool AtRoot();
//        Status SeekSimpleIterator(const int* seek_values, const int seek_depth);
//
//        int  current_depth;
//        int  max_depth;
//        bool at_end;
//
//        bool peeked;
//
//        SimpleIterator*          simple_iterator;
//        const std::vector<int*>& simple_iterator_data;
//};
//
//
//#endif /* SIMPLE_TRIE_ITERATOR_H_ */
