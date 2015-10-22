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

#include "canned-query.h"
#include "search-metadata.h"

#include <v8-cpp.h>


/**

--doc:class SearchQuery
 * 
 * Represents a particular query
 *
 * A scope must return an instance of this class from its implementation of Scope.search().
 *
 * @module ScopeJS
 * 
 * @class SearchQuery
 * 
 * @example

     var scopes = require('unity-js-scopes')
     function on_search(canned_query, metadata) {
       return new scopes.lib.search_query(
         canned_query,
         metadata,
         // run
         function(search_reply) {}
         // cancelled
         function() {});
     }
     scopes.self.initialize(
      {}
      ,
      {
        run: function() { },
        start: function(scope_id) { },
        search: on_search,
      }
    );

--/doc:class

--doc:constructor
 * 
 * @constructor
 * @param canned_query
 * @param metadata
 * @param run Function({SearchReply}) Function callback that is to be called by the scope runtime to start the query.
              Your implementation of run() can use the provided SearchReply object to
              push results for the query and call finished() on the reply object when
              you are done with pushing results. You can push results from within run(),
              in which case the query implicitly completes when run() returns.
              Alternatively, run() can store the reply object and return immediately.
 * @param cancelled Function() Called by the scopes runtime when the query originator cancels a query.
              Your implementation of this method should ensure that the scope stops
              processing the current query as soon as possible. Any calls to a `push()` method
              once a query is cancelled are ignored, so continuing to push after cancellation
              only wastes CPU cycles.
--/doc:constructor

--doc:prototype SearchQuery

--doc:member
 * Get a canned query for this search request
 * @method query
 * @return CannedQuery
--doc:/member
query: function() {
}
--/doc:member

--doc:member
 * Get metadata for this search request
 * @method search_metadata
 * @return SearchMetadata
--doc:/member
search_metadata: function() {
}
--/doc:member

--doc:member
 * Check whether this query is still valid
 * @method valid
 * @return Boolean False if the query is finished or was cancelled ealier.
--doc:/member
valid: function() {
}
--/doc:member

--doc:member
 * Returns a dictionary with the scope's current settings
 * @method settings
 * @return Dictionary
--doc:/member
settings: function() {
}
--/doc:member

--/doc:prototype

 */

class SearchQuery : public unity::scopes::SearchQueryBase,
    public std::enable_shared_from_this<SearchQuery>
{
 public:
  SearchQuery(std::shared_ptr<CannedQuery> query,
              std::shared_ptr<SearchMetadata> metadata,
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


