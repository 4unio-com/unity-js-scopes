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
var request = require('sync-request');
var query_url = "http://www.colourlovers.com/api/palettes?format=json&numResults=100&keywords="

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
            return scopes.lib.new_search_query(
                canned_query,
                metadata,
                // run
                function(search_reply) {
                    var qs = canned_query.query_string();
                    var cat_title = "";
                    if (!qs) {
                        cat_title = "Best palettes"
                    }
                    var category = search_reply.register_category("simple", cat_title, "");
                    var res = request('GET', query_url+qs);
                    r = JSON.parse(res.getBody())
                    for(i = 0; i < r.length; i++) {
                        var categorised_result = scopes.lib.new_categorised_result(category);
                        categorised_result.set_uri(r[i].url);
                        categorised_result.set_title(r[i].title);
                        categorised_result.set_art(r[i].imageUrl);
                        search_reply.push(categorised_result);
                    }
                },
                // cancelled
                function() {
                });
        },
        preview: function(result, action_metadata) {}
    }
    );

