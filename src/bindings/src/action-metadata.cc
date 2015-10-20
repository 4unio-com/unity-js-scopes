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

#include "action-metadata.h"

ActionMetaData::ActionMetaData(unity::scopes::ActionMetadata const &action_metadata)
  : unity::scopes::ActionMetadata(action_metadata) {
}

ActionMetaData::ActionMetaData(std::string const &locale,
                               std::string const &form_factor)
  : unity::scopes::ActionMetadata(locale, form_factor) {
}

ActionMetaData::~ActionMetaData() {
}

unity::scopes::Variant ActionMetaData::get(const std::string& key) {
  return (*this)[key];
}

void ActionMetaData::set(const std::string& key,
                         const unity::scopes::Variant& val) {
  (*this)[key] = val;
}
