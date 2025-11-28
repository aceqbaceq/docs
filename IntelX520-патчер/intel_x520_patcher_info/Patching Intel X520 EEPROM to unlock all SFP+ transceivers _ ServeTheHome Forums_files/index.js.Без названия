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
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
var _createClass = function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; }();

function _classCallCheck(instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } }

var covers = function () {
    function Covers(_ref) {
        var _this = this;

        var _ref$settings = _ref.settings,
            settings = _ref$settings === undefined ? {} : _ref$settings,
            _ref$init = _ref.init,
            init = _ref$init === undefined ? false : _ref$init,
            _ref$commonVersion = _ref.commonVersion,
            commonVersion = _ref$commonVersion === undefined ? '20180112' : _ref$commonVersion,
            width = _ref.width,
            height = _ref.height;

        _classCallCheck(this, Covers);

        this.init = function () {
            _this.initGet();
            _this.initSet();
        };

        this.initGet = function () {
            _this.rootEle = window.document.querySelector(_this.settings.coverSelector);
            _this.saveEle = window.document.querySelector(_this.settings.saveSelector);
            _this.cancelEle = window.document.querySelector(_this.settings.cancelSelector);
            _this.positionEle = window.document.querySelector(_this.settings.positionSelector);

            if (_this.rootEle !== null) {
                _this.cropY = parseFloat(_this.rootEle.style.backgroundPositionY) || 50;
            }
        };

        this.initSet = function () {
            _this.running = true;
            window.XF.Click.register('cover-position', _this.positionCoverClick);
            if (window.location.search.indexOf('th_coversInit=1') >= 0) {
                var oldSearch = window.location.search;
                var splitSearch = oldSearch.replace('?', '').split('&');
                var newSearch = '';
                for (var i = 0, len = splitSearch.length; i < len; i++) {
                    var currentSearch = splitSearch[i];
                    if (currentSearch !== 'th_coversInit=1') {
                        if (newSearch !== '') {
                            newSearch += '&';
                        }
                        newSearch += currentSearch;
                    }
                }
                if (newSearch !== '') {
                    newSearch = '?' + newSearch;
                }

                window.history.replaceState({}, '', window.location.href.replace(oldSearch, newSearch));
                _this.initDrag();
            }
        };

        this.enableSave = function () {
            if (_this.changeMade === false) {
                _this.saveEle.addEventListener('click', _this.submit);
                _this.saveEle.classList.remove('is-disabled');
                _this.changeMade = true;
            }
        };

        this.enableCancel = function () {
            _this.cancelEle.addEventListener('click', _this.cancel);
        };

        this.positionCoverClick = window.XF.Click.newHandler({
            eventNameSpace: 'XFClickCover',
            init: function init() {},
            click: function click() {
                return _this.initDrag();
            }
        });

        this.initDrag = function () {
            if (_this.rootEle !== null) {
                _this.enableCancel();
                window.XF.MenuWatcher.closeAll();
                window.document.querySelector('html').classList.add(_this.settings.activeClass);
                _this.rootEle.classList.add(_this.settings.activeClass);
                _this.rootEle.addEventListener('mousedown', _this.dragStart);
                window.document.addEventListener('mousemove', _this.drag);
                window.document.addEventListener('mouseup', _this.dragEnd);
                if (window.XF.Feature.has('touchevents')) {
                    _this.rootEle.addEventListener('touchstart', _this.dragStart, { passive: false });
                    window.document.addEventListener('touchmove', _this.drag, { passive: false });
                    window.document.addEventListener('touchend', _this.dragEnd, { passive: false });
                    window.document.addEventListener('touchcancel', _this.dragEnd, { passive: false });
                }
            }
            return false;
        };

        this.removeDrag = function () {
            window.document.querySelector('html').classList.remove(_this.settings.activeClass);
            _this.rootEle.classList.remove(_this.settings.activeClass);
            _this.rootEle.removeEventListener('mousedown', _this.dragStart);
            window.document.removeEventListener('mousemove', _this.drag);
            window.document.removeEventListener('mouseup', _this.dragEnd);
            if (window.XF.Feature.has('touchevents')) {
                _this.rootEle.removeEventListener('touchstart', _this.dragStart);
                window.document.removeEventListener('touchmove', _this.drag);
                window.document.removeEventListener('touchend', _this.dragEnd);
                window.document.removeEventListener('touchcancel', _this.dragEnd);
            }
        };

        this.getYPos = function (e) {
            var root = window.XF.Feature.has('touchevents') && e.touches.length > 0 ? e.touches[0] : e;

            return root.clientY || root.pageY || root.y;
        };

        this.dragStart = function (e) {
            _this.paneWidth = _this.rootEle.offsetWidth;
            _this.paneHeight = _this.rootEle.offsetHeight;
            _this.dragStartY = _this.getYPos(e);
        };

        this.drag = function (e) {
            var dragStartY = _this.dragStartY;


            if (dragStartY > -1) {
                var currentY = _this.getYPos(e);
                var dragDistance = dragStartY - currentY;
                var percent = _this.findImgPercent(dragDistance);
                _this.recentPercent = percent;

                _this.setPosition(percent);

                if (window.XF.Feature.has('touchevents')) {
                    e.preventDefault();
                }
            }
        };

        this.dragEnd = function () {
            if (_this.dragStartY !== -1) {
                _this.dragStartY = -1;
                _this.cropY = _this.recentPercent;
                _this.enableSave();
            }
        };

        this.findImgPercent = function (dragDistance) {
            var imgWidth = _this.imgWidth,
                imgHeight = _this.imgHeight,
                paneWidth = _this.paneWidth,
                paneHeight = _this.paneHeight,
                cropY = _this.cropY;


            var imgRatio = imgWidth / imgHeight;
            var paneRatio = paneWidth / paneHeight;
            if (imgRatio > paneRatio) {
                // return 50;
            }
            var currentHeight = imgHeight * (paneWidth / imgWidth);
            var percent = dragDistance / currentHeight * 100 + cropY;

            if (percent > 100) {
                return 100;
            }
            if (percent < 0) {
                return 0;
            }

            return percent;
        };

        this.setPosition = function (val) {
            _this.rootEle.style.backgroundPositionY = val + '%';
        };

        this.submit = function () {
            _this.removeDrag();
            window.XF.ajax('POST', _this.settings.url, {
                cropY: _this.cropY
            });
        };

        this.cancel = function () {
            _this.removeDrag();
        };

        this.running = false;
        this.settings = Object.assign({
            coverSelector: '.cover-hasImage',
            activeClass: 'cover--positioning',
            saveSelector: '.cover__save',
            cancelSelector: '.cover__cancel',
            positionSelector: '.cover__positionTrigger'
        }, settings);

        this.commonVersion = commonVersion;
        this.common = window.themehouse.common[commonVersion];
        this.rootEle = null;
        this.saveEle = null;
        this.cancelEle = null;
        this.positionEle = null;
        this.cropY = 50;
        this.dragStartY = -1;
        this.imgWidth = width;
        this.imgHeight = height;
        this.paneWidth = 0;
        this.paneHeight = 0;
        this.recentPercent = 50;
        this.changeMade = false;

        if (init) {
            this.init();
        }
    }

    _createClass(Covers, [{
        key: 'register',
        value: function register() {
            this.common.register({
                phase: 'initGet',
                addon: 'TH_Covers',
                func: this.initGet,
                order: 10
            });
            this.common.register({
                phase: 'initSet',
                addon: 'TH_Covers',
                func: this.initSet,
                order: 10
            });
        }
    }]);

    return Covers;
}();

if (typeof window.themehouse === 'undefined') {
    window.themehouse = {};
}

window.themehouse.covers = {
    covers: covers
};

/* harmony default export */ __webpack_exports__["default"] = (covers);

/***/ })
/******/ ]);