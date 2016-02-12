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

#include "action-metadata.h"
#include "activation-query.h"
#include "activation-query-proxy.h"
#include "canned-query.h"
#include "search-query.h"
#include "search-query-proxy.h"
#include "search-metadata.h"
#include "result.h"
#include "preview-query.h"
#include "preview-query-proxy.h"
#include "event_queue.h"

ScopeBase::ScopeBase()
  : isolate_(v8::Isolate::GetCurrent()) {
}
ScopeBase::~ScopeBase() {
#if defined(SCOPE_JS_DELETE_CALLBACK)
#error "Duplicate SCOPE_JS_DELETE_CALLBACK definitions"
#endif

#define SCOPE_JS_DELETE_CALLBACK(cb) \
  do { if ( ! cb.IsEmpty()) cb.Reset(); } while(0)

  SCOPE_JS_DELETE_CALLBACK(start_callback_);
  SCOPE_JS_DELETE_CALLBACK(stop_callback_);
  SCOPE_JS_DELETE_CALLBACK(run_callback_);
  SCOPE_JS_DELETE_CALLBACK(search_callback_);
  SCOPE_JS_DELETE_CALLBACK(perform_action_callback_);

#undef SCOPE_JS_DELETE_CALLBACK
}

void ScopeBase::start(std::string const& scope_id) {
  if (start_callback_.IsEmpty()) {
    return;
  }

  EventQueue::instance().run(isolate_, [this, scope_id]
  {
    v8::Local<v8::Function> start_callback =
        v8cpp::to_local<v8::Function>(isolate_, start_callback_);

    v8cpp::call_v8(
        isolate_,
        start_callback,
        v8cpp::to_v8(isolate_, scope_id.c_str())
    );
  });
}

void ScopeBase::stop() {
  if (stop_callback_.IsEmpty()) {
    return;
  }

  EventQueue::instance().run(isolate_, [this]
  {
    v8::Local<v8::Function> stop_callback =
        v8cpp::to_local<v8::Function>(isolate_, stop_callback_);

    v8cpp::call_v8(
        isolate_,
        stop_callback
    );
  });
}

void ScopeBase::run() {
  if (run_callback_.IsEmpty()) {
    return;
  }

  EventQueue::instance().run(isolate_, [this]
  {
    v8::Local<v8::Function> run_callback =
        v8cpp::to_local<v8::Function>(isolate_, run_callback_);

    v8cpp::call_v8(
        isolate_,
        run_callback
    );
  });
}

unity::scopes::SearchQueryBase::UPtr ScopeBase::search(
      unity::scopes::CannedQuery const &query,
      unity::scopes::SearchMetadata const &metadata) {
  if (search_callback_.IsEmpty()) {
    return nullptr;
  }

  return EventQueue::instance().run<unity::scopes::SearchQueryBase::UPtr>(isolate_, [this, query, metadata]
  {
    // wrap & fire
    std::shared_ptr<CannedQuery> q(
        new CannedQuery(query));

    std::shared_ptr<SearchMetadata> m(
      new SearchMetadata(metadata));

    v8::Local<v8::Function> search_callback =
        v8cpp::to_local<v8::Function>(isolate_, search_callback_);

    v8::Handle<v8::Value> result =
      v8cpp::call_v8(
        isolate_,
        search_callback,
        v8cpp::to_v8(isolate_, q),
        v8cpp::to_v8(isolate_, m)
      );

    std::shared_ptr<SearchQuery> sq =
      v8cpp::from_v8<std::shared_ptr<SearchQuery>>(isolate_, result);

    if (!sq) {
      return unity::scopes::SearchQueryBase::UPtr(nullptr);
    }

    return unity::scopes::SearchQueryBase::UPtr(new SearchQueryProxy(sq));
  });
}

unity::scopes::ActivationQueryBase::UPtr ScopeBase::activate(
      unity::scopes::Result const &result,
      unity::scopes::ActionMetadata const &metadata) {
  return EventQueue::instance().run<unity::scopes::ActivationQueryBase::UPtr>(isolate_, [this]
  {
    return nullptr;
  });
}

unity::scopes::ActivationQueryBase::UPtr ScopeBase::perform_action(
      unity::scopes::Result const &result,
      unity::scopes::ActionMetadata const &metadata,
      std::string const &widget_id,
      std::string const &action_id) {
  if (perform_action_callback_.IsEmpty()) {
    return nullptr;
  }

  return EventQueue::instance().run<unity::scopes::ActivationQueryBase::UPtr>(
      isolate_,
      [this, result, metadata, widget_id, action_id] {

    std::shared_ptr<Result> r(new Result(result));
    std::shared_ptr<ActionMetaData> m(
        new ActionMetaData(metadata));

    v8::Local<v8::Function> perform_action_callback =
        v8cpp::to_local<v8::Function>(isolate_, perform_action_callback_);

    v8::Handle<v8::Value> wrapped_activation_query =
        v8cpp::call_v8(
          isolate_,
          perform_action_callback,
          v8cpp::to_v8(isolate_, r),
          v8cpp::to_v8(isolate_, m),
          widget_id,
          action_id
        );

    std::shared_ptr<ActivationQuery> aq =
      v8cpp::from_v8<std::shared_ptr<ActivationQuery>>(
          isolate_,
          wrapped_activation_query);
    if (!aq) {
      return unity::scopes::ActivationQueryBase::UPtr(nullptr);
    }

    return unity::scopes::ActivationQueryBase::UPtr(new ActivationQueryProxy(aq));
  });
}

unity::scopes::PreviewQueryBase::UPtr ScopeBase::preview(
      unity::scopes::Result const &result,
      unity::scopes::ActionMetadata const &action_metadata) {
  if (preview_callback_.IsEmpty()) {
    return nullptr;
  }

  return EventQueue::instance().run<unity::scopes::PreviewQueryBase::UPtr>(
      isolate_,
      [this, result, action_metadata]
  {
    // wrap & fire
    std::shared_ptr<Result> r(new Result(result));

    std::shared_ptr<ActionMetaData> m(
        new ActionMetaData(action_metadata));

    v8::Local<v8::Function> preview_callback =
        v8cpp::to_local<v8::Function>(isolate_, preview_callback_);

    v8::Handle<v8::Value> wrapped_preview =
        v8cpp::call_v8(
          isolate_,
          preview_callback,
          v8cpp::to_v8(isolate_, r),
          v8cpp::to_v8(isolate_, m)
        );

    // TODO watch out release
    std::shared_ptr<PreviewQuery> sq =
      v8cpp::from_v8<std::shared_ptr<PreviewQuery>>(
          isolate_,
          wrapped_preview);

    if (!sq) {
      return unity::scopes::PreviewQueryBase::UPtr(nullptr);
    }

    return unity::scopes::PreviewQueryBase::UPtr(new PreviewQueryProxy(sq));
  });
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

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  preview_callback_.Reset(args.GetIsolate(), cb);
}

void ScopeBase::onperform_action(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  perform_action_callback_.Reset(args.GetIsolate(), cb);
}

std::shared_ptr<Registry> ScopeBase::get_registry() const {
  return std::shared_ptr<Registry>(new Registry(registry()));
}
