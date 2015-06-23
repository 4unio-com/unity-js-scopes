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
  : result_(result) {
}

Result::~Result() {
}

v8::Local<v8::Value> Result::uri(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  std::string uri = result_.uri();
  return v8cpp::to_v8(args.GetIsolate(), uri.c_str());
}

void Result::set_uri(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1 || !args[0]->IsString()) {
    throw std::runtime_error("Invalid arguments");
  }
  result_.set_uri(*(v8::String::Utf8Value(args[0]->ToString())));
}

v8::Local<v8::Value> Result::title(v8::FunctionCallbackInfo<v8::Value> const& args) {
  std::string title = result_.title();
  return v8cpp::to_v8(args.GetIsolate(), title.c_str());
}

void Result::set_title(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1 || !args[0]->IsString()) {
    throw std::runtime_error("Invalid arguments");
  }
  result_.set_title(*(v8::String::Utf8Value(args[0]->ToString())));
}

v8::Local<v8::Value> Result::art(v8::FunctionCallbackInfo<v8::Value> const& args) {
  std::string art = result_.art();
  return v8cpp::to_v8(args.GetIsolate(), art.c_str());
}

void Result::set_art(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1 || !args[0]->IsString()) {
    throw std::runtime_error("Invalid arguments");
  }
  result_.set_art(*(v8::String::Utf8Value(args[0]->ToString())));
}

v8::Local<v8::Value> Result::dnd_uri(v8::FunctionCallbackInfo<v8::Value> const& args) {
  std::string dnd_uri = result_.dnd_uri();
  return v8cpp::to_v8(args.GetIsolate(), dnd_uri.c_str());
}

void Result::set_dnd_uri(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1 || !args[0]->IsString()) {
    throw std::runtime_error("Invalid arguments");
  }
  result_.set_dnd_uri(*(v8::String::Utf8Value(args[0]->ToString())));
}

const unity::scopes::Result& Result::get_result() const {
  return result_;
}
