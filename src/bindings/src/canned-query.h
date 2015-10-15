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
  CannedQuery(const unity::scopes::CannedQuery& canned_query);
  CannedQuery(v8::Local<v8::Value> arg1,
              v8::Local<v8::Value> arg2,
              v8::Local<v8::Value> arg3);

  // v8 bindings
  void set_department_id(const std::string& department_id);
  void set_query_string(const std::string& query_string);
  void set_filter_state(std::shared_ptr<unity::scopes::FilterState> filter_state);

  std::string scope_id() const;
  std::string department_id() const;
  std::string query_string() const;
  std::string to_uri() const;
  std::shared_ptr<unity::scopes::FilterState> filter_state() const;

  unity::scopes::CannedQuery & canned_query();

 private:
  std::unique_ptr<unity::scopes::CannedQuery> query_;
};

#endif // _UNITY_JS_CANNED_QUERY_H_
