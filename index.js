'use strict'

const binding = require('node-gyp-build')(__dirname)
module.exports.promise = function () {
  const wrap = new binding.PromiseWrap()
  const promise = wrap.promise

  promise.resolve = wrap.resolve.bind(wrap)
  promise.reject = wrap.reject.bind(wrap)

  return promise
}
