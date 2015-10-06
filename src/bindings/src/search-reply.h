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

#ifndef _UNITY_JS_SEARCH_REPLY_H_
#define _UNITY_JS_SEARCH_REPLY_H_

#include <unity/scopes/SearchReplyProxyFwd.h>
#include <unity/scopes/Category.h>
#include <unity/scopes/CategorisedResult.h>

#include <v8-cpp.h>


class SearchReply
{
 public:
  SearchReply(unity::scopes::SearchReplyProxy const& reply);
  ~SearchReply();

  unity::scopes::Category::SCPtr register_category(
      const std::string& id,
      const std::string& title,
      const std::string& icon,
      std::shared_ptr<unity::scopes::CategoryRenderer> category_renderer);

  unity::scopes::Category::SCPtr
    lookup_category(const std::string& id);

  void push(std::shared_ptr<unity::scopes::CategorisedResult> categorised_result);

 private:

  unity::scopes::SearchReplyProxy const reply_;
};

#endif // _UNITY_JS_SEARCH_REPLY_H_


