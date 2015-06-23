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

#include <stdexcept>

#include <node.h>

#include "scope-base.h"
#include "scope.h"
#include "canned-query.h"
#include "category.h"
#include "categorised-result.h"
#include "category-renderer.h"
#include "search-query.h"
#include "search-reply.h"
#include "search-metadata.h"
#include "result.h"
#include "action-metadata.h"
#include "preview-query.h"
#include "preview-widget.h"

v8::Handle<v8::Object> new_scope(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 2) {
    throw std::runtime_error("Invalid number of arguments");
  }
  if (!args[0]->IsString() || !args[1]->IsString()) {
    throw std::runtime_error("Invalid arguments types");
  }

  std::string scope_id = *(v8::String::Utf8Value(args[0]->ToString()));
  std::string config_file = *(v8::String::Utf8Value(args[1]->ToString()));

  JsScope* scope = new JsScope(scope_id, config_file);
  return v8cpp::export_object<JsScope>(v8::Isolate::GetCurrent(), scope);
}

v8::Handle<v8::Object> new_search_query(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 4) {
    throw std::runtime_error("Invalid number of arguments");
  }

  CannedQuery *c =
    v8cpp::import_object<CannedQuery>(v8::Isolate::GetCurrent(), args[0]->ToObject());

  SearchMetaData *s =
    v8cpp::import_object<SearchMetaData>(v8::Isolate::GetCurrent(), args[1]->ToObject());

  if (!c || !s) {
    throw std::runtime_error("Invalid arguments types");
  }

  if (!args[2]->IsFunction() || !args[3]->IsFunction()) {
    throw std::runtime_error("Invalid arguments types");
  }

  v8::Local<v8::Function> run_callback =
    v8::Handle<v8::Function>::Cast(args[2]);
  v8::Local<v8::Function> cancelled_callback =
    v8::Handle<v8::Function>::Cast(args[3]);

  SearchQuery *sq =
    new SearchQuery(
        c->get_canned_query(),
        static_cast<const unity::scopes::SearchMetadata&>(*s),
        run_callback,
        cancelled_callback);
  return v8cpp::export_object<SearchQuery>(v8::Isolate::GetCurrent(), sq);
}

v8::Handle<v8::Object> new_category_renderer(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    throw std::runtime_error("Invalid number of arguments");
  }
  if (!args[0]->IsString()) {
    throw std::runtime_error("Invalid arguments types");
  }

  std::string json_text = *(v8::String::Utf8Value(args[0]->ToString()));

  CategoryRenderer* category_renderer = new CategoryRenderer(json_text);
  return v8cpp::export_object<CategoryRenderer>(
      v8::Isolate::GetCurrent(), category_renderer);
}

v8::Handle<v8::Object> new_preview_query(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 4) {
    throw std::runtime_error("Invalid number of arguments");
  }

  Result *r = v8cpp::import_object<Result>(v8::Isolate::GetCurrent(), args[0]->ToObject());

  ActionMetaData *a =
    v8cpp::import_object<ActionMetaData>(v8::Isolate::GetCurrent(), args[1]->ToObject());

  if (!r || !a) {
    throw std::runtime_error("Invalid arguments types");
  }

  if (!args[2]->IsFunction()) {
    throw std::runtime_error("Invalid arguments types");
  }

  v8::Local<v8::Function> run_callback =
    v8::Handle<v8::Function>::Cast(args[2]);

  if (!args[3]->IsFunction()) {
    throw std::runtime_error("Invalid arguments types");
  }

  v8::Local<v8::Function> cancelled_callback =
    v8::Handle<v8::Function>::Cast(args[3]);

  PreviewQuery *pq =
    new PreviewQuery(
        r->get_result(),
        a->get_action_metadata(),
        run_callback,
        cancelled_callback);
  return v8cpp::export_object<PreviewQuery>(v8::Isolate::GetCurrent(), pq);
}

