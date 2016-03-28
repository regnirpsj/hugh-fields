// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/test/adapter_multi.cpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <sstream> // std::ostringstream

// includes, project

#include <hugh/field/adapter/multi.hpp>
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

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_container, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>                     c;
  adapter::multi<typename T::value_type> const f(c, "f",
                                                 std::bind(&test::container_multi<T>::cb_get, &c),
                                                 std::bind(&test::container_multi<T>::cb_set, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_add, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_sub, &c,
                                                           std::placeholders::_1));

  BOOST_CHECK(&c == &f.container());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_name, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>                     c;
  adapter::multi<typename T::value_type> const f(c, "f",
                                                 std::bind(&test::container_multi<T>::cb_get, &c),
                                                 std::bind(&test::container_multi<T>::cb_set, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_add, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_sub, &c,
                                                           std::placeholders::_1));

  BOOST_CHECK("f" == f.name());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_last_change, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>                     c;
  adapter::multi<typename T::value_type> const f(c, "f",
                                                 std::bind(&test::container_multi<T>::cb_get, &c),
                                                 std::bind(&test::container_multi<T>::cb_set, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_add, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_sub, &c,
                                                           std::placeholders::_1));

  BOOST_CHECK(hugh::support::clock::now() > f.last_change());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_get, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>                     c;
  adapter::multi<typename T::value_type> const f(c, "f",
                                                 std::bind(&test::container_multi<T>::cb_get, &c),
                                                 std::bind(&test::container_multi<T>::cb_set, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_add, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_sub, &c,
                                                           std::placeholders::_1));

  BOOST_CHECK(T() == f.get());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_set, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>               c;
  adapter::multi<typename T::value_type> f(c, "f",
                                           std::bind(&test::container_multi<T>::cb_get, &c),
                                           std::bind(&test::container_multi<T>::cb_set, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_add, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_sub, &c,
                                                     std::placeholders::_1));
  
  BOOST_CHECK(T() == f.set(T()));
}

#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1800))
BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_set_initlist, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>               c;
  adapter::multi<typename T::value_type> f(c, "f",
                                           std::bind(&test::container_multi<T>::cb_get, &c),
                                           std::bind(&test::container_multi<T>::cb_set, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_add, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_sub, &c,
                                                     std::placeholders::_1));

  BOOST_CHECK(T() == f.set({ }));
}
#endif

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_add, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>               c;
  adapter::multi<typename T::value_type> f(c, "f",
                                           std::bind(&test::container_multi<T>::cb_get, &c),
                                           std::bind(&test::container_multi<T>::cb_set, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_add, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_sub, &c,
                                                     std::placeholders::_1));

  BOOST_CHECK(f.add(typename T::value_type()));  
  BOOST_CHECK(1 == f.get().size());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_sub, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>               c;
  adapter::multi<typename T::value_type> f(c, "f",
                                           std::bind(&test::container_multi<T>::cb_get, &c),
                                           std::bind(&test::container_multi<T>::cb_set, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_add, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_sub, &c,
                                                     std::placeholders::_1));

  BOOST_CHECK(f.add(typename T::value_type()));
  BOOST_CHECK(f.sub(typename T::value_type()));
  BOOST_CHECK(true == f.get().empty());
}


BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_op_dereference, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>                     c;
  adapter::multi<typename T::value_type> const f(c, "f",
                                                 std::bind(&test::container_multi<T>::cb_get, &c),
                                                 std::bind(&test::container_multi<T>::cb_set, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_add, &c,
                                                           std::placeholders::_1),
                                                 std::bind(&test::container_multi<T>::cb_sub, &c,
                                                           std::placeholders::_1));

  BOOST_CHECK(T() == *f);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_op_assign, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>               c;
  adapter::multi<typename T::value_type> f(c, "f",
                                           std::bind(&test::container_multi<T>::cb_get, &c),
                                           std::bind(&test::container_multi<T>::cb_set, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_add, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_sub, &c,
                                                     std::placeholders::_1));
  
  BOOST_CHECK(T() == *(f = T()));
}

#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1800))
BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_op_assign_initlist, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>               c;
  adapter::multi<typename T::value_type> f(c, "f",
                                           std::bind(&test::container_multi<T>::cb_get, &c),
                                           std::bind(&test::container_multi<T>::cb_set, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_add, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_sub, &c,
                                                     std::placeholders::_1));
  
  BOOST_CHECK(T() == *(f = { }));
}
#endif

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_op_add, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>               c;
  adapter::multi<typename T::value_type> f(c, "f",
                                           std::bind(&test::container_multi<T>::cb_get, &c),
                                           std::bind(&test::container_multi<T>::cb_set, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_add, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_sub, &c,
                                                     std::placeholders::_1));

  f += typename T::value_type();
  
  BOOST_CHECK(1 == f.get().size());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_op_sub, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>               c;
  adapter::multi<typename T::value_type> f(c, "f",
                                           std::bind(&test::container_multi<T>::cb_get, &c),
                                           std::bind(&test::container_multi<T>::cb_set, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_add, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_sub, &c,
                                                     std::placeholders::_1));

  f += typename T::value_type();
  f -= typename T::value_type();
  
  BOOST_CHECK(true == f.get().empty());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_field_adapter_multi_print_on, T,
                              hugh::field::test::multi_types)
{
  using namespace hugh::field;
  
  test::container_multi<T>               c;
  adapter::multi<typename T::value_type> f(c, "f",
                                           std::bind(&test::container_multi<T>::cb_get, &c),
                                           std::bind(&test::container_multi<T>::cb_set, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_add, &c,
                                                     std::placeholders::_1),
                                           std::bind(&test::container_multi<T>::cb_sub, &c,
                                                     std::placeholders::_1));
  std::ostringstream                       ostr;

  ostr << c;

  BOOST_CHECK(!ostr.str().empty());
}
