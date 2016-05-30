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

#ifndef _UNITY_JS_VALUE_SLIDER_LABELS_H_
#define _UNITY_JS_VALUE_SLIDER_LABELS_H_

#include <unity/scopes/ValueSliderLabels.h>

#include <v8-cpp.h>

/**

--doc:class ValueSliderLabels
 * 
 * Labels used by a ValueSliderFilter
 *
 * The ValueSliderLabels class holds labels for a ValueSliderFilter.
 * Labels for the minimum and maximum values must be provided.
 * In addition, an arbitrary number of extra labels can be defined; these labels
 * mark intermediate values between the minimum and maximum value.
 * 
 * @module ScopeJS
 * @class ValueSliderLabels
--/doc:class

--doc:constructor
 * Create a ValueSliderLabels instance with labels for minimum and maximum, as well as extra labels.
 * 
 * Note that any extra labels act only as a guidance for the user
 * (i.e. they do not limit the available choices).
 * The Unity shell is free to omit some or all of the labels depending
 * on the available screen space.
 * 
 * @constructor
 * @param min_label {String} The label for minimum value of the associated ValueSliderFilter filter.
 * @param max_label {String} The label for maximum value of the associated ValueSliderFilter filter.
 * @param extra_labels {Array of {"value": Number, "label": String} objects} [optional] Additional labels for values between minimum and maximum values.
 *                                         
--/doc:constructor

--doc:prototype ValueSliderLabels

--doc:member
 * Get the label for the minimum value of the filter.
 * @method min_label
 * @return {String} The label for the minimum value
--doc:/member
min_label: function() {
}
--/doc:member

--doc:member
 * Get the label for the maximum value of the filter.
 * @method max_label
 * @return {String} The label for the maximum value
--doc:/member
max_label: function() {
}
--/doc:member

--doc:member
 * Get the labels for intermediate values of the filter
 * @method extra_labels
 * @return {Array of {Number, String} object}
--doc:/member
extra_labels: function() {
}
--/doc:member

--/doc:prototype

 */

class ValueSliderLabels
{
 public:
  ValueSliderLabels(const unity::scopes::ValueSliderLabels& labels);
  ValueSliderLabels(std::string const &min_label,
                    std::string const &max_label,
                    v8::Local<v8::Value> extra_labels);

  std::string min_label() const;
  std::string max_label() const;
  v8::Local<v8::Value> extra_labels() const;

  unity::scopes::ValueSliderLabels get_labels();

 private:
  std::unique_ptr<unity::scopes::ValueSliderLabels> vsl_;
};

#endif // _UNITY_JS_VALUE_SLIDER_LABELS_H_


