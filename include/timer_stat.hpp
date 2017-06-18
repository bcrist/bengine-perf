#pragma once
#ifndef BE_PERF_TIMER_STAT_HPP_
#define BE_PERF_TIMER_STAT_HPP_

#include "stat_base.hpp"
#include <boost/iterator/indirect_iterator.hpp>
#include <vector>

namespace be::perf {

class Stats;
class TimerStat;

namespace detail {

///////////////////////////////////////////////////////////////////////////////
class TimerStatChildren final : Immovable {
   friend class TimerStat;
   using child_container = std::vector<TimerStat*>;
public:
   using iterator = boost::indirect_iterator<child_container::iterator>;
   using const_iterator = boost::indirect_iterator<child_container::const_iterator>;

   iterator begin();
   const_iterator begin() const;
   iterator end();
   const_iterator end() const;

   size_t size() const;
   bool empty() const;

   TimerStat& front();
   const TimerStat& front() const;
   TimerStat& back();
   const TimerStat& back() const;

   TimerStat& operator[](size_t index);
   const TimerStat& operator[](size_t index) const;

   void capacity(size_t record_capacity);
   void clear_records();

   void next_record();
   void next_record(U64 sample_id);

   U64 total_elapsed() const;
   U64 total_elapsed(size_t record_index) const;

private:
   child_container children_;
};

///////////////////////////////////////////////////////////////////////////////
struct TimerStatRec {
   U64 sample_id;
   U64 elapsed;
   U64 n_reports;
};

} // be::perf::detail

///////////////////////////////////////////////////////////////////////////////
class TimerStat final : public StatBase<detail::TimerStatRec> {
   friend class TimerStats;
public:
   using child_container = detail::TimerStatChildren;

   TimerStat(TimerStat&& other);

   void clear_parent();
   void parent(TimerStat& stat);
   TimerStat* parent() const;

   child_container children;

   void capacity(std::size_t capacity);
   std::size_t capacity();

   U64 sample_id(std::size_t index) const;
   U64 elapsed(std::size_t index) const;
   I64 exclusive_elapsed(std::size_t index) const;
   U64 report_count(std::size_t index) const;
   
   void clear();

   void next_record();
   void next_record(U64 sample_id);
   void report(U64 duration);
   U64 sample_id() const;
   U64 elapsed() const;
   I64 exclusive_elapsed() const;
   U64 report_count() const;

private:
   TimerStat(Stats& owner, Id id, S name);

   TimerStat* parent_;
   bool use_active_;
   record active_;
};

} // be::perf

#endif

