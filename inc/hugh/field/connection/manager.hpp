// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/connection/manager.hpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_FIELD_CONNECTION_MANAGER_HPP)

#define HUGH_FIELD_CONNECTION_MANAGER_HPP

// includes, system

#include <boost/bimap/bimap.hpp>                 // boost::bimaps::*
#include <boost/bimap/unordered_multiset_of.hpp> // boost::bimaps::unordered_multiset_of<>
#include <boost/utility/mutexed_singleton.hpp>   // boost::mutexed_singleton<>

// includes, project

#include <hugh/field/connection/update.hpp>
#include <hugh/support/printable.hpp>
#include <hugh/field/export.h>

namespace hugh {
  
  namespace field {

    class base;
  
    namespace connection {

      class base;
    
      // types, exported (class, enum, struct, union, typedef)

      class HUGH_FIELD_EXPORT manager : public support::printable,
                                        public boost::mutexed_singleton<manager> {

        BOOST_SINGLETON_PLACEMENT_DECLARATION;
      
      public:

        using field_type           = field::base;
        using update_function_type = std::function<void ()>;
      
        bool connect   (field_type* const    /* src     */,
                        field_type* const    /* dst     */,
                        update_function_type /* upd     */);
        bool disconnect(field_type* const    /* src/dst */);
        bool update    (field_type* const    /* src     */);
      
        std::string status() const;
      
        virtual void print_on(std::ostream&) const;
      
      private:

        template <class, int, typename> friend class boost::mutexed_singleton;
      
        struct dst {};
        struct src {};
        struct upd {};
      
        using connection_src_type =
          boost::bimaps::unordered_multiset_of<boost::bimaps::tagged<field_type*, src>>;
        using connection_dst_type =
          boost::bimaps::unordered_multiset_of<boost::bimaps::tagged<field_type*, dst>>;
        using connection_upd_type =
          boost::bimaps::with_info<boost::bimaps::tagged<update_function_type, upd>>;
        using connection_rel_type =
          boost::bimaps::unordered_multiset_of_relation<>;
        using connection_map_type =
          boost::bimaps::bimap<connection_src_type,
                               connection_dst_type,
                               connection_rel_type,
                               connection_upd_type>;

        connection_map_type connection_map_;
      
        explicit manager(boost::restricted);

        template <typename, typename>
          void print_helper(field_type*, std::ostream&) const;
      
      };
    
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace connection {

    // functions, inlined (inline)

    /**
     * \brief establishes a connection between a source and destination field
     *
     * ...
     *
     * \param  source field
     * \param  destination field
     * \param  update operator (dflt: assign)
     * \return true if connection established
     *
     * \thow   nothing
     */
    template <typename T1, typename T2 = T1>
    bool connect   (T1* const                                  /* src */,
                    T2* const                                  /* dst */,
                    std::function<void (T1* const, T2* const)> /* upd */ =
                    connection::update::assign<T1,T2>);

    /**
     * \brief breaks the connection of either a source or a destination field
     *
     * ...
     *
     * \param  source or destination field
     * \return true if disconnected
     *
     * \thow   nothing
     */
    template <typename T>
    bool disconnect(T* const /* src || dst */);
  
  } // namespace field {

} // namespace hugh {

#include <hugh/field/connection/manager.inl>

#endif // #if !defined(HUGH_FIELD_CONNECTION_MANAGER_HPP)
