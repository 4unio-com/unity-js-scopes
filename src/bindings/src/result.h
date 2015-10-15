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

#ifndef _UNITY_JS_RESULT_H_
#define _UNITY_JS_RESULT_H_

#include <unity/scopes/Result.h>

#include <v8-cpp.h>

#include "common.h"

/**

--doc:class Result
 * The attributes of a result returned by a Scope
 * 
 * The Result API provides convenience methods for some typical attributes (title, art), but scopes are free to add and use any custom attributes with set/get methods. The only required attribute is 'uri' and it must not be empty before calling Reply.push().
 *
 * @class Result
--/doc:class

--doc:prototype Result

--doc:member
 * Check if this Result instance has a stored result
 * @return Boolean
--doc:/member
has_stored_result: function() {
}
--/doc:member

--doc:member
 * Get a stored result
 * @return Result
--doc:/member
retrieve: function() {
}
--/doc:member

--doc:member
 * Set the "uri" attribute of this result.
 * @param uri String
--doc:/member
set_uri: function(String: uri) {
}
--/doc:member

--doc:member
 * Set the "title" attribute of this result.
 * @param title String
--doc:/member
set_title: function(String: title) {
}
--/doc:member

--doc:member
 * Set the "art" attribute of this result.
 * @param art String
--doc:/member
set_art: function(String: art) {
}
--/doc:member

--doc:member
 * Set the "dnd_uri" attribute of this result.
 * @param dnd_uri String
--doc:/member
set_dnd_uri: function(String: dnd_uri) {
}
--/doc:member

--doc:member
 * Indicates to the receiver that this scope should intercept activation requests for this result
--doc:/member
set_intercept_activation: function() {
}
--/doc:member

--doc:member
 * Check if this result should be activated directly by the shell because the scope doesn't handle activation of this result
 * @return Boolean
--doc:/member
direct_activation: function() {
}
--/doc:member

--doc:member
 * Get the "uri" property of this Result
 * @return String
--doc:/member
uri: function() {
}
--/doc:member

--doc:member
 * Get the "title" property of this Result
 * @return String
--doc:/member
title: function() {
}
--/doc:member

--doc:member
 * Get the "art" property of this Result
 * @return String
--doc:/member
art: function() {
}
--/doc:member

--doc:member
 * Get the "dnd_uri" property of this Result
 * @return String
--doc:/member
dnd_uri: function() {
}
--/doc:member

--doc:member
 * Check if this Result has an attribute
 * @return Boolean
--doc:/member
contains: function() {
}
--/doc:member

--doc:member
 * Get the value of an attribute
 * @param value String
 * @return Dictonary
--doc:/member
value: function(String: value) {
}
--/doc:member

--doc:member
 * Set the value of an attribute
 * @param key String
 * @param value String
--doc:/member
set: function(String: key, String: value) {
}
--/doc:member

--doc:member
 * Get the value of an attribute
 * @param key String
 * @return String, Number or Object
--doc:/member
get: function(String: key) {
}
--/doc:member

--/doc:prototype

 */

class Result : public unity::scopes::Result
{
 public:
  Result(unity::scopes::Result const &result);

  // v8 bindings
  std::shared_ptr<Result> retrieve_stored_result() const;
  void store(std::shared_ptr<Result> result, bool intercept_activation);

  void set(v8::FunctionCallbackInfo<v8::Value> const& args);
  v8::Handle<v8::Value> get(const std::string& key);
};

#endif // _UNITY_JS_RESULT_H_
