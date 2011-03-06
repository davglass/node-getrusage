## getrusage for Node

Simple wrapper around the unix method `getrusage` for reporting CPU Time and other process information


## Installation

    npm install getrusage

Or: 
    
    git clone git://github.com/davglass/node-getrusage.git
    cd node-getrusage
    make

## Usage

    var proc = require('getrusage');
    console.log(proc.usage());
    console.log(proc.getcputime());
    console.log(proc.getusertime());
