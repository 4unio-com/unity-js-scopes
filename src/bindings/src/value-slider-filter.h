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

#include "value-slider-labels.h"
#include "filter-group.h"

#include <unity/scopes/ValueSliderFilter.h>

class ValueSliderFilter
{
public:
    ValueSliderFilter(std::string const& id, double min, double max, double default_value,
                      ValueSliderLabels const& value_labels, FilterGroup const& group);

    unity::scopes::ValueSliderFilter::SPtr get_filter();

private:
    unity::scopes::ValueSliderFilter::SPtr filter_;
};

#endif // _UNITY_JS_VALUE_SLIDER_FILTER_H_


