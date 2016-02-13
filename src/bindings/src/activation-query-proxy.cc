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

#include "activation-query-proxy.h"

#include <unity/scopes/Result.h>
#include <unity/scopes/ActionMetadata.h>


ActivationQueryProxy::ActivationQueryProxy(
      std::shared_ptr<unity::scopes::ActivationQueryBase> backend)
  : unity::scopes::ActivationQueryBase(
        backend->result(),
        backend->action_metadata(),
        backend->widget_id(),
        backend->action_id()),
    backend_(backend) {
}

void ActivationQueryProxy::cancelled() {
  backend_->cancelled();
}

unity::scopes::ActivationResponse ActivationQueryProxy::activate() {
  return backend_->activate();
}
