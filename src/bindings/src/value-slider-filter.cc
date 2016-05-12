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

ValueSliderFilter::ValueSliderFilter(v8::FunctionCallbackInfo<v8::Value> const& args)
{
    if (args.Length() == 5)
    {
        auto a = v8cpp::from_v8<std::string>(args.GetIsolate(), args[0]);
        auto b = v8cpp::from_v8<double>(args.GetIsolate(), args[1]);
        auto c = v8cpp::from_v8<double>(args.GetIsolate(), args[2]);
        auto d = v8cpp::from_v8<double>(args.GetIsolate(), args[3]);
        auto e = v8cpp::from_v8<std::shared_ptr<ValueSliderLabels>>(args.GetIsolate(), args[4]);

        filter_ = unity::scopes::ValueSliderFilter::create(a, b, c, d, e->get_labels());
        labels_ = e;
    }
    else if (args.Length() == 6)
    {
        auto a = v8cpp::from_v8<std::string>(args.GetIsolate(), args[0]);
        auto b = v8cpp::from_v8<double>(args.GetIsolate(), args[1]);
        auto c = v8cpp::from_v8<double>(args.GetIsolate(), args[2]);
        auto d = v8cpp::from_v8<double>(args.GetIsolate(), args[3]);
        auto e = v8cpp::from_v8<std::shared_ptr<ValueSliderLabels>>(args.GetIsolate(), args[4]);
        auto f = v8cpp::from_v8<std::shared_ptr<FilterGroup>>(args.GetIsolate(), args[5]);

        filter_ = unity::scopes::ValueSliderFilter::create(a, b, c, d, e->get_labels(), f->get_filter_group());
        labels_ = e;
        filter_group_ = f;
    }
    else
    {
        throw std::runtime_error("Invalid number of arguments");
    }
}

void ValueSliderFilter::set_display_hints(int hints)
{
    filter_->set_display_hints(hints);
}

int ValueSliderFilter::display_hints() const
{
    return filter_->display_hints();
}

std::string ValueSliderFilter::id() const
{
    return filter_->id();
}

std::string ValueSliderFilter::filter_type() const
{
    return filter_->filter_type();
}

void ValueSliderFilter::set_title(std::string const& title)
{
    return filter_->set_title(title);
}

std::string ValueSliderFilter::title() const
{
    return filter_->title();
}

std::shared_ptr<FilterGroup> ValueSliderFilter::filter_group() const
{
    return filter_group_;
}

void ValueSliderFilter::set_default_value(double val)
{
    return filter_->set_default_value(val);
}

double ValueSliderFilter::default_value() const
{
    return filter_->default_value();
}

double ValueSliderFilter::min() const
{
    return filter_->min();
}

double ValueSliderFilter::max() const
{
    return filter_->max();
}

bool ValueSliderFilter::has_value(unity::scopes::FilterState const& filter_state) const
{
    return filter_->has_value(filter_state);
}

double ValueSliderFilter::value(unity::scopes::FilterState const& filter_state) const
{
    return filter_->value(filter_state);
}

std::shared_ptr<ValueSliderLabels> ValueSliderFilter::labels() const
{
    return labels_;
}

void ValueSliderFilter::update_state(unity::scopes::FilterState& filter_state, double value) const
{
    return filter_->update_state(filter_state, value);
}

unity::scopes::ValueSliderFilter::SPtr ValueSliderFilter::get_filter()
{
    return filter_;
}
