/* MSL
 * Copyright (c) 1995-2006 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2006/02/09 16:58:58 $
 * $Revision: 1.21.2.5 $
 */

// Adapted for interoperation with reverse-engineered headers.

#pragma once

#include "Metrowerks/compressed_pair.h"
#include <MSL_C++/MSL_Common/detail/type_traits.hpp>
#include <MSL_C++/MSL_Common/type_traits.h>

#define _MSL_NO_THROW throw()

#if !_MSL_TR1_NAMESPACE
#define _TR1 tr1
#define _STD_TR1 _STD::tr1
#ifdef _MSL_NO_CPP_NAMESPACE
#define _MSL_START_TR1_NAMESPACE namespace tr1 {
#define _MSL_END_TR1_NAMESPACE }
#else // _MSL_NO_CPP_NAMESPACE
#define _MSL_START_TR1_NAMESPACE                                               \
    namespace std {                                                            \
    namespace tr1 {
#define _MSL_END_TR1_NAMESPACE                                                 \
    }                                                                          \
    }
#endif // _MSL_NO_CPP_NAMESPACE
#else  // _MSL_TR1_NAMESPACE
#ifdef _MSL_NO_CPP_NAMESPACE
#define _MSL_START_TR1_NAMESPACE
#define _MSL_END_TR1_NAMESPACE
#else // _MSL_NO_CPP_NAMESPACE
#define _MSL_START_TR1_NAMESPACE namespace std {
#define _MSL_END_TR1_NAMESPACE }
#endif // _MSL_NO_CPP_NAMESPACE
#define _TR1 _STD
#define _STD_TR1 _STD
#endif // _MSL_TR1_NAMESPACE

// msl_smart_pointers

#ifndef _MSL_SMART_POINTERS
#define _MSL_SMART_POINTERS

// #include <mslconfig>

#include <exception>
#include <iosfwd>
#include <msl_utility>
#include <typeinfo>

#if defined(_MSL_SHARED_PTR_HAS_MUTEX) && !defined(__POWERPC__)
#include <msl_mutex>
#endif
#ifdef _MSL_ARRAY_AUTO_PTR
#include <RefCountedPtrArray.h>
#endif

#ifndef RC_INVOKED

#ifdef __MWERKS__
#pragma options align = native
#endif

#ifdef _MSL_FORCE_ENUMS_ALWAYS_INT
#if _MSL_FORCE_ENUMS_ALWAYS_INT
#pragma enumsalwaysint on
#else
#pragma enumsalwaysint off
#endif
#endif // _MSL_FORCE_ENUMS_ALWAYS_INT

