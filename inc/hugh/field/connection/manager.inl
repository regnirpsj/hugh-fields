// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/connection/manager.inl                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_CONNECTION_MANAGER_INL)

#define HUGH_FIELD_CONNECTION_MANAGER_INL

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
  
    // functions, inlined (inline)

    template <typename T1, typename T2>
    inline bool
    connect(T1* const a, T2* const b, std::function<void (T1* const, T2* const)> c)
    {
      TRACE("hugh::field::connect<" + support::demangle(typeid(T1)) + "," +
            support::demangle(typeid(T2)) + ">");

      return connection::manager::instance->connect(a, b, std::bind(c, a, b));
    }

    template <typename T>
    inline bool
    disconnect(T const* const a)
    {
      TRACE("hugh::field::disconnect<" + support::demangle(typeid(T)) + ">");
    
      return connection::manager::instance->disconnect(a);
    }
  
  } // namespace field {

} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_FIELD_CONNECTION_MANAGER_INL)
