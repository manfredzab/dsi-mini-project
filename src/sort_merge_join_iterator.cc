#include <algorithm>
#include "../include/sort_merge_join_iterator.h"

bool CompareTrieIteratorsByKeys(SimpleTrieIterator* first, SimpleTrieIterator* second)
{
    int first_result, second_result;
    first->Key(&first_result); second->Key(&second_result);

    return (first_result < second_result);
}

SortMergeJoinIterator::SortMergeJoinIterator(std::vector<SimpleTrieIterator*>& iterators) : iterators(iterators)
{
    this->at_end = false;
    this->current_iterator = 0;
    this->key = 0;
    this->key_multiplicity = 1;
}

void SortMergeJoinIterator::Init()
{
    at_end = false;
    for (std::vector<SimpleTrieIterator*>::iterator iterator = iterators.begin(); iterator != iterators.end(); ++iterator)
    {
        at_end |= (*iterator)->AtEnd();
    }

    if (!at_end)
    {
        sort(iterators.begin(), iterators.end(), CompareTrieIteratorsByKeys);
        current_iterator = 0;
        Search();
    }
}

void SortMergeJoinIterator::Search()
{
    int iterator_count = iterators.size();

    int max_key;
    iterators[(current_iterator - 1 + iterator_count) % iterator_count]->Key(&max_key);

    while (true)
    {
        int min_key;
        iterators[current_iterator]->Key(&min_key);

        if (min_key == max_key)
        {
            key = min_key;

            // Deal with duplicates
            key_multiplicity = 1;

            for (int i = 0; i < iterator_count; i++)
            {
                int current_iterator_key_multiplicity = 1;

                int current_key;
                Status peek_status = iterators[current_iterator]->Peek(&current_key);

                while ((current_key == key) && (peek_status == kOK))
                {
                    iterators[current_iterator]->Next();
                    iterators[current_iterator]->Peek(&current_key);

                    current_iterator_key_multiplicity++;
                }

                key_multiplicity *= current_iterator_key_multiplicity;

                current_iterator = (current_iterator + 1) % iterator_count;
            }

            return;
        }
        else
        {
            while ((min_key < max_key) && !iterators[current_iterator]->AtEnd())
            {
                iterators[current_iterator]->Next();
                iterators[current_iterator]->Key(&min_key);
            }

            if (iterators[current_iterator]->AtEnd())
            {
                at_end = true;
                return;
            }
            else
            {
                max_key = min_key;
                current_iterator = (current_iterator + 1) % iterator_count;
            }
        }
    }
}


Status SortMergeJoinIterator::Next()
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
        iterators[current_iterator]->Next();
        if (iterators[current_iterator]->AtEnd())
        {
            at_end = true;
            return kFail;
        }

        current_iterator = (current_iterator + 1) % iterators.size();
        Search();
    }

    return (this->AtEnd()) ? kFail : kOK;
}


Status SortMergeJoinIterator::Key(int* result)
{
    *result = this->key;

    return kOK;
}

bool SortMergeJoinIterator::AtEnd()
{
    return this->at_end;
}

int SortMergeJoinIterator::KeyMultiplicity()
{
    return this->key_multiplicity;
}
