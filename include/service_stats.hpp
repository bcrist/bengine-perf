#pragma once
#ifndef BE_UTIL_SERVICE_PERF_STATS_HPP_
#define BE_UTIL_SERVICE_PERF_STATS_HPP_

#include <be/core/service.hpp>
#include "stats.hpp"

namespace be {

///////////////////////////////////////////////////////////////////////////////
template <>
struct SuppressUndefinedService<perf::Stats> : True { };

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceTraits<perf::Stats> : ServiceTraits<> {
   using lazy_ids = yes;
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceName<perf::Stats> {
   const char* operator()() {
      return "perf::Stats";
   }
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceInitDependencies<perf::Stats> {
   void operator()();
};

///////////////////////////////////////////////////////////////////////////////
template <>
struct ServiceCleanup<perf::Stats> {
   void operator()(std::unique_ptr<perf::Stats>& service) {
      service.reset();
   }
};

///////////////////////////////////////////////////////////////////////////////
perf::Stats& perf_stats();

} // be

#endif
