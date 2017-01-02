#include "pch.hpp"
#include "service_stats.hpp"
#include <be/core/service_helpers.hpp>
#include <be/core/service_log.hpp>

namespace be {

///////////////////////////////////////////////////////////////////////////////
void ServiceInitDependencies<perf::Stats>::operator()() {
   default_log();
}

///////////////////////////////////////////////////////////////////////////////
perf::Stats& perf_stats() {
   return service<perf::Stats>();
}

} // be
