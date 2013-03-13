#ifndef RELATION_H_
#define RELATION_H_

#include <string>
#include <vector>

struct Relation
{
    public:
        std::string name;
        std::vector<std::string> attribute_names;

        std::vector<int*> data;
};

#endif /* RELATION_H_ */
