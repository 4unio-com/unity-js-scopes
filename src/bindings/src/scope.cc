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

#include "scope.h"

#include <cstdlib>

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "../../common/config.h"


JavascriptScopeRuntime::JavascriptScopeRuntime(
      const std::string& config_file)
      : scope_base_(new ScopeBase()) {
    std::string current_runtime_config = config_file;

    if (current_runtime_config.empty()) {
      char * env_runtime_config =
        std::getenv(kJavascriptUnityRuntimeEnvVarName);

      if (env_runtime_config) {
        current_runtime_config = env_runtime_config;

        if ( ! boost::ends_with(current_runtime_config, ".ini")) {
          throw std::runtime_error("Invalid runtime config (ini file)");
        }

        if (!boost::filesystem::path(current_runtime_config).is_absolute()) {
          current_runtime_config = boost::filesystem::canonical(current_runtime_config).native();
        }
      }
    }

    runtime_ = unity::scopes::Runtime::create(current_runtime_config);
}

JavascriptScopeRuntime::~JavascriptScopeRuntime() {
}

ScopeBase* JavascriptScopeRuntime::scope_base() {
  // TODO: !!!! wrong object ownership management
  return scope_base_.get();
}

void JavascriptScopeRuntime::run(const std::string& scope_config) {
  if (!scope_config_.empty()) {
    throw std::runtime_error("Scope already running");
  }

  std::string current_scope_config = scope_config;

  if (current_scope_config.empty()) {
    char * env_scope_config =
      std::getenv(kJavascriptUnityScopeIdEnvVarName);

    if (env_scope_config) {
      current_scope_config = env_scope_config;
    }
  }

  if ( ! boost::ends_with(current_scope_config, ".ini")) {
    throw std::runtime_error("Invalid scope id (ini file)");
  }

  if (!boost::filesystem::path(current_scope_config).is_absolute()) {
    current_scope_config = boost::filesystem::canonical(current_scope_config).native();
  }

  scope_config_ = current_scope_config;

  // Unlock access to the main isolate so that our callbacks will work
  v8::Unlocker unlocker(v8::Isolate::GetCurrent());
  runtime_->run_scope(scope_base_.get(), current_scope_config);
}

std::string JavascriptScopeRuntime::scope_config() const {
  return scope_config_;
}
