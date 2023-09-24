#pragma once
#include "CoreLight.h"

#include <cmath>
#include <cassert>
#include <cstdint>
#include <immintrin.h>
#include <string>
#include <iostream>

#pragma warning (push)
#pragma warning (disable : 4201) //to avoid nameless struct / union warning.
namespace fm //Fast Math
{
	inline constexpr double pi()
	{
		return 3.14159265358979323846;
	}

	inline double to_radians(double degrees)
	{
		return degrees * 0.01745329251994329576923690768489;
	}

	template<typename T>
	T min(T a, T b)
	{
		return ((a) < (b) ? (a) : (b));
	}

	template<typename T>
	T max(T a, T b)
	{
		return ((a) > (b) ? (a) : (b));
	}

	template<typename T>
	T clamp(T x, T a, T b)
	{
		return max(min(x, b), a);
	}

	template<typename T>
	void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	struct ivec2
	{
		int x, y;

		ivec2(int x, int y)
			: x(x), y(y) {}
		ivec2(const int i)
			: ivec2(i, i) {}
		ivec2()
			: ivec2(0) {}
		ivec2(const ivec2& i)
			: ivec2(i.x, i.y) {}

		int& operator[](size_t i)
		{
			assert(i < 2);
			return *(&x + i);
		}

		ivec2 operator - () const { return { -x, -y }; }
		ivec2 operator + (const ivec2& i) const { return { x + i.x, y + i.y }; }
		ivec2 operator - (const ivec2& i) const { return { x - i.x, y - i.y }; }
		ivec2 operator * (const ivec2& i) const { return { x * i.x, y * i.y }; }
		ivec2 operator * (const int i) const { return { x * i, y * i }; }
		ivec2 operator / (const ivec2& i) const { return { x / i.x, y / i.y }; }
		ivec2 operator / (const int i) const { return { x / i, y / i }; }
		const ivec2& operator += (const ivec2& i) { return *this = *this + i; }
		const ivec2& operator -= (const ivec2& i) { return *this = *this - i; }
		const ivec2& operator *= (const ivec2& i) { return *this = *this * i; }
		const ivec2& operator *= (const int i) { return *this = *this * i; }
		const ivec2& operator /= (const ivec2& i) { return *this = *this / i; }
		const ivec2& operator /= (const int i) { return *this = *this / i; }
	};

	struct vec2
	{
		double x, y;

		vec2(double x, double y)
			: x(x), y(y) {}
		vec2(const double i)
			: vec2(i, i) {}
		vec2()
			: vec2(0) {}
		vec2(const vec2& i)
			: vec2(i.x, i.y) {}

		double& operator[](size_t i)
		{
			assert(i < 2);
			return *(&x + i);
		}

		vec2 operator - () const { return { -x, -y }; }
		vec2 operator + (const vec2& i) const { return { x + i.x, y + i.y }; }
		vec2 operator - (const vec2& i) const { return { x - i.x, y - i.y }; }
		vec2 operator * (const vec2& i) const { return { x * i.x, y * i.y }; }
		vec2 operator * (const double i) const { return { x * i, y * i }; }
		vec2 operator / (const vec2& i) const { return { x / i.x, y / i.y }; }
		vec2 operator / (const double i) const { return { x / i, y / i }; }
		const vec2& operator += (const vec2& i) { return *this = *this + i; }
		const vec2& operator -= (const vec2& i) { return *this = *this - i; }
		const vec2& operator *= (const vec2& i) { return *this = *this * i; }
		const vec2& operator *= (const double i) { return *this = *this * i; }
		const vec2& operator /= (const vec2& i) { return *this = *this / i; }
		const vec2& operator /= (const double i) { return *this = *this / i; }
	};

	struct vec3
	{
		double x, y, z;

		vec3(double x, double y, double z)
			: x(x), y(y), z(z) {}
		vec3(const double i)
			: vec3(i, i, i) {}
		vec3()
			: vec3(0) {}
		vec3(const vec3& i)
			: vec3(i.x, i.y, i.z) {}

