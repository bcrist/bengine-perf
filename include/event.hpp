#pragma once
#ifndef BE_PERF_EVENT_HPP_
#define BE_PERF_EVENT_HPP_

#include "perf_autolink.hpp"
#include <be/core/id.hpp>
#include <be/core/verbosity.hpp>

namespace be::perf {
   
class EventStat;

template <v::Verbosity>
class ScopedEvent;

class Event final
{
   friend void swap(Event& a, Event& b) { a.swap_(b); }
public:
   Event();
   explicit Event(Id id);
   explicit Event(EventStat& stat);
   template <v::Verbosity V> Event(const ScopedEvent<V>& event);
   Event(const Event& other);
   Event(Event&& other);
   Event& operator=(Event other);

   explicit operator bool() const;
   EventStat* stat() const;

   void start();
   void cancel();
   void finish(U64 event_id, const S& data);
   void finish(U64 event_id, S&& data = S());
   bool started() const;
   
private:
   void swap_(Event& other);

   EventStat* stat_;
   bool started_;
   U64 start_ticks_;
};

template <v::Verbosity V>
inline Event::Event(const ScopedEvent<V>& event)
   : stat_(event.stat())
{ }

} // be::perf

#endif
