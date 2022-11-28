#pragma once
//Data types are outside namespace for ease of use

using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;

using u8 = unsigned char;
using u16 = unsigned short; 
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

#if defined(_WIN64) || !defined(x64) || !defined(X64)
    using u_size = u64;
    using i_size = i64;
#else
    using u_size = u32;
    using i_size = i32;
#endif

#define I8_MIN		(-127i8 - 1)
#define I16_MIN		(-32767i16 - 1)
#define I32_MIN		(-2147483647i32 - 1)
#define I64_MIN		(-9223372036854775807i64 - 1)
#define I8_MAX		127i8
#define I16_MAX		32767i16
#define I32_MAX		2147483647i32
#define I64_MAX		9223372036854775807i64
#define UT8_MAX		0xffui8
#define U16_MAX		0xffffui16
#define U32_MAX		0xffffffffui32
#define U64_MAX		0xffffffffffffffffui64

#define F32_EPSILON 1.192092896e-07F
#define F64_EPSILON 2.2204460492503131e-016
#define F32_MIN     1.175494351e-38F
#define F64_MIN     2.2250738585072014e-308
#define F32_MAX     3.402823466e+38F
#define F64_MAX     1.7976931348623158e+308