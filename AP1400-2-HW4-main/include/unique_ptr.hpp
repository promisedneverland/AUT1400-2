
template <typename T>
UniquePtr<T> make_unique(T t) {
    return UniquePtr<T>(new T(t));
}
