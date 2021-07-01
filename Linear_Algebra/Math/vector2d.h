#pragma once
#include <memory>

#include "matrix.h"

namespace math
{
	class vector2d
	{
	protected:
		std::unique_ptr<matrix> matrix_;

	public:
		vector2d(float x, float y);
		virtual ~vector2d() = default;

		explicit operator const matrix&() const;
		explicit operator matrix& () const;
		virtual auto operator*= (std::size_t scalar) -> vector2d&;
		virtual auto operator/= (std::size_t scalar) -> vector2d&;
		virtual auto operator+= (const matrix& other) -> vector2d&;
		virtual auto operator-= (const matrix& other) -> vector2d&;
		virtual auto operator*= (const matrix& other) -> vector2d&;

		auto x() const -> const float&;
		auto y() const -> const float&;
	};
}
