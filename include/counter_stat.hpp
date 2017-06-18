#pragma once
#ifndef BE_PERF_COUNTER_STAT_HPP_
#define BE_PERF_COUNTER_STAT_HPP_

#include "stat_base.hpp"

namespace be::perf {

class Stats;

namespace detail {

///////////////////////////////////////////////////////////////////////////////
struct CounterStatRec {
   U64 sample_id;
   U64 count;
   U64 n_reports;
};

} // be::perf::detail

///////////////////////////////////////////////////////////////////////////////
class CounterStat final : public StatBase<detail::CounterStatRec> {
   friend class CounterStats;
public:
   CounterStat(CounterStat&& other);

   U64 sample_id(size_t index) const;
   U64 count(size_t index) const;
   U64 report_count(size_t index) const;
   
   void clear();

   void next_record();
   void next_record(U64 sample_id);
   void report(I64 delta);
   U64 sample_id() const;
   U64 count() const;
   U64 report_count() const;

private:
   CounterStat(Stats& owner, Id id, S name);

   record active_;
   bool use_active_;
};

} // be::perf

#endif

