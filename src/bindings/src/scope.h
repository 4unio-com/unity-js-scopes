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

#ifndef _UNITY_JS_SCOPES_H_
#define _UNITY_JS_SCOPES_H_

#include <memory>
#include <string>

#include <unity/scopes/ScopeBase.h>
#include <unity/scopes/Runtime.h>

#include <v8-cpp.h>

#include "scope-base.h"

class JsScope
{
 public:
  JsScope(const std::string& scope_id,
          const std::string& config_file);
  ~JsScope();

  v8::Handle<v8::Object> scope_base();
  void run(v8::FunctionCallbackInfo<v8::Value> const& args);

 private:

  unity::scopes::Runtime::UPtr runtime_;
  std::unique_ptr<ScopeBase> scope_base_;
  std::string scope_id_;
};

#endif // _UNITY_JS_SCOPES_BASE_H_


