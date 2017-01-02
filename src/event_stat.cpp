#include "pch.hpp"
#include "event_stat.hpp"
#include "stats.hpp"

namespace be {
namespace perf {

///////////////////////////////////////////////////////////////////////////////
EventStat::EventStat(EventStat&& other)
   : StatBase(other.owner_, other.id_, other.name_)
{ }

///////////////////////////////////////////////////////////////////////////////
U64 EventStat::sample_id(size_t index) const {
   return data_[index].event_id;
}

///////////////////////////////////////////////////////////////////////////////
TU EventStat::timestamp(size_t index) const {
   return data_[index].timestamp;
}

///////////////////////////////////////////////////////////////////////////////
U64 EventStat::duration(size_t index) const {
   return data_[index].duration;
}

///////////////////////////////////////////////////////////////////////////////
const S& EventStat::data(size_t index) const {
   return data_[index].data;
}

///////////////////////////////////////////////////////////////////////////////
void EventStat::report(U64 event_id, U64 duration, S data) {
   TU begin = ts_now() - perf_delta_to_tu(duration);
   data_.push_back(record { event_id, begin, duration, std::move(data) });
}

///////////////////////////////////////////////////////////////////////////////
EventStat::EventStat(Stats& owner, Id id, S name)
   : StatBase(owner, id, std::move(name))
{ }

} // be::perf
} // be