		double& operator[](size_t i)
		{
			assert(i < 3);
			return *(&x + i);
		}

		vec3 operator - () const { return { -x, -y, -z }; }
		vec3 operator + (const vec3& i) const { return { x + i.x, y + i.y, z + i.z }; }
		vec3 operator - (const vec3& i) const { return { x - i.x, y - i.y, z - i.z }; }
		vec3 operator * (const vec3& i) const { return { x * i.x, y * i.y, z * i.z }; }
		vec3 operator * (const double i) const { return { x * i, y * i, z * i }; }
		vec3 operator / (const vec3& i) const { return { x / i.x, y / i.y, z / i.z }; }
		vec3 operator / (const double i) const { return { x / i, y / i, z / i }; }
		const vec3& operator += (const vec3& i) { return *this = *this + i; }
		const vec3& operator -= (const vec3& i) { return *this = *this - i; }
		const vec3& operator *= (const vec3& i) { return *this = *this * i; }
		const vec3& operator *= (const double i) { return *this = *this * i; }
		const vec3& operator /= (const vec3& i) { return *this = *this / i; }
		const vec3& operator /= (const double i) { return *this = *this / i; }

		bool operator==(const vec3& i) { return x == i.x && y == i.y && z == i.z; }

		[[nodiscard]] uint32_t get_argb() const
		{
			const double t_r = clamp<double>(x, 0, 1);
			const double t_g = clamp<double>(y, 0, 1);
			const double t_b = clamp<double>(z, 0, 1);
			return 255 | (static_cast<uint8_t>(t_r * 255) << 16) | (static_cast<uint8_t>(t_g * 255) << 8) | (static_cast<uint8_t>(t_b * 255));
		}

		[[nodiscard]] uint32_t get_rgba() const
		{
			const double t_r = clamp<double>(x, 0, 1);
			const double t_g = clamp<double>(y, 0, 1);
			const double t_b = clamp<double>(z, 0, 1);
			return static_cast<uint32_t>((static_cast<uint8_t>(t_r * 255) << 24) | (static_cast<uint8_t>(t_g * 255) << 16) | (static_cast<uint8_t>(t_b * 255) << 8) | 255);
		}

		[[nodiscard]] double dot(const vec3& i) const
		{
			return (x * i.x + y * i.y + z * i.z);
		}

		[[nodiscard]] vec3 cross(const vec3& i) const
		{
			return vec3(
				y * i.z - z * i.y,
				z * i.x - x * i.z,
				x * i.y - y * i.x);
		}
	};

	struct alignas(4 * sizeof(double)) vec4
	{
		double x, y, z, w;

		vec4(double x, double y, double z, double w)
			: x(x), y(y), z(z), w(w) {}
		vec4(const double i)
			: vec4(i, i, i, i) {}
		vec4()
			: vec4(0) {}
		vec4(const vec4& i)
			: vec4(i.x, i.y, i.z, i.w) {}
		vec4(const vec3& i)
			: vec4(i.x, i.y, i.z, 0.f) {}

		double& operator[](size_t i)
		{
			assert(i < 4);
			return *(&x + i);
		}

		const double& operator[](size_t i) const
		{
			assert(i < 4);
			return *(&x + i);
		}

