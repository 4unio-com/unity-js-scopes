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

#include "canned-query.h"

CannedQuery::CannedQuery(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 3) {
    throw std::runtime_error("Invalid number of arguments for query");
  }

  if (!args[0]->IsString()) {
    throw std::runtime_error("Invalid type for argument index 1");
  }

  std::string scope_id =
    *(v8::String::Utf8Value(args[0]->ToString()));

  if (args[1]->IsString() && args[2]->IsString()) {

    std::string query_str =
      *(v8::String::Utf8Value(args[1]->ToString()));

    std::string department_id =
      *(v8::String::Utf8Value(args[2]->ToString()));

    query_.reset(
        new unity::scopes::CannedQuery(
            scope_id,
            query_str,
            department_id));
  } else {
    query_.reset(
        new unity::scopes::CannedQuery(scope_id));
  }
}

CannedQuery::CannedQuery(const unity::scopes::CannedQuery& canned_query) {
  query_.reset(new unity::scopes::CannedQuery(canned_query));
}

void CannedQuery::set_department_id(const std::string& department_id) {
  query_->set_department_id(department_id);
}

void CannedQuery::set_query_string(const std::string& query_string) {
  query_->set_query_string(query_string);
}

void CannedQuery::set_filter_state(std::shared_ptr<unity::scopes::FilterState> filter_state) {
  query_->set_filter_state(*filter_state);
}

std::string CannedQuery::scope_id() const {
  return query_->scope_id();
}

std::string CannedQuery::department_id() const {
  return query_->department_id();
}

std::string CannedQuery::query_string() const {
  return query_->query_string();
}

std::string CannedQuery::to_uri() const {
  return query_->to_uri();
}

unity::scopes::FilterState CannedQuery::filter_state() const {
  return query_->filter_state();
}

unity::scopes::CannedQuery & CannedQuery::canned_query() {
  return *query_.get();
}
