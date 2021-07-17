#pragma once
#include "dimensional_matrix.h"

namespace math
{
    class matrix3d final : public base::dimensional_matrix<matrix3d>
    {
    public:
        matrix3d(float x, float y, float z);
        explicit matrix3d(std::unique_ptr<matrix> matrix_init);

    	/*
    	 * The matrix which this method is called on will be on the right side of the multiplication
    	 * 
    	 * YES: matrix_4X4 * this_matrix
    	 *
    	 * NO: this_matrix * matrix_4X4
    	 */
        auto multiply_by_4X4(const matrix& matrix_4X4) -> std::unique_ptr<matrix3d>;

        auto x() const -> const float&;
        auto y() const -> const float&;
        auto z() const -> const float&;
    };
}


