// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/connection/update.inl                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_CONNECTION_UPDATE_INL)

#define HUGH_FIELD_CONNECTION_UPDATE_INL

// includes, system

#include <numeric> // std::accumulate

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>
#if defined(HUGH_USE_TRACE) || defined(HUGH_ALL_TRACE)
#  include <typeinfo>
#  include <hugh/support/type_info.hpp>
#endif

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable:4244) //  conversion from 'T1' to 'T2', possible loss of data
#endif

namespace hugh {
  
  namespace field {

    namespace connection {

      namespace update {
      
        // functions, inlined (inline)

        template <typename T1, typename T2>
        inline void
        assign(T1* const s, T2* const d)
        {
          TRACE("hugh::field::connection::update::assign<" + support::demangle(typeid(T1)) + "," +
                support::demangle(typeid(T2)) + ">");
        
          d->set(s->get());
        }

        template <typename T1, typename T2>
        inline void
        average(T1* const s, T2* const d)
        {
          TRACE("hugh::field::connection::update::average<" + support::demangle(typeid(T1)) + "," +
                support::demangle(typeid(T2)) + ">");

          if (!s->get().empty()) {
            d->set(std::accumulate(s->get().begin(), s->get().end(), typename T1::value_type()) /
                   s->get().size());
          } else {
            d->set(typename T1::value_type());
          }
        }
      
        template <typename T1, typename T2>
        inline void
        append(T1* const s, T2* const d)
        {
          TRACE("hugh::field::connection::update::append<" + support::demangle(typeid(T1)) + "," +
                support::demangle(typeid(T2)) + ">");
        
          d->add(s->get());
        }

        template <typename T1, typename T2>
        inline void
        prepend(T1* const s, T2* const d)
        {
          TRACE("hugh::field::connection::update::prepend<" + support::demangle(typeid(T1)) + "," +
                support::demangle(typeid(T2)) + ">");
        
          typename T2::value_container_type tmp(d->get());

          tmp.insert(s->get(), tmp.begin());

          d->set(tmp);
        }
      
      } // namespace update {
    
    } // namespace connection {
  
  } // namespace field {

} // namespace hugh {

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_FIELD_CONNECTION_UPDATE_INL)
