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

#include "common.h"

v8::Local<v8::Value> unity::scopesjs::from_variant(
      const unity::scopes::Variant& variant) {
  switch(variant.which()) {
  case unity::scopes::Variant::Null:
    return v8::Null(v8::Isolate::GetCurrent());
    break;
  case unity::scopes::Variant::Int:
    return v8::Integer::New(v8::Isolate::GetCurrent(), variant.get_int());
    break;
  case unity::scopes::Variant::Bool:
    return v8::Boolean::New(v8::Isolate::GetCurrent(), variant.get_bool());
    break;
  case unity::scopes::Variant::String:
    return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), variant.get_string().c_str());
    break;
  case unity::scopes::Variant::Double:
    return v8::Number::New(v8::Isolate::GetCurrent(), variant.get_double());
    break;
  case unity::scopes::Variant::Int64:
    return v8::Number::New(v8::Isolate::GetCurrent(), variant.get_int());
    break;
  case unity::scopes::Variant::Dict:
    {
      v8::Handle<v8::Object> o = v8::Object::New(v8::Isolate::GetCurrent());
      for (const auto& e : variant.get_dict()) {
        o->Set(v8::String::NewFromUtf8(
                                       v8::Isolate::GetCurrent(),
                                       e.first.c_str()),
               from_variant(e.second));
      }
      return o;
    }
    break;
  case unity::scopes::Variant::Array:
    {
      const unity::scopes::VariantArray & va =
        variant.get_array();
      v8::Handle<v8::Array> a =
        v8::Array::New(v8::Isolate::GetCurrent(), variant.get_array().size());
      
      for (size_t i = 0; i < va.size(); ++i) {
        a->Set(i, from_variant(va[i]));
      }
      return a;
    }
    break;
  }

  return v8::Null(v8::Isolate::GetCurrent());
}

unity::scopes::Variant unity::scopesjs::to_variant(
      v8::Local<v8::Value> value) {
  using unity::scopes::Variant;
  using unity::scopes::VariantArray;
  using unity::scopes::VariantMap;

  Variant v;

  if (value->IsString()) {
    v = *(v8::String::Utf8Value(value->ToString()));
  } else if (value->IsUint32()) {
    v = Variant((double) value->ToUint32()->Value());
  } else if (value->IsInt32()) {
    v = Variant(value->ToInt32()->Value());
  } else if (value->IsBoolean()) {
    v = Variant(value->ToBoolean()->Value());
  } else if (value->IsNumber()) {
    v = Variant(value->NumberValue());
  } else if (value->IsObject()) {
    v8::Handle<v8::Object> o = v8::Handle<v8::Object>::Cast(value);

    v8::Local<v8::Array> names = o->GetPropertyNames();

    VariantMap vm;

    for (size_t i = 0; i < names->Length(); ++i) {
      std::string name = *(v8::String::Utf8Value(names->Get(i)));
      vm[name] = to_variant(o->Get(v8::String::NewFromUtf8(
                                   v8::Isolate::GetCurrent(), name.c_str())));
    }

    v = vm;
  } else if (value->IsArray()) {
    v8::Handle<v8::Object> o = v8::Handle<v8::Object>::Cast(value);

    VariantArray va;

    for (size_t i = 0;
         i < o->Get(v8::String::NewFromUtf8(
                      v8::Isolate::GetCurrent(), "length"))->ToObject()->Uint32Value();
         ++i) {
      va.push_back(to_variant(o->Get(i)));
    }

    v = va;
  }

  return v;
}
