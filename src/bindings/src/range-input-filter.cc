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

#include "range-input-filter.h"

RangeInputFilter::RangeInputFilter(std::string const& id, std::string const& start_prefix_label,
                                   std::string const& start_postfix_label, std::string const& central_label,
                                   std::string const& end_prefix_label, std::string const& end_postfix_label,
                                   FilterGroup const& group)
    : filter_(unity::scopes::RangeInputFilter::create(id, start_prefix_label, start_postfix_label,
                                                      central_label, end_prefix_label, end_postfix_label,
                                                      group.get_filter_group())){
}

void RangeInputFilter::set_title(std::string const& title)
{
    filter_->set_title(title);
}

bool RangeInputFilter::has_start_value(unity::scopes::FilterState const& filter_state) const
{
    return filter_->has_start_value(filter_state);
}

bool RangeInputFilter::has_end_value(unity::scopes::FilterState const& filter_state) const
{
    return filter_->has_end_value(filter_state);
}

double RangeInputFilter::start_value(unity::scopes::FilterState const& filter_state) const
{
    return filter_->start_value(filter_state);
}

double RangeInputFilter::end_value(unity::scopes::FilterState const& filter_state) const
{
    return filter_->end_value(filter_state);
}

unity::scopes::RangeInputFilter::SPtr RangeInputFilter::get_filter()
{
    return filter_;
}
