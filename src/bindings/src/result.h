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

#ifndef _UNITY_JS_RESULT_H_
#define _UNITY_JS_RESULT_H_

#include <unity/scopes/Result.h>

#include <v8-cpp.h>

#include "common.h"

class Result : public unity::scopes::Result
{
 public:
  Result(unity::scopes::Result const &result);

  // v8 bindings
  std::shared_ptr<Result> retrieve_stored_result() const;
  void store(std::shared_ptr<Result> result, bool intercept_activation);

};

template <typename T>
void set_result_value(T * self,
                      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 2) {
    throw std::runtime_error("Invalid number of arguments");
  }

  if (!args[0]->IsString()) {
    throw std::runtime_error("Invalid argument type");
  }

  std::string key =
    *(v8::String::Utf8Value(args[0]->ToString()));

  (*static_cast<unity::scopes::Result*>(self))[key] = unity::scopesjs::to_variant(args[1]);
}

template <typename T>
v8::Handle<v8::Value> get_result_value(const T * self,
                                       const std::string& key) {
  return unity::scopesjs::from_variant((*static_cast<const unity::scopes::Result*>(self))[key]);
}


#endif // _UNITY_JS_RESULT_H_
