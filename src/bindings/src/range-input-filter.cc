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

#include "common.h"

RangeInputFilter::RangeInputFilter(std::string const& id,
                                   v8::Local<v8::Value> default_start_value,
                                   v8::Local<v8::Value> default_end_value,
                                   std::string const& start_prefix_label,
                                   std::string const& start_postfix_label,
                                   std::string const& central_label,
                                   std::string const& end_prefix_label,
                                   std::string const& end_postfix_label,
                                   std::shared_ptr<FilterGroup> group) {
  unity::scopes::FilterGroup::SCPtr filter_group;
  if (group) {
    filter_group = group->get_filter_group();
  }

  filter_ = 
    unity::scopes::RangeInputFilter::create(
          id,
          unity::scopesjs::to_variant(default_start_value),
          unity::scopesjs::to_variant(default_end_value),
          start_prefix_label,
          start_postfix_label,
          central_label,
          end_prefix_label,
          end_postfix_label,
          filter_group);
}

std::string RangeInputFilter::start_prefix_label() const {
  return filter_->start_prefix_label();
}

std::string RangeInputFilter::start_postfix_label() const {
  return filter_->start_postfix_label();
}

std::string RangeInputFilter::end_prefix_label() const {
  return filter_->end_prefix_label();
}

std::string RangeInputFilter::end_postfix_label() const {
  return filter_->end_postfix_label();
}

std::string RangeInputFilter::central_label() const {
  return filter_->central_label();
}

v8::Local<v8::Value> RangeInputFilter::default_start_value() const {
  unity::scopes::Variant v =
    filter_->default_start_value();
  switch(v.which()) {
  case unity::scopes::Variant::Null:
    return v8::Null(v8::Isolate::GetCurrent());
  case unity::scopes::Variant::Int:
    return v8::Integer::New(v8::Isolate::GetCurrent(), v.get_int());
  case unity::scopes::Variant::Double:
    return v8::Number::New(v8::Isolate::GetCurrent(), v.get_double());
  default:
    throw std::runtime_error("Invalid default start value");
  }
}

v8::Local<v8::Value> RangeInputFilter::default_end_value() const {
  unity::scopes::Variant v =
    filter_->default_end_value();
  switch(v.which()) {
  case unity::scopes::Variant::Null:
    return v8::Null(v8::Isolate::GetCurrent());
  case unity::scopes::Variant::Int:
    return v8::Integer::New(v8::Isolate::GetCurrent(), v.get_int());
  case unity::scopes::Variant::Double:
    return v8::Number::New(v8::Isolate::GetCurrent(), v.get_double());
  default:
    throw std::runtime_error("Invalid default start value");
  }
}

bool RangeInputFilter::has_start_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const {
  return true;
}

bool RangeInputFilter::has_end_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const {
  return true;
}

double RangeInputFilter::start_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const {
  return true;
}

double RangeInputFilter::end_value(std::shared_ptr<unity::scopes::FilterState> filter_state) const {
  return true;
}
  
void RangeInputFilter::update_state(std::shared_ptr<unity::scopes::FilterState> filter_state,
                                    v8::Local<v8::Value> start_value,
                                    v8::Local<v8::Value> end_value) const {
}

void RangeInputFilter::set_display_hints(int hints) {
  filter_->set_display_hints(hints);
}

int RangeInputFilter::display_hints() const {
  return filter_->display_hints();
}

std::string RangeInputFilter::id() const {
  return filter_->id();
}

unity::scopes::VariantMap RangeInputFilter::serialize() const {
  return filter_->serialize();
}

std::string RangeInputFilter::filter_type() const {
  return filter_->filter_type();
}

unity::scopes::RangeInputFilter::SPtr RangeInputFilter::get_filter() {
  return filter_;
}

void RangeInputFilter::set_title(const std::string& title) {
  filter_->set_title(title);
}

std::string RangeInputFilter::title() const {
  return filter_->title();
}

std::shared_ptr<FilterGroup> RangeInputFilter::filter_group() {
  unity::scopes::FilterGroup::SCPtr fg = filter_->filter_group();
  if (!fg) {
    return std::shared_ptr<FilterGroup>();
  }
  return std::shared_ptr<FilterGroup>(new FilterGroup(fg));
}
