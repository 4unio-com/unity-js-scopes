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

#include "activation-query.h"

#include "event_queue.h"

ActivationQuery::ActivationQuery(
      unity::scopes::Result const& result,
      unity::scopes::ActionMetadata const& metadata,
      const v8::Local<v8::Function> &cancelled_callback)
    : unity::scopes::ActivationQueryBase(result, metadata),
      isolate_(v8::Isolate::GetCurrent()),
      cancelled_callback_(v8::Isolate::GetCurrent(), cancelled_callback) {
}

ActivationQuery::~ActivationQuery() {
  if (!cancelled_callback_.IsEmpty()) {
    cancelled_callback_.Reset();
  }
}

void ActivationQuery::cancelled() {
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

v8::Local<v8::Value>
ActivationQuery::activate(v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(isolate_, nullptr);
  //   unity::scopes::ActivationResponse 
}

