/* MSL
 * Copyright (c) 1995-2006 Freescale Corporation.  All rights reserved.
 *
 * $Date: 2006/02/09 16:59:38 $
 * $Revision: 1.1.2.5 $
 */

// Adapted for interoperation with reverse-engineered headers.

// type_traits

#ifndef  _TYPE_TRAITS
#define  _TYPE_TRAITS

/*  type_traits

namespace std
{
namespace tr1
{

// [4.3] helper class:
template <class T, T v> struct integral_constant;
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

// [4.5.1] primary type categories:
template <class T> struct is_void;
template <class T> struct is_integral;
template <class T> struct is_floating_point;
template <class T> struct is_array;
template <class T> struct is_pointer;
template <class T> struct is_reference;
template <class T> struct is_member_object_pointer;
template <class T> struct is_member_function_pointer;
template <class T> struct is_enum;
template <class T> struct is_union;
template <class T> struct is_class;
template <class T> struct is_function;

// [4.5.2] composite type categories:
template <class T> struct is_arithmetic;
template <class T> struct is_fundamental;
template <class T> struct is_object;
template <class T> struct is_scalar;
template <class T> struct is_compound;
template <class T> struct is_member_pointer;

// [4.5.3] type properties:
template <class T> struct is_const;
template <class T> struct is_volatile;
template <class T> struct is_pod;
template <class T> struct is_empty;
template <class T> struct is_polymorphic;
template <class T> struct is_abstract;
template <class T> struct has_trivial_constructor;
template <class T> struct has_trivial_copy;
template <class T> struct has_trivial_assign;
template <class T> struct has_trivial_destructor;
template <class T> struct has_nothrow_constructor;
template <class T> struct has_nothrow_copy;
template <class T> struct has_nothrow_assign;
template <class T> struct has_virtual_destructor;
template <class T> struct is_signed;
template <class T> struct is_unsigned;
template <class T> struct alignment_of;
template <class T> struct rank;
template <class T, unsigned I = 0> struct extent;

// [4.6] type relations:
template <class T, class U> struct is_same;
template <class Base, class Derived> struct is_base_of;
template <class From, class To> struct is_convertible;

// [4.7.1] const-volatile modifications:
template <class T> struct remove_const;
template <class T> struct remove_volatile;
template <class T> struct remove_cv;
template <class T> struct add_const;
template <class T> struct add_volatile;
template <class T> struct add_cv;

// [4.7.2] reference modifications:
template <class T> struct remove_reference;
template <class T> struct add_reference;

// [4.7.3] array modifications:
template <class T> struct remove_extent;
template <class T> struct remove_all_extents;

// [4.7.4] pointer modifications:
template <class T> struct remove_pointer;
template <class T> struct add_pointer;

// [4.8] other transformations:
template <std::size_t Len, std::size_t Align> struct aligned_storage;

}  // tr1
}  // std
*/

// #include <mslconfig>
#include <cstddef>

#ifndef RC_INVOKED

#ifdef __MWERKS__
#pragma options align=native
#endif

#ifdef _MSL_FORCE_ENUMS_ALWAYS_INT
	#if _MSL_FORCE_ENUMS_ALWAYS_INT
		#pragma enumsalwaysint on
	#else
		#pragma enumsalwaysint off
	#endif
#endif  // _MSL_FORCE_ENUMS_ALWAYS_INT

#ifdef _MSL_FORCE_ENABLE_BOOL_SUPPORT
	#if _MSL_FORCE_ENABLE_BOOL_SUPPORT
		#pragma bool on
	#else
		#pragma bool off
	#endif
#endif  // _MSL_FORCE_ENABLE_BOOL_SUPPORT

// _MSL_START_TR1_NAMESPACE

// integral_constant

template <class T, T v>
struct integral_constant
{
	static const T                  value = v;
	typedef T                       value_type;
	typedef integral_constant<T, v> type;
};

typedef integral_constant<bool, true>  true_type;
typedef integral_constant<bool, false> false_type;

namespace detail
{
	struct two {char x; char y;};
}

