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

#include "categorised-result.h"

#include <stdexcept>

#include <unity/scopes/SearchReply.h>


SearchReply::SearchReply(unity::scopes::SearchReplyProxy const& reply)
  : isolate_(v8::Isolate::GetCurrent())
  , reply_(reply){
}

unity::scopes::Category::SCPtr SearchReply::lookup_category(
      const std::string& id) {
  return reply_->lookup_category(id);
}

bool SearchReply::push(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1 && args.Length() != 2) {
    throw std::runtime_error("Invalid number of arguments");
  }

  if (args.Length() == 1) {
    auto cr =
      v8cpp::from_v8<std::shared_ptr<CategorisedResult>>(isolate_, args[0]);
    return reply_->push(*cr);
  }

  // TODO fix v8cpp shortcoming here
  auto filters =
    v8cpp::from_v8<std::list<v8::Value>>(isolate_, args[0]);
  //  auto filter_state =
  //  v8cpp::from_v8<std::shared_ptr<unity::scopes::FilterState>>(isolate_, args[1]);

  return reply_->push(
      unity::scopes::Filters(),
      unity::scopes::FilterState());//*filter_state);
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

void SearchReply::finished()
{
  reply_->finished();
}
