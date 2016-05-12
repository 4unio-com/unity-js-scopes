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

#include "common.h"

//std::string const& min_label, std::string const& max_label, ValueLabelPairList const& extra_labels

ValueSliderLabels::ValueSliderLabels(v8::FunctionCallbackInfo<v8::Value> const& args)
{
    if (args.Length() != 2 && args.Length() != 3) {
      throw std::runtime_error("Invalid number of arguments");
    }
    if (!args[0]->IsString()) {
      throw std::runtime_error("Invalid argument type");
    }
    if (!args[1]->IsString()) {
      throw std::runtime_error("Invalid argument type");
    }

    std::string min_label =
      *(v8::String::Utf8Value(args[0]->ToString()));

    std::string max_label =
      *(v8::String::Utf8Value(args[1]->ToString()));

    if (args.Length() == 3)
    {
        ValueLabelPairList extra_labels;

        try
        {
            auto extra_labels_a = unity::scopesjs::to_variant(args[2]).get_array();

            for (auto const& label : extra_labels_a)
            {
                auto label_pair = label.get_array();
                if (label_pair.size() == 2)
                {
                    extra_labels.push_back(ValueLabelPair(label_pair[0].get_double(), label_pair[1].get_string()));
                }
            }
        } catch(...)
        {
            throw std::runtime_error("ValueSliderLabels::ValueSliderLabels: Malformed 'extra_labels' argument! Expected format: [[2, \"2\"], [4, \"4\"]]");
        }

        labels_ = std::make_shared<unity::scopes::ValueSliderLabels>(unity::scopes::ValueSliderLabels(min_label, max_label, extra_labels));
    }
    else
    {
        labels_ = std::make_shared<unity::scopes::ValueSliderLabels>(unity::scopes::ValueSliderLabels(min_label, max_label));
    }
}

std::string ValueSliderLabels::min_label() const
{
    return labels_->min_label();
}

std::string ValueSliderLabels::max_label() const
{
    return labels_->max_label();
}

ValueLabelPairList ValueSliderLabels::extra_labels() const
{
    return labels_->extra_labels();
}

unity::scopes::ValueSliderLabels ValueSliderLabels::get_labels() const
{
    return *labels_;
}
