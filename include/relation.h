#ifndef RELATION_H_
#define RELATION_H_

#include <string>
#include <vector>

namespace c875114
{

/**
 * Relation detail holder: stores relation name, attribute names and tuple data. Each tuple is stored as
 * a sequence of integers on the heap, and the tuple data is stored as a vector of pointers to individual
 * tuple locations on the heap.
 */
struct Relation
{
    ~Relation()
    {
        // Release the tuple data
        for (std::vector<int*>::iterator it = data.begin(); it != data.end(); ++it)
        {
            delete[] *it;
        }
    }

    std::string name;                          /**< Relation name. */
    std::vector<std::string> attribute_names;  /**< Attribute names. */

    std::vector<int*> data;                    /**< Tuple data. */
};

} /* namespace c875114 */

#endif /* RELATION_H_ */
