#pragma once

#include <cstdint>
#include <limits>
#include <cstring>


using s8 = int8_t;
using u8 = uint8_t;
using s16 = int16_t;
using u16 = uint16_t;
using s32 = int32_t;
using u32 = uint32_t;
using s64 = int64_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;
using pstr = char*;
using pcstr = const char*;

template <typename T>
constexpr T type_max = std::numeric_limits<T>::max();

template <typename T>
constexpr T type_min = std::numeric_limits<T>::lowest();

template <typename T>
constexpr T type_zero = T(0);

template <typename T>
constexpr T type_epsilon = std::numeric_limits<T>::epsilon();

constexpr auto int_max = type_max<int>;
constexpr auto int_min = type_min<int>;
constexpr auto int_zero = type_zero<int>;

constexpr auto flt_max = type_max<float>;
constexpr auto flt_min = type_min<float>;
constexpr auto flt_zero = type_zero<float>;
constexpr auto flt_eps = type_epsilon<float>;

constexpr auto dbl_max = type_max<double>;
constexpr auto dbl_min = type_min<double>;
constexpr auto dbl_zero = type_zero<double>;
constexpr auto dbl_eps = type_epsilon<double>;

using string16 = char[16];
using string32 = char[32];
using string64 = char[64];
using string128 = char[128];
using string256 = char[256];
using string512 = char[512];
using string1024 = char[1024];
using string2048 = char[2048];
using string4096 = char[4096];
constexpr size_t max_path_size = 2 * _MAX_PATH;
using string_path = char[max_path_size];


#ifdef CORE_API_EXPORTS
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)

#endif

#ifdef ENGINE_API_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)

#endif


#ifdef RENDER_API_EXPORTS
#define RENDER_API __declspec(dllexport)
#else
#define RENDER_API __declspec(dllimport)

#endif


