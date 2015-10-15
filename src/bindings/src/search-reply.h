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

#include "categorised-result.h"

#include <v8-cpp.h>


/**

--doc:class SearchReply
 * Allows the results of a preview to be sent to the preview requester.
 * 
 * @class SearchReply
--/doc:class

--doc:prototype SearchReply

--doc:member
 * Register new category and send it to the source of the query
 * @param id String id
 * @param title String title
 * @param icon String icon
 * @param category_renderer CategoryRenderer
--doc:/member
register_category: function(String: id, String: title, String: icon, [optional] CategoryRenderer: category_renderer) {
}
--/doc:member

--doc:member
 * Returns a previously registered category
 * @param id
--doc:/member
lookup_category: function(String: id) {
}
--/doc:member

--doc:member
 * Sends a single result to the source of a query
 * @param result CategorisedResult
--doc:/member
push: function(CategorisedResult: result) {
}
--/doc:member

--doc:member
 * Informs the source of a query that the query was terminated due to an error
 * @return error String error
--doc:/member
error: function(String: error) {
}
--/doc:member

--doc:member
 * Informs the source of a query that the query results are complete
--doc:/member
finished: function() {
}
--/doc:member

--/doc:prototype

 */

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

  void push(std::shared_ptr<CategorisedResult> categorised_result);

  void finished();

 private:

  unity::scopes::SearchReplyProxy const reply_;
};

#endif // _UNITY_JS_SEARCH_REPLY_H_


