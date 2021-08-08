#pragma once
#include "dimensional_matrix.h"

namespace math
{
    class matrix3d final : public base::dimensional_matrix<matrix3d>
    {
    public:
        matrix3d();
        matrix3d(float x, float y, float z);
        explicit matrix3d(std::unique_ptr<matrix> matrix_init);

    	/*
    	 * The matrix which this method is called on will be on the right side of the multiplication
    	 * 
    	 * YES: matrix_4X4 * this_matrix
    	 *
    	 * NO: this_matrix * matrix_4X4
    	 */
        auto multiply_by_4X4(const matrix& matrix_4X4) const -> std::unique_ptr<matrix3d>;

        auto get_projection(const matrix& projection_matrix, int screen_center_x, int screen_center_y) const -> std::unique_ptr<matrix3d>;

        auto length() const -> float;
        auto normalise() const -> std::unique_ptr<matrix3d>;

        auto x() const -> const float&;
        auto x() -> float&;
    	
        auto y() const -> const float&;
        auto y() -> float&;
    	
        auto z() const -> const float&;
        auto z() -> float&;

        auto w() const -> const float&;
        auto w() -> float&;
    };
}


