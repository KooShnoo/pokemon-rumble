#ifndef _METROWERKS_TYPE_TRAITS_CALL_TRAITS
#define _METROWERKS_TYPE_TRAITS_CALL_TRAITS

#include "MSL_C++/msl_utility"

namespace Metrowerks {

    namespace details {
    template <class T, bool PassByValue, bool IsReference, bool IsArray>
    struct ct_imp {
        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef const_reference param_type;
    };

    template <class T> struct ct_imp<T, true, false, false> {
        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef T const param_type;
    };

    template <class T> struct ct_imp<T, false, true, false> {
        typedef typename remove_reference<T>::type value_type;
        typedef T reference;
        typedef const T const_reference;
        typedef reference param_type;
    };

    template <class T> struct ct_imp<T, false, false, true> {
        typedef typename remove_bounds<T>::type const *value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef const value_type param_type;
};
} // namespace details

template <class T> struct call_traits {
    private:
        static const bool PassByValue = Metrowerks::has_trivial_copy_ctor<T>::value &&
                                        sizeof(T) <= sizeof(void *) &&
                                        !is_array<T>::value ||
                                    is_arithmetic<T>::value;
        static const bool IsReference = is_reference<T>::value;
        static const bool IsArray = is_array<T>::value;
        typedef typename details::ct_imp<T, PassByValue, IsReference, IsArray> imp;

    public:
        typedef typename imp::value_type value_type;
        typedef typename imp::reference reference;
        typedef typename imp::const_reference const_reference;
        typedef typename imp::param_type param_type;
};

}

#endif
