#ifndef JOIN_ALGORITHM_TYPE_H_
#define JOIN_ALGORITHM_TYPE_H_

namespace c875114
{

/**
 * Join algorithm type. Sort-merge (kSortMerge), trie-based sort-merge (kSortMergeTrie) and leapfrog (kLeapfrog) join algorithms are supported.
 */
enum JoinAlgorithmType
{
    kSortMerge = 0,
    kSortMergeTrie,
    kLeapfrog
};

} /* namespace c875114 */

#endif /* JOIN_ALGORITHM_TYPE_H_ */
