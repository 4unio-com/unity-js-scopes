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

#ifndef _UNITY_JS_ACTIVATION_QUERY_PROXY_H_
#define _UNITY_JS_ACTIVATION_QUERY_PROXY_H_

#include <unity/scopes/ActivationQueryBase.h>

#include <v8-cpp.h>


class ActivationQueryProxy : public unity::scopes::ActivationQueryBase
{
 public:
  ActivationQueryProxy(
      std::shared_ptr<unity::scopes::ActivationQueryBase> backend);

  unity::scopes::ActivationResponse activate() override;
  unity::scopes::Result result() const;
  unity::scopes::ActionMetadata action_metadata() const;
  std::string widget_id() const;
  std::string action_id() const;
  void cancelled() override;
  bool valid() const;
  unity::scopes::VariantMap settings() const;

  // TODO handle the subsearch override functions

 private:
  std::shared_ptr<unity::scopes::ActivationQueryBase> backend_;
};

#endif // _UNITY_JS_ACTIVATION_QUERY_PROXY_H_


