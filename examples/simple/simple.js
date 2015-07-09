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

scopes.initialize('simple.ini', '')

scopes.me.onsearch(function(canned_query, metadata) {
    return scopes.lib.new_search_query(
        canned_query,
        metadata,
        // run
        function(search_reply) {
            var qs =
                canned_query.query_string();
            var category =
                search_reply.register_category("simple", "hello world from js", "");

            var categorised_result =
                scopes.lib.new_categorised_result(category);
            categorised_result.set_uri("http://www.ubuntu.com");
            categorised_result.set_title("Ubuntu");

            search_reply.push(categorised_result);
        },
        // cancelled
        function() {
        });
});

scopes.me.onpreview(function(result, action_metadata) {
});
