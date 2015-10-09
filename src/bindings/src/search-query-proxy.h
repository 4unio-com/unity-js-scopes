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

#ifndef _UNITY_JS_SEARCH_QUERY_PROXY_H_
#define _UNITY_JS_SEARCH_QUERY_PROXY_H_

#include <unity/scopes/SearchQueryBase.h>

#include <v8-cpp.h>


class SearchQueryProxy : public unity::scopes::SearchQueryBase
{
 public:
  SearchQueryProxy(
      std::shared_ptr<unity::scopes::SearchQueryBase> backend);

  void run(unity::scopes::SearchReplyProxy const &reply) override;
  unity::scopes::CannedQuery query() const;
  unity::scopes::SearchMetadata search_metadata() const;
  void cancelled() override;
  bool valid() const;
  unity::scopes::VariantMap settings() const;

  // TODO handle the subsearch override functions

 private:
  std::shared_ptr<unity::scopes::SearchQueryBase> backend_;
};

#endif // _UNITY_JS_SEARCH_QUERY_PROXY_H_