		vec4 operator - () const { return { -x, -y, -z, -w }; }
		vec4 operator + (const vec4& i) const { return { x + i.x, y + i.y, z + i.z, w + i.w }; }
		vec4 operator - (const vec4& i) const { return { x - i.x, y - i.y, z - i.z, w - i.w }; }
		vec4 operator * (const vec4& i) const { return { x * i.x, y * i.y, z * i.z, w * i.w }; }
		vec4 operator * (const double i) const { return { x * i, y * i, z * i, w * i }; }
		vec4 operator / (const vec4& i) const { return { x / i.x, y / i.y, z / i.z, w / i.w }; }
		vec4 operator / (const double i) const { return { x / i, y / i, z / i, w / i }; }
		const vec4& operator += (const vec4& i) { return *this = *this + i; }
		const vec4& operator -= (const vec4& i) { return *this = *this - i; }
		const vec4& operator *= (const vec4& i) { return *this = *this * i; }
		const vec4& operator *= (const double i) { return *this = *this * i; }
		const vec4& operator /= (const vec4& i) { return *this = *this / i; }
		const vec4& operator /= (const double i) { return *this = *this / i; }

		[[nodiscard]] uint32_t get_argb() const
		{
			const double t_a = clamp<double>(w, 0, 1);
			const double t_r = clamp<double>(x, 0, 1);
			const double t_g = clamp<double>(y, 0, 1);
			const double t_b = clamp<double>(z, 0, 1);
			return static_cast<uint32_t>((static_cast<uint8_t>(t_a * 255) << 24) | (static_cast<uint8_t>(t_r * 255) << 16) | (static_cast<uint8_t>(t_g * 255) << 8) | (static_cast<uint8_t>(t_b * 255)));
		}

		[[nodiscard]] uint32_t get_rgba() const
		{
			const double t_a = clamp<double>(w, 0, 1);
			const double t_r = clamp<double>(x, 0, 1);
			const double t_g = clamp<double>(y, 0, 1);
			const double t_b = clamp<double>(z, 0, 1);
			return static_cast<uint32_t>((static_cast<uint8_t>(t_r * 255) << 24) | (static_cast<uint8_t>(t_g * 255) << 16) | (static_cast<uint8_t>(t_b * 255) << 8) | (static_cast<uint8_t>(t_a * 255)));
		}
	};

	struct mat3
	{
		vec3 x, y, z;

		mat3() {}

		mat3(double i) :
			x(i, 0, 0),
			y(0, i, 0),
			z(0, 0, i)
		{}

		mat3(vec3 x, vec3 y, vec3 z)
			: x(x), y(y), z(z) {}
		mat3(const mat3& i)
			: x(i.x), y(i.y), z(i.z) {}

		vec3& operator[](size_t i)
		{
			assert(i < 3);
			return *(&x + i);
		}

		mat3 operator*(mat3& i)
		{
			return
			{
				{x[0] * i.x[0] + x[1] * i.y[0] + x[2] * i.z[0]},
				{y[0] * i.x[1] + y[1] * i.y[1] + y[2] * i.z[1]},
				{z[0] * i.x[2] + z[1] * i.y[2] + z[2] * i.z[2]}
			};
		}
	};

	struct mat4
	{
		vec4 x, y, z, w;

		mat4() {}

		mat4(double i) :
			x(i, 0, 0, 0),
			y(0, i, 0, 0),
			z(0, 0, i, 0),
			w(0, 0, 0, i) {}

		mat4(vec4 x, vec4 y, vec4 z, vec4 w)
			: x(x), y(y), z(z), w(w) {}
		mat4(const mat4& i)
			: x(i.x), y(i.y), z(i.z), w(i.w) {}

		mat4(const mat3& i)
			: x(i.x), y(i.y), z(i.z), w(0.f, 0.f, 0.f, 1.f) {}

		vec4& operator[](size_t i)
		{
			assert(i < 4);
			return *(&x + i);
		}

		const vec4& operator[](size_t i) const
		{
			assert(i < 4);
			return *(&x + i);
		}

