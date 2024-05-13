#ifndef SETASARRAY_ITERATOR_ITERATOR_H
#define SETASARRAY_ITERATOR_ITERATOR_H


template<typename T>
class Iterator {
public:
    virtual ~Iterator() {}
    virtual bool IsDone() const = 0;
    virtual const T & operator*() const = 0;
    virtual void operator++() = 0;
};


#endif //SETASARRAY_ITERATOR_ITERATOR_H
