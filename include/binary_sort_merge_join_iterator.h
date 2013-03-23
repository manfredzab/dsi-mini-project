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
 * Binary sort-merge join class. It produces a non-materialized result of sort-merge joining
 * two relations. The tuples of a resulting iterator are sorted based on the given join-order.
 */
class BinarySortMergeJoinIterator : public virtual IIterator<int*>
{
    public:
        /**
         * A structure used in producing the correct order of attributes in the resulting tuple
         * from the two source tuples.
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

        /**
         * Initializes the iterator. This method must be called before calling any other method
         * of the iterator.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Init();

        /**
         * Returns the tuple key at a current position of the iterator.
         * @param out_key A pointer to the memory location where the tuple should be
         *                stored.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Key(int** out_key);

        /**
         * Positions the join iterator at the next position in the join result.
         * @returns kOK on success, failure otherwise.
         */
        virtual Status Next();

        /**
         * Checks if the join iterator is positioned at the last tuple in the join result.
         * @returns true if the iterator is positioned at the last tuple, false otherwise.
         */
        virtual bool AtEnd();

        /**
         * Not supported by the binary sort merge join iterator.
         * @returns kNotSupported
         */
        virtual Status Multiplicity(int* out_result);


    private:
        /**
         * A functor for lexicographically comparing tuples from the same relation.
         */
        struct SameRelationTupleComparisonFunctor
        {
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

            bool operator()(const int* first_tuple, const int* second_tuple)
            {
                return (kLessThan == CompareTuples(first_tuple, second_tuple));
            }

            const std::vector<int>& compare_positions;
            int                     compare_positions_count;
        };

        /**
         * Gathers tuples with the same key, starting at the current relation iterator position.
         * @param relation_iterator A reference to a simple relation iterator.
         * @param comparison_functor A reference to the tuple comparison functor (@see SameRelationTupleComparisonFunctor).
         * @param out_same_key_result_tuples A reference to the list into which the same key tuples should be placed.
         */
        void  GatherSameKeyTuples(SimpleIterator& relation_iterator, SameRelationTupleComparisonFunctor& comparison_functor, std::list<int*>& out_same_key_tuples);

        /**
         * Builds a resulting relation tuple from the two input relation tuples (from outer and inner relations).
         * The result is stored in the "key" member of the binary sort-merge join iterator.
         * @param outer_tuple Outer relation tuple.
         * @param inner_tuple Inner relation tuple.
         */
        void CreateResultTupleAsKey(int* outer_tuple, int* inner_tuple);

        /**
         * Lexicographically compares tuples from outer and inner relations based on the join attribute positions.
         * @param outer_relation_tuple Outer relation tuple.
         * @param inner_relation_tuple Inner relation tuple.
         * @returns Lexicographic comparison result.
         */
        Equality CompareTuplesAtDifferentRelations(int* outer_relation_tuple, int* inner_relation_tuple);

        Relation&                                    outer_relation;                          /**< Reference to outer relation. */
        Relation&                                    inner_relation;                          /**< Reference to inner relation. */

        SimpleIterator*                              outer_relation_iterator;                 /**< Simple outer relation iterator. */
        SimpleIterator*                              inner_relation_iterator;                 /**< Simple inner relation iterator. */

        SameRelationTupleComparisonFunctor           outer_relation_tuple_comparison_functor; /* Outer relation tuple comparison functor. */
        SameRelationTupleComparisonFunctor           inner_relation_tuple_comparison_functor; /* Inner relation tuple comparison functor. */

        std::list<int*>                              outer_relation_duplicates;               /**< A list of tuples with the same attribute values at the
                                                                                                   join positions for the outer relation. */
        std::list<int*>                              inner_relation_duplicates;               /**< A list of tuples with the same attribute values at the
                                                                                                   join positions for the inner relation. */
        std::list<int*>::iterator                    inner_relation_duplicates_position;      /**< An iterator through the inner relation tuples with the
                                                                                                   same attribute values as the current key. */

        int*                                         key;                                     /**< A pointer to the current key. */
        bool                                         at_end;                                  /** "At-end" flag. */

        const std::vector<AttributeOrderDescriptor>& result_relation_tuple_order;             /**< Attribute re-ordering vector which describes how a
                                                                                                   result tuple should be built from the two source tuples. */
        int                                          result_relation_attribute_count;         /**< Result relation tuple size. */

        const std::vector<int>&                      outer_relation_join_attribute_positions; /**< A vector of join attribute positions within the attributes
                                                                                                   of outer relation. */
        const std::vector<int>&                      inner_relation_join_attribute_positions; /**< A vector of join attribute positions within the attributes
                                                                                                   of inner relation. */
        int                                          join_attribute_count;                    /**< Join attribute count. */
};

} /* namespace uk_ac_ox_cs_c875114 */

#endif /* BINARY_SORT_MERGE_JOIN_ITERATOR_H_ */
