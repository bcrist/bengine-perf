#pragma once
#ifndef BE_PERF_COUNTER_HPP_
#define BE_PERF_COUNTER_HPP_

#include "perf_autolink.hpp"
#include <be/core/id.hpp>
#include <be/core/verbosity.hpp>

namespace be::perf {

class CounterStat;

template <v::Verbosity>
class ScopedCounter;

///////////////////////////////////////////////////////////////////////////////
class Counter final {
   friend void swap(Counter& a, Counter& b) { a.swap_(b); }
public:
   Counter();
   explicit Counter(Id id);
   explicit Counter(CounterStat& stat);

   template <v::Verbosity V>
   Counter(const ScopedCounter<V>& counter)
      : stat_(counter.stat())
   { }

   Counter(const Counter& other);
   Counter(Counter&& other);
   Counter& operator=(Counter other);

   explicit operator bool() const;
   CounterStat* stat() const;

   void count(I64 delta = 1ull);

private:
   void swap_(Counter& other);

   CounterStat* stat_;
};

} // be::perf

#endif
