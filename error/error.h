#pragma once
#include "errcode.h"
#include "../basic/basic.h"

#define define_new_error_type(type,error_prefix)\
class type##_error : public std::exception {\
public:\
	explicit  type##_error(const char* message): msg_(prefix+message){}\
	template<class ..._STR>explicit type##_error(_STR... str)\
		{strappend(str...);}\
	explicit  type##_error(const std::string& message): msg_(prefix + message) {} \
	virtual ~type##_error() throw () {}\
	virtual const char* what() const throw () {return msg_.c_str();}\
protected:\
	std::string prefix= error_prefix;\
	std::string msg_;\
	template<class _NOW,class ..._STR>void strappend(_NOW now,_STR... str)\
		{msg_+=now;}\
	template<class _NOW>void strappend(_NOW now){msg_+=now;}\
}

define_new_error_type(cpp, "ERROR ON PREPROCESSING: ");

define_new_error_type(parse, "ERROR ON PARSING: ");

define_new_error_type(lex, "ERROR ON LEXICAL ANALYSISING: ");
define_new_error_type(type, "ERROR ON TYPE CHECK: ");
define_new_error_type(scope, "ERROR ON SCOPE CHECK: ");

#undef define_new_error_type