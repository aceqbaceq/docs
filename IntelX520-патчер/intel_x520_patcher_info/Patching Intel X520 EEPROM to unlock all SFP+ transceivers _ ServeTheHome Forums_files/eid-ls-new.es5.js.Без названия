function _createForOfIteratorHelper(t, r) {
    var n = "undefined" != typeof Symbol && t[Symbol.iterator] || t["@@iterator"];
    if (!n) {
        if (Array.isArray(t) || (n = _unsupportedIterableToArray(t)) || r && t && "number" == typeof t.length) {
            n && (t = n);
            var e = 0, o = function t() {
            };
            return {
                s: o, n: function r() {
                    return e >= t.length ? {done: !0} : {done: !1, value: t[e++]}
                }, e: function t(r) {
                    throw r
                }, f: o
            }
        }
        throw new TypeError("Invalid attempt to iterate non-iterable instance.\nIn order to be iterable, non-array objects must have a [Symbol.iterator]() method.")
    }
    var a = !0, u = !1, c;
    return {
        s: function r() {
            n = n.call(t)
        }, n: function t() {
            var r = n.next();
            return a = r.done, r
        }, e: function t(r) {
            u = !0, c = r
        }, f: function t() {
            try {
                a || null == n.return || n.return()
            } finally {
                if (u) throw c
            }
        }
    }
}

function _unsupportedIterableToArray(t, r) {
    if (t) {
        if ("string" == typeof t) return _arrayLikeToArray(t, r);
        var n = Object.prototype.toString.call(t).slice(8, -1);
        return "Object" === n && t.constructor && (n = t.constructor.name), "Map" === n || "Set" === n ? Array.from(t) : "Arguments" === n || /^(?:Ui|I)nt(?:8|16|32)(?:Clamped)?Array$/.test(n) ? _arrayLikeToArray(t, r) : void 0
    }
}

function _arrayLikeToArray(t, r) {
    (null == r || r > t.length) && (r = t.length);
    for (var n = 0, e = new Array(r); n < r; n++) e[n] = t[n];
    return e
}

