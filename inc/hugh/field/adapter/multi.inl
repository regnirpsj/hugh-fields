// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/adapter/multi.inl                                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_ADAPTER_MULTI_INL)

#define HUGH_FIELD_ADAPTER_MULTI_INL

// includes, system

//#include <>

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>
#if defined(UKACHULLDCS_USE_TRACE) || defined(UKACHULLDCS_ALL_TRACE)
#  include <typeinfo>
#  include <hugh/support/type_info.hpp>
#endif

namespace hugh {
  
  namespace field {

    namespace adapter {
    
      // functions, inlined (inline)

      template <typename T, typename C>
      inline /* explicit */
      multi<T,C>::multi(container_type& a, std::string const& b,
                        get_callback_type c, set_callback_type d,
                        add_callback_type e, sub_callback_type f)
        : inherited (a, b),
          get_value_(c),
          set_value_(d),
          add_value_(e),
          sub_value_(f)
      {
        TRACE("hugh::field::adapter::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::multi");
      }
    
      template <typename T, typename C>
      inline /* virtual */
      multi<T,C>::~multi()
      {
        TRACE("hugh::field::adapter::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::~multi");
      }

      template <typename T, typename C>
      inline /* virtual */ typename multi<T,C>::value_container_type const&
      multi<T,C>::get() const
      {
        TRACE("hugh::field::adapter::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::get");

        return get_value_();
      }
  
      template <typename T, typename C>
      inline /* virtual */ typename multi<T,C>::value_container_type
      multi<T,C>::set(value_container_type const& a)
      {
        TRACE("hugh::field::adapter::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::set");

        value_container_type const result(set_value_(a));

        inherited::changed();

        return result;
      }

      template <typename T, typename C>
      inline /* virtual */ typename multi<T,C>::value_container_type
      multi<T,C>::set(value_container_type&& a)
      {
        TRACE("hugh::field::adapter::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::set(move)");

        value_container_type const result(set_value_(a));

        inherited::changed();

        return result;
      }
    
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      template <typename T, typename C>
      inline /* virtual */ typename multi<T,C>::value_container_type
      multi<T,C>::set(std::initializer_list<value_type> a)
      {
        TRACE("hugh::field::adapter::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::set(std::initializer_list<" +
              support::demangle(typeid(T)) + ">)");

        value_container_type const result(set_value_(a));

        inherited::changed();

        return result;
      }
#endif
    
      template <typename T, typename C>
      inline /* virtual */ bool
      multi<T,C>::add(value_type const& a)
      {
        TRACE("hugh::field::adapter::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::add");

        bool const result(add_value_(a));

        if (result) {
          inherited::changed();
        }

        return result;
      }

      template <typename T, typename C>
      inline /* virtual */ bool
      multi<T,C>::add(value_type&& a)
      {
        TRACE("hugh::field::adapter::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::add(move)");

        bool const result(add_value_(a));

        if (result) {
          inherited::changed();
        }

        return result;
      }
    
      template <typename T, typename C>
      inline /* virtual */ bool
      multi<T,C>::sub(value_type const& a)
      {
        TRACE("hugh::field::adapter::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::sub");

        bool const result(sub_value_(a));

        if (result) {
          inherited::changed();
        }

        return result;
      }

    } // namespace adapter {
  
  } // namespace field {

} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_FIELD_ADAPTER_MULTI_INL)
