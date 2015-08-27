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

#include <unity/scopes/PreviewReplyProxyFwd.h>
#include "column-layout.h"
#include "preview-widget.h"

#include <v8-cpp.h>

class PreviewReply
{
 public:
  PreviewReply(unity::scopes::PreviewReplyProxy const& reply);
  ~PreviewReply();

  // v8 bindings
  void register_layout(std::vector<ColumnLayout*> const& columns);
  void push(std::vector<PreviewWidget*> const& widgets);
  void finished();

 private:
  unity::scopes::PreviewReplyProxy const& reply_;
};

#endif // _UNITY_JS_PREVIEW_REPLY_H_