#ifdef _MSL_FORCE_ENABLE_BOOL_SUPPORT
#if _MSL_FORCE_ENABLE_BOOL_SUPPORT
#pragma bool on
#else
#pragma bool off
#endif
#endif // _MSL_FORCE_ENABLE_BOOL_SUPPORT

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifndef _MSL_NO_CPP_NAMESPACE
namespace std {
#endif

namespace detail {

template <typename T> struct default_delete {
    default_delete() {}
    template <class U> default_delete(const default_delete<U> &) {}
    void operator()(T *ptr) const {
        typedef char incomplete[sizeof(T)];
        delete ptr;
    }
};

template <typename T> struct default_delete<T[]> {
    void operator()(T *ptr) const {
        typedef char incomplete[sizeof(T)];
        delete[] ptr;
    }
};

template <typename T, size_t N> struct default_delete<T[N]> {
    void operator()(T *ptr, size_t) const {
        typedef char incomplete[sizeof(T)];
        delete[] ptr;
    }
};

} // namespace detail

//  lib.auto.ptr, pointers:

#ifndef _MSL_USE_AUTO_PTR_96

// hh 980103 Nov. '97 version of auto_ptr added
// hh 980805 member template operators not supported yet.

#if defined(_MSL_ARRAY_AUTO_PTR) && !defined(_MSL_NO_MEMBER_TEMPLATE)

template <class Y, class traits> struct auto_ptr_ref {
    Y *ptr_;
};

template <class X, class traits = _Single<X>> class auto_ptr {
  public:
    typedef X element_type;

    //  lib.auto.ptr.cons construct/copy/destroy:
    explicit auto_ptr(X *p = 0) _MSL_NO_THROW;
    auto_ptr(auto_ptr &a) _MSL_NO_THROW;
#ifndef _MSL_MUST_INLINE_MEMBER_TEMPLATE
    template <class Y>
    auto_ptr(auto_ptr<Y, typename traits::rebind<Y>::other> &a) _MSL_NO_THROW;
#else
    template <class Y>
    inline auto_ptr(auto_ptr<Y, typename traits::rebind<Y>::other> &a)
        _MSL_NO_THROW : ptr_(a.release()) {}
#endif // _MSL_MUST_INLINE_MEMBER_TEMPLATE
    auto_ptr &operator=(auto_ptr &a) _MSL_NO_THROW;
#ifndef _MSL_MUST_INLINE_MEMBER_TEMPLATE
    template <class Y>
    auto_ptr &
    operator=(auto_ptr<Y, typename traits::rebind<Y>::other> &a) _MSL_NO_THROW;
#else
    template <class Y>
    inline auto_ptr &
    operator=(auto_ptr<Y, typename traits::rebind<Y>::other> &a) _MSL_NO_THROW {
        reset(a.release());
        return *this;
    }
#endif // _MSL_MUST_INLINE_MEMBER_TEMPLATE
    ~auto_ptr() __attribute__((nothrow));

    //  lib.auto.ptr.members members:
    X &operator*() const _MSL_NO_THROW;
    X *operator->() const _MSL_NO_THROW;
    X *get() const _MSL_NO_THROW;
    X *release() _MSL_NO_THROW;
    void reset(X *p = 0) _MSL_NO_THROW;

    //  lib.auto.ptr.conv conversions:
    auto_ptr(auto_ptr_ref<X, traits> r) _MSL_NO_THROW;
    auto_ptr &operator=(auto_ptr_ref<X, traits> r) _MSL_NO_THROW;
#if !defined(_MSL_NO_MEMBER_TEMPLATE) && __MWERKS__ >= 0x2400
    template <class Y>
    operator auto_ptr_ref<Y, typename traits::rebind<Y>::other>() _MSL_NO_THROW;
    template <class Y>
    operator auto_ptr<Y, typename traits::rebind<Y>::other>() _MSL_NO_THROW;
#endif // !defined (_MSL_NO_MEMBER_TEMPLATE) && __MWERKS__ >= 0x2400
  private:
    X *ptr_;
};

template <class X, class traits>
inline X *auto_ptr<X, traits>::release() _MSL_NO_THROW {
    X *tmp = ptr_;
    ptr_ = 0;
    return tmp;
}

template <class X, class traits>
inline void auto_ptr<X, traits>::reset(X *p) _MSL_NO_THROW {
    if (ptr_ != p) {
        traits::destroy(ptr_);
        ptr_ = p;
    }
}

template <class X, class traits>
inline auto_ptr<X, traits>::auto_ptr(X *p) _MSL_NO_THROW : ptr_(p) {}

template <class X, class traits>
inline auto_ptr<X, traits>::auto_ptr(auto_ptr &a) _MSL_NO_THROW
    : ptr_(a.release()) {}

#ifndef _MSL_MUST_INLINE_MEMBER_TEMPLATE

template <class X, class traits>
template <class Y>
inline auto_ptr<X, traits>::auto_ptr(
    auto_ptr<Y, typename traits::rebind<Y>::other> &a) _MSL_NO_THROW
    : ptr_(a.release()) {}

#endif // _MSL_MUST_INLINE_MEMBER_TEMPLATE

template <class X, class traits>
inline auto_ptr<X, traits> &
auto_ptr<X, traits>::operator=(auto_ptr &a) _MSL_NO_THROW {
    reset(a.release());
    return *this;
}

#ifndef _MSL_MUST_INLINE_MEMBER_TEMPLATE

template <class X, class traits>
template <class Y>
inline auto_ptr<X, traits> &auto_ptr<X, traits>::operator=(
    auto_ptr<Y, typename traits::rebind<Y>::other> &a) _MSL_NO_THROW {
    reset(a.release());
    return *this;
}

#endif // _MSL_MUST_INLINE_MEMBER_TEMPLATE

template <class X, class traits> inline auto_ptr<X, traits>::~auto_ptr() {
    traits::destroy(ptr_);
}

template <class X, class traits>
inline X &auto_ptr<X, traits>::operator*() const _MSL_NO_THROW {
    return *ptr_;
}

template <class X, class traits>
inline X *auto_ptr<X, traits>::operator->() const _MSL_NO_THROW {
    return ptr_;
}

template <class X, class traits>
inline X *auto_ptr<X, traits>::get() const _MSL_NO_THROW {
    return ptr_;
}

template <class X, class traits>
inline auto_ptr<X, traits>::auto_ptr(auto_ptr_ref<X, traits> r) _MSL_NO_THROW
    : ptr_(r.ptr_) {}

template <class X, class traits>
inline auto_ptr<X, traits> &
auto_ptr<X, traits>::operator=(auto_ptr_ref<X, traits> r) _MSL_NO_THROW {
    reset(r.ptr_);
    return *this;
}

#if !defined(_MSL_NO_MEMBER_TEMPLATE) && __MWERKS__ >= 0x2400

template <class X, class traits>
template <class Y>
inline auto_ptr<X, traits>::operator auto_ptr_ref<
    Y, typename traits::rebind<Y>::other>() _MSL_NO_THROW {
    auto_ptr_ref<Y, typename traits::rebind<Y>::other> r;
    r.ptr_ = release();
    return r;
}

template <class X, class traits>
template <class Y>
inline auto_ptr<X, traits>::operator auto_ptr<
    Y, typename traits::rebind<Y>::other>() _MSL_NO_THROW {
    return auto_ptr<Y, typename traits::rebind<Y>::other>(release());
}

#endif // !defined (_MSL_NO_MEMBER_TEMPLATE) && __MWERKS__ >= 0x2400

#else // defined(_MSL_ARRAY_AUTO_PTR) && !defined(_MSL_NO_MEMBER_TEMPLATE)

template <class Y> struct auto_ptr_ref {
    Y *ptr_;
};

template <class X> class auto_ptr {
  public:
    typedef X element_type;

    //  lib.auto.ptr.cons construct/copy/destroy:
    explicit auto_ptr(X *p = 0) _MSL_NO_THROW;
    auto_ptr(auto_ptr &a) _MSL_NO_THROW;
#ifndef _MSL_NO_MEMBER_TEMPLATE
#ifndef _MSL_MUST_INLINE_MEMBER_TEMPLATE
    template <class Y> auto_ptr(auto_ptr<Y> &a) _MSL_NO_THROW;
#else
    template <class Y>
    inline auto_ptr(auto_ptr<Y> &a) _MSL_NO_THROW : ptr_(a.release()) {}
#endif // _MSL_MUST_INLINE_MEMBER_TEMPLATE
#endif // _MSL_NO_MEMBER_TEMPLATE
    auto_ptr &operator=(auto_ptr &a) _MSL_NO_THROW;
#ifndef _MSL_NO_MEMBER_TEMPLATE
#ifndef _MSL_MUST_INLINE_MEMBER_TEMPLATE
    template <class Y> auto_ptr &operator=(auto_ptr<Y> &a) _MSL_NO_THROW;
#else
    template <class Y>
    inline auto_ptr &operator=(auto_ptr<Y> &a) _MSL_NO_THROW {
        reset(a.release());
        return *this;
    }
#endif // _MSL_MUST_INLINE_MEMBER_TEMPLATE
#endif // _MSL_NO_MEMBER_TEMPLATE
    ~auto_ptr() __attribute__((nothrow));

    //  lib.auto.ptr.members members:
    X &operator*() const _MSL_NO_THROW;
    X *operator->() const _MSL_NO_THROW;
    X *get() const _MSL_NO_THROW;
    X *release() _MSL_NO_THROW;
    void reset(X *p = 0) _MSL_NO_THROW;

    //  lib.auto.ptr.conv conversions:
    auto_ptr(auto_ptr_ref<X> r) _MSL_NO_THROW;
    auto_ptr &operator=(auto_ptr_ref<X> r) _MSL_NO_THROW;
#if !defined(_MSL_NO_MEMBER_TEMPLATE) && __MWERKS__ >= 0x2400
    template <class Y> operator auto_ptr_ref<Y>() _MSL_NO_THROW;
    template <class Y> operator auto_ptr<Y>() _MSL_NO_THROW;
#endif // !defined (_MSL_NO_MEMBER_TEMPLATE) && __MWERKS__ >= 0x2400
  private:
    X *ptr_;
};

template <class X> inline X *auto_ptr<X>::release() _MSL_NO_THROW {
    X *tmp = ptr_;
    ptr_ = 0;
    return tmp;
}

template <class X> inline void auto_ptr<X>::reset(X *p) _MSL_NO_THROW {
    if (ptr_ != p) {
        delete ptr_;
        ptr_ = p;
    }
}

template <class X> inline auto_ptr<X>::auto_ptr(X *p) _MSL_NO_THROW : ptr_(p) {}

template <class X>
inline auto_ptr<X>::auto_ptr(auto_ptr &a) _MSL_NO_THROW : ptr_(a.release()) {}

#ifndef _MSL_NO_MEMBER_TEMPLATE
#ifndef _MSL_MUST_INLINE_MEMBER_TEMPLATE

template <class X>
template <class Y>
inline auto_ptr<X>::auto_ptr(auto_ptr<Y> &a) _MSL_NO_THROW : ptr_(a.release()) {
}

#endif // _MSL_MUST_INLINE_MEMBER_TEMPLATE
#endif // _MSL_NO_MEMBER_TEMPLATE

template <class X>
inline auto_ptr<X> &auto_ptr<X>::operator=(auto_ptr &a) _MSL_NO_THROW {
    reset(a.release());
    return *this;
}

#ifndef _MSL_NO_MEMBER_TEMPLATE
#ifndef _MSL_MUST_INLINE_MEMBER_TEMPLATE

template <class X>
template <class Y>
inline auto_ptr<X> &auto_ptr<X>::operator=(auto_ptr<Y> &a) _MSL_NO_THROW {
    reset(a.release());
    return *this;
}

#endif // _MSL_MUST_INLINE_MEMBER_TEMPLATE
#endif // _MSL_NO_MEMBER_TEMPLATE

template <class X> inline auto_ptr<X>::~auto_ptr() { delete ptr_; }

template <class X> inline X &auto_ptr<X>::operator*() const _MSL_NO_THROW {
    return *ptr_;
}

template <class X> inline X *auto_ptr<X>::operator->() const _MSL_NO_THROW {
    return ptr_;
}

template <class X> inline X *auto_ptr<X>::get() const _MSL_NO_THROW {
    return ptr_;
}

template <class X>
inline auto_ptr<X>::auto_ptr(auto_ptr_ref<X> r) _MSL_NO_THROW : ptr_(r.ptr_) {}

template <class X>
inline auto_ptr<X> &auto_ptr<X>::operator=(auto_ptr_ref<X> r) _MSL_NO_THROW {
    reset(r.ptr_);
    return *this;
}

#if !defined(_MSL_NO_MEMBER_TEMPLATE) && __MWERKS__ >= 0x2400

template <class X>
template <class Y>
inline auto_ptr<X>::operator auto_ptr_ref<Y>() _MSL_NO_THROW {
    auto_ptr_ref<Y> r;
    r.ptr_ = release();
    return r;
}

template <class X>
template <class Y>
inline auto_ptr<X>::operator auto_ptr<Y>() _MSL_NO_THROW {
    return auto_ptr<Y>(release());
}

#endif // !defined (_MSL_NO_MEMBER_TEMPLATE) && __MWERKS__ >= 0x2400

#endif // defined(_MSL_ARRAY_AUTO_PTR) && !defined(_MSL_NO_MEMBER_TEMPLATE)

#else // _MSL_USE_AUTO_PTR_96

// hh 980103 Dec. '96 version of auto_ptr fixed

template <class X> class auto_ptr {
  public:
    typedef X element_type;
    explicit auto_ptr(X *p = 0) _MSL_NO_THROW;
#ifndef _MSL_NO_MEMBER_TEMPLATE
    template <class Y> auto_ptr(const auto_ptr<Y> &a) _MSL_NO_THROW;
    template <class Y> auto_ptr &operator=(const auto_ptr<Y> &a) _MSL_NO_THROW;
#endif // _MSL_NO_MEMBER_TEMPLATE
    auto_ptr(const auto_ptr &a) _MSL_NO_THROW;
    auto_ptr &operator=(const auto_ptr &a) _MSL_NO_THROW;
    ~auto_ptr() __attribute__((nothrow));
    X &operator*() const _MSL_NO_THROW;
    X *operator->() const _MSL_NO_THROW;
    X *get() const _MSL_NO_THROW;
    X *release() const _MSL_NO_THROW;
    bool owns() const _MSL_NO_THROW;

  private:
    X *ptr_;
    mutable bool owns_;
};

template <class X> inline bool auto_ptr<X>::owns() const _MSL_NO_THROW {
    return owns_;
}

template <class X> inline X *auto_ptr<X>::release() const _MSL_NO_THROW {
    owns_ = false;
    return ptr_;
}

template <class X>
inline auto_ptr<X>::auto_ptr(X *p) _MSL_NO_THROW : ptr_(p), owns_(p != 0) {}

#ifndef _MSL_NO_MEMBER_TEMPLATE

template <class X>
template <class Y>
inline auto_ptr<X>::auto_ptr(const auto_ptr<Y> &a) _MSL_NO_THROW {
    owns_ = a.owns();
    ptr_ = a.release();
}

template <class X>
template <class Y>
inline auto_ptr<X> &auto_ptr<X>::operator=(const auto_ptr<Y> &a) _MSL_NO_THROW {
    if (owns_)
        delete ptr_;
    owns_ = a.owns();
    ptr_ = a.release();
    return *this;
}

#endif // _MSL_NO_MEMBER_TEMPLATE

template <class X>
inline auto_ptr<X>::auto_ptr(const auto_ptr &a) _MSL_NO_THROW {
    owns_ = a.owns_;
    ptr_ = a.release();
}

// hh 980923 rewrote op=
template <class X>
auto_ptr<X> &auto_ptr<X>::operator=(const auto_ptr &a) _MSL_NO_THROW {
    if (this == &a)
        return *this;
    if (ptr_ == a.ptr_) {
        owns_ = owns_ || a.owns_;
        ptr_ = a.release();
    } else {
        if (owns_)
            delete ptr_;
        owns_ = a.owns_;
        ptr_ = a.release();
    }
    return *this;
}

template <class X> inline auto_ptr<X>::~auto_ptr() {
    if (owns_)
        delete ptr_;
}

template <class X> inline X &auto_ptr<X>::operator*() const _MSL_NO_THROW {
    return *ptr_;
}

template <class X> inline X *auto_ptr<X>::operator->() const _MSL_NO_THROW {
    return ptr_;
}

template <class X> inline X *auto_ptr<X>::get() const _MSL_NO_THROW {
    return ptr_;
}

#endif // _MSL_USE_AUTO_PTR_96

#ifndef _MSL_NO_CPP_NAMESPACE
} // namespace std
#endif

