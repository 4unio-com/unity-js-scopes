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

#include "preview-reply.h"

#include <stdexcept>

#include <unity/scopes/PreviewReply.h>

PreviewReply::PreviewReply(unity::scopes::PreviewReplyProxy const& reply)
  : reply_(reply){
}

PreviewReply::~PreviewReply() {
}

v8::Local<v8::Value> PreviewReply::register_layout(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 3) {
    // TODO fix
    throw std::runtime_error("Invalid number of arguments");
  }
}

void PreviewReply::push(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
}
