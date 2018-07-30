#pragma once

#include "../basic/basic.h"

enum class token {
	comma,				// ,
	semicolon,			// ;
	colon,				// :
	question,			// ?
	lbrace,				// {
	rbrace,				// }
	lbracket,			// [
	rbracket,			// ]
	lparenthesis,		// (
	rparenthesis,		// )
	add,				// +
	sub,				// -
	mul,				// *
	div,				// /
	mod,				// %
	not,				// !
	bnot,				// ~
	band,				// &
	bor,				// |
	greater,			// >
	less,				// <
	assign,				// =
	inc,				// ++
	dec,				// --
	addass,				// +=
	subass,				// -=
	mulass,				// *=
	divass,				// /=
	modass,				// %=
	shlass,				//<<=
	shrass,				//>>=
	orass,				// |=
	andass,				// &=
	xorass,				// ^=
	equal,				// ==
	lor,				// ||
	land,				// &&
	nequal,				// !=
	lequal,				// <=
	gequal,				// >=
	shl,				// <<
	shr,				// >>
	point,				// .
	arrow,				// ->
	tokellipsis,		//...
	int_literal,
	uint_literal,
	double_literal,
	char_literal,
	string_literal,
	identifier,
	toktypedef,
	tokvoid,
	tokconst,
	tokchar,
	tokint,
	tokunsigned,
	tokshort,
	toklong,
	tokfloat,
	tokdouble,
	toksizeof,
	tokstruct,
	tokenum,
	tokunion,
	tokif,
	tokelse,
	tokdo,
	tokfor,
	tokwhile,
	tokreturn,
	tokgoto,
	tokswitch,
	tokcase,
	tokdefault,
	tokbreak,
	tokcontinue,
	tokauto,
	tokextern,
	tokstatic,
	whitespace

};