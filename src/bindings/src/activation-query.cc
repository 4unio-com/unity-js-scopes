/*
 * Copyright 2015-2016 Canonical Ltd.
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

ActivationQuery::ActivationQuery(v8::FunctionCallbackInfo<v8::Value> const& args)
    : unity::scopes::ActivationQueryBase(
          *v8cpp::from_v8<std::shared_ptr<Result>>(v8::Isolate::GetCurrent(), args[0]),
          *v8cpp::from_v8<std::shared_ptr<ActionMetaData>>(v8::Isolate::GetCurrent(), args[1]),
          v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[2]),
          v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[3])),
      isolate_(v8::Isolate::GetCurrent()) {

  if (args.Length() != 6) {
    throw std::runtime_error("Invalid number of arguments for activation query");
  }

  int arg_count = args.Length();
  if (   !args[arg_count-1]->IsFunction()
      || !args[arg_count-2]->IsFunction()) {
    throw std::runtime_error("Invalid argument: Function expected for activation query");
  }

  v8::Local<v8::Function> activate_callback =
    v8::Handle<v8::Function>::Cast(args[arg_count-2]);

  v8::Local<v8::Function> cancelled_callback =
    v8::Handle<v8::Function>::Cast(args[arg_count-1]);

  activate_callback_.Reset(args.GetIsolate(), activate_callback);
  cancelled_callback_.Reset(args.GetIsolate(), cancelled_callback);
}

ActivationQuery::~ActivationQuery() {
  if (!cancelled_callback_.IsEmpty()) {
    cancelled_callback_.Reset();
  }
  if (!activate_callback_.IsEmpty()) {
    activate_callback_.Reset();
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

unity::scopes::ActivationResponse ActivationQuery::activate() {
  if (activate_callback_.IsEmpty()) {
    return unity::scopes::ActivationResponse(
        unity::scopes::ActivationResponse::Status::NotHandled);
  }

  return EventQueue::instance().run<unity::scopes::ActivationResponse>(isolate_, [this]
  {
    v8::Local<v8::Function> activate_callback =
        v8cpp::to_local<v8::Function>(isolate_, activate_callback_);

    v8::Handle<v8::Value> wrapped_activation_response =
      v8cpp::call_v8_with_receiver(
        isolate_,
        v8cpp::to_v8(isolate_, shared_from_this()),
        activate_callback);

    std::shared_ptr<ActivationResponse> ar =
      v8cpp::from_v8<std::shared_ptr<ActivationResponse>>(
          isolate_,
          wrapped_activation_response);

    if (!ar) {
      // defaults to nothandled
      return unity::scopes::ActivationResponse(
          unity::scopes::ActivationResponse::Status::NotHandled);
    }

    return ar->get_activation_response();
  });
}

std::shared_ptr<ActionMetaData>
ActivationQuery::action_metadata() const {
  return std::shared_ptr<ActionMetaData>(
      new ActionMetaData(unity::scopes::ActivationQueryBase::action_metadata()));
}

std::shared_ptr<Result> ActivationQuery::result() const {
  return std::shared_ptr<Result>(
      new Result(unity::scopes::ActivationQueryBase::result()));
}

