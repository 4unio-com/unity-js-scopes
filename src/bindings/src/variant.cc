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

#include "variant.h"

#include "common.h"

namespace {

std::string
variant_string_from_type(unity::scopes::Variant::Type type) {
  switch(type) {
  case unity::scopes::Variant::Null:
    return "Null";
  case unity::scopes::Variant::Int:
    return "Int";
  case unity::scopes::Variant::Bool:
    return "Bool";
  case unity::scopes::Variant::String:
    return "String";
  case unity::scopes::Variant::Double:
    return "Double";
  case unity::scopes::Variant::Dict:
    return "Dict";
  case unity::scopes::Variant::Array:
    return "Array";
  case unity::scopes::Variant::Int64:
    return "Int64";
  }
  throw std::runtime_error("Invalid Variant type value");
}

}


Variant::Variant(unity::scopes::Variant const &variant)
  : variant_(new unity::scopes::Variant(variant)) {
}

Variant::Variant(v8::Local<v8::Value> arg)
  : variant_(new unity::scopes::Variant(unity::scopesjs::to_variant(arg))) {
}

std::string Variant::serialize_json() const {
  return variant_->serialize_json();
}

int Variant::get_int() const {
  return variant_->get_int();
}

int64_t Variant::get_int64_t() const {
  return variant_->get_int64_t();
}

double Variant::get_double() const {
  return variant_->get_double();
}

bool Variant::get_bool() const {
  return variant_->get_bool();
}

std::string Variant::get_string() const {
  return variant_->get_string();
}

Variant::VariantMap Variant::get_dict() const {
  VariantMap vm;
  for(auto &v: variant_->get_dict()) {
    vm[v.first] = std::make_shared<Variant>(v.second);
  }
  return vm;
}

Variant::VariantArray Variant::get_array() const {
  VariantArray va;
  for(auto &v: variant_->get_array()) {
    va.push_back(std::make_shared<Variant>(v));
  }
  return va;
}

bool Variant::is_null() const {
  return variant_->is_null();
}

std::string Variant::which() {
  return variant_string_from_type(variant_->which());
}

