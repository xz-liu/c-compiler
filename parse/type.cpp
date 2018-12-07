#include "type.h"

std::string & get_quat_op_name(quat_op op) {
	static std::map<quat_op, std::string> mp{
		{quat_op::label , "label " },
		{quat_op::jmp, "jmp" },
		{quat_op::btrue , "btrue " },
		{quat_op::bfalse, "bfalse" },
		{quat_op::newvar , "newvar " },
		{quat_op::func , "func " },
		{quat_op::funcparam , "funcparam " },
		{quat_op::funcend, "funcend" },
		{quat_op::structdef, "structdef" },
		{quat_op::structend, "structend" },
		{quat_op::cblock, "cblock" },
		{quat_op::cend, "cend" },
		{quat_op::push , "push " },
		{quat_op::call, "call" },
		{quat_op::callend,"callend"},
		{quat_op::ret, "ret" },
		{quat_op::retval, "retval" },
		{quat_op::arrayval, "arrayval" }, 
		{quat_op::structval , "structval " },
		{quat_op::add, "add" },
		{quat_op::sub, "sub" },
		{quat_op::mul, "mul" },
		{quat_op::div, "div" }, 
		{quat_op::mod , "mod " },
		{quat_op::shl, "shl" },
		{quat_op::shr, "shr" },
		{quat_op::e, "e" },
		{quat_op::ne, "ne" },
		{quat_op::ge, "ge" }, 
		{quat_op::le, "le" }, 
		{quat_op::l, "l" },
		{quat_op::g, "g" },
		{quat_op::bxor, "bxor" },
		{quat_op::bor, "bor" },
		{quat_op::band, "band" },
		{quat_op::lor, "lor" },
		{quat_op::land, "land" },
		{quat_op::inc , "inc " },
		{quat_op::dec, "dec" }, 
		{quat_op::bnot, "bnot" }, 
		{quat_op::lnot, "lnot" },
		{quat_op::pos, "pos" }, 
		{quat_op::neg, "neg" },
		{quat_op::assign, "assign" },
		{quat_op::initlst, "initlst" },
		{quat_op::initlstend, "initlstend" },
		{quat_op::initlstitem, "initlstitem" },
	};
	return mp[op];
}
std::string get_label_type_name(labels::label_type ty) {
	std::map<labels::label_type,std::string> mp{
		{labels::loop_begin, "loop_begin"},
		{labels::loop_end, "loop_end"},
		{labels::for_suf, "for_suf"},
		{labels::for_begin, "for_begin"},
		{labels::if_end, "if_end"},
		{labels::else_end, "else_end"},
		{labels::user, "user"},
		{labels::switch_end, "switch_end"},
		{labels::case_end, "case_end"},
		{labels::fail, "fail"},
	};
	return mp[ty];
}
std::string get_name_of_now(int now,lex_data const & data) {
	if (now < 0)return  "{@False}";
	if(now>=data.lex_result.size()) {
		return std::string("tmp_") + std::to_string(now - data.lex_result.size());
	}
	switch (data.get_type_token(now)) {
	case type_token::string_literal:return data.get_str(now);
	case type_token::int_literal:return std::to_string(data.get_int(now));
	case type_token::char_literal:return std::to_string(data.get_char(now));
	case type_token::double_literal:return std::to_string(data.get_double(now));
	case type_token::identifier:return (data.get_id(now));
	case type_token::type: return get_type_name(now, data);
	default: return token_name[token(data.lex_result[now].second)];
	}
	return "{@Failed}";
}
std::string get_assign_type_name(int now, lex_data const &data) {
	switch (now) {
		case assign_type::normal : return "normal";
		case assign_type::add : return "add";
		case assign_type::sub : return "sub";
		case assign_type::mul : return "mul";
		case assign_type::div : return "div";
		case assign_type::mod : return "mod";
		case assign_type::shl : return "shl";
		case assign_type::shr : return "shr";
		case assign_type::and : return "and";
		case assign_type::or : return "or";
		case assign_type::xor : return "xor";
		case assign_type::init : return "init";
	}
}
std::string get_type_name(int now, lex_data const &data) {
	if(types::is_struct(now)) {
		return "{@struct}" + get_name_of_now(types::struct_data_rank(now), data);
	}
	switch (now) {
		case types::none : return "none";
		case types::void_type : return "void_type";
		case types::int16 : return "int16";
		case types::int32 : return "int32";
		case types::int64 : return "int64";
		case types::uint16 : return "uint16";
		case types::uint32 : return "uint32";
		case types::uint64 : return "uint64";
		case types::char8 : return "char8";
		case types::uchar8 : return "uchar8";
		case types::float32 : return "float32";
		case types::float64 : return "float64";
		case types::type_struct : return "type_struct";
	}
}

