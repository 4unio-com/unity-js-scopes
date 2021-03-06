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
var http = require('http');

var query_host = "www.colourlovers.com"
var query_path = "/api/palettes?format=json&numResults=100&keywords="

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
                    var qs = canned_query.query_string();
                    var cat_title = "";
                    if (!qs) {
                        cat_title = "Best palettes"
                    }
                    var category = search_reply.register_category("simple", cat_title, "");

                    var options = {
                        host: query_host,
                        path: query_path + qs
                    };

                    callback = function(response) {
                        var res = '';

                        // Another chunk of data has been recieved, so append it to res
                        response.on('data', function(chunk) {
                            res += chunk;
                        });

                        // The whole response has been recieved
                        response.on('end', function() {
                            r = JSON.parse(res);
                            for (i = 0; i < r.length; i++) {
                                var categorised_result = new scopes.lib.CategorisedResult(category);
                                categorised_result.set_uri(r[i].url);
                                categorised_result.set_title(r[i].title);
                                categorised_result.set_art(r[i].imageUrl);
                                search_reply.push(categorised_result);

                                // Limit result count to 15
                                if (i == 14) {
                                    break;
                                }
                            }
                            search_reply.finished(); // TODO: The user shouldn't need to call this explicitly.
                        });
                    }

                    http.request(options, callback).end();
                },
                // cancelled
                function() {
                });
        },
        preview: function(result, action_metadata) {
            return new scopes.lib.PreviewQuery(
                result,
                action_metadata,
                // run
                function(preview_reply) {
                    var layout1col = new scopes.lib.ColumnLayout(1);
                    var layout2col = new scopes.lib.ColumnLayout(2);
                    var layout3col = new scopes.lib.ColumnLayout(3);
                    layout1col.add_column(["image", "header", "summary"]);

                    layout2col.add_column(["image"]);
                    layout2col.add_column(["header", "summary"]);

                    layout3col.add_column(["image"]);
                    layout3col.add_column(["header", "summary"]);
                    layout3col.add_column([]);

                    preview_reply.register_layout([layout1col, layout2col, layout3col]);

                    var header = new scopes.lib.PreviewWidget("header", "header");
                    header.add_attribute_mapping("title", "title");
                    header.add_attribute_mapping("subtitle", "subtitle");

                    var image = new scopes.lib.PreviewWidget("image", "image");
                    image.add_attribute_mapping("source", "art");

                    var description = new scopes.lib.PreviewWidget("summary", "text");
                    description.add_attribute_mapping("text", "description");

                    preview_reply.push([image, header, description ]);
                    preview_reply.finished(); // TODO: The user shouldn't need to call this explicitly.
                },
                // cancelled
                function() {
                });
        }
    }
);

