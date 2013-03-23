#ifndef BINARY_SORT_MERGE_JOIN_ITERATOR_H_
#define BINARY_SORT_MERGE_JOIN_ITERATOR_H_

#include <string>
#include <vector>
#include <list>
#include "equality.h"
#include "relation.h"
#include "interface_iterator.h"
#include "simple_iterator.h"

namespace uk_ac_ox_cs_c875114
{

/**
 * Binary sort-merge join iterator. It produces a non-materialized result of sort-merge joining
 * two relations. The tuples of a resulting iterator are sorted based on the given join-order.
 */
class BinarySortMergeJoinIterator : public virtual IIterator<int*>
{
    public:
        /**
         * Holds the information on how to produce the correct order of attributes in the
         * resulting relation's tuple from the two source relation tuples.
         */
        struct AttributeOrderDescriptor
        {
            bool is_outer_relation;        /**< Flag to check whether the result tuple value should be produced
                                                by taking a value from the outer or from the inner relation. */
            int  relation_attribute_index; /**< Index of the attribute from which the value should be taken. */
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
        /**
         * Functor for lexicographically comparing tuples from the same relation.
         */
        struct SameRelationTupleComparisonFunctor
        {
            /**
             * Constructs the functor given the positions of the attributes over which
             * the tuples should be compared.
             * @param compare_positions Positions of arguments over which tuples should be compared
             */
            SameRelationTupleComparisonFunctor(const std::vector<int>& compare_positions) : compare_positions(compare_positions)
            {
                compare_positions_count = compare_positions.size();
            };

            /**
             * Compares two tuples lexicographically based on the compare attribute positions (initialized in the constructor).
             * @param first_tuple First tuple.
             * @param second_tuple Second tuple.
             * @returns first tuple < second tuple, if kLessThan is returned,
             *          first tuple > second tuple, if kGreaterThan is returned,
             *          first tuple = second tuple, if kEqual is returned.
             */
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

            /**
             * Compares two tuples lexicographically based on the compare attribute positions (initialized in the constructor).
             * @param first_tuple First tuple.
             * @param second_tuple Second tuple.
             * @returns true if first tuple < second tuple, false otherwise.
             */
            bool operator()(const int* first_tuple, const int* second_tuple)
            {
                return (kLessThan == CompareTuples(first_tuple, second_tuple));
            }

            const std::vector<int>& compare_positions;        /**< Attribute positions over which tuples should be compared. */
            int                     compare_positions_count;  /**< Total number of attributes over which tuples should be compared. */
        };

        void     GatherSameKeyTuples(SimpleIterator& relation_iterator, SameRelationTupleComparisonFunctor& comparison_functor, std::list<int*>& out_same_key_tuples);
        void     CreateResultTupleAsKey(int* outer_tuple, int* inner_tuple);
        Equality CompareTuplesAtDifferentRelations(int* outer_relation_tuple, int* inner_relation_tuple);

        Relation&                                    outer_relation;                          /**< Reference to outer relation. */
        Relation&                                    inner_relation;                          /**< Reference to inner relation. */

        SimpleIterator*                              outer_relation_iterator;                 /**< Simple outer relation iterator. */
        SimpleIterator*                              inner_relation_iterator;                 /**< Simple inner relation iterator. */

        SameRelationTupleComparisonFunctor           outer_relation_tuple_comparison_functor; /* Outer relation tuple comparison functor. */
        SameRelationTupleComparisonFunctor           inner_relation_tuple_comparison_functor; /* Inner relation tuple comparison functor. */

        std::list<int*>                              outer_relation_duplicates;               /**< A list of tuples with the same attribute values at the join positions for the outer relation. */
        std::list<int*>                              inner_relation_duplicates;               /**< A list of tuples with the same attribute values at the join positions for the inner relation. */
        std::list<int*>::iterator                    inner_relation_duplicates_position;      /**< An iterator through the inner relation tuples with the same attribute values as the current key. */

        int*                                         key;                                     /**< A pointer to the current key. */
        bool                                         at_end;                                  /** "At-end" flag. */

        const std::vector<AttributeOrderDescriptor>& result_relation_tuple_order;             /**< Attribute re-ordering vector which describes how a result tuple should be built from the two source tuples. */
        int                                          result_relation_attribute_count;         /**< Result relation tuple size. */

        const std::vector<int>&                      outer_relation_join_attribute_positions; /**< A vector of join attribute positions within the attributes of outer relation. */
        const std::vector<int>&                      inner_relation_join_attribute_positions; /**< A vector of join attribute positions within the attributes of inner relation. */
        int                                          join_attribute_count;                    /**< Join attribute count. */
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* BINARY_SORT_MERGE_JOIN_ITERATOR_H_ */
