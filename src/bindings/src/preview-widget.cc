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

#include "common.h"


PreviewWidget::PreviewWidget(std::string const &id,
                             std::string const &widget_type)
  : unity::scopes::PreviewWidget(id, widget_type) {
}

PreviewWidget::PreviewWidget(std::string const &definition)
  : unity::scopes::PreviewWidget(definition) {
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
    unity::scopes::PreviewWidget::add_attribute_value(key, v);
  } else if (args[1]->IsBoolean()) {
    unity::scopes::Variant v(
        args[1]->BooleanValue());
    unity::scopes::PreviewWidget::add_attribute_value(key, v);
  } else if (args[1]->IsInt32()) {
    unity::scopes::Variant v(
        args[1]->Int32Value());
    unity::scopes::PreviewWidget::add_attribute_value(key, v);
  } else if (args[1]->IsNumber()) {
    unity::scopes::Variant v(
        args[1]->NumberValue());
    unity::scopes::PreviewWidget::add_attribute_value(key, v);
  }
}

void PreviewWidget::add_widget(
      std::shared_ptr<unity::scopes::PreviewWidget> preview_widget) {
  unity::scopes::PreviewWidget::add_widget(*preview_widget.get());
}
