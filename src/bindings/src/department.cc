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

Department::Department(v8::FunctionCallbackInfo<v8::Value> const & args) {
  if (args.Length() != 2 && args.Length() != 3) {
    throw std::runtime_error("Invalid number of arguments for department");
  }

  if (args[0]->IsString()) {
    auto department_id =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[0]);
    auto cq =
      v8cpp::from_v8<std::shared_ptr<CannedQuery>>(
          v8::Isolate::GetCurrent(), args[1]);
    auto label =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[2]);

    department_ =
      unity::scopes::Department::create(department_id, cq->canned_query(), label);
  } else {
    auto cq =
      v8cpp::from_v8<std::shared_ptr<CannedQuery>>(
          v8::Isolate::GetCurrent(), args[0]);
    auto label =
      v8cpp::from_v8<std::string>(v8::Isolate::GetCurrent(), args[1]);

    department_ = unity::scopes::Department::create(cq->canned_query(), label);
  }
}

void Department::set_subdepartments(std::vector<std::shared_ptr<Department>> departments) {
  unity::scopes::DepartmentList deps;
  for (auto & d: departments) {
    deps.push_back(d->department());
  }
  department_->set_subdepartments(deps);
}

void Department::add_subdepartment(std::shared_ptr<Department> const &department) {
  department_->add_subdepartment(department->department());
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

std::shared_ptr<CannedQuery>
Department::query () const {
  return std::make_shared<CannedQuery>(department_->query());
}

std::vector<std::shared_ptr<Department>>
Department::subdepartments() const {
  std::vector<std::shared_ptr<Department>> deps;
  for (auto & d: department_->subdepartments()) {
    deps.push_back(std::make_shared<Department>(*d));
  }
  return deps;
}

bool Department::has_subdepartments() const {
  return department_->has_subdepartments();
}

unity::scopes::Department::SCPtr Department::department() {
  return department_;
}
