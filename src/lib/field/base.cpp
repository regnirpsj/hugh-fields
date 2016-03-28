// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/base.cpp                                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/field/base.hpp"

// includes, system

#include <algorithm>              // std::find<>
#include <boost/io/ios_state.hpp> // boost::io::ios_all_saver
#include <ostream>                // std::ostream
#include <stdexcept>              // std::logic_error

// includes, project

#include <hugh/field/connection/manager.hpp>
#include <hugh/field/container.hpp>
#include <hugh/support/io_utils.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {
  
  namespace field {
  
    // variables, exported
  
    // functions, exported

    container const&
    base::container() const
    {
      TRACE("hugh::field::base::container(get)");

      return container_;
    }

    std::string const&
    base::name() const
    {
      TRACE("hugh::field::base::name(get)");

      return name_;
    }

    support::clock::time_point const&
    base::last_change() const
    {
      TRACE("hugh::field::base::last_change(get)");
    
      return last_change_;
    }
  
    void
    base::touch()
    {
      TRACE("hugh::field::base::touch");

      changed();
    }
  
    /* virtual */ void
    base::print_on(std::ostream& os) const
    {
      TRACE_NEVER("hugh::field::base::print_on");

      using support::ostream::operator<<;

      boost::io::ios_all_saver const ias(os);
    
      os << '['
         << std::right << std::setw(19) << name_
         << '@'
         << std::hex << std::showbase << this
         << "->c@"
         << std::hex << std::showbase << &container_
         << ':'
         << std::dec << last_change_
         << ']';
    }
  
    /* explicit */
    base::base(container_type& a, std::string const& b)
      : container_  (a),
        name_       (b),
        last_change_(support::clock::now())
    {
      TRACE("hugh::field::base::base");

      if (name_.empty()) {
        throw std::logic_error("hugh::field::base::base: field names cannot be empty!");
      }
    
      container_.add(this);
    }
  
    /* virtual */
    base::~base()
    {
      TRACE("hugh::field::base::~base");

      connection::manager::instance->disconnect(this);
    
      container_.sub(this);
    }

    void
    base::changed()
    {
      TRACE("hugh::field::base::changed");

      last_change_ = support::clock::now();
    
      container_.changed(*this);
    
      notify();
    }
  
    void
    base::notify()
    {
      TRACE("hugh::field::base::notify");

      connection::manager::instance->update(this);
    }
  
  } // namespace field {

} // namespace hugh {
