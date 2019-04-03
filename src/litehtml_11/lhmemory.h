#pragma once
#ifdef LITEHTMLCPP98
#error "Dear user for c++98 you need litehtml_boost\\lhmemory.h"
#endif

#include <memory>

#define lhmemory_shared_ptr		std::shared_ptr
#define lhmemory_weak_ptr		std::weak_ptr
#define lhmemory_make_shared	std::make_shared
#define lhmemory_enable_shared_from_this std::enable_shared_from_this