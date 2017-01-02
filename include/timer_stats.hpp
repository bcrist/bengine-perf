#pragma once
#ifndef BE_PERF_TIMER_STATS_HPP_
#define BE_PERF_TIMER_STATS_HPP_

#include "timer_stat.hpp"
#include <boost/iterator/indirect_iterator.hpp>
#include <unordered_map>

namespace be {
namespace perf {

///////////////////////////////////////////////////////////////////////////////
class TimerStats final : Immovable {
   friend class TimerStat;
   friend class Stats;
   using map = std::unordered_map<Id, TimerStat>;
   using root_set = std::vector<TimerStat*>;
public:
   using iterator = boost::indirect_iterator<root_set::iterator>;
   using const_iterator = boost::indirect_iterator<root_set::const_iterator>;

   iterator begin()              { return iterator(roots_.begin()); }
   const_iterator begin() const  { return const_iterator(roots_.begin()); }
   iterator end()                { return iterator(roots_.end()); }
   const_iterator end() const    { return const_iterator(roots_.end()); }

   size_t size() const { return roots_.size(); }
   bool empty() const  { return roots_.empty(); }

   TimerStat& operator[](Id id);
   TimerStat& operator[](const S& name);

   void clear();

private:
   TimerStats(Stats& stats);

   void set_root_(TimerStat& stat);
   void set_child_(TimerStat& stat);

   Stats& stats_;
   map map_;
   root_set roots_;
};

} // be::perf
} // be

#endif
