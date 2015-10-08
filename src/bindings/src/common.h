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

#include <string>

#include <v8-cpp.h>

#include "unity/scopes/Variant.h"


namespace unity {
namespace scopesjs {

unity::scopes::Variant
to_variant(v8::Local<v8::Value> value);

v8::Local<v8::Value>
from_variant(const unity::scopes::Variant& variant);

} // namespace scopesjs
} // namespace unity

