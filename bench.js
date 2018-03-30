'use strict'

const bench = require('nanobench')
const make = require('.')
const N = 1000000

bench(`new Promise ${N} times`, function (b) {
  var i = 0

  next()

  function next () {
    if (++i === N) {
      b.end()
      return
    }

    new Promise(function (resolve) {
      resolve(42)
    }).then(next)
  }
})

bench(`make.promise ${N} times`, function (b) {
  var i = 0

  next()

  function next () {
    if (++i === N) {
      b.end()
      return
    }

    const p = make.promise()
    p.resolve(42)
    p.then(next)
  }
})
