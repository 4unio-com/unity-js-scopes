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

#include <v8-cpp.h>

#include <node.h>

#include "scope-base.h"
#include "scope.h"
#include "canned-query.h"
#include "category.h"
#include "categorized-result.h"
#include "search-query.h"
#include "search-reply.h"

v8::Handle<v8::Object> new_scope(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 2) {
    throw std::exception("Invalid number of arguments");
  }
  if (!args[0]->IsString() || !args[1]->IsString()) {
    throw std::exception("Invalid arguments types");
  }

  std::string scope_id = *(v8::String::Utf8Value(args[0]->ToString()));
  std::string config_fgile = *(v8::String::Utf8Value(args[1]->ToString()));

  JsScope* scope = new JsScope(scope_id, config_file);
  auto x = v8cpp::export_object<JsScope>(v8::Isolate::GetCurrent(), scope);
  return x;
}

void InitAll(v8::Handle<v8::Object> exports)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    v8cpp::Class<JsScope> js_scope(isolate);
    js_scope
      .add_method("scope_base", &SearchHandler::scope_base);

    v8cpp::Class<ScopeBase> scope_base(isolate);
    scope_base
      .add_method("onstart", &ScopeBase::onstart)
      .add_method("onstop", &ScopeBase::onstop)
      .add_method("onrun", &ScopeBase::onrun)
      .add_method("onsearch", &ScopeBase::onsearch);

    v8cpp::Class<Category> category(isolate);
    category
      .add_method("id", &Category::id)
      .add_method("title", &Category::title)
      .add_method("icon", &Category::icon);

    v8cpp::Class<CategorisedResult> categorised_result(isolate);
    categorised_result
      .set_constructor()
      .add_method("set_uri", &CategorisedResult::set_uri)
      .add_method("set_title", &CategorisedResult::set_title);

    v8cpp::Class<CannedQuery> canned_query(isolate);
    canned_query
      .set_constructor()
      .add_method("query_string", &CannedQuery::query_string)
      .add_method("to_uri", &CannedQuery::to_uri);

    v8cpp::Class<SearchReply> search_reply(isolate);
    search_reply
      .add_method("register_category", &SearchReply::register_category)
      .add_method("push", &SearchReply::push);

    v8cpp::Class<SearchQuery> search_query(isolate);
    search_query
      .set_constructor<v8::Local<v8::Object>,
                       v8::Local<v8::Object>,
                       v8::Local<v8::Function>,
                       v8::Local<v8::Function> >()
      .add_method("onrun", &SearchQuery::onrun)
      .add_method("oncancelled", &SearchQuery::oncancelled);

    v8cpp::Module module(isolate);
    module.add_function("new_scope", &new_scope);

    exports->SetPrototype(module.create_prototype());
}

NODE_MODULE(addon, InitAll)
