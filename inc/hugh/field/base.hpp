// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/base.hpp                                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_BASE_HPP)

#define HUGH_FIELD_BASE_HPP

// includes, system

#include <string> // std::string

// includes, project

#include <hugh/support/chrono.hpp>
#include <hugh/support/printable.hpp>
#include <hugh/field/export.h>

namespace hugh {
  
  namespace field {

    class container;
  
    // types, exported (class, enum, struct, union, typedef)

    /**
     * \brief Abstract base class of all fields.
     *
     * A field is an interface to \c get or \c set the contained value(s). This abstract base class
     * is inherited by, which provide the actual specializations:
     *   - \c hugh::field::single::value<T>
     *   - \c hugh::field::single::adapter<T>
     *   - \c hugh::field::multi::value<T>
     *   - \c hugh::field::multi::adapter<T>
     *
     * A field belongs to a \c container where its hase a \c name. Registration and deregistration
     * with a container are enforced by contstructor and destructor (RAII style)
     *
     * A field can be {\c touch}ed, which will act as a \c set operation without an actual change.
     *
     * 
     */
    class HUGH_FIELD_EXPORT base : public support::printable {

    public:

      using container_type = field::container;
      using time_point     = support::clock::time_point;

      /**
       * \brief Returns the c\ container instance this field belongs to.
       */
      container_type const& container() const;

      /**
       * \brief Returns the field's name.
       */
      std::string const& name() const;

      /**
       * \brief Returns the \c time_point the field was changed last.
       */      
      time_point const& last_change() const;

      /**
       * \brief Force evaluation of the field by its owning \c container without actually changing
       *        its value.
       */
      void touch();

      /**
       * \brief Overloaded member for \c std::ostream insertion
       */
      virtual void print_on(std::ostream&) const;
    
    protected:

      container_type& container_;
      std::string     name_;
      time_point      last_change_;
    
      explicit base(container_type&, std::string const&);
      virtual ~base() =0;

      void changed();
      void notify ();
    
    };
  
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)
  
  } // namespace field {

} // namespace hugh {

#endif // #if !defined(HUGH_FIELD_BASE_HPP)
