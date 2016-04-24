// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/value/single.hpp                                                     */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_VALUE_SINGLE_HPP)

#define HUGH_FIELD_VALUE_SINGLE_HPP

// includes, system

// #include <>

// includes, project

#include <hugh/field/single/base.hpp>

namespace hugh {
  
  namespace field {

    namespace value {
    
      // types, exported (class, enum, struct, union, typedef)

      template <typename T>
      class single : public field::single::base<T> {

      public:

        using inherited      = field::single::base<T>;
        using container_type = typename inherited::container_type;
        using value_type     = typename inherited::value_type;
    
        explicit single(container_type&    /* container */,
                        std::string const& /* name      */,
                        value_type const&  /* init      */ = value_type());
        explicit single(container_type&    /* container */,
                        std::string const& /* name      */,
                        value_type&&       /* init      */);
        virtual ~single();
    
        virtual value_type const& get() const;
        virtual value_type        set(value_type const&);
        virtual value_type        set(value_type&&);
        
        using inherited::operator=;
      
      private:

        value_type value_;
    
      };
    
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace value {

  } // namespace field {

} // namespace hugh {

#include <hugh/field/value/single.inl>

#endif // #if !defined(HUGH_FIELD_VALUE_SINGLE_HPP)
