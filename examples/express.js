#!/usr/bin/env node

var proc = require('getrusage');
var fs = require('fs');
var count = 0;

var timer = setInterval(function() {
    console.log('Starting..');
    for (var i = 0; i < 5000; i++) {
        fs.readFile('/etc/passwd', encoding='utf8');
    }
    count++;
    if (count === 10) {
        console.log('STOPPING');
        clearInterval(timer);
    }
}, 3000);

setInterval(function() {
    console.log(proc.usage());
}, 1000);

