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

#include "category.h"

Category::Category() {
}

Category::~Category() {
}

v8::Local<v8::Value> Category::id(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  v8::Isolate *isolate = args.GetIsolate();
  return v8cpp::to_v8(isolate, unity::scopes::Category::id().c_str());
}

v8::Local<v8::Value> Category::title(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  v8::Isolate *isolate = args.GetIsolate();
  return v8cpp::to_v8(isolate, unity::scopes::Category::title().c_str());
}

v8::Local<v8::Value> Category::icon(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  v8::Isolate *isolate = args.GetIsolate();
  return v8cpp::to_v8(isolate, unity::scopes::Category::icon().c_str());
}
