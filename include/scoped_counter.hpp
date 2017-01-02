#pragma once
#ifndef BE_PERF_SCOPED_COUNTER_HPP_
#define BE_PERF_SCOPED_COUNTER_HPP_

#include "counter.hpp"
#include <be/core/service_log.hpp>

#if !defined(BE_PERF_NO_DEBUG_COUNTERS) && !defined(BE_PERF_DEBUG_COUNTERS) && defined(BE_DEBUG)
#define BE_PERF_DEBUG_COUNTERS
#endif

namespace be {
namespace perf {

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V = v::info>
class ScopedCounter final : NonCopyable {
public:
   ScopedCounter() { count_(); }
   explicit ScopedCounter(const Counter& timer) : counter_(timer) { count_(); }
   explicit ScopedCounter(Counter&& timer) : counter_(std::move(timer)) { count_(); }
   explicit ScopedCounter(Id id) : counter_(id) { count_(); }
   explicit ScopedCounter(CounterStat& stat) : counter_(stat) { count_(); }

   explicit operator bool() const { return !!counter_; }
   CounterStat* stat() const { return counter_.stat(); }

   void count(I64 count = 1ull) { count_(count); }

private:
   void count_(I64 count = 1ull) {
      if (check_verbosity(V, default_log().verbosity_mask())) {
         counter_.count(count);
      }
   }

   Counter counter_;
};

#ifndef BE_PERF_DEBUG_COUNTERS
template <>
class ScopedCounter<v::debug> final : NonCopyable {
public:
   ScopedCounter() { }
   explicit ScopedCounter(const Counter& counter) { }
   explicit ScopedCounter(Counter&& counter) { }
   explicit ScopedCounter(Id id) { }
   explicit ScopedCounter(CounterStat& stat) { }

   explicit operator bool() const { return false; }
   CounterStat* stat() const { return nullptr; }

   void count(I64 count = 1ull) { }
};
#endif

using DebugCounter = ScopedCounter<v::debug>;

} // be::perf
} // be

#endif
