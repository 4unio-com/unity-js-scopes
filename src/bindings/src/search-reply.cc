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

#include "search-reply.h"

#include <stdexcept>

#include <unity/scopes/SearchReply.h>


SearchReply::SearchReply(unity::scopes::SearchReplyProxy const& reply)
  : reply_(reply){
}

SearchReply::~SearchReply() {
}

unity::scopes::Category::SCPtr SearchReply::lookup_category(
      const std::string& id) {
  return reply_->lookup_category(id);
}

void SearchReply::push(
      std::shared_ptr<unity::scopes::CategorisedResult> categorised_result) {
  reply_->push(*categorised_result);
}

unity::scopes::Category::SCPtr SearchReply::register_category(
      const std::string& id,
      const std::string& title,
      const std::string& icon,
      std::shared_ptr<unity::scopes::CategoryRenderer> category_renderer) {
  return reply_->register_category(
      id,
      title,
      icon,
      category_renderer ? *category_renderer : unity::scopes::CategoryRenderer());
}
