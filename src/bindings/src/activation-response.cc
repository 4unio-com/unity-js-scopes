/*
 * Copyright 2016 Canonical Ltd.
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

#include "activation-response.h"

#include "event_queue.h"

ActivationResponse::ActivationResponse()
    : activation_response_(
          new unity::scopes::ActivationResponse(
              unity::scopes::ActivationResponse::Status::NotHandled)) {
}

ActivationResponse::ActivationResponse(
        v8::Local<v8::Value> const& arg) {
  if (arg->IsInt32()) {
    auto status = arg->ToInt32()->Value();
    activation_response_.reset(
        new unity::scopes::ActivationResponse(
            static_cast<unity::scopes::ActivationResponse::Status>(
                status)));
  } else {
    auto query =
        v8cpp::from_v8<std::shared_ptr<CannedQuery>>(
            v8::Isolate::GetCurrent(),
            arg);
    activation_response_.reset(
        new unity::scopes::ActivationResponse(
            query->canned_query()));
  }
}

int ActivationResponse::status() {
  return static_cast<int>(activation_response_->status());
}

std::shared_ptr<CannedQuery> ActivationResponse::query() const {
  return std::make_shared<CannedQuery>(activation_response_->query());
}

unity::scopes::Variant ActivationResponse::scope_data() const {
  return activation_response_->scope_data();
}

void ActivationResponse::set_scope_data(unity::scopes::Variant const& v) {
  activation_response_->set_scope_data(v);
}

unity::scopes::ActivationResponse
ActivationResponse::get_activation_response() const {
  return *activation_response_;
}
