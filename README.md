## getrusage for Node

Simple wrapper around the unix method `getrusage` for reporting CPU Time and other process information


## Installation

    npm install getrusage

Or:

    git clone git://github.com/davglass/node-getrusage.git
    cd node-getrusage
    npm install

## Usage

    var proc = require('getrusage');
    console.log(proc.usage());          # Run "man getrusage" for fields.
    console.log(proc.getcputime());     # User time + system time.
    console.log(proc.getsystemtime());  # System time.

## Tests

    npm install && npm test


## Build Status

[![Build Status](https://secure.travis-ci.org/davglass/node-getrusage.png?branch=master)](http://travis-ci.org/davglass/node-getrusage)