// is_convertible

namespace detail
{

template <class From, class To>
struct is_convertible
{
private:
	static From f;

#ifdef _MSL_MOVE
	template <class U> static char test(U&&);
#else
	template <class U> static char test(const U&);
#endif
	template <class U> static detail::two test(...);
public:
#ifdef _MSL_MOVE
	static const bool value = sizeof(test<To>(static_cast<From&&>(f))) == 1;
#else
	static const bool value = sizeof(test<To>(f)) == 1;
#endif
};

template <class To>   struct is_convertible<void, To>   {static const bool value = false;};
template <class From> struct is_convertible<From, void> {static const bool value = true;};
template <>           struct is_convertible<void, void> {static const bool value = true;};

}  // detail

template <class From, class To>
struct is_convertible
	: public integral_constant<bool, detail::is_convertible<From, To>::value>
{};


// remove_const

template <class T> struct remove_const          {typedef T type;};
template <class T> struct remove_const<T const> {typedef T type;};

// remove_volatile

template <class T> struct remove_volatile             {typedef T type;};
template <class T> struct remove_volatile<T volatile> {typedef T type;};

// remove_cv

template <class T> struct remove_cv
	{typedef typename remove_const<typename remove_volatile<T>::type>::type type;};

// is_void

namespace detail
{

template <class T> struct is_void : public integral_constant<bool, false> {};
template <> struct is_void<void> : public integral_constant<bool, true> {};

} // detail

template <class T> struct is_void
	: public integral_constant
	         <bool,
	         detail::is_void<typename remove_cv<T>::type>::value>
{};

// is_integral;

namespace detail
{

template <class T> struct is_integral : public integral_constant<bool, false> {};

#ifndef _MSL_NO_BOOL
template <> struct is_integral<bool> : public integral_constant<bool, true> {};
#endif

template <> struct is_integral<char>          : public integral_constant<bool, true> {};
template <> struct is_integral<signed char>   : public integral_constant<bool, true> {};
template <> struct is_integral<unsigned char> : public integral_constant<bool, true> {};

#if !defined(_MSL_NO_WCHART_LANG_SUPPORT) && !defined(_MSL_NO_WCHART_CPP_SUPPORT)
template <> struct is_integral<wchar_t> : public integral_constant<bool, true> {};
#endif

template <> struct is_integral<short>          : public integral_constant<bool, true> {};
template <> struct is_integral<unsigned short> : public integral_constant<bool, true> {};

template <> struct is_integral<int>          : public integral_constant<bool, true> {};
template <> struct is_integral<unsigned int> : public integral_constant<bool, true> {};

template <> struct is_integral<long>          : public integral_constant<bool, true> {};
template <> struct is_integral<unsigned long> : public integral_constant<bool, true> {};

#if _MSL_LONGLONG
template <> struct is_integral<long long>          : public integral_constant<bool, true> {};
template <> struct is_integral<unsigned long long> : public integral_constant<bool, true> {};
#endif  // _MSL_LONGLONG

} // detail

template <class T> struct is_integral
	: public integral_constant
	         <bool,
	         detail::is_integral<typename remove_cv<T>::type>::value>
{};

// is_floating_point

namespace detail
{

template <class T> struct is_floating_point : public integral_constant<bool, false> {};

template <> struct is_floating_point<float>       : public integral_constant<bool, true> {};
template <> struct is_floating_point<double>      : public integral_constant<bool, true> {};
template <> struct is_floating_point<long double> : public integral_constant<bool, true> {};

} // detail

template <class T> struct is_floating_point
	: public integral_constant
	         <bool,
	         detail::is_floating_point<typename remove_cv<T>::type>::value>
{};

// is_array

template <class T> struct is_array                 : public integral_constant<bool, false> {};
template <class T> struct is_array<T[]>            : public integral_constant<bool, true> {};
template <class T, size_t N> struct is_array<T[N]> : public integral_constant<bool, true> {};

// is_pointer

