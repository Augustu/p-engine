#ifndef PENGINE_COMMON_H
#define PENGINE_COMMON_H

#ifdef ERROR
#undef ERROR
#endif

#include <glog/logging.h>

using namespace google;

namespace pengine
{

    static void InitLog(const char* argv0)
    {
        FLAGS_log_dir = "./";
        FLAGS_logtostdout = true;

        InitGoogleLogging(argv0);
    }

}

#endif