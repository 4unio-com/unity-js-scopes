/*
 * Copyright 2015-2016 Canonical Ltd.
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

#ifndef _UNITY_JS_ACTIVATION_QUERY_H_
#define _UNITY_JS_ACTIVATION_QUERY_H_

#include <unity/scopes/ActivationQueryBase.h>

#include "action-metadata.h"
#include "result.h"
#include "activation-response.h"

#include <v8-cpp.h>

/**

--doc:class ActivationQuery
 * 
 * Represents an activation request that is executed inside a scope
 * 
 * @module ScopeJS
 * @class ActivationQuery
--/doc:class

--doc:prototype ActivationQuery

--doc:member
 * Return response to the activation request
 * @method activate
 * @return ActivationResponse
--doc:/member
activate: function() {
}
--/doc:member

--doc:member
 * Get the result for this activation request handler
 * @method result
 * @return Result
--doc:/member
result: function() {
}
--/doc:member

--doc:member
 * Get the metadata for this activation request handler
 * @method action_metadata
 * @return ActionMetadata
--doc:/member
action_metadata: function() {
}
--/doc:member

--doc:member
 * Get the widget identifier for this activation request handler
 * @method widget_id
 * @return String
--doc:/member
widget_id: function() {
}
--/doc:member

--doc:member
 * Get the action identifier for this activation request handler
 * @method action_id
 * @return String
--doc:/member
action_id: function() {
}
--/doc:member

--doc:member
 * Check whether this query is still valid
 * @method valid
 * @return Boolean
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

class ActivationQuery : public unity::scopes::ActivationQueryBase,
    public std::enable_shared_from_this<ActivationQuery>
{
 public:
  ActivationQuery(v8::FunctionCallbackInfo<v8::Value> const& args);
  ~ActivationQuery();

  void cancelled() override;
  unity::scopes::ActivationResponse activate() override;

  std::shared_ptr<ActionMetaData> action_metadata() const;
  std::shared_ptr<Result> result() const;

 private:
  v8::Isolate* isolate_;

  v8::Persistent<v8::Function> cancelled_callback_;
  v8::Persistent<v8::Function> activate_callback_;
};

#endif // _UNITY_JS_ACTIVATION_QUERY_H_
