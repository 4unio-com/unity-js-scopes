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

#include "preview-query.h"

PreviewQuery::PreviewQuery(
      unity::scopes::Result const& result,
      unity::scopes::ActionMetadata const& metadata,
      const v8::Local<v8::Function> &run_callback)
  : unity::scopes::PreviewQueryBase(result, metadata),
    run_callback_(v8::Isolate::GetCurrent(), run_callback) {
}

PreviewQuery::~PreviewQuery() {
  if (!run_callback_.IsEmpty()) {
    run_callback_.Reset();
  }
}

void PreviewQuery::onrun(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    return;
  }

  if (!args[0]->IsFunction()) {
    // TODO fix
    return;
  }

  if (!run_callback_.IsEmpty()) {
    run_callback_.Reset();
  }

  v8::Local<v8::Function> cb = v8::Handle<v8::Function>::Cast(args[0]);
  run_callback_.Reset(args.GetIsolate(), cb);
}

void PreviewQuery::run(unity::scopes::PreviewReplyProxy const& reply) {
}