		mat4 operator*(const mat4& i) const
		{
			mat4 result;
#ifdef USE_SIMD

			__m256d row1 = _mm256_loadu_pd(&x.x);
			__m256d row2 = _mm256_loadu_pd(&y.x);
			__m256d row3 = _mm256_loadu_pd(&z.x);
			__m256d row4 = _mm256_loadu_pd(&w.x);

			for (int j = 0; j < 4; ++j) {
				__m256d col = _mm256_set_pd(i.w[j], i.z[j], i.y[j], i.x[j]);

				__m256d r1 = _mm256_mul_pd(row1, col);
				__m256d r2 = _mm256_mul_pd(row2, col);
				__m256d r3 = _mm256_mul_pd(row3, col);
				__m256d r4 = _mm256_mul_pd(row4, col);

				r1 = _mm256_hadd_pd(r1, r1);
				r2 = _mm256_hadd_pd(r2, r2);
				r3 = _mm256_hadd_pd(r3, r3);
				r4 = _mm256_hadd_pd(r4, r4);

				double res1[4], res2[4], res3[4], res4[4];
				_mm256_storeu_pd(res1, r1);
				_mm256_storeu_pd(res2, r2);
				_mm256_storeu_pd(res3, r3);
				_mm256_storeu_pd(res4, r4);

				result.x[j] = res1[0] + res1[2];
				result.y[j] = res2[0] + res2[2];
				result.z[j] = res3[0] + res3[2];
				result.w[j] = res4[0] + res4[2];
			}

#else
			result.x.x = x.x * i.x.x + x.y * i.y.x + x.z * i.z.x + x.w * i.w.x;
			result.x.y = x.x * i.x.y + x.y * i.y.y + x.z * i.z.y + x.w * i.w.y;
			result.x.z = x.x * i.x.z + x.y * i.y.z + x.z * i.z.z + x.w * i.w.z;
			result.x.w = x.x * i.x.w + x.y * i.y.w + x.z * i.z.w + x.w * i.w.w;

			result.y.x = y.x * i.x.x + y.y * i.y.x + y.z * i.z.x + y.w * i.w.x;
			result.y.y = y.x * i.x.y + y.y * i.y.y + y.z * i.z.y + y.w * i.w.y;
			result.y.z = y.x * i.x.z + y.y * i.y.z + y.z * i.z.z + y.w * i.w.z;
			result.y.w = y.x * i.x.w + y.y * i.y.w + y.z * i.z.w + y.w * i.w.w;

			result.z.x = z.x * i.x.x + z.y * i.y.x + z.z * i.z.x + z.w * i.w.x;
			result.z.y = z.x * i.x.y + z.y * i.y.y + z.z * i.z.y + z.w * i.w.y;
			result.z.z = z.x * i.x.z + z.y * i.y.z + z.z * i.z.z + z.w * i.w.z;
			result.z.w = z.x * i.x.w + z.y * i.y.w + z.z * i.z.w + z.w * i.w.w;

			result.w.x = w.x * i.x.x + w.y * i.y.x + w.z * i.z.x + w.w * i.w.x;
			result.w.y = w.x * i.x.y + w.y * i.y.y + w.z * i.z.y + w.w * i.w.y;
			result.w.z = w.x * i.x.z + w.y * i.y.z + w.z * i.z.z + w.w * i.w.z;
			result.w.w = w.x * i.x.w + w.y * i.y.w + w.z * i.z.w + w.w * i.w.w;
#endif
			return result;
		}

		const mat4& operator *= (const mat4& i) { return *this = *this * i; }

		std::string to_string()
		{
			return std::to_string(x.x) + " : " + std::to_string(x.y) + " : " + std::to_string(x.z) + " : " + std::to_string(x.w) + "\n" +
				std::to_string(y.x) + " : " + std::to_string(y.y) + " : " + std::to_string(y.z) + " : " + std::to_string(y.w) + "\n" +
				std::to_string(z.x) + " : " + std::to_string(z.y) + " : " + std::to_string(z.z) + " : " + std::to_string(z.w) + "\n" +
				std::to_string(w.x) + " : " + std::to_string(w.y) + " : " + std::to_string(w.z) + " : " + std::to_string(w.w) + "\n";
		}
	};

	struct quat
	{
		double x, y, z, w;

