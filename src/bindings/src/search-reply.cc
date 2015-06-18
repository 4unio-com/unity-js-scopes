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

#include "search-reply.h"

#include "category.h"

SearchReply::SearchReply(unity::scopes::SearchReplyProxy const& reply)
  : reply_(reply){
}

SearchReply::~SearchReply() {
}

v8::Local<v8::Value> SearchReply::register_category(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 3) {
    // TODO fix
    throw std::exception("Invalid number of arguments");
  }

  if (!args[0]->IsString()
      || !args[1]->IsString()
      || !args[2]->IsString()) {
    // TODO fix
    throw std::exception("Invalid type of arguments");
  }

  std::string id;
  std::string title;
  std::string icon;

  id = *(v8::String::Utf8Value(args[0]->ToString()));
  title = *(v8::String::Utf8Value(args[1]->ToString()));
  icon = *(v8::String::Utf8Value(args[2]->ToString()));

  Category *category = new Category(*reply_.register_category(is, title, icon));

  v8::Isolate *isolate = args.GetIsolate();

  return v8cpp::export_object<Category>(isolate, category);
}

void SearchReply::push(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    // TODO fix
    throw std::exception("Invalid number of arguments");
  }

  CategorisedResult *r =
    v8cpp::import_object<CategorisedResult>(
        Isolate::GetCurrent(),
        args[0]->ToObject());
  if (!r) {
    throw std::exception("Invalid argument type");
  }

  reply_.push(r);
}