namespace detail
{

template <class T> struct is_pointer     : public integral_constant<bool, false> {};
template <class T> struct is_pointer<T*> : public integral_constant<bool, true> {};

} // detail

template <class T> struct is_pointer
	: public integral_constant
	         <bool,
	         detail::is_pointer<typename remove_cv<T>::type>::value>
{};

// is_reference

template <class T> struct is_reference     : public integral_constant<bool, false> {};
template <class T> struct is_reference<T&> : public integral_constant<bool, true> {};

#ifdef _MSL_MOVE

template <class T> struct is_reference<T&&> : public integral_constant<bool, true> {};

template <class T> struct is_lvalue_reference     : public integral_constant<bool, false> {};
template <class T> struct is_lvalue_reference<T&> : public integral_constant<bool, true> {};

template <class T> struct is_rvalue_reference      : public integral_constant<bool, false> {};
template <class T> struct is_rvalue_reference<T&&> : public integral_constant<bool, true> {};

#endif  // _MSL_MOVE


template <bool b, class T = void> struct restrict_to          {};
template <class T>                struct restrict_to<true, T> {typedef T type;};

// remove_bounds

template <class T>                  struct remove_bounds       {typedef T type;};
// template <class T, _CSTD::size_t N> struct remove_bounds<T[N]> {typedef T type;};
template <class T>                  struct remove_bounds<T[]>  {typedef T type;};
// is_member_function_pointer

#ifdef __MWERKS__

template <class T> struct is_member_function_pointer 
: public integral_constant<bool, ((__builtin_type(T) & 0xF000) == 0x4000) &&
	                              (__builtin_classify_type(T) == 12)> {};

#else  // __MWERKS__


namespace detail
{

template <class T> struct is_member_function_pointer : public integral_constant<bool, false> {};

template <class R, class T> struct is_member_function_pointer<R (T::*)()>
	: public integral_constant<bool, true> {};
template <class R, class T> struct is_member_function_pointer<R (T::*)() const>
	: public integral_constant<bool, true> {};
template <class R, class T> struct is_member_function_pointer<R (T::*)() volatile>
	: public integral_constant<bool, true> {};
template <class R, class T> struct is_member_function_pointer<R (T::*)() const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0> struct is_member_function_pointer<R (T::*)(A0)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0> struct is_member_function_pointer<R (T::*)(A0) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0> struct is_member_function_pointer<R (T::*)(A0) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0> struct is_member_function_pointer<R (T::*)(A0) const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0, class A1>
	struct is_member_function_pointer<R (T::*)(A0, A1)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1>
	struct is_member_function_pointer<R (T::*)(A0, A1) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1>
	struct is_member_function_pointer<R (T::*)(A0, A1) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1>
	struct is_member_function_pointer<R (T::*)(A0, A1) const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0, class A1, class A2>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2) const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0, class A1, class A2, class A3>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3) const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0, class A1, class A2, class A3, class A4>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4) const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5) const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6) const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7) const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7, class A8>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7, A8)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7, class A8>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7, A8) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7, class A8>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7, A8) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7, class A8>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7, A8) const volatile>
	: public integral_constant<bool, true> {};

template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7, class A8, class A9>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7, A8, A9)>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7, class A8, class A9>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7, A8, A9) const>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7, class A8, class A9>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7, A8, A9) volatile>
	: public integral_constant<bool, true> {};
template <class R, class T, class A0, class A1, class A2, class A3, class A4,
                            class A5, class A6, class A7, class A8, class A9>
	struct is_member_function_pointer<R (T::*)(A0, A1, A2, A3, A4,
	                                           A5, A6, A7, A8, A9) const volatile>
	: public integral_constant<bool, true> {};

}  // detail

template <class T> struct is_member_function_pointer
	: public integral_constant
	         <bool,
	         detail::is_member_function_pointer<typename remove_cv<T>::type>::value>
{};

#endif  // __MWERKS__

// is_member_pointer

namespace detail
{

template <class T> struct is_member_pointer                  : public integral_constant<bool, false> {};
template <class T, class U> struct is_member_pointer<U T::*> : public integral_constant<bool, true> {};

}  // detail

