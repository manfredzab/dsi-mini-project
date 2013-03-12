#ifndef QUERY_H_
#define QUERY_H_

struct Query
{
    public:
        std::vector<std::string> relation_names;
        std::vector<std::string> join_attributes;
};


#endif /* QUERY_H_ */
