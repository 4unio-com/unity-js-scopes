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

#include "search-metadata.h"

SearchMetaData::SearchMetaData(const unity::scopes::SearchMetadata& meta_data)
  : unity::scopes::SearchMetadata(meta_data) {
}

void SearchMetaData::set_location(
      std::shared_ptr<unity::scopes::Location> location) {
  if (location) {
    unity::scopes::SearchMetadata::set_location(*location);
  }
}

std::shared_ptr<unity::scopes::Location> SearchMetaData::location() const {
  return std::shared_ptr<unity::scopes::Location>(
      new unity::scopes::Location(unity::scopes::SearchMetadata::location()));
}
