// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/adapter/single.inl                                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_ADAPTER_SINGLE_INL)

#define HUGH_FIELD_ADAPTER_SINGLE_INL

// includes, system

//#include <>

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>
#if defined(HUGH_USE_TRACE) || defined(HUGH_ALL_TRACE)
#  include <typeinfo>
#  include <hugh/support/type_info.hpp>
#endif

namespace hugh {
  
  namespace field {

    namespace adapter {
    
      // functions, inlined (inline)

      template <typename T>
      inline /* explicit */
      single<T>::single(container_type& a, std::string const& b,
                        get_callback_type c, set_callback_type d)
        : inherited (a, b),
          get_value_(c),
          set_value_(d)
      {
        TRACE("hugh::field::adapter::single<" + support::demangle(typeid(T)) + ">::single");
      }

      template <typename T>
      inline /* virtual */
      single<T>::~single()
      {
        TRACE("hugh::field::adapter::single<" + support::demangle(typeid(T)) + ">::~single");
      }
    
      template <typename T>
      inline /* virtual */ typename single<T>::value_type const&
      single<T>::get() const
      {
        TRACE("hugh::field::adapter::single<" + support::demangle(typeid(T)) + ">::get");

        return get_value_();
      }
    
      template <typename T>
      inline /* virtual */ typename single<T>::value_type
      single<T>::set(value_type const& a)
      {
        TRACE("hugh::field::adapter::single<" + support::demangle(typeid(T)) + ">::set");

        value_type const result(set_value_(a));

        inherited::changed();

        return result;
      }

      template <typename T>
      inline /* virtual */ typename single<T>::value_type
      single<T>::set(value_type&& a)
      {
        TRACE("hugh::field::adapter::single<" + support::demangle(typeid(T)) + ">::set(move)");

        value_type const result(set_value_(a));

        inherited::changed();

        return result;
      }
    
    } // namespace adapter {

  } // namespace field {

} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_FIELD_ADAPTER_SINGLE_INL)
