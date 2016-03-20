// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh//field/multi/base.hpp                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_MULTI_BASE_HPP)

#define HUGH_FIELD_MULTI_BASE_HPP

// includes, system

#include <initializer_list> // std::initializer_list<>
#include <vector>           // std::vector<>

// includes, project

#include <hugh/field/base.hpp>

namespace hugh {
  
  namespace field {

    namespace multi {
    
      // types, exported (class, enum, struct, union, typedef)

      template <typename T, typename C = std::vector<T>>
        class base : public field::base {

        public:
      
          using inherited            = field::base;
          using container_type       = inherited::container_type;
          using value_container_type = C;
          using value_type           = T;

          virtual void print_on(std::ostream&) const;
    
          virtual value_container_type const& get() const                            =0;
          virtual value_container_type        set(value_container_type const&)       =0;
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
          virtual value_container_type        set(std::initializer_list<value_type>) =0;
#endif
          virtual bool                        add(value_type const&)                 =0;
          virtual bool                        sub(value_type const&)                 =0;

          value_container_type const& operator* () const;
          value_container_type const* operator->() const;
          base&                       operator= (value_container_type const&);
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
          base&                       operator= (std::initializer_list<value_type>);
#endif
          base&                       operator+=(value_type const&);
          base&                       operator-=(value_type const&);
      
        protected:

          explicit base(container_type&    /* container */,
                        std::string const& /* name      */);
      
        };
    
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace multi {
  
  } // namespace field {

 } // namespace hugh {

#include <hugh/field/multi/base.inl>

#endif // #if !defined(HUGH_FIELD_MULTI_BASE_HPP)
