/*
 * Copyright 2016 Canonical Ltd.
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

#ifndef _UNITY_JS_ACTIVATION_RESPONSE_H_
#define _UNITY_JS_ACTIVATION_RESPONSE_H_

#include <unity/scopes/ActivationResponse.h>

#include "action-metadata.h"
#include "canned-query.h"
#include "variant.h"
#include "result.h"

#include <v8-cpp.h>

/**

--doc:class ActivationResponse
 * 
 * Represents response to a result activation
 * 
 * @module ScopeJS
 * @class ActivationResponse
--/doc:class

--doc:constructor
 *
 * @constructor
 * @param status|query ActivationResponseStatus to create a response with given status or CannedQuery to create an ActivationResponse with status defs.ActivationResponseStatus.PerformQuery and a search query to be executed
--/doc:constructor

--doc:prototype ActivationResponse

--doc:member
 * Get activation status
 * @method status
 * @return ActivationResponseStatus
--doc:/member
status: function() {
}
--/doc:member

--doc:member
 * Attach arbitrary data to this response
 * @method set_scope_data
 * @param data
--doc:/member
set_scope_data: function(data: {Object}) {
}
--/doc:member

--doc:member
 * Get data attached to this response object
 * @method scope_data
 * @return Object
--doc:/member
scope_data: function() {
}
--/doc:member

--doc:member
 * A query to be executed if status is defs.ActivationResponseStatus.PerformQuery
 * @method query
 * @return CannedQuery
--doc:/member
query: function() {
}
--/doc:member

--/doc:prototype
 */

class ActivationResponse
{
 public:
  ActivationResponse();
  ActivationResponse(v8::Local<v8::Value> const& arg);
  ~ActivationResponse();

  int status();
  std::shared_ptr<CannedQuery> query() const;
  unity::scopes::Variant scope_data() const;
  void set_scope_data(unity::scopes::Variant const&);

  unity::scopes::ActivationResponse get_activation_response() const;

 private:
  std::unique_ptr<unity::scopes::ActivationResponse> activation_response_;
};

#endif // _UNITY_JS_ACTIVATION_QUERY_H_
