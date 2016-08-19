/*
 * Copyright 2015-2016 Canonical Ltd.
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

var SCOPE_NAME = 'simple'

function dump_scope_metadata(metadata) {
    console.log('Scope info');
    console.log('  ' + metadata.scope_id());
    console.log('  ' + metadata.display_name());
    console.log('  ' + metadata.description());
    console.log('  ' + metadata.author());
    console.log('  ' + metadata.art());
    console.log('  ' + metadata.icon());
    console.log('  ' + metadata.search_hint());
    console.log('  ' + metadata.hot_key());
    console.log('  ' + metadata.invisible());
    console.log('  ' + metadata.scope_directory());
    console.log('  ' + metadata.results_ttl_type());
    console.log('  ' + metadata.location_data_needed());
}

function dump_scope_registry_data() {
    try {
        console.log('Registry data ' +
                    scopes.self.registry.is_scope_running(SCOPE_NAME));
    } catch (e) {
        console.log('   ' + e);
    }

    try {
        var scopes_metadata = scopes.self.registry.list()

        for (var s in scopes_metadata) {
            dump_scope_metadata(scopes_metadata[s])
        }
    } catch (e) {
        console.log(e);
    }

    try {
        console.log('First pass')
        var scopes_metadata = scopes.self.registry.list_if(function(info) {
            return info.scope_id() == 'forth'
        })

        for (var s in scopes_metadata) {
            dump_scope_metadata(scopes_metadata[s])
        }

        console.log('Second pass')
        scopes_metadata = scopes.self.registry.list_if(function(info) {
            return info.scope_id() == 'simple'
        })

        for (var s in scopes_metadata) {
            dump_scope_metadata(scopes_metadata[s])
        }
    } catch (e) {
        console.log(e);
    }

    try {
        var scopes_metadata = scopes.self.registry.list()

        for (var s in scopes_metadata) {
            scopes.self.registry.set_scope_state_callback(
                scopes_metadata[s].scope_id(),
                function(is_running) {
                    console.log('I am possibly running '
                                + (is_running ? '(yes) ' : '(no) ') 
                                + scopes_metadata[s].scope_id())
            })
        }
    } catch (e) {
        console.log(e);
    }
}

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
            dump_scope_registry_data();
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

                    // Create a simple department
                    var root_department =
                        new scopes.lib.Department("", canned_query, "Simple Department")
                    
                    console.log('Department\'s associated query string : '
                                + root_department.query().query_string())
                    
                    var child_department =
                        new scopes.lib.Department("child", canned_query, "Simple Child Department")

                    root_department.set_subdepartments([child_department])
                    
                    search_reply.register_departments(root_department)
                    
                    var categorised_result =
                        new scopes.lib.CategorisedResult(category);
                    categorised_result.set_uri("http://www.ubuntu.com");
                    categorised_result.set_title("'" + qs + "'");
                    categorised_result.set_intercept_activation();

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
        preview: function(result, action_metadata) {},
        activate: function(result, metadata) {
            return new scopes.lib.ActivationQuery(
                result,
                metadata,
                "",
                "",
                // activate
                function() {
                    console.log('Activate called');

                    var activation_response = new scopes.lib.ActivationResponse(
                        scopes.defs.ActivationResponseStatus.NotHandled);

                    return activation_response;
                },
                // cancelled
                function() {
                }
            );
        },
    }
);
