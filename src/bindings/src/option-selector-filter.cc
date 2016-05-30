/*
 * Copyright 2015-2016 Canonical Ltd.
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

#include "option-selector-filter.h"


OptionSelectorFilter::OptionSelectorFilter(
      std::string const &id,
      std::string const &label,
      bool multi_select)
  : filter_(unity::scopes::OptionSelectorFilter::create(id, label, multi_select)){
}

std::string OptionSelectorFilter::label() const {
  return filter_->label();
}

bool OptionSelectorFilter::multi_select() const {
  return filter_->multi_select();
}

unity::scopes::FilterOption::SCPtr OptionSelectorFilter::add_option(
      std::string const& id,
      std::string const& label) {
  return filter_->add_option(id, label);
}

std::list<unity::scopes::FilterOption::SCPtr> OptionSelectorFilter::options() const {
  return filter_->options();
}

bool OptionSelectorFilter::has_active_option(
      unity::scopes::FilterState const& filter_state) const {
  return filter_->has_active_option(filter_state);
}

std::set<unity::scopes::FilterOption::SCPtr> OptionSelectorFilter::active_options(
      unity::scopes::FilterState const& filter_state) const {
  return filter_->active_options(filter_state);
}

void OptionSelectorFilter::update_state(
      unity::scopes::FilterState& filter_state,
      unity::scopes::FilterOption::SCPtr option,
      bool active) const {
  filter_->update_state(filter_state, option, active);
}

void OptionSelectorFilter::set_display_hints(int hints) {
  filter_->set_display_hints(hints);
}

int OptionSelectorFilter::display_hints() const {
  return filter_->display_hints();
}

std::string OptionSelectorFilter::id() const {
  return filter_->id();
}

unity::scopes::VariantMap OptionSelectorFilter::serialize() const {
  return filter_->serialize();
}

std::string OptionSelectorFilter::filter_type() const {
  return filter_->filter_type();
}

unity::scopes::OptionSelectorFilter::SPtr OptionSelectorFilter::get_filter() {
  return filter_;
}

void OptionSelectorFilter::set_title(const std::string& title) {
  filter_->set_title(title);
}

std::string OptionSelectorFilter::title() const {
  return filter_->title();
}

std::shared_ptr<FilterGroup> OptionSelectorFilter::filter_group() {
  unity::scopes::FilterGroup::SCPtr fg = filter_->filter_group();
  if (!fg) {
    return std::shared_ptr<FilterGroup>();
  }
  return std::shared_ptr<FilterGroup>(new FilterGroup(fg));
}
