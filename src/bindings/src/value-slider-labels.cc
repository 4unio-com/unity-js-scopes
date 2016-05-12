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

ValueSliderLabels::ValueSliderLabels(std::string const& min_label, std::string const& max_label,
                                     ValueLabelPairList const& extra_labels)
    : labels_(unity::scopes::ValueSliderLabels(min_label, max_label, extra_labels)){
}

unity::scopes::ValueSliderLabels ValueSliderLabels::get_labels() const
{
    return labels_;
}
