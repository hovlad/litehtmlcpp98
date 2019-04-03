#pragma once
// bilding was checked with BOOST version 1.68.0 and GCC version 4.3.2
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/move/unique_ptr.hpp>
#include <boost/foreach.hpp>//BOOST_FOREACH
#include <boost/move/move.hpp>

#ifndef LITEHTMLCPP98
#error "Dear user for c++11 you need litehtml_11\\lhmemory.h"
#endif

#define lhmemory_for BOOST_FOREACH

#define lhmemory_shared_ptr		boost::shared_ptr
#define lhmemory_weak_ptr		boost::weak_ptr
#define lhmemory_make_shared	boost::make_shared
#define lhmemory_enable_shared_from_this boost::enable_shared_from_this
#define lhmemory_unique_ptr		boost::shared_ptr
#define lhmemory_move			boost::move

//c++98 not exists move initialization of non-const reference of type
#define lhmemory_move_ncrt//c++11 std::move

#ifdef LITEHTMLCPP98
#define lhmemory_emplace_back	push_back//c++11 emplace_back
#define override
#endif
