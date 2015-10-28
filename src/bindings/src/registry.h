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

#ifndef _UNITY_JS_REGISTRY_H_
#define _UNITY_JS_REGISTRY_H_

#include <unity/scopes/Registry.h>

#include <v8-cpp.h>

/**

--doc:class Registry
 * 
 * White pages service for available scopes
 * 
 * @module ScopeJS
 * 
 * @class Registry
--/doc:class

--doc:prototype Registry

--doc:member
 * Returns the metadata for the scope with the given ID
 * @method get_metadata
 * @param id {String} Attribute definition
 * @return {ScopeMetadata}
--doc:/member
get_metadata: function(id) {
}
--/doc:member

--doc:member
 * Returns a map containing the metadata for all scopes
 * @method list
 * @return {Dictionary of String -> ScopeMetadata}
--doc:/member
list: function() {
}
--/doc:member

--doc:member
 * Returns a map containing only those scopes for which predicate returns true
 * @method list_if
 * @param predicate {Function(ScopeMetadata)} a function that must return true for each metadata item to be included in the map.
 * @return {Dictionary of String -> ScopeMetadata}
--doc:/member
list_if: function(predicate) {
}
--/doc:member

--doc:member
 * Returns whether a scope is currently running or not
 * @method is_scope_running
 * @param scope_id {String} The ID of the scope from which we wish to retrieve state
 * @return {Boolean} True if the scope is running, and False if it is not running
--doc:/member
is_scope_running: function(scope_id) {
}
--/doc:member

--doc:member
 * Assigns a callback method to be executed when a scope's running state (started / stopped) changes
 * @method set_scope_state_callback
 * @param scope_id {String} The ID of the scope from which we wish to retrieve state changes
 * @param callback {Function(is_running: Boolean)} The function that is invoked when a scope changes running state
--doc:/member
set_scope_state_callback: function(scope_id, callback) {
}
--/doc:member

--doc:member
 * Assigns a callback method to be executed when the registry's scope list changes
 * 
 * Note: Upon receiving this callback, you should retrieve the updated scopes list via the list() method if you wish to retain synchronisation between client and server
 * @method set_list_update_callback
 * @param callback {Function()} The function that is invoked when an update occurs
--doc:/member
set_list_update_callback: function(callback) {
}
--/doc:member

--/doc:prototype
 */

class Registry : public std::enable_shared_from_this<Registry>
{
 public:
  Registry(unity::scopes::RegistryProxy proxy);

  unity::scopes::ScopeMetadata get_metadata(std::string const &scope_id);
  unity::scopes::MetadataMap list();
  unity::scopes::MetadataMap list_if(v8::Local<v8::Function> predicate);
  bool is_scope_running(const std::string& scope_id);
  void set_scope_state_callback(const std::string& scope_id,
                                v8::Local<v8::Function> callback);
  void set_list_update_callback(v8::Local<v8::Function> callback);

 private:

  v8::Isolate * isolate_;
  unity::scopes::RegistryProxy proxy_;
};

#endif // _UNITY_IS_REGISTRY_
