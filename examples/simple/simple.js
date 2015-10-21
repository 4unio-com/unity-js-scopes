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

var scopes = require('unity-js-scopes')

scopes.self.initialize(
    {}
    ,
    {
        run: function() {
            console.log('Running...')
        },
        start: function(scope_id) {
            console.log('Starting scope id: '
                        + scope_id
                        + ', '
                        + scopes.self.scope_config)
        },
        search: function(canned_query, metadata) {
            return new scopes.lib.search_query(
                canned_query,
                metadata,
                // run
                function(search_reply) {
                    var qs =
                        canned_query.query_string();
                    var category =
                        search_reply.register_category(
                            "simple",
                            "hello world from js",
                            "",
                            null);

                    var categorised_result =
                        new scopes.lib.categorised_result(category);
                    categorised_result.set_uri("http://www.ubuntu.com");
                    categorised_result.set_title("'" + qs + "'");

                    var filter_state =
                        new scopes.lib.filter_state();
                    var option_state =
                        new scopes.lib.option_selector_filter('id', 'push', false);

                    var p = search_reply.push([option_state], filter_state);
                    console.log(' push : ' + p);

                    search_reply.push(categorised_result);
                },
                // cancelled
                function() {
                });
        },
        preview: function(result, action_metadata) {}
    }
);

