#pragma once
#ifndef BE_PERF_STAT_BASE_HPP_
#define BE_PERF_STAT_BASE_HPP_

#include "perf_autolink.hpp"
#include <be/core/id.hpp>
#include <boost/circular_buffer.hpp>

namespace be {
namespace perf {

class Stats;

///////////////////////////////////////////////////////////////////////////////
template <typename R>
class StatBase : Immovable {
protected:
   using record_container = boost::circular_buffer<R>;

public:
   using iterator = typename record_container::const_iterator;
   using record = R;

   Stats& owner() { return owner_; }
   const Stats& owner() const { return owner_; }

   Id id() const { return id_; }

   void name(S name) { name_ = std::move(name); }
   const S& name() const { return name_; }

   void capacity(size_t capacity) { data_.set_capacity(capacity); }
   size_t capacity() const { return data_.capacity(); }

   iterator begin() const { return data_.begin(); }
   iterator end() const { return data_.end(); }

   size_t size() const { return data_.size(); }
   bool empty() const { return data_.empty(); }

   const record& front() const { return data_.front(); }
   const record& back() const { return data_.back(); }
   const record& operator[](size_t index) const { return data_[index]; }

   void clear() { data_.clear(); }

protected:
   StatBase(Stats& owner, Id id, S name)
      : id_(id),
        owner_(owner),
        name_(std::move(name))
   { }

   Id id_;
   Stats& owner_;
   S name_;

   record_container data_;
};

} // perf
} // be

#endif
