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

--doc:class OnlineAccountClientServiceStatus
 * 
 * An object that contains the details about a service's status and authorization parameters
 * 
 * @module ScopeJS
 * @class OnlineAccountClientServiceStatus
--/doc:class

--doc:prototype OnlineAccountClientServiceStatus

--doc:member
 * Check if state for the given filter has been stored
 * @property account_id {String}
--doc:/member
--/doc:member

--doc:member
 * True if this service is enabled
 * @property service_enabled {Boolean}
--doc:/member
--/doc:member

--doc:member
 * True if this service is authenticated
 * @property service_authenticated {Boolean}
--doc:/member
--/doc:member

--doc:member
 * "ConsumerKey" / "ClientId" OAuth (1 / 2) parameter.
 * @property client_id {String}
--doc:/member
--/doc:member

--doc:member
 * "ClientSecret" / "ConsumerSecret" OAuth (1 / 2) parameter.
 * @property client_secret {String}
--doc:/member
--/doc:member

--doc:member
 * "AccessToken" OAuth parameter.
 * @property access_token {String}
--doc:/member
--/doc:member

--doc:member
 * "TokenSecret" OAuth parameter.
 * @property token_secret {String}
--doc:/member
--/doc:member

--doc:member
 * Error message (empty if no error occurred).
 * @property error {String}
--doc:/member
--/doc:member

--/doc:prototype

 */
