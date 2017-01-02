#if !defined(BE_PERF_SCOPED_TIMER_HPP_) && !defined(DOXYGEN)
#include "scoped_timer.hpp"
#elif !defined(BE_PERF_SCOPED_TIMER_INL_)
#define BE_PERF_SCOPED_TIMER_INL_

namespace be {
namespace perf {

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline ScopedTimer<V>::ScopedTimer()
{
   if (check_verbosity(V, default_log().verbosity_mask())) {
      timer_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline ScopedTimer<V>::ScopedTimer(const Timer& timer)
   : timer_(timer)
{
   if (check_verbosity(V, default_log().verbosity_mask())) {
      timer_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline ScopedTimer<V>::ScopedTimer(Timer&& timer)
   : timer_(std::move(timer))
{
   if (check_verbosity(V, default_log().verbosity_mask())) {
      timer_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline ScopedTimer<V>::ScopedTimer(Id id)
   : timer_(id)
{
   if (check_verbosity(V, default_log().verbosity_mask())) {
      timer_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline ScopedTimer<V>::ScopedTimer(TimerStat& stat)
   : timer_(stat)
{
   if (check_verbosity(V, default_log().verbosity_mask())) {
      timer_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline ScopedTimer<V>::~ScopedTimer() {
   if (check_verbosity(V, default_log().verbosity_mask())) {
      timer_.stop();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline ScopedTimer<V>::operator bool() const {
   return !!timer_;
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline TimerStat* ScopedTimer<V>::stat() const {
   return timer_.stat();
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline void ScopedTimer<V>::start() {
   if (check_verbosity(V, default_log().verbosity_mask())) {
      timer_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline U64 ScopedTimer<V>::restart() {
   if (check_verbosity(V, default_log().verbosity_mask())) {
      return timer_.restart();
   }

   return elapsed();
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline U64 ScopedTimer<V>::stop() {
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      return timer_.stop();
   }

   return elapsed();
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline U64 ScopedTimer<V>::last_started() const {
   return timer_.last_started();
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline U64 ScopedTimer<V>::last_stopped() const {
   return timer_.last_stopped();
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline U64 ScopedTimer<V>::get_elapsed() const {
   return timer_.elapsed();
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
inline bool ScopedTimer<V>::started() const {
   return timer_.started();
}

} // be::perf
} // be

#endif