#ifndef _MSL_NO_CPP_NAMESPACE
namespace Metrowerks {
#else
#ifndef Metrowerks
#define Metrowerks
#endif
#endif // _MSL_NO_CPP_NAMESPACE

template <class Allocator> class alloc2deleter {
    typedef typename remove_reference<Allocator>::type::pointer pointer;
    typedef typename remove_reference<Allocator>::type::size_type size_type;
    typedef typename ::detail::select<is_reference<Allocator>::value, Allocator,
                                      const Allocator &>::type param;

  public:
    alloc2deleter(param alloc, size_type size) : alloc_(alloc), size_(size) {}
    void operator()(pointer ptr) { alloc_.deallocate(ptr, size_); }

  private:
    Allocator alloc_;
    size_type size_;
};

namespace detail {

#ifndef _MSL_MOVE

template <class Imp> struct move_ptr_ref {
    move_ptr_ref(const Imp &p) : p_(p) {}
    Imp p_;
};

#endif // _MSL_MOVE

} // namespace detail

template <class T, class D = typename std::detail::default_delete<T> >
class move_ptr {
  private:
    typedef compressed_pair<T *, D> imp_type;

  public:
    typedef T element_type;

  private:
    struct nat {
        int dummy_;
    };
    typedef typename remove_const<element_type>::type non_const_type;

  public:
    typedef D deleter_type;

    move_ptr() : ptr_((T *)0) {}

    template <class Y>
    explicit move_ptr(
        Y *p, typename restrict_to<is_convertible<Y *, T *>::value, nat>::type =
                  nat())
        : ptr_(p) {}

    move_ptr(
        T *p,
        typename ::detail::select<is_reference<D>::value, D, const D &>::type d)
        : ptr_(p, d) {}

    // enable move from rvalue
#ifdef _MSL_MOVE
    move_ptr(T *p, typename remove_reference<D>::type &&d) : ptr_(p, move(d)) {
        __static_assert(!is_reference<D>::value,
                        "rvalue deleter bound to reference");
    }

    move_ptr(move_ptr &&a) : ptr_(a.release(), forward<D>(a.ptr_.second())) {}

    template <class U, class E>
    move_ptr(
        move_ptr<U, E> &&a,
        typename restrict_to<
            is_convertible<U *, T *>::value && is_convertible<E, D>::value &&
                (!is_reference<D>::value || is_same<D, E>::value),
            nat>::type = nat())
        : ptr_(a.release(), forward<D>(a.ptr_.second())) {}

    move_ptr &operator=(move_ptr &&a) {
        reset(a.release());
        ptr_.second() = move(a.ptr_.second());
        return *this;
    }

    template <class U, class E> move_ptr &operator=(move_ptr<U, E> &&a) {
        reset(a.release());
        ptr_.second() = move(a.ptr_.second());
        return *this;
    }
#else  // _MSL_MOVE
    move_ptr(detail::move_ptr_ref<imp_type> a) : ptr_(a.p_) {}
    template <class U> move_ptr(detail::move_ptr_ref<U> a) : ptr_(a.p_) {}
    move_ptr &operator=(detail::move_ptr_ref<imp_type> a) {
        reset(a.p_.first());
        ptr_.second() = a.p_.second();
        return *this;
    }
    template <class U> move_ptr &operator=(detail::move_ptr_ref<U> a) {
        reset(a.p_.first());
        ptr_.second() = a.p_.second();
        return *this;
    }
    template <class U> operator detail::move_ptr_ref<U>() {
        return detail::move_ptr_ref<U>(U(release(), ptr_.second()));
    }
#endif // _MSL_MOVE

    ~move_ptr();

    T &operator*() const throw() { return *ptr_.first(); }
    T *operator->() const throw() { return ptr_.first(); }
    T *get() const throw() { return ptr_.first(); }
    T *release() throw() {
        T *tmp = ptr_.first();
        ptr_.first() = 0;
        return tmp;
    }
    void reset(T *p = 0);
    void swap(move_ptr &a) { ptr_.swap(a.ptr_); }
    deleter_type &get_deleter() { return ptr_.second(); }
    const deleter_type &get_deleter() const { return ptr_.second(); }

