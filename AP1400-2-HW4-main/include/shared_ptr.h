#ifndef SHARED_PTR
#define SHARED_PTR

#include <iostream>
template <typename T>
class SharedPtr
{
public:
    SharedPtr() : _p(nullptr), referenceCount(nullptr) {}
    SharedPtr(T *_p) : _p(_p)
    {
        referenceCount = new int(1);
    }
    SharedPtr(const SharedPtr &sharedPtr)
    {
        _p = sharedPtr._p;
        referenceCount = sharedPtr.referenceCount;
        (*referenceCount)++;
    }
    SharedPtr operator=(const SharedPtr &sharedPtr)
    {
        if (sharedPtr._p == _p)
        {
            return *this;
        }
        loseOnePointer();
        _p = sharedPtr._p;
        referenceCount = sharedPtr.referenceCount;
        if (referenceCount)
        {
            (*referenceCount)++;
        }
        return *this;
        std::cout << *_p << use_count() << std::endl;
    }
    int use_count() { return referenceCount == nullptr ? 0 : *referenceCount; }
    T *get() { return _p; }
    T operator*() { return *_p; }
    T *operator->() { return _p; }
    operator bool()
    {
        return _p != nullptr;
    }
    void reset()
    {
        loseOnePointer();
    }
    void reset(T *p)
    {
        loseOnePointer();
        _p = p;
        referenceCount = new int(1);
    }
    void loseOnePointer()
    {
        if (referenceCount != nullptr)
        {
            (*referenceCount)--;
            if (*referenceCount <= 0)
            {
                delete _p;
                delete referenceCount;
                _p = nullptr;
                referenceCount = nullptr;
            }
        }
    }
    ~SharedPtr()
    {
        loseOnePointer();;
    }

private:
    T *_p = nullptr;
    int *referenceCount = nullptr;
};

#include "shared_ptr.hpp"
#endif // SHARED_PTR