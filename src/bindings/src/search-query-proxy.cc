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

#include "search-query-proxy.h"

#include <unity/scopes/Result.h>
#include <unity/scopes/SearchMetadata.h>

SearchQueryProxy::SearchQueryProxy(
      std::shared_ptr<unity::scopes::SearchQueryBase> backend)
    : unity::scopes::SearchQueryBase(backend->query(), backend->search_metadata()),
      backend_(backend) {
}

void SearchQueryProxy::run(unity::scopes::SearchReplyProxy const &reply) {
  backend_->run(reply);
}

unity::scopes::CannedQuery SearchQueryProxy::query() const {
  return backend_->query();
}

unity::scopes::SearchMetadata SearchQueryProxy::search_metadata() const {
  return backend_->search_metadata();
}

void SearchQueryProxy::cancelled() {
  backend_->cancelled();
}

bool SearchQueryProxy::valid() const {
  return backend_->valid();
}

unity::scopes::VariantMap SearchQueryProxy::settings() const {
  return backend_->settings();
}
