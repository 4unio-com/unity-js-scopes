/*
 * Copyright 2016 Canonical Ltd.
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

#ifndef _UNITY_JS_VALUE_SLIDE_FILTER_H_
#define _UNITY_JS_VALUE_SLIDE_FILTER_H_

#include <unity/scopes/RangeInputFilter.h>

#include <v8-cpp.h>

#include "filter-group.h"


/**

--doc:class RangeInputFilter
 * 
 * A range filter allows a start and end value to be entered by the user.
 * 
 * A RangeInputFilter is composed of two input boxes that accept numeric
 * values (both of them optional).
 * The filter can have prefix and/or postfix labels for the start and end
 * value, respectively, plus a single label that is displayed between the two input boxes.
 * The filter can provide defaults for that start and end value, which are
 * used by the UI if the user does not enter explicit values.
 *
 * @module ScopeJS
 * @class RangeInputFilter
--/doc:class

--doc:constructor
 * Creates a RangeInputFilter
 *
 * @constructor
 * @param {String} id A unique identifier for the filter that can be used to later identify it among several filters.
 * @param {String} start_prefix_label A display label for the input box for the start value, displayed to the left (can be empty).
 * @param {String} start_postfix_label A display label for the input box for the start value, displayed to the right (can be empty).
 * @param {String} central_label A display label displayed between the two input boxes (can be empty).
 * @param {String} end_prefix_label A display label for the input box for the end value, displayed to the left (can be empty).
 * @param {String} end_postfix_label A display label for the input box for the end value, displayed to the right (can be empty).
--/doc:constructor

--doc:constructor
 * Creates a RangeInputFilter with specific default values for start and end
 *
 * @constructor
 * @param {String} id A unique identifier for the filter that can be used to later identify it among several filters.
 * @param {Number} default_start_value The default start value or null.
 * @param {Number} default_end_value The default end value or null.
 * @param {String} start_prefix_label A display label for the input box for the start value, displayed to the left (can be empty).
 * @param {String} start_postfix_label A display label for the input box for the start value, displayed to the right (can be empty).
 * @param {String} central_label A display label displayed between the two input boxes (can be empty).
 * @param {String} end_prefix_label A display label for the input box for the end value, displayed to the left (can be empty).
 * @param {String} end_postfix_label A display label for the input box for the end value, displayed to the right (can be empty).
--/doc:constructor

--doc:constructor
 * Creates a RangeInputFilter inside a FilterGroup
 *
 * @constructor
 * @param {String} id A unique identifier for the filter that can be used to later identify it among several filters.
 * @param {String} start_prefix_label A display label for the input box for the start value, displayed to the left (can be empty).
 * @param {String} start_postfix_label A display label for the input box for the start value, displayed to the right (can be empty).
 * @param {String} central_label A display label displayed between the two input boxes (can be empty).
 * @param {String} end_prefix_label A display label for the input box for the end value, displayed to the left (can be empty).
 * @param {String} end_postfix_label A display label for the input box for the end value, displayed to the right (can be empty).
 * @param {FilterGroup} filter_group The filter group associated with this filter.
--/doc:constructor

--doc:constructor
 * Creates a RangeInputFilter with specific default values for start and end,
 * inside a FilterGroup
 *
 * @constructor
 * @param {String} id A unique identifier for the filter that can be used to later identify it among several filters.
 * @param {Number} default_start_value The default start value or null.
 * @param {Number} default_end_value The default end value or null.
 * @param {String} start_prefix_label A display label for the input box for the start value, displayed to the left (can be empty).
 * @param {String} start_postfix_label A display label for the input box for the start value, displayed to the right (can be empty).
 * @param {String} central_label A display label displayed between the two input boxes (can be empty).
 * @param {String} end_prefix_label A display label for the input box for the end value, displayed to the left (can be empty).
 * @param {String} end_postfix_label A display label for the input box for the end value, displayed to the right (can be empty).
 * @param {FilterGroup} filter_group The filter group associated with this filter.
--/doc:constructor

--doc:prototype RangeInputFilter

--doc:member
 * Sets display hints for the Shell UI
 * @method set_display_hints
 * @param hints {DisplayHints} A combination of DisplayHints for this filter.
--doc:/member
set_display_hints: function(hints) {
}
--/doc:member

--doc:member
 * Get display hints of this filter
 * @method display_hints
 * @return {DisplayHints} Display hints flags
--doc:/member
display_hints: function() {
}
--/doc:member

--doc:member
 * Set an optional title of this filter
 * @method set_title
 * @param title {String} The title.
--doc:/member
set_title: function(title) {
}
--/doc:member

--doc:member
 * Get the optional title of this filter
 * @method title
 * @return {String} The title (possibly empty)
--doc:/member
title: function() {
}
--/doc:member

--doc:member
 * Get the identifier of this filter
 * @method id
 * @return {String} identifier of this filter
--doc:/member
id: function() {
}
--/doc:member

--doc:member
 * Get the type name of this filter
 * @method filter_type
 * @return {String} type name of this filter
--doc:/member
filter_type: function() {
}
--/doc:member

--doc:member
 * Get the filter group this filter belongs to
 * @method filter_group
 * @return {FilterGroup} The filter group (or null)
--doc:/member
filter_group: function() {
}
--/doc:member



--doc:member
 * Get the prefix label of start value
 * @method start_prefix_label
 * @return {String} The prefix label of start value
--doc:/member
start_prefix_label: function() {
}
--/doc:member

--doc:member
 * Get the postfix label of start value
 * @method start_postfix_label
 * @return {String} The postfix label of start value
--doc:/member
start_postfix_label: function() {
}
--/doc:member

--doc:member
 * Get the postfix label of end value
 * @method end_postfix_label
 * @return {String} The postfix label of end value
--doc:/member
end_postfix_label: function() {
}
--/doc:member

--doc:member
 * Get the prefix label of end value
 * @method end_prefix_label
 * @return {String} The prefix label of end value
--doc:/member
end_prefix_label: function() {
}
--/doc:member

--doc:member
 * Get the central label for this filter
 * @method central_label
 * @return {String} The central label of end value
--doc:/member
central_label: function() {
}
--/doc:member

--doc:member
 * Check if filter state holds an start value for this filter instance
 * @method has_start_value
 * @param {FilterState} filter_state The state of filters
 * @return {Boolean} `true` if filter_state has an start value for this filter.
--doc:/member
has_start_value: function(filter_state) {
}
--/doc:member

--doc:member
 * Check if filter state holds an end value for this filter instance
 * @method has_end_value
 * @param {FilterState} filter_state The state of filters
 * @return {Boolean} `true` if filter_state has an end value for this filter.
--doc:/member
has_end_value: function(filter_state) {
}
--/doc:member

--doc:member
 * Get the start value for this filter instance
 * @method start_value
 * @param {FilterState} filter_state The state of filters
 * @return The start value or the default start value if not null
--doc:/member
start_value: function(filter_state) {
}
--/doc:member

--doc:member
 * Get the end value for this filter instance
 * @method end_value
 * @param {FilterState} filter_state The state of filters
 * @return The start value or the default end value if not null
--doc:/member
end_value: function(filter_state) {
}
--/doc:member

--doc:member
 * Store start and end value for this filter in the filter state
 * Updates filter_state with start and end values for this filter instance.
 * Allowed data types for start_value and end_value are null or a number.
 * Pass null as start_value or end_value if that value is unspecified
 * (hasn't been entered or was erased by the user from the input box).
 * 
 * @method update_state
 * @param filter_state {FilterState}
 * @param start_value Start value
 * @param end_value End value
--doc:/member
update_state: function(filter_state, start_value, end_value) {
}
--/doc:member

--/doc:prototype

 */


class RangeInputFilter
{
 public:
  RangeInputFilter(v8::FunctionCallbackInfo<v8::Value> args);

  std::string start_prefix_label() const;
  std::string start_postfix_label() const;
  std::string end_prefix_label() const;
  std::string end_postfix_label() const;
  std::string central_label() const;
  v8::Local<v8::Value> default_start_value() const;
  v8::Local<v8::Value> default_end_value() const;
  bool has_start_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const;
  bool has_end_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const;
  double start_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const;
  double end_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const;
  
  void update_state(std::shared_ptr<unity::scopes::FilterState> filter_state,
                    v8::Local<v8::Value> start_value,
                    v8::Local<v8::Value> end_value) const;

  void set_display_hints(int hints);
  int display_hints() const;
  void set_title(const std::string& title);
  std::string title() const;
  std::string id() const;
  unity::scopes::VariantMap serialize() const;
  std::string filter_type() const;
  std::shared_ptr<FilterGroup> filter_group();

  unity::scopes::RangeInputFilter::SPtr get_filter();

 private:
  unity::scopes::RangeInputFilter::SPtr filter_;
};

#endif // _UNITY_JS_RANGE_INPUT_FILTER_H_


