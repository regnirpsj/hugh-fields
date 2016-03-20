// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/value/multi.inl                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_VALUE_MULTI_INL)

#define HUGH_FIELD_VALUE_MULTI_INL

// includes, system

#include <algorithm> // std::find<>

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

      template <typename T, typename C>
      inline /* explicit */
      multi<T,C>::multi(container_type& a, std::string const& b, value_container_type const& c)
        : inherited       (a, b),
          value_container_(c)
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::multi");
      }

      template <typename T, typename C>
      inline /* explicit */
      multi<T,C>::multi(container_type& a, std::string const& b, value_container_type&& c)
        : inherited       (a, b),
          value_container_(c)
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::multi(move)");
      }
    
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      template <typename T, typename C>
      inline /* explicit */
      multi<T,C>::multi(container_type& a, std::string const& b,
                        std::initializer_list<value_type> c)
        : inherited       (a, b),
          value_container_(c)
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::multi(std::initializer_list<" +
              support::demangle(typeid(T)) + ">)");
      }
#endif
    
      template <typename T, typename C>
      inline /* virtual */
      multi<T,C>::~multi()
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::~multi");
      }
  
      template <typename T, typename C>
      inline /* virtual */ typename multi<T,C>::value_container_type const&
      multi<T,C>::get() const
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::get");

        return value_container_;
      }
    
      template <typename T, typename C>
      inline /* virtual */ typename multi<T,C>::value_container_type
      multi<T,C>::set(value_container_type const& a)
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::set");

        value_container_type const result(value_container_);
    
        value_container_ = a;

        inherited::changed();

        return result;
      }

      template <typename T, typename C>
      inline /* virtual */ typename multi<T,C>::value_container_type
      multi<T,C>::set(value_container_type&& a)
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::set(move)");

        value_container_type const result(value_container_);
    
        value_container_ = a;

        inherited::changed();

        return result;
      }
    
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      template <typename T, typename C>
      inline /* virtual */ typename multi<T,C>::value_container_type
      multi<T,C>::set(std::initializer_list<value_type> a)
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::set" +
              "(std::initializer_list<" + support::demangle(typeid(T)) + ">)");

        value_container_type const result(value_container_);
    
        value_container_ = a;

        inherited::changed();

        return result;
      }
#endif
    
      template <typename T, typename C>
      inline /* virtual */ bool
      multi<T,C>::add(value_type const& a)
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::add");

        bool       result(false);
        auto const found (std::find(value_container_.begin(), value_container_.end(), a));

        if (value_container_.end() == found) {
          value_container_.insert(value_container_.end(), a);

          inherited::changed();

          result = true;
        }

        return result;
      }

      template <typename T, typename C>
      inline /* virtual */ bool
      multi<T,C>::add(value_type&& a)
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::add(move)");

        bool       result(false);
        auto const found (std::find(value_container_.begin(), value_container_.end(), a));

        if (value_container_.end() == found) {
          value_container_.insert(value_container_.end(), a);

          inherited::changed();

          result = true;
        }

        return result;
      }
    
      template <typename T, typename C>
      inline /* virtual */ bool
      multi<T,C>::sub(value_type const& a)
      {
        TRACE("hugh::field::value::multi<" + support::demangle(typeid(T)) + "," +
              support::demangle(typeid(C)) + ">::sub");

        bool       result(false);
        auto const found (std::find(value_container_.begin(), value_container_.end(), a));

        if (value_container_.end() != found) {
          value_container_.erase(found);
        
          inherited::changed();

          result = true;
        }

        return result;
      }
    
    } // namespace value {

  } // namespace field {

} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_FIELD_VALUE_MULTI_INL)
