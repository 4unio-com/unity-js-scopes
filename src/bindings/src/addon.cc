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

#include <v8-cpp.h>

#include <stdexcept>

#include <unity/scopes/ActionMetadata.h>
#include <unity/scopes/Category.h>
#include <unity/scopes/CategoryRenderer.h>
#include <unity/scopes/OperationInfo.h>
#include <unity/scopes/Result.h>
#include <unity/scopes/SearchReply.h>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

#include <node.h>

#include "action-metadata.h"
#include "activation-query.h"
#include "canned-query.h"
#include "categorised-result.h"
#include "department.h"
#include "filter-group.h"
#include "online-account-client.h"
#include "option-selector-filter.h"
#include "preview-query.h"
#include "preview-reply.h"
#include "preview-widget.h"
#include "scope-base.h"
#include "scope.h"
#include "search-query.h"
#include "search-reply.h"
#include "search-metadata.h"
#include "registry.h"
#include "result.h"
#include "variant.h"
#include "value-slider-labels.h"
#include "value-slider-filter.h"
#include "range-input-filter.h"

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

void InitAll(v8::Handle<v8::Object> exports)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();

    // TODO: which enum should be bound
    v8cpp::Class<Variant> variant(isolate);
    variant
      .set_constructor<v8::Local<v8::Value>>()
      .add_method("get_int", &Variant::get_int)
      .add_method("get_int64_t", &Variant::get_int64_t)
      .add_method("get_double", &Variant::get_double)
      .add_method("get_bool", &Variant::get_bool)
      .add_method("get_string", &Variant::get_string)
      .add_method("get_dict", &Variant::get_dict)
      .add_method("get_array", &Variant::get_array)
      .add_method("is_null", &Variant::is_null)
      .add_method("which", &Variant::which)
      .add_method("serialize_json", &Variant::serialize_json);

    // Also bind the original Variant class for direct access (E.g. via settings)
    v8cpp::Class<unity::scopes::Variant> variant_base(isolate);
    variant_base
      .add_method("get_int", &unity::scopes::Variant::get_int)
      .add_method("get_int64_t", &unity::scopes::Variant::get_int64_t)
      .add_method("get_double", &unity::scopes::Variant::get_double)
      .add_method("get_bool", &unity::scopes::Variant::get_bool)
      .add_method("get_string", &unity::scopes::Variant::get_string)
      .add_method("get_dict", &unity::scopes::Variant::get_dict)
      .add_method("get_array", &unity::scopes::Variant::get_array)
      .add_method("is_null", &unity::scopes::Variant::is_null)
      //.add_method("which", &unity::scopes::Variant::which)
      .add_method("serialize_json", &unity::scopes::Variant::serialize_json)
      .add_method("deserialize_json", &unity::scopes::Variant::deserialize_json);


    v8cpp::Class<JavascriptScopeRuntime> js_scope(isolate);
    js_scope
      .add_method("scope_base", &JavascriptScopeRuntime::scope_base)
      .add_method("scope_config", &JavascriptScopeRuntime::scope_config)
      .add_method("run", &JavascriptScopeRuntime::run)
      .add_method("stop", &JavascriptScopeRuntime::stop);

    v8cpp::Class<ScopeBase> scope_base(isolate);
    scope_base
      .add_inheritance<unity::scopes::ScopeBase>()
      .add_method("onstart", &ScopeBase::onstart)
      .add_method("onstop", &ScopeBase::onstop)
      .add_method("onrun", &ScopeBase::onrun)
      .add_method("onsearch", &ScopeBase::onsearch)
      .add_method("onpreview", &ScopeBase::onpreview)
      .add_method("onperform_action", &ScopeBase::onperform_action)
      .add_method("onactivate", &ScopeBase::onactivate)
      .add_method("registry", &ScopeBase::get_registry)
      // unity::scopes::ScopeBase
      .add_method("scope_directory", &unity::scopes::ScopeBase::scope_directory)
      .add_method("cache_directory", &unity::scopes::ScopeBase::cache_directory)
      .add_method("tmp_directory", &unity::scopes::ScopeBase::tmp_directory)
      .add_method("settings", &unity::scopes::ScopeBase::settings);

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
      .set_constructor<v8::FunctionCallbackInfo<v8::Value>>()
      // unity::scopes::ActivationQueryBase
      .add_method("widget_id", &unity::scopes::ActivationQueryBase::widget_id)
      .add_method("action_id", &unity::scopes::ActivationQueryBase::action_id)
      .add_method("valid", &unity::scopes::QueryBase::valid)
      .add_method("settings", &unity::scopes::QueryBase::settings)
      // ActivationQuery
      .add_method("result", &ActivationQuery::result)
      .add_method("action_metadata", &ActivationQuery::action_metadata);

    v8cpp::Class<ActivationResponse> activation_response(isolate);
    activation_response
      .set_constructor<v8::Local<v8::Value>>()
      // ActivationResponse
      .add_method("status", &ActivationResponse::status)
      .add_method("set_scope_data", &ActivationResponse::set_scope_data)
      .add_method("scope_data", &ActivationResponse::scope_data)
      .add_method("query", &ActivationResponse::query);

    v8cpp::Class<unity::scopes::Category> category(isolate);
    category
      // unity::scopes::Category
      .add_method("query", &unity::scopes::Category::query)
      .add_method("id", &unity::scopes::Category::id)
      .add_method("title", &unity::scopes::Category::title)
      .add_method("icon", &unity::scopes::Category::icon);
    // TODO renderer_template

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

    v8cpp::Class<CannedQuery> canned_query(isolate);
    canned_query
      .set_constructor<v8::FunctionCallbackInfo<v8::Value>>()
      .add_method("set_department_id", &CannedQuery::set_department_id)
      .add_method("set_query_string", &CannedQuery::set_query_string)
      .add_method("set_filter_state", &CannedQuery::set_filter_state)
      .add_method("scope_id", &CannedQuery::scope_id)
      .add_method("department_id", &CannedQuery::department_id)
      .add_method("query_string", &CannedQuery::query_string)
      .add_method("to_uri", &CannedQuery::to_uri)
      .add_method("filter_state", &CannedQuery::filter_state);

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

    v8cpp::Class<Department> department(isolate);
    department
      .set_constructor<v8::FunctionCallbackInfo<v8::Value>>()
      .add_method("set_subdepartments", &Department::set_subdepartments)
      .add_method("add_subdepartment", &Department::add_subdepartment)
      .add_method("set_alternate_label", &Department::set_alternate_label)
      .add_method("set_has_subdepartments", &Department::set_has_subdepartments)
      .add_method("id", &Department::id)
      .add_method("label", &Department::label)
      .add_method("alternate_label", &Department::alternate_label)
      .add_method("query", &Department::query)
      .add_method("subdepartments", &Department::subdepartments)
      .add_method("has_subdepartments", &Department::has_subdepartments);

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

    v8cpp::Class<FilterGroup> filter_group(isolate);
    filter_group
      .set_constructor<std::string const&, std::string const&>()
      .add_method("id", &FilterGroup::id)
      .add_method("label", &FilterGroup::label);

    v8cpp::Class<unity::scopes::FilterState> filter_state(isolate);
    filter_state
      .set_constructor<>()
      .add_method("has_filter", &unity::scopes::FilterState::has_filter)
      .add_method("remove", &unity::scopes::FilterState::remove);

    v8cpp::Class<unity::scopes::FilterOption> filter_option(isolate);
    filter_option
      .add_method("id", &unity::scopes::FilterOption::id)
      .add_method("label", &unity::scopes::FilterOption::label);

    v8cpp::Class<OptionSelectorFilter> option_selector_filter(isolate);
    option_selector_filter
      .set_constructor<std::string, std::string, bool>()
      .add_method("label", &OptionSelectorFilter::label)
      .add_method("multi_select", &OptionSelectorFilter::multi_select)
      .add_method("add_option", &OptionSelectorFilter::add_option)
      .add_method("options", &OptionSelectorFilter::options)
      .add_method("has_active_option", &OptionSelectorFilter::has_active_option)
      .add_method("active_options", &OptionSelectorFilter::active_options)
      .add_method("update_state", &OptionSelectorFilter::update_state)
      // FilterBase
      .add_method("set_display_hints", &OptionSelectorFilter::set_display_hints)
      .add_method("display_hints", &OptionSelectorFilter::display_hints)
      .add_method("set_title", &OptionSelectorFilter::set_title)
      .add_method("title", &OptionSelectorFilter::title)
      .add_method("id", &OptionSelectorFilter::id)
      .add_method("filter_type", &OptionSelectorFilter::filter_type)
      .add_method("filter_group", &OptionSelectorFilter::filter_group);

    v8cpp::Class<unity::scopes::OperationInfo> operation_info(isolate);
    operation_info
      .set_constructor<unity::scopes::OperationInfo::InfoCode, std::string>()
      .add_method("code", &unity::scopes::OperationInfo::code)
      .add_method("message", &unity::scopes::OperationInfo::message);

    v8cpp::Class<PreviewWidget> preview_widget(isolate);
    preview_widget
      .set_constructor<v8::Local<v8::Value>, v8::Local<v8::Value>>()
      // PreviewWidget
      .add_method("id", &PreviewWidget::id)
      .add_method("widget_type", &PreviewWidget::widget_type)
      .add_method("attribute_mappings", &PreviewWidget::attribute_mappings)
      .add_method("attribute_values", &PreviewWidget::attribute_values)
      .add_method("widgets", &PreviewWidget::widgets)
      .add_method("data", &PreviewWidget::data)
      .add_method("add_attribute_mapping", &PreviewWidget::add_attribute_mapping)
      .add_method("add_attribute_value", &PreviewWidget::add_attribute_value)
      .add_method("add_widget", &PreviewWidget::add_widget);

    v8cpp::Class<PreviewQuery> preview_query(isolate);
    preview_query
      .add_inheritance<unity::scopes::PreviewQueryBase>()
      .set_constructor<std::shared_ptr<Result>, std::shared_ptr<ActionMetaData>, v8::Local<v8::Function>, v8::Local<v8::Function>>()
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
      .add_method("info", &PreviewReply::info)
      .add_method("finished", &PreviewReply::finished);

    v8cpp::Class<Result> result(isolate);
    result
      .add_inheritance<unity::scopes::Result>()
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
      .add_method("register_departments", &SearchReply::register_departments)
      .add_method("info", &SearchReply::info)
      .add_method("push", &SearchReply::push)
      .add_method("lookup_category", &SearchReply::lookup_category)
      .add_method("finished", &SearchReply::finished);

    v8cpp::Class<SearchQuery> search_query(isolate);
    search_query
      .set_constructor<std::shared_ptr<CannedQuery>, std::shared_ptr<SearchMetadata>, v8::Local<v8::Function>, v8::Local<v8::Function>>()
      .add_method("onrun", &SearchQuery::onrun)
      .add_method("oncancelled", &SearchQuery::oncancelled);

    v8cpp::Class<RangeInputFilter> range_input_filter(isolate);
    range_input_filter
      .add_method("start_prefix_label", &RangeInputFilter::start_prefix_label)
      .add_method("start_postfix_label", &RangeInputFilter::start_postfix_label)
      .add_method("end_prefix_label", &RangeInputFilter::end_prefix_label)
      .add_method("end_postfix_label", &RangeInputFilter::end_postfix_label)
      .add_method("central_label", &RangeInputFilter::central_label)
      .add_method("default_start_value", &RangeInputFilter::default_start_value)
      .add_method("default_end_value", &RangeInputFilter::default_end_value)
      .add_method("has_start_value", &RangeInputFilter::has_start_value)
      .add_method("has_end_value", &RangeInputFilter::has_end_value)
      .add_method("start_value", &RangeInputFilter::start_value)
      .add_method("end_value", &RangeInputFilter::end_value)
      .add_method("update_state", &RangeInputFilter::update_state)
      .add_method("set_display_hints", &RangeInputFilter::set_display_hints)
      .add_method("display_hints", &RangeInputFilter::display_hints)
      .add_method("set_title", &RangeInputFilter::set_title)
      .add_method("title", &RangeInputFilter::title)
      .add_method("id", &RangeInputFilter::id)
      .add_method("filter_type", &RangeInputFilter::filter_type)
      .add_method("filter_group", &RangeInputFilter::filter_group);

    v8cpp::Class<Registry> registry(isolate);
    registry
      // Registry
      .add_method("get_metadata", &Registry::get_metadata)
      .add_method("list", &Registry::list)
      .add_method("list_if", &Registry::list_if)
      .add_method("is_scope_running", &Registry::is_scope_running)
      .add_method("set_scope_state_callback", &Registry::set_scope_state_callback)
      .add_method("set_list_update_callback", &Registry::set_list_update_callback);

    v8cpp::Class<unity::scopes::ScopeMetadata> scope_metadata(isolate);
    scope_metadata
      // unity::scopes::ScopeMetadata
      .add_method("scope_id", &unity::scopes::ScopeMetadata::scope_id)
      // .add_method("scope_proxy", &unity::scopes::ScopeMetadata::scope_proxy)
      .add_method("display_name", &unity::scopes::ScopeMetadata::display_name)
      .add_method("description", &unity::scopes::ScopeMetadata::description)
      .add_method("author", &unity::scopes::ScopeMetadata::author)
      .add_method("art", &unity::scopes::ScopeMetadata::art)
      .add_method("icon", &unity::scopes::ScopeMetadata::icon)
      .add_method("search_hint", &unity::scopes::ScopeMetadata::search_hint)
      .add_method("hot_key", &unity::scopes::ScopeMetadata::hot_key)
      .add_method("invisible", &unity::scopes::ScopeMetadata::invisible)
      // .add_method("appearance_attributes", &unity::scopes::ScopeMetadata::appearance_attributes)
      .add_method("scope_directory", &unity::scopes::ScopeMetadata::scope_directory)
      // .add_method("serialize", &unity::scopes::ScopeMetadata::serialize)
      .add_method("results_ttl_type", &unity::scopes::ScopeMetadata::results_ttl_type)
      // .add_method("settings_definitions", &unity::scopes::ScopeMetadata::settings_definitions)
      .add_method("location_data_needed", &unity::scopes::ScopeMetadata::location_data_needed);

    v8cpp::Class<SearchMetadata> search_metadata(isolate);
    search_metadata
      .set_constructor<v8::FunctionCallbackInfo<v8::Value>>()
      // SearchMetadata
      .add_method("set_cardinality", &SearchMetadata::set_cardinality)
      .add_method("cardinality", &SearchMetadata::cardinality)
      .add_method("has_location", &SearchMetadata::has_location)
      .add_method("remove_location", &SearchMetadata::remove_location)
      .add_method("set_aggregated_keywords", &SearchMetadata::set_aggregated_keywords)
      .add_method("aggregated_keywords", &SearchMetadata::aggregated_keywords)
      .add_method("is_aggregated", &SearchMetadata::is_aggregated)
      .add_method("set_hint", &SearchMetadata::set_hint)
      .add_method("hints", &SearchMetadata::hints)
      .add_method("set", &SearchMetadata::set)
      .add_method("get", &SearchMetadata::get)
      .add_method("set_location", &SearchMetadata::set_location)
      .add_method("location", &SearchMetadata::location)
      .add_method("locale", &SearchMetadata::locale)
      .add_method("form_factor", &SearchMetadata::form_factor)
      .add_method("set_internet_connectivity", &SearchMetadata::set_internet_connectivity)
      .add_method("internet_connectivity", &SearchMetadata::internet_connectivity);

    v8cpp::Class<OnlineAccountClient> online_account_client(isolate);
    online_account_client
      .set_constructor<std::string, std::string, std::string>()
      // OnlineAccountClient
      .add_method("refresh_service_statuses", &OnlineAccountClient::refresh_service_statuses)
      .add_method("set_service_update_callback", &OnlineAccountClient::set_service_update_callback)
      .add_method("get_service_statuses", &OnlineAccountClient::get_service_statuses)
      .add_method("register_account_login_item", &OnlineAccountClient::register_account_login_item)
      .add_method("register_account_login_widget", &OnlineAccountClient::register_account_login_widget);

    v8cpp::Class<unity::scopes::OnlineAccountClient::ServiceStatus> online_account_service_status(isolate);
    online_account_service_status
      .set_constructor<>()
      // unity::scopes::OnlineAccountClient::ServiceStatus
      .add_member("account_id", &unity::scopes::OnlineAccountClient::ServiceStatus::account_id)
      .add_member("service_enabled", &unity::scopes::OnlineAccountClient::ServiceStatus::service_enabled)
      .add_member("service_authenticated", &unity::scopes::OnlineAccountClient::ServiceStatus::service_authenticated)
      .add_member("client_id", &unity::scopes::OnlineAccountClient::ServiceStatus::client_id)
      .add_member("client_secret", &unity::scopes::OnlineAccountClient::ServiceStatus::client_secret)
      .add_member("access_token", &unity::scopes::OnlineAccountClient::ServiceStatus::access_token)
      .add_member("token_secret", &unity::scopes::OnlineAccountClient::ServiceStatus::token_secret)
      .add_member("error", &unity::scopes::OnlineAccountClient::ServiceStatus::error);

    v8cpp::Class<ValueSliderFilter> value_slider_filter(isolate);
    value_slider_filter
      .add_method("set_default_value", &ValueSliderFilter::set_default_value)
      .add_method("min", &ValueSliderFilter::min)
      .add_method("max", &ValueSliderFilter::max)
      .add_method("has_value", &ValueSliderFilter::has_value)
      .add_method("value", &ValueSliderFilter::value)
      .add_method("labels", &ValueSliderFilter::labels)
      .add_method("update_state", &ValueSliderFilter::update_state)
      .add_method("set_display_hints", &ValueSliderFilter::set_display_hints)
      .add_method("display_hints", &ValueSliderFilter::display_hints)
      .add_method("set_title", &ValueSliderFilter::set_title)
      .add_method("title", &ValueSliderFilter::title)
      .add_method("id", &ValueSliderFilter::id)
      .add_method("filter_group", &ValueSliderFilter::filter_group)
      .add_method("filter_type", &ValueSliderFilter::filter_type)
      .add_method("default_value", &ValueSliderFilter::default_value);

    v8cpp::Class<ValueSliderLabels> value_slider_labels(isolate);
    value_slider_labels
      .add_method("min_label", &ValueSliderLabels::min_label)
      .add_method("max_label", &ValueSliderLabels::max_label)
      .add_method("extra_labels", &ValueSliderLabels::extra_labels);

    v8cpp::Module module(isolate);
    module.add_class("js_scope", js_scope);
    module.add_class("scope_base", scope_base);
    module.add_class("ActionMetadata", action_metadata);
    module.add_class("ActivationQuery", activation_query);
    module.add_class("ActivationResponse", activation_response);
    module.add_class("Category", category);
    module.add_class("CategorisedResult", categorised_result);
    module.add_class("CannedQuery", canned_query);
    module.add_class("CategoryRenderer", category_renderer);
    module.add_class("ColumnLayout", column_layout);
    module.add_class("Department", department);
    module.add_class("FilterGroup", filter_group);
    module.add_class("FilterOption", filter_option);
    module.add_class("FilterState", filter_state);
    module.add_class("Location", location);
    module.add_class("OnlineAccountClient", online_account_client);
    module.add_class("OnlineAccountClientServiceStatus", online_account_service_status);
    module.add_class("OperationInfo", operation_info);
    module.add_class("OptionSelectorFilter", option_selector_filter);
    module.add_class("PreviewWidget", preview_widget);
    module.add_class("PreviewQuery", preview_query);
    module.add_class("PreviewReply", preview_reply);
    module.add_class("RangeInputFilter", range_input_filter);
    module.add_class("Registry", registry);
    module.add_class("Result", result);
    module.add_class("ScopeMetadata", scope_metadata);
    module.add_class("SearchReply", search_reply);
    module.add_class("SearchQuery", search_query);
    module.add_class("SearchMetadata", search_metadata);
    module.add_class("Variant", variant);
    module.add_class("VariantBase", variant_base);
    module.add_class("ValueSliderFilter", value_slider_filter);
    module.add_class("ValueSliderLabels", value_slider_labels);

    // Factory functions
    module.add_function("new_scope", &new_scope);

    // Standalone functions
    module.add_function("new_category_renderer_from_file", &new_category_renderer_from_file);
    module.add_function("runtime_version", &get_scopes_runtime_version);

    exports->SetPrototype(module.create_prototype());
}

NODE_MODULE(unity_js_scopes_bindings, InitAll)
