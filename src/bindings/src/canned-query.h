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

#ifndef _UNITY_JS_CANNED_QUERY_H_
#define _UNITY_JS_CANNED_QUERY_H_

#include <unity/scopes/CannedQuery.h>

#include <v8-cpp.h>

class CannedQuery
{
 public:
  CannedQuery(unity::scopes::CannedQuery const &query);
  ~CannedQuery();

  // v8 binding
  v8::Local<v8::Value> query_string(
      v8::FunctionCallbackInfo<v8::Value> const& args);
  v8::Local<v8::Value> to_uri(
      v8::FunctionCallbackInfo<v8::Value> const& args);

  unity::scopes::CannedQuery const & get_canned_query();
  
 private:

  unity::scopes::CannedQuery const query_;
};

#endif // _UNITY_JS_CANNED_QUERY_H_