template <class T> struct is_member_pointer
	: public integral_constant
	         <bool,
	         detail::is_member_pointer<typename remove_cv<T>::type>::value>
{};

// is_member_object_pointer

template <class T> struct is_member_object_pointer
	: public integral_constant
		<
			bool,
			is_member_pointer<T>::value &&
			!is_member_function_pointer<T>::value
		> {};

// is_union

#ifdef __MWERKS__

template <class T> struct is_union : public integral_constant<bool, __builtin_type(T) == 0x2001> {};

#else  // __MWERKS__

namespace detail
{

template <class T> struct is_union : public integral_constant<bool, false> {};  // hook

}  // detail

template <class T>
struct is_union
	: public integral_constant<bool, detail::is_union<typename remove_cv<T>::type>::value>
{};

#endif  // __MWERKS__

// is_class

#ifdef __MWERKS__

template <class T>
struct is_class
	: public integral_constant<bool, !is_reference<T>::value && __builtin_type(T) == 0x2000>
{};

#else  // __MWERKS__

namespace detail
{

template <class T>
struct is_class
{
	template <class U> static char test(void (U::*)());
	template <class U> static detail::two test(...);

	static const bool value = sizeof(test<T>(0)) == 1 && !is_union<T>::value;
};

}  // detail

template <class T>
struct is_class
	: public integral_constant<bool, detail::is_class<typename remove_cv<T>::type>::value>
{};

#endif  // __MWERKS__

// is_function

#ifdef __MWERKS__

template <class T> struct is_function : public integral_constant<bool, __builtin_type(T) == 0x8000> {};

#else  // __MWERKS__

template <class T> struct is_function : public integral_constant<bool, false> {};
	
template <class R> struct is_function<R ()> : public integral_constant<bool, true> {};
template <class R, class A0> struct is_function<R (A0)> : public integral_constant<bool, true> {};
template <class R, class A0, class A1> struct is_function<R (A0, A1)>
	: public integral_constant<bool, true> {};
template <class R, class A0, class A1, class A2> struct is_function<R (A0, A1, A2)>
	: public integral_constant<bool, true> {};
template <class R, class A0, class A1, class A2, class A3> struct is_function<R (A0, A1, A2, A3)>
	: public integral_constant<bool, true> {};
template <class R, class A0, class A1, class A2, class A3, class A4>
struct is_function<R (A0, A1, A2, A3, A4)>
	: public integral_constant<bool, true> {};
template <class R, class A0, class A1, class A2, class A3, class A4,
                   class A5>
struct is_function<R (A0, A1, A2, A3, A4, A5)>
	: public integral_constant<bool, true> {};
template <class R, class A0, class A1, class A2, class A3, class A4,
                   class A5, class A6>
struct is_function<R (A0, A1, A2, A3, A4, A5, A6)>
	: public integral_constant<bool, true> {};
template <class R, class A0, class A1, class A2, class A3, class A4,
                   class A5, class A6, class A7>
struct is_function<R (A0, A1, A2, A3, A4, A5, A6, A7)>
	: public integral_constant<bool, true> {};
template <class R, class A0, class A1, class A2, class A3, class A4,
                   class A5, class A6, class A7, class A8>
struct is_function<R (A0, A1, A2, A3, A4, A5, A6, A7, A8)>
	: public integral_constant<bool, true> {};
template <class R, class A0, class A1, class A2, class A3, class A4,
                   class A5, class A6, class A7, class A8, class A9>
struct is_function<R (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9)>
	: public integral_constant<bool, true> {};

#endif  // __MWERKS__

// is_enum

#ifdef __MWERKS__

template <class T>
struct is_enum
	: public integral_constant<bool, (__builtin_type(T) & 0xff00) == 0x0400>
{};

#else  // __MWERKS__

