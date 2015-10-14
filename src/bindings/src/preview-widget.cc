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

#include <unity/scopes/VariantBuilder.h>

#include "common.h"


PreviewWidget::PreviewWidget(v8::Local<v8::Value> arg1,
                             v8::Local<v8::Value> arg2)
      : isolate_(v8::Isolate::GetCurrent()) {
  if (!arg1->IsString()) {
    throw std::runtime_error("Invalid type");
  }

  if (arg2->IsString()) {
    std::string id =
      *(v8::String::Utf8Value(arg1->ToString()));
    std::string widget_type =
      *(v8::String::Utf8Value(arg2->ToString()));

    preview_widget_.reset(
        new unity::scopes::PreviewWidget(id, widget_type));
  } else {
    std::string definition =
      *(v8::String::Utf8Value(arg1->ToString()));

    preview_widget_.reset(
        new unity::scopes::PreviewWidget(definition));
  }
}

PreviewWidget::PreviewWidget(const unity::scopes::PreviewWidget& preview_widget)
  : isolate_(v8::Isolate::GetCurrent()),
    preview_widget_(new unity::scopes::PreviewWidget(preview_widget)) {
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
    preview_widget_->add_attribute_value(key, v);
  } else if (args[1]->IsBoolean()) {
    unity::scopes::Variant v(
        args[1]->BooleanValue());
    preview_widget_->add_attribute_value(key, v);
  } else if (args[1]->IsInt32()) {
    unity::scopes::Variant v(
        args[1]->Int32Value());
    preview_widget_->add_attribute_value(key, v);
  } else if (args[1]->IsNumber()) {
    unity::scopes::Variant v(
        args[1]->NumberValue());
    preview_widget_->add_attribute_value(key, v);
  } else if (args[1]->IsObject()) {
    unity::scopes::VariantBuilder vb;

    unity::scopes::Variant v =
      unity::scopesjs::to_variant(args[1]);

    if (v.which() == unity::scopes::Variant::Dict) {
      unity::scopes::VariantMap vm = v.get_dict();
      std::vector<std::pair<std::string, unity::scopes::Variant>> t;

      for (auto &c : vm) {
        t.push_back({c.first, c.second});
      }

      vb.add_tuple(t);
      preview_widget_->add_attribute_value(key, vb.end());
    }
  }
}

void PreviewWidget::add_widget(
      std::shared_ptr<unity::scopes::PreviewWidget> preview_widget) {
  preview_widget_->add_widget(*preview_widget.get());
}

std::string PreviewWidget::id() const {
  return preview_widget_->id();
}

void PreviewWidget::add_attribute_mapping(const std::string& k,
                                          const std::string& field_name) {
  preview_widget_->add_attribute_mapping(k, field_name);
}

std::string PreviewWidget::widget_type() const {
  return preview_widget_->widget_type();
}

std::map<std::string, std::string> PreviewWidget::attribute_mappings() const {
  return preview_widget_->attribute_mappings();
}

v8::Local<v8::Object> PreviewWidget::attribute_values() const {
  v8::Handle<v8::Object> o = v8::Object::New(isolate_);

  for (auto& v: preview_widget_->attribute_values()) {
    o->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),
                                   v.first.c_str()),
           unity::scopesjs::from_variant(v.second));
  }

  return o;
}

std::vector<std::shared_ptr<PreviewWidget>> PreviewWidget::widgets() const {
  std::vector<std::shared_ptr<PreviewWidget>>
    ws;
  for (auto & w: preview_widget_->widgets()) {
    ws.push_back(std::shared_ptr<PreviewWidget>(new PreviewWidget(w)));
  }
  return ws;
}

std::string PreviewWidget::data() const {
  return preview_widget_->data();
}

unity::scopes::PreviewWidget & PreviewWidget::preview_widget() const {
  return *preview_widget_;
}
