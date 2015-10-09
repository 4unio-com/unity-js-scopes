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

#include <unity/scopes/ActionMetadata.h>
#include <unity/scopes/CannedQuery.h>
#include <unity/scopes/Category.h>
#include <unity/scopes/CategoryRenderer.h>
#include <unity/scopes/Result.h>
#include <unity/scopes/SearchReply.h>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

#include <node.h>

#include "action-metadata.h"
#include "activation-query.h"
#include "categorised-result.h"
#include "scope-base.h"
#include "scope.h"
#include "search-query.h"
#include "search-reply.h"
#include "search-metadata.h"
#include "result.h"
#include "action-metadata.h"
#include "preview-query.h"
#include "preview-reply.h"
#include "preview-widget.h"

// TODO static
JavascriptScopeRuntime* new_scope(const std::string& runtime_config) {
  return new JavascriptScopeRuntime(runtime_config);
}

v8::Handle<v8::Object> get_scopes_runtime_version() {
  v8::Handle<v8::Object> o =
    v8::Object::New(v8::Isolate::GetCurrent());

  int major, minor, micro;
  unity::scopes::ScopeBase::runtime_version(major, minor, micro);

  o->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "major"),
         v8::Integer::New(v8::Isolate::GetCurrent(), major));
  o->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "minor"),
         v8::Integer::New(v8::Isolate::GetCurrent(), minor));
  o->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "micro"),
         v8::Integer::New(v8::Isolate::GetCurrent(), micro));

  return o;
}

std::shared_ptr<unity::scopes::CategoryRenderer>
new_category_renderer_from_file(const std::string& file_path) {
  return std::shared_ptr<unity::scopes::CategoryRenderer>(
      new unity::scopes::CategoryRenderer(
          unity::scopes::CategoryRenderer::from_file(file_path)));
}

v8::Handle<v8::Object> new_SearchQuery(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 4) {
    throw std::runtime_error("Invalid number of arguments");
  }

  std::shared_ptr<unity::scopes::CannedQuery> c =
    v8cpp::from_v8<std::shared_ptr<unity::scopes::CannedQuery>>(
        v8::Isolate::GetCurrent(),
        args[0]->ToObject());

  std::shared_ptr<SearchMetaData> s =
    v8cpp::from_v8<std::shared_ptr<SearchMetaData>>(
        v8::Isolate::GetCurrent(),
        args[1]->ToObject());

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

  std::shared_ptr<SearchQuery> sq(
    new SearchQuery(
        *c,
        static_cast<const unity::scopes::SearchMetadata&>(*s),
        run_callback,
        cancelled_callback)
  );

  return v8cpp::to_v8(v8::Isolate::GetCurrent(), sq);
}

v8::Handle<v8::Object> new_PreviewQuery(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 4) {
    throw std::runtime_error("Invalid number of arguments");
  }

  std::shared_ptr<Result> r =
    v8cpp::from_v8<std::shared_ptr<Result>>(
        v8::Isolate::GetCurrent(),
        args[0]->ToObject());

  std::shared_ptr<ActionMetaData> a =
    v8cpp::from_v8<std::shared_ptr<ActionMetaData>>(
        v8::Isolate::GetCurrent(),
        args[1]->ToObject());

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

  std::shared_ptr<PreviewQuery> pq(
      new PreviewQuery(
        *r,
        *a,
        run_callback,
        cancelled_callback));

  return v8cpp::to_v8(v8::Isolate::GetCurrent(), pq);
}

v8::Handle<v8::Object> new_PreviewWidget(
      v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() < 1 || args.Length() > 2) {
    throw std::runtime_error("Invalid number of arguments");
  }

  if (args.Length() == 2) {
    if (!args[0]->IsString() || !args[1]->IsString()) {
      throw std::runtime_error("Invalid arguments types: should be id, widget_type");
    }
    std::string id =
      *(v8::String::Utf8Value(args[0]->ToString()));

    std::string widget_type =
      *(v8::String::Utf8Value(args[1]->ToString()));

    PreviewWidget* preview_widget =
      new PreviewWidget(id, widget_type);

    return v8cpp::to_v8(v8::Isolate::GetCurrent(), preview_widget);
  }

  if (!args[0]->IsString()) {
    throw std::runtime_error("Invalid arguments types");
  }
  
  std::string definition =
    *(v8::String::Utf8Value(args[0]->ToString()));
  
  PreviewWidget* preview_widget =
    new PreviewWidget(definition);
  
  return v8cpp::to_v8(v8::Isolate::GetCurrent(), preview_widget);
}

