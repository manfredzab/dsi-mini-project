#include <algorithm>
#include "../include/simple_join_iterator.h"

namespace uk_ac_ox_cs_c875114
{

using std::vector;


bool CompareTrieIteratorsByKeys(ITrieIterator<int>* first, ITrieIterator<int>* second);


SimpleJoinIterator::SimpleJoinIterator(vector<ITrieIterator<int>*>& iterators) : iterators(iterators)
{
    this->at_end = false;
    this->current_iterator_index = 0;
    this->key = 0;
    this->min_key = 0;
    this->max_key = 0;
    this->key_multiplicity = 1;
}


Status SimpleJoinIterator::Init()
{
    at_end = false;
    for (vector<ITrieIterator<int>*>::iterator iterator = iterators.begin(); iterator != iterators.end(); ++iterator)
    {
        at_end |= (*iterator)->AtEnd();
    }

    if (!at_end)
    {
        sort(iterators.begin(), iterators.end(), CompareTrieIteratorsByKeys);
        current_iterator_index = 0;
        Search();
    }

    return kOK;
}


void SimpleJoinIterator::Search()
{
    int iterator_count = iterators.size();

    iterators[(current_iterator_index - 1 + iterator_count) % iterator_count]->Key(&max_key);

    while (true)
    {
        iterators[current_iterator_index]->Key(&min_key);

        if (min_key == max_key)
        {
            key = min_key;

            // Count key multiplicity
            key_multiplicity = 1;
            for (int i = 0; i < iterator_count; i++)
            {
                int current_iterator_key_multiplicity;
                iterators[current_iterator_index]->Multiplicity(&current_iterator_key_multiplicity);

                key_multiplicity *= current_iterator_key_multiplicity;

                current_iterator_index = (current_iterator_index + 1) % iterator_count;
            }

            return;
        }
        else
        {
            SeekCurrentIteratorToMaxKey();

            if (iterators[current_iterator_index]->AtEnd())
            {
                at_end = true;
                return;
            }
            else
            {
                iterators[current_iterator_index]->Key(&max_key);
                current_iterator_index = (current_iterator_index + 1) % iterator_count;
            }
        }
    }
}


void SimpleJoinIterator::SeekCurrentIteratorToMaxKey()
{
    while ((min_key < max_key) && !iterators[current_iterator_index]->AtEnd())
    {
        iterators[current_iterator_index]->Next();
        iterators[current_iterator_index]->Key(&min_key);
    }
}


Status SimpleJoinIterator::Next()
{
    if (this->AtEnd())
    {
        return kFail;
    }

    iterators[current_iterator_index]->Next();
    if (iterators[current_iterator_index]->AtEnd())
    {
        at_end = true;
        return kFail;
    }

    current_iterator_index = (current_iterator_index + 1) % iterators.size();
    Search();

    return (this->AtEnd()) ? kFail : kOK;
}


Status SimpleJoinIterator::Key(int* out_key)
{
    *out_key = this->key;

    return kOK;
}


Status SimpleJoinIterator::Multiplicity(int* out_multiplicity)
{
    *out_multiplicity = this->key_multiplicity;

    return kOK;
}


bool SimpleJoinIterator::AtEnd()
{
    return this->at_end;
}


bool CompareTrieIteratorsByKeys(ITrieIterator<int>* first, ITrieIterator<int>* second)
{
    int first_result, second_result;
    first->Key(&first_result); second->Key(&second_result);

    return (first_result < second_result);
}


} // namespace uk_ac_ox_cs_c875114
