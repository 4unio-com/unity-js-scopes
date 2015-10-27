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

#ifndef _UNITY_JS_OPTION_SELECTOR_FILTER_H_
#define _UNITY_JS_OPTION_SELECTOR_FILTER_H_

#include <unity/scopes/OptionSelectorFilter.h>

#include <v8-cpp.h>


/**

--doc:class OptionSelectorFilter
 * 
 * A selection filter that displays a list of choices and allows one or more of them to be selected
 * 
 * @module ScopeJS
 * @class OptionSelectorFilter
--/doc:class

--doc:constructor
 * 
 * @constructor
 * @param id {String} A unique identifier for the filter that can be used to identify it later among several filters
 * @param label {String} A display label for the filter
 * @param multi_select {Boolean} If true, the filter permits more than option to be selected; otherwise, only a single option can be selected
--/doc:constructor

--doc:prototype OptionSelectorFilter

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

--doc:member
 * Sets display hints for the Shell UI
 * @method set_display_hints
 * @param hints {int} 0 is Default filter hint, 1 is Primary filter hint
--doc:/member
set_display_hints: function(hints) {
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

--/doc:prototype

 */


class OptionSelectorFilter
{
 public:
  OptionSelectorFilter(std::string const &id, std::string const &label, bool multi_select);

  std::string label() const;
  bool multi_select() const;
  unity::scopes::FilterOption::SCPtr add_option(std::string const& id, std::string const& label);
  std::list<unity::scopes::FilterOption::SCPtr> options() const;
  bool has_active_option(unity::scopes::FilterState const& filter_state) const;
  std::set<unity::scopes::FilterOption::SCPtr> active_options(unity::scopes::FilterState const& filter_state) const;
  void update_state(unity::scopes::FilterState& filter_state, unity::scopes::FilterOption::SCPtr option, bool active) const;

  void set_display_hints(int hints);
  int display_hints() const;
  std::string id() const;
  unity::scopes::VariantMap serialize() const;
  std::string filter_type() const;

  unity::scopes::OptionSelectorFilter::SPtr get_filter();

 private:
  unity::scopes::OptionSelectorFilter::SPtr filter_;
};

#endif // _UNITY_JS_OPTION_SELECTOR_FILTER_H_