void InitAll(v8::Handle<v8::Object> exports)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    v8cpp::Class<unity::scopes::VariantMap> variant_map(isolate);
    v8cpp::Class<unity::scopes::VariantArray> variant_array(isolate);

    // TODO: which enum should be bound
    v8cpp::Class<unity::scopes::Variant> variant(isolate);
    variant
      .add_method("get_int", &unity::scopes::Variant::get_int)
      .add_method("get_double", &unity::scopes::Variant::get_double)
      .add_method("get_bool", &unity::scopes::Variant::get_bool)
      .add_method("get_string", &unity::scopes::Variant::get_string)
      .add_method("get_dict", &unity::scopes::Variant::get_dict)
      .add_method("get_array", &unity::scopes::Variant::get_array)
      .add_method("is_null", &unity::scopes::Variant::is_null)
      .add_method("which", &unity::scopes::Variant::which)
      .add_method("serialize_json", &unity::scopes::Variant::serialize_json)
      .add_method("deserialize_json", &unity::scopes::Variant::deserialize_json)
      .add_method("which", &unity::scopes::Variant::which);

    v8cpp::Class<JavascriptScopeRuntime> js_scope(isolate);
    js_scope
      .add_method("scope_base", &JavascriptScopeRuntime::scope_base)
      .add_method("scope_config", &JavascriptScopeRuntime::scope_config)
      .add_method("run", &JavascriptScopeRuntime::run);

    v8cpp::Class<ScopeBase> scope_base(isolate);
    scope_base
      .add_inheritance<unity::scopes::ScopeBase>()
      .add_method("onstart", &ScopeBase::onstart)
      .add_method("onstop", &ScopeBase::onstop)
      .add_method("onrun", &ScopeBase::onrun)
      .add_method("onsearch", &ScopeBase::onsearch)
      .add_method("onpreview", &ScopeBase::onpreview)
      // unity::scopes::ScopeBase
      .add_method("scope_directory", &unity::scopes::ScopeBase::scope_directory)
      .add_method("cache_directory", &unity::scopes::ScopeBase::cache_directory)
      .add_method("tmp_directory", &unity::scopes::ScopeBase::tmp_directory)
      .add_method("settings", &unity::scopes::ScopeBase::settings)
      .add_method("registry", &unity::scopes::ScopeBase::registry);

    v8cpp::Class<ActionMetaData> action_metadata(isolate);
    action_metadata
      . add_inheritance<unity::scopes::ActionMetadata>()
      // unity::scopes::ActionMetadata
      .add_method("set_scope_data", &unity::scopes::ActionMetadata::set_scope_data)
      .add_method("scope_data", &unity::scopes::ActionMetadata::scope_data)
      .add_method("set_hint", &unity::scopes::ActionMetadata::set_hint)
      .add_method("hints", &unity::scopes::ActionMetadata::hints)
      .add_method("contains_hint", &unity::scopes::ActionMetadata::contains_hint)
      // unity::scopes::QueryMetadata
      .add_method("locale", &unity::scopes::ActionMetadata::locale)
      .add_method("form_factor", &unity::scopes::ActionMetadata::form_factor)
      .add_method("set_internet_connectivity", &unity::scopes::ActionMetadata::set_internet_connectivity)
      .add_method("internet_connectivity", &unity::scopes::QueryMetadata::internet_connectivity)
      // ActionMetaData
      .add_method("get", &ActionMetaData::get)
      .add_method("set", &ActionMetaData::set);

    v8cpp::Class<ActivationQuery> activation_query(isolate);
    activation_query
      .add_inheritance<unity::scopes::ActivationQueryBase>()
      // ActivationQuery
      .add_method("activate", &ActivationQuery::activate)
      .add_method("result", &ActivationQuery::result)
      .add_method("action_metadata", &ActivationQuery::action_metadata)
      // unity::scopes::ActivationQueryBase
      .add_method("widget_id", &unity::scopes::ActivationQueryBase::widget_id)
      .add_method("action_id", &unity::scopes::ActivationQueryBase::action_id)
      // QueryBase
      .add_method("valid", &unity::scopes::QueryBase::valid)
      .add_method("settings", &unity::scopes::QueryBase::settings);

    v8cpp::Class<unity::scopes::Category> category(isolate);
    category
      // unity::scopes::Category
      .add_method("query", &unity::scopes::Category::query)
      .add_method("id", &unity::scopes::Category::id)
      .add_method("title", &unity::scopes::Category::title)
      .add_method("icon", &unity::scopes::Category::icon);

    v8cpp::Class<CategorisedResult> categorised_result(isolate);
    categorised_result
      .add_inheritance<unity::scopes::Result>()
      .set_constructor<unity::scopes::Category::SCPtr>()
      // unity::scopes::Result
      .add_method("set_uri", &unity::scopes::Result::set_uri)
      .add_method("set_title", &unity::scopes::Result::set_title)
      .add_method("set_art", &unity::scopes::Result::set_art)
      .add_method("set_dnd_uri", &unity::scopes::Result::set_dnd_uri)
      .add_method("set_intercept_activation", &unity::scopes::Result::set_intercept_activation)
      .add_method("direct_activation", &unity::scopes::Result::direct_activation)
      .add_method("uri", &unity::scopes::Result::uri)
      .add_method("title", &unity::scopes::Result::title)
      .add_method("art", &unity::scopes::Result::art)
      .add_method("dnd_uri", &unity::scopes::Result::dnd_uri)
      .add_method("contains", &unity::scopes::Result::contains)
      // CategorisedResult
      // TODO fix / proper namedpropertyaccessorhandler
      .add_method("set", &CategorisedResult::set)
      .add_method("get", &CategorisedResult::get)
      .add_method("set_category", &CategorisedResult::set_category)
      .add_method("category", &CategorisedResult::category);

    v8cpp::Class<unity::scopes::CannedQuery> canned_query(isolate);
    canned_query
      .add_method("set_department_id", &unity::scopes::CannedQuery::set_department_id)
      .add_method("set_query_string", &unity::scopes::CannedQuery::set_query_string)
      .add_method("set_filter_state", &unity::scopes::CannedQuery::set_filter_state)
      .add_method("scope_id", &unity::scopes::CannedQuery::scope_id)
      .add_method("department_id", &unity::scopes::CannedQuery::department_id)
      .add_method("filter_state", &unity::scopes::CannedQuery::filter_state)
      .add_method("query_string", &unity::scopes::CannedQuery::query_string)
      .add_method("to_uri", &unity::scopes::CannedQuery::to_uri);

    // TODO Should it be more of a value type? (it seems to be used that way
    // in unity API)
    v8cpp::Class<unity::scopes::CategoryRenderer> category_renderer(isolate);
    category_renderer
      .set_constructor<std::string>()
      .add_method("data", &unity::scopes::CategoryRenderer::data);

    v8cpp::Class<unity::scopes::ColumnLayout> column_layout(isolate);
    column_layout
      .set_constructor<int>()
      .add_method("add_column", &unity::scopes::ColumnLayout::add_column)
      .add_method("size", &unity::scopes::ColumnLayout::size)
      .add_method("number_of_columns", &unity::scopes::ColumnLayout::number_of_columns)
      .add_method("column", &unity::scopes::ColumnLayout::column);

    v8cpp::Class<PreviewWidget> preview_widget(isolate);
    preview_widget
      .add_inheritance<unity::scopes::PreviewWidget>()
      // unity::scopes::PreviewWidget
      .add_method("id", &unity::scopes::PreviewWidget::id)
      .add_method("widget_type", &unity::scopes::PreviewWidget::widget_type)
      .add_method("attribute_mappings", &unity::scopes::PreviewWidget::attribute_mappings)
      .add_method("data", &unity::scopes::PreviewWidget::data)
      .add_method("add_attribute_mapping", &unity::scopes::PreviewWidget::add_attribute_mapping)
      // PreviewWidget
      .add_method("add_attribute_value", &PreviewWidget::add_attribute_value)
      .add_method("add_widget", &PreviewWidget::add_widget);

    v8cpp::Class<PreviewQuery> preview_query(isolate);
    preview_query
      .add_inheritance<unity::scopes::PreviewQueryBase>()
      // unity::scopes::QueryBase
      .add_method("valid", &unity::scopes::QueryBase::valid)
      .add_method("settings", &unity::scopes::QueryBase::settings)
      // PreviewQuery
      .add_method("result", &PreviewQuery::result)
      .add_method("action_metadata", &PreviewQuery::action_metadata);

    // TODO handle info()
    v8cpp::Class<PreviewReply> preview_reply(isolate);
    preview_reply
      // PreviewReply
      .add_method("register_layout", &PreviewReply::register_layout)
      .add_method("push", &PreviewReply::push)
      // unity::scopes::PreviewReply
      .add_method("finished", &unity::scopes::PreviewReply::finished);

    v8cpp::Class<Result> result(isolate);
    result
      // unity::scopes::Result
      .add_method("art", &unity::scopes::Result::art)
      .add_method("set_art", &unity::scopes::Result::set_art)
      .add_method("title", &unity::scopes::Result::title)
      .add_method("set_title", &unity::scopes::Result::set_title)
      .add_method("dnd_uri", &unity::scopes::Result::dnd_uri)
      .add_method("set_dnd_uri", &unity::scopes::Result::set_dnd_uri)
      .add_method("uri", &unity::scopes::Result::uri)
      .add_method("set_uri", &unity::scopes::Result::set_uri)
      .add_method("set_intercept_activation", &unity::scopes::Result::set_intercept_activation)
      .add_method("direct_activation", &unity::scopes::Result::direct_activation)
      .add_method("has_stored_result", &unity::scopes::Result::has_stored_result)
      // Result
      // TODO fix / proper namedpropertyaccessorhandler
      .add_method("set", &Result::set)
      .add_method("get", &Result::get)
      .add_method("retrieve_stored_result", &Result::retrieve_stored_result)
      .add_method("store", &Result::store);

    v8cpp::Class<SearchReply> search_reply(isolate);
    search_reply
      // SearchReply
      .add_method("register_category", &SearchReply::register_category)
      .add_method("push", &SearchReply::push)
      .add_method("lookup_category", &SearchReply::lookup_category)
      .add_method("finished", &SearchReply::finished);

    v8cpp::Class<SearchQuery> search_query(isolate);
    search_query
      .add_method("onrun", &SearchQuery::onrun)
      .add_method("oncancelled", &SearchQuery::oncancelled);

    v8cpp::Class<unity::scopes::Location> location(isolate);
    location
      // unity::scopes::Location
      .add_method("altitude", &unity::scopes::Location::altitude)
      .add_method("has_altitude", &unity::scopes::Location::has_altitude)
      .add_method("area_code", &unity::scopes::Location::area_code)
      .add_method("has_area_code", &unity::scopes::Location::has_area_code)
      .add_method("city", &unity::scopes::Location::city)
      .add_method("has_city", &unity::scopes::Location::has_city)
      .add_method("has_country_code", &unity::scopes::Location::has_country_code)
      .add_method("country_code", &unity::scopes::Location::country_code)
      .add_method("has_country_name", &unity::scopes::Location::has_country_name)
      .add_method("country_name", &unity::scopes::Location::country_name)
      .add_method("has_horizontal_accuracy", &unity::scopes::Location::has_horizontal_accuracy)
      .add_method("horizontal_accuracy", &unity::scopes::Location::horizontal_accuracy)
      .add_method("latitude", &unity::scopes::Location::latitude)
      .add_method("longitude", &unity::scopes::Location::longitude)
      .add_method("has_region_code", &unity::scopes::Location::has_region_code)
      .add_method("region_code", &unity::scopes::Location::region_code)
      .add_method("has_region_name", &unity::scopes::Location::has_region_name)
      .add_method("region_name", &unity::scopes::Location::region_name)
      .add_method("has_vertical_accuracy", &unity::scopes::Location::has_vertical_accuracy);

    v8cpp::Class<SearchMetaData> search_metadata(isolate);
    search_metadata
      .add_inheritance<unity::scopes::SearchMetadata>()
      // unity::scopes::SearchMetadata
      .add_method("set_cardinality", &unity::scopes::SearchMetadata::set_cardinality)
      .add_method("cardinality", &unity::scopes::SearchMetadata::cardinality)
      .add_method("has_location", &unity::scopes::SearchMetadata::has_location)
      .add_method("set_hint", &unity::scopes::SearchMetadata::set_hint)
      .add_method("hints", &unity::scopes::SearchMetadata::hints)
      // QueryMetadata
      .add_method("locale", &unity::scopes::QueryMetadata::locale)
      .add_method("form_factor", &unity::scopes::QueryMetadata::form_factor)
      .add_method("set_internet_connectivity", &unity::scopes::QueryMetadata::set_internet_connectivity)
      .add_method("internet_connectivity", &unity::scopes::QueryMetadata::internet_connectivity)
      // SearchMetaData
      .add_method("set_location", &SearchMetaData::set_location)
      .add_method("location", &SearchMetaData::location);

    v8cpp::Module module(isolate);
    module.add_class("js_scope", js_scope);
    module.add_class("scope_base", scope_base);
    module.add_class("action_metadata", action_metadata);
    module.add_class("activation_query", activation_query);
    module.add_class("category", category);
    module.add_class("categorised_result", categorised_result);
    module.add_class("canned_query", canned_query);
    module.add_class("categorised_result", categorised_result);
    module.add_class("category_renderer", category_renderer);
    module.add_class("column_layout", column_layout);
    module.add_class("location", location);
    module.add_class("preview_widget", preview_widget);
    module.add_class("preview_query", preview_query);
    module.add_class("preview_reply", preview_reply);
    module.add_class("result", result);
    module.add_class("search_reply", search_reply);
    module.add_class("search_query", search_query);
    module.add_class("search_metadata", search_metadata);
    module.add_class("variant", variant);
    module.add_class("variant_map", variant_map);
    module.add_class("variant_array", variant_array);

    module.add_function("new_scope", &new_scope);
    module.add_function("new_SearchQuery", &new_SearchQuery);
    module.add_function("new_PreviewQuery", &new_PreviewQuery);
    module.add_function("new_PreviewWidget", &new_PreviewWidget);
    module.add_function("new_category_renderer_from_file", &new_category_renderer_from_file);

    module.add_function("runtime_version", &get_scopes_runtime_version);

    exports->SetPrototype(module.create_prototype());
}

NODE_MODULE(unity_js_scopes_bindings, InitAll)