namespace detail
{

template <class T>
struct is_enum
{
	static const bool value = !is_integral<T>::value &&
	                          !is_floating_point<T>::value &&
	                          !is_reference<T>::value &&
	                          !is_class<T>::value &&
	                          !is_union<T>::value &&
	                          !is_function<T>::value &&
	                          is_convertible<T, int>::value;
};

}  // detail

template <class T>
struct is_enum
	: public integral_constant<bool, detail::is_enum<typename remove_cv<T>::type>::value>
{};

#endif  // __MWERKS__

// is_arithmetic

template <class T>
struct is_arithmetic
	: public integral_constant<bool, is_integral<T>::value || is_floating_point<T>::value>
{};

// is_fundamental

template <class T>
struct is_fundamental
	: public integral_constant<bool, is_arithmetic<T>::value || is_void<T>::value>
{};

// is_scalar

template <class T>
struct is_scalar
	: public integral_constant<bool, is_arithmetic<T>::value     ||
	                                 is_member_pointer<T>::value ||
	                                 is_pointer<T>::value        ||
	                                 is_enum<T>::value           >
	                                 
{};

// is_object

template <class T>
struct is_object
	: public integral_constant<bool, !(is_void<T>::value      ||
	                                   is_reference<T>::value ||
	                                   is_function<T>::value  )>
	                                 
{};

// is_compound

template <class T>
struct is_compound
	: public integral_constant<bool, !is_fundamental<T>::value>
	                                 
{};

// is_const

template <class T> struct is_const          : public integral_constant<bool, false> {};
template <class T> struct is_const<T const> : public integral_constant<bool, true> {};

// add_const

namespace detail
{

template <class T, bool add = !(is_reference<T>::value ||
                                is_function<T>::value  ||
                                is_const<T>::value     )>
struct add_const
{
	typedef T const type;
};

template <class T>
struct add_const<T, false>
{
	typedef T type;
};

}  // detail

template <class T>
struct add_const
{
	typedef typename detail::add_const<T>::type type;
};

// is_volatile

template <class T> struct is_volatile             : public integral_constant<bool, false> {};
template <class T> struct is_volatile<T volatile> : public integral_constant<bool, true> {};

// add_volatile

namespace detail
{

template <class T, bool add = !(is_reference<T>::value ||
                                is_function<T>::value  ||
                                is_volatile<T>::value  )>
struct add_volatile
{
	typedef T volatile type;
};

template <class T>
struct add_volatile<T, false>
{
	typedef T type;
};

}  // detail

template <class T>
struct add_volatile
{
	typedef typename detail::add_volatile<T>::type type;
};

// add_cv

template <class T>
struct add_cv
{
	typedef typename add_const<typename add_volatile<T>::type>::type type;
};

// remove_reference

template <class T> struct remove_reference     {typedef T type;};
template <class T> struct remove_reference<T&> {typedef T type;};
#ifdef _MSL_MOVE
template <class T> struct remove_reference<T&&> {typedef T type;};
#endif

// add_reference

template <class T> struct add_reference     {typedef T& type;};
template <class T> struct add_reference<T&> {typedef T& type;};
#ifdef _MSL_MOVE
template <class T> struct add_reference<T&&> {typedef T&& type;};
#endif
template <>        struct add_reference<void>                {typedef void type;};
template <>        struct add_reference<const void>          {typedef void type;};
template <>        struct add_reference<volatile void>       {typedef void type;};
template <>        struct add_reference<const volatile void> {typedef void type;};

// remove_extent

template <class T>           struct remove_extent       {typedef T type;};
template <class T, size_t N> struct remove_extent<T[N]> {typedef T type;};
template <class T>           struct remove_extent<T[]>  {typedef T type;};

// remove_all_extents

template <class T>           struct remove_all_extents       {typedef T type;};
template <class T, size_t N> struct remove_all_extents<T[N]>
	{typedef typename remove_all_extents<T>::type type;};
template <class T>                  struct remove_all_extents<T[]>
	{typedef typename remove_all_extents<T>::type type;};

// rank

template <class T> struct rank : public integral_constant<unsigned, 0> {};

template <class T> struct rank<T[]>
	: public integral_constant<unsigned, rank<T>::value + 1> {};

