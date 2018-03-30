'use strict'

const { test } = require('tap')
const make = require('.')

test('resolve', async function (t) {
  const promise = make.promise()

  setImmediate(() => {
    promise.resolve(42)
  })

  const res = await promise
  t.equal(res, 42)
})

test('reject', async function (t) {
  const promise = make.promise()

  setImmediate(() => {
    promise.reject(new Error('kaboom'))
  })

  try {
    await promise
  } catch (err) {
    t.equal(err.message, 'kaboom')
  }
})

test('resolve sync', async function (t) {
  const promise = make.promise()
  promise.resolve(42)

  const res = await promise
  t.equal(res, 42)
})

test('reject sync', function (t) {
  t.plan(1)

  const promise = make.promise()
  promise.catch(function (err) {
    t.equal(err.message, 'kaboom')
  })
  promise.reject(new Error('kaboom'))
})
