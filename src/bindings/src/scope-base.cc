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
#include "search-query.h"
#include "search-metadata.h"
#include "result.h"
#include "action-metadata.h"
#include "preview-query.h"

ScopeBase::ScopeBase()
  : isolate_(v8::Isolate::GetCurrent()) {
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

  v8::Local<v8::Function> start_callback =
    v8cpp::to_local<v8::Function>(isolate_, start_callback_);

  v8cpp::call_v8(isolate_,
                 start_callback,
                 v8cpp::to_v8(isolate_, scope_id.c_str()));
}

void ScopeBase::stop() {
  if (stop_callback_.IsEmpty()) {
    return;
  }

  v8::Local<v8::Function> stop_callback =
    v8cpp::to_local<v8::Function>(isolate_, stop_callback_);

  v8cpp::call_v8(isolate_, stop_callback);
}

void ScopeBase::run() {
  if (run_callback_.IsEmpty()) {
    return;
  }

  v8::Local<v8::Function> run_callback =
    v8cpp::to_local<v8::Function>(isolate_, run_callback_);

  v8cpp::call_v8(isolate_, run_callback);
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

  v8::Local<v8::Function> search_callback =
    v8cpp::to_local<v8::Function>(isolate_, search_callback_);

  v8::Locker l(isolate_);
  v8::Isolate::Scope isolate_scope(isolate_);
  v8::HandleScope handle_scope(isolate_);
  v8::Context::Scope context_scope(v8::Context::New(isolate_));

  v8::Handle<v8::Value> result =
    v8cpp::call_v8(isolate_,
                   search_callback,
                   v8cpp::to_v8(isolate_, q),
                   v8cpp::to_v8(isolate_, m));

  // TODO watch out release
  SearchQuery * sq = 
    v8cpp::from_v8<SearchQuery*>(isolate_, result);

  return unity::scopes::SearchQueryBase::UPtr(sq);
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
      unity::scopes::ActionMetadata const &action_metadata) {
  if (preview_callback_.IsEmpty()) {
    return nullptr;
  }

  // wrap & fire
  Result *r = new Result(result);
  ActionMetaData *m = new ActionMetaData(action_metadata);

  v8::Local<v8::Function> preview_callback =
    v8cpp::to_local<v8::Function>(isolate_, preview_callback_);

  v8::Handle<v8::Value> wrapped_preview = 
    v8cpp::call_v8(isolate_,
                   preview_callback,
                   v8cpp::to_v8(isolate_, r),
                   v8cpp::to_v8(isolate_, m));

  // TODO watch out release
  PreviewQuery * sq =
    v8cpp::from_v8<PreviewQuery*>(isolate_, wrapped_preview);

  return unity::scopes::PreviewQueryBase::UPtr(sq);
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

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  start_callback_.Reset(args.GetIsolate(), cb);
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

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  stop_callback_.Reset(args.GetIsolate(), cb);
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

  if (run_callback_.IsEmpty()) {
    run_callback_.Reset();
  }

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  run_callback_.Reset(args.GetIsolate(), cb);
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

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  search_callback_.Reset(args.GetIsolate(), cb);
}

void ScopeBase::onpreview(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  if (preview_callback_.IsEmpty()) {
    preview_callback_.Reset();
  }

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  preview_callback_.Reset(args.GetIsolate(), cb);
}

v8::Local<v8::Value> ScopeBase::get_scope_directory(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), scope_directory().c_str());
}

v8::Local<v8::Value> ScopeBase::get_cache_directory(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), cache_directory().c_str());
}

v8::Local<v8::Value> ScopeBase::get_tmp_directory(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), tmp_directory().c_str());
}