    operator int nat::*() const { return ptr_.first() ? &nat::dummy_ : 0; }
#ifdef _MSL_MOVE
    move_ptr(int nat::*) : ptr_((T *)0) {}
#endif
    move_ptr &operator=(int nat::*) {
        reset();
        return *this;
    }

  private:
    imp_type ptr_;

    // disable copy from lvalue
#ifdef _MSL_MOVE
    move_ptr(const move_ptr &a);
    template <class U, class E> move_ptr(const move_ptr<U, E> &a);
    move_ptr &operator=(const move_ptr &a);
    template <class U, class E> move_ptr &operator=(const move_ptr<U, E> &a);
#else  // _MSL_MOVE
    move_ptr(move_ptr &a);
    move_ptr &operator=(move_ptr &a);
#endif // _MSL_MOVE

    template <class U, class E> friend class move_ptr;
};

template <class T, class D> move_ptr<T, D>::~move_ptr() {
    if (ptr_.first())
        ptr_.second()(const_cast<non_const_type *>(ptr_.first()));
}

template <class T, class D> void move_ptr<T, D>::reset(T *p) {
    if (ptr_.first() != p) {
        if (ptr_.first())
            ptr_.second()(const_cast<non_const_type *>(ptr_.first()));
        ptr_.first() = p;
    }
}

template <class T, class D> class move_ptr<T[], D> {
  private:
    typedef compressed_pair<T *, D> imp_type;

  public:
    typedef T element_type;

  private:
    struct nat {
        int dummy_;
    };
    typedef typename remove_const<element_type>::type non_const_type;

  public:
    typedef D deleter_type;

    move_ptr() : ptr_((T *)0) {}

    template <class Y>
    explicit move_ptr(
        Y p,
        typename restrict_to<
            is_pointer<Y>::value &&
            is_same<typename remove_pointer<Y>::type, T>::value>::type * = 0)
        : ptr_(p) {}

    template <class Y>
    move_ptr(
        Y p,
        typename ::detail::select<is_reference<D>::value, D, const D &>::type d,
        typename restrict_to<
            is_pointer<Y>::value &&
            is_same<typename remove_pointer<Y>::type, T>::value>::type * = 0)
        : ptr_(p, d) {}

    // enable move from rvalue
#ifdef _MSL_MOVE
    template <class Y>
    move_ptr(Y p, typename remove_reference<D>::type &&d,
             typename restrict_to<is_pointer<Y>::value &&
                                  is_same<typename remove_pointer<Y>::type,
                                          T>::value>::type * = 0)
        : ptr_(p, move(d)) {
        __static_assert(!is_reference<D>::value,
                        "rvalue deleter bound to reference");
    }

    move_ptr(move_ptr &&a) : ptr_(a.release(), forward<D>(a.ptr_.second())) {}

    move_ptr &operator=(move_ptr &&a) {
        reset(a.release());
        ptr_.second() = move(a.ptr_.second());
        return *this;
    }

#else  // _MSL_MOVE
    move_ptr(detail::move_ptr_ref<imp_type> a) : ptr_(a.p_) {}
    move_ptr &operator=(detail::move_ptr_ref<imp_type> a) {
        reset(a.p_.first());
        ptr_.second() = a.p_.second();
        return *this;
    }
    operator detail::move_ptr_ref<imp_type>() {
        return detail::move_ptr_ref<imp_type>(
            imp_type(release(), ptr_.second()));
    }
#endif // _MSL_MOVE

    ~move_ptr();

    T &operator[](size_t i) const { return ptr_.first()[i]; }
    T *get() const throw() { return ptr_.first(); }
    T *release() throw() {
        T *tmp = ptr_.first();
        ptr_.first() = 0;
        return tmp;
    }
    void reset(T *p = 0);
    void swap(move_ptr &a) { ptr_.swap(a.ptr_); }
    deleter_type &get_deleter() { return ptr_.second(); }
    const deleter_type &get_deleter() const { return ptr_.second(); }

    operator int nat::*() const { return ptr_.first() ? &nat::dummy_ : 0; }
#ifdef _MSL_MOVE
    move_ptr(int nat::*) : ptr_((T *)0) {}
#endif
    move_ptr &operator=(int nat::*) {
        reset();
        return *this;
    }

  private:
    imp_type ptr_;

    // disable copy from lvalue
#ifdef _MSL_MOVE
    move_ptr(const move_ptr &a);
    move_ptr &operator=(const move_ptr &a);
#else  // _MSL_MOVE
    move_ptr(move_ptr &a);
    move_ptr &operator=(move_ptr &a);
#endif // _MSL_MOVE
    template <class U> void reset(U *);
};

template <class T, class D> move_ptr<T[], D>::~move_ptr() {
    if (ptr_.first())
        ptr_.second()(const_cast<non_const_type *>(ptr_.first()));
}

template <class T, class D> void move_ptr<T[], D>::reset(T *p) {
    if (ptr_.first() != p) {
        if (ptr_.first())
            ptr_.second()(const_cast<non_const_type *>(ptr_.first()));
        ptr_.first() = p;
    }
}

template <class T, class D, size_t N> class move_ptr<T[N], D> {
  private:
    typedef compressed_pair<T *, D> imp_type;

  public:
    typedef T element_type;

  private:
    struct nat {
        int dummy_;
    };
    typedef typename remove_const<element_type>::type non_const_type;

  public:
    typedef D deleter_type;
    static const size_t size = N;

    move_ptr() : ptr_((T *)0) {}

    template <class Y>
    explicit move_ptr(
        Y p,
        typename restrict_to<
            is_pointer<Y>::value &&
            is_same<typename remove_pointer<Y>::type, T>::value>::type * = 0)
        : ptr_(p) {}

    template <class Y>
    move_ptr(
        Y p,
        typename ::detail::select<is_reference<D>::value, D, const D &>::type d,
        typename restrict_to<
            is_pointer<Y>::value &&
            is_same<typename remove_pointer<Y>::type, T>::value>::type * = 0)
        : ptr_(p, d) {}

    // enable move from rvalue
#ifdef _MSL_MOVE
    template <class Y>
    move_ptr(Y p, typename remove_reference<D>::type &&d,
             typename restrict_to<is_pointer<Y>::value &&
                                  is_same<typename remove_pointer<Y>::type,
                                          T>::value>::type * = 0)
        : ptr_(p, move(d)) {
        __static_assert(!is_reference<D>::value,
                        "rvalue deleter bound to reference");
    }

    move_ptr(move_ptr &&a) : ptr_(a.release(), forward<D>(a.ptr_.second())) {}

    move_ptr &operator=(move_ptr &&a) {
        reset(a.release());
        ptr_.second() = move(a.ptr_.second());
        return *this;
    }

#else  // _MSL_MOVE
    move_ptr(detail::move_ptr_ref<imp_type> a) : ptr_(a.p_) {}
    move_ptr &operator=(detail::move_ptr_ref<imp_type> a) {
        reset(a.p_.first());
        ptr_.second() = a.p_.second();
        return *this;
    }
    operator detail::move_ptr_ref<imp_type>() {
        return detail::move_ptr_ref<imp_type>(
            imp_type(release(), ptr_.second()));
    }
#endif // _MSL_MOVE

    ~move_ptr();

    T &operator[](size_t i) const { return ptr_.first()[i]; }
    T *get() const throw() { return ptr_.first(); }
    T *release() throw() {
        T *tmp = ptr_.first();
        ptr_.first() = 0;
        return tmp;
    }
    void reset(T *p = 0);
    void swap(move_ptr &a) { ptr_.swap(a.ptr_); }
    deleter_type &get_deleter() { return ptr_.second(); }
    const deleter_type &get_deleter() const { return ptr_.second(); }

    operator int nat::*() const { return ptr_.first() ? &nat::dummy_ : 0; }
#ifdef _MSL_MOVE
    move_ptr(int nat::*) : ptr_((T *)0) {}
#endif
    move_ptr &operator=(int nat::*) {
        reset();
        return *this;
    }

  private:
    imp_type ptr_;

    // disable copy from lvalue
#ifdef _MSL_MOVE
    move_ptr(const move_ptr &a);
    move_ptr &operator=(const move_ptr &a);
#else  // _MSL_MOVE
    move_ptr(move_ptr &a);
    move_ptr &operator=(move_ptr &a);
#endif // _MSL_MOVE
    template <class U> void reset(U *);
};

template <class T, class D, size_t N> move_ptr<T[N], D>::~move_ptr() {
    if (ptr_.first())
        ptr_.second()(const_cast<non_const_type *>(ptr_.first()), N);
}

template <class T, class D, size_t N> void move_ptr<T[N], D>::reset(T *p) {
    if (ptr_.first() != p) {
        if (ptr_.first())
            ptr_.second()(const_cast<non_const_type *>(ptr_.first()), N);
        ptr_.first() = p;
    }
}

template <class T1, class D1, class T2, class D2>
inline bool operator==(const move_ptr<T1, D1> &a, const move_ptr<T2, D2> &b) {
    return a.get() == b.get();
}

template <class T1, class D1, class T2, class D2>
inline bool operator!=(const move_ptr<T1, D1> &a, const move_ptr<T2, D2> &b) {
    return !(a == b);
}

template <class T1, class D1, class T2, class D2>
inline bool operator<(const move_ptr<T1, D1> &a, const move_ptr<T2, D2> &b) {
    return a.get() < b.get();
}

template <class T1, class D1, class T2, class D2>
inline bool operator>(const move_ptr<T1, D1> &a, const move_ptr<T2, D2> &b) {
    return b < a;
}

template <class T1, class D1, class T2, class D2>
inline bool operator<=(const move_ptr<T1, D1> &a, const move_ptr<T2, D2> &b) {
    return !(b < a);
}

template <class T1, class D1, class T2, class D2>
inline bool operator>=(const move_ptr<T1, D1> &a, const move_ptr<T2, D2> &b) {
    return !(a < b);
}

template <class T, class D>
inline void swap(move_ptr<T, D> &a, move_ptr<T, D> &b) {
    return a.swap(b);
}

#ifndef _MSL_MOVE

// create an "rvalue" move_ptr<T>
template <class T, class D>
inline detail::move_ptr_ref<compressed_pair<T *, D> > move(move_ptr<T, D> &x) {
    return x;
}

#endif // _MSL_MOVE

// template <class T, class D>
// struct is_zero_default_contructible<move_ptr<T, D> > {
//     static const bool value = is_zero_default_contructible<D>::value;
// };

// template <class T, class D>
// struct has_trivial_dtor_after_move_ctor<move_ptr<T, D> > {
//     static const bool value = has_trivial_dtor<D>::value;
// };

// template <class T, class D> struct has_trivial_move_ctor<move_ptr<T, D> > {
//     static const bool value = has_trivial_copy_ctor<D>::value;
// };

// template <class T, class D> struct move_with_swap<move_ptr<T, D> > {
//     static const bool value =
//         has_trivial_copy_ctor<D>::value && has_trivial_assignment<D>::value;
// };

#ifndef _MSL_NO_CPP_NAMESPACE
} // namespace Metrowerks
#endif

