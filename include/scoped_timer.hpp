#pragma once
#ifndef BE_PERF_SCOPED_TIMER_HPP_
#define BE_PERF_SCOPED_TIMER_HPP_

#include "timer.hpp"

#if !defined(BE_PERF_NO_DEBUG_TIMERS) && !defined(BE_PERF_DEBUG_TIMERS) && defined(BE_DEBUG)
#define BE_PERF_DEBUG_TIMERS
#endif

namespace be {
namespace perf {

template <v::Verbosity V = v::info>
class ScopedTimer final : NonCopyable {
public:
   ScopedTimer();
   explicit ScopedTimer(const Timer& timer);
   explicit ScopedTimer(Timer&& timer);
   explicit ScopedTimer(Id id);
   explicit ScopedTimer(TimerStat& stat);
   ~ScopedTimer();

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
   Timer timer_;
};

#ifndef BE_PERF_DEBUG_TIMERS
template <>
class ScopedTimer<v::debug> final : NonCopyable {
public:
   ScopedTimer() { }
   explicit ScopedTimer(const Timer& timer) { }
   explicit ScopedTimer(Timer&& timer) { }
   explicit ScopedTimer(Id id) { }
   explicit ScopedTimer(TimerStat& stat) { }

   explicit operator bool() const { return false; }
   TimerStat* stat() const { return nullptr; }

   void start() { }
   U64 restart() { return 0; }
   U64 stop() { return 0; }
   U64 last_started() const { return 0; }
   U64 last_stopped() const { return 0; }
   U64 elapsed() const { return 0; }
   bool started() const { return false; }
};
#endif

typedef ScopedTimer<v::debug> DebugTimer;

} // be::perf
} // be

#include "scoped_timer.inl"

#endif
