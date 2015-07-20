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
      : runtime_(unity::scopes::Runtime::create(config_file)),
        scope_base_(new ScopeBase()) {
}

JavascriptScopeRuntime::~JavascriptScopeRuntime() {
}

ScopeBase* JavascriptScopeRuntime::scope_base() {
  // TODO: !!!! wrong object ownership management
  return scope_base_.get();
}

void JavascriptScopeRuntime::run(const std::string& scope_id) {
  std::string current_scope_id = scope_id;

  if (current_scope_id.empty()) {
    char * env_scope_id =
      std::getenv(kJavascriptUnityScopeIdEnvVarName);

    if (env_scope_id) {
      current_scope_id = env_scope_id;
    }
  }

  if ( ! boost::ends_with(current_scope_id, ".ini")) {
    throw std::runtime_error("Invalid scope id (ini file)");
  }

  if (!boost::filesystem::path(current_scope_id).is_absolute()) {
    current_scope_id = boost::filesystem::canonical(current_scope_id).native();
  }

  runtime_->run_scope(scope_base_.get(), current_scope_id);
}