v8::Handle<v8::Object> new_preview_widget(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() < 1 || args.Length() > 2) {
    throw std::runtime_error("Invalid number of arguments");
  }

  if (args.Length() == 2) {
    if (!args[0]->IsString() || !args[1]->IsString()) {
      throw std::runtime_error("Invalid arguments types");
    }
    std::string id =
      *(v8::String::Utf8Value(args[0]->ToString()));

    std::string widget_type =
      *(v8::String::Utf8Value(args[1]->ToString()));

    PreviewWidget* preview_widget =
      new PreviewWidget(id, widget_type);

    return v8cpp::export_object<PreviewWidget>(
        v8::Isolate::GetCurrent(), preview_widget);
  }

  if (!args[0]->IsString()) {
    throw std::runtime_error("Invalid arguments types");
  }
  
  std::string definition =
    *(v8::String::Utf8Value(args[0]->ToString()));
  
  PreviewWidget* preview_widget =
    new PreviewWidget(definition);
  
  return v8cpp::export_object<PreviewWidget>(
        v8::Isolate::GetCurrent(), preview_widget);
}

v8::Handle<v8::Object> new_categorised_result(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1) {
    throw std::runtime_error("Invalid number of arguments");
  }

  Category *c =
    v8cpp::import_object<Category>(v8::Isolate::GetCurrent(),
                                   args[0]->ToObject());

  if (!c) {
    throw std::runtime_error("Invalid arguments types");
  }

  CategorisedResult *cr = new CategorisedResult(c);

  return v8cpp::export_object<CategorisedResult>(v8::Isolate::GetCurrent(), cr);
}

void InitAll(v8::Handle<v8::Object> exports)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    v8cpp::Class<JsScope> js_scope(isolate);
    js_scope
      .add_method("run", &JsScope::run);

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
      .add_method("set_uri", &CategorisedResult::set_uri)
      .add_method("set_title", &CategorisedResult::set_title);

    v8cpp::Class<CannedQuery> canned_query(isolate);
    canned_query
      .add_method("query_string", &CannedQuery::query_string)
      .add_method("to_uri", &CannedQuery::to_uri);

    v8cpp::Class<SearchReply> search_reply(isolate);
    search_reply
      .add_method("register_category", &SearchReply::register_category)
      .add_method("push", &SearchReply::push);

    v8cpp::Class<Result> result(isolate);
    result
      .add_method("art", &Result::art)
      .add_method("set_art", &Result::set_art)
      .add_method("title", &Result::title)
      .add_method("set_title", &Result::set_title)
      .add_method("dnd_uri", &Result::dnd_uri)
      .add_method("set_dnd_uri", &Result::set_dnd_uri)
      .add_method("uri", &Result::uri)
      .add_method("set_uri", &Result::set_uri);

    v8cpp::Class<SearchQuery> search_query(isolate);
    search_query
      .add_method("onrun", &SearchQuery::onrun)
      .add_method("oncancelled", &SearchQuery::oncancelled);

    v8cpp::Class<ActionMetaData> action_metadata(isolate);

    v8cpp::Class<SearchMetaData> search_metadata(isolate);

    v8cpp::Class<PreviewWidget> preview_widget(isolate);
    preview_widget
      .add_method("add_attribute_value", &PreviewWidget::add_attribute_value)
      .add_method("add_attribute_mapping", &PreviewWidget::add_attribute_mapping)
      .add_method("add_widget", &PreviewWidget::add_widget)
      .add_method("id", &PreviewWidget::id)
      .add_method("widget_type", &PreviewWidget::widget_type)
      .add_method("attribute_mappings", &PreviewWidget::attribute_mappings)
      .add_method("attribute_values", &PreviewWidget::attribute_values)
      .add_method("widgets", &PreviewWidget::widgets)
      .add_method("data", &PreviewWidget::data);

    v8cpp::Module module(isolate);
    module.add_function("new_scope", &new_scope);
    module.add_function("new_search_query", &new_search_query);
    module.add_function("new_category_renderer", &new_category_renderer);
    module.add_function("new_preview_widget", &new_preview_widget);

    exports->SetPrototype(module.create_prototype());
}

NODE_MODULE(unity_js_scopes_bindings, InitAll)
