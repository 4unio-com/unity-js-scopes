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

#ifndef _UNITY_JS_COLUMN_LAYOUT_H_
#define _UNITY_JS_COLUMN_LAYOUT_H_

#include <unity/scopes/ColumnLayout.h>

#include <v8-cpp.h>

class ColumnLayout
{
 public:
  ColumnLayout(int num_of_columns);
  ~ColumnLayout();

  // v8 implementation
  void add_column(v8::FunctionCallbackInfo<v8::Value> const& args);
  v8::Local<v8::Value> size(v8::FunctionCallbackInfo<v8::Value> const& args);
  v8::Local<v8::Value> number_of_columns(v8::FunctionCallbackInfo<v8::Value> const& args);
  v8::Local<v8::Value> column(v8::FunctionCallbackInfo<v8::Value> const& args);

  const unity::scopes::ColumnLayout&
    get_column_layout() const;

 private:

  unity::scopes::ColumnLayout column_layout_;
};

#endif // _UNITY_JS_COLUMN_LAYOUT_H_
