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

#include "column-layout.h"

ColumnLayout::ColumnLayout(int num_of_columns)
  : column_layout_(num_of_columns) {
}

ColumnLayout::~ColumnLayout() {
}

void ColumnLayout::add_column(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    return;
  }

  if (!args[0]->IsArray()) {
    return;
  }

  std::vector<std::string> columns;

  v8::Handle<v8::Array> array =
    v8::Handle<v8::Array>::Cast(args[0]);
  for (size_t i = 0; i < array->Length(); i++) {
    v8::Local<v8::Value> element = array->Get(i);
    if (!element->IsString()) {
      return;
    }
    columns.push_back(
        *v8::String::Utf8Value(element->ToString()));
  }
  column_layout_.add_column(columns);
}

v8::Local<v8::Value> ColumnLayout::size(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), column_layout_.size());
}

v8::Local<v8::Value> ColumnLayout::number_of_columns(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), column_layout_.number_of_columns());
}

v8::Local<v8::Value> ColumnLayout::column(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (!args.Length() != 1 || !args[0]->IsInt32()) {
    return v8cpp::to_v8(args.GetIsolate(), nullptr);
  }

  int index = args[0]->Int32Value();
  std::vector<std::string> c =
    column_layout_.column(index);

  v8::Handle<v8::Array> array =
    v8::Array::New(args.GetIsolate(), c.size());

  for (std::vector<std::string>::size_type i = 0;
       i < c.size();
       ++i) {
    array->Set(i, v8::String::NewFromUtf8(args.GetIsolate(), c[i].c_str()));
  }
  return array;
}

const unity::scopes::ColumnLayout& ColumnLayout::get_column_layout() const {
  return column_layout_;
}