_MSL_START_TR1_NAMESPACE

class bad_weak_ptr : public exception {
  public:
    bad_weak_ptr() {}
    virtual const char *what() const _MSL_NO_THROW { return "bad_weak_ptr"; }
};

template <class T> class shared_ptr;
template <class T> class weak_ptr;

namespace detail {

class shared_ptr_deleter_common {
  public:
    shared_ptr_deleter_common() : use_count_(1), weak_count_(1) {}
    virtual ~shared_ptr_deleter_common() {}
#if defined(_MSL_SHARED_PTR_HAS_MUTEX) && !defined(__POWERPC__)
    void attach(bool lock = true);
    void attach_weak(bool lock = true);
#else  // _MSL_SHARED_PTR_HAS_MUTEX
    void attach();
    void attach_weak();
#endif // _MSL_SHARED_PTR_HAS_MUTEX
    void release();
#if defined(_MSL_SHARED_PTR_HAS_MUTEX) && defined(__POWERPC__)
    void release_weak(unsigned acquired = 0, unsigned released = 0);
#else
    void release_weak();
#endif
    ptrdiff_t use_count() const { return use_count_; }
#ifndef _MSL_NO_RTTI
    virtual const void *get_deleter(const type_info &) const = 0;
#endif
    virtual void dispose() = 0;

  private:
    ptrdiff_t use_count_;
    ptrdiff_t weak_count_;
#if defined(_MSL_SHARED_PTR_HAS_MUTEX) && !defined(__POWERPC__)
    Metrowerks::mutex mut_;
#endif // _MSL_SHARED_PTR_HAS_MUTEX
    template <class U> friend class shared_ptr;
    template <class U> friend class weak_ptr;

    shared_ptr_deleter_common(const shared_ptr_deleter_common &);
    shared_ptr_deleter_common &operator=(const shared_ptr_deleter_common &);
};

// see msl_thread.cpp for shared_ptr_deleter_common source

#ifndef _MSL_SHARED_PTR_HAS_MUTEX

inline void shared_ptr_deleter_common::attach() { ++use_count_; }

inline void shared_ptr_deleter_common::attach_weak() { ++weak_count_; }

#elif defined(__POWERPC__)

inline void shared_ptr_deleter_common::attach() {
    register ptrdiff_t *const p = &use_count_;
    register ptrdiff_t a;
    asm
    {
	loop:
		lwarx    a, 0, p
		addi     a, a, 1
		stwcx.   a, 0, p
		bne-     loop
    }
}

inline void shared_ptr_deleter_common::attach_weak() {
    register ptrdiff_t *const p = &weak_count_;
    register ptrdiff_t a;
    asm
    {
	loop:
		lwarx    a, 0, p
		addi     a, a, 1
		stwcx.   a, 0, p
		bne-     loop
    }
}

#endif // _MSL_SHARED_PTR_HAS_MUTEX

template <class T, class D = typename std::detail::default_delete<T> >
class shared_ptr_deleter : public shared_ptr_deleter_common {
    typedef typename remove_bounds<T>::type element_type;
    typedef typename remove_const<element_type>::type non_const_type;

  public:
    explicit shared_ptr_deleter(element_type *ptr) : p_(ptr) {}
    shared_ptr_deleter(element_type *ptr, D &d) : p_(ptr, d) {}
#ifndef _MSL_NO_RTTI
    virtual const void *get_deleter(const type_info &t) const {
        return t == typeid(D) ? &p_.second() : 0;
    };
#endif // _MSL_NO_RTTI
    virtual void dispose() {
        p_.second()(const_cast<non_const_type *>(p_.first()));
    }

  private:
    Metrowerks::compressed_pair<element_type *, D> p_;
};

} // namespace detail

template <class T> class shared_ptr;
template <class T> class enable_shared_from_this;

template <class T, class U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U> &r);

template <class T, class U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U> &r);

template <class T, class U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U> &r);

template <class T, class U>
bool operator<(shared_ptr<T> const &a, shared_ptr<U> const &b);

template <class T, class U>
bool operator<(weak_ptr<T> const &a, weak_ptr<U> const &b);

