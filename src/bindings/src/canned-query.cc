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

CannedQuery::CannedQuery(v8::Local<v8::Value> arg1,
                         v8::Local<v8::Value> arg2,
                         v8::Local<v8::Value> arg3) {
  if (!arg1->IsString()) {
    throw std::runtime_error("Invalid type for argument index 1");
  }

  std::string scope_id =
    *(v8::String::Utf8Value(arg1->ToString()));

  if (arg2->IsString() && arg3->IsString()) {

    std::string query_str =
      *(v8::String::Utf8Value(arg2->ToString()));

    std::string department_id =
      *(v8::String::Utf8Value(arg3->ToString()));

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

std::shared_ptr<unity::scopes::FilterState> CannedQuery::filter_state() const {
  return std::shared_ptr<unity::scopes::FilterState>(
      new unity::scopes::FilterState(
          query_->filter_state()));
}

unity::scopes::CannedQuery & CannedQuery::canned_query() {
  return *query_.get();
}
