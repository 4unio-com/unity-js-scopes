#!/usr/bin/env python3

# Copyright (C) 2015 Canonical Ltd.

# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA  02110-1301  USA

import http.server
import os
import socketserver
import sys
from urllib.parse import urlparse,parse_qs

def read_file(path):
    file = os.path.join(os.path.dirname(__file__), path)
    if os.path.isfile(file):
        with open(file, 'r') as fp:
            content = fp.read()
    else:
        content = ''

    return content

class MyRequestHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        sys.stderr.write("GET: %s\n" % self.path)
        sys.stderr.flush()

        parse = urlparse(self.path)
        path = parse.path
        query = parse_qs(parse.query)
        
        if path == '/data/2.5/weather':
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()

            mode = 'json'
            if 'mode' in query:
                mode = query['mode'][0]

            self.wfile.write(bytes(read_file('weather/%s.%s' % (query['q'][0], mode)), 'UTF-8'))
        elif path == '/data/2.5/forecast/daily':
            self.send_response(200)
            self.send_header("Content-type", "text/html")
            self.end_headers()

            mode = 'json'
            if 'mode' in query:
                mode = query['mode'][0]

            self.wfile.write(bytes(read_file('forecast/%s.%s' % (query['q'][0], mode)), 'UTF-8'))
        else:
            self.send_response(404)
            self.send_header("Content-type", "text/html")
            self.end_headers()
            self.wfile.write(bytes('ERROR', 'UTF-8'))

if __name__ == "__main__":
    Handler = MyRequestHandler
    httpd = socketserver.TCPServer(("127.0.0.1", 0), Handler)

    sys.stdout.write('%d\n' % httpd.server_address[1])
    sys.stdout.flush()

    httpd.serve_forever()
