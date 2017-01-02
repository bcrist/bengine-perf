#include "pch.hpp"
#include "event.hpp"
#include "event_stat.hpp"
#include "service_stats.hpp"
#include <be/core/time.hpp>

namespace be {
namespace perf {

///////////////////////////////////////////////////////////////////////////////
Event::Event()
   : stat_(nullptr),
     started_(false),
     start_ticks_(0ull)
{ }

///////////////////////////////////////////////////////////////////////////////
Event::Event(Id id)
   : stat_(&(perf_stats().events[id])),
     started_(false),
     start_ticks_(0ull)
{ }

///////////////////////////////////////////////////////////////////////////////
Event::Event(EventStat& stat)
   : stat_(&stat),
     started_(false),
     start_ticks_(0ull)
{ }

///////////////////////////////////////////////////////////////////////////////
Event::Event(const Event& other)
   : stat_(other.stat_),
     started_(other.started_),
     start_ticks_(other.start_ticks_)
{ }

///////////////////////////////////////////////////////////////////////////////
Event::Event(Event&& other)
   : stat_(other.stat_),
     started_(false),
     start_ticks_(0ull)
{
   swap_(other);
}

///////////////////////////////////////////////////////////////////////////////
Event& Event::operator=(Event other) {
   swap_(other);
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
Event::operator bool() const {
   return stat_ != nullptr;
}

///////////////////////////////////////////////////////////////////////////////
EventStat* Event::stat() const {
   return stat_;
}

///////////////////////////////////////////////////////////////////////////////
void Event::start() {
   start_ticks_ = perf_now();
}

///////////////////////////////////////////////////////////////////////////////
void Event::cancel() {
   started_ = false;
}

///////////////////////////////////////////////////////////////////////////////
void Event::finish(U64 event_id, const S& data) {
   U64 now = perf_now();
   if (stat_) {
      U64 duration = now - start_ticks_;
      stat_->report(event_id, duration, data);
   }
   started_ = false;
}

///////////////////////////////////////////////////////////////////////////////
void Event::finish(U64 event_id, S&& data) {
   U64 now = perf_now();
   if (stat_) {
      U64 duration = now - start_ticks_;
      stat_->report(event_id, duration, data);
   }
   started_ = false;
}

///////////////////////////////////////////////////////////////////////////////
bool Event::started() const {
   return started_;
}

///////////////////////////////////////////////////////////////////////////////
void Event::swap_(Event & other) {
   using std::swap;
   swap(stat_, other.stat_);
   swap(started_, other.started_);
   swap(start_ticks_, other.start_ticks_);
}

} // be::perf
} // be
