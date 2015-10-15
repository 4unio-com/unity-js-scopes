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
 * A widget for a preview.
 * 
 * @class PreviewWidget
--/doc:class

--doc:prototype PreviewWidget

--doc:member
 * Adds an attribute definition and its value
 * @param key Attribute definition
 * @param value Value. The value can be a string, number, object
--doc:/member
add_attribute_value: function(String: key, Variant: value) {
}
--/doc:member

--doc:member
 * Adds an attribute definition using a component mapping
 * @param key Attribute definition
 * @param value Value
--doc:/member
add_attribute_mapping: function(String: key, String: value) {
}
--/doc:member

--doc:member
 * Adds a widget into expandable widget
 * @param widget The widget that needs to be added
--doc:/member
add_widget: function(PreviewWidget: widget) {
}
--/doc:member

--doc:member
 * Get the identifier of this widget
 * @return Id string
--doc:/member
id: function() {
}
--/doc:member

--doc:member
 * Get type name of this widget
 * @return Widget type
--doc:/member
widget_type: function() {
}
--/doc:member

--doc:member
 * Get the components of this widget
 * @return Dictionary of widget components
--doc:/member
attribute_mappings: function() {
}
--/doc:member

--doc:member
 * Get the attributes of this widget
 * @return Object corresponding to attributes of this widget
--doc:/member
attribute_values: function() {
}
--/doc:member

--doc:member
 * Get widgets of 'expandable' widget
 * @return List of PreviewWidget
--doc:/member
widgets: function() {
}
--/doc:member

--doc:member
 * Get a JSON representation of this widget
 * @return String representation of widget
--doc:/member
data: function() {
}
--/doc:member

--/doc:prototype
 */

class PreviewWidget : public unity::scopes::PreviewWidget
{
 public:
  PreviewWidget(std::string const &id,
                std::string const &widget_type);
  PreviewWidget(const std::string& definition);
  ~PreviewWidget();

  // v8 binding
  void add_attribute_value(v8::FunctionCallbackInfo<v8::Value> const& args);
  void add_widget(std::shared_ptr<unity::scopes::PreviewWidget> preview_widget);
};

#endif // _UNITY_JS_PREVIEW_WIDGET_H_
