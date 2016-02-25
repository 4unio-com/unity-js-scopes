/*
 * Copyright 2015, 2016 Canonical Ltd.
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

#include "online-account-client.h"
#include "event_queue.h"

OnlineAccountClient::OnlineAccountClient(
      std::string const &service_name,
      std::string const &service_type,
      std::string const &provider_name)
  : oa_client_(
      new unity::scopes::OnlineAccountClient(
        service_name,
        service_type,
        provider_name)),
    service_update_callback_set_(false),
    isolate_(v8::Isolate::GetCurrent()) {
}

void OnlineAccountClient::refresh_service_statuses() {
  oa_client_->refresh_service_statuses();
}

void OnlineAccountClient::setupServiceUpdateCallback() {
  if (service_update_callback_set_) {
    return;
  }
  service_update_callback_set_ = true;
  oa_client_->set_service_update_callback(
      std::bind(&OnlineAccountClient::service_update_callback,
                shared_from_this(),
                std::placeholders::_1)
  );
}

void OnlineAccountClient::set_service_update_callback(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  setupServiceUpdateCallback();

  if (args.Length() != 1 || !args[0]->IsFunction()) {
    throw std::runtime_error("Invalid argument: expecting a callback function");
  }

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  service_update_callback_.Reset(args.GetIsolate(), cb);
}

std::vector<unity::scopes::OnlineAccountClient::ServiceStatus>
OnlineAccountClient::get_service_statuses() {
  return oa_client_->get_service_statuses();
}

unity::scopes::OnlineAccountClient::PostLoginAction
post_login_action_from_string(const std::string& post_login_action) {
  if (post_login_action == "Unknown") {
    return unity::scopes::OnlineAccountClient::Unknown;
  }
  if (post_login_action == "DoNothing") {
    return unity::scopes::OnlineAccountClient::DoNothing;
  }
  if (post_login_action == "InvalidateResults") {
    return unity::scopes::OnlineAccountClient::InvalidateResults;
  }
  if (post_login_action == "ContinueActivation") {
    return unity::scopes::OnlineAccountClient::ContinueActivation;
  }
  throw std::runtime_error("Invalid PostLoginAction value");
}

void OnlineAccountClient::register_account_login_item(
      std::shared_ptr<Result> result,
      std::shared_ptr<CannedQuery> canned_query,
      const std::string& login_passed_action,
      const std::string& login_failed_action) {
  oa_client_->register_account_login_item(
      *result,
      canned_query->canned_query(),
      post_login_action_from_string(login_passed_action),
      post_login_action_from_string(login_failed_action));
}

void OnlineAccountClient::register_account_login_widget(
      std::shared_ptr<PreviewWidget> preview_widget,
      const std::string& login_passed_action,
      const std::string& login_failed_action) {
  oa_client_->register_account_login_item(
      preview_widget->preview_widget(),
      post_login_action_from_string(login_passed_action),
      post_login_action_from_string(login_failed_action));
}

void OnlineAccountClient::service_update_callback(
      std::shared_ptr<OnlineAccountClient> self,
      unity::scopes::OnlineAccountClient::ServiceStatus const& service_status) {
  if (self->service_update_callback_.IsEmpty()) {
    return;
  }

  using unity::scopes::OnlineAccountClient;

  EventQueue::instance().run(self->isolate_, [self, service_status]
  {
    v8::Local<v8::Function> service_update_callback =
        v8cpp::to_local<v8::Function>(
            self->isolate_,
            self->service_update_callback_);

    v8cpp::call_v8(
      self->isolate_,
      service_update_callback,
      std::shared_ptr<OnlineAccountClient::ServiceStatus>(
          new OnlineAccountClient::ServiceStatus(service_status))
    );
  });
}
