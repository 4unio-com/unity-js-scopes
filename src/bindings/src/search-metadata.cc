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

#include "search-metadata.h"

#include "common.h"

namespace {

unity::scopes::QueryMetadata::ConnectivityStatus
connectivity_status_from_string(const std::string& connectivity_status) {
  if (connectivity_status == "Unknown") {
    return unity::scopes::QueryMetadata::Unknown;
  }
  if (connectivity_status == "Connected") {
    return unity::scopes::QueryMetadata::Connected;
  }
  if (connectivity_status == "Disconnected") {
    return unity::scopes::QueryMetadata::Disconnected;
  }
  throw std::runtime_error("Invalid connectivity status string");
}

std::string
string_from_connectivity_status(unity::scopes::QueryMetadata::ConnectivityStatus connectivity_status) {
  switch (connectivity_status) {
  case unity::scopes::QueryMetadata::Unknown:
    return "Unknown";
  case unity::scopes::QueryMetadata::Connected:
    return "Connected";
  case unity::scopes::QueryMetadata::Disconnected:
    return "Disconnected";
  }
  throw std::runtime_error("Invalid connectivity status string");
}

}


SearchMetadata::SearchMetadata(v8::FunctionCallbackInfo<v8::Value> const& args) {
  if (args.Length() != 2 || args.Length() != 3) {
    throw std::runtime_error("Invalid number of arguments");
  }

  if (args[0]->IsString()) {
    auto locale =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[0]);
    auto form_factor =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[1]);

    metadata_.reset(new unity::scopes::SearchMetadata(locale, form_factor));
  } else {
    auto cardinality =
      v8cpp::from_v8<int>(v8::Isolate::GetCurrent(), args[0]);
    auto locale =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[1]);
    auto form_factor =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[2]);

    metadata_.reset(new unity::scopes::SearchMetadata(cardinality, locale, form_factor));
  }
}

SearchMetadata::SearchMetadata(const unity::scopes::SearchMetadata& meta_data)
  : metadata_(new unity::scopes::SearchMetadata(meta_data)) {
}

void SearchMetadata::set_location(
      const unity::scopes::Location& location) {
  metadata_->set_location(location);
}

unity::scopes::Location SearchMetadata::location() const {
  return metadata_->location();
}

void SearchMetadata::set_cardinality(int cardinality) {
  metadata_->set_cardinality(cardinality);
}
 
int SearchMetadata::cardinality() const {
  return metadata_->cardinality();
}

bool SearchMetadata::has_location() const {
  return metadata_->has_location();
}

void SearchMetadata::remove_location() {
  metadata_->remove_location();
}

void SearchMetadata::set_aggregated_keywords(std::set<std::string> const& aggregated_keywords) {
  metadata_->set_aggregated_keywords(aggregated_keywords);
}

std::set<std::string> SearchMetadata::aggregated_keywords() const {
  return metadata_->aggregated_keywords();
}

bool SearchMetadata::is_aggregated() const {
  return metadata_->is_aggregated();
}

void SearchMetadata::set_hint(std::string const& key, v8::Local<v8::Value> value) {
  metadata_->set_hint(key, unity::scopesjs::to_variant(value));
}

v8::Local<v8::Value> SearchMetadata::hints() const {
  return unity::scopesjs::from_variant(unity::scopes::Variant(metadata_->hints()));
}

void SearchMetadata::set(const std::string& k, v8::Local<v8::Value> value) {
  (*metadata_)[k] = unity::scopesjs::to_variant(value);
}

v8::Local<v8::Value> SearchMetadata::get(const std::string& k) {
  return unity::scopesjs::from_variant((*metadata_)[k]);
}

std::shared_ptr<unity::scopes::SearchMetadata> SearchMetadata::metadata() {
  return metadata_;
}

std::string SearchMetadata::locale() const {
  return metadata_->locale();
}

std::string SearchMetadata::form_factor() const {
  return metadata_->form_factor();
}

void SearchMetadata::set_internet_connectivity(const std::string& internet_connectivity) {
  metadata_->set_internet_connectivity(connectivity_status_from_string(internet_connectivity));
}

std::string SearchMetadata::internet_connectivity() const {
  return string_from_connectivity_status(metadata_->internet_connectivity());
}
