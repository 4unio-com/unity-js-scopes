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

#ifndef _UNITY_JS_PREVIEW_QUERY_PROXY_H_
#define _UNITY_JS_PREVIEW_QUERY_PROXY_H_

#include <unity/scopes/PreviewQueryBase.h>

#include <v8-cpp.h>


class PreviewQueryProxy : public unity::scopes::PreviewQueryBase
{
 public:
  PreviewQueryProxy(
      std::shared_ptr<unity::scopes::PreviewQueryBase> backend);

  void run(unity::scopes::PreviewReplyProxy const &reply) override;
  unity::scopes::Result result () const;
  unity::scopes::ActionMetadata action_metadata () const;
  bool valid() const;
  unity::scopes::VariantMap settings() const;
  void cancelled() override;

  // TODO handle the subsearch override functions

 private:
  std::shared_ptr<unity::scopes::PreviewQueryBase> backend_;
};

#endif // _UNITY_JS_SEARCH_QUERY_PROXY_H_


