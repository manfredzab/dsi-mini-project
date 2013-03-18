#ifndef BINARY_SORT_MERGE_JOIN_ITERATOR_H_
#define BINARY_SORT_MERGE_JOIN_ITERATOR_H_

#include <string>
#include <vector>
#include "query.h"
#include "relation.h"
#include "join_iterator.h"
#include "simple_relation_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class BinarySortMergeJoinIterator : public virtual IJoinIterator
{
    public:
        BinarySortMergeJoinIterator(const Relation& outer_relation, const Relation& inner_relation, const Query& query);
        virtual ~BinarySortMergeJoinIterator() { };

        virtual void   Init();
        virtual void   Search();
        virtual Status Key(int* out_key);
        virtual Status Multiplicity(int* out_result);
        virtual Status Next();
        virtual bool   AtEnd();

    private:
        struct AttributeOrderDescriptor
        {
            bool is_outer_relation;
            int  relation_attribute_index;
        };

        std::vector<std::string>              result_relation_attribute_names;
        std::vector<AttributeOrderDescriptor> result_relation_tuple_order;

        const Relation&                       outer_relation;
        SimpleRelationIterator                outer_relation_iterator;
        std::vector<int>                      outer_relation_join_attribute_positions;

        const Relation&                       inner_relation;
        SimpleRelationIterator                inner_relation_iterator;
        std::vector<int>                      inner_relation_join_attribute_positions;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* BINARY_SORT_MERGE_JOIN_ITERATOR_H_ */
