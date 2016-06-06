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

#include <unity/scopes/FilterState.h>

ValueSliderFilter::ValueSliderFilter(v8::FunctionCallbackInfo<v8::Value> args) {
  if (args.Length() != 5 && args.Length() != 6) {
    throw std::runtime_error("Invalid number of arguments");
  }

  if (args.Length() == 5) {
    auto id =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[0]);
    auto min =
      v8cpp::from_v8<double>(v8::Isolate::GetCurrent(), args[1]);
    auto max =
      v8cpp::from_v8<double>(v8::Isolate::GetCurrent(), args[2]);
    auto default_value =
      v8cpp::from_v8<double>(v8::Isolate::GetCurrent(), args[3]);
    auto value_slider_labels =
      v8cpp::from_v8<std::shared_ptr<ValueSliderLabels>>(v8::Isolate::GetCurrent(), args[4]);

    unity::scopes::ValueSliderLabels labels =
      value_slider_labels->get_labels();
    filter_ =
      unity::scopes::ValueSliderFilter::create(
        id, min, max, default_value, labels);
  } else {
    auto id =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[0]);
    auto min =
      v8cpp::from_v8<double>(v8::Isolate::GetCurrent(), args[1]);
    auto max =
      v8cpp::from_v8<double>(v8::Isolate::GetCurrent(), args[2]);
    auto default_value =
      v8cpp::from_v8<double>(v8::Isolate::GetCurrent(), args[3]);
    auto value_slider_labels =
      v8cpp::from_v8<std::shared_ptr<ValueSliderLabels>>(v8::Isolate::GetCurrent(), args[4]);
    auto group =
      v8cpp::from_v8<std::shared_ptr<FilterGroup>>(v8::Isolate::GetCurrent(), args[5]);

    unity::scopes::ValueSliderLabels labels =
      value_slider_labels->get_labels();
    unity::scopes::FilterGroup::SCPtr filter_group;
    if (group) {
      filter_group = group->get_filter_group();
    }
    filter_ =
      unity::scopes::ValueSliderFilter::create(
        id, min, max, default_value, labels, filter_group);
  }
}

void ValueSliderFilter::set_default_value(double val) {
  filter_->set_default_value(val);
}

double ValueSliderFilter::default_value() const {
  return filter_->default_value();
}

double ValueSliderFilter::min() const {
  return filter_->min();
}

double ValueSliderFilter::max() const {
  return filter_->max();
}

bool ValueSliderFilter::has_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const {
  return filter_->has_value(*filter_state);
}

double ValueSliderFilter::value(std::shared_ptr<unity::scopes::FilterState> filter_state) const {
  return filter_->value(*filter_state);
}

std::shared_ptr<ValueSliderLabels> ValueSliderFilter::labels() const {
  return std::shared_ptr<ValueSliderLabels>(
      new ValueSliderLabels(filter_->labels()));
}

void ValueSliderFilter::update_state(
      std::shared_ptr<unity::scopes::FilterState> filter_state,
      double value) const {
  filter_->update_state(*filter_state, value);
}

void ValueSliderFilter::set_display_hints(int hints) {
  filter_->set_display_hints(hints);
}

int ValueSliderFilter::display_hints() const {
  return filter_->display_hints();
}

std::string ValueSliderFilter::id() const {
  return filter_->id();
}

unity::scopes::VariantMap ValueSliderFilter::serialize() const {
  return filter_->serialize();
}

std::string ValueSliderFilter::filter_type() const {
  return filter_->filter_type();
}

void ValueSliderFilter::set_title(const std::string& title) {
  filter_->set_title(title);
}

std::string ValueSliderFilter::title() const {
  return filter_->title();
}

std::shared_ptr<FilterGroup> ValueSliderFilter::filter_group() {
  unity::scopes::FilterGroup::SCPtr fg = filter_->filter_group();
  if (!fg) {
    return std::shared_ptr<FilterGroup>();
  }
  return std::shared_ptr<FilterGroup>(
      new FilterGroup(fg));
}
