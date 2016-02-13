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

#ifndef _UNITY_JS_SCOPES_BASE_H_
#define _UNITY_JS_SCOPES_BASE_H_

#include <v8-cpp.h>

#include <unity/scopes/ScopeBase.h>

#include "registry.h"

class ScopeBase : public unity::scopes::ScopeBase
{
 public:
  ScopeBase();
  ~ScopeBase() override;

  // v8 bindings
  void onstart(v8::FunctionCallbackInfo<v8::Value> const& args);
  void onstop(v8::FunctionCallbackInfo<v8::Value> const& args);
  void onrun(v8::FunctionCallbackInfo<v8::Value> const& args);

  void onsearch(v8::FunctionCallbackInfo<v8::Value> const& args);
  void onpreview(v8::FunctionCallbackInfo<v8::Value> const& args);
  void onactivate(v8::FunctionCallbackInfo<v8::Value> const& args);
  void onperform_action(v8::FunctionCallbackInfo<v8::Value> const& args);

  std::shared_ptr<Registry> get_registry() const;
  
  // unity::scopes::ScopeBase implementation
  void start(std::string const& scope_id) override;
  void stop() override;
  void run() override;

  unity::scopes::SearchQueryBase::UPtr search(
      unity::scopes::CannedQuery const &query,
      unity::scopes::SearchMetadata const &metadata) override;

  unity::scopes::PreviewQueryBase::UPtr preview(
      unity::scopes::Result const &result,
      unity::scopes::ActionMetadata const &metadata) override;

  unity::scopes::ActivationQueryBase::UPtr activate(
      unity::scopes::Result const &result,
      unity::scopes::ActionMetadata const &metadata) override;

  unity::scopes::ActivationQueryBase::UPtr perform_action(
      unity::scopes::Result const &result,
      unity::scopes::ActionMetadata const &metadata,
      std::string const &widget_id,
      std::string const &action_id) override;

 private:
  v8::Isolate* isolate_;

  v8::Persistent<v8::Function> start_callback_;
  v8::Persistent<v8::Function> stop_callback_;
  v8::Persistent<v8::Function> run_callback_;

  v8::Persistent<v8::Function> search_callback_;
  v8::Persistent<v8::Function> preview_callback_;
  v8::Persistent<v8::Function> perform_action_callback_;
  v8::Persistent<v8::Function> activate_callback_;
};

#endif // _UNITY_JS_SCOPES_BASE_H_


