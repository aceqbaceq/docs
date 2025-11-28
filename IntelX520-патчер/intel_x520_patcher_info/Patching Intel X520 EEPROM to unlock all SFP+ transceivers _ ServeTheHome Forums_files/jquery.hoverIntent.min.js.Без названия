/*
 hoverIntent v1.9.0 // 2017.09.01 // jQuery v1.7.0+
 http://briancherne.github.io/jquery-hoverIntent/

 You may use hoverIntent under the terms of the MIT license. Basically that
 means you are free to use hoverIntent as long as this header is left intact.
 Copyright 2007-2017 Brian Cherne
*/
(function(c){"function"===typeof define&&define.amd?define(["jquery"],c):jQuery&&!jQuery.fn.hoverIntent&&c(jQuery)})(function(c){var n={interval:100,sensitivity:6,timeout:0},p=0,d,k,l=function(a){d=a.pageX;k=a.pageY},m=function(a,c,b,g){if(Math.sqrt((b.pX-d)*(b.pX-d)+(b.pY-k)*(b.pY-k))<g.sensitivity)return c.off(b.event,l),delete b.timeoutId,b.isActive=!0,a.pageX=d,a.pageY=k,delete b.pX,delete b.pY,g.over.apply(c[0],[a]);b.pX=d;b.pY=k;b.timeoutId=setTimeout(function(){m(a,c,b,g)},g.interval)};c.fn.hoverIntent=
function(a,d,b){var g=p++,f=c.extend({},n);c.isPlainObject(a)?(f=c.extend(f,a),c.isFunction(f.out)||(f.out=f.over)):f=c.isFunction(d)?c.extend(f,{over:a,out:d,selector:b}):c.extend(f,{over:a,out:a,selector:d});a=function(a){var b=c.extend({},a),d=c(this),h=d.data("hoverIntent");h||d.data("hoverIntent",h={});var e=h[g];e||(h[g]=e={id:g});e.timeoutId&&(e.timeoutId=clearTimeout(e.timeoutId));h=e.event="mousemove.hoverIntent.hoverIntent"+g;"mouseenter"===a.type?e.isActive||(e.pX=b.pageX,e.pY=b.pageY,
d.off(h,l).on(h,l),e.timeoutId=setTimeout(function(){m(b,d,e,f)},f.interval)):e.isActive&&(d.off(h,l),e.timeoutId=setTimeout(function(){var a=e,c=f.out;delete d.data("hoverIntent")[a.id];c.apply(d[0],[b])},f.timeout))};return this.on({"mouseenter.hoverIntent":a,"mouseleave.hoverIntent":a},f.selector)}});