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

#include "preview-query-proxy.h"

#include <unity/scopes/Result.h>
#include <unity/scopes/ActionMetadata.h>

PreviewQueryProxy::PreviewQueryProxy(
      std::shared_ptr<unity::scopes::PreviewQueryBase> backend)
    : unity::scopes::PreviewQueryBase(backend->result(), backend->action_metadata()),
    backend_(backend) {
}

void PreviewQueryProxy::run(unity::scopes::PreviewReplyProxy const &reply) {
  backend_->run(reply);
}

unity::scopes::Result PreviewQueryProxy::result() const {
  return backend_->result();
}

unity::scopes::ActionMetadata PreviewQueryProxy::action_metadata() const {
  return backend_->action_metadata();
}

void PreviewQueryProxy::cancelled() {
  backend_->cancelled();
}

bool PreviewQueryProxy::valid() const {
  return backend_->valid();
}

unity::scopes::VariantMap PreviewQueryProxy::settings() const {
  return backend_->settings();
}
