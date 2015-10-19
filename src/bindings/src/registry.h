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