		quat() = default;
		quat(double x, double y, double z, double w)
			: x(x), y(y), z(z), w(w) {}
		quat(double a_x, double a_y, double a_z)
		{
			double cy = std::cos(a_z * 0.5f);
			double sy = std::sin(a_z * 0.5f);
			double cp = std::cos(a_y * 0.5f);
			double sp = std::sin(a_y * 0.5f);
			double cr = std::cos(a_x * 0.5f);
			double sr = std::sin(a_x * 0.5f);

			w = cr * cp * cy + sr * sp * sy;
			x = sr * cp * cy - cr * sp * sy;
			y = cr * sp * cy + sr * cp * sy;
			z = cr * cp * sy - sr * sp * cy;
		}

		quat(const vec3& i)
			: quat(i.x, i.y, i.z) {}

		quat operator - () const { return { -x, -y, -z, -w }; }
		quat operator + (const quat& i) const { return { x + i.x, y + i.y, z + i.z, w + i.w }; }
		quat operator - (const quat& i) const { return { x - i.x, y - i.y, z - i.z, w - i.w }; }
		quat operator * (const double i) const { return { x * i, y * i, z * i, w * i }; }
		quat operator * (const quat& i) const {
			return
			{
				w * i.x + x * i.w + y * i.z - z * i.y,
				w * i.y - x * i.z + y * i.w + z * i.x,
				w * i.z + x * i.y - y * i.x + z * i.w,
				w * i.w - x * i.x - y * i.y - z * i.z
			};
		}
		const quat& operator += (const quat& i) { return *this = *this + i; }
		const quat& operator -= (const quat& i) { return *this = *this - i; }
		const quat& operator *= (const quat& i) { return *this = *this * i; }
		const quat& operator *= (const double i) { return *this = *this * i; }

		vec3 rotate(const vec3& v) const
		{
			quat p(v.x, v.y, v.z, 0);
			quat q_inv(-x, -y, -z, w);
			quat result = (*this) * p * q_inv;

			return vec3(result.x, result.y, result.z);
		}

		vec3 get_euler() const
		{
			vec3 angles;

			// yaw (z-axis rotation)
			{
				double siny_cosp = 2.f * (y * z + w * x);
				double cosy_cosp = w * w - x * x - y * y + z * z;

				angles.x = std::atan2(siny_cosp, cosy_cosp);
			}

			// pitch (y-axis rotation)
			{
				double sinp = 2.f * (w * y - z * x);
				if (std::abs(sinp) >= 1.f)
					angles.y = std::copysign(pi() / 2.f, sinp); // use 90 degrees if out of range
				else
					angles.y = std::asin(sinp);
			}

			// roll (x-axis rotation)
			{
				double t_y = 2.f * (x * y + w * z);
				double t_x = w * w + x * x - y * y - z * z;

				angles.z = std::atan2(t_y, t_x);
			}

			return angles;
		}
	};

	inline vec2 normalize(const vec2& i)
	{
		double mag = std::sqrt(i.x * i.x + i.y * i.y);
		assert(mag != 0.f && "Try using normalize_safe instead");
		double inv = 1.f / mag;
		return { i.x * inv, i.y * inv };
	}


	inline vec2 normalize_safe(const vec2& i)
	{
		double mag = std::sqrt(i.x * i.x + i.y * i.y);
		if (mag == 0.f)
			mag = 1.f;
		double inv = 1.f / mag;
		return { i.x * inv, i.y * inv };
	}

	inline vec3 normalize(const vec3& i)
	{
		double mag = std::sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
		assert(mag != 0.f && "Try using normalize_safe instead");
		double inv = 1.f / mag;
		return { i.x * inv, i.y * inv, i.z * inv };
	}

	inline vec3 normalize_safe(const vec3& i)
	{
		double mag = std::sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
		if (mag == 0.f)
			mag = 1.f;
		double inv = 1.f / mag;
		return { i.x * inv, i.y * inv, i.z * inv };
	}

