#pragma once
#ifndef BE_PERF_EVENT_STAT_HPP_
#define BE_PERF_EVENT_STAT_HPP_

#include "stat_base.hpp"
#include <be/core/time.hpp>

namespace be {
namespace perf {

class Stats;

namespace detail {

///////////////////////////////////////////////////////////////////////////////
struct EventStatRec {
   U64 event_id;
   TU timestamp;
   U64 duration;
   S data;
};

} // be::perf::detail

///////////////////////////////////////////////////////////////////////////////
class EventStat final : public StatBase<detail::EventStatRec> {
   friend class EventStats;
public:
   EventStat(EventStat&& other);

   U64 sample_id(size_t index) const;
   TU timestamp(size_t index) const;
   U64 duration(size_t index) const;
   const S& data(size_t index) const;
   
   void report(U64 event_id, U64 duration, S data);

private:
   EventStat(Stats& owner, Id id, S name);
};

} // be::perf
} // be

#endif