template <class T> class shared_ptr {
  public:
    typedef T element_type;

    // constructors
    shared_ptr();
    template <class Y> explicit shared_ptr(Y *p);
#ifdef _MSL_MOVE
    template <class Y, class D> shared_ptr(Y *p, D &&d);
#else
    template <class Y, class D> shared_ptr(Y *p, D d);
#endif
    shared_ptr(const shared_ptr &r);
    template <class Y>
    shared_ptr(const shared_ptr<Y> &r,
               typename restrict_to<
                   is_convertible<Y *, element_type *>::value>::type * = 0);
    template <class Y>
    explicit shared_ptr(
        const weak_ptr<Y> &r,
        typename restrict_to<is_convertible<Y *, element_type *>::value>::type
            * = 0);
    template <class Y> explicit shared_ptr(auto_ptr<Y> &r);

    // destructor
    ~shared_ptr() _MSL_NO_THROW;

    // assignment
    shared_ptr &operator=(const shared_ptr &r);
    template <class Y> shared_ptr &operator=(const shared_ptr<Y> &r);
    template <class Y> shared_ptr &operator=(auto_ptr<Y> &r);

    // modifiers
    void swap(shared_ptr &r);
    void reset();
    template <class Y> void reset(Y *p);
    template <class Y, class D> void reset(Y *p, D d);

    // observers
    element_type *get() const { return ptr_; }
    typename add_reference<element_type>::type operator*() const {
        return *ptr_;
    }
    element_type *operator->() const { return ptr_; }
    long use_count() const {
        return static_cast<long>(s_ ? s_->use_count() : 0);
    }
    bool unique() const { return s_ && s_->use_count() == 1; }

  private:
    struct bool_type {
        int dummy_;
    };

  public:
    operator int bool_type::*() const { return ptr_ ? &bool_type::dummy_ : 0; }

    shared_ptr(int bool_type::*);
    shared_ptr &operator=(int bool_type::*);
#ifndef _MSL_NO_RTTI
    template <class D> D *get_deleter() const;
#endif
  private:
    element_type *ptr_;
    detail::shared_ptr_deleter_common *s_;

    template <class U> friend class shared_ptr;
    template <class U> friend class weak_ptr;
    template <class U, class V>
    friend bool operator<(shared_ptr<U> const &a, shared_ptr<V> const &b);
    template <class V, class U>
    friend shared_ptr<V> static_pointer_cast(const shared_ptr<U> &r);
    template <class V, class U>
    friend shared_ptr<V> const_pointer_cast(const shared_ptr<U> &r);
    template <class V, class U>
    friend shared_ptr<V> dynamic_pointer_cast(const shared_ptr<U> &r);

    shared_ptr(element_type *p, detail::shared_ptr_deleter_common *s);

    template <class Y, class U>
    void enable_from_this(const enable_shared_from_this<Y> *p, U *py);
    void enable_from_this(const void *, const void *) {}
};

template <class T> inline shared_ptr<T>::shared_ptr() : ptr_(0), s_(0) {}

template <class T>
inline shared_ptr<T>::shared_ptr(int bool_type::*) : ptr_(0), s_(0) {}

template <class T>
template <class Y, class U>
void shared_ptr<T>::enable_from_this(const enable_shared_from_this<Y> *p,
                                     U *py) {
    if (py)
        weak_ptr<Y>(const_cast<typename remove_const<U>::type *>(py), s_)
            .swap(const_cast<enable_shared_from_this<Y> *>(p)->__weak_this);
}

template <class T>
inline shared_ptr<T>::shared_ptr(element_type *p,
                                 detail::shared_ptr_deleter_common *s)
    : ptr_(p), s_(s) {
    s_->attach();
}

template <class T>
template <class Y>
shared_ptr<T>::shared_ptr(Y *p) : ptr_(p) {
    Metrowerks::move_ptr<Y> hold(p);
    s_ = new detail::shared_ptr_deleter<
        Y, typename std::detail::default_delete<Y> >(p);
    hold.release();
    enable_from_this(p, p);
}

#ifdef _MSL_MOVE

template <class T>
template <class Y, class D>
shared_ptr<T>::shared_ptr(Y *p, D &&d) : ptr_(p) {
    Metrowerks::move_ptr<Y, D &> hold(p, d);
    s_ = new detail::shared_ptr_deleter<Y, D>(p, d);
    hold.release();
    enable_from_this(p, p);
}

#else // _MSL_MOVE

template <class T>
template <class Y, class D>
shared_ptr<T>::shared_ptr(Y *p, D d) : ptr_(p) {
    Metrowerks::move_ptr<Y, D &> hold(p, d);
    s_ = new detail::shared_ptr_deleter<Y, D>(p, d);
    hold.release();
    enable_from_this(p, p);
}

#endif // _MSL_MOVE

template <class T>
inline shared_ptr<T>::shared_ptr(const shared_ptr &r) : ptr_(r.ptr_), s_(r.s_) {
    if (s_)
        s_->attach();
}

template <class T>
template <class Y>
inline shared_ptr<T>::shared_ptr(
    const shared_ptr<Y> &r,
    typename restrict_to<is_convertible<Y *, element_type *>::value>::type *)
    : ptr_(r.ptr_), s_(r.s_) {
    if (s_)
        s_->attach();
}

template <class T>
template <class Y>
shared_ptr<T>::shared_ptr(auto_ptr<Y> &r)
    : s_(new detail::shared_ptr_deleter<Y>(r.get())) {
    enable_from_this(r.get(), r.get());
    ptr_ = r.release();
}

template <class T> shared_ptr<T>::~shared_ptr() _MSL_NO_THROW {
    if (s_)
        s_->release();
}

template <class T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr &r) {
    shared_ptr(r).swap(*this);
    return *this;
}

template <class T> shared_ptr<T> &shared_ptr<T>::operator=(int bool_type::*) {
    reset();
    return *this;
}

template <class T>
template <class Y>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<Y> &r) {
    shared_ptr(r).swap(*this);
    return *this;
}

template <class T>
template <class Y>
shared_ptr<T> &shared_ptr<T>::operator=(auto_ptr<Y> &r) {
    shared_ptr(r).swap(*this);
    return *this;
}

template <class T> inline void shared_ptr<T>::swap(shared_ptr &r) {
    void *tmp = ptr_;
    ptr_ = r.ptr_;
    r.ptr_ = (element_type *)tmp;
    tmp = s_;
    s_ = r.s_;
    r.s_ = (detail::shared_ptr_deleter_common *)tmp;
}

template <class T> void shared_ptr<T>::reset() { shared_ptr().swap(*this); }

template <class T> template <class Y> void shared_ptr<T>::reset(Y *p) {
    shared_ptr(p).swap(*this);
}

template <class T>
template <class Y, class D>
void shared_ptr<T>::reset(Y *p, D d) {
    shared_ptr(p, d).swap(*this);
}

#ifndef _MSL_NO_RTTI

template <class T> template <class D> D *shared_ptr<T>::get_deleter() const {
    return (D *)(s_ ? s_->get_deleter(typeid(D)) : 0);
}

#endif // _MSL_NO_RTTI

