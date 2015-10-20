de/*
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

/**

--doc:class ColumnLayout
 * Describes a column layout for preview widgets.
 * 
 * @class ColumnLayout
--/doc:class

--doc:constructor
 * Creates a layout definition that expects num_of_columns columns to be added with ColumnLayout.add_column.
 * 
 * @param num_of_columns The number of columns for the layout.
--/doc:constructor

--doc:prototype ColumnLayout

--doc:member
 * Adds a new column and assigns widgets to it.
 * @param widget_ids ColumnLayout expects exactly the number of columns passed to the constructor to be created with the add_column method.
--doc:/member
add_column: function(Array of Strings: widget_ids) {
}
--/doc:member

--doc:member
 * Get the current number of columns in this layout.
 * @return The number of columns added with add_column()
--doc:/member
size: function() {
}
--/doc:member

--doc:member
 * Get the number of columns expected by this layout as specified in the constructor.
 * @return The number of columns expected by this layout.
--doc:/member
number_of_columns: function() {
}
--/doc:member

--doc:member
 * Retrieve the list of widgets for given column.
 * @param index The index of a column.
 * @return The widget identifiers for the given column index.
--doc:/member
number_of_columns: function(index) {
}
--/doc:member

--/doc:prototype

 */

