#pragma once
#ifndef BE_PERF_VERSION_HPP_
#define BE_PERF_VERSION_HPP_

#include <be/core/macros.hpp>

#define BE_PERF_VERSION_MAJOR 0
#define BE_PERF_VERSION_MINOR 1
#define BE_PERF_VERSION_REV 6

/*!! include('common/version', 'be::perf') !! 6 */
/* ################# !! GENERATED CODE -- DO NOT MODIFY !! ################# */
#define BE_PERF_VERSION (BE_PERF_VERSION_MAJOR * 100000 + BE_PERF_VERSION_MINOR * 1000 + BE_PERF_VERSION_REV)
#define BE_PERF_VERSION_STRING "be::perf " BE_STRINGIFY(BE_PERF_VERSION_MAJOR) "." BE_STRINGIFY(BE_PERF_VERSION_MINOR) "." BE_STRINGIFY(BE_PERF_VERSION_REV)

/* ######################### END OF GENERATED CODE ######################### */

#endif
