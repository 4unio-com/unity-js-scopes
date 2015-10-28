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

#ifndef _UNITY_JS_CATEGORISED_RESULT_H_
#define _UNITY_JS_CATEGORISED_RESULT_H_

#include <unity/scopes/CategorisedResult.h>

#include <v8-cpp.h>

/**

--doc:class CategorisedResult
 * 
 * A result, including the category it belongs to.
 * 
 * @module ScopeJS
 * @class CategorisedResult
--/doc:class

--doc:constructor
 *
 * @constructor
 * @param category The category for the result.
--/doc:constructor

--doc:prototype CategorisedResult

--doc:member
 * Updates the category of this result.
 * @method set_category
 * @param category The category for the result.
--doc:/member
set_category: function(Category: category) {
}
--/doc:member

--doc:member
 * Get the category instance this result belongs to.
 * @method category
 * @return {Category} The category instance.
--doc:/member
category: function() {
}
--/doc:member

--doc:member
 * This method is meant to be used by aggregator scopes which want to modify
 * results they receive, but want to keep a copy of the original result so
 * that they can be correctly handled by the original scopes
 * who created them when it comes to activation or previews.
 * Scopes middleware will automatically pass the correct inner stored result
 * to the activation or preview request handler
 * 
 * @method store
 * @param {Result} The original result to store within this result.
 * @param {Boolean} intercept_activation True if this scope should receive activation and preview requests.
--doc:/member
store: function({Result}: result, {Boolean}: intercept_activation) {
}
--/doc:member

--doc:member
 * Check if this Result instance has a stored result.
 * @method has_stored_result
 * @return {Boolean} True if there is a stored result
--doc:/member
has_stored_result: function() {
}
--/doc:member

--doc:member
 * Get a stored result.
 * @method retrieve
 * @return {Result} stored result
--doc:/member
retrieve: function() {
}
--/doc:member

--doc:member
 * Set the "uri" attribute of this result.
 * @method set_uri
 * @param uri {String}
--doc:/member
set_uri: function(uri) {
}
--/doc:member

--doc:member
 * Set the "title" attribute of this result.
 * @method set_title
 * @param title {String}
--doc:/member
set_title: function(title) {
}
--/doc:member

--doc:member
 * Set the "art" attribute of this result.
 * @method set_art
 * @param art {String}
--doc:/member
set_art: function(art) {
}
--/doc:member

--doc:member
 * Set the "dnd_uri" attribute of this result.
 * @method set_dnd_uri
 * @param dnd_uri {String}
--doc:/member
set_dnd_uri: function(dnd_uri) {
}
--/doc:member

--doc:member
 * Indicates to the receiver that this scope should intercept
 * activation requests for this result.
 * By default, a scope receives preview requests for the results it
 * creates, but does not receive activation requests (they are handled
 * directly by the shell). Intercepting activation implies intercepting
 * preview requests as well; this is important for scopes that forward
 * results from other scopes and call set_intercept_activation() on these scopes.
 * A scope that sets intercept activation flag for a result should re-implement
 * Scope.activate() and provide an implementation of ActivationQuery that
 * handles the actual activation. If not called, the result will be activated
 * directly by the Unity shell whithout involving the scope, assuming an appropriate
 * URI schema handler is present on the system.
 * 
 * @method set_intercept_activation
--doc:/member
set_intercept_activation: function() {
}
--/doc:member

--doc:member
 * Check if this result should be activated directly by the shell
 * because the scope doesn't handle activation of this result.
 * @method direct_activation
 * @return {Boolean} True if this result needs to be activated directly.
--doc:/member
direct_activation: function() {
}
--/doc:member

--doc:member
 * Get the "uri" property of this Result.
 * This method returns an empty string if this attribute is not of type String.
 * @method uri
 * @return {String} The value of "uri" or the empty string.
--doc:/member
uri: function() {
}
--/doc:member

--doc:member
 * Get the "title" property of this Result.
 * This method returns an empty string if this attribute is not of type String.
 * @method title
 * @return {String} The value of "title" or the empty string.
--doc:/member
title: function() {
}
--/doc:member

--doc:member
 * Get the "art" property of this Result.
 * This method returns an empty string if this attribute is not of type String.
 * @method art
 * @return {String} The value of "art" or the empty string.
--doc:/member
art: function() {
}
--/doc:member

--doc:member
 * Get the "dnd_uri" property of this Result.
 * This method returns an empty string if this attribute is not of type String.
 * @method dnd_uri
 * @return {String} The value of "dnd_uri" or the empty string.
--doc:/member
dnd_uri: function() {
}
--/doc:member

--doc:member
 * Check if this Result has an attribute.
 * @method contains
 * @param key The attribute name.
 * @return {Boolean} True if the attribute is set.
--doc:/member
contains: function(key) {
}
--/doc:member

--doc:member
 * Check if this result is an online account login result.
 * @method is_account_login_result
 * @return {Boolean} True if this result is an online account login result.
--doc:/member
is_account_login_result: function() {
}
--/doc:member

--doc:member
 * Gets the value of a custom metadata attribute.
 * @method get
 * @param key {String} The name of the attribute.
 * @return Attribute value or null
--doc:/member
get: function(key) {
}
--/doc:member

--doc:member
 * Sets the value of a custom metadata attribute.
 * @method set
 * @param key {String} The name of the attribute.
 * @param value The value of the attribute.
--doc:/member
set: function(key, value) {
}
--/doc:member

--/doc:prototype

 */

class CategorisedResult : public unity::scopes::CategorisedResult
{
 public:
  CategorisedResult(unity::scopes::CategorisedResult const &categorised_result);
  CategorisedResult(unity::scopes::Category::SCPtr category);
  
  // v8 bindings
  void set(v8::FunctionCallbackInfo<v8::Value> const& args);
  v8::Handle<v8::Value> get(const std::string& key);

  unity::scopes::Category::SCPtr category() const;
  void set_category(unity::scopes::Category::SCPtr category);
};

#endif // _UNITY_JS_CATEGORISED_RESULT_H_
