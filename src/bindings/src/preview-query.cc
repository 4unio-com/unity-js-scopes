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

#include "preview-query.h"
#include "preview-reply.h"
#include "event_queue.h"

PreviewQuery::PreviewQuery(
      std::shared_ptr<Result> result,
      std::shared_ptr<ActionMetaData> metadata,
      const v8::Local<v8::Function> &run_callback,
      const v8::Local<v8::Function> &cancelled_callback)
  : unity::scopes::PreviewQueryBase(*result, *metadata),
    isolate_(v8::Isolate::GetCurrent()),
    run_callback_(v8::Isolate::GetCurrent(), run_callback),
    cancelled_callback_(v8::Isolate::GetCurrent(), cancelled_callback) {
}

PreviewQuery::~PreviewQuery() {
  if (!run_callback_.IsEmpty()) {
    run_callback_.Reset();
  }
  if (!cancelled_callback_.IsEmpty()) {
    cancelled_callback_.Reset();
  }
}

void PreviewQuery::run(unity::scopes::PreviewReplyProxy const& reply) {
  if (run_callback_.IsEmpty()) {
    return;
  }

  EventQueue::instance().run(isolate_, [this, reply]
  {
    std::shared_ptr<PreviewReply> r =
      std::shared_ptr<PreviewReply>(new PreviewReply(reply));

    v8::Local<v8::Function> run_callback =
        v8cpp::to_local<v8::Function>(isolate_, run_callback_);

    v8cpp::call_v8_with_receiver(
        isolate_,
        v8cpp::to_v8(isolate_, shared_from_this()),
        run_callback,
        v8cpp::to_v8(isolate_, r)
    );
  });
}

void PreviewQuery::cancelled() {
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

std::shared_ptr<ActionMetaData>
PreviewQuery::action_metadata() const {
  return std::shared_ptr<ActionMetaData>(
      new ActionMetaData(unity::scopes::PreviewQueryBase::action_metadata()));
}

std::shared_ptr<Result> PreviewQuery::result() const {
  return std::shared_ptr<Result>(
      new Result(unity::scopes::PreviewQueryBase::result()));
}