template <class T> class shared_ptr<T[]> {
  public:
    typedef T element_type;

    // constructors
    shared_ptr();
    template <class Y>
    explicit shared_ptr(
        Y p,
        typename restrict_to<
            is_pointer<Y>::value &&
            is_same<typename remove_pointer<Y>::type, T>::value>::type * = 0);
    template <class D> shared_ptr(T *p, D d);
    shared_ptr(const shared_ptr &r);
    explicit shared_ptr(const weak_ptr<T[]> &r);

    // destructor
    ~shared_ptr();

    // assignment
    shared_ptr &operator=(const shared_ptr &r);

    // modifiers
    void swap(shared_ptr &r);
    void reset();
    void reset(T *p);
    template <class D> void reset(T *p, D d);

    // observers
    element_type *get() const { return ptr_; }
    typename add_reference<element_type>::type operator[](size_t i) const {
        return ptr_[i];
    }
    long use_count() const {
        return static_cast<long>(s_ ? s_->use_count() : 0);
    }
    bool unique() const { return s_ && s_->use_count() == 1; }

  private:
    struct bool_type {
        int dummy_;
    };

  public:
    operator int bool_type::*() const { return ptr_ ? &bool_type::dummy_ : 0; }

    shared_ptr(int bool_type::*);
    shared_ptr &operator=(int bool_type::*);

#ifndef _MSL_NO_RTTI
    template <class D> D *get_deleter() const;
#endif
  private:
    element_type *ptr_;
    detail::shared_ptr_deleter_common *s_;

    template <class U> friend class weak_ptr;
    template <class U, class V>
    friend bool operator<(shared_ptr<U> const &a, shared_ptr<V> const &b);
    template <class V, class U>
    friend shared_ptr<V> static_pointer_cast(const shared_ptr<U> &r);
    template <class V, class U>
    friend shared_ptr<V> const_pointer_cast(const shared_ptr<U> &r);
    template <class V, class U>
    friend shared_ptr<V> dynamic_pointer_cast(const shared_ptr<U> &r);

    shared_ptr(element_type *p, detail::shared_ptr_deleter_common *s);
};

template <class T> inline shared_ptr<T[]>::shared_ptr() : ptr_(0), s_(0) {}

template <class T>
inline shared_ptr<T[]>::shared_ptr(int bool_type::*) : ptr_(0), s_(0) {}

template <class T>
inline shared_ptr<T[]>::shared_ptr(element_type *p,
                                   detail::shared_ptr_deleter_common *s)
    : ptr_(p), s_(s) {
    s_->attach();
}

template <class T>
template <class Y>
shared_ptr<T[]>::shared_ptr(
    Y p, typename restrict_to<
             is_pointer<Y>::value &&
             is_same<typename remove_pointer<Y>::type, T>::value>::type *)
    : ptr_(p) {
    Metrowerks::move_ptr<T[]> hold(p);
    s_ = new detail::shared_ptr_deleter<T[]>(p);
    hold.release();
}

template <class T>
template <class D>
shared_ptr<T[]>::shared_ptr(T *p, D d) : ptr_(p) {
    Metrowerks::move_ptr<T[], D &> hold(p, d);
    s_ = new detail::shared_ptr_deleter<T[], D>(p, d);
    hold.release();
}

template <class T>
inline shared_ptr<T[]>::shared_ptr(const shared_ptr &r)
    : ptr_(r.ptr_), s_(r.s_) {
    if (s_)
        s_->attach();
}

template <class T> shared_ptr<T[]>::~shared_ptr() {
    if (s_)
        s_->release();
}

template <class T>
shared_ptr<T[]> &shared_ptr<T[]>::operator=(const shared_ptr &r) {
    shared_ptr(r).swap(*this);
    return *this;
}

template <class T>
shared_ptr<T[]> &shared_ptr<T[]>::operator=(int bool_type::*) {
    reset();
    return *this;
}

template <class T> inline void shared_ptr<T[]>::swap(shared_ptr &r) {
    void *tmp = ptr_;
    ptr_ = r.ptr_;
    r.ptr_ = (element_type *)tmp;
    tmp = s_;
    s_ = r.s_;
    r.s_ = (detail::shared_ptr_deleter_common *)tmp;
}

template <class T> void shared_ptr<T[]>::reset() { shared_ptr().swap(*this); }

template <class T> void shared_ptr<T[]>::reset(T *p) {
    shared_ptr(p).swap(*this);
}

template <class T> template <class D> void shared_ptr<T[]>::reset(T *p, D d) {
    shared_ptr(p, d).swap(*this);
}

#ifndef _MSL_NO_RTTI

template <class T> template <class D> D *shared_ptr<T[]>::get_deleter() const {
    return (D *)(s_ ? s_->get_deleter(typeid(D)) : 0);
}

#endif // _MSL_NO_RTTI

template <class T, class U>
inline bool operator==(const shared_ptr<T> &a, const shared_ptr<U> &b) {
    return a.get() == b.get();
}

template <class T, class U>
inline bool operator!=(const shared_ptr<T> &a, const shared_ptr<U> &b) {
    return a.get() != b.get();
}

template <class T, class U>
inline bool operator<(const shared_ptr<T> &a, const shared_ptr<U> &b) {
    return a.s_ < b.s_;
}

template <class T, class U>
inline bool operator>(const shared_ptr<T> &a, const shared_ptr<U> &b) {
    return b < a;
}

template <class T, class U>
inline bool operator>=(const shared_ptr<T> &a, const shared_ptr<U> &b) {
    return !(a < b);
}

template <class T, class U>
inline bool operator<=(const shared_ptr<T> &a, const shared_ptr<U> &b) {
    return !(b < a);
}

template <class T> inline void swap(shared_ptr<T> &a, shared_ptr<T> &b) {
    return a.swap(b);
}

template <class T, class U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U> &r) {
#if defined(__MWERKS__) && __MWERKS__ >= 0x4000
    __static_assert(!is_array<T>::value && !is_array<U>::value,
                    "static_pointer_cast converting array form of shared_ptr");
#endif
    return r.s_ ? shared_ptr<T>(
                      static_cast<typename shared_ptr<T>::element_type *>(
                          r.ptr_),
                      r.s_)
                : shared_ptr<T>();
}

template <class T, class U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U> &r) {
#if defined(__MWERKS__) && __MWERKS__ >= 0x4000
    __static_assert(is_array<T>::value == is_array<U>::value,
                    "const_pointer_cast converting incompatible shared_ptr's");
#endif
    return r.s_
               ? shared_ptr<T>(
                     const_cast<typename shared_ptr<T>::element_type *>(r.ptr_),
                     r.s_)
               : shared_ptr<T>();
}

#ifndef _MSL_NO_RTTI

template <class T, class U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U> &r) {
#if defined(__MWERKS__) && __MWERKS__ >= 0x4000
    __static_assert(!is_array<T>::value && !is_array<U>::value,
                    "dynamic_pointer_cast converting array form of shared_ptr");
#endif
    typename shared_ptr<T>::element_type *p =
        dynamic_cast<typename shared_ptr<T>::element_type *>(r.get());
    return p ? shared_ptr<T>(p, r.s_) : shared_ptr<T>();
}

#endif // _MSL_NO_RTTI

#ifndef _MSL_NO_IO

template <class E, class T, class Y>
inline basic_ostream<E, T> &operator<<(basic_ostream<E, T> &os,
                                       const shared_ptr<Y> &p) {
    return os << p.get();
}

#endif // _MSL_NO_IO

#ifndef _MSL_NO_RTTI

template <class D, class T> inline D *get_deleter(const shared_ptr<T> &p) {
    return p.template get_deleter<D>();
}

#endif // _MSL_NO_RTTI

namespace detail {

template <class T, class U> struct accept {
  private:
    static const bool is_T_array = is_array<T>::value;
    static const bool is_U_array = is_array<U>::value;

  public:
    static const bool value =
        is_T_array && is_U_array && is_same<T, U>::value ||
        !is_T_array && !is_U_array && is_convertible<U *, T *>::value;
};

} // namespace detail

