#pragma once
#include <memory>
#include <vector>

namespace math
{
	class matrix
	{
	protected:
		std::size_t rows_;
		std::size_t columns_;
		std::vector<float> values_;

	public:
		matrix(std::size_t rows, std::size_t columns, float init = float{});

		auto rows() const noexcept -> std::size_t;

		auto columns() const noexcept -> std::size_t;

		auto resize(std::size_t new_row, std::size_t new_col) -> void;

		auto get(std::size_t row, std::size_t col) -> float&;

		auto get(std::size_t row, std::size_t col) const -> const float&;

		auto operator()(std::size_t row, std::size_t col) -> float&;

		auto operator()(std::size_t row, std::size_t col) const -> const float&;

		auto has_equal_values(const matrix& other) const -> bool;

		/// <summary>
		/// Multiply the current matrix with a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value.</param>
		/// <returns>The scalar multiplication result.</returns>
		auto operator*=(std::size_t scalar) -> matrix&;
		auto operator*(std::size_t scalar) -> std::unique_ptr<matrix>;

		/// <summary>
		/// Divide the current matrix with a scalar.
		/// </summary>
		/// <param name="scalar">The scalar value.</param>
		/// <returns>The scalar division result.</returns>
		auto operator/=(std::size_t scalar) -> matrix&;
		auto operator/(std::size_t scalar) -> std::unique_ptr<matrix>;

		/// <remarks>
		/// The other matrix should have the same amount of rows and columns as the current matrix.<br/>
		/// e.g. <paramref name="other"/> has 3 rows and 5 columns then the current matrix should have 3 rows and 5 columns.
		/// </remarks>
		/// <summary>
		/// Adds the <paramref name="other"/> matrix's values to the current matrix's values.
		/// </summary>
		/// <param name="other">The other matrix.</param>
		/// <returns>The addition result.</returns>
		auto operator+=(const matrix& other) -> matrix&;
		auto operator+(const matrix& other) -> std::unique_ptr<matrix>;

		/// <remarks>
		/// The other matrix should have the same amount of rows and columns as the current matrix.<br/>
		/// e.g. <paramref name="other"/> has 3 rows and 5 columns then the current matrix should have 3 rows and 5 columns.
		/// </remarks>
		/// <summary>
		/// Subtracts the <paramref name="other"/> matrix's values from the current matrix's values.
		/// </summary>
		/// <param name="other">The other matrix.</param>
		/// <returns>The subtraction result.</returns>
		auto operator-=(const matrix& other) -> matrix&;
		auto operator-(const matrix& other) -> std::unique_ptr<matrix>;

		/// <summary>
		/// Multiplies the current matrix's values with the other matrix's values.
		/// </summary>
		/// <param name="other">The other matrix.</param>
		/// <returns>The multiplication result.</returns>
		auto operator*=(const matrix& other) -> matrix&;
		auto operator*(const matrix& other) -> std::unique_ptr<matrix>;

	private:
		/// <remarks>
		/// Additive rules apply to + and - operations.
		/// <summary>
		/// Asserts that the additive rule (equal rows and columns to both matrixes) is correct or not.
		/// </summary>
		/// <param name="other">The other matrix.</param>
		auto assertAdditiveRule(const matrix& other) const -> void;

		/// <remarks>
		/// Multiplicative rules apply to /, * and % operations.
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other">The other matrix.</param>
		auto assertMultiplicativeRule(const matrix& other) const -> void;
	};
}
