// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/single/base.inl                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_SINGLE_BASE_INL)

#define HUGH_FIELD_SINGLE_BASE_INL

// includes, system

#include <stdexcept> // std::logic_error
#include <typeinfo>

// includes, project

#include <hugh/support/string.hpp>
#include <hugh/support/type_info.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

namespace hugh {
  
  namespace field {

    namespace single {
  
      // functions, inlined (inline)

      template <typename T>
      inline /* virtual */ void
      base<T>::print_on(std::ostream& os) const
      {
        TRACE_NEVER("hugh::field::single::base<" + support::demangle(typeid(T)) + ">::print_on");

        os << '[';

        inherited::print_on(os);

        os << ',' << get() << ']';
      }

      template <>
      inline /* virtual */ void
      base<std::wstring>::print_on(std::ostream& os) const
      {
        TRACE_NEVER("hugh::field::single::base<std::wstring>::print_on");

        os << '[';

        inherited::print_on(os);

        os << ',' << support::wstring_to_string(get()) << ']';
      }
    
      template <typename T>
      inline /* virtual */ typename base<T>::value_type const&
      base<T>::get() const
      {
        TRACE("hugh::field::single::base<" + support::demangle(typeid(T)) + ">::get");

        throw std::logic_error("pure virtual function 'field::single::base<" +
                               support::demangle(typeid(T)) + ">::get' called");
      }

      template <typename T>
      inline /* virtual */ typename base<T>::value_type
      base<T>::set(value_type const&)
      {
        TRACE("hugh::field::single::base<" + support::demangle(typeid(T)) + ">::set");

        throw std::logic_error("pure virtual function 'field::single::base<" +
                               support::demangle(typeid(T)) + ">::set' called");
      }

      template <typename T>
      inline typename base<T>::value_type const&
      base<T>::operator*() const
      {
        TRACE_NEVER("hugh::field::single::base<" + support::demangle(typeid(T)) + ">::operator*");

        return get();
      }
    
      template <typename T>
      inline typename base<T>::value_type const*
      base<T>::operator->() const
      {
        TRACE_NEVER("hugh::field::single::base<" + support::demangle(typeid(T)) + ">::operator->");

        return &(get());
      }

      template <typename T>
      inline base<T>&
      base<T>::operator=(value_type const& a)
      {
        TRACE_NEVER("hugh::field::single::base<" + support::demangle(typeid(T)) + ">::operator=");

        set(a);

        return *this;
      }

      template <typename T>
      inline /* explicit */
      base<T>::base(container_type& a, std::string const& b)
        : inherited(a, b)
      {
        TRACE("hugh::field::single::base<" + support::demangle(typeid(T)) + ">::base");
      }
    
    } // namespace single {
  
  } // namespace field {

} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_FIELD_SINGLE_BASE_INL)
