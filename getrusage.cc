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
#include <nan.h>

using namespace Nan;


NAN_METHOD(GetCPUTime) {
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);

    info.GetReturnValue().Set(New<v8::Number>(
        (double)ru.ru_utime.tv_sec + (double)ru.ru_utime.tv_usec * 1e-6 +
        (double)ru.ru_stime.tv_sec + (double)ru.ru_stime.tv_usec * 1e-6));
}

NAN_METHOD(GetSystemTime) {
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);

    info.GetReturnValue().Set(New<v8::Number>(
        (double)ru.ru_stime.tv_sec + (double)ru.ru_stime.tv_usec * 1e-6));
}

static v8::Handle<v8::Value> timevalToNumber(struct timeval &tim) {
    return New<v8::Number>((double)tim.tv_sec + (double)tim.tv_usec * 1e-6);
}

NAN_METHOD(GetUsage) {
    EscapableHandleScope scope;

    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);

    v8::Local<v8::Object> output = New<v8::Object>();

    #define FIELD(name, conv) \
        Set(output, New<v8::String>(#name).ToLocalChecked(), conv(ru.ru_##name))

    FIELD(utime, timevalToNumber);         /* user time used */
    FIELD(stime, timevalToNumber);         /* system time used */
    FIELD(maxrss, New<v8::Number>);        /* maximum resident set size */
    FIELD(ixrss, New<v8::Number>);         /* integral shared memory size */
    FIELD(idrss, New<v8::Number>);         /* integral unshared data size */
    FIELD(isrss, New<v8::Number>);         /* integral unshared stack size */
    FIELD(minflt, New<v8::Number>);        /* page reclaims */
    FIELD(majflt, New<v8::Number>);        /* page faults */
    FIELD(nswap, New<v8::Number>);         /* swaps */
    FIELD(inblock, New<v8::Number>);       /* block input operations */
    FIELD(oublock, New<v8::Number>);       /* block output operations */
    FIELD(msgsnd, New<v8::Number>);        /* messages sent */
    FIELD(msgrcv, New<v8::Number>);        /* messages received */
    FIELD(nsignals, New<v8::Number>);      /* signals received */
    FIELD(nvcsw, New<v8::Number>);         /* voluntary context switches */
    FIELD(nivcsw, New<v8::Number>);        /* involuntary context switches */

    #undef FIELD

    info.GetReturnValue().Set(scope.Escape(output));
}

NAN_MODULE_INIT(Init) {
    SetMethod(target, "usage", GetUsage);
    SetMethod(target, "getcputime", GetCPUTime);
    SetMethod(target, "getsystemtime", GetSystemTime);
}

NODE_MODULE(getrusage, Init)
