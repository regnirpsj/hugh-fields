// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/adapter/multi.hpp                                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_ADAPTER_MULTI_HPP)

#define HUGH_FIELD_ADAPTER_MULTI_HPP

// includes, system

#include <functional> // std::function<>
#include <vector>     // std::vector<>

// includes, project

#include <hugh/field/multi/base.hpp>

namespace hugh {
  
  namespace field {

    namespace adapter {
    
      // types, exported (class, enum, struct, union, typedef)

      template <typename T, typename C = std::vector<T>>
        class multi : public field::multi::base<T,C> {

        public:

          using inherited            = field::multi::base<T,C>;
          using container_type       = typename inherited::container_type;
          using value_container_type = typename inherited::value_container_type;
          using value_type           = typename inherited::value_type;
          using get_callback_type    = std::function<C const& ()>;
          using set_callback_type    = std::function<C        (C const&)>;
          using add_callback_type    = std::function<bool     (T const&)>;
          using sub_callback_type    = std::function<bool     (T const&)>;
      
          explicit multi(container_type&    /* container */,
                         std::string const& /* name      */,
                         get_callback_type  /* get_cb    */,
                         set_callback_type  /* set_cb    */,
                         add_callback_type  /* add_cb    */,
                         sub_callback_type  /* sub_cb    */);
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

          get_callback_type get_value_;
          set_callback_type set_value_;
          add_callback_type add_value_;
          sub_callback_type sub_value_;
      
        };
    
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace adapter {
  
  } // namespace field {

} // namespace hugh {

#include <hugh/field/adapter/multi.inl>

#endif // #if !defined(HUGH_FIELD_ADAPTER_MULTI_HPP)