template <class T> class weak_ptr {
  public:
    typedef typename remove_bounds<T>::type element_type;

    // constructors
    weak_ptr();
    weak_ptr(const weak_ptr &r);
    template <class Y>
    weak_ptr(const weak_ptr<Y> &r,
             typename restrict_to<detail::accept<T, Y>::value>::type * = 0);
    template <class Y>
    weak_ptr(const shared_ptr<Y> &r,
             typename restrict_to<detail::accept<T, Y>::value>::type * = 0);

    // destructor
    ~weak_ptr();

    // assignment
    weak_ptr &operator=(const weak_ptr &r);

    template <class Y>
    typename restrict_to<detail::accept<T, Y>::value, weak_ptr<T> &>::type
    operator=(const weak_ptr<Y> &r);

    template <class Y>
    typename restrict_to<detail::accept<T, Y>::value, weak_ptr &>::type
    operator=(const shared_ptr<Y> &r);

    // modifiers
    void swap(weak_ptr &r);
    void reset();

    // observers
    long use_count() const {
        return static_cast<long>(s_ ? s_->use_count() : 0);
    }
    bool expired() const { return !s_ || s_->use_count() == 0; }
    shared_ptr<T> lock() const;

  private:
    element_type *ptr_;
    detail::shared_ptr_deleter_common *s_;

    template <class U> friend class shared_ptr;
    template <class U> friend class weak_ptr;
    template <class U, class V>
    friend bool operator<(weak_ptr<U> const &a, weak_ptr<V> const &b);

    template <class Y> weak_ptr(Y *p, detail::shared_ptr_deleter_common *s);
};

template <class T> inline weak_ptr<T>::weak_ptr() : ptr_(0), s_(0) {}

template <class T>
inline weak_ptr<T>::weak_ptr(const weak_ptr &r) : ptr_(r.ptr_), s_(r.s_) {
    if (s_)
        s_->attach_weak();
}

template <class T>
template <class Y>
weak_ptr<T>::weak_ptr(const weak_ptr<Y> &r,
                      typename restrict_to<detail::accept<T, Y>::value>::type *)
    : ptr_(r.ptr_), s_(r.s_) {
    if (s_)
        s_->attach_weak();
}

template <class T>
template <class Y>
inline weak_ptr<T>::weak_ptr(
    const shared_ptr<Y> &r,
    typename restrict_to<detail::accept<T, Y>::value>::type *)
    : ptr_(r.ptr_), s_(r.s_) {
    if (s_)
        s_->attach_weak();
}

template <class T>
template <class Y>
inline weak_ptr<T>::weak_ptr(Y *p, detail::shared_ptr_deleter_common *s)
    : ptr_(p), s_(s) {
    s_->attach_weak();
}

template <class T> weak_ptr<T>::~weak_ptr() {
    if (s_)
        s_->release_weak();
}

template <class T> weak_ptr<T> &weak_ptr<T>::operator=(const weak_ptr &r) {
    weak_ptr(r).swap(*this);
    return *this;
}

template <class T>
template <class Y>
typename restrict_to<detail::accept<T, Y>::value, weak_ptr<T> &>::type
weak_ptr<T>::operator=(const weak_ptr<Y> &r) {
    weak_ptr(r).swap(*this);
    return *this;
}

template <class T>
template <class Y>
typename restrict_to<detail::accept<T, Y>::value, weak_ptr<T> &>::type
weak_ptr<T>::operator=(const shared_ptr<Y> &r) {
    weak_ptr(r).swap(*this);
    return *this;
}

template <class T> inline void weak_ptr<T>::swap(weak_ptr &r) {
    {
        element_type *tmp = ptr_;
        ptr_ = r.ptr_;
        r.ptr_ = (element_type *)tmp;
    }
    {
        detail::shared_ptr_deleter_common *tmp = s_;
        s_ = r.s_;
        r.s_ = (detail::shared_ptr_deleter_common *)tmp;
    }
}

template <class T> void weak_ptr<T>::reset() { weak_ptr().swap(*this); }

template <class T> shared_ptr<T> weak_ptr<T>::lock() const {
#ifdef _MSL_SHARED_PTR_HAS_MUTEX
    if (s_ == 0)
        return shared_ptr<T>();
    shared_ptr<T> r;
#ifndef __POWERPC__
    {
        Metrowerks::mutex::scoped_lock lock(s_->mut_);
        if (s_->use_count() != 0) {
            r.ptr_ = ptr_;
            r.s_ = s_;
            r.s_->attach(false);
        }
    }
#else  // __POWERPC__
    register ptrdiff_t *const p = &s_->use_count_;
    register ptrdiff_t a;
    asm
    {
	loop:
		lwarx    a, 0, p
    }
    if (a != 0) {
        asm
            {
			addi     a, a, 1
			stwcx.   a, 0, p
			bne-     loop
            }
        r.ptr_ = ptr_;
        r.s_ = s_;
    }
#endif // __POWERPC__
    return r;
#else // _MSL_SHARED_PTR_HAS_MUTEX
    return expired() ? shared_ptr<T>() : shared_ptr<T>(*this);
#endif
}

template <class T>
template <class Y>
shared_ptr<T>::shared_ptr(
    const weak_ptr<Y> &r,
    typename restrict_to<is_convertible<Y *, element_type *>::value>::type *)
    : ptr_(0), s_(0) {
    shared_ptr<T> p = r.lock();
    if (p.use_count() == 0)
#ifndef _MSL_NO_EXCEPTIONS
        throw bad_weak_ptr();
#else
        Metrowerks::__msl_error("bad_weak_ptr");
#endif
    swap(p);
}

template <class T>
shared_ptr<T[]>::shared_ptr(const weak_ptr<T[]> &r) : ptr_(0), s_(0) {
    shared_ptr<T[]> p = r.lock();
    if (p.use_count() == 0)
#ifndef _MSL_NO_EXCEPTIONS
        throw bad_weak_ptr();
#else
        Metrowerks::__msl_error("bad_weak_ptr");
#endif
    swap(p);
}

template <class T, class U>
inline bool operator<(const weak_ptr<T> &a, const weak_ptr<U> &b) {
    return a.s_ < b.s_;
}

template <class T, class U>
inline bool operator>(const weak_ptr<T> &a, const weak_ptr<U> &b) {
    return b < a;
}

template <class T, class U>
inline bool operator>=(const weak_ptr<T> &a, const weak_ptr<U> &b) {
    return !(a < b);
}

template <class T, class U>
inline bool operator<=(const weak_ptr<T> &a, const weak_ptr<U> &b) {
    return !(b < a);
}

template <class T> inline void swap(weak_ptr<T> &a, weak_ptr<T> &b) {
    a.swap(b);
}

template <class T> class enable_shared_from_this {
#if defined(__MWERKS__) && __MWERKS__ >= 0x4000
    __static_assert(!is_array<T>::value,
                    "enable_shared_from_this instantiated with array type");
#endif
  public:
    shared_ptr<T> shared_from_this() { return shared_ptr<T>(__weak_this); }
    shared_ptr<T const> shared_from_this() const {
        return shared_ptr<T const>(__weak_this);
    }

  protected:
    enable_shared_from_this() {}
    enable_shared_from_this(const enable_shared_from_this &) {}
    enable_shared_from_this &operator=(const enable_shared_from_this &) {
        return *this;
    }
    ~enable_shared_from_this() {}

  private:
    weak_ptr<T> __weak_this;

    template <class Y> friend class shared_ptr;
};

_MSL_END_TR1_NAMESPACE

#ifdef _MSL_FORCE_ENUMS_ALWAYS_INT
#pragma enumsalwaysint reset
#endif

#ifdef _MSL_FORCE_ENABLE_BOOL_SUPPORT
#pragma bool reset
#endif

#ifdef __MWERKS__
#pragma options align = reset
#endif

#endif // RC_INVOKED

#endif // _MSL_SMART_POINTERS

// hh 030624 Created
// hh 030417 Added move_ptr and shared_ptr
// hh 030527 Made move_ptr pseudo movable
// hh 030711 Removed reference to reference bug in move_ptr::get_deleter
// hh 030711 Added no-throw spec to shared_ptr_deleter_common::release() and
// ~shared_ptr() hh 030711 Hid __option(RTTI) behind macro for portability hh
// 030711 Corrected template signature in friend statements of shared_ptr hh
// 031001 Fixed return type of shared_ptr::operator*() hh 040111 Restricted
// shared_ptr and weak_ptr constructors to convertible types per Rani Sharoni
// suggestion on boost.
