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

var lib = require('./unity_js_scopes_bindings');
var core = require('./lib/scope-core.js');

// Init the first time it is accessed
var self;

function Scope(scope_binding) {
    this._scope_binding = scope_binding;
    this._base = scope_binding.scope_base();
 }
Scope.property = {
    ready: function() {
        return this._scope_binding.run(this._base);
    },
    run: function(callback) {
        this._base.run(callback);
    },
    start: function(callback) {
        this._base.start(callback);
    },
    stop: function(callback) {
        this._base.stop(callback);
    },
    search: function(callback) {
        this._base.search(callback);
    },
    activate: function(callback) {
        // TODO
    },
    performAction: function(callback) {
        // TODO
    },
    preview: function(callback) {
        this._base.preview(callback);
    },
    get scope_directory() {
        return this._base.scope_directory;
    },
    get cache_directory() {
        return this._base.scope_directory;
    },
    get tmp_directory() {
        return this._base.scope_directory;
    },
    get registry() {
        return null
    },
    get settings() {
        return null
    },
};

function setup_scope(scope_id, config_file) {
    if (self) {
        return;
    }
    self = new Scope(core.new_scope(scope_id, config_file));
}

module.exports = {
    init: function(scope_id, config_file) {
        setup_scope(scope_id, config_file);
    },
    lib: lib
}

Object.defineProperty(module.exports,
                      "me",
                      {
                          value: function() {
                              console.log('self ' + self)
                              if (! self) {
                                  return null
                              }
                              return self;
                          },
                          writable: false,
                          enumerable: true
                      });
