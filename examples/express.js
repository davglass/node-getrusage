#!/usr/bin/env node

var proc = require('../build/default/getrusage');
var fs = require('fs');
var app = require('express').createServer();

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

app.listen();

setInterval(function() {
    console.log(proc.usage());
}, 1000);

