#include "pch.hpp"
#include "timer_stats.hpp"

namespace be::perf {

///////////////////////////////////////////////////////////////////////////////
TimerStat& TimerStats::operator[](Id id) {
   map::iterator it = map_.find(id);
   if (it == map_.end()) {
      std::pair<map::iterator, bool> res = map_.emplace(id, TimerStat(stats_, id, S(id)));
      it = res.first;
      roots_.push_back(&it->second);
   }

   return it->second;
}

///////////////////////////////////////////////////////////////////////////////
TimerStat& TimerStats::operator[](const S& name) {
   Id id(name);
   map::iterator it = map_.find(id);
   if (it == map_.end()) {
      std::pair<map::iterator, bool> res = map_.emplace(id, TimerStat(stats_, id, name));
      it = res.first;
      roots_.push_back(&it->second);
   }

   return it->second;
}

///////////////////////////////////////////////////////////////////////////////
void TimerStats::clear() {
   roots_.clear();
   map_.clear();
}

///////////////////////////////////////////////////////////////////////////////
TimerStats::TimerStats(Stats& stats)
   : stats_(stats)
{ }

///////////////////////////////////////////////////////////////////////////////
void TimerStats::set_root_(TimerStat& stat) {
   root_set::iterator it = std::find(roots_.begin(), roots_.end(), &stat);
   if (it == roots_.end()) {
      roots_.push_back(&stat);
   }
}

///////////////////////////////////////////////////////////////////////////////
void TimerStats::set_child_(TimerStat& stat) {
   root_set::iterator it = std::find(roots_.begin(), roots_.end(), &stat);
   if (it != roots_.end()) {
      roots_.erase(it);
   }
}

} // be::perf
