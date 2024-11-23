
#include "shared_ptr.h"
template <typename T>
SharedPtr<T> make_shared(T t) {
    return SharedPtr<T>(new T(t));
}