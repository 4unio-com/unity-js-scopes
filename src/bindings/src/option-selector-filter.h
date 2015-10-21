/*
 * Copyright 2015 Canonical Ltd.
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

#ifndef _UNITY_JS_OPTION_SELECTOR_FILTER_H_
#define _UNITY_JS_OPTION_SELECTOR_FILTER_H_

#include <unity/scopes/OptionSelectorFilter.h>

#include <v8-cpp.h>


class OptionSelectorFilter
{
 public:
  OptionSelectorFilter(std::string const &id, std::string const &label, bool multi_select);

  std::string label() const;
  bool multi_select() const;
  unity::scopes::FilterOption::SCPtr add_option(std::string const& id, std::string const& label);
  std::list<unity::scopes::FilterOption::SCPtr> options() const;
  bool has_active_option(unity::scopes::FilterState const& filter_state) const;
  std::set<unity::scopes::FilterOption::SCPtr> active_options(unity::scopes::FilterState const& filter_state) const;
  void update_state(unity::scopes::FilterState& filter_state, unity::scopes::FilterOption::SCPtr option, bool active) const;

  void set_display_hints(int hints);
  int display_hints() const;
  std::string id() const;
  unity::scopes::VariantMap serialize() const;
  std::string filter_type() const;

  unity::scopes::OptionSelectorFilter::SPtr get_filter();

 private:
  unity::scopes::OptionSelectorFilter::SPtr filter_;
};

#endif // _UNITY_JS_OPTION_SELECTOR_FILTER_H_


