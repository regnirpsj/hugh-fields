// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/connection/manager.cpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/field/connection/manager.hpp"

// includes, system

#include <sstream> // std::ostringstream

// includes, project

#include <hugh/field/base.hpp>
#include <hugh/support/io_utils.hpp>
#include <hugh/support/type_info.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

#define HUGH_FIELD_CONNECTION_MANAGER_VERBOSE
#if !defined(HUGH_USE_TRACE)
#  undef HUGH_FIELD_CONNECTION_MANAGER_VERBOSE
#endif

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal
  
} // namespace {

BOOST_SINGLETON_PLACEMENT(hugh::field::connection::manager);

namespace hugh {
  
  namespace field {
  
    namespace connection {
  
      // variables, exported
  
      // functions, exported

      bool
      manager::connect(field_type* const s, field_type* const d, update_function_type u)
      {
        TRACE("hugh::field::connection::manager::connect");

        bool result(false);

        if (s != d) {
          typedef connection_map_type::value_type value_type;

          value_type const sd(s, d, u);
          value_type const ds(d, s, u);
          auto const       found_sd(connection_map_.find(sd));
          auto const       found_ds(connection_map_.find(ds));
        
          if ((connection_map_.end() == found_sd) && (connection_map_.end() == found_ds)) {
            auto const inserted(connection_map_.insert(sd));

            if (true == (result = inserted.second)) {
              inserted.first->get<upd>()();
            }

#if defined(HUGH_FIELD_CONNECTION_MANAGER_VERBOSE)
            std::cout << support::trace::prefix() << "hugh::field::connection::manager::connect: "
                      << "added ("
                      << inserted.first->get<src>()->name()
                      << ':'
                      << inserted.first->get<dst>()->name()
                      << ':'
                      << &inserted.first->get<upd>()
                      << ')'
                      << '\n';
#endif
          }
#if defined(HUGH_FIELD_CONNECTION_MANAGER_VERBOSE)
          else {
            std::cout << support::trace::prefix() << "hugh::field::connection::manager::connect: "
                      << "rejected ("
                      << sd.get<src>()->name()
                      << ':'
                      << sd.get<dst>()->name()
                      << ':'
              //<< support::demangle(sd.get<upd>().target_type()) << '@'
                      << &sd.get<upd>()
                      << ')';

            if (connection_map_.end() != found_sd) {
              std::cout << " =?= "
                        << '('
                        << found_sd->get<src>()->name()
                        << ':'
                        << found_sd->get<dst>()->name()
                        << ':'
                //<< support::demangle(found_sd->get<upd>().target_type()) << '@'
                        << &found_sd->get<upd>()
                        << ')';
            }

            if (connection_map_.end() != found_ds) {
              std::cout << " =?= "
                        << '('
                        << found_ds->get<src>()->name()
                        << ':'
                        << found_ds->get<dst>()->name()
                        << ':'
                //<< support::demangle(found_ds->get<upd>().target_type()) << '@'
                        << &found_ds->get<upd>()
                        << ')';
            }
          
            std::cout << '\n';
          }
#endif
        }
      
        return result;
      }
    
      bool
      manager::disconnect(field_type* const f)
      {
        TRACE("hugh::field::connection::manager::disconnect");

        bool result(false);

        {
          auto found(connection_map_.by<src>().find(f));

          while (connection_map_.by<src>().end() != found) {
            if (found->get<src>() == f) {
#if defined(HUGH_FIELD_CONNECTION_MANAGER_VERBOSE)
              std::cout << support::trace::prefix()
                        << "hugh::field::connection::manager::disconnect: "
                        << "removing source ("
                        << found->get<src>()->name()
                        << ':'
                        << found->get<dst>()->name()
                        << ':'
                        << &found->get<upd>()
                        << ')'
                        << '\n';
#endif

              found = connection_map_.by<src>().erase(found);
            
              result |= true;
            } else {
              ++found;
            }
          }
        }
      
        {
          auto found(connection_map_.by<dst>().find(f));
        
          while (connection_map_.by<dst>().end() != found) {
            if (found->get<dst>() == f) {
#if defined(HUGH_FIELD_CONNECTION_MANAGER_VERBOSE)
              std::cout << support::trace::prefix()
                        << "hugh::field::connection::manager::disconnect: "
                        << "removing destination ("
                        << found->get<src>()->name()
                        << ':'
                        << found->get<dst>()->name()
                        << ':'
                        << &found->get<upd>()
                        << ')'
                        << '\n';
#endif

              found = connection_map_.by<dst>().erase(found);
            
              result |= true;
            } else {
              ++found;
            }
          }
        }
      
        return result;
      }

