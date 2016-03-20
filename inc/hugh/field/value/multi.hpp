// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/value/multi.hpp                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_VALUE_MULTI_HPP)

#define HUGH_FIELD_VALUE_MULTI_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/field/multi/base.hpp>

namespace hugh {
  
  namespace field {

    namespace value {
    
      // types, exported (class, enum, struct, union, typedef)

      template <typename T, typename C = std::vector<T>>
        class multi : public field::multi::base<T,C> {

        public:

          using inherited            = field::multi::base<T,C>;
          using container_type       = typename inherited::container_type;
          using value_container_type = typename inherited::value_container_type;
          using value_type           = typename inherited::value_type;        

          explicit multi(container_type&                   /* container */,
                         std::string const&                /* name */,
                         value_container_type const&       /* init */ = value_container_type());
          explicit multi(container_type&                   /* container */,
                         std::string const&                /* name */,
                         value_container_type&&            /* init */);
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
          explicit multi(container_type&                   /* container */,
                         std::string const&                /* name */,
                         std::initializer_list<value_type> /* init */);
#endif
          virtual ~multi();
    
          virtual value_container_type const& get() const;
          virtual value_container_type        set(value_container_type const&);
          virtual value_container_type        set(value_container_type&&);
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
          virtual value_container_type        set(std::initializer_list<value_type>);
#endif
          virtual bool                        add(value_type const&);
          virtual bool                        add(value_type&&);
          virtual bool                        sub(value_type const&);

          //using inherited::operator*;
          using inherited::operator=;
          //using inherited::operator+=;
          //using inherited::operator-=;
      
        private:

          value_container_type value_container_;
    
        };
    
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace value {
  
  } // namespace field {

} // namespace hugh {

#include <hugh/field/value/multi.inl>

#endif // #if !defined(HUGH_FIELD_VALUE_MULTI_HPP)
