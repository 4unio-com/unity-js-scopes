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

#include "preview-reply.h"

#include <stdexcept>

#include <unity/scopes/PreviewReply.h>

PreviewReply::PreviewReply(unity::scopes::PreviewReplyProxy const& reply)
  : reply_(reply){
}

PreviewReply::~PreviewReply() {
}

void PreviewReply::register_layout(std::vector<ColumnLayout*> const& columns) {
  unity::scopes::ColumnLayoutList columns_list;
  for (auto const& column : columns)
  {
    columns_list.emplace_back(column->get_column_layout());
  }
  reply_->register_layout(columns_list);
}

void PreviewReply::push(std::vector<PreviewWidget*> const& widgets) {
  unity::scopes::PreviewWidgetList widgets_list;
  for (auto const& widget : widgets)
  {
    widgets_list.emplace_back(widget->get_preview_widget());
  }
  reply_->push(widgets_list);
}

void PreviewReply::finished()
{
  reply_->finished();
}
