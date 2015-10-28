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

#ifndef _UNITY_JS_SEARCH_METADATA_H_
#define _UNITY_JS_SEARCH_METADATA_H_

#include <unity/scopes/SearchMetadata.h>

#include <v8-cpp.h>

/**

--doc:class SearchMetadata
 * 
 * Metadata passed with search requests.
 * 
 * Two forms of construction are allowed depending on the number
 * and types of the parameters:
 *  - with locale and form factor
 *  or
 *  - with cardinality, locale, and form factor.
 *
 * @module ScopeJS
 * @class SearchMetadata
--/doc:class

--doc:constructor
 * 
 * @constructor
 * @param cardinality maximum number of search results
 * @param locale locale string, eg. en_EN
 * @param form_factor form factor name, e.g. phone, desktop, phone-version etc.
 * @param category The category for the result.
--/doc:constructor

--doc:prototype SearchMetadata

--doc:member
 * Set cardinality.
 * @method set_cardinality
 * @param cardinality {Int}
--doc:/member
set_cardinality: function(cardinality) {
}
--/doc:member

--doc:member
 * Get cardinality.
 * @method cardinality
 * @return {Int}
--doc:/member
cardinality: function() {
}
--/doc:member

--doc:member
 * Set location.
 * @method set_location
 * @param location {Location} data
--doc:/member
set_location: function(location) {
}
--/doc:member

--doc:member
 * Get location.
 * @method location
 * @return {Location} data representing the current location, including attributes such as city and country.
--doc:/member
location: function() {
}
--/doc:member

--doc:member
 * Does the SearchMetadata have a location.
 * @method has_location
 * @return {Boolean} True if there is a location property.
--doc:/member
has_location: function() {
}
--/doc:member

--doc:member
 * Remove location data entirely.
 * This method does nothing if no location data is present.
 * @method remove_location
--doc:/member
remove_location: function() {
}
--/doc:member

--doc:member
 * Set the list of scope keywords used to initiate this search request.
 * @method set_aggregated_keywords
 * @param aggregated_keywords {Array of String} The list of scope keywords used to initiate this search request.
--doc:/member
set_aggregated_keywords: function() {
}
--/doc:member

--doc:member
 * Get the list of scope keywords used to initiate this search request.
 * @method aggregated_keywords
 * @return {Array of String} The list of scope keywords used to initiate this search request.
--doc:/member
aggregated_keywords: function() {
}
--/doc:member

--doc:member
 * Check if this search request originated from an aggregator scope.
 * @method is_aggregated
 * @return {Boolean} True if this search request originated from an aggregator scope.
--doc:/member
is_aggregated: function() {
}
--/doc:member

--doc:member
 * Sets a hint.
 * @method set_hint
 * @param key {String} The name of the hint.
 * @param value Hint value
--doc:/member
set_hint: function(key, value) {
}
--/doc:member

--doc:member
 * Get all hints.
 * @method hints
 * @return {Dictionary}
--doc:/member
hints: function() {
}
--/doc:member

--doc:member
 * Check if this SearchMetadata has a hint.
 * @method contains_hint
 * @param key {String} The hint name.
 * @return {Boolean} True if the hint is set.
--doc:/member
contains_hint: function(key) {
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

--doc:member
 * Get the form factor string.
 * @method form_factor
 * @return The form factor string
--doc:/member
form_factor: function() {
}
--/doc:member

--doc:member
 * Get the locale string.
 * @method locale
 * @return The locale string
--doc:/member
locale: function() {
}
--/doc:member

--doc:member
 * Get internet connectivity status.
 * @method internet_connectivity
 * @return {ConnectivityStatus} The internet connectivity status.
--doc:/member
internet_connectivity: function() {
}
--/doc:member

--doc:member
 * Set internet connectivity status.
 * @method set_internet_connectivity
 * @param {ConnectivityStatus} The internet connectivity status.
--doc:/member
set_internet_connectivity: function(connectivity_status) {
}
--/doc:member

--/doc:prototype

 */

class SearchMetadata
{
 public:
  SearchMetadata(v8::FunctionCallbackInfo<v8::Value> const& args);
  SearchMetadata(const unity::scopes::SearchMetadata&);

  void set_cardinality(int cardinality);
  int cardinality() const;
  bool has_location() const;
  void remove_location();
  void set_aggregated_keywords(std::set<std::string> const& aggregated_keywords);
  std::set<std::string> aggregated_keywords() const;
  bool is_aggregated() const;
  void set_hint(std::string const& key, v8::Local<v8::Value> value);
  v8::Local<v8::Value> hints() const;
  void set(const std::string& k, v8::Local<v8::Value> value);
  v8::Local<v8::Value> get(const std::string& k);
  void set_location(const unity::scopes::Location& location);
  unity::scopes::Location location() const;

  std::string locale() const;
  std::string form_factor() const;
  void set_internet_connectivity(const std::string& internet_connectivity);
  std::string internet_connectivity() const;

  std::shared_ptr<unity::scopes::SearchMetadata> metadata();

 private:
  std::shared_ptr<unity::scopes::SearchMetadata> metadata_;
};

#endif // _UNITY_JS_SEARCH_METADATA_H_
