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

#include "result.h"

Result::Result(unity::scopes::Result const &result)
  : unity::scopes::Result(result) {
}

std::shared_ptr<Result>
Result::retrieve_stored_result() const {
  return std::shared_ptr<Result>(
      new Result(unity::scopes::Result::retrieve()));
}

void Result::store(
      std::shared_ptr<Result> result,
      bool intercept_activation) {
  unity::scopes::Result::store(
      *result,
      intercept_activation
  );
}
