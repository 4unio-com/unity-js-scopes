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

#ifndef _UNITY_JS_CATEGORISED_RESULT_H_
#define _UNITY_JS_CATEGORISED_RESULT_H_

#include <unity/scopes/CategorisedResult.h>

#include <v8-cpp.h>

#include "category.h"

class CategorisedResult : public unity::scopes::CategorisedResult
{
 public:
  CategorisedResult(Category * category);
  ~CategorisedResult() override;

  // v8 binding
  void set_uri(v8::FunctionCallbackInfo<v8::Value> const& args);
  void set_title(v8::FunctionCallbackInfo<v8::Value> const& args);
  void set_art(v8::FunctionCallbackInfo<v8::Value> const& args);

 private:

  // TODO ownership & lifetime !
  // better to own the scptr
  Category * category_;
};

#endif // _UNITY_JS_CATEGORISED_RESULT_H_
