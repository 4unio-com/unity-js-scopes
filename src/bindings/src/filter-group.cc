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

#include "filter-group.h"

FilterGroup::FilterGroup(unity::scopes::FilterGroup::SCPtr p)
  : _fg(p) {
}

FilterGroup::FilterGroup(std::string const& id, std::string const& label)
  : _fg(unity::scopes::FilterGroup::create(id, label)) {
}

std::string FilterGroup::id() {
  return _fg->id();
}

std::string FilterGroup::label() {
  return _fg->label();
}

unity::scopes::FilterGroup::SCPtr FilterGroup::get_filter_group() {
  return _fg;
}
