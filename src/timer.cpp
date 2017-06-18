#include "pch.hpp"
#include "timer.hpp"
#include "timer_stat.hpp"
#include "service_stats.hpp"

namespace be::perf {

///////////////////////////////////////////////////////////////////////////////
Timer::Timer()
   : stat_(nullptr),
     started_(false),
     start_ticks_(0ull),
     stop_ticks_(0ull)
{ }

///////////////////////////////////////////////////////////////////////////////
Timer::Timer(Id id)
   : stat_(&perf_stats().timers[id]),
     started_(false),
     start_ticks_(0ull),
     stop_ticks_(0ull)
{ }

///////////////////////////////////////////////////////////////////////////////
Timer::Timer(TimerStat& stat)
   : stat_(&stat),
     started_(false),
     start_ticks_(0ull),
     stop_ticks_(0ull)
{ }

///////////////////////////////////////////////////////////////////////////////
Timer::Timer(const Timer& other)
   : stat_(other.stat_),
     started_(other.started_),
     start_ticks_(other.start_ticks_),
     stop_ticks_(other.stop_ticks_)
{ }

///////////////////////////////////////////////////////////////////////////////
Timer::Timer(Timer&& other)
   : stat_(other.stat_),
     started_(false),
     start_ticks_(0ull),
     stop_ticks_(0ull)
{
   swap_(other);
}

///////////////////////////////////////////////////////////////////////////////
Timer& Timer::operator=(Timer other) {
   swap_(other);
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
Timer::operator bool() const {
   return stat_ != nullptr;
}

///////////////////////////////////////////////////////////////////////////////
TimerStat* Timer::stat() const {
   return stat_;
}

///////////////////////////////////////////////////////////////////////////////
void Timer::start() {
   if (!started_) {
      started_ = true;
      start_ticks_ = perf_now();
   }
}

///////////////////////////////////////////////////////////////////////////////
U64 Timer::restart() {
   U64 t = perf_now();
   if (started_) {
      U64 elapsed = t - start_ticks_;
      start_ticks_ = t;

      if (stat_) {
         stat_->report(elapsed);
      }

      return elapsed;
   } else {
      started_ = true;
      start_ticks_ = t;
      return 0ull;
   }
}

///////////////////////////////////////////////////////////////////////////////
U64 Timer::stop() {
   U64 t = perf_now();
   if (started_) {
      started_ = false;
      stop_ticks_ = t;
      U64 elapsed = stop_ticks_ - start_ticks_;

      if (stat_) {
         stat_->report(elapsed);
      }

      return elapsed;
   } else {
      return elapsed();
   }
}

///////////////////////////////////////////////////////////////////////////////
U64 Timer::last_started() const {
   return start_ticks_;
}

///////////////////////////////////////////////////////////////////////////////
U64 Timer::last_stopped() const {
   return stop_ticks_;
}

///////////////////////////////////////////////////////////////////////////////
U64 Timer::elapsed() const {
   if (started_) {
      return perf_now() - start_ticks_;
   } else {
      return stop_ticks_ - start_ticks_;
   }
}

///////////////////////////////////////////////////////////////////////////////
bool Timer::started() const {
   return started_;
}

///////////////////////////////////////////////////////////////////////////////
void Timer::swap_(Timer& other) {
   using std::swap;
   swap(stat_, other.stat_);
   swap(started_, other.started_);
   swap(start_ticks_, other.start_ticks_);
   swap(stop_ticks_, other.stop_ticks_);
}

} // be::perf
