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

#include "activation-query-proxy.h"

#include <unity/scopes/Result.h>
#include <unity/scopes/ActionMetadata.h>

ActivationQueryProxy::ActivationQueryProxy(
      std::shared_ptr<unity::scopes::ActivationQueryBase> backend)
  : unity::scopes::ActivationQueryBase(backend->result(), backend->action_metadata()),
    backend_(backend) {
}

unity::scopes::ActivationResponse ActivationQueryProxy::activate() {
  return backend_->activate();
}

unity::scopes::Result ActivationQueryProxy::result() const {
  return backend_->result();
}

unity::scopes::ActionMetadata ActivationQueryProxy::action_metadata() const {
  return backend_->action_metadata();
}

std::string ActivationQueryProxy::widget_id() const {
  return backend_->widget_id();
}

std::string ActivationQueryProxy::action_id() const {
  return backend_->action_id();
}

void ActivationQueryProxy::cancelled() {
  backend_->cancelled();
}

bool ActivationQueryProxy::valid() const {
  return backend_->valid();
}

unity::scopes::VariantMap ActivationQueryProxy::settings() const {
  return backend_->settings();
}
