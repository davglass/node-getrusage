/*
*/

#include <v8.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <node.h>

using namespace v8;


Handle<Value> GetCPUTime(const Arguments& args) {
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);

    return Number::New(
        (double)ru.ru_utime.tv_sec + (double)ru.ru_utime.tv_usec * 1e-6 +
        (double)ru.ru_stime.tv_sec + (double)ru.ru_stime.tv_usec * 1e-6);
}

Handle<Value> GetSystemTime(const Arguments& args) {
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);

    return Number::New(
        (double)ru.ru_stime.tv_sec + (double)ru.ru_stime.tv_usec * 1e-6);
}

static Handle<Value> timevalToNumber(struct timeval &tim) {
  return Number::New((double)tim.tv_sec + (double)tim.tv_usec * 1e-6);
}

Handle<Value> GetUsage(const Arguments& args) {
    HandleScope scope;

    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);

    Local<Object> info = Object::New();

    #define FIELD(name, conv) \
        info->Set(String::NewSymbol(#name), conv(ru.ru_##name))

    FIELD(utime, timevalToNumber);     /* user time used */
    FIELD(stime, timevalToNumber);     /* system time used */
    FIELD(maxrss, Number::New);        /* maximum resident set size */
    FIELD(ixrss, Number::New);         /* integral shared memory size */
    FIELD(idrss, Number::New);         /* integral unshared data size */
    FIELD(isrss, Number::New);         /* integral unshared stack size */
    FIELD(minflt, Number::New);        /* page reclaims */
    FIELD(majflt, Number::New);        /* page faults */
    FIELD(nswap, Number::New);         /* swaps */
    FIELD(inblock, Number::New);       /* block input operations */
    FIELD(oublock, Number::New);       /* block output operations */
    FIELD(msgsnd, Number::New);        /* messages sent */
    FIELD(msgrcv, Number::New);        /* messages received */
    FIELD(nsignals, Number::New);      /* signals received */
    FIELD(nvcsw, Number::New);         /* voluntary context switches */
    FIELD(nivcsw, Number::New);        /* involuntary context switches */

    #undef FIELD

    return scope.Close(info);
}

extern "C" void init(Handle<Object> target) {
    HandleScope scope;

    target->Set(String::New("usage"), FunctionTemplate::New(GetUsage)->GetFunction());
    target->Set(String::New("getcputime"), FunctionTemplate::New(GetCPUTime)->GetFunction());
    target->Set(String::New("getsystemtime"), FunctionTemplate::New(GetSystemTime)->GetFunction());
}

NODE_MODULE(getrusage, init)
