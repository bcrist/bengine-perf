#include "pch.hpp"
#include "stats.hpp"

namespace be {
namespace perf {

///////////////////////////////////////////////////////////////////////////////
Stats::Stats()
   : counters(*this),
     timers(*this),
     events(*this)
{ }

///////////////////////////////////////////////////////////////////////////////
void Stats::clear() {
   counters.clear();
   timers.clear();
   events.clear();
}

} // be::perf
} // be
