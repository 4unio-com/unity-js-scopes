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

#ifndef _UNITY_JS_RANGE_INPUT_FILTER_H_
#define _UNITY_JS_RANGE_INPUT_FILTER_H_

#include "filter-group.h"

#include <unity/scopes/RangeInputFilter.h>

#include <v8-cpp.h>

class RangeInputFilter
{
public:
    RangeInputFilter(v8::FunctionCallbackInfo<v8::Value> const& args);

    // FilterBase
    void set_display_hints(int hints);
    int display_hints() const;
    std::string id() const;
    std::string filter_type() const;
    void set_title(std::string const& title);
    std::string title() const;
    std::shared_ptr<FilterGroup> filter_group() const;

    // RangeInputFilter
    std::string start_prefix_label() const;
    std::string start_postfix_label() const;
    std::string end_prefix_label() const;
    std::string end_postfix_label() const;
    std::string central_label() const;
    unity::scopes::Variant default_start_value() const;
    unity::scopes::Variant default_end_value() const;
    bool has_start_value(unity::scopes::FilterState const& filter_state) const;
    bool has_end_value(unity::scopes::FilterState const& filter_state) const;
    double start_value(unity::scopes::FilterState const& filter_state) const;
    double end_value(unity::scopes::FilterState const& filter_state) const;
    void update_state(unity::scopes::FilterState& filter_state, unity::scopes::Variant const& start_value, unity::scopes::Variant const& end_value) const;

    unity::scopes::RangeInputFilter::SPtr get_filter();

private:
    unity::scopes::RangeInputFilter::SPtr filter_;
    std::shared_ptr<FilterGroup> filter_group_;
};

#endif // _UNITY_JS_RANGE_INPUT_FILTER_H_


