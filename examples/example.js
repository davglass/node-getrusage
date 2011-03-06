#!/usr/bin/env node

var proc = require('../build/default/getrusage');
var util = require('util');



for (var i = 0; i < 50000; i++) {
    util.print('.');
}

process.on('exit', function() {
    console.log('');
    console.log(proc.usage());
    console.log('CPU Time: ', proc.getcputime());
    console.log('User Time: ', proc.getusertime());
});
