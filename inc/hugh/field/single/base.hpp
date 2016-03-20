// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/single/base.hpp                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_SINGLE_BASE_HPP)

#define HUGH_FIELD_SINGLE_BASE_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/field/base.hpp>

namespace hugh {
  
  namespace field {

    namespace single {
    
      // types, exported (class, enum, struct, union, typedef)

      template <typename T>
      class base : public field::base {

      public:

        using inherited      = field::base;
        using container_type = inherited::container_type;
        using value_type     = T;

        virtual void print_on(std::ostream&) const;
    
        virtual value_type const& get() const            =0;
        virtual value_type        set(value_type const&) =0;

        value_type const& operator* () const;
        value_type const* operator->() const;
        base&             operator= (value_type const&);

      protected:

        explicit base(container_type&    /* container */,
                      std::string const& /* name      */);
      
      };
    
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace single {
  
  } // namespace field {

} // namespace hugh {

#include <hugh/field/single/base.inl>

#endif // #if !defined(HUGH_FIELD_SINGLE_BASE_HPP)