!function (t, r) {
    try {
        var n = function r(n) {
                if (!n || "string" != typeof n) return !1;
                var o = e(n);
                if (!V.includes(t.btoa(o))) return !1;
                try {
                    if (!I.test(n)) return !1
                } catch (t) {
                    return !1
                }
                var u = w("eid:rbox:common-eid-keywords");
                if (a(u, n)) return !1;
                var c = L("eid:tfa:common-eid-keywords", "");
                return !a(c, n)
            }, e = function t(r) {
                return r.slice(r.indexOf("@") + 1)
            }, o = function t() {
                if (null !== _) return _;
                try {
                    (_ = window.localStorage).setItem("~~~", "!"), _.removeItem("~~~")
                } catch (t) {
                    _ = null
                }
                return _
            }, a = function t(r, n) {
                if (!n || !r || "string" != typeof r) return !1;
                try {
                    var e;
                    return r.split(",").some(function (t) {
                        return n.includes(t)
                    })
                } catch (t) {
                    return !1
                }
            }, u = function r() {
                return t._trcIsUTactive ? U : null
            }, c = function r() {
                t._trcIsUTactive && (U = [])
            }, i = function t() {
                if (!o()) return [];
                try {
                    return Object.keys(_)
                } catch (t) {
                    return []
                }
            }, l = function t(r) {
                if (r && "string" == typeof r) try {
                    return r.length > 1e4 ? null : r.match(Q)
                } catch (t) {
                    return null
                }
                return null
            }, f = function t() {
                try {
                    var r, n = _createForOfIteratorHelper(i()), e;
                    try {
                        for (n.s(); !(e = n.n()).done;) {
                            var o = e.value;
                            try {
                                var a = _[o];
                                if ("string" == typeof a) {
                                    var u = l(a);
                                    u && u.forEach(function (t) {
                                        b(t.toLowerCase())
                                    })
                                }
                            } catch (t) {
                                continue
                            }
                        }
                    } catch (t) {
                        n.e(t)
                    } finally {
                        n.f()
                    }
                } catch (t) {
                }
            }, d = function t(r) {
                return !U.includes(r) && (U.push(r), !0)
            }, b = function t(r) {
                if (n(r)) {
                    g(r, function (t) {
                        if (d(t)) {
                            var n = m(r);
                            p(t, n)
                        }
                    });
                    try {
                        var e = r.replace(T, "");
                        r !== e && g(e, function (t) {
                            if (d(t)) {
                                var r = m(e);
                                p(t, r)
                            }
                        })
                    } catch (t) {
                    }
                }
            }, m = function r(n) {
                var e;
                if ((L("eid:send-eid-encoded", !0) || w("eid:send-eid-encoded")) && s() && t.btoa) try {
                    return t.btoa(n)
                } catch (t) {
                    return null
                }
                return null
            }, s = function t() {
                return 4444 === Math.floor(1e5 * Math.random())
            }, y = function t() {
                try {
                    return _ && _["taboola global:user-id"]
                } catch (t) {
                    return null
                }
            }, v = function r() {
                var n = t.TFASC && t.TFASC.tfaUserId && "function" == typeof t.TFASC.tfaUserId.getUserId ? t.TFASC.tfaUserId.getUserId() : null,
                    e = t.TRC.pageManager && "function" == typeof t.TRC.pageManager.getUserId ? t.TRC.pageManager.getUserId() : null,
                    o = y();
                return n || e || o
            }, p = function t(r, n) {
                var e = v();
                if (r && e) {
                    var o = [];
                    W("uils", e, o), W(Y, Z(r), o), n && W(A, n, o);
                    var a = new Image, u;
                    return (L("tfa:add-referrer-policy-when-firing-pixel", !0) || w("rbox:add-referrer-policy-when-firing-pixel")) && (a.referrerPolicy = "no-referrer-when-downgrade"), a.src = "".concat(C(), "//trc.taboola.com/sg/tfa-eid/1/um/?").concat(o.join("&")), a
                }
            }, Z = function t(r) {
                try {
                    for (var n = r.slice(0, j) + S + r.slice(j), e = "", o = 0; o < n.length; o++) e += String.fromCharCode(n.charCodeAt(o) + N);
                    return e
                } catch (t) {
                    return r
                }
            }, h = function t(r) {
                return Array.from(new Uint8Array(r), function (t) {
                    return t.toString(16).padStart(2, "0")
                }).join("")
            }, g = function t(r, n) {
                try {
                    var e = (new TextEncoder).encode(r), o = R.subtle.digest("SHA-256", e);
                    o instanceof Promise ? o.then(h).then(n).catch(function () {
                    }) : o instanceof CryptoOperation && n(h(o.result))
                } catch (t) {
                }
            }, W = function t(r, n, e) {
                if (e && n && r) {
                    var o = encodeURIComponent(r), a = encodeURIComponent(n);
                    e.push("".concat(o, "=").concat(a))
                }
            }, L = function r(n, e) {
                return t._tfa && t._tfa.config && "function" == typeof t._tfa.config.safeGet ? t._tfa.config.safeGet(n, e) : null
            }, w = function t(r) {
                var n;
                return (TRCImpl ? TRCImpl.global : {})[r]
            }, C = function t() {
                return G
            }, F = function n() {
                X || "function" != typeof TextEncoder ? X = !0 : ("complete" === r.readyState ? f() : t.addEventListener("load", function () {
                    return f()
                }), X = !0)
            }, Y = "eflp", A = "deit", G = "https:", Q = /[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}/gi,
            I = /^(([^<>()\[\]\\.,;:\s@"]+(\.[^<>()\[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/,
            S = "RUl2QU54VNERVSF", j = 17, N = 5, T = /\+(.*?)(?=@)/,
            V = ["Z21haWwuY29t", "b3V0bG9vay5jb20=", "aG90bWFpbC5jb20=", "bGl2ZS5jb20=", "bXNuLmNvbQ==", "aWNsb3VkLmNvbQ==", "bWUuY29t", "bWFjLmNvbQ==", "eWFob28uY29t", "eW1haWwuY29t", "cm9ja2V0bWFpbC5jb20=", "YW9sLmNvbQ==", "em9oby5jb20=", "Y29tY2FzdC5uZXQ=", "dmVyaXpvbi5uZXQ=", "YmVsbC5uZXQ=", "YXR0Lm5ldA==", "c2JjZ2xvYmFsLm5ldA==", "cm9nZXJzLmNvbQ==", "aHVzaG1haWwuY29t", "MTYzLmNvbQ==", "MTI2LmNvbQ==", "c2luYS5jb20=", "YWxpeXVuLmNvbQ==", "bWFpbC5ydQ==", "eWFuZGV4LnJ1", "eWFuZGV4LmNvbQ==", "Z214LmNvbQ==", "Z214LmRl", "Z214Lm5ldA==", "d2ViLmRl", "b3JhbmdlLmZy", "bGFwb3N0ZS5uZXQ=", "bGliZXJvLml0", "dmlyZ2lsaW8uaXQ=", "c2V6bmFtLmN6", "d3AucGw=", "b25ldC5wbA==", "bWFpbGJveC5vcmc=", "dHV0YW5vdGEuY29t", "cG9zdGVvLmRl", "dGVsZW5ldC5iZQ==", "Y2VudHJ1bS5jeg==", "ZW1haWwuY3o=", "dC1vbmxpbmUuZGU=", "ZnJlZW5ldC5kZQ==", "MWFuZDEuY29t", "aW9ub3MuY29t", "bWFpbC5kZQ==", "ZnJlZS5mcg==", "c2ZyLmZy", "dGltLml0", "dGFsa3RhbGsubmV0", "YnRpbnRlcm5ldC5jb20=", "c2t5LmNvbQ==", "d2FsbGEuY28uaWw=", "eWFob28uY28uanA=", "bmF2ZXIuY29t", "ZGF1bS5uZXQ=", "ZG9jb21vLm5lLmpw", "cHJvdG9uLm1l", "cHJvdG9ubWFpbC5jb20=", "ZmFzdG1haWwuY29t", "ZmFzdG1haWwuZm0=", "bWFpbC5jb20=", "dW9sLmNvbS5icg==", "ZmliZXJ0ZWwuY29tLmFy", "dGVsa29tc2EubmV0", "c3RjLmNvbS5zYQ==", "YmlncG9uZC5jb20=", "b3B0dXNuZXQuY29tLmF1", "eHRyYS5jby5ueg==", "YWZyaWNhb25saW5lLmNvLmtl", "ZXRoaW9uZXQuZXQ=", "cmVkaWZmbWFpbC5jb20="],
            R = window.crypto || window.msCrypto, X = !1, U = [], _ = null;
        F()
    } catch (t) {
        __trcError("Error running eidls - tag loader", t)
    }
}(window, document);