template <class T, size_t N> struct rank<T[N]>
	: public integral_constant<unsigned, rank<T>::value + 1> {};

// extent

template <class T, unsigned I = 0>       struct extent          : public integral_constant<size_t, 0> {};
template <class T>                       struct extent<T, 0>    : public integral_constant<size_t, 0> {};
template <class T>                       struct extent<T[], 0>  : public integral_constant<size_t, 0> {};
template <class T, unsigned I>           struct extent<T[], I>  : public integral_constant<size_t, extent<T, I-1>::value> {};
template <class T, size_t N>             struct extent<T[N], 0> : public integral_constant<size_t, N> {};
template <class T, size_t N, unsigned I> struct extent<T[N], I> : public integral_constant<size_t, extent<T, I-1>::value> {};

// is_signed

namespace detail
{

template <class T, bool integral = is_integral<T>::value>
struct is_signed
{
	static const bool value = T(-1) < T(0);
};

template <class T>
struct is_signed<T, false>
{
	static const bool value = false;
};

}  // detail

template <class T> struct is_signed : public integral_constant<bool, detail::is_signed<T>::value> {};

// is_unsigned

namespace detail
{

template <class T, bool integral = is_integral<T>::value>
struct is_unsigned
{
	static const bool value = !(T(-1) < T(0));
};

template <class T>
struct is_unsigned<T, false>
{
	static const bool value = false;
};

}  // detail

template <class T> struct is_unsigned : public integral_constant<bool, detail::is_unsigned<T>::value> {};

// remove_pointer

template <class T> struct remove_pointer                   {typedef T type;};
template <class T> struct remove_pointer<T*>               {typedef T type;};
template <class T> struct remove_pointer<T*const>          {typedef T type;};
template <class T> struct remove_pointer<T*volatile>       {typedef T type;};
template <class T> struct remove_pointer<T*const volatile> {typedef T type;};

// add_pointer

template <class T> struct add_pointer {typedef typename remove_reference<T>::type* type;};

// is_same

template <class T, class U> struct is_same : public integral_constant<bool, false> {};
template <class T> struct is_same<T, T>    : public integral_constant<bool, true> {};

// is_base_of

template <class Base, class Derived>
struct is_base_of
	: public integral_constant<bool,
		is_same<Base, Derived>::value ||
		(
		is_class<Base>::value &&
		is_class<Derived>::value &&
		is_convertible<
			typename add_pointer<Derived>::type,
			typename add_pointer<Base>::type
		>::value
		)>
{};

// has_trivial_copy

#ifdef __MWERKS__

template <class T> struct has_trivial_copy
	: public integral_constant<bool,
		is_reference<T>::value || bool(__builtin_trivial_members(T) & 0x4)> {};

#else  // __MWERKS__

template <class T> struct has_trivial_copy
	: public integral_constant<bool,
		is_scalar<T>::value   ||
		is_union<T>::value    ||
		is_reference<T>::value
	> {};

#endif  // __MWERKS__

// has_trivial_assign

#ifdef __MWERKS__

template <class T> struct has_trivial_assign
	: public integral_constant<bool, 
		!is_const<T>::value && !is_reference<T>::value && bool(__builtin_trivial_members(T) & 0x2)> {};

#else  // __MWERKS__

template <class T> struct has_trivial_assign
	: public integral_constant<bool,
		!is_const<T>::value &&
		!is_reference<T>::value &&
		(
		is_scalar<T>::value ||
		is_union<T>::value
		)
	> {};

#endif  // __MWERKS__

// has_trivial_destructor

#ifdef __MWERKS__

template <class T> struct has_trivial_destructor
	: public integral_constant<bool,
		is_reference<T>::value || bool(__builtin_trivial_members(T) & 0x1)
	>
{};

#else  // __MWERKS__

namespace detail
{

template <class T>
struct has_trivial_destructor
{
	static const bool value = is_scalar<T>::value
	                       || is_union<T>::value
	                       || is_reference<T>::value;
};

}  // detail

template <class T> struct has_trivial_destructor
	: public integral_constant<bool,
		detail::has_trivial_destructor<typename remove_all_extents<T>::type>::value
	>
{};

#endif  // __MWERKS__

// has_trivial_constructor

#if defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T> struct has_trivial_constructor
	: public integral_constant<bool,
		is_object<T>::value && bool(__builtin_trivial_members(T) & 0x8)
	>
{};

#else  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

namespace detail
{

template <class T>
struct has_trivial_constructor
{
	static const bool value = is_scalar<T>::value || is_union<T>::value;
};

}  // detail

template <class T>
struct has_trivial_constructor
	: public integral_constant<bool,
		detail::has_trivial_constructor<typename remove_all_extents<T>::type>::value
	>
{};

#endif  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

// is_pod

#if defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T>
struct is_pod 
	: public integral_constant<bool, is_object<T>::value && __builtin_is_pod(T)>
{};

#else  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T>
struct is_pod 
	: public integral_constant<bool,
		has_trivial_constructor<T>::value &&
		has_trivial_copy<T>::value        &&
		has_trivial_assign<T>::value      &&
		has_trivial_destructor<T>::value
	>
{};

#endif  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

// is_empty

namespace detail
{

template <class T, bool b = is_class<T>::value>
struct is_empty1
	: T
{
	double d_;
};

template <class T>
struct is_empty1<T, false>
{
	T t_;
	double d_;
};

template <class T>
struct is_empty2
{
	double d_;
};

}  // detail

template <class T> struct is_empty
	: public integral_constant<bool,
		sizeof(detail::is_empty1<T>) == sizeof(detail::is_empty2<T>) &&
		has_trivial_assign<T>::value
	>
{};

// is_polymorphic

#if defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T>
struct is_polymorphic 
	: public integral_constant<bool, is_class<T>::value && __builtin_is_polymorphic(T)>
{};

#else  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

namespace detail
{

template <class T>
struct is_polymorphic_test1
	: T
{
};

template <class T>
struct is_polymorphic_test2
	: T
{
	virtual ~is_polymorphic_test2();
};

template <class T, bool b = is_class<T>::value>
struct is_polymorphic
{
	static const bool value = sizeof(is_polymorphic_test1<T>) == sizeof(is_polymorphic_test2<T>);
};

template <class T>
struct is_polymorphic<T, false>
{
	static const bool value = false;
};

}  // detail

template <class T> struct is_polymorphic : public integral_constant<bool, detail::is_polymorphic<T>::value> {};

#endif  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

// is_abstract

#if defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T>
struct is_abstract 
	: public integral_constant<bool, is_class<T>::value && __builtin_is_abstract(T)>
{};

#else  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

namespace detail
{

template <class T>
struct is_abstract
{
private:
    template <class U> static detail::two test(U (*)[1]);
    template <class U> static char test(...);
public:
    static const bool value = sizeof(test<T>(0)) == 1;
};

}  // detail

template <class T> struct is_abstract : public integral_constant<bool, detail::is_abstract<T>::value> {};

#endif  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

// has_nothrow_constructor

#if defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T> struct has_nothrow_constructor
	: public integral_constant<bool,
		is_object<T>::value && __builtin_has_nothrow_default_constructor(T)> {};

#else  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T> struct has_nothrow_constructor
	: public integral_constant<bool, has_trivial_constructor<T>::value> {};

#endif  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

// has_nothrow_copy

#if defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T> struct has_nothrow_copy
	: public integral_constant<bool,
		is_reference<T>::value || __builtin_has_nothrow_copy(T)> {};

#else  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T> struct has_nothrow_copy
	: public integral_constant<bool, has_trivial_copy<T>::value> {};

#endif  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

// has_nothrow_assign

#if defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T> struct has_nothrow_assign
	: public integral_constant<bool,
		!is_const<T>::value && !is_reference<T>::value &&  __builtin_has_nothrow_assign(T)> {};

#else  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T> struct has_nothrow_assign
	: public integral_constant<bool, has_trivial_assign<T>::value> {};

