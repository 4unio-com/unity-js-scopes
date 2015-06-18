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

CannedQuery::CannedQuery(unity::scopes::CannedQuery const &query)
  : query_(query) {
}

CannedQuery::~CannedQuery() {
}

v8::Local<v8::Value> CannedQuery::query_string(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(Isolate::GetCurrent(), query_.query_string().c_str());
}

v8::Local<v8::Value> CannedQuery::to_uri(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(Isolate::GetCurrent(), query_.to_uri().c_str());
}