      bool
      manager::update(field_type* const s)
      {
        TRACE("hugh::field::connection::manager::update");

        bool result(false);
        auto found (connection_map_.by<src>().find(s));

        while (connection_map_.by<src>().end() != found) {
          if (found->get<src>() == s) {
#if defined(HUGH_FIELD_CONNECTION_MANAGER_VERBOSE)
            std::cout << support::trace::prefix() << "hugh::field::connection::manager::update: "
                      << "source ("
                      << found->get<src>()->name()
                      << ':'
                      << found->get<dst>()->name()
                      << ':'
                      << &found->get<upd>()
                      << ')'
                      << '\n';
#endif
            
            found->get<upd>()();
          
            result |= true;
          }

          ++found;
        }
      
        return result;
      }
    
      std::string
      manager::status() const
      {
        TRACE_NEVER("hugh::field::connection::manager::status");

        std::ostringstream result;

        result << "[\n"
           << std::string(2, '-') << " sources " << std::string(99, '-') << '\n';
      
        for (auto const f : connection_map_) {
          std::ostringstream ostr;
        
          print_helper<src, dst>(f.get<src>(), ostr);

#if defined(HUGH_FIELD_CONNECTION_MANAGER_VERBOSE)
          ostr << std::string(std::max(static_cast<unsigned long>(60), ostr.str().length()+1) -
                              ostr.str().length(), ' ');
    
          print_helper<dst, src>(f.get<src>(), ostr);
#endif
        
          result << ostr.str() << '\n';
        }

        result << std::string(2, '-') << " destinations " << std::string(94, '-') << '\n';
      
        for (auto const f : connection_map_) {
          std::ostringstream ostr;
        
          print_helper<dst, src>(f.get<dst>(), ostr);

#if defined(HUGH_FIELD_CONNECTION_MANAGER_VERBOSE)
          ostr << std::string(std::max(static_cast<unsigned long>(60), ostr.str().length()+1) -
                              ostr.str().length(), ' ');
    
          print_helper<src, dst>(f.get<dst>(), ostr);
#endif
        
          result << ostr.str() << '\n';
        }
      
        result << ']';
        
        return result.str();
      }    
    
      /* explicit */
      manager::manager(boost::restricted)
        : boost::mutexed_singleton<manager>(),
          connection_map_                  ()
      {
        TRACE("hugh::field::connection::manager::manager");
      }

      template <typename L, typename R>
      void
      manager::print_helper(field_type* a, std::ostream& os) const
      {
        TRACE_NEVER("hugh::field::connection::manager::print_helper");
      
        auto current(connection_map_.by<L>().find(a));
    
        os << a->name() << ' ' << ((typeid(L) == typeid(src)) ? "->" : "<-") << " { ";
    
        while (connection_map_.by<L>().end() != current) {
          if (current->template get<L>() == a) {
            os << '(' << (current->template get<R>())->name()
               << ":"
              //<< support::demangle(current->template get<upd>().target_type()) << '@'
               << &current->template get<upd>() << "),";
          }
      
          ++current;
        }
    
        os << support::ostream::remove(1) << '}';
      }
    
    } // namespace connection {
  
  } // namespace field {

} // namespace hugh {