#endif  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

// has_virtual_destructor

#if defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T> struct has_virtual_destructor
	: public integral_constant<bool, __builtin_has_virtual_destructor(T)> {};

#else  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

template <class T> struct has_virtual_destructor
	: public integral_constant<bool, false> {};

#endif  // defined(__MWERKS__) && __MWERKS__ >= 0x4010

// alignment_of

#ifdef __MWERKS__

namespace detail
{

template <class T, bool b = is_reference<T>::value>
struct alignment_of
	: public integral_constant<size_t, __builtin_align(typename remove_reference<T>::type*)> {};

template <class T>
struct alignment_of<T, false>
	: public integral_constant<size_t, __builtin_align(T)> {};

}  // detail

template <class T> struct alignment_of
	: public integral_constant<size_t, detail::alignment_of<T>::value> {};

#else  // __MWERKS__

#ifdef DECOMP_IDE_FLAG

// dummy implementation for IDE error suppression
template <class T>
struct alignment_of {
	static const std::size_t value = 0;
};

#else
#error "Unsupported compiler."
#endif // DECOMP_IDE_FLAG

#endif  // __MWERKS__

// aligned_storage

namespace detail
{

template <bool b, class T1, class T2>
struct select
{
	typedef T1 type;
};

template <class T1, class T2>
struct select<false, T1, T2>
{
	typedef T2 type;
};

template <class H, class T>
struct type_list
{
	typedef H head;
	typedef T tail;
};

struct nat {};


template <class T>
struct align_type
{
	static const size_t value = alignment_of<T>::value;
	typedef T type;
};

struct align_8
{
	double d;
};

typedef
	type_list<align_type<unsigned char>,
	type_list<align_type<unsigned short>,
	type_list<align_type<unsigned int>,
	type_list<align_type<unsigned long>,
#if _MSL_LONGLONG
	type_list<align_type<unsigned long long>,
#endif
	type_list<align_type<double>,
	type_list<align_type<align_8>,
#ifdef __VEC__
	type_list<align_type<vector unsigned int>,
#endif
	nat
#ifdef __VEC__
	>
#endif
	> >
#if _MSL_LONGLONG
	>
#endif
	> > > >
	all_aligning_types;

template <class TL, size_t Align>
struct find_pod
{
	typedef void type;
};

template <class H, class T, size_t Align>
struct find_pod<type_list<H, T>, Align>
{
	typedef typename select<
		Align == H::value,
		typename H::type,
		typename find_pod<T, Align>::type
	>::type type;
};

template <class H, size_t Align>
struct find_pod<type_list<H, nat>, Align>
{
	typedef typename select<
		Align == H::value,
		typename H::type,
		void
	>::type type;
};

template <class TL>
struct find_max_pod;

template <class H, class T>
struct find_max_pod<type_list<H, T> >
{
private:
	typedef typename find_max_pod<T>::type tmax;
public:
	typedef typename select<
		tmax::value < H::value,
		H,
		tmax
	>::type type;
};

template <class H>
struct find_max_pod<type_list<H, nat> >
{
	typedef H type;
};

}  // detail

template <size_t Len, size_t Align = detail::find_max_pod<detail::all_aligning_types>::type::value>
struct aligned_storage
{
	union type
	{
		unsigned char __data[Len];
		typedef typename detail::find_pod<detail::all_aligning_types, Align>::type __align_type;
		// __static_assert(!is_same<__align_type, void>::value, "Alignment not supported for this value");
		__align_type __align;
	}; 
};

// _MSL_END_TR1_NAMESPACE

#ifdef _MSL_FORCE_ENUMS_ALWAYS_INT
	#pragma enumsalwaysint reset
#endif

#ifdef _MSL_FORCE_ENABLE_BOOL_SUPPORT
	#pragma bool reset
#endif

#ifdef __MWERKS__
#pragma options align=reset
#endif

#endif // RC_INVOKED

#endif // _TYPE_TRAITS

// hh 050714 Created