	inline vec4 normalize(const vec4& i)
	{
		double mag = std::sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
		assert(mag != 0.f && "Try using normalize_safe instead");
		double inv = 1.f / mag;
		return { i.x * inv, i.y * inv, i.z * inv, i.w * inv };
	}

	inline vec4 normalize_safe(const vec4& i)
	{
		double mag = std::sqrt(i.x * i.x + i.y * i.y + i.z * i.z);
		if (mag == 0.f)
			mag = 1.f;
		double inv = 1.f / mag;
		return { i.x * inv, i.y * inv, i.z * inv, i.w * inv };
	}

	inline mat4 translate(mat4 matrix, vec3 vector)
	{
		matrix.w = matrix.x * vector.x + matrix.y * vector.y + matrix.z * vector.z + matrix.w;
		return matrix;
	}

	inline mat4 scale(mat4 matrix, vec3 vector)
	{
		matrix[0] = matrix[0] * vector[0];
		matrix[1] = matrix[1] * vector[1];
		matrix[2] = matrix[2] * vector[2];
		return matrix;
	}

	inline mat4 rotate(mat4 m, double angle, vec3 v)
	{
		double const a = angle;
		double const c = cos(a);
		double const s = sin(a);

		vec3 axis(normalize(v));
		vec3 temp(axis * (1.f - c));

		mat4 temp_matrix;
		temp_matrix[0][0] = c + temp[0] * axis[0];
		temp_matrix[0][1] = temp[0] * axis[1] + s * axis[2];
		temp_matrix[0][2] = temp[0] * axis[2] - s * axis[1];

		temp_matrix[1][0] = temp[1] * axis[0] - s * axis[2];
		temp_matrix[1][1] = c + temp[1] * axis[1];
		temp_matrix[1][2] = temp[1] * axis[2] + s * axis[0];

		temp_matrix[2][0] = temp[2] * axis[0] + s * axis[1];
		temp_matrix[2][1] = temp[2] * axis[1] - s * axis[0];
		temp_matrix[2][2] = c + temp[2] * axis[2];

		mat4 result;
		result[0] = m[0] * temp_matrix[0][0] + m[1] * temp_matrix[0][1] + m[2] * temp_matrix[0][2];
		result[1] = m[0] * temp_matrix[1][0] + m[1] * temp_matrix[1][1] + m[2] * temp_matrix[1][2];
		result[2] = m[0] * temp_matrix[2][0] + m[1] * temp_matrix[2][1] + m[2] * temp_matrix[2][2];
		result[3] = m[3];
		return result;
	}

	inline mat4 get_perspective(double fovy, double aspect, double znear, double zfar)
	{
		assert(abs(aspect - std::numeric_limits<double>::epsilon()) > 0.f);

		double const tanHalfFovy = tan(fovy / 2.f);

		mat4 result(1.f);
		result[0][0] = 1.f / (aspect * tanHalfFovy);
		result[1][1] = 1.f / (tanHalfFovy);
		result[2][2] = -(zfar + znear) / (zfar - znear);
		result[2][3] = -1.f;
		result[3][2] = -2.f * zfar * znear / (zfar - znear);
		return result;
	}

	inline mat4 look_at(const vec3& eye, const vec3& target, const vec3& up)
	{
		vec3 zaxis = normalize(eye - target);
		vec3 xaxis = normalize(up.cross(zaxis));
		vec3 yaxis = zaxis.cross(xaxis);

		mat4 view;
		view[0][0] = xaxis.x;
		view[1][0] = xaxis.y;
		view[2][0] = xaxis.z;
		view[3][0] = -xaxis.dot(eye);

		view[0][1] = yaxis.x;
		view[1][1] = yaxis.y;
		view[2][1] = yaxis.z;
		view[3][1] = -yaxis.dot(eye);

		view[0][2] = zaxis.x;
		view[1][2] = zaxis.y;
		view[2][2] = zaxis.z;
		view[3][2] = -zaxis.dot(eye);

		return view;
	}

