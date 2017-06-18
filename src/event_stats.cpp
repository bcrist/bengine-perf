#include "pch.hpp"
#include "event_stats.hpp"

namespace be::perf {

///////////////////////////////////////////////////////////////////////////////
EventStat& EventStats::operator[](Id id) {
   map::iterator it = map_.find(id);
   if (it == map_.end()) {
      std::pair<map::iterator, bool> res = map_.emplace(id, EventStat(stats_, id, S(id)));
      it = res.first;
   }

   return it->second;
}

///////////////////////////////////////////////////////////////////////////////
EventStat& EventStats::operator[](const S& name) {
   Id id(name);
   map::iterator it = map_.find(id);
   if (it == map_.end()) {
      std::pair<map::iterator, bool> res = map_.emplace(id, EventStat(stats_, id, name));
      it = res.first;
   }

   return it->second;
}

///////////////////////////////////////////////////////////////////////////////
void EventStats::clear() {
   map_.clear();
}

///////////////////////////////////////////////////////////////////////////////
EventStats::EventStats(Stats & stats)
   : stats_(stats)
{ }

} // be::perf
