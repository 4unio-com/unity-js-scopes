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

class RangeInputFilter
{
public:
    RangeInputFilter(std::string const& id, std::string const& start_prefix_label,
                     std::string const& start_postfix_label, std::string const& central_label,
                     std::string const& end_prefix_label, std::string const& end_postfix_label,
                     FilterGroup const& group);

    void set_title(std::string const& title);

    bool has_start_value(unity::scopes::FilterState const& filter_state) const;
    bool has_end_value(unity::scopes::FilterState const& filter_state) const;

    double start_value(unity::scopes::FilterState const& filter_state) const;
    double end_value(unity::scopes::FilterState const& filter_state) const;

    unity::scopes::RangeInputFilter::SPtr get_filter();

private:
    unity::scopes::RangeInputFilter::SPtr filter_;
};

#endif // _UNITY_JS_RANGE_INPUT_FILTER_H_


