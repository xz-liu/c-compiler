#pragma once

#include "../basic/basic.h"
enum class token {
	toktypedef,	//	typedef
	tokvoid,	//	void
	tokconst,	//	const
	tokvolatile,//	volatile
	tokchar,	//	char
	tokint,	//	int
	tokunsigned,	//	unsigned
	tokshort,	//	short
	toklong,	//	long
	tokfloat,	//	float
	tokdouble,	//	double
	toksizeof,	//	sizeof
	tokstruct,	//	struct
	tokenum,	//	enum
	tokunion,	//	union
	tokif,	//	if
	tokelse,	//	else
	tokdo,	//	do
	tokfor,	//	for
	tokwhile,	//	while
	tokreturn,	//	return
	tokgoto,	//	goto
	tokswitch,	//	switch
	tokcase,	//	case
	tokdefault,	//	default
	tokbreak,	//	break
	tokcontinue,	//	continue
	tokauto,	//	auto
	tokregister,	//	register

	tokextern,	//	extern
	tokstatic,	//	static


	tokpragma = 100,	//	pragma
	tokinclude,	//	include
	tokdefine,	//	define
	tokundef,	//	undef
	tokifdef,	//	ifdef
	tokelif,	//	elif
	tokendif,	//	endif


	double_literal = 150,	//	-?[0-9]+((\.[0-9]+)([eE]-?[0-9]+)|(\.[0-9]+)|([eE]-?[0-9]+))[fF]?
	int_literal,	//	-?(0|[1-9][0-9]*|0[xX][0-9a-fA-F]+|0[0-7]+)[uU]?[lL]{0,2}
	char_literal,	//	'.'
	string_literal,	//	".*"
	include_file,	//	<[a-zA-Z_\\/]+(\.[a-zA-Z_\\/]+)?>
	identifier,	//	[a-zA-Z_][0-9a-zA-Z_]*

	inc = 200,	//	\+\+
	dec,	//	--
	addass,	//	\+=
	subass,	//	-=
	mulass,	//	\*=
	divass,	//	/=
	modass,	//	%=
	shlass,	//	<<=
	shrass,	//	>>=
	orass,	//	\|=
	andass,	//	&=
	xorass,	//	\^=
	equal,	//	==
	lor,	//	\|\|
	land,	//	&&
	nequal,	//	!=
	lequal,	//	<=
	gequal,	//	>=
	shl,	//	<<
	shr,	//	>>
	point,	//	\.
	arrow,	//	->
	tokellipsis,	//	\.{3}
	hashhash,	//	##
	hash,	//	#
	semicolon,	//	;
	colon,	//	:
	question,	//	\?
	lbrace,	//	\{
	rbrace,	//	\}
	lbracket,	//	\[
	rbracket,	//	\]
	lparenthesis,	//	\(
	rparenthesis,	//	\)
	add,	//	\+
	sub,	//	-
	mul,	//	\*
	div,	//	/
	mod,	//	%
	not,	//	!
	bnot,	//	~
	band,	//	&
	bor,	//	\|
	bxor,	//	\^
	greater,	//	>
	less,	//	<
	assign,	//	=
	comma,	//	,
	whitespace,	//	[\r\n\t\s]+
	dummy =1000000
};

enum class type_token {
	keyword,
	cpp_keyword,
	double_literal,
	int_literal,
	char_literal,
	string_literal,
	include_file,
	identifier,
	delimiter,
	dummy = 1000000,
};


type_token to_type_token(token t);
int token_to_number(token t);
std::string nameof(type_token t);
std::map<std::string, token> get_token_map();