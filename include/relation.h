#ifndef RELATION_H_
#define RELATION_H_

#include <string>
#include <vector>

namespace uk_ac_ox_cs_c875114
{

struct Tuple
{
    int* key;
    int  multiplicity;

    static bool AreKeysEqual(Tuple& first, Tuple& second, int tuple_size)
    {
        for (int i = 0; i < tuple_size; i++)
        {
            if (first.key[i] != second.key[i])
            {
                return false;
            }
        }

        return true;
    }
};

struct Relation
{
    ~Relation()
    {
        for (std::vector<Tuple>::iterator it = data.begin(); it != data.end(); ++it)
        {
            delete[] it->key;
        }
    }

    std::string name;
    std::vector<std::string> attribute_names;

    std::vector<Tuple> data;
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* RELATION_H_ */
