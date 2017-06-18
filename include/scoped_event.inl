#if !defined(BE_PERF_SCOPED_EVENT_HPP_) && !defined(DOXYGEN)
#include "scoped_event.hpp"
#elif !defined(BE_PERF_SCOPED_EVENT_INL_)
#define BE_PERF_SCOPED_EVENT_INL_

namespace be::perf {

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::ScopedEvent() {
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::ScopedEvent(const Event& event)
   : event_(event)
{
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::ScopedEvent(Event&& event)
   : event_(std::move(event))
{
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::ScopedEvent(Id id)
   : event_(id)
{
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::ScopedEvent(EventStat& stat)
   : event_(stat)
{
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::ScopedEvent(Id stat_id, Id event_id, const S& data)
   : event_(stat_id),
     data_(data),
     event_id_(event_id)
{
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::ScopedEvent(Id stat_id, Id event_id, S&& data)
   : event_(stat_id),
     data_(std::move(data)),
     event_id_(event_id)
{
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::ScopedEvent(EventStat& stat, Id event_id, const S& data)
   : event_(stat),
     data_(data),
     event_id_(event_id)
{
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::ScopedEvent(EventStat& stat, Id event_id, S&& data)
   : event_(stat),
     data_(std::move(data)),
     event_id_(event_id)
{
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.start();
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::~ScopedEvent() {
   event_.finish(event_id_, std::move(data_));
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
ScopedEvent<V>::operator bool() const {
   return (bool)event_;
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
EventStat* ScopedEvent<V>::stat() const {
   return event_.getStat();
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
const S& ScopedEvent<V>::data() const {
   return data_;
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
void ScopedEvent<V>::data(S data) {
   data_ = std::move(data);
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
Id ScopedEvent<V>::event_id() const {
   return event_id_;
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
void ScopedEvent<V>::event_id(Id event_id) {
   event_id_ = event_id;
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
void ScopedEvent<V>::start() {
   event_.start();
}
///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
void ScopedEvent<V>::cancel() {
   event_.cancel();
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
void ScopedEvent<V>::finish(U64 event_id, S data) {
   if (check_verbosity(V, default_log().verbosity_mask()))) {
      event_.finish(event_id, std::move(data));
   }
}

///////////////////////////////////////////////////////////////////////////////
template <v::Verbosity V>
bool ScopedEvent<V>::started() const {
   return check_verbosity(V, default_log().verbosity_mask()) && event_.started();
}

} // be::perf

#endif
