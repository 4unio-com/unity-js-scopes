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

#ifndef _UNITY_JS_PREVIEW_REPLY_H_
#define _UNITY_JS_PREVIEW_REPLY_H_

#include <unity/scopes/PreviewReply.h>

#include "preview-widget.h"

#include <v8-cpp.h>

/**

--doc:class PreviewReply
 * @module ScopeJS
 * 
 * Allows the results of a preview to be sent to the preview requester.
 * 
 * @class PreviewReply
--/doc:class

--doc:prototype PreviewReply

--doc:member
 * Registers a list of column layouts for the current preview
 * @method register_layout
 * @param layout {Array of Column layout}
--doc:/member
register_layout: function(layout) {
}
--/doc:member

--doc:member
 * Sends widget definitions to the sender of the preview query
 * @method push
 * @param widget_list {Array of PreviewWidget}
--doc:/member
push: function(widget_list) {
}
--/doc:member

--doc:member
 * Informs the source of a query that the query results are complete
 * @method finished
 * @return Boolean
--doc:/member
finished: function() {
}
--/doc:member

--doc:member
 * Informs the source of a query that the query was terminated due to an error
 * @method error
 * @return error String error
--doc:/member
error: function(error) {
}
--/doc:member

--/doc:prototype

 */

class PreviewReply
{
 public:
  PreviewReply(unity::scopes::PreviewReplyProxy const& reply);
  ~PreviewReply();

  // v8 bindings
  void register_layout(
      std::vector<std::shared_ptr<unity::scopes::ColumnLayout>> const& columns);
  void push(
      std::vector<std::shared_ptr<PreviewWidget>> const& widgets);
  void finished();

 private:
  unity::scopes::PreviewReplyProxy const reply_;
};

#endif // _UNITY_JS_PREVIEW_REPLY_H_


