//#include <string>
//
//#include "../include/simple_trie_iterator.h"
//#include "../include/status.h"
//
//SimpleTrieIterator::SimpleTrieIterator(const Relation& relation)
//{
//    this->at_end = false;
//    this->peeked = false;
//
//    this->max_depth = relation.attribute_names.size() - 1;
//    this->current_depth = -1;
//
//    this->simple_iterator_data = relation.data;
//    this->simple_iterator = new SimpleIterator(this->simple_iterator_data);
//}
//
//SimpleTrieIterator::~SimpleTrieIterator()
//{
//    delete this->simple_iterator;
//}
//
//Status SimpleTrieIterator::SeekSimpleIterator(const int* seek_values, const int seek_depth)
//{
//    Status status = kOK;
//
//    // Check if the seek key is ahead or behind the current position in file
//    bool forward = true;
//    for (int i = 0; i <= seek_depth; i++)
//    {
//        this->simple_iterator->attribute_index = i;
//
//        int current_key;
//        this->simple_iterator->Key(&current_key);
//
//        if (current_key >= seek_values[i])
//        {
//            forward = false;
//            break;
//        }
//    }
//
//    // If we are not seeking forward, reset the iterator
//    delete this->simple_iterator;
//    this->simple_iterator = new SimpleIterator(this->simple_iterator_data);
//
//    // Seek forwards for the search tuple
//    for (int i = 0; i <= seek_depth; i++)
//    {
//        this->simple_iterator->attribute_index = i;
//
//        int current_key;
//        this->simple_iterator->Key(&current_key);
//
//        while (!this->simple_iterator->AtEnd() && (current_key < seek_values[i]))
//        {
//            this->simple_iterator->Next();
//            this->simple_iterator->Key(&current_key);
//        }
//
//        if (this->simple_iterator->AtEnd())
//        {
//            status = kFail;
//            break;
//        }
//    }
//
//    this->simple_iterator->attribute_index = current_depth;
//    return status;
//}
//
//
//Status SimpleTrieIterator::Open()
//{
//    if (peeked)
//    {
//
//    }
//    else
//    {
//        if (this->current_depth == this->max_depth)
//        {
//            return kFail;
//        }
//
//        this->current_depth++;
//        this->at_end = false;
//
//        this->simple_iterator->attribute_index = this->current_depth;
//
//        return kOK;
//    }
//}
//
//
//Status TrieIterator::Up()
//{
//    if (this->AtRoot())
//    {
//        return kFail;
//    }
//
//    this->at_end = false;
//    this->current_node = this->current_node->parent;
//    return kOK;
//}
//
//
//Status SimpleTrieIterator::Peek(int* result)
//{
//    this->peeked = true;
//
//    int seek_key[this->current_depth + 1];
//    for (int i = 0; i <= this->current_depth; i++)
//    {
//        this->simple_iterator->attribute_index = i;
//        this->simple_iterator->Key(&seek_key[i]);
//    }
//    seek_key[this->current_depth]++;
//
//    Status status = this->SeekSimpleIterator(seek_key, this->current_depth);
//
//    // If you're trying to peek and you hit the end - reset the iterator's position
//    if (this->AtEnd())
//    {
//
//    }
//
//    return kOK;
//}
//
//
//Status SimpleTrieIterator::Key(int* result)
//{
//    if (this->AtRoot())
//    {
//        return kFail;
//    }
//
//    return this->simple_iterator->Key(result);
//}
//
//
//Status SimpleTrieIterator::Next()
//{
//    if (this->AtRoot() || this->AtEnd())
//    {
//        return kFail;
//    }
//
//    if (peeked)
//    {
//        peeked = false;
//        return kOK;
//    }
//
//
//    Status status = kOK;
//
//    int seek_key[this->current_depth + 1];
//    for (int i = 0; i <= this->current_depth; i++)
//    {
//        this->simple_iterator->attribute_index = i;
//        this->simple_iterator->Key(&seek_key[i]);
//    }
//    seek_key[this->current_depth]++;
//
//    status = this->SeekSimpleIterator(seek_key, this->current_depth);
//
//    if (status == kFail)
//    {
//        this->at_end = true;
//    }
//
//    return status;
//}
//
//
//bool SimpleTrieIterator::AtEnd()
//{
//    return this->at_end;
//}
//
//
//bool SimpleTrieIterator::AtRoot()
//{
//    return (this->current_depth == -1);
//}
