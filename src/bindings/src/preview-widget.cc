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

#include "preview-widget.h"

PreviewWidget::PreviewWidget(std::string const &id,
                             std::string const &widget_type)
  : preview_widget_(id, widget_type) {
}

PreviewWidget::PreviewWidget(std::string const &definition)
  : preview_widget_(definition) {
}

PreviewWidget::~PreviewWidget() {
}

void PreviewWidget::add_attribute_value(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 2) {
    return;
  }
  if (!args[0]->IsString()) {
    return;
  }

  std::string key =
    *v8::String::Utf8Value(args[0]->ToString());

  if (args[1]->IsString()) {
    unity::scopes::Variant v(
        *v8::String::Utf8Value(args[1]->ToString()));
    preview_widget_.add_attribute_value(key, v);
  } else if (args[1]->IsBoolean()) {
    unity::scopes::Variant v(
        args[1]->BooleanValue());
    preview_widget_.add_attribute_value(key, v);
  } else if (args[1]->IsInt32()) {
    unity::scopes::Variant v(
        args[1]->Int32Value());
    preview_widget_.add_attribute_value(key, v);
  } else if (args[1]->IsNumber()) {
    unity::scopes::Variant v(
        args[1]->NumberValue());
    preview_widget_.add_attribute_value(key, v);
  }
}

void PreviewWidget::add_attribute_mapping(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 2) {
    return;
  }
  if (!args[0]->IsString() || !args[1]->IsString()) {
    return;
  }

  std::string key =
    *v8::String::Utf8Value(args[0]->ToString());

  std::string field_name =
    *v8::String::Utf8Value(args[1]->ToString());

  preview_widget_.add_attribute_mapping(
      key, field_name);
}

void PreviewWidget::add_widget(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    return;
  }

  PreviewWidget *pw =
    v8cpp::from_v8<PreviewWidget*>(args.GetIsolate(), args[0]);
  if (!pw) {
    return;
  }

  preview_widget_.add_widget(pw->get_preview_widget());
}

const unity::scopes::PreviewWidget&
PreviewWidget::get_preview_widget() const {
  return preview_widget_;
}

v8::Local<v8::Value> PreviewWidget::id(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), preview_widget_.id());
}

v8::Local<v8::Value> PreviewWidget::widget_type(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), preview_widget_.widget_type());
}

v8::Local<v8::Value> PreviewWidget::attribute_mappings(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  std::map<std::string, std::string> am =
    preview_widget_.attribute_mappings();
  return v8cpp::to_v8(args.GetIsolate(), am);
}

v8::Local<v8::Value> PreviewWidget::attribute_values(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), nullptr);
}

v8::Local<v8::Value> PreviewWidget::widgets(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), nullptr);
}

v8::Local<v8::Value> PreviewWidget::data(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  return v8cpp::to_v8(args.GetIsolate(), preview_widget_.data().c_str());
}
