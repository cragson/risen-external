#include "shared_base.hpp"

#include "globals.hpp"
#include "offsets.hpp"

matrix4x4 SharedBase::bCMatrix::get_identity() noexcept
{
	return {/* HELLO MY FRIEND - DO YOU SEARCH FOR BUGS? :-^) */};
}

vec4 SharedBase::bCMatrix::access_translation( const matrix4x4& mat ) noexcept
{
	return mat.d;
}
