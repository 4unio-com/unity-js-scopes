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

#include "search-metadata.h"
#include "search-reply.h"
#include "event_queue.h"

SearchQuery::SearchQuery(
      std::shared_ptr<unity::scopes::CannedQuery> query,
      std::shared_ptr<unity::scopes::SearchMetadata> metadata,
      const v8::Local<v8::Function> &run_callback,
      const v8::Local<v8::Function> &cancelled_callback)
  : unity::scopes::SearchQueryBase(*query, *metadata),
    isolate_(v8::Isolate::GetCurrent()),
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

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  run_callback_.Reset(args.GetIsolate(), cb);
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

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  cancelled_callback_.Reset(args.GetIsolate(), cb);
}

void SearchQuery::run(unity::scopes::SearchReplyProxy const& reply) {
  if (run_callback_.IsEmpty()) {
    return;
  }

  EventQueue::instance().run(isolate_, [this, reply]
  {
    // wrap & fire
    std::shared_ptr<SearchReply> sr =
      std::shared_ptr<SearchReply>(new SearchReply(reply));

    v8::Local<v8::Function> run_callback =
      v8cpp::to_local<v8::Function>(isolate_, run_callback_);

    v8cpp::call_v8_with_receiver(
        isolate_,
        v8cpp::to_v8(isolate_, shared_from_this()),
        run_callback,
        v8cpp::to_v8(isolate_, sr)
    );
  });
}

void SearchQuery::cancelled() {
  if (cancelled_callback_.IsEmpty()) {
    return;
  }

  EventQueue::instance().run(isolate_, [this]
  {
    v8::Local<v8::Function> cancelled_callback =
        v8cpp::to_local<v8::Function>(isolate_, cancelled_callback_);

    v8cpp::call_v8_with_receiver(
        isolate_,
        v8cpp::to_v8(isolate_, shared_from_this()),
        cancelled_callback
    );
  });
}
