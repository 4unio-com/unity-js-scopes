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

#ifndef _UNITY_JS_ONLINE_ACCOUNT_CLIENT_H_
#define _UNITY_JS_ONLINE_ACCOUNT_CLIENT_H_

#include <unity/scopes/CannedQuery.h>
#include <unity/scopes/OnlineAccountClient.h>

#include "result.h"
#include "preview-widget.h"
#include "event_queue.h"

#include <v8-cpp.h>

class OnlineAccountClient : public std::enable_shared_from_this<OnlineAccountClient>
{
 public:
  OnlineAccountClient(std::string const &service_name,
                      std::string const &service_type,
                      std::string const &provider_name);

  // v8 bindings
  void set_service_update_callback(v8::FunctionCallbackInfo<v8::Value> const& args);
  v8::Handle<v8::Value> get_service_statuses();
  void register_account_login_item(std::shared_ptr<Result> result,
                                   std::shared_ptr<unity::scopes::CannedQuery> canned_query,
                                   const std::string& login_passed_action,
                                   const std::string& login_failed_action);
  void register_account_login_widget(std::shared_ptr<PreviewWidget> preview_widget,
                                     const std::string& login_passed_action,
                                     const std::string& login_failed_action);
  void refresh_service_statuses();

 private:

  static void service_update_callback(std::shared_ptr<OnlineAccountClient> self,
                                      unity::scopes::OnlineAccountClient::ServiceStatus const&);

  v8::Persistent<v8::Function> service_update_callback_;

  std::unique_ptr<unity::scopes::OnlineAccountClient> oa_client_;

  v8::Isolate* isolate_;
};

#endif // _UNITY_JS_ONLINE_ACCOUNT_CLIENT_H_
