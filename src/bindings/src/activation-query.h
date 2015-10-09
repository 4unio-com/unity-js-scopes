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

#ifndef _UNITY_JS_ACTIVATION_QUERY_H_
#define _UNITY_JS_ACTIVATION_QUERY_H_

#include <unity/scopes/ActivationQueryBase.h>

#include <v8-cpp.h>

class ActivationQuery : public unity::scopes::ActivationQueryBase,
  public std::enable_shared_from_this<ActivationQuery>
{
 public:
  ActivationQuery(unity::scopes::Result const& result,
                  unity::scopes::ActionMetadata const& metadata,
                  const v8::Local<v8::Function> &cancelled_callback);
  ~ActivationQuery() override;

  // v8 bindings
  v8::Local<v8::Value> activate(v8::FunctionCallbackInfo<v8::Value> const& args);

  // PreviewQueryBase implementation
  void cancelled() override;

 private:
  v8::Isolate* isolate_;

  v8::Persistent<v8::Function> cancelled_callback_;
};

#endif // _UNITY_JS_ACTIVATION_QUERY_H_
