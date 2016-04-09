// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/value/single.inl                                                     */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_VALUE_SINGLE_INL)

#define HUGH_FIELD_VALUE_SINGLE_INL

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

    namespace value {
    
      // functions, inlined (inline)

      template <typename T>
      inline /* explicit */
      single<T>::single(container_type& a, std::string const& b, value_type const& c)
        : inherited(a, b),
          value_   (c)
      {
        TRACE("hugh::field::value::single<" + support::demangle(typeid(T)) + ">::single");
      }

      template <typename T>
      inline /* explicit */
      single<T>::single(container_type& a, std::string const& b, value_type&& c)
        : inherited(a, b),
          value_   (std::move(c))
      {
        TRACE("hugh::field::value::single<" + support::demangle(typeid(T)) + ">::single(move)");
      }
    
      template <typename T>
      inline /* virtual */
      single<T>::~single()
      {
        TRACE("hugh::field::value::single<" + support::demangle(typeid(T)) + ">::~single");
      }
  
      template <typename T>
      inline /* virtual */ typename single<T>::value_type const&
      single<T>::get() const
      {
        TRACE("hugh::field::value::single<" + support::demangle(typeid(T)) + ">::get");
    
        return value_;
      }
    
      template <typename T>
      inline /* virtual */ typename single<T>::value_type
      single<T>::set(value_type const& a)
      {
        TRACE("hugh::field::value::single<" + support::demangle(typeid(T)) + ">::set");

        value_type const result(value_);
    
        value_ = a;

        inherited::changed();

        return result;
      }

      template <typename T>
      inline /* virtual */ typename single<T>::value_type
      single<T>::set(value_type&& a)
      {
        TRACE("hugh::field::value::single<" + support::demangle(typeid(T)) + ">::set(move)");

        value_type const result(value_);
    
        value_ = std::move(a);

        inherited::changed();

        return result;
      }
    
    } // namespace value {
  
  } // namespace field {

} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_FIELD_VALUE_SINGLE_INL)
