// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/test/connection_manager.cpp                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <hugh/field/connection/manager.hpp>
#include <hugh/field/container.hpp>
#include <hugh/field/value/multi.hpp>
#include <hugh/field/value/single.hpp>
#include <shared.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)  
  
  // variables, internal
  
  // functions, internal

  template <typename T1, typename T2>
  std::function<void (T1* const, T2* const)>
  make_function(T1 const&, T2 const&, void (*f)(T1* const, T2* const))
  {
    return f;
  }
  
} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_field_connection_manager_print)
{
  using namespace hugh::field;

  connection::manager::lease cml;
  
  BOOST_CHECK(&cml);  
  BOOST_TEST_MESSAGE(cml->status());
  
  {
    test::container_single<unsigned> c;
    value::single<unsigned>          f1(c, "f1");
    value::single<signed>            f2(c, "f2");
    value::single<unsigned>          f3(c, "f3");

    BOOST_CHECK( connect(&f1, &f2));
    BOOST_CHECK(!connect(&f1, &f2));
    BOOST_CHECK( connect(&f1, &f3));

    f1.touch();
    
    BOOST_TEST_MESSAGE(cml->status());
    
    {
      BOOST_CHECK(!connect(&f3, &f3));
      
      value::single<unsigned> f4(c, "f4");
      
      BOOST_CHECK( connect(&f3, &f4));
      BOOST_CHECK(!connect(&f4, &f3));

      test::container_single<float> cf;
      value::single<float>          f5(cf, "f5");

      BOOST_CHECK( connect(&f5, &f3));
      BOOST_CHECK(!connect(&f3, &f5));

      f3.touch();
      f5.touch();
      
      BOOST_TEST_MESSAGE(cml->status());
    }

    {
      using connection::update::average;
      
      test::container_single<float> cf;
      value::multi<float>           f6(cf, "f6", { 1, 2, 3, });
      
      BOOST_CHECK( connect(&f6, &f3, make_function(f6, f3, average)));
      
      f6.touch();

      BOOST_CHECK(2 == f3.get());
      
      BOOST_TEST_MESSAGE(cml->status());
    }

    {
      using connection::update::append;
      
      test::container_single<float> cf;
      value::multi<float>           f6(cf, "f6");
      
      BOOST_CHECK(connect(&f3, &f6, make_function(f3, f6, append)));
      
      f3.touch();

      BOOST_CHECK(f3.get() == *(f6.get().rbegin()));
      
      BOOST_TEST_MESSAGE(cml->status());
    }

    {
      using connection::update::prepend;
      
      test::container_single<float> cf;
      value::multi<float>           f6(cf, "f6");
      
      BOOST_CHECK(connect(&f3, &f6, make_function(f3, f6, prepend)));
      
      f3.touch();

      BOOST_CHECK(f3.get() == *(f6.get().begin()));
      
      BOOST_TEST_MESSAGE(cml->status());
    }

    BOOST_TEST_MESSAGE(cml->status());
  }
  
  BOOST_TEST_MESSAGE(cml->status());
}
