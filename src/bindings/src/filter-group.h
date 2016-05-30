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

#ifndef _UNITY_JS_FILTER_GROUP_H_
#define _UNITY_JS_FILTER_GROUP_H_

#include <unity/scopes/FilterGroup.h>

#include <v8-cpp.h>

/**

--doc:class FilterGroup
 * 
 * Groups several filters into an expandable widget in the UI.
 * 
 * @module ScopeJS
 * @class FilterGroup
--/doc:class

--doc:constructor
 *
 * @constructor
 * @param id The id of the filter group.
 * @param label The label corresponding to the filter group.
--/doc:constructor

--doc:prototype FilterGroup

--doc:member
 * Get the id of the widget group.
 * @method id
 * @return {String} The identifier.
--doc:/member
id: function() {
}
--/doc:member

--doc:member
 * Get the label of the widget group.
 * @method label
 * @return {String} The label.
--doc:/member
label: function() {
}
--/doc:member

--/doc:prototype

 */

class FilterGroup
{
 public:
  FilterGroup(unity::scopes::FilterGroup::SCPtr p);
  FilterGroup(std::string const& id, std::string const& label);

  std::string id();
  std::string label();

  unity::scopes::FilterGroup::SCPtr get_filter_group();

 private:
  unity::scopes::FilterGroup::SCPtr _fg;
};

#endif // _UNITY_JS_FILTER_GROUP_H_
