#include "pch.hpp"
#include "counter_stat.hpp"
#include "stats.hpp"

namespace be {
namespace perf {

///////////////////////////////////////////////////////////////////////////////
CounterStat::CounterStat(CounterStat&& other)
   : StatBase(other.owner_, other.id_, other.name_),
     use_active_(false)
{
   active_.sample_id = 0;
   active_.count = 0;
   active_.n_reports = 0;
}

///////////////////////////////////////////////////////////////////////////////
U64 CounterStat::sample_id(size_t index) const {
   return data_[index].sample_id;
}

///////////////////////////////////////////////////////////////////////////////
U64 CounterStat::count(size_t index) const {
   return data_[index].count;
}

///////////////////////////////////////////////////////////////////////////////
U64 CounterStat::report_count(size_t index) const {
   return data_[index].n_reports;
}

///////////////////////////////////////////////////////////////////////////////
void CounterStat::clear() {
   data_.clear();
   use_active_ = false;
   active_.sample_id = 0;
   active_.count = 0;
   active_.n_reports = 0;
}

///////////////////////////////////////////////////////////////////////////////
void CounterStat::next_record() {
   U64 id = active_.sample_id + 1;
   if (use_active_) {
      data_.push_back(active_);
   } else {
      use_active_ = true;
   }

   active_.sample_id = id;
   active_.count = 0ull;
   active_.n_reports = 0ull;
}

///////////////////////////////////////////////////////////////////////////////
void CounterStat::next_record(U64 sample_id) {
   data_.push_back(active_);
   if (use_active_) {
      data_.push_back(active_);
   } else {
      use_active_ = true;
   }

   active_.sample_id = sample_id;
   active_.count = 0ull;
   active_.n_reports = 0ull;
}

///////////////////////////////////////////////////////////////////////////////
void CounterStat::report(I64 delta) {
   active_.count += delta;
   ++active_.n_reports;
}

///////////////////////////////////////////////////////////////////////////////
U64 CounterStat::sample_id() const {
   return active_.sample_id;
}

///////////////////////////////////////////////////////////////////////////////
U64 CounterStat::count() const {
   return active_.count;
}

///////////////////////////////////////////////////////////////////////////////
U64 CounterStat::report_count() const {
   return active_.n_reports;
}

///////////////////////////////////////////////////////////////////////////////
CounterStat::CounterStat(Stats& owner, Id id, S name)
   : StatBase(owner, id, std::move(name)),
     use_active_(false)
{
   active_.sample_id = 0;
   active_.count = 0;
   active_.n_reports = 0;
}

} // be::perf
} // be
