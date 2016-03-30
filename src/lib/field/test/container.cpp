// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/test/container.cpp                                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <array>          // std::array<>
#include <algorithm>      // std::find<>
#include <glm/glm.hpp>    // glm::vec3
#include <glm/gtx/io.hpp> // glm::operator<<

// includes, project

#include <hugh/field/adapters.hpp>
#include <hugh/field/container.hpp>
#include <hugh/field/values.hpp>
#include <hugh/support/chrono_io.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  using namespace hugh;
  
  class container : public field::container {

    typedef std::vector<unsigned> unsigned_list_type;
    
  public:

    field::value::single<bool>        svf_bool;
    field::value::single<std::string> svf_string;
    field::value::multi<glm::vec3>    mvf_vec3;
    field::adapter::single<unsigned>  saf_unsigned;
    field::adapter::multi<unsigned>   maf_unsigned;

    explicit container()
      : field::container(),
        svf_bool        (*this, "svf_bool",
                         true),
        svf_string      (*this, "svf_string",
                         std::string("abcdefghijklmnopqrstuvwxyz")),
        mvf_vec3        (*this, "mvf_vec3",
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
                         { glm::vec3(1), glm::vec3(2) }
#else
                         std::vector<glm::vec3>(2, glm::vec3(1))
#endif
                         ),
        saf_unsigned    (*this, "saf_unsigned",
                         std::bind(&container::cb_get_saf_unsigned, this),
                         std::bind(&container::cb_set_saf_unsigned, this, std::placeholders::_1)),
        maf_unsigned    (*this, "maf_unsigned",
                         std::bind(&container::cb_get_maf_unsigned, this),
                         std::bind(&container::cb_set_maf_unsigned, this, std::placeholders::_1),
                         std::bind(&container::cb_add_maf_unsigned, this, std::placeholders::_1),
                         std::bind(&container::cb_sub_maf_unsigned, this, std::placeholders::_1))
    {
      // 'field::adapter::[multi|single]<>::set' not working in initializer list
      saf_unsigned = 1;
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      maf_unsigned = { 1, 2, 3, 4 };
#else
      maf_unsigned = unsigned_list_type(4, 1);
#endif
    }

    bool needs_evaluation() const
    {
      return (support::clock::resolution < (last_change_ - last_evaluate_));
    }
    
  protected:

    virtual void do_evaluate()
    {
      field::container::do_evaluate();
    }
    
  private:

    unsigned           value_;
    unsigned_list_type value_list_;

    unsigned const& cb_get_saf_unsigned() const
    {
      return value_;
    }
    
    unsigned cb_set_saf_unsigned(unsigned const& a)
    {
      unsigned const result(value_);

      value_ = a;
      
      return result;
    }

    unsigned_list_type const& cb_get_maf_unsigned() const
    {
      return value_list_;
    }
    
    unsigned_list_type cb_set_maf_unsigned(unsigned_list_type const& a)
    {
      unsigned_list_type const result(value_list_);

      value_list_ = a;
      
      return result;
    }
    
    bool cb_add_maf_unsigned(/*typename*/ unsigned_list_type::value_type const& a)
    {
      bool result(false);
      auto found (std::find(value_list_.begin(), value_list_.end(), a));

      if (value_list_.end() == found) {
        value_list_.insert(value_list_.end(), a);
        result = true;
      }
      
      return result;
    }
    
    bool cb_sub_maf_unsigned(/*typename*/ unsigned_list_type::value_type const& a)
    {
      bool result(false);
      auto found (std::find(value_list_.begin(), value_list_.end(), a));

      if (value_list_.end() != found) {
        value_list_.erase(found);
        result = true;
      }
      
      return result;
    }
    
  };
  
  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_field_container_ctor)
{
  container const c;
  
  BOOST_CHECK(true == *c.svf_bool);
}

BOOST_AUTO_TEST_CASE(test_hugh_field_container_print_on)
{
  container const c;
  
  BOOST_CHECK(true == *c.svf_bool);
  BOOST_CHECK(std::string("abcdefghijklmnopqrstuvwxyz").length() == c.svf_string.get().length());
  BOOST_TEST_MESSAGE(std::boolalpha << c);
}

BOOST_AUTO_TEST_CASE(test_hugh_field_container_mgr)
{
  std::array<container, 5> const c = {
    {
      container(), container(), container(), container(), container(),
    }
  };

  {
    for (auto const& a : c) {
      BOOST_CHECK       (true == *a.svf_bool);
      BOOST_TEST_MESSAGE(std::boolalpha << a);
    }
  }

  {
    container::manager& cmgr(container::eval_manager());
    
    BOOST_TEST_MESSAGE("evalmgr: " << cmgr);
    
    cmgr.evaluate();
    
    for (auto const& a : c) {
      BOOST_CHECK(!a.needs_evaluation());
    }
    
    BOOST_TEST_MESSAGE("evalmgr: " << cmgr);
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_field_container_fields)
{
  container const c;
  
  BOOST_CHECK(true == *c.svf_bool);

  unsigned i(0);
  
  for (auto const& f : c.fields()) {
    BOOST_TEST_MESSAGE(std::right << std::setw(2) << i++ << ':' << *f);
  }
  
  BOOST_TEST_MESSAGE("evalmgr: " << container::eval_manager());
}
