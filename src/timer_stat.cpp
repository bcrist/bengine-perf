#include "pch.hpp"
#include "timer_stat.hpp"
#include "stats.hpp"

namespace be {
namespace perf {
namespace detail {

///////////////////////////////////////////////////////////////////////////////
TimerStatChildren::iterator TimerStatChildren::begin() {
   return iterator(children_.begin());
}

///////////////////////////////////////////////////////////////////////////////
TimerStatChildren::const_iterator TimerStatChildren::begin() const {
   return const_iterator(children_.begin());
}

///////////////////////////////////////////////////////////////////////////////
TimerStatChildren::iterator TimerStatChildren::end() {
   return iterator(children_.end());
}

///////////////////////////////////////////////////////////////////////////////
TimerStatChildren::const_iterator TimerStatChildren::end() const {
   return const_iterator(children_.end());
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TimerStatChildren::size() const {
   return children_.size();
}

///////////////////////////////////////////////////////////////////////////////
bool TimerStatChildren::empty() const {
   return children_.empty();
}

///////////////////////////////////////////////////////////////////////////////
TimerStat& TimerStatChildren::front() {
   return *children_.front();
}

///////////////////////////////////////////////////////////////////////////////
const TimerStat& TimerStatChildren::front() const {
   return *children_.front();
}

///////////////////////////////////////////////////////////////////////////////
TimerStat& TimerStatChildren::back() {
   return *children_.back();
}

///////////////////////////////////////////////////////////////////////////////
const TimerStat& TimerStatChildren::back() const {
   return *children_.back();
}

///////////////////////////////////////////////////////////////////////////////
TimerStat& TimerStatChildren::operator[](size_t index) {
   return *children_[index];
}

///////////////////////////////////////////////////////////////////////////////
const TimerStat& TimerStatChildren::operator[](size_t index) const {
   return *children_[index];
}

///////////////////////////////////////////////////////////////////////////////
void TimerStatChildren::capacity(size_t record_capacity) {
   for (TimerStat* stat : children_) {
      stat->capacity(record_capacity);
   }
}

///////////////////////////////////////////////////////////////////////////////
void TimerStatChildren::clear_records() {
   for (TimerStat* stat : children_) {
      stat->clear();
   }
}

///////////////////////////////////////////////////////////////////////////////
void TimerStatChildren::next_record() {
   for (TimerStat* stat : children_) {
      stat->next_record();
   }
}

///////////////////////////////////////////////////////////////////////////////
void TimerStatChildren::next_record(U64 sample_id) {
   for (TimerStat* stat : children_) {
      stat->next_record(sample_id);
   }
}

///////////////////////////////////////////////////////////////////////////////
U64 TimerStatChildren::total_elapsed() const {
   U64 elapsed = 0;
   for (TimerStat* stat : children_) {
      elapsed += stat->elapsed();
   }
   return elapsed;
}

///////////////////////////////////////////////////////////////////////////////
U64 TimerStatChildren::total_elapsed(size_t record_index) const {
   U64 elapsed = 0;
   for (TimerStat* stat : children_) {
      elapsed += stat->elapsed(record_index);
   }
   return elapsed;
}

} // be::perf::detail

///////////////////////////////////////////////////////////////////////////////
TimerStat::TimerStat(TimerStat&& other)
   : StatBase(other.owner_, other.id_, other.name_),
     parent_(nullptr),
     use_active_(false)
{
   assert(other.parent() == nullptr);
   assert(other.children.empty());

   active_.sample_id = 0;
   active_.elapsed = 0;
   active_.n_reports = 0;
}

///////////////////////////////////////////////////////////////////////////////
void TimerStat::clear_parent() {
   if (parent_) {
      auto& con = parent_->children.children_;
      auto it = std::find(con.begin(), con.end(), this);
      con.erase(it);

      parent_ = nullptr;
      owner_.timers.set_root_(*this);
   }
}

///////////////////////////////////////////////////////////////////////////////
void TimerStat::parent(TimerStat& stat) {
   if (&stat.owner() != &owner_) {
      throw std::invalid_argument("New parent has different owner!");
   }

   TimerStat* cursor = &stat;
   while (cursor) {
      if (cursor == this) {
         throw std::invalid_argument("Setting parent would create circular reference!");
      }

      cursor = cursor->parent();
   }
   
   if (parent_) {
      if (parent_ == &stat) {
         return;
      }

      auto& con = parent_->children.children_;
      auto it = std::find(con.begin(), con.end(), this);
      con.erase(it);
   } else {
      owner_.timers.set_child_(*this);
   }

   parent_ = &stat;
   stat.children.children_.push_back(this);
   capacity(stat.capacity());
   while (stat.size() > size()) {
      next_record();
   }
}

///////////////////////////////////////////////////////////////////////////////
TimerStat* TimerStat::parent() const {
   return parent_;
}

///////////////////////////////////////////////////////////////////////////////
void TimerStat::capacity(size_t capacity) {
   data_.set_capacity(capacity);
   children.capacity(capacity);
}

///////////////////////////////////////////////////////////////////////////////
std::size_t TimerStat::capacity() {
   return data_.capacity();
}

///////////////////////////////////////////////////////////////////////////////
U64 TimerStat::sample_id(size_t index) const {
   return data_[index].sample_id;
}

///////////////////////////////////////////////////////////////////////////////
U64 TimerStat::elapsed(size_t index) const {
   return data_[index].elapsed;
}

///////////////////////////////////////////////////////////////////////////////
I64 TimerStat::exclusive_elapsed(size_t index) const {
   return (I64)elapsed(index) - (I64)children.total_elapsed(index);
}

///////////////////////////////////////////////////////////////////////////////
U64 TimerStat::report_count(size_t index) const {
   return data_[index].n_reports;
}

///////////////////////////////////////////////////////////////////////////////
void TimerStat::clear() {
   data_.clear();
   use_active_ = false;
   active_.sample_id = 0;
   active_.elapsed = 0;
   active_.n_reports = 0;
   children.clear_records();
}

///////////////////////////////////////////////////////////////////////////////
void TimerStat::next_record() {
   U64 id = active_.sample_id + 1;
   if (use_active_) {
      data_.push_back(active_);
   } else {
      use_active_ = true;
   }

   active_.sample_id = id;
   active_.elapsed = 0ull;
   active_.n_reports = 0ull;
   children.next_record();
}

///////////////////////////////////////////////////////////////////////////////
void TimerStat::next_record(U64 sample_id) {
   data_.push_back(active_);
   if (use_active_) {
      data_.push_back(active_);
   } else {
      use_active_ = true;
   }

   active_.sample_id = sample_id;
   active_.elapsed = 0ull;
   active_.n_reports = 0ull;
   children.next_record(sample_id);
}

///////////////////////////////////////////////////////////////////////////////
void TimerStat::report(U64 duration) {
   active_.elapsed += duration;
   ++active_.n_reports;
}

///////////////////////////////////////////////////////////////////////////////
U64 TimerStat::sample_id() const {
   return active_.sample_id;
}

///////////////////////////////////////////////////////////////////////////////
U64 TimerStat::elapsed() const {
   return active_.elapsed;
}

///////////////////////////////////////////////////////////////////////////////
I64 TimerStat::exclusive_elapsed() const {
   return (I64)elapsed() - (I64)children.total_elapsed();
}

///////////////////////////////////////////////////////////////////////////////
U64 TimerStat::report_count() const {
   return active_.n_reports;
}

///////////////////////////////////////////////////////////////////////////////
TimerStat::TimerStat(Stats& owner, Id id, S name)
   : StatBase(owner, id, std::move(name)),
     parent_(nullptr),
     use_active_(false)
{
   active_.sample_id = 0;
   active_.elapsed = 0;
   active_.n_reports = 0;
}

} // be::perf
} // be
