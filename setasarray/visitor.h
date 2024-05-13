#ifndef SETASARRAY_VISITOR_H
#define SETASARRAY_VISITOR_H

template<typename T>
class Visitor {
public:
    virtual void Visit(T &element) = 0;

    virtual bool IsDone() const { return false; }
};

class AddingVisitor : public Visitor<int> {
private:
    int sum = 0;
    bool isDone = false;
public:
    AddingVisitor();
    void Visit(int &element);
    int getAndResetSum();
};

class Odd_Visitor : public Visitor<int> {
protected:
    bool IsDone_;
public:
    Odd_Visitor() : IsDone_(false) {};

    void Visit(int &element);
    bool IsDone() const { return IsDone_; }
};

#endif //SETASARRAY_VISITOR_H
