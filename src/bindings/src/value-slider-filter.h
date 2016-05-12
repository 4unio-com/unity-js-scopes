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
    ValueSliderFilter(v8::FunctionCallbackInfo<v8::Value> const& args);

    // FilterBase
    void set_display_hints(int hints);
    int display_hints() const;
    std::string id() const;
    std::string filter_type() const;
    void set_title(std::string const& title);
    std::string title() const;
    std::shared_ptr<FilterGroup> filter_group() const;

    // ValueSliderFilter
    void set_default_value(double val);
    double default_value() const;
    double min() const;
    double max() const;
    bool has_value(unity::scopes::FilterState const& filter_state) const;
    double value(unity::scopes::FilterState const& filter_state) const;
    std::shared_ptr<ValueSliderLabels> labels() const;
    void update_state(unity::scopes::FilterState& filter_state, double value) const;

    unity::scopes::ValueSliderFilter::SPtr get_filter();

private:
    unity::scopes::ValueSliderFilter::SPtr filter_;
    std::shared_ptr<FilterGroup> filter_group_;
    std::shared_ptr<ValueSliderLabels> labels_;
};

#endif // _UNITY_JS_VALUE_SLIDER_FILTER_H_


