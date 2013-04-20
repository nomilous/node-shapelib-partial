#!/usr/bin/env coffee

fun = require './build/Release/function'


console.log fun.multiply 9.9


func = fun.function()
console.log func 9.9



fun.callback 9.9, (result) -> 

    console.log result




obj = require './build/Release/object'

console.log obj 'value1', 'value2'



Class = require('./build/Release/class').MyClass

c = new Class 99

console.log c.increment()
console.log c.increment()
console.log c.increment()
