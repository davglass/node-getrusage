var vows = require('vows'),
    assert = require('assert'),
    proc = require('../'),
    waste = function() {
        for (var i =0; i < 900000; i++) {
            //Nothing here
        }
    };

vows.describe('Test Loading and Bindings').addBatch({
    'Should be loaded': {
        topic: function () {
            return proc
        },
        'should have 3 methods': function (topic) {
            assert.isFunction(topic.usage);
            assert.isFunction(topic.getcputime);
            assert.isFunction(topic.getsystemtime);
        },
        'proc.usage() should return an object': function(topic) {
            var usage = topic.usage();
            var keys = [ 'utime','stime','maxrss','ixrss','idrss','isrss','minflt','majflt','nswap','inblock','oublock','msgsnd','msgrcv','nsignals','nvcsw','nivcsw'];
            assert.isObject(usage);
            assert.deepEqual(Object.keys(usage), keys);
        },
        'proc.getcputime() should return a number': function(topic) {
            waste();
            var time = topic.getcputime();
            assert.isNumber(time);
            assert.isTrue((time > 0));
        },
        'proc.getsystemtime() should return a number': function(topic) {
            waste();
            var time = topic.getsystemtime();
            assert.isNumber(time);
            assert.isTrue((time > 0));
        }
    }
}).export(module);
