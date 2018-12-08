#include "type.h"
#include "../error/error.h"

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
	std::map<labels::label_type, std::string> mp{
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
std::string get_name_of_now(int now, lex_data const & data) {
	if (now < 0)return  "{@False}";
	if (now >= data.lex_result.size()) {
		return std::string("{@Temp_") + std::to_string(now - data.lex_result.size())+"}";
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
std::string get_assign_type_name(int now) {
	switch (now) {
	case assign_type::normal: return "normal";
	case assign_type::add: return "add";
	case assign_type::sub: return "sub";
	case assign_type::mul: return "mul";
	case assign_type::div: return "div";
	case assign_type::mod: return "mod";
	case assign_type::shl: return "shl";
	case assign_type::shr: return "shr";
	case assign_type::and: return "and";
	case assign_type:: or : return "or";
	case assign_type::xor: return "xor";
	case assign_type::init: return "init";
	}
}
std::string get_type_name(int now, lex_data const &data) {
	if (symbols::is_struct(now)) {
		return "{@struct}" + get_name_of_now(symbols::struct_index(now), data);
	}
	switch (now) {
	case symbols::none: return "none";
	case symbols::void_type: return "void_type";
	case symbols::int16: return "int16";
	case symbols::int32: return "int32";
	case symbols::int64: return "int64";
	case symbols::uint16: return "uint16";
	case symbols::uint32: return "uint32";
	case symbols::uint64: return "uint64";
	case symbols::char8: return "char8";
	case symbols::uchar8: return "uchar8";
	case symbols::float32: return "float32";
	case symbols::float64: return "float64";
	case symbols::struct_type: return "type_struct";
	}
}

std::string get_type_name(symbols::type now, lex_data const& data) {
	if (now.second) {
		return get_type_name(now.first, data) + "[" + std::to_string(now.second) + "]";
	}
	return get_type_name(now.first, data);
}

void symbols::debug_single_quat(
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
		cout << endl;
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
			<< get_assign_type_name(qt.second[2]) << endl;
		break;
	case quat_op::initlst:
	case quat_op::initlstend:
		cout << get_name_of_now(qt.second[0], data) << endl;
		break;
	case quat_op::initlstitem:
		cout << get_name_of_now(qt.second[0], data) << ","
			<< get_name_of_now(qt.second[1], data) << endl;
		break;
	}

}
void symbols::debug_quat(std::vector<parser::quat_type> const & quats,
	labels const & label_lst,
	lex_data const & data) {
	for (auto && qt : quats) {
		debug_single_quat(qt, label_lst, data);
	}
}


int symbols::binocular_type_cast(type ta, type tb, quat_op op) {
	int tya = ta.first, tyb = tb.first;
	if (is_void(tya) || is_void(tyb))
		throw type_error("No op for void type");
	if (op == quat_op::structval) {
		if (is_struct(tya) && !ta.second) {
			return no_type_cast;
		}
		throw type_error("No . op for " + get_type_name(ta, data));
	}
	if (op == quat_op::arrayval) {
		if (!ta.second)
			if (!is_int_or_char(tyb) || tb.second) {
				throw type_error("No [] op for " + get_type_name(tya, data) + "and" + get_type_name(tyb, data));
			}
		return no_type_cast;
	}
	if (is_struct(tya) || is_struct(tyb)) {
		throw type_error("No " + get_quat_op_name(op) + " op for " + get_type_name(tya, data) + "and" + get_type_name(tyb, data));
	}
	if (ta.second == 0 && tb.second == 0) {
		switch (op) {
		case quat_op::mod:
			if (!(is_int_or_char(tya) && is_int_or_char(tyb)))
				throw type_error("No % op for " + get_type_name(tya, data) + " and " + get_type_name(tyb, data));
		case quat_op::add:
		case quat_op::sub:
		case quat_op::mul:
		case quat_op::div:
			return simple_type_cast(tya, tyb);
		case quat_op::shl:
			if (!(is_int_or_char(tya) && is_int_or_char(tyb)))
				throw type_error("No << op for " + get_type_name(tya, data) + " and " + get_type_name(tyb, data));
		case quat_op::shr:
			if (!(is_int_or_char(tya) && is_int_or_char(tyb)))
				throw type_error("No >> op to " + get_type_name(tya, data) + " and " + get_type_name(tyb, data));
			return no_type_cast;
		case quat_op::e:
		case quat_op::ne:
		case quat_op::ge:
		case quat_op::le:
		case quat_op::l:
		case quat_op::g:
			return simple_type_cast(tya, tyb);
		case quat_op::bxor:
		case quat_op::bor:
		case quat_op::band:
			if (!(is_int_or_char(tya) && is_int_or_char(tyb)))
				throw type_error("No &|^ op to " + get_type_name(tya, data) + " and " + get_type_name(tyb, data));
			return simple_type_cast(tya, tyb);
		case quat_op::lor:
		case quat_op::land:
			return  no_type_cast;
		}
	} else throw type_error("No " + get_quat_op_name(op) + " to " + get_type_name(tya, data) + " and " + get_type_name(tyb, data));

	return no_type_cast;
}

void symbols::monocular_type_check(type ty, quat_op op) {
	if (ty.second || !is_basic_type(ty.first) || (op == quat_op::bnot && !is_int_or_char(ty.first))) {
		throw type_error("No " + get_quat_op_name(op) + " to " + get_type_name(ty, data));
	}
}

void symbols::assign_type_check(type lhs, type rhs, int atype) {
	if (!is_basic_type(lhs.first) || !is_basic_type(rhs.first))
		throw type_error("Cannot assign " + get_type_name(rhs, data) + " to " + get_type_name(lhs, data));
	if (lhs.second || rhs.second) {
		if (atype == assign_type::init) {
			if (lhs.first == rhs.first&& rhs.second <= lhs.second) {
				return;
			}
		}
		throw type_error("Cannot assign " + get_type_name(rhs, data) + " to " + get_type_name(lhs, data));
	}
	switch (atype) {
	case assign_type::normal:
	case assign_type::add:
	case assign_type::sub:
	case assign_type::mul:
	case assign_type::div:break;
	case assign_type::mod:
	case assign_type::shl:
	case assign_type::shr:
	case assign_type::and:
	case assign_type:: or :
	case assign_type::xor:
		if (is_int_or_char(lhs.first) && is_int_or_char(rhs.first))return;
	}
	throw type_error("Cannot assign " + get_type_name(rhs, data) + " to " + get_type_name(lhs, data));
}

void throw_scope_error(int id,lex_data const &data,scope::handle_scope h_curr) {
	throw scope_error("In " + h_curr->scope_name + " :" + " undefined symbol ", get_name_of_now(id, data));
}

void symbols::handle_single_quat(parser::quat_type const & qt, lex_data const & data) {
	using std::cout;
	using std::endl;
	switch (qt.first) {
	case quat_op::label:
	case quat_op::jmp:
		quats.push_back(qt);
		break;
	case quat_op::btrue:
	case quat_op::bfalse: {
		int exp = qt.second[1];
		auto handle = h_curr->find_handle_of_id(exp, data);
		if (!handle)throw_scope_error(exp, data, h_curr);
		if(handle->get_type_of_id(exp,data) == scope::variable) {
			if(can_cast_to_bool(var_list[handle->get_index(exp,data)].first)) {
				quats.push_back(qt);
				break;
			}
		}
		throw type_error(get_name_of_now(exp, data) + " is not an exp"); 
		break;
	}
	case quat_op::newvar: {
		int id = qt.second[0], type = qt.second[1], arr = qt.second[2];
		
	}
		/*cout << get_name_of_now(qt.second[0], data) << ","
			<< get_type_name(qt.second[1], data) << ","
			<< " [ " << get_name_of_now(qt.second[2], data) << " ] " << endl;*/
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
		cout << endl;
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
			<< get_assign_type_name(qt.second[2]) << endl;
		break;
	case quat_op::initlst:
	case quat_op::initlstend:
		cout << get_name_of_now(qt.second[0], data) << endl;
		break;
	case quat_op::initlstitem:
		cout << get_name_of_now(qt.second[0], data) << ","
			<< get_name_of_now(qt.second[1], data) << endl;
		break;
	}
	
}

symbols::symbols(std::vector<parser::quat_type> const&unhandled_quats, lex_data const& data)
	:data(data) ,root_scope(std::make_shared<scope>(nullptr,"GLOBAL")){
	h_curr = root_scope;
	
}
