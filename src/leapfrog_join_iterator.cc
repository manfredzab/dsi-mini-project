#include <algorithm>
#include "../include/leapfrog_join_iterator.h"


bool CompareTrieIteratorsByKeys(TrieIterator* first, TrieIterator* second);


LeapfrogJoinIterator::LeapfrogJoinIterator(std::vector<TrieIterator*>& iterators) : iterators(iterators)
{
    this->at_end = false;
    this->current_iterator_index = 0;
    this->key = 0;
    this->key_multiplicity = 1;
}


void LeapfrogJoinIterator::Init()
{
    at_end = false;
    for (std::vector<TrieIterator*>::iterator iterator = iterators.begin(); iterator != iterators.end(); ++iterator)
    {
        at_end |= (*iterator)->AtEnd();
    }

    if (!at_end)
    {
        sort(iterators.begin(), iterators.end(), CompareTrieIteratorsByKeys);
        current_iterator_index = 0;
        Search();
    }
}


void LeapfrogJoinIterator::Search()
{
    int iterator_count = iterators.size();

    int max_key;
    iterators[(current_iterator_index - 1 + iterator_count) % iterator_count]->Key(&max_key);

    while (true)
    {
        int min_key;
        iterators[current_iterator_index]->Key(&min_key);

        if (min_key == max_key)
        {
            key = min_key;

            // Deal with duplicates
            key_multiplicity = 1;

            for (int i = 0; i < iterator_count; i++)
            {
                int current_iterator_key_multiplicity = 1;

                int current_key;
                Status peek_status = iterators[current_iterator_index]->Peek(&current_key);

                while ((current_key == key) && (peek_status == kOK))
                {
                    iterators[current_iterator_index]->Next();
                    peek_status = iterators[current_iterator_index]->Peek(&current_key);

                    current_iterator_key_multiplicity++;
                }

                key_multiplicity *= current_iterator_key_multiplicity;

                current_iterator_index = (current_iterator_index + 1) % iterator_count;
            }

            return;
        }
        else
        {
            iterators[current_iterator_index]->Seek(max_key);

            if (iterators[current_iterator_index]->AtEnd())
            {
                at_end = true;
                return;
            }
            else
            {
                max_key = min_key;
                current_iterator_index = (current_iterator_index + 1) % iterator_count;
            }
        }
    }
}


Status LeapfrogJoinIterator::Next()
{
    if (this->AtEnd())
    {
        return kFail;
    }

    if (key_multiplicity > 1)
    {
        key_multiplicity--;
    }
    else
    {
        iterators[current_iterator_index]->Next();
        if (iterators[current_iterator_index]->AtEnd())
        {
            at_end = true;
            return kFail;
        }

        current_iterator_index = (current_iterator_index + 1) % iterators.size();
        Search();
    }

    return (this->AtEnd()) ? kFail : kOK;
}


Status LeapfrogJoinIterator::Seek(int seek_key)
{
    iterators[current_iterator_index]->Seek(seek_key);
    if (iterators[current_iterator_index]->AtEnd())
    {
        at_end = true;
    }
    else
    {
        current_iterator_index = (current_iterator_index + 1) % iterators.size();
        Search();
    }

    return (this->AtEnd()) ? kFail : kOK;
}


Status LeapfrogJoinIterator::Key(int* result)
{
    *result = this->key;

    return kOK;
}


bool LeapfrogJoinIterator::AtEnd()
{
    return this->at_end;
}


bool CompareTrieIteratorsByKeys(TrieIterator* first, TrieIterator* second)
{
    int first_result, second_result;
    first->Key(&first_result); second->Key(&second_result);

    return (first_result < second_result);
}
