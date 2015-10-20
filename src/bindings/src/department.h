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

#ifndef _UNITY_JS_DEPARTMENT_H_
#define _UNITY_JS_DEPARTMENT_H_

#include <unity/scopes/Department.h>
#include <unity/scopes/CannedQuery.h>

#include <v8-cpp.h>

class Department
{
 public:
  Department(const unity::scopes::Department& d);
  Department(v8::FunctionCallbackInfo<v8::Value> const& args);

  // v8 bindings
  void set_subdepartments(std::vector<std::shared_ptr<Department>> departments);
  void add_subdepartment(std::shared_ptr<Department> const &department);
  void set_alternate_label(std::string const &label);
  void set_has_subdepartments(bool subdepartments);
  std::string id() const;
  std::string label() const;
  std::string alternate_label() const;
  unity::scopes::CannedQuery query () const;
  std::vector<std::shared_ptr<Department>> subdepartments() const;
  bool has_subdepartments() const;

  unity::scopes::Department::SCPtr department();

 private:
  std::shared_ptr<unity::scopes::Department> department_;
};

#endif // _UNITY_JS_DEPARTMENT_H_
