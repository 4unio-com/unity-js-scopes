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
    std::vector<std::vector<v8::Local<v8::Value>>> labels =
      v8cpp::from_v8<std::vector<std::vector<v8::Local<v8::Value>>>>(
                v8::Isolate::GetCurrent(),
                extra_labels);

    unity::scopes::ValueLabelPairList vlp_list;

    for (auto label : labels) {
      if (label.size() == 2 &&
            label[0]->IsNumber() &&
            label[1]->IsString()) {
        double v = v8cpp::from_v8<double>(
            v8::Isolate::GetCurrent(),
            label[0]);
        std::string l = v8cpp::from_v8<std::string>(
            v8::Isolate::GetCurrent(),
            label[1]);

        vlp_list.push_back(unity::scopes::ValueLabelPair(v, l));
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
      v8::Handle<v8::Array> label_pair =
        v8::Array::New(v8::Isolate::GetCurrent(), 2);

      label_pair->Set(0, v8::Number::New(v8::Isolate::GetCurrent(), labels[i].first));
      label_pair->Set(1, v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), labels[i].second.c_str()));

      a->Set(i, label_pair);
  }
  return a;
}

unity::scopes::ValueSliderLabels ValueSliderLabels::get_labels() {
  return *vsl_;
}

