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

/**

--doc:class Category
 * @module ScopeJS
 * 
 * A set of related results returned by a scope
 *  and displayed within a single pane in the Unity dash.
 * 
 * To create a Category, use SearchReply.register_category.
 * 
 * @class Category
--/doc:class

--doc:prototype Category

--doc:member
 * Get identifier of this Category
 * @method id
 * @return String The category identifier.
--doc:/member
id: function() {
}
--/doc:member

--doc:member
 * Get title of this Category
 * @method title
 * @return String The category title.
--doc:/member
title: function() {
}
--/doc:member

--doc:member
 * Get icon of this Category
 * @method icon
 * @return String The category icon.
--doc:/member
icon: function() {
}
--/doc:member

--doc:member
 * Query to perform when this category is expanded
 * @method query
 * @return CannedQuery The expansion query or null.
--doc:/member
query: function() {
}
--/doc:member

--/doc:prototype

 */

