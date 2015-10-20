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

#ifndef _UNITY_JS_ACTION_METADATA_H_
#define _UNITY_JS_ACTION_METADATA_H_

#include <unity/scopes/ActionMetadata.h>

#include <v8-cpp.h>

/**

--doc:class ActionMetadata
 * @module ScopeJS
 * 
 * Metadata passed to scopes for preview and activation
 * 
 * @class ActionMetadata
--/doc:class

--doc:prototype ActionMetadata
--doc:member
 * Check if this ActionMetadata has a hint
 * @method contains_hint
 * @param hint {String}
 * @return Boolean
--doc:/member
contains_hint: function(hint) {
}
--/doc:member

--doc:member
 * Set the value of an attribute
 * @method set
 * @param key {String}
 * @param value {String}, {Number} or {Object}
--doc:/member
set: function(key, value) {
}
--/doc:member

--doc:member
 * Get the value of an attribute
 * @method get
 * @param key {String}
 * @return {String}, {Number} or {Object}
--doc:/member
get: function(key) {
}
--/doc:member

--/doc:prototype

 */

class ActionMetaData : public unity::scopes::ActionMetadata
{
 public:
  ActionMetaData(unity::scopes::ActionMetadata const &action_metadata);
  ActionMetaData(std::string const &locale,
                 std::string const &form_factor);
  ~ActionMetaData();

  // unity::scopes::ActionMetadata extra v8 bindings
  unity::scopes::Variant get(const std::string& key);
  void set(const std::string& key, const unity::scopes::Variant& val);
};

#endif // _UNITY_JS_ACTION_METADATA_H_
