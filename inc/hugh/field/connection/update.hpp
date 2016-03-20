// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/connection/update.hpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_CONNECTION_UPDATE_HPP)

#define HUGH_FIELD_CONNECTION_UPDATE_HPP

// includes, system

//#include <>

// includes, project

// #include <>

namespace hugh {
  
  namespace field {
  
    namespace connection {

      namespace update {
      
        // types, exported (class, enum, struct, union, typedef)
      
        // variables, exported (extern)

        // functions, inlined (inline)

        template <typename T1, typename T2>
        void assign(T1* const /* src */, T2* const /* dst */);

        template <typename T1, typename T2>
        void average(T1* const /* src */, T2* const /* dst */);
      
        template <typename T1, typename T2>
        void append(T1* const /* src */, T2* const /* dst */);

        template <typename T1, typename T2>
        void prepend(T1* const /* src */, T2* const /* dst */);
      
        // functions, exported (extern)

      } // namespace update {
      
    } // namespace connection {
  
  } // namespace field {

} // namespace hugh {
    
#include <hugh/field/connection/update.inl>

#endif // #if !defined(HUGH_FIELD_CONNECTION_UPDATE_HPP)
