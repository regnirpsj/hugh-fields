// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/field/defaults.cpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <string> // std::string

// includes, project

#include <hugh/field/adapters.hpp>
#include <hugh/field/connections.hpp>
#include <hugh/field/container.hpp>
#include <hugh/field/export.h>
#include <hugh/field/values.hpp>

#define HUGH_FIELD_DEFAULT_SPECIALIZATIONS
#undef HUGH_FIELD_DEFAULT_SPECIALIZATIONS

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

// variables, exported

#if defined(HUGH_FIELD_DEFAULT_SPECIALIZATIONS)

#  define DEFAULT_FIELD_TYPES_FOR(type)              \
  template class HUGH_FIELD_EXPORT hugh::field::value::multi   <type>; \
  template class HUGH_FIELD_EXPORT hugh::field::value::single  <type>; \
  template class HUGH_FIELD_EXPORT hugh::field::adapter::multi <type>; \
  template class HUGH_FIELD_EXPORT hugh::field::adapter::single<type>

DEFAULT_FIELD_TYPES_FOR(         bool);
DEFAULT_FIELD_TYPES_FOR(signed   char);
DEFAULT_FIELD_TYPES_FOR(unsigned char);
DEFAULT_FIELD_TYPES_FOR(         char16_t);
DEFAULT_FIELD_TYPES_FOR(         char32_t);
DEFAULT_FIELD_TYPES_FOR(signed   short);
DEFAULT_FIELD_TYPES_FOR(unsigned short);
DEFAULT_FIELD_TYPES_FOR(signed   int);
DEFAULT_FIELD_TYPES_FOR(unsigned int);
DEFAULT_FIELD_TYPES_FOR(signed   long int);
DEFAULT_FIELD_TYPES_FOR(unsigned long int);
DEFAULT_FIELD_TYPES_FOR(signed   long long int);
DEFAULT_FIELD_TYPES_FOR(unsigned long long int);
DEFAULT_FIELD_TYPES_FOR(         float);
DEFAULT_FIELD_TYPES_FOR(         double);
DEFAULT_FIELD_TYPES_FOR(         long double);
DEFAULT_FIELD_TYPES_FOR(         std::string);
DEFAULT_FIELD_TYPES_FOR(         std::wstring);

#undef DEFAULT_FIELD_TYPES_FOR

#endif // #if defined(HUGH_FIELD_DEFAULT_SPECIALIZATIONS)

#if defined(_MSC_VER)
HUGH_FIELD_EXPORT void getRidOfLNK4221FieldDefaults(){}
#endif
