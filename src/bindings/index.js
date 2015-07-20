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

function Scope() {}

Scope.prototype = {
    initialize: function(options, runtime_config) {
        this._setup_backend();

        if (! options || typeof(options) !== 'object') {
            throw "No or invalid options specified";
        }
        
        if (! runtime_config || typeof(runtime_config) !== 'object') {
            throw "No or invalid runtime configuration specified";
        }

        if (runtime_config.run && typeof(runtime_config.run) === 'function') {
            this._base.onrun(runtime_config.run);
        }

        if (runtime_config.start && typeof(runtime_config.start) === 'function') {
            this._base.onstart(runtime_config.start);
        }

        if (runtime_config.stop && typeof(runtime_config.stop) === 'function') {
            this._base.onstop(runtime_config.stop);
        }

        if (runtime_config.preview && typeof(runtime_config.preview) === 'function') {
            this._base.onpreview(runtime_config.preview);
        }

        if (runtime_config.activate && typeof(runtime_config.activate) === 'function') {
            // this._base.onactivate(runtime_config.activate);
        }

        return this._scope_binding.run(
            options && options.scope_id ? options.scope_id : "");
    },
    _setup_backend: function(options) {
        if (! this._scope_binding) {
            this._scope_binding = core.new_scope(options ? options.runtime_config : "");
            this._base = this._scope_binding.scope_base();
        }
    },
    get scope_directory() {
        return this._base.get_scope_directory();
    },
    get cache_directory() {
        return this._base.get_cache_directory();
    },
    get tmp_directory() {
        return this._base.get_tmp_directory();
    },
    get registry() {
        return null
    },
    get settings() {
        return null
    },
};

module.exports = {
    lib: lib
}

Object.defineProperty(
    module.exports,
    "self",
    {
        get: function() {
            if (! self) {
                self = new Scope();
            }
            return self;
        },
    });
