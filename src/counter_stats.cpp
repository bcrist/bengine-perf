#include "pch.hpp"
#include "counter_stats.hpp"

namespace be::perf {

///////////////////////////////////////////////////////////////////////////////
CounterStat& CounterStats::operator[](Id id) {
   map::iterator it = map_.find(id);
   if (it == map_.end()) {
      std::pair<map::iterator, bool> res = map_.emplace(id, CounterStat(stats_, id, S(id)));
      it = res.first;
   }

   return it->second;
}

///////////////////////////////////////////////////////////////////////////////
CounterStat& CounterStats::operator[](const S& name) {
   Id id(name);
   map::iterator it = map_.find(id);
   if (it == map_.end()) {
      std::pair<map::iterator, bool> res = map_.emplace(id, CounterStat(stats_, id, name));
      it = res.first;
   }

   return it->second;
}

///////////////////////////////////////////////////////////////////////////////
void CounterStats::clear() {
   map_.clear();
}

///////////////////////////////////////////////////////////////////////////////
CounterStats::CounterStats(Stats & stats)
   : stats_(stats)
{ }

} // be::perf
