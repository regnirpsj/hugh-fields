// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/test/connection_update.cpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <hugh/field/connection/update.hpp>
#include <hugh/field/value/multi.hpp>
#include <hugh/field/value/single.hpp>
#include <shared.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>

BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_connection_update_single, T,
                              hugh::field::test::single_types)
{
  using namespace hugh::field;

  typedef test::container_single<T> container_type;
  typedef value::single<T>          field_type;

  container_type c;
  field_type     f(c, "f");

  BOOST_CHECK(T() == f.get());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_field_connection_update_multi, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;

  typedef test::container_multi<T> container_type;
  typedef value::multi<T>          field_type;

  container_type c;
  field_type     f(c, "f");

  BOOST_CHECK(0 == f.get().size());
}
