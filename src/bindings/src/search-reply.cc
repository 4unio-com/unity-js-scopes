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

#include "categorised-result.h"
#include "option-selector-filter.h"
#include "range-input-filter.h"
#include "value-slider-filter.h"

#include <stdexcept>

#include <unity/scopes/SearchReply.h>


namespace {

unity::scopes::Filters from_v8_to_filters(
      v8::Isolate* isolate,
      v8::Local<v8::Value> value) {
  unity::scopes::Filters
    filter_bases;
  v8::Handle<v8::Object> o = v8::Handle<v8::Object>::Cast(value);
  for (size_t i = 0;
       i < o->Get(v8::String::NewFromUtf8(isolate, "length"))->ToObject()->Uint32Value();
       ++i) {
    v8::Local<v8::Value> fv = o->Get(i);
    try {
      auto f = v8cpp::from_v8<std::shared_ptr<OptionSelectorFilter>>(isolate, fv);
      filter_bases.push_back(f->get_filter());
    } catch(...) { }
    try {
      auto f = v8cpp::from_v8<std::shared_ptr<RangeInputFilter>>(isolate, fv);
      filter_bases.push_back(f->get_filter());
    } catch(...) { }
    try {
      auto f = v8cpp::from_v8<std::shared_ptr<ValueSliderFilter>>(isolate, fv);
      filter_bases.push_back(f->get_filter());
    } catch(...) { }
  }
  return filter_bases;
}
  
}


SearchReply::SearchReply(unity::scopes::SearchReplyProxy const& reply)
  : isolate_(v8::Isolate::GetCurrent())
  , reply_(reply){
}

unity::scopes::Category::SCPtr SearchReply::lookup_category(
      const std::string& id) {
  return reply_->lookup_category(id);
}

bool SearchReply::push(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 1 && args.Length() != 2) {
    throw std::runtime_error("Invalid number of arguments for search reply");
  }

  if (args.Length() == 1) {
    auto cr =
      v8cpp::from_v8<std::shared_ptr<CategorisedResult>>(isolate_, args[0]);
    return reply_->push(*cr);
  }

  auto filter_state =
      v8cpp::from_v8<std::shared_ptr<unity::scopes::FilterState>>(isolate_, args[1]);

  // TODO fix v8cpp shortcoming here
  return reply_->push(
      from_v8_to_filters(isolate_, args[0]),
      *filter_state);
}

unity::scopes::Category::SCPtr SearchReply::register_category(
      const std::string& id,
      const std::string& title,
      const std::string& icon,
      std::shared_ptr<unity::scopes::CategoryRenderer> category_renderer) {
  return reply_->register_category(
      id,
      title,
      icon,
      category_renderer ? *category_renderer : unity::scopes::CategoryRenderer());
}

void SearchReply::finished()
{
  reply_->finished();
}

void SearchReply::register_departments(std::shared_ptr<Department> department) {
  reply_->register_departments(department->department());
}

void SearchReply::info(const unity::scopes::OperationInfo& info) {
  reply_->info(info);
}
