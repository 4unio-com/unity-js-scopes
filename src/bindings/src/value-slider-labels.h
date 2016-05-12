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

#ifndef _UNITY_JS_VALUE_SLIDER_LABELS_H_
#define _UNITY_JS_VALUE_SLIDER_LABELS_H_

#include <unity/scopes/ValueSliderLabels.h>

#include <v8-cpp.h>

typedef std::pair<double, std::string> ValueLabelPair;
typedef std::vector<ValueLabelPair> ValueLabelPairList;

class ValueSliderLabels
{
public:
    ValueSliderLabels(v8::FunctionCallbackInfo<v8::Value> const& args);

    std::string min_label() const;
    std::string max_label() const;
    ValueLabelPairList extra_labels() const;
    unity::scopes::VariantMap serialize() const;

    unity::scopes::ValueSliderLabels get_labels() const;

private:
    std::shared_ptr<unity::scopes::ValueSliderLabels> labels_;
};

#endif // _UNITY_JS_VALUE_SLIDER_LABELS_H_


