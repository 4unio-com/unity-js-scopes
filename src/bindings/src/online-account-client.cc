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

#include "online-account-client.h"


OnlineAccountClient::OnlineAccountClient(
      std::string const &service_name,
      std::string const &service_type,
      std::string const &provider_name,
      unity::scopes::OnlineAccountClient::MainLoopSelect main_loop_select)
  : oa_client_(
      new unity::scopes::OnlineAccountClient(
        service_name,
        service_type,
        provider_name,
        main_loop_select)),
    isolate_(v8::Isolate::GetCurrent()) {

  oa_client_->set_service_update_callback(
      std::bind(&OnlineAccountClient::service_update_callback,
                this,
                std::placeholders::_1)
  );
}

void OnlineAccountClient::refresh_service_statuses() {
  oa_client_->refresh_service_statuses();
}

void OnlineAccountClient::set_service_update_callback(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if ( ! service_update_callback_.IsEmpty()) {
    service_update_callback_.Reset();
  }

  if (args.Length() != 1 || !args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  if (service_update_callback_.IsEmpty()) {
    service_update_callback_.Reset();
  }

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  service_update_callback_.Reset(args.GetIsolate(), cb);
}

v8::Handle<v8::Value> OnlineAccountClient::get_service_statuses() {
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
      std::shared_ptr<unity::scopes::CannedQuery> canned_query,
      const std::string& login_passed_action,
      const std::string& login_failed_action) {
  oa_client_->register_account_login_item(
      *result,
      *canned_query,
      post_login_action_from_string(login_passed_action),
      post_login_action_from_string(login_failed_action));
}

void OnlineAccountClient::register_account_login_widget(
      std::shared_ptr<PreviewWidget> preview_widget,
      const std::string& login_passed_action,
      const std::string& login_failed_action) {
  oa_client_->register_account_login_item(
      *preview_widget,
      post_login_action_from_string(login_passed_action),
      post_login_action_from_string(login_failed_action));
}

v8::Handle<v8::Object>
service_status_to_json(
      v8::Isolate* isolate,
      unity::scopes::OnlineAccountClient::ServiceStatus service_status) {
  v8::Handle<v8::Object> o = v8::Object::New(isolate);

  o->Set(v8::String::NewFromUtf8(isolate, "account_id"),
         v8::Number::New(isolate, service_status.account_id));

  o->Set(v8::String::NewFromUtf8(isolate, "service_enabled"),
         v8::Boolean::New(isolate, service_status.service_enabled));

  o->Set(v8::String::NewFromUtf8(isolate, "service_authenticated"),
         v8::Boolean::New(isolate, service_status.service_authenticated));

  o->Set(v8::String::NewFromUtf8(isolate, "client_id"),
         v8::String::NewFromUtf8(isolate, service_status.client_id.c_str()));

  o->Set(v8::String::NewFromUtf8(isolate, "client_secret"),
         v8::String::NewFromUtf8(isolate, service_status.client_secret.c_str()));

  o->Set(v8::String::NewFromUtf8(isolate, "access_token"),
         v8::String::NewFromUtf8(isolate, service_status.access_token.c_str()));

  o->Set(v8::String::NewFromUtf8(isolate, "token_secret"),
         v8::String::NewFromUtf8(isolate, service_status.token_secret.c_str()));

  o->Set(v8::String::NewFromUtf8(isolate, "error"),
         v8::String::NewFromUtf8(isolate, service_status.error.c_str()));

  return o;
}

void OnlineAccountClient::service_update_callback(
      OnlineAccountClient *self,
      unity::scopes::OnlineAccountClient::ServiceStatus const& service_status) {
  if (self->service_update_callback_.IsEmpty()) {
    return;
  }

  v8::Local<v8::Function> service_update_callback =
    v8cpp::to_local<v8::Function>(self->isolate_, self->service_update_callback_);

  v8cpp::call_v8(
      self->isolate_,
      service_update_callback,
      service_status_to_json(self->isolate_, service_status)
  );
}
