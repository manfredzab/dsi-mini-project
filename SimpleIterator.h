#ifndef SIMPLEITERATOR_H_
#define SIMPLEITERATOR_H_

class SimpleIterator
{
public:
    SimpleIterator();
    virtual ~SimpleIterator();

    int Key();
    int Next();
    bool AtEnd();
};

#endif /* SIMPLEITERATOR_H_ */
