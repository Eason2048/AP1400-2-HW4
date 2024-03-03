#ifndef SHARED_PTR
#define SHARED_PTR

template <typename T>
class SharedPtr {
public:
    SharedPtr();
    SharedPtr(T *p);
    SharedPtr(const SharedPtr &sp);
    ~SharedPtr();

    T* get() const;
    size_t use_count() const;
    void reset();
    void reset(T *p);

    SharedPtr& operator =(const SharedPtr &sp);
    T operator *() const;
    T* operator ->();
    operator bool();
private:
    T* _p{};
    size_t* counter_ptr{};
};

template<typename T>
SharedPtr<T>::SharedPtr() {
    _p = nullptr;
    counter_ptr = nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr(T *p) {
    counter_ptr = new size_t(1);
    _p = p;
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr &sp) {
    if (counter_ptr != nullptr && *counter_ptr == 1) {
        delete counter_ptr;
        delete _p;
        _p = nullptr;
        counter_ptr = nullptr;
    }
    counter_ptr = sp.counter_ptr;
    _p = sp._p;
    *counter_ptr += 1;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    if (counter_ptr != nullptr ) {
        if (*counter_ptr == 1) {
            delete counter_ptr;
            delete _p;
            counter_ptr = nullptr;
            _p = nullptr;
        } else {
            *counter_ptr -= 1;
        }
    }
}

template<typename T>
T * SharedPtr<T>::get() const {
    return _p;
}

template<typename T>
size_t SharedPtr<T>::use_count() const {
    if (counter_ptr == nullptr) {
        return 0;
    }
    return *counter_ptr;
}

template<typename T>
void SharedPtr<T>::reset() {
    delete counter_ptr;
    delete _p;
    _p = nullptr;
    counter_ptr = nullptr;
}

template<typename T>
void SharedPtr<T>::reset(T *p) {
    delete _p;
    _p = p;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr &sp) {
    if (this != &sp) {
        if (counter_ptr != nullptr && *counter_ptr == 1) {
            delete counter_ptr;
            delete _p;
            counter_ptr = nullptr;
            _p =nullptr;
        }
        *sp.counter_ptr += 1;
        counter_ptr = sp.counter_ptr;
        _p = sp._p;
    }
    return *this;
}

template<typename T>
T SharedPtr<T>::operator*() const {
    return *_p;
}

template<typename T>
T * SharedPtr<T>::operator->() {
    return _p;
}

template<typename T>
SharedPtr<T>::operator bool() {
    return _p != nullptr;
}

template<typename T>
inline SharedPtr<T> make_shared(T t) {
    T* tmp = new T(t);
    return SharedPtr<T>(tmp);
}

#endif //SHARED_PTR
