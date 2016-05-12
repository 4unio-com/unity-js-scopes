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

#include "common.h"
#include "range-input-filter.h"

RangeInputFilter::RangeInputFilter(v8::FunctionCallbackInfo<v8::Value> const& args)
{
    if (args.Length() == 6)
    {
        auto a = v8cpp::from_v8<std::string>(args.GetIsolate(), args[0]);
        auto b = v8cpp::from_v8<std::string>(args.GetIsolate(), args[1]);
        auto c = v8cpp::from_v8<std::string>(args.GetIsolate(), args[2]);
        auto d = v8cpp::from_v8<std::string>(args.GetIsolate(), args[3]);
        auto e = v8cpp::from_v8<std::string>(args.GetIsolate(), args[4]);
        auto f = v8cpp::from_v8<std::string>(args.GetIsolate(), args[5]);

        filter_ = unity::scopes::RangeInputFilter::create(a, b, c, d, e, f);
    }
    else if (args.Length() == 7)
    {
        auto a = v8cpp::from_v8<std::string>(args.GetIsolate(), args[0]);
        auto b = v8cpp::from_v8<std::string>(args.GetIsolate(), args[1]);
        auto c = v8cpp::from_v8<std::string>(args.GetIsolate(), args[2]);
        auto d = v8cpp::from_v8<std::string>(args.GetIsolate(), args[3]);
        auto e = v8cpp::from_v8<std::string>(args.GetIsolate(), args[4]);
        auto f = v8cpp::from_v8<std::string>(args.GetIsolate(), args[5]);
        auto g = v8cpp::from_v8<std::shared_ptr<FilterGroup>>(args.GetIsolate(), args[6]);

        filter_ = unity::scopes::RangeInputFilter::create(a, b, c, d, e, f, g->get_filter_group());
        filter_group_ = g;
    }
    else if (args.Length() == 8)
    {
        auto a = v8cpp::from_v8<std::string>(args.GetIsolate(), args[0]);
        auto b = unity::scopesjs::to_variant(args[1]);
        auto c = unity::scopesjs::to_variant(args[2]);
        auto d = v8cpp::from_v8<std::string>(args.GetIsolate(), args[3]);
        auto e = v8cpp::from_v8<std::string>(args.GetIsolate(), args[4]);
        auto f = v8cpp::from_v8<std::string>(args.GetIsolate(), args[5]);
        auto g = v8cpp::from_v8<std::string>(args.GetIsolate(), args[6]);
        auto h = v8cpp::from_v8<std::string>(args.GetIsolate(), args[7]);

        filter_ = unity::scopes::RangeInputFilter::create(a, b, c, d, e, f, g, h);
    }
    else if (args.Length() == 9)
    {
        auto a = v8cpp::from_v8<std::string>(args.GetIsolate(), args[0]);
        auto b = unity::scopesjs::to_variant(args[1]);
        auto c = unity::scopesjs::to_variant(args[2]);
        auto d = v8cpp::from_v8<std::string>(args.GetIsolate(), args[3]);
        auto e = v8cpp::from_v8<std::string>(args.GetIsolate(), args[4]);
        auto f = v8cpp::from_v8<std::string>(args.GetIsolate(), args[5]);
        auto g = v8cpp::from_v8<std::string>(args.GetIsolate(), args[6]);
        auto h = v8cpp::from_v8<std::string>(args.GetIsolate(), args[7]);
        auto i = v8cpp::from_v8<std::shared_ptr<FilterGroup>>(args.GetIsolate(), args[8]);

        filter_ = unity::scopes::RangeInputFilter::create(a, b, c, d, e, f, g, h, i->get_filter_group());
        filter_group_ = i;
    }
    else
    {
        throw std::runtime_error("Invalid number of arguments");
    }
}

void RangeInputFilter::set_display_hints(int hints)
{
    filter_->set_display_hints(hints);
}

int RangeInputFilter::display_hints() const
{
    return filter_->display_hints();
}

std::string RangeInputFilter::id() const
{
    return filter_->id();
}

std::string RangeInputFilter::filter_type() const
{
    return filter_->filter_type();
}

void RangeInputFilter::set_title(std::string const& title)
{
    filter_->set_title(title);
}

std::string RangeInputFilter::title() const
{
    return filter_->title();
}

std::shared_ptr<FilterGroup> RangeInputFilter::filter_group() const
{
    return filter_group_;
}

std::string RangeInputFilter::start_prefix_label() const
{
    return filter_->start_prefix_label();
}

std::string RangeInputFilter::start_postfix_label() const
{
    return filter_->start_postfix_label();
}

std::string RangeInputFilter::end_prefix_label() const
{
    return filter_->end_prefix_label();
}

std::string RangeInputFilter::end_postfix_label() const
{
    return filter_->end_postfix_label();
}

std::string RangeInputFilter::central_label() const
{
    return filter_->central_label();
}

unity::scopes::Variant RangeInputFilter::default_start_value() const
{
    return filter_->default_start_value();
}

unity::scopes::Variant RangeInputFilter::default_end_value() const
{
    return filter_->default_end_value();
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

void RangeInputFilter::update_state(unity::scopes::FilterState& filter_state, unity::scopes::Variant const& start_value, unity::scopes::Variant const& end_value) const
{
    return filter_->update_state(filter_state, start_value, end_value);
}

unity::scopes::RangeInputFilter::SPtr RangeInputFilter::get_filter()
{
    return filter_;
}
