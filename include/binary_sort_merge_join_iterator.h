#ifndef BINARY_SORT_MERGE_JOIN_ITERATOR_H_
#define BINARY_SORT_MERGE_JOIN_ITERATOR_H_

#include <string>
#include <vector>
#include <list>
#include "relation.h"
#include "interface_iterator.h"
#include "simple_iterator.h"

namespace uk_ac_ox_cs_c875114
{

class BinarySortMergeJoinIterator : public virtual IIterator<int*>
{
    public:
        struct AttributeOrderDescriptor
        {
            bool is_outer_relation;
            int  relation_attribute_index;
        };

        BinarySortMergeJoinIterator(Relation& outer_relation,
                                    Relation& inner_relation,
                                    const std::vector<AttributeOrderDescriptor>& result_relation_tuple_order,
                                    const std::vector<int>& outer_relation_join_attribute_positions,
                                    const std::vector<int>& inner_relation_join_attribute_positions);

        virtual ~BinarySortMergeJoinIterator();

        virtual Status Init();
        virtual Status Key(int** out_key);
        virtual Status Multiplicity(int* out_result);
        virtual Status Next();
        virtual bool   AtEnd();

    private:
        enum Equality
        {
            kLessThan = 0,
            kEqual,
            kGreaterThan
        };

        struct SameRelationTupleComparisonFunctor
        {
            SameRelationTupleComparisonFunctor(const std::vector<int>& compare_positions) : compare_positions(compare_positions)
            {
                compare_positions_count = compare_positions.size();
            };

            Equality CompareTuples(const int* first_tuple, const int* second_tuple)
            {
                for (int i = 0; i < compare_positions_count; i++)
                {
                    if (first_tuple[compare_positions[i]] > second_tuple[compare_positions[i]])
                    {
                        return kGreaterThan;
                    }
                    else if (first_tuple[compare_positions[i]] < second_tuple[compare_positions[i]])
                    {
                        return kLessThan;
                    }
                }

                return kEqual;
            }

            bool operator()(const int* first_tuple, const int* second_tuple)
            {
                return (kLessThan == CompareTuples(first_tuple, second_tuple));
            }

            const std::vector<int>& compare_positions;
            int                     compare_positions_count;
        };

        void     GatherSameKeyTuples(SimpleIterator& relation_iterator, SameRelationTupleComparisonFunctor& comparison_functor, std::list<int*>& out_same_key_tuples);
        void     CreateResultTupleAsKey(int* outer_tuple, int* inner_tuple);
        Equality CompareTuplesAtDifferentRelations(int* outer_relation_tuple, int* inner_relation_tuple);

        Relation&                                    outer_relation;
        Relation&                                    inner_relation;

        SimpleIterator*                      outer_relation_iterator;
        SimpleIterator*                      inner_relation_iterator;

        SameRelationTupleComparisonFunctor           outer_relation_tuple_comparison_functor;
        SameRelationTupleComparisonFunctor           inner_relation_tuple_comparison_functor;

        std::list<int*>                              outer_relation_duplicates;
        std::list<int*>                              inner_relation_duplicates;
        std::list<int*>::iterator                    inner_relation_duplicates_position;

        int*                                         key;
        bool                                         at_end;

        const std::vector<AttributeOrderDescriptor>& result_relation_tuple_order;
        int                                          result_relation_attribute_count;

        const std::vector<int>&                      outer_relation_join_attribute_positions;
        const std::vector<int>&                      inner_relation_join_attribute_positions;
        int                                          join_attribute_count;
};

} // namespace uk_ac_ox_cs_c875114

#endif /* BINARY_SORT_MERGE_JOIN_ITERATOR_H_ */