void types::debug_single_quat(
	parser::quat_type const & qt, 
	labels const & label_lst,
	lex_data const & data
) {
	using std::cout;
	using std::endl;
	cout << get_quat_op_name(qt.first) << "\t:";
	switch (qt.first) {
	case quat_op::label:
	case quat_op::jmp:
		cout << get_label_type_name(label_lst[qt.second[0]].second) << "{" << qt.second[0] << "}" << endl;
		break;
	case quat_op::btrue:
	case quat_op::bfalse:
		cout << get_label_type_name(label_lst[qt.second[0]].second)
			<< "{" << qt.second[0] << "} ,"
			<< get_name_of_now(qt.second[1], data) << endl;
		break;
	case quat_op::newvar:
		cout << get_name_of_now(qt.second[0], data) << ","
			<< get_type_name(qt.second[1], data) << ","
			<< " [ " << get_name_of_now(qt.second[2], data) << " ] " << endl;
		break;
	case quat_op::func:
		cout << get_name_of_now(qt.second[0], data) << ","
			<< get_type_name(qt.second[1], data) << endl;
		break;
	case quat_op::funcparam:
		cout << get_name_of_now(qt.second[0], data) << ","
			<< get_type_name(qt.second[1], data) << ","
			<< " [ " << qt.second[2] << " ] " << endl;
		break;
	case quat_op::funcend:
	case quat_op::structdef:
	case quat_op::structend:
		cout << get_name_of_now(qt.second[0], data) << endl;
		break;
	case quat_op::cblock:
	case quat_op::cend:
		break;
	case quat_op::push:
		cout << get_name_of_now(qt.second[0], data) << endl;
		break;
	case quat_op::call:
	case quat_op::callend:
		cout << get_name_of_now(qt.second[0], data) << endl;
		break;
	case quat_op::ret: break;
	case quat_op::retval:
		cout << get_name_of_now(qt.second[2], data) << endl;
		break;
	case quat_op::arrayval:
	case quat_op::structval:
	case quat_op::add:
	case quat_op::sub:
	case quat_op::mul:
	case quat_op::div:
	case quat_op::mod:
	case quat_op::shl:
	case quat_op::shr:
	case quat_op::e:
	case quat_op::ne:
	case quat_op::ge:
	case quat_op::le:
	case quat_op::l:
	case quat_op::g:
	case quat_op::bxor:
	case quat_op::bor:
	case quat_op::band:
	case quat_op::lor:
	case quat_op::land:
		cout << get_name_of_now(qt.second[0], data) << ","
			<< get_name_of_now(qt.second[1], data) << ","
			<< get_name_of_now(qt.second[2], data) << endl;
		break;
	case quat_op::inc:
	case quat_op::dec:
		cout << get_name_of_now(qt.second[0], data) << endl;
		break;
	case quat_op::bnot:
	case quat_op::lnot:
	case quat_op::pos:
	case quat_op::neg:
		cout << get_name_of_now(qt.second[0], data) << ","
			<< get_name_of_now(qt.second[2], data) << endl;
		break;
	case quat_op::assign:
		cout << get_name_of_now(qt.second[0], data) << ","
			<< get_name_of_now(qt.second[1], data) << ","
			<< get_assign_type_name(qt.second[2], data) << endl;
		break;
	case quat_op::initlst:
	case quat_op::initlstend:
	case quat_op::initlstitem:
		cout << get_name_of_now(qt.second[0], data) << endl;
		break;
	}
	
}
void types::debug_quat(std::vector<parser::quat_type> const & quats,
	labels const & label_lst,
	lex_data const & data) {
	for (auto && qt : quats) {
		debug_single_quat(qt, label_lst, data);
	}
}
