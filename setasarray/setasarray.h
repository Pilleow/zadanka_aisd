#ifndef SETASARRAY_SETASARRAY_H
#define SETASARRAY_SETASARRAY_H

#include <vector>
#include "visitor.h"

template<typename T>
class Container {
protected:

    Container() {};
public:
    virtual int Count() const = 0;

    virtual bool IsEmpty() const { return Count() == 0; };

    virtual bool IsFull() const = 0;

    virtual void MakeNull() = 0;

    virtual void Accept(Visitor<T> &v) = 0;
};


template<typename T>
class Set : public virtual Container<T> {
protected:
    int count;
    int universeSize;
public:
    Set(int n) : universeSize(n) {}

    int UniverseSize() const { return universeSize; }

    int Count() const { return count; };

    virtual void Insert(T element) = 0;

    virtual bool IsMember(T element) const = 0;

    virtual void Withdraw(T element) = 0;
};


class SetAsArray : public Set<int> {
    std::vector<bool> array;
public:
    SetAsArray(unsigned int);

    void MakeNull();

    void Insert(int element);

    bool IsMember(int element) const;

    void Withdraw(int element);

    bool IsFull() const { return (Count() == UniverseSize()); };

    void Accept(Visitor<int> &v);

    friend SetAsArray operator+(
            SetAsArray const &, SetAsArray const &);

    friend SetAsArray operator-(
            SetAsArray const &, SetAsArray const &);

    friend SetAsArray operator*(
            SetAsArray const &, SetAsArray const &);

    friend bool operator==(
            SetAsArray const &, SetAsArray const &);

    friend bool operator<=(
            SetAsArray const &, SetAsArray const &);

    void Wypisz() const;
};

#endif //SETASARRAY_SETASARRAY_H
