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

#ifndef _UNITY_JS_PREVIEW_WIDGET_H_
#define _UNITY_JS_PREVIEW_WIDGET_H_

#include <unity/scopes/PreviewWidget.h>

#include <v8-cpp.h>

class PreviewWidget
{
 public:
  PreviewWidget(v8::Local<v8::Value> arg1,
                v8::Local<v8::Value> arg2);
  PreviewWidget(const unity::scopes::PreviewWidget& preview_widget);

  // v8 binding
  void add_attribute_value(v8::FunctionCallbackInfo<v8::Value> const& args);
  void add_widget(std::shared_ptr<unity::scopes::PreviewWidget> preview_widget);
  std::string id() const;
  void add_attribute_mapping(const std::string& k, const std::string& field_name);
  std::string widget_type() const;
  std::map<std::string, std::string> attribute_mappings() const;
  v8::Local<v8::Object> attribute_values() const;
  std::vector<std::shared_ptr<PreviewWidget>> widgets() const;
  std::string data() const;

  unity::scopes::PreviewWidget & preview_widget() const;

 private:
  v8::Isolate* isolate_;
  std::unique_ptr<unity::scopes::PreviewWidget> preview_widget_;
};

#endif // _UNITY_JS_PREVIEW_WIDGET_H_
