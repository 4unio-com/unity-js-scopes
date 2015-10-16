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

#include "department.h"


Department::Department(const unity::scopes::Department& d)
  : department_(new unity::scopes::Department(d)) {
}

Department::Department(v8::Local<v8::Value> arg1
                       , v8::Local<v8::Value> arg2
                       , v8::Local<v8::Value> arg3) {
  if (arg1->IsString()) {
    auto department_id =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), arg1);
    auto cq =
      v8cpp::from_v8<std::shared_ptr<unity::scopes::CannedQuery>>(
          v8::Isolate::GetCurrent(), arg2);
    auto label =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), arg3);

    department_ = unity::scopes::Department::create(department_id, *cq, label);
  } else {
    auto cq =
      v8cpp::from_v8<std::shared_ptr<unity::scopes::CannedQuery>>(
          v8::Isolate::GetCurrent(), arg1);
    auto label =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), arg2);

    department_ = unity::scopes::Department::create(*cq, label);
  }
}

void Department::set_subdepartments(std::vector<std::shared_ptr<Department>> departments) {
  unity::scopes::DepartmentList deps;
  for (auto & d: departments) {
    deps.push_back(unity::scopes::Department::SCPtr(new unity::scopes::Department(d->department())));
  }
  department_->set_subdepartments(deps);
}

void Department::add_subdepartment(std::shared_ptr<Department> const &department) {
  unity::scopes::Department::SCPtr dep(new unity::scopes::Department(department->department()));
  department_->add_subdepartment(dep);
}

void Department::set_alternate_label(std::string const &label) {
  department_->set_alternate_label(label);
}

void Department::set_has_subdepartments(bool subdepartments) {
  department_->set_has_subdepartments(subdepartments);
}

std::string Department::id() const {
  return department_->id();
}

std::string Department::label() const {
  return department_->label();
}

std::string Department::alternate_label() const {
  return department_->alternate_label();
}

std::shared_ptr<unity::scopes::CannedQuery>
Department::query () const {
  return std::shared_ptr<unity::scopes::CannedQuery> (
      new unity::scopes::CannedQuery(department_->query()));
}

std::vector<std::shared_ptr<Department>>
Department::subdepartments() const {
  std::vector<std::shared_ptr<Department>> deps;
  for (auto & d: department_->subdepartments()) {
    deps.push_back(std::shared_ptr<Department>(new Department(*d)));
  }
  return deps;
}

bool Department::has_subdepartments() const {
  return department_->has_subdepartments();
}

const unity::scopes::Department& Department::department() const {
  return *department_.get();
}

unity::scopes::Department& Department::department() {
  return *department_.get();
}
