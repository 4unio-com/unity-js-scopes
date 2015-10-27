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
            return new scopes.lib.SearchQuery(
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
                        new scopes.lib.CategorisedResult(category);
                    categorised_result.set_uri("http://www.ubuntu.com");
                    categorised_result.set_title("'" + qs + "'");

                    var filter_state =
                        new scopes.lib.FilterState();
                    var option_filter =
                        new scopes.lib.OptionSelectorFilter('me', 'push', false);
                    var option = option_filter.add_option("id", "yes");

                    var p = search_reply.push([option_filter], filter_state);
                    console.log(' push : ' + p);

                    // You can specify information about a search reply context
                    search_reply.info(
                        new scopes.lib.OperationInfo(
                            scopes.defs.OperationInfo.Code.PoorInternet,
                            "Poor internet connection"));

                    search_reply.push(categorised_result);
                },
                // cancelled
                function() {
                });
        },
        preview: function(result, action_metadata) {}
    }
);

