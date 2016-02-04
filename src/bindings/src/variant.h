/*
 * Copyright 2015 Canonical Ltd.
 *
 * This file is part of unity-js-scopes.
 *
 * unity-js-scopes is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * unity-js-scopes is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _UNITY_JS_VARIANT_H_
#define _UNITY_JS_VARIANT_H_

#include <unity/scopes/Variant.h>

#include <v8-cpp.h>

class Variant
{
 public:

  typedef std::map<std::string, std::shared_ptr<Variant>> VariantMap;
  typedef std::vector<std::shared_ptr<Variant>> VariantArray;
  
 public:
  Variant(unity::scopes::Variant const &variant);
  Variant(v8::Local<v8::Value> arg);

  // v8 bindings
  std::string serialize_json() const;
  int get_int() const;
  int64_t get_int64_t() const;
  double get_double() const;
  bool get_bool() const;
  std::string get_string() const;
  VariantMap get_dict() const;
  VariantArray get_array() const;
  bool is_null() const;
  std::string which();

  unity::scopes::Variant variant() const;

 private:
  std::shared_ptr<unity::scopes::Variant> variant_;
};

#endif // _UNITY_JS_VARIANT_H_
