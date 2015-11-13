// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Flags: --harmony-computed-property-names --harmony-sloppy

assertThrows(function f() {
  var t = { toString: function() { throw new Error(); } };
  var o = { [t]: 23 };
}, Error);

assertThrows(function f() {
  var t = { toString: function() { throw new Error(); } };
  class C { [t]() { return 23; } };
}, Error);
