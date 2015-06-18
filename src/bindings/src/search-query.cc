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

#include "search-query.h"

#include "canned-query.h"
#include "search-metadata.h"
#include "search-reply.h"

SearchQuery::SearchQuery(
      const v8::Local<v8::Object>& query,
      const v8::Local<v8::Object>& metadata,
      const v8::Local<v8::Function> &run_callback,
      const v8::Local<v8::Function> &cancelled_callback)
  : unity::scopes::SearchQueryBase(
        *v8cpp::import_object<CannedQuery>(v8::Isolate::GetCurrent(), query),
        *v8cpp::import_object<SearchMetaData>(v8::Isolate::GetCurrent(), metadata)),
    run_callback_(v8::Isolate::GetCurrent(), run_callback),
    cancelled_callback_(v8::Isolate::GetCurrent(), cancelled_callback) {
}

SearchQuery::~SearchQuery() {
  if (!run_callback_.IsEmpty()) {
    run_callback_.Reset();
  }
  if (!cancelled_callback_.IsEmpty()) {
    cancelled_callback_.Reset();
  }
}

void SearchQuery::onrun(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  if (!run_callback_.IsEmpty()) {
    run_callback_.Reset();
  }

  run_callback_ =
    v8::Persistent<v8::Function>::New(args.GetIsolate(), v8::Local<v8::Function>::Cast(args[0]->ToObject));
}

void SearchQuery::oncancelled(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  if (cancelled_callback_.IsEmpty()) {
    cancelled_callback_.Reset();
  }

  cancelled_callback_ =
    v8::Persistent<v8::Function>::New(args.GetIsolate(),
                                      v8::Local<v8::Function>::Cast(args[0]->ToObject()));
}

v8::Local<v8::Value> SearchQuery::query(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  CannedQuery *q =
    new CannedQuery(unity::scopes::SearchQueryBase::query());

  v8::Isolate *isolate = v8::Isolate::GetCurrent();

  auto wrapped_q = v8cpp::export_object<CannedQuery>(isolate, q);

  return wrapped_q;
}

void SearchQuery::run(unity::scopes::SearchReplyProxy const& reply) {
  if (run_callback_.IsEmpty()) {
    return;
  }

  // wrap & fire
  SearchReply *sr = new SearchReply(reply);

  v8::Isolate *isolate = v8::Isolate::GetCurrent();

  auto wrapped_sr = v8cpp::export_object<SearchReply>(isolate, sr);

  v8::Local<v8::Function> run_callback =
    v8cpp::to_local<v8::Function>(isolate, run_callback_);

  v8cpp::call_v8(isolate, run_callback, wrapped_sr);
}

void SearchQuery::cancelled() {
  if (cancelled_callback_.IsEmpty()) {
    return;
  }

  v8::Isolate *isolate = v8::Isolate::GetCurrent();

  v8::Local<v8::Function> cancelled_callback =
    v8cpp::to_local<v8::Function>(isolate, cancelled_callback_);

  v8cpp::call_v8(isolate, cancelled_callback);
}
