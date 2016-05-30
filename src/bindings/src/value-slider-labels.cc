/*
 * Copyright 2016 Canonical Ltd.
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

#include "value-slider-labels.h"

ValueSliderLabels::ValueSliderLabels(std::string const &min_label,
                                     std::string const &max_label,
                                     v8::Local<v8::Value> extra_labels) {
  if (extra_labels->IsNull() || extra_labels->IsUndefined()) {
    vsl_.reset(new unity::scopes::ValueSliderLabels(min_label, max_label));
  } else if (extra_labels->IsArray()) {
    std::vector<v8::Local<v8::Value>> labels =
      v8cpp::from_v8<std::vector<v8::Local<v8::Value>>>(
                v8::Isolate::GetCurrent(),
                extra_labels);
    unity::scopes::ValueLabelPairList vlp_list;
    
    for (auto label : labels) {
      if (label->IsObject()) {
          v8::Handle<v8::Object> o =
            v8::Handle<v8::Object>::Cast(label);
          v8::Local<v8::Value> value_string =
            v8::String::NewFromUtf8(
                v8::Isolate::GetCurrent(),
                "value");
          v8::Local<v8::Value> label_string =
            v8::String::NewFromUtf8(
                v8::Isolate::GetCurrent(),
                "label");

          if (o->Has(value_string) && o->Has(label_string)) {
            double v = o->Get(value_string)->ToObject()->NumberValue();
            std::string l =
              *(v8::String::Utf8Value(o->Get(value_string)->ToObject()->ToString()));

            vlp_list.push_back(unity::scopes::ValueLabelPair(v, l));
          }
      }
    }
    vsl_.reset(
        new unity::scopes::ValueSliderLabels(
            min_label, max_label, vlp_list));
  } else {
    throw std::runtime_error("Invalid ValueSliderLabels creation parameters");
  }
}

ValueSliderLabels::ValueSliderLabels(const unity::scopes::ValueSliderLabels& labels) {
  vsl_.reset(new unity::scopes::ValueSliderLabels(labels));
}

std::string ValueSliderLabels::min_label() const {
  return vsl_->min_label();
}

std::string ValueSliderLabels::max_label() const {
  return vsl_->max_label();
}

v8::Local<v8::Value> ValueSliderLabels::extra_labels() const {
  unity::scopes::ValueLabelPairList labels =
    vsl_->extra_labels();

  v8::Handle<v8::Array> a =
    v8::Array::New(v8::Isolate::GetCurrent(), labels.size());

  for (size_t i = 0; i < labels.size(); ++i) {
      v8::Handle<v8::Object> o =
        v8::Object::New(v8::Isolate::GetCurrent());

      v8::Local<v8::Value> value_string =
        v8::String::NewFromUtf8(
                v8::Isolate::GetCurrent(),
                "value");
      v8::Local<v8::Value> label_string =
        v8::String::NewFromUtf8(
                v8::Isolate::GetCurrent(),
                "label");

      o->Set(value_string,
             v8::Number::New(v8::Isolate::GetCurrent(),
                             labels[i].first));
      o->Set(label_string,
             v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),
                                     labels[i].second.c_str()));

      a->Set(i, o);
  }
  return a;
}

unity::scopes::ValueSliderLabels ValueSliderLabels::get_labels() {
  return *vsl_;
}