	inline mat3 to_mat3(const quat& q)
	{
		mat3 result(1.f);
		double qxx(q.x * q.x);
		double qyy(q.y * q.y);
		double qzz(q.z * q.z);
		double qxz(q.x * q.z);
		double qxy(q.x * q.y);
		double qyz(q.y * q.z);
		double qwx(q.w * q.x);
		double qwy(q.w * q.y);
		double qwz(q.w * q.z);

		result[0][0] = 1.f - 2.f * (qyy + qzz);
		result[0][1] = 2.f * (qxy + qwz);
		result[0][2] = 2.f * (qxz - qwy);

		result[1][0] = 2.f * (qxy - qwz);
		result[1][1] = 1.f - 2.f * (qxx + qzz);
		result[1][2] = 2.f * (qyz + qwx);

		result[2][0] = 2.f * (qxz + qwy);
		result[2][1] = 2.f * (qyz - qwx);
		result[2][2] = 1.f - 2.f * (qxx + qyy);
		return result;
	}

	inline mat4 to_mat4(const quat& q)
	{
		mat3 matrix3 = to_mat3(q);
		mat4 matrix4 = mat4(matrix3);
		return matrix4;
	}

	inline quat normalize(const quat& q)
	{
		double n = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
		if (n <= 0.f)
			return { 0,0,0,0 };
		n = 1.f / n;
		return
		{
			q.x * n,
			q.y * n,
			q.z * n,
			q.w * n
		};
	}

	inline quat angle_axis(double angle, const vec3& i)
	{
		double a(angle);
		double s = std::sin(a * 0.5f);

		vec3 xyz = i * s;
		return { xyz.x, xyz.y, xyz.z,std::cos(a * 0.5f) };
	}

	//Random functions
	inline uint32_t wang_hash(uint32_t seed)
	{
		seed = (seed ^ 61) ^ (seed >> 16);
		seed *= 9;
		seed = seed ^ (seed >> 4);
		seed *= 0x27d4eb2d;
		seed = seed ^ (seed >> 15);
		return seed;
	}
	inline double wang_hashf(uint32_t seed) // Return value between 0.f amd 1.f
	{
		return wang_hash(seed) * (1.0f / 4294967296.0f);
	}

	inline uint32_t xorshift32(uint32_t* pstate)
	{
		// Xorshift algorithm from George Marsaglia's paper
		uint32_t state = *pstate;
		state ^= (state << 13);
		state ^= (state >> 17);
		state ^= (state << 5);
		return (*pstate) = state;
	}
	inline double xorshift32f(uint32_t* state) // Return value between 0.f amd 1.f
	{
		return xorshift32(state) * (1.0f / 4294967296.0f);
	}

	inline vec2 clamp2(vec2 x, vec2 a, vec2 b)
	{
		return
		{
			clamp(x.x, a.x, b.x),
			clamp(x.y, a.y, b.y)
		};
	}

	inline ivec2 clamp2(ivec2 x, ivec2 a, ivec2 b)
	{
		return
		{
			clamp(x.x, a.x, b.x),
			clamp(x.y, a.y, b.y)
		};
	}

	inline vec2 max2(vec2 a, vec2 b)
	{
		return
		{
			max(a.x, b.x),
			max(a.y, b.y)
		};
	}

	inline vec2 min2(vec2 a, vec2 b)
	{
		return
		{
			min(a.x, b.x),
			min(a.y, b.y)
		};
	}

	inline double lerp(double a, double b, double t)
	{
		return a + (b - a) * t;
	}

	inline fm::vec2 lerp2(fm::vec2 a, fm::vec2 b, double t)
	{
		return a + (b - a) * t;
	}

	inline fm::vec3 lerp3(fm::vec3 a, fm::vec3 b, double t)
	{
		return a + (b - a) * t;
	}
}

#pragma warning (pop)
