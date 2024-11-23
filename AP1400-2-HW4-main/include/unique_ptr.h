#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr
{

public:
    UniquePtr(T *p) : _p(p) {}
    UniquePtr()
    {
        _p = nullptr;
    }
    UniquePtr(UniquePtr &unique_ptr) = delete;
    UniquePtr(const UniquePtr &unique_ptr) = delete;
    UniquePtr operator=(const UniquePtr &unique_ptr) = delete;

    ~UniquePtr()
    {
        delete _p;
        _p = nullptr;
    }
    T *get() { return _p; }
    T operator*()
    {
        return *_p;
    }
    T *operator->()
    {
        return _p;
    }
    void reset() {
        delete _p;
        _p = nullptr;
    }
    void reset(T* newp) {
        delete _p;
        _p = newp;
    }
    operator bool() {
        return _p != nullptr;
    }
    UniquePtr(UniquePtr&& unique_ptr) {
        _p = unique_ptr._p;
        unique_ptr._p = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& unique_ptr) {
        _p = unique_ptr._p;
        unique_ptr._p = nullptr;
        return *this;
    }
    T* release() {
        T* temp = _p;
        _p = nullptr;
        return temp;
    }
private:
    T *_p;
};

#include "unique_ptr.hpp"

#endif // UNIQUE_PTR