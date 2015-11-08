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

#include <unity/scopes/OnlineAccountClient.h>

#include "canned-query.h"
#include "result.h"
#include "preview-widget.h"
#include "event_queue.h"

#include <v8-cpp.h>

/**

--doc:class OnlineAccountClient
 * 
 * A simple interface for integrating online accounts access and monitoring into scopes.
 * 
 * @module ScopeJS
 * @class OnlineAccountClient
--/doc:class

--doc:constructor
 * 
 * @constructor
 * @param service_name {String} The name of the service (E.g. "com.ubuntu.scopes.youtube_youtube")
 * @param service_type {String} The type of service (E.g. "sharing")
 * @param provider_name {String} The name of the service provider (E.g. "google")
--/doc:constructor

--doc:prototype OnlineAccountClient

--doc:member
 * Get statuses for all services matching the name, type and provider specified on construction
 * @method get_service_statuses
 * @return {Array of OnlineAccountClientServiceStatus} list of service statuses
--doc:/member
get_service_statuses: function() {
}
--/doc:member

--doc:member
 * Refresh all service statuses
 * WARNING: If a service update callback is set, this method will invoke that callback for each service monitored. Therefore, DO NOT call this method from within your callback function!
 * @method refresh_service_statuses
--doc:/member
refresh_service_statuses: function() {
}
--/doc:member

--doc:member
 * Register a result item that requires the user to be logged in.
 * @param result {Result} The result item that needs account access
 * @param query {CannedQuery} The scope's current query
 * @param login_passed_action {PostLoginAction} The action to take upon successful login
 * @param login_failed_action {PostLoginAction} The action to take upon unsuccessful login
 * @method register_account_login_item
--doc:/member
refresh_account_login_item: function(result, query, login_passed_action, login_failed_action) {
}
--/doc:member

--doc:member
 * Refresh all service statuses
 * @method register_account_login_item
 * @param widget {PreviewWidget} The widget item that needs account access
 * @param login_passed_action {PostLoginAction} The action to take upon successful login
 * @param login_failed_action {PostLoginAction} The action to take upon unsuccessful login
--doc:/member
register_account_login_item: function(widget, login_passed_action, login_failed_action) {
}
--/doc:member

--doc:member
 * Set the callback function to be invoked when a service status changes
 * @method set_service_update_callback
 * @param {Function(OnlineAccountServiceStatus)} callback
--doc:/member
set_service_update_callback: function(callback) {
}
--/doc:member

--/doc:prototype

 */

class OnlineAccountClient : public std::enable_shared_from_this<OnlineAccountClient>
{
 public:
  OnlineAccountClient(std::string const &service_name,
                      std::string const &service_type,
                      std::string const &provider_name);

  // v8 bindings
  void set_service_update_callback(v8::FunctionCallbackInfo<v8::Value> const& args);
  std::vector<unity::scopes::OnlineAccountClient::ServiceStatus> get_service_statuses();
  void register_account_login_item(std::shared_ptr<Result> result,
                                   std::shared_ptr<CannedQuery> canned_query,
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
