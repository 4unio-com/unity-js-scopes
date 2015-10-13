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

#ifndef _UNITY_JS_SEARCH_QUERY_H_
#define _UNITY_JS_SEARCH_QUERY_H_

#include <unity/scopes/SearchQueryBase.h>

#include <v8-cpp.h>

class SearchQuery : public unity::scopes::SearchQueryBase,
    public std::enable_shared_from_this<SearchQuery>
{
 public:
  SearchQuery(std::shared_ptr<unity::scopes::CannedQuery> query,
              std::shared_ptr<unity::scopes::SearchMetadata> metadata,
              const v8::Local<v8::Function> &run_callback,
              const v8::Local<v8::Function> &cancelled_callback);
  ~SearchQuery() override;

  // v8 binding
  void onrun(v8::FunctionCallbackInfo<v8::Value> const& args);
  void oncancelled(v8::FunctionCallbackInfo<v8::Value> const& args);
 
  // unity::scopes::SearchQueryBase implementation
  void run(unity::scopes::SearchReplyProxy const& reply) override;
  void cancelled() override;

 private:
  v8::Isolate* isolate_;

  v8::Persistent<v8::Function> run_callback_;
  v8::Persistent<v8::Function> cancelled_callback_;
};

#endif // _UNITY_JS_SEARCH_QUERY_H_


