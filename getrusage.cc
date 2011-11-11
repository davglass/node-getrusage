/*
*/

#include <v8.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ev.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <node.h>

using namespace v8;

double getcputime(void) {
    struct timeval tim;
    struct rusage ru;
    
    getrusage(RUSAGE_SELF, &ru);
    
    tim = ru.ru_utime;
    double t=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
    tim=ru.ru_stime;        
    t+=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;        
    return t;
} 

double getusertime(void) {
    struct timeval tim;
    struct rusage ru;
    
    getrusage(RUSAGE_SELF, &ru);
    
    tim = ru.ru_stime;
    double t=(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
    return t;
} 


Handle<Value> GetCPUTime(const Arguments& args) {
    return Number::New(getcputime());
}

Handle<Value> GetUserTime(const Arguments& args) {
    return Number::New(getusertime());
}

/**
* http://rabbit.eng.miami.edu/info/functions/time.html#getrusage
* Wrapper around getrusage
*/

Handle<Value> GetUsage(const Arguments& args) {
    HandleScope scope;

    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    
    Local<Object> info = Object::New();

    //CPU Time
    static Persistent<String> c_time;
    double cpu_time;
    c_time = NODE_PSYMBOL("cputime");
    cpu_time = getcputime();
    //printf("getCPUTime: %f\n", cpu_time);
    info->Set(c_time, Number::New(cpu_time));

    //User Time
    static Persistent<String> u_time;
    double user_time;
    u_time = NODE_PSYMBOL("usertime");
    user_time = getusertime();
    //printf("getUSERTime: %f\n", user_time);
    info->Set(u_time, Number::New(user_time));

    //max resident set size
    static Persistent<String> max_rss;
    max_rss = NODE_PSYMBOL("maxrss");
    info->Set(max_rss, Number::New(ru.ru_maxrss));

    //memory size for code
    static Persistent<String> ix_rss;
    ix_rss = NODE_PSYMBOL("ixrss");
    info->Set(ix_rss, Number::New(ru.ru_ixrss));

    //memory size for statics, globals, and new/malloc
    static Persistent<String> id_rss;
    id_rss = NODE_PSYMBOL("idrss");
    info->Set(id_rss, Number::New(ru.ru_idrss));

    //stack size (memory used by local variables)
    static Persistent<String> is_rss;
    is_rss = NODE_PSYMBOL("isrss");
    info->Set(is_rss, Number::New(ru.ru_isrss));

    //minor page faults: "page reclaims"
    static Persistent<String> minflt;
    minflt = NODE_PSYMBOL("minflt");
    info->Set(minflt, Number::New(ru.ru_minflt));

    //major page faults: swaps in
    static Persistent<String> majflt;
    majflt = NODE_PSYMBOL("majflt");
    info->Set(majflt, Number::New(ru.ru_majflt));

    //page swaps
    static Persistent<String> nswap;
    nswap = NODE_PSYMBOL("nswap");
    info->Set(nswap, Number::New(ru.ru_nswap));

    //block input operations, disc etc
    static Persistent<String> inblock;
    inblock = NODE_PSYMBOL("inblock");
    info->Set(inblock, Number::New(ru.ru_inblock));

    //block output operations, disc, etc
    static Persistent<String> oublock;
    oublock = NODE_PSYMBOL("oublock");
    info->Set(oublock, Number::New(ru.ru_oublock));

    //messages sent
    static Persistent<String> msgsnd;
    msgsnd = NODE_PSYMBOL("msgsnd");
    info->Set(msgsnd, Number::New(ru.ru_msgsnd));

    //messages received
    static Persistent<String> msgrcv;
    msgrcv = NODE_PSYMBOL("msgrcv");
    info->Set(msgrcv, Number::New(ru.ru_msgrcv));

    //signals received
    static Persistent<String> nsignals;
    nsignals = NODE_PSYMBOL("nsignals");
    info->Set(nsignals, Number::New(ru.ru_nsignals));

    //voluntary context switches (process loses CPU)
    static Persistent<String> nvcsw;
    nvcsw = NODE_PSYMBOL("nvcsw");
    info->Set(nvcsw, Number::New(ru.ru_nvcsw));

    //involuntary context switches (process loses CPU)
    static Persistent<String> nivcsw;
    nivcsw = NODE_PSYMBOL("nivcsw");
    info->Set(nivcsw, Number::New(ru.ru_nivcsw));

    return scope.Close(info);
    
}

const char* ToCString(const v8::String::Utf8Value& value) {
	return *value ? *value : "<string conversion failed>";
}

extern "C" void init(Handle<Object> target) {
	HandleScope scope;
	
	target->Set(String::New("usage"), FunctionTemplate::New(GetUsage)->GetFunction());
	target->Set(String::New("getcputime"), FunctionTemplate::New(GetCPUTime)->GetFunction());
	target->Set(String::New("getusertime"), FunctionTemplate::New(GetUserTime)->GetFunction());
}

