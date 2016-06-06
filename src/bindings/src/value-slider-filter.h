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

#ifndef _UNITY_JS_VALUE_SLIDER_FILTER_H_
#define _UNITY_JS_VALUE_SLIDER_FILTER_H_

#include <unity/scopes/ValueSliderFilter.h>

#include <v8-cpp.h>

#include "filter-group.h"
#include "filter-state.h"
#include "value-slider-labels.h"


/**

--doc:class ValueSliderFilter
 * 
 * A value slider filter that allows for selecting a value within a given range.
 *
 * The ValueSliderFilter allows for selecting a value within a range defined by minimum and maximum values.
 * Both minimum and maximum values can have labels and, in addition, the scope may provide extra labels to mark other values from that range - these label will serve as a guidance to the user.
 * 
 * 
 * @module ScopeJS
 * @class ValueSliderFilter
--/doc:class

--doc:constructor
 * 
 * @constructor
 * @param {String} id A unique identifier for the filter that can be used to later identify it among several filters.
 * @param {Number} min The minimum allowed value
 * @param {Number} max The maximum allowed value
 * @param {Number} default_value The default value of this filter, from the min..max range.
 * @param {ValueSliderLabels} value_labels The labels for min and max values as well as optional extra labels.
--/doc:constructor

--doc:constructor
 * 
 * @constructor
 * @param {String} id A unique identifier for the filter that can be used to later identify it among several filters.
 * @param {Number} min The minimum allowed value
 * @param {Number} max The maximum allowed value
 * @param {Number} default_value The default value of this filter, from the min..max range.
 * @param {ValueSliderLabels} value_labels The labels for min and max values as well as optional extra labels.
 * @param {FilterGroup} group [optional] A filter group this filter should be added to.
--/doc:constructor

--doc:prototype ValueSliderFilter

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
 * Get the label of this filter
 * @method label
 * @return {String} label of this filter
--doc:/member
label: function() {
}
--/doc:member

--doc:member
 * Check if this filter supports multiple options to be selected
 * @method multi_select
 * @return {Boolean} True if this filter multiple options to be selected
--doc:/member
multi_select: function() {
}
--/doc:member

--doc:member
 * Add a new option to this filter
 * @method add_option
 * @return FilterOption The added filter option
--doc:/member
add_option: function() {
}
--/doc:member

--doc:member
 * Get all options of this filter, in the order they were added
 * @method options
 * @return {Array of FilterOption}
--doc:/member
options: function() {
}
--/doc:member

--doc:member
 * Check if an option is active for this filter
 * @method has_active_option
 * @param filter_state FilterState
 * @return {Boolean} True if an option is active for this filter
--doc:/member
has_active_option: function(filter_state) {
}
--/doc:member

--doc:member
 * Get active options from an instance of FilterState for this filter
 * @method active_options
 * @param filter_state FilterState
 * @return {Array of FilterOption} LIst of active FilterOption
--doc:/member
active_options: function() {
}
--/doc:member

--doc:member
 * Marks given FilterOption of this filter instance as active (or not active) in a FilterState object.
 * Records the given FilterOption as "selected" in the FilterState. This is meant to be used to modify a FilterState received with a search request before sending it back to the client (UI shell).
 * @method update_state
 * @param filter_state {FilterState}
 * @param option {FilterOption}
 * @param active {Boolean}
--doc:/member
update_state: function(filter_state, option, active) {
}
--/doc:member

--/doc:prototype

 */


class ValueSliderFilter
{
 public:
  ValueSliderFilter(v8::FunctionCallbackInfo<v8::Value> args);

  void set_default_value(double val);
  double default_value() const;
  double min() const;
  double max() const;
  bool has_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const;
  double value(std::shared_ptr<unity::scopes::FilterState> filter_state) const;
  std::shared_ptr<ValueSliderLabels> labels() const;

  void update_state(std::shared_ptr<unity::scopes::FilterState> filter_state
                    , double value) const;
  void set_display_hints(int hints);
  int display_hints() const;
  void set_title(const std::string& title);
  std::string title() const;
  std::string id() const;
  unity::scopes::VariantMap serialize() const;
  std::string filter_type() const;
  std::shared_ptr<FilterGroup> filter_group();

 private:
  unity::scopes::ValueSliderFilter::UPtr filter_;
};

#endif // _UNITY_JS_VALUE_SLIDER_FILTER_H_


