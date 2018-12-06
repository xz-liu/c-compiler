#pragma once
#include "../basic/basic.h"
#include "../lex/lex.h"

struct cpp {
	cpp( std::string const&file_name);

	std::string result( );

};