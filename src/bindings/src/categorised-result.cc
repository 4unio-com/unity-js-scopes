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

#include "categorised-result.h"

CategorisedResult::CategorisedResult(Category * category)
  : unity::scopes::CategorisedResult(category->get_category()),
    category_(category) {
}

CategorisedResult::~CategorisedResult() {
}

void CategorisedResult::set_uri(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsString()) {
    // TODO fix
    return;
  }

  unity::scopes::CategorisedResult::set_uri(*(v8::String::Utf8Value(args[0]->ToString())));
}

void CategorisedResult::set_title(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsString()) {
    // TODO fix
    return;
  }

  unity::scopes::CategorisedResult::set_title(*(v8::String::Utf8Value(args[0]->ToString())));
}
