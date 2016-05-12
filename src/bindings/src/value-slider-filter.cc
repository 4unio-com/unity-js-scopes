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

#include "value-slider-filter.h"

ValueSliderFilter::ValueSliderFilter(std::string const& id, double min, double max, double default_value,
                                     ValueSliderLabels const& value_labels, std::shared_ptr<FilterGroup> const& group)
    : filter_(unity::scopes::ValueSliderFilter::create(id, min, max, default_value,
                                                       value_labels.get_labels(), group->get_filter_group())){
}

unity::scopes::ValueSliderFilter::SPtr ValueSliderFilter::get_filter()
{
    return filter_;
}

void ValueSliderFilter::set_title(std::string const& title)
{
    filter_->set_title(title);
}

bool ValueSliderFilter::has_value(unity::scopes::FilterState const& filter_state) const
{
    return filter_->has_value(filter_state);
}

double ValueSliderFilter::value(unity::scopes::FilterState const& filter_state) const
{
    return filter_->value(filter_state);
}
