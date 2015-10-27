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

/**

--doc:class Department
 * 
 * A department with optional sub-department
 * 
 * @module ScopeJS
 * @class Department
--/doc:class

--doc:constructor
 * 
 * @constructor
 * @param query {CannedQuery} query associated with the Department
 * @param label {String} name of the Department
--/doc:constructor

--doc:prototype OnlineAccountClient

--doc:member
 * Add sub-department to this department
 * @method add_subdepartment
 * @param {Department} sub department
--doc:/member
add_subdepartment: function(department) {
}
--/doc:member

--doc:member
 * Get the alternate label of this department
 * Return the alternate label of this department. The alternate label expresses the plural "all" form of the normal label. For example, if the normal label is "Books", then the alternate label is "All Books". Note that alternate label and can be empty - in that case the normal label should be displayed instead
 * @method alternate_label
 * @return {String} alternate label
--doc:/member
alternate_label: function() {
}
--/doc:member

--doc:member
 * Set sub-departments of this department
 * @param departments {Array of Department}
 * @method set_subdepartments
--doc:/member
set_subdepartments: function(departments) {
}
--/doc:member

--doc:member
 * Sets has_subdepartments flag of this department
 * @method set_has_subdepartments
 * @param subdepartments {Boolean}
--doc:/member
set_has_subdepartments: function(subdepartments) {
}
--/doc:member

--doc:member
 * Get the identifier of this department
 * @method id
 * @return {String} identifier of this department
--doc:/member
id: function() {
}
--/doc:member

--doc:member
 * Get the label of this department
 * @method label
 * @return {String} label of this department
--doc:/member
label: function() {
}
--/doc:member

--doc:member
 * Get the alternate label of this department
 * @method alternate_label
 * @return {String} alternate label of this department
--doc:/member
alternate_label: function() {
}
--/doc:member

--doc:member
 * Get the canned query associated with this department
 * @method query
 * @return {CannedQuery} canned query associated with this department
--doc:/member
query: function() {
}
--/doc:member

--doc:member
 * Get list of sub-departments of this department
 * @method subdepartments
 * @return {Array of Department} list of sub-departments of this department
--doc:/member
subdepartments: function() {
}
--/doc:member

--doc:member
 * Check if this department has subdepartments or has_subdepartments flag is set
 * @method has_subdepartments
 * @return {Boolean} True if this department has subdepartments or has_subdepartments flag is set
--doc:/member
has_subdepartments: function() {
}
--/doc:member

--/doc:prototype

 */

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
