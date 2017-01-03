#ifndef __CONFIG_H__
#define __CONFIG_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined(_MSC_VER) && ! defined(__clang__)
#  define CONSTEXPR
#  define NOEXCEPT _NOEXCEPT
#elif __cplusplus >= 201402
// C++14
#  define CONSTEXPR constexpr
#  define NOEXCEPT noexcept
#else
// C++11
#  define CONSTEXPR const
#  define NOEXCEPT noexcept
#endif

#endif // __CONFIG_H__




