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

#ifndef _UNITY_JS_PREVIEW_WIDGET_H_
#define _UNITY_JS_PREVIEW_WIDGET_H_

#include <unity/scopes/PreviewWidget.h>

#include <v8-cpp.h>

/**

--doc:class PreviewWidget
 * 
 * A widget for a preview.
 * 
 * @module ScopeJS
 * 
 * @class PreviewWidget
--/doc:class

--doc:prototype PreviewWidget

--doc:member
 * Adds an attribute definition and its value
 * @method add_attribute_value
 * @param key {String} Attribute definition
 * @param value {String}, {Number}, {Object}. The value can be a string, number, object
--doc:/member
add_attribute_value: function(key, value) {
}
--/doc:member

--doc:member
 * Adds an attribute definition using a component mapping
 * @method add_attribute_mapping
 * @param key {String} Attribute definition
 * @param value {String} Value
--doc:/member
add_attribute_mapping: function(key, value) {
}
--/doc:member

--doc:member
 * Adds a widget into expandable widget
 * @method add_widget
 * @param widget {PreviewWidget} The widget that needs to be added
--doc:/member
add_widget: function(widget) {
}
--/doc:member

--doc:member
 * Get the identifier of this widget
 * @method id
 * @return Id {String}
--doc:/member
id: function() {
}
--/doc:member

--doc:member
 * Get type name of this widget
 * @method widget_type
 * @return {String} Widget type
--doc:/member
widget_type: function() {
}
--/doc:member

--doc:member
 * Get the components of this widget
 * @method attribute_mappings
 * @return Dictionary of widget components
--doc:/member
attribute_mappings: function() {
}
--/doc:member

--doc:member
 * Get the attributes of this widget
 * @method attribute_values
 * @return Object corresponding to attributes of this widget
--doc:/member
attribute_values: function() {
}
--/doc:member

--doc:member
 * Get widgets of 'expandable' widget
 * @method widgets
 * @return List of PreviewWidget
--doc:/member
widgets: function() {
}
--/doc:member

--doc:member
 * Get a JSON representation of this widget
 * @method data
 * @return String representation of widget
--doc:/member
data: function() {
}
--/doc:member

--/doc:prototype
 */

class PreviewWidget
{
 public:
  PreviewWidget(v8::Local<v8::Value> arg1,
                v8::Local<v8::Value> arg2);
  PreviewWidget(const unity::scopes::PreviewWidget& preview_widget);

  // v8 binding
  void add_attribute_value(v8::FunctionCallbackInfo<v8::Value> const& args);
  void add_widget(std::shared_ptr<unity::scopes::PreviewWidget> preview_widget);
  std::string id() const;
  void add_attribute_mapping(const std::string& k, const std::string& field_name);
  std::string widget_type() const;
  std::map<std::string, std::string> attribute_mappings() const;
  v8::Local<v8::Object> attribute_values() const;
  std::vector<std::shared_ptr<PreviewWidget>> widgets() const;
  std::string data() const;

  unity::scopes::PreviewWidget & preview_widget() const;

 private:
  v8::Isolate* isolate_;
  std::unique_ptr<unity::scopes::PreviewWidget> preview_widget_;
};

#endif // _UNITY_JS_PREVIEW_WIDGET_H_
