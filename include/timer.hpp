#pragma once
#ifndef BE_PERF_TIMER_HPP_
#define BE_PERF_TIMER_HPP_

#include "perf_autolink.hpp"
#include <be/core/id.hpp>
#include <be/core/verbosity.hpp>

namespace be::perf {

class TimerStat;

template <v::Verbosity>
class ScopedTimer;

///////////////////////////////////////////////////////////////////////////////
class Timer final {
   friend void swap(Timer& a, Timer& b) { a.swap_(b); }
public:
   Timer();
   explicit Timer(Id id);
   explicit Timer(TimerStat& stat);

   template <v::Verbosity V>
   Timer(const ScopedTimer<V>& timer)
      : stat_(timer.stat()),
        started_(timer.started()),
        start_ticks_(timer.last_started()),
        stop_ticks_(timer.last_stopped())
   { }

   Timer(const Timer& other);
   Timer(Timer&& other);
   Timer& operator=(Timer other);

   explicit operator bool() const;
   TimerStat* stat() const;

   void start();
   U64 restart();
   U64 stop();

   U64 last_started() const;
   U64 last_stopped() const;
   U64 elapsed() const;
   bool started() const;

private:
   void swap_(Timer& other);

   TimerStat* stat_;
   bool started_;
   U64 start_ticks_;
   U64 stop_ticks_;
};

} // be::perf

#endif
