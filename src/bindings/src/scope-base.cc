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

#include "scope-base.h"

#include "canned-query.h"
#include "search-metadata.h"

ScopeBase::ScopeBase() {
}
ScopeBase::~ScopeBase() {
  if ( ! start_callback_.IsEmpty()) {
    start_callback_.Reset();
  }
  if ( ! stop_callback_.IsEmpty()) {
    stop_callback_.Reset();
  }
  if ( ! run_callback_.IsEmpty()) {
    run_callback_.Reset();
  }
  if ( ! search_callback_.IsEmpty()) {
    search_callback_.Reset();
  }
}

void ScopeBase::start(std::string const& scope_id) {
  if (start_callback_.IsEmpty()) {
    return;
  }

  v8::Isolate * isolate = Isolate::GetCurrent();

  v8::Local<v8::Function> start_callback =
    v8cpp::to_local<v8::Function>(isolate, start_callback_);

  v8cpp::call_v8(isolate, start_callback, v8cpp::to_v8(isolate, scope_id.c_str()));
}

void ScopeBase::stop() {
  if (stop_callback_.IsEmpty()) {
    return;
  }

  v8::Isolate * isolate = Isolate::GetCurrent();

  v8::Local<v8::Function> stop_callback =
    v8cpp::to_local<v8::Function>(isolate, stop_callback_);

  v8cpp::call_v8(isolate, stop_callback);
}

void ScopeBase::run() {
  if (run_callback_.IsEmpty()) {
    return;
  }

  v8::Isolate * isolate = Isolate::GetCurrent();

  v8::Local<v8::Function> run_callback =
    v8cpp::to_local<v8::Function>(isolate, run_callback_);

  v8cpp::call_v8(isolate, run_callback);
}

unity::scopes::SearchQueryBase::UPtr ScopeBase::search(
      unity::scopes::CannedQuery const &query,
      unity::scopes::SearchMetadata const &metadata) {
  if (search_callback_.IsEmpty()) {
    return nullptr;
  }

  // wrap & fire
  CannedQuery *q = new CannedQuery(query);
  SearchMetaData *m = new SearchMetaData(metadata);

  v8::Isolate *isolate = Isolate::GetCurrent();

  v8::Local<v8::Function> search_callback =
    v8cpp::to_local<v8::Function>(isolate, search_callback_);

  v8::Handle<v8::Value> result = 
    v8cpp::call_v8(isolate,
                   search_callback,
                   v8cpp::export_object<CannedQuery>(isolate, q),
                   v8cpp::export_object<SearchMetaData>(isolate, m));

  SearchQuery * sq =
    v8cpp::import_object<SearchQuery>(isolate, result);
  return sq;
}

unity::scopes::ActivationQueryBase::UPtr ScopeBase::activate(
      unity::scopes::Result const &result,
      unity::scopes::ActionMetadata const &metadata) {
  return nullptr;
}

unity::scopes::ActivationQueryBase::UPtr ScopeBase::perform_action(
      unity::scopes::Result const &result,
      unity::scopes::ActionMetadata const &metadata,
      std::string const &widget_id,
      std::string const &action_id) {
  return nullptr;
}

unity::scopes::PreviewQueryBase::UPtr ScopeBase::preview(
      unity::scopes::Result const &result,
      unity::scopes::ActionMetadata const &metadata) {
  return nullptr;
}

void ScopeBase::onstart(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  if (start_callback_.IsEmpty()) {
    start_callback_.Reset();
  }

  start_callback_ =
    v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[0]));
}

void ScopeBase::onstop(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  if (stop_callback_.IsEmpty()) {
    stop_callback_.Reset();
  }

  stop_callback_ =
    v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[0]));
}

void ScopeBase::onrun(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  if (start_callback_.IsEmpty()) {
    start_callback_.Reset();
  }

  start_callback_ =
    v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[0]));
}

void ScopeBase::onsearch(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  if (search_callback_.IsEmpty()) {
    search_callback_.Reset();
  }

  search_callback_ =
    v8::Persistent<v8::Function>::New(v8::Local<v8::Function>::Cast(args[0]));
}

