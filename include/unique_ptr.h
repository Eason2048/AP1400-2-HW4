#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
public:
    explicit UniquePtr(T* p);
    UniquePtr() = default;
    UniquePtr(const UniquePtr &p) = delete;

    ~UniquePtr();

    T* get();

    void reset();
    void reset(T* p);
    T* release();

    T operator*() const;
    UniquePtr& operator=(const UniquePtr& rhs) = delete;
    T* operator->();
    operator bool() const;
private:
    T* _p{};
};

template<typename T>
UniquePtr<T>::UniquePtr(T *p) {
    _p = p;
}

template<typename T>
UniquePtr<T>::~UniquePtr() {
    delete _p;
    _p = nullptr;
}

template<typename T>
T * UniquePtr<T>::get() {
    return _p;
}

template<typename T>
void UniquePtr<T>::reset() {
    delete _p;
    _p = nullptr;
}

template<typename T>
void UniquePtr<T>::reset(T *p) {
    delete _p;
    _p = p;
}

template<typename T>
T * UniquePtr<T>::release() {
    T* p = _p;
    _p = nullptr;
    return p;
}

template<typename T>
T UniquePtr<T>::operator*() const {
    return *_p;
}

template<typename T>
T * UniquePtr<T>::operator->() {
    return _p;
}

template<typename T>
UniquePtr<T>::operator bool() const {
    return _p != nullptr;
}

template <typename T>
inline UniquePtr<T> make_unique(T p) {
    T* t = new T{p};
    return UniquePtr<T>(t);
}







#endif //UNIQUE_PTR