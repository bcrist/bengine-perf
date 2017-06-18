#pragma once
#ifndef BE_PERF_STATS_HPP_
#define BE_PERF_STATS_HPP_

#include "counter_stats.hpp"
#include "timer_stats.hpp"
#include "event_stats.hpp"

namespace be::perf {

///////////////////////////////////////////////////////////////////////////////
class Stats final : Immovable {
public:
   Stats();

   void clear();
  
   CounterStats counters;
   TimerStats timers;
   EventStats events;

private:   
};

} // be::perf

#endif
