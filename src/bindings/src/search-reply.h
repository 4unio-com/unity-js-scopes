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

#include <v8-cpp.h>

class SearchReply
{
 public:
  SearchReply(unity::scopes::SearchReplyProxy const& reply);
  ~SearchReply();

  v8::Local<v8::Value> register_category(v8::FunctionCallbackInfo<v8::Value> const& args);
  void push(v8::FunctionCallbackInfo<v8::Value> const& args);

 private:

  unity::scopes::SearchReplyProxy const reply_;
};

#endif // _UNITY_JS_SEARCH_REPLY_H_


