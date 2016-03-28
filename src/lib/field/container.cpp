// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/container.cpp                                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/field/container.hpp"

// includes, system

#include <algorithm>              // std::find<>
#include <boost/io/ios_state.hpp> // boost::io::ios_all_saver
#include <ostream>                // std::ostream
#include <stdexcept>              // std::logic_error
#include <typeinfo>               // typeid

// includes, project

#include <hugh/field/base.hpp>
#include <hugh/support/io_utils.hpp>
#include <hugh/support/thread.hpp>
#include <hugh/support/type_info.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  class dflt_cntnr_mgr : public hugh::field::container::manager {

    using lock_type  = hugh::support::simple_lock;
    using lock_guard = hugh::support::simple_lock_guard;
    using inherited  = hugh::field::container::manager;
    
  public:

    explicit dflt_cntnr_mgr()
      : inherited           (),
        container_list_lock_()
    {
      TRACE("hugh::field::container::<unnamed>::dflt_cntnr_mgr::dflt_cntnr_mgr");
    }
    
    virtual ~dflt_cntnr_mgr()
    {
      TRACE("hugh::field::container::<unnamed>::dflt_cntnr_mgr::~dflt_cntnr_mgr");
    }

    virtual void print_on(std::ostream& os) const
    {
      TRACE_NEVER("hugh::field::container::<unnamed>::dflt_cntnr_mgr::print_on");

      lock_guard const lg(container_list_lock_);

      inherited::print_on(os);
    }

    virtual void evaluate()
    {
      TRACE("hugh::field::container::<unnamed>::dflt_cntnr_mgr::evaluate");

      lock_guard const lg(container_list_lock_);

      return inherited::evaluate();
    }

  protected:

    virtual bool schedule(hugh::field::container* a)
    {
      TRACE("hugh::field::container::<unnamed>::dflt_cntnr_mgr::schedule");

      lock_guard const lg(container_list_lock_);

      return inherited::schedule(a);
    }
    
    virtual bool unschedule(hugh::field::container* a)
    {
      TRACE("hugh::field::container::<unnamed>::dflt_cntnr_mgr::unschedule");

      lock_guard const lg(container_list_lock_);

      return inherited::unschedule(a);
    }
    
  private:

    mutable lock_type container_list_lock_;
    
  };
  
  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {
  
  namespace field {
  
    // variables, exported

    /* static */ std::unique_ptr<container::manager> container::mgr(new dflt_cntnr_mgr);
    
    // functions, exported
  
    /* virtual */
    container::manager::~manager()
    {
      TRACE("hugh::field::container::manager::~manager");
    }

    /* virtual */ void
    container::manager::print_on(std::ostream& os) const
    {
      TRACE_NEVER("hugh::field::container::manager::print_on");
    
      using support::ostream::operator<<;
      
      os << container_list_;
    }

    /* virtual */ void
    container::manager::evaluate()
    {
      TRACE("hugh::field::container::manager::evaluate");
    
      for (auto c : container_list_) {
        c->evaluate();
      }

      container_list_.clear();
    }
  
    /* explicit */
    container::manager::manager()
      : support::printable  (),
        container_list_     ()
    {
      TRACE("hugh::field::container::manager::manager");
    }

    /* virtual */ bool
    container::manager::schedule(container* a)
    {
      TRACE("hugh::field::container::manager::schedule");

      bool       result(false);
      auto const found (std::find(container_list_.begin(), container_list_.end(), a));

      if (container_list_.end() == found) {
        container_list_.push_back(a);

        result = true;
      }

      return result;
    }
  
    /* virtual */ bool
    container::manager::unschedule(container* a)
    {
      TRACE("hugh::field::container::manager::unschedule");

      bool       result(false);
      auto const found (std::find(container_list_.begin(), container_list_.end(), a));

      if (container_list_.end() != found) {
        container_list_.erase(found);

        result = true;
      }

      return result;
    }
  
    /* static */ container::manager&
    container::eval_manager()
    {
      TRACE("hugh::field::container::manager::eval_manager");

      return *mgr;
    }

    container::field_list_type const&
    container::fields() const
    {
      TRACE("hugh::field::container::manager::fields");

      return field_list_;
    }
  
    void
    container::touch()
    {
      TRACE("hugh::field::container::touch");

      do_touch();
    
      mgr->schedule(this);
    }

    void
    container::evaluate()
    {
      TRACE("hugh::field::container::evaluate");

      do_evaluate();

      last_evaluate_ = support::clock::now();
    }

    void
    container::changed(base& f)
    {
      TRACE("hugh::field::container::changed");
    
      do_changed(f);

      last_change_ = support::clock::now();
    
      touch();
    }

    namespace {

      thread_local unsigned indent(0);
    
    } // namespace {
  
    /* virtual */ void
    container::print_on(std::ostream& os) const
    {
      TRACE_NEVER("hugh::field::container::print_on");

      boost::io::ios_all_saver const ias(os);
    
      std::string prefix(indent, '\t');
      
      os << '\n' << prefix << '['
         << support::demangle(typeid(*this))
         << '@'
         << std::hex << std::showbase << this
         << ":["
         << std::dec << last_change_
         << ':'
         << std::dec << last_evaluate_
         << "],";

      ++indent;
      {
        prefix += ' ';
      
        for (auto const& f : field_list_) {
          os << '\n' << prefix << std::boolalpha << *f;
        }
      
        os << '\n'
           << prefix << "mgr:" << *mgr
           << ']';
      }
      --indent;
    }
  
    /* explicit */
    container::container()
      : support::printable(),
        last_change_      (support::clock::now()),
        last_evaluate_    (last_change_),
        field_list_       ()
    {
      TRACE("hugh::field::container::container");
    }

    /* virtual */
    container::~container()
    {
      TRACE("hugh::field::container::~container");

      mgr->unschedule(this);
    }

    /* virtual */ void
    container::do_touch()
    {
      TRACE("hugh::field::container::do_touch");
    }
  
    /* virtual */ void
    container::do_evaluate()
    {
      TRACE("hugh::field::container::do_evaluate");
    }
  
    /* virtual */ void
    container::do_changed(base&)
    {
      TRACE("hugh::field::container::do_changed");
    }
  
    void
    container::add(base* a)
    {
      TRACE("hugh::field::container::add");

      auto const found(std::find(field_list_.begin(), field_list_.end(), a));

      if (field_list_.end() == found) {
        field_list_.push_back(a);
      } else {
        throw std::logic_error("hugh::field::container::add: "
                               "unable to register the same field twice!");
      }
    }
  
    void
    container::sub(base* a)
    {
      TRACE("hugh::field::container::sub");

      auto const found(std::find(field_list_.begin(), field_list_.end(), a));

      if (field_list_.end() != found) {
        field_list_.erase(found);
      } else {
        throw std::logic_error("hugh::field::container::sub: "
                               "unable to unregister non-existent field!");
      }
    }
  
  } // namespace field {

} // namespace hugh {
