#pragma once
#ifndef BE_PERF_SCOPED_EVENT_HPP_
#define BE_PERF_SCOPED_EVENT_HPP_

#include "event.hpp"
#include <be/core/service_log.hpp>

#if !defined(BE_PERF_NO_DEBUG_EVENTS) && !defined(BE_PERF_DEBUG_EVENTS) && defined(BE_DEBUG)
#define BE_PERF_DEBUG_EVENTS
#endif

namespace be::perf {
   
class EventStat;

template <v::Verbosity V = v::info>
class ScopedEvent final {
public:
   ScopedEvent();
   explicit ScopedEvent(const Event& event);
   explicit ScopedEvent(Event&& event);
   explicit ScopedEvent(Id stat_id);
   explicit ScopedEvent(EventStat& stat);
   ScopedEvent(Id stat_id, Id event_id, const S& data);
   ScopedEvent(Id stat_id, Id event_id, S&& data = S());
   ScopedEvent(EventStat& stat, Id event_id, const S& data);
   ScopedEvent(EventStat& stat, Id event_id, S&& data = S());
   ~ScopedEvent();

   explicit operator bool() const;
   EventStat* stat() const;

   const S& data() const;
   void data(S data);

   Id event_id() const;
   void event_id(Id event_id);

   void start();
   void cancel();
   void finish(U64 event_id, S data = S());
   bool started() const;
   
private:
   Event event_;
   S data_;
   Id event_id_;
};

#ifndef BE_PERF_DEBUG_EVENTS
template <>
class ScopedEvent<v::debug> final : NonCopyable {
public:
   ScopedEvent() { }
   explicit ScopedEvent(const Event& event) { }
   explicit ScopedEvent(Event&& event) { }
   explicit ScopedEvent(Id id) { }
   explicit ScopedEvent(EventStat& stat) { }
   ScopedEvent(Id stat_id, Id event_id, const S& data) { }
   ScopedEvent(Id stat_id, Id event_id, S&& data = S()) { }
   ScopedEvent(EventStat& stat, Id event_id, const S& data) { }
   ScopedEvent(EventStat& stat, Id event_id, S&& data = S()) { }

   explicit operator bool() const { return false; }
   EventStat* getStat() const { return nullptr; }

   const S& data() const { static S empty; return empty; }
   void data(S data) { }

   Id event_id() const { return Id(); }
   void event_id(Id event_id) { }

   void start() { }
   void cancel() { }
   void finish(U64 event_id, S data = S()) { }
   bool started() const { return false; }
};
#endif

typedef ScopedEvent<v::debug> DebugTimer;

} // be::perf

#include "scoped_event.inl"

#endif
