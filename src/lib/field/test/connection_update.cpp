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

#include <hugh/field/connection/manager.hpp>
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

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_connection_update_assign_single, T,
                              hugh::field::test::single_types)
{
  using namespace hugh::field;

  using container_type = test::container_single<T>;
  using field_type     = value::single<T>;

  container_type c;
  field_type     f1(c, "f1");
  field_type     f2(c, "f2");

  BOOST_CHECK( connect(&f1, &f2));
  BOOST_CHECK(!connect(&f2, &f1));
  
  f1.touch();
  
  BOOST_CHECK(f1.get() == f2.get());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_connection_update_assign_multi, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;

  using container_type = test::container_multi<T>;
  using field_type     = value::multi<T>;

  container_type c;
  field_type     f1(c, "f1");
  field_type     f2(c, "f2");

  BOOST_CHECK( connect(&f1, &f2));
  BOOST_CHECK(!connect(&f2, &f1));
  
  f1.touch();
  
  BOOST_CHECK(f1.get().size() == f2.get().size());
}
