#ifndef RELATION_H_
#define RELATION_H_

#include <string>
#include <vector>

namespace uk_ac_ox_cs_c875114
{

struct Relation
{
    ~Relation()
    {
        for (std::vector<int*>::iterator it = data.begin(); it != data.end(); ++it)
        {
            delete[] *it;
        }
    }

    std::string name;
    std::vector<std::string> attribute_names;

    std::vector<int*> data;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* RELATION_H_ */
