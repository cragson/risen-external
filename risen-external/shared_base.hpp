#pragma once
#include "math.hpp"


namespace SharedBase::bCMatrix
{
	[[nodiscard]] matrix4x4 get_identity() noexcept;

	[[nodiscard]] vec4 access_translation( const matrix4x4& mat ) noexcept;
}
