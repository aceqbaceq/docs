/******/ (function(modules) { // webpackBootstrap
/******/ 	// The module cache
/******/ 	var installedModules = {};
/******/
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/
/******/ 		// Check if module is in cache
/******/ 		if(installedModules[moduleId]) {
/******/ 			return installedModules[moduleId].exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = installedModules[moduleId] = {
/******/ 			i: moduleId,
/******/ 			l: false,
/******/ 			exports: {}
/******/ 		};
/******/
/******/ 		// Execute the module function
/******/ 		modules[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/
/******/ 		// Flag the module as loaded
/******/ 		module.l = true;
/******/
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/
/******/
/******/ 	// expose the modules object (__webpack_modules__)
/******/ 	__webpack_require__.m = modules;
/******/
/******/ 	// expose the module cache
/******/ 	__webpack_require__.c = installedModules;
/******/
/******/ 	// define getter function for harmony exports
/******/ 	__webpack_require__.d = function(exports, name, getter) {
/******/ 		if(!__webpack_require__.o(exports, name)) {
/******/ 			Object.defineProperty(exports, name, {
/******/ 				configurable: false,
/******/ 				enumerable: true,
/******/ 				get: getter
/******/ 			});
/******/ 		}
/******/ 	};
/******/
/******/ 	// getDefaultExport function for compatibility with non-harmony modules
/******/ 	__webpack_require__.n = function(module) {
/******/ 		var getter = module && module.__esModule ?
/******/ 			function getDefault() { return module['default']; } :
/******/ 			function getModuleExports() { return module; };
/******/ 		__webpack_require__.d(getter, 'a', getter);
/******/ 		return getter;
/******/ 	};
/******/
/******/ 	// Object.prototype.hasOwnProperty.call
/******/ 	__webpack_require__.o = function(object, property) { return Object.prototype.hasOwnProperty.call(object, property); };
/******/
/******/ 	// __webpack_public_path__
/******/ 	__webpack_require__.p = "";
/******/
/******/ 	// Load entry module and return exports
/******/ 	return __webpack_require__(__webpack_require__.s = 0);
/******/ })
/************************************************************************/
/******/ ([
/* 0 */
/***/ (function(module, exports, __webpack_require__) {

var _typeof = typeof Symbol === "function" && typeof Symbol.iterator === "symbol" ? function (obj) { return typeof obj; } : function (obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; };

var _window$themehouse$co2;

function _defineProperty(obj, key, value) { if (key in obj) { Object.defineProperty(obj, key, { value: value, enumerable: true, configurable: true, writable: true }); } else { obj[key] = value; } return obj; }

// http://paulirish.com/2011/requestanimationframe-for-smart-animating/
// http://my.opera.com/emoller/blog/2011/12/20/requestanimationframe-for-smart-er-animating

// requestAnimationFrame polyfill by Erik Möller. fixes from Paul Irish and Tino Zijdel

// MIT license

var polyfills = function polyfills() {
    var lastTime = 0;
    var vendors = ['ms', 'moz', 'webkit', 'o'];
    for (var x = 0; x < vendors.length && !window.requestAnimationFrame; ++x) {
        window.requestAnimationFrame = window[vendors[x] + 'RequestAnimationFrame'];
        window.cancelAnimationFrame = window[vendors[x] + 'CancelAnimationFrame'] || window[vendors[x] + 'CancelRequestAnimationFrame'];
    }

    if (!window.requestAnimationFrame) {
        window.requestAnimationFrame = function (callback) {
            var currTime = new Date().getTime();
            var timeToCall = Math.max(0, 16 - (currTime - lastTime));
            var id = window.setTimeout(function () {
                callback(currTime + timeToCall);
            }, timeToCall);
            lastTime = currTime + timeToCall;
            return id;
        };
    }

    if (!window.cancelAnimationFrame) {
        window.cancelAnimationFrame = function (id) {
            clearTimeout(id);
        };
    }

    (function (ElementProto) {
        if (typeof ElementProto.matches !== 'function') {
            ElementProto.matches = ElementProto.msMatchesSelector || ElementProto.mozMatchesSelector || ElementProto.webkitMatchesSelector || function matches(selector) {
                var element = this;
                var elements = (element.document || element.ownerDocument).querySelectorAll(selector);
                var index = 0;

                while (elements[index] && elements[index] !== element) {
                    ++index;
                }

                return Boolean(elements[index]);
            };
        }

        if (typeof ElementProto.closest !== 'function') {
            ElementProto.closest = function closest(selector) {
                var element = this;

                while (element && element.nodeType === 1) {
                    if (element.matches(selector)) {
                        return element;
                    }

                    element = element.parentNode;
                }
                return null;
            };
        }
    })(window.Element.prototype);

    if (typeof Object.assign !== 'function') {
        // Must be writable: true, enumerable: false, configurable: true
        Object.defineProperty(Object, "assign", {
            value: function assign(target, varArgs) {
                // .length of function is 2
                'use strict';

                if (target == null) {
                    // TypeError if undefined or null
                    throw new TypeError('Cannot convert undefined or null to object');
                }

                var to = Object(target);

                for (var index = 1; index < arguments.length; index++) {
                    var nextSource = arguments[index];

                    if (nextSource != null) {
                        // Skip over if undefined or null
                        for (var nextKey in nextSource) {
                            // Avoid bugs when hasOwnProperty is shadowed
                            if (Object.prototype.hasOwnProperty.call(nextSource, nextKey)) {
                                to[nextKey] = nextSource[nextKey];
                            }
                        }
                    }
                }
                return to;
            },
            writable: true,
            configurable: true
        });
    }
};

polyfills();

__webpack_require__(1);

var version = '20180112';

if (typeof window.themehouse === 'undefined') {
    window.themehouse = {};
}

if (typeof window.themehouse.data === 'undefined') {
    window.themehouse.data = {};
}

if (typeof window.themehouse.common === 'undefined') {
    window.themehouse.common = {};
}

window.themehouse.common[version] = (_window$themehouse$co2 = {
    events: {},
    debug: false,
    values: {},
    timeout: null,

    measureScroll: function measureScroll() {
        window.themehouse.common[version].values.scrollX = window.scrollX;
        window.themehouse.common[version].values.scrollY = window.scrollY;
    },

    measureResize: function measureResize() {
        window.themehouse.common[version].values.innerWidth = window.innerWidth;
        window.themehouse.common[version].values.innerHeight = window.innerHeight;
        window.themehouse.common[version].values.offsetHeight = window.document.body.offsetHeight;
        window.themehouse.common[version].values.offsetWidth = window.document.body.offsetWidth;
    },

    register: function register(config) {
        if (typeof window.themehouse.common[version].events[config.phase] === 'undefined') {
            window.themehouse.common[version].events[config.phase] = [];
        }

        window.themehouse.common[version].events[config.phase].push(config);

        window.themehouse.common[version].ensureRun();
    },


    ensureRun: function ensureRun() {
        if (window.themehouse.common[version].timeout !== null) {
            window.clearTimeout(window.themehouse.common[version].timeout);
        }
        window.themehouse.common[version].timeout = window.setTimeout(window.themehouse.common[version].initMissing, 500);
    },

    initMissing: function initMissing() {
        window.themehouse.common[version].timeout = null;
        var phases = ['initGet', 'afterGet', 'initSet', 'afterSet'];
        for (var phaseIndex = 0, phaseLen = phases.length; phaseIndex < phaseLen; phaseIndex++) {
            var phase = phases[phaseIndex];
            var events = window.themehouse.common[version].events[phase];
            if (events) {
                for (var eventIndex = 0, eventLen = events.length; eventIndex < eventLen; eventIndex++) {
                    var event = events[eventIndex];
                    if (event.hasRun !== true) {
                        window.themehouse.common[version].runEvent(eventIndex, phase);
                    }
                }
            }
        }
    },

    init: function init() {
        var _this = this;

        var common = window.themehouse.common[version];
        var phaseTime = common.time();

        this.measureScroll();
        this.measureResize();
        window.themehouse.common[version].run('initGet');
        window.themehouse.common[version].run('initSet');

        window.addEventListener('resize', function () {
            _this.measureScroll();
            _this.measureResize();
            window.themehouse.common[version].run('resizeGet');
            window.themehouse.common[version].run('resizeSet');
        });
        window.addEventListener('scroll', function () {
            _this.measureScroll();
            window.themehouse.common[version].run('scrollGet');
            window.themehouse.common[version].run('scrollSet');
        });

        window.setTimeout(function () {
            window.themehouse.common[version].run('afterGet'); // low priority
            window.themehouse.common[version].run('afterSet');
        }, 0);

        if (common.debug) {
            console.log('Total Register: ' + common.round(common.time() - phaseTime, 5) + ' ms');
            console.log('=====================');
        }
    },
    measureWindowSize: function measureWindowSize() {
        window.themehouse.data.windowWidth = window.innerWidth;
        window.themehouse.data.windowHeight = window.innerHeight;
    }
}, _defineProperty(_window$themehouse$co2, 'measureScroll', function measureScroll() {
    window.themehouse.data.scrollX = window.scrollX;
    window.themehouse.data.scrollY = window.scrollY;
}), _defineProperty(_window$themehouse$co2, 'run', function run(phase) {
    var common = window.themehouse.common[version];
    var events = common.events[phase] || [];
    var debug = common.debug;
    var phaseTime = common.time();
    for (var i = 0, len = events.length; i < len; i++) {
        common.runEvent(i, phase);
    }

    if (debug) {
        console.log('Total ' + phase + ': ' + common.round(common.time() - phaseTime, 5) + ' ms');
        console.log('=====================');
    }
}), _defineProperty(_window$themehouse$co2, 'runEvent', function runEvent(eventIndex, phase) {
    var common = window.themehouse.common[version];
    var debug = common.debug;
    var _window$themehouse$co = window.themehouse.common[version].events[phase][eventIndex],
        func = _window$themehouse$co.func,
        addon = _window$themehouse$co.addon;


    window.themehouse.common[version].events[phase][eventIndex].hasRun = true;

    if (typeof func === 'function') {
        var time = common.time();
        func();
        if (debug) {
            console.log(addon + '-' + phase + ': ' + common.round(common.time() - time, 5) + ' ms');
        }
    }
}), _defineProperty(_window$themehouse$co2, 'time', function time() {
    if (window.themehouse.common[version] === false) return 0;
    if (typeof window.performance === 'undefined') {
        return Date.now();
    }
    return window.performance.now ? window.performance.now() + window.performance.timing.navigationStart : Date.now();
}), _defineProperty(_window$themehouse$co2, 'round', function round(num) {
    var points = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : 2;

    return Math.round(num * Math.pow(10, points)) / Math.pow(10, points);
}), _defineProperty(_window$themehouse$co2, 'fetch', function fetch(link) {
    window.jQuery.ajax(link);
}), _defineProperty(_window$themehouse$co2, 'log', function log() {
    for (var _len = arguments.length, msg = Array(_len), _key = 0; _key < _len; _key++) {
        msg[_key] = arguments[_key];
    }

    console.log(msg); // eslint-disable-line no-console
}), _defineProperty(_window$themehouse$co2, 'warn', function warn() {
    for (var _len2 = arguments.length, msg = Array(_len2), _key2 = 0; _key2 < _len2; _key2++) {
        msg[_key2] = arguments[_key2];
    }

    console.warn(msg); // eslint-disable-line no-console
}), _defineProperty(_window$themehouse$co2, 'error', function error() {
    for (var _len3 = arguments.length, msg = Array(_len3), _key3 = 0; _key3 < _len3; _key3++) {
        msg[_key3] = arguments[_key3];
    }

    console.error(msg); // eslint-disable-line no-console
}), _defineProperty(_window$themehouse$co2, 'resizeFire', function resizeFire() {
    if (window.document.createEvent) {
        // W3C
        var ev = window.document.createEvent('Event');
        ev.initEvent('resize', true, true);
        window.dispatchEvent(ev);
    } else {
        // IE
        window.document.fireEvent('onresize');
    }
}), _window$themehouse$co2);

window.document.addEventListener('DOMContentLoaded', function () {
    var init = true;
    if (_typeof(window.themehouse) === 'object') {
        if (_typeof(window.themehouse.settings) === 'object') {
            if (_typeof(window.themehouse.settings.common) === 'object') {
                if (_typeof(window.themehouse.settings.common[version]) === 'object') {
                    var commonSettings = window.themehouse.settings.common[version];
                    if (commonSettings.init === false) {
                        init = false;
                    }
                }
            }
        }
    }
    if (init) {
        window.themehouse.common[version].init();
    }
});

/***/ }),
/* 1 */
/***/ (function(module, exports, __webpack_require__) {

/* WEBPACK VAR INJECTION */(function(global) {/*!
Copyright (C) 2015 by WebReflection

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
(function (Object, GOPS) {'use strict';

  // (C) Andrea Giammarchi - Mit Style

  if (GOPS in Object) return;

  var
    setDescriptor,
    G = typeof global === typeof G ? window : global,
    id = 0,
    random = '' + Math.random(),
    prefix = '__\x01symbol:',
    prefixLength = prefix.length,
    internalSymbol = '__\x01symbol@@' + random,
    DP = 'defineProperty',
    DPies = 'defineProperties',
    GOPN = 'getOwnPropertyNames',
    GOPD = 'getOwnPropertyDescriptor',
    PIE = 'propertyIsEnumerable',
    gOPN = Object[GOPN],
    gOPD = Object[GOPD],
    create = Object.create,
    keys = Object.keys,
    freeze = Object.freeze || Object,
    defineProperty = Object[DP],
    $defineProperties = Object[DPies],
    descriptor = gOPD(Object, GOPN),
    ObjectProto = Object.prototype,
    hOP = ObjectProto.hasOwnProperty,
    pIE = ObjectProto[PIE],
    toString = ObjectProto.toString,
    indexOf = Array.prototype.indexOf || function (v) {
      for (var i = this.length; i-- && this[i] !== v;) {}
      return i;
    },
    addInternalIfNeeded = function (o, uid, enumerable) {
      if (!hOP.call(o, internalSymbol)) {
        defineProperty(o, internalSymbol, {
          enumerable: false,
          configurable: false,
          writable: false,
          value: {}
        });
      }
      o[internalSymbol]['@@' + uid] = enumerable;
    },
    createWithSymbols = function (proto, descriptors) {
      var self = create(proto);
      gOPN(descriptors).forEach(function (key) {
        if (propertyIsEnumerable.call(descriptors, key)) {
          $defineProperty(self, key, descriptors[key]);
        }
      });
      return self;
    },
    copyAsNonEnumerable = function (descriptor) {
      var newDescriptor = create(descriptor);
      newDescriptor.enumerable = false;
      return newDescriptor;
    },
    get = function get(){},
    onlyNonSymbols = function (name) {
      return  name != internalSymbol &&
              !hOP.call(source, name);
    },
    onlySymbols = function (name) {
      return  name != internalSymbol &&
              hOP.call(source, name);
    },
    propertyIsEnumerable = function propertyIsEnumerable(key) {
      var uid = '' + key;
      return onlySymbols(uid) ? (
        hOP.call(this, uid) &&
        this[internalSymbol]['@@' + uid]
      ) : pIE.call(this, key);
    },
    setAndGetSymbol = function (uid) {
      var descriptor = {
        enumerable: false,
        configurable: true,
        get: get,
        set: function (value) {
          setDescriptor(this, uid, {
            enumerable: false,
            configurable: true,
            writable: true,
            value: value
          });
          addInternalIfNeeded(this, uid, true);
        }
      };
      defineProperty(ObjectProto, uid, descriptor);
      return freeze(source[uid] = defineProperty(
        Object(uid),
        'constructor',
        sourceConstructor
      ));
    },
    Symbol = function Symbol(description) {
      if (this && this !== G) {
        throw new TypeError('Symbol is not a constructor');
      }
      return setAndGetSymbol(
        prefix.concat(description || '', random, ++id)
      );
    },
    source = create(null),
    sourceConstructor = {value: Symbol},
    sourceMap = function (uid) {
      return source[uid];
    },
    $defineProperty = function defineProp(o, key, descriptor) {
      var uid = '' + key;
      if (onlySymbols(uid)) {
        setDescriptor(o, uid, descriptor.enumerable ?
            copyAsNonEnumerable(descriptor) : descriptor);
        addInternalIfNeeded(o, uid, !!descriptor.enumerable);
      } else {
        defineProperty(o, key, descriptor);
      }
      return o;
    },
    $getOwnPropertySymbols = function getOwnPropertySymbols(o) {
      return gOPN(o).filter(onlySymbols).map(sourceMap);
    }
  ;

  descriptor.value = $defineProperty;
  defineProperty(Object, DP, descriptor);

  descriptor.value = $getOwnPropertySymbols;
  defineProperty(Object, GOPS, descriptor);

  descriptor.value = function getOwnPropertyNames(o) {
    return gOPN(o).filter(onlyNonSymbols);
  };
  defineProperty(Object, GOPN, descriptor);

  descriptor.value = function defineProperties(o, descriptors) {
    var symbols = $getOwnPropertySymbols(descriptors);
    if (symbols.length) {
      keys(descriptors).concat(symbols).forEach(function (uid) {
        if (propertyIsEnumerable.call(descriptors, uid)) {
          $defineProperty(o, uid, descriptors[uid]);
        }
      });
    } else {
      $defineProperties(o, descriptors);
    }
    return o;
  };
  defineProperty(Object, DPies, descriptor);

  descriptor.value = propertyIsEnumerable;
  defineProperty(ObjectProto, PIE, descriptor);

  descriptor.value = Symbol;
  defineProperty(G, 'Symbol', descriptor);

  // defining `Symbol.for(key)`
  descriptor.value = function (key) {
    var uid = prefix.concat(prefix, key, random);
    return uid in ObjectProto ? source[uid] : setAndGetSymbol(uid);
  };
  defineProperty(Symbol, 'for', descriptor);

  // defining `Symbol.keyFor(symbol)`
  descriptor.value = function (symbol) {
    if (onlyNonSymbols(symbol))
      throw new TypeError(symbol + ' is not a symbol');
    return hOP.call(source, symbol) ?
      symbol.slice(prefixLength * 2, -random.length) :
      void 0
    ;
  };
  defineProperty(Symbol, 'keyFor', descriptor);

  descriptor.value = function getOwnPropertyDescriptor(o, key) {
    var descriptor = gOPD(o, key);
    if (descriptor && onlySymbols(key)) {
      descriptor.enumerable = propertyIsEnumerable.call(o, key);
    }
    return descriptor;
  };
  defineProperty(Object, GOPD, descriptor);

  descriptor.value = function (proto, descriptors) {
    return arguments.length === 1 ?
      create(proto) :
      createWithSymbols(proto, descriptors);
  };
  defineProperty(Object, 'create', descriptor);

  descriptor.value = function () {
    var str = toString.call(this);
    return (str === '[object String]' && onlySymbols(this)) ? '[object Symbol]' : str;
  };
  defineProperty(ObjectProto, 'toString', descriptor);

  try { // fails in few pre ES 5.1 engines
    setDescriptor = create(
      defineProperty(
        {},
        prefix,
        {
          get: function () {
            return defineProperty(this, prefix, {value: false})[prefix];
          }
        }
      )
    )[prefix] || defineProperty;
  } catch(o_O) {
    setDescriptor = function (o, key, descriptor) {
      var protoDescriptor = gOPD(ObjectProto, key);
      delete ObjectProto[key];
      defineProperty(o, key, descriptor);
      defineProperty(ObjectProto, key, protoDescriptor);
    };
  }

}(Object, 'getOwnPropertySymbols'));

(function (O, S) {
  var
    dP = O.defineProperty,
    ObjectProto = O.prototype,
    toString = ObjectProto.toString,
    toStringTag = 'toStringTag',
    descriptor
  ;
  [
    'iterator',           // A method returning the default iterator for an object. Used by for...of.
    'match',              // A method that matches against a string, also used to determine if an object may be used as a regular expression. Used by String.prototype.match().
    'replace',            // A method that replaces matched substrings of a string. Used by String.prototype.replace().
    'search',             // A method that returns the index within a string that matches the regular expression. Used by String.prototype.search().
    'split',              // A method that splits a string at the indices that match a regular expression. Used by String.prototype.split().
    'hasInstance',        // A method determining if a constructor object recognizes an object as its instance. Used by instanceof.
    'isConcatSpreadable', // A Boolean value indicating if an object should be flattened to its array elements. Used by Array.prototype.concat().
    'unscopables',        // An Array of string values that are property values. These are excluded from the with environment bindings of the associated objects.
    'species',            // A constructor function that is used to create derived objects.
    'toPrimitive',        // A method converting an object to a primitive value.
    toStringTag           // A string value used for the default description of an object. Used by Object.prototype.toString().
  ].forEach(function (name) {
    if (!(name in Symbol)) {
      dP(Symbol, name, {value: Symbol(name)});
      switch (name) {
        case toStringTag:
          descriptor = O.getOwnPropertyDescriptor(ObjectProto, 'toString');
          descriptor.value = function () {
            var
              str = toString.call(this),
              tst = this[Symbol.toStringTag]
            ;
            return typeof tst === 'undefined' ? str : ('[object ' + tst + ']');
          };
          dP(ObjectProto, 'toString', descriptor);
          break;
      }
    }
  });
}(Object, Symbol));

(function (Si, AP, SP) {

  function returnThis() { return this; }

  // make Arrays usable as iterators
  // so that other iterables can copy same logic
  if (!AP[Si]) AP[Si] = function () {
    var
      i = 0,
      self = this,
      iterator = {
        next: function next() {
          var done = self.length <= i;
          return done ?
            {done: done} :
            {done: done, value: self[i++]};
        }
      }
    ;
    iterator[Si] = returnThis;
    return iterator;
  };

  // make Strings usable as iterators
  // to simplify Array.from and for/of like loops
  if (!SP[Si]) SP[Si] = function () {
    var
      fromCodePoint = String.fromCodePoint,
      self = this,
      i = 0,
      length = self.length,
      iterator = {
        next: function next() {
          var
            done = length <= i,
            c = done ? '' : fromCodePoint(self.codePointAt(i))
          ;
          i += c.length;
          return done ?
            {done: done} :
            {done: done, value: c};
        }
      }
    ;
    iterator[Si] = returnThis;
    return iterator;
  };

}(Symbol.iterator, Array.prototype, String.prototype));

module.exports = Object.getOwnPropertySymbols;
/* WEBPACK VAR INJECTION */}.call(exports, __webpack_require__(2)))

/***/ }),
/* 2 */
/***/ (function(module, exports) {

var g;

// This works in non-strict mode
g = (function() {
	return this;
})();

try {
	// This works if eval is allowed (see CSP)
	g = g || Function("return this")() || (1,eval)("this");
} catch(e) {
	// This works if the window reference is available
	if(typeof window === "object")
		g = window;
}

// g can still be undefined, but nothing to do about it...
// We return undefined, instead of nothing here, so it's
// easier to handle this case. if(!global) { ...}

module.exports = g;


/***/ })
/******/ ]);