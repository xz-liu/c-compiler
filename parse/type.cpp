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
		{quat_op::type_cast,"type_cast"},
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
		return std::string("{@Temp_") + std::to_string(now - data.lex_result.size()) + "}";
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
		return "{@struct}" + get_name_of_now(symbols::struct_id_pos(now), data);
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
		cout << get_name_of_now(qt.second[0], data)<< ","
		<< qt.second[1] << endl;
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
	case quat_op::type_cast:
		cout << get_name_of_now(qt.second[0], data) << ","
			<< get_type_name(qt.second[1], data) << ","
			<< get_name_of_now(qt.second[2], data) << endl;
	}

}
void symbols::debug_quat(std::vector<parser::quat_type> const & quats,
	labels const & label_lst,
	lex_data const & data) {
	for (auto && qt : quats) {
		debug_single_quat(qt, label_lst, data);
	}
}

void symbols::debug_quat(std::vector<quat> const & quats,
	labels const & label_lst,
	lex_data const & data) {
	for (auto && qt : quats) {
		debug_single_quat(qt, label_lst, data);
	}
}

void symbols::debug_single_quat(quat const & qt, labels const & label_lst, lex_data const & data) {
	debug_single_quat(qt.first, label_lst, data);
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
	if (lhs.second || rhs.second) {
		if (atype == assign_type::init) {
			if (same_cat_type(lhs.first, rhs.first) && rhs.second <= lhs.second) {
				return;
			}
		}
		throw type_error("Cannot assign array " + get_type_name(rhs, data) + " to " + get_type_name(lhs, data));
	}
	if (!is_basic_type(lhs.first) || !is_basic_type(rhs.first)) {
		if (lhs.first == rhs.first&& atype == assign_type::init)return;

		throw type_error("Cannot assign !basic type " + get_type_name(rhs, data) + " to " + get_type_name(lhs, data));
	}
	switch (atype) {
	case assign_type::normal:
	case assign_type::add:
	case assign_type::sub:
	case assign_type::mul:
	case assign_type::init:
	case assign_type::div:return;
	case assign_type::mod:
	case assign_type::shl:
	case assign_type::shr:
	case assign_type::and:
	case assign_type:: or :
	case assign_type::xor:
		if (is_int_or_char(lhs.first) && is_int_or_char(rhs.first))return;
	}
	throw type_error("Cannot assign " + get_assign_type_name(atype) + " " + get_type_name(rhs, data) + " to " + get_type_name(lhs, data));
}

void throw_scope_error(int id, lex_data const &data, scope::handle_scope h_curr, std::string const& def) {
	throw scope_error("In " + h_curr->scope_name + " :  " + def + " symbol <" + get_name_of_now(id, data) + ">");
}
void symbols::handle_single_quat(parser::quat_type const & qt, lex_data const & data, int quat_pos) {
#define get_var_or_const_type(ty,id) \
	if (is_const(id, data)) {\
		ty = get_const_type(id, data);\
	} else {\
		auto handle = h_curr->find_handle_of_id(id, data);\
		if (!handle)throw_scope_error(id, data, h_curr, "undefined");\
		if (handle->get_type_of_id(id, data) != scope::variable)\
			throw type_error("symbol mismatch, need variable or constexpr :" + get_name_of_now(id, data));\
		ty = var_list[handle->get_index(id, data)].first.first;\
	}\

	auto push_quat = [&](parser::quat_type q) {
		quats.push_back(make_pair(q, h_curr));
		//quats.emplace_back(q, h_curr);
	};

#define type_cast(ty2,size2,id_to_cast,islvalue,id_scope,tvc)\
	id_scope->insert_new_id(get_name_of_now(tvc, data), new_var(ty2, size2, islvalue, id_scope), scope::variable);\
	push_quat(std::make_pair(quat_op::type_cast,std::array<int,3>{id_to_cast, ty2, tvc})) ;\

	switch (qt.first) {
	case quat_op::label:
	case quat_op::jmp:
		push_quat(qt);
		break;
	case quat_op::btrue:
	case quat_op::bfalse:
	{
		int exp = qt.second[1];
		if (is_const(exp, data)) {
			if (get_const_type(exp, data).second)
				throw type_error("array cannot convert to bool");
			push_quat(qt);
			break;
		} else {
			auto handle = h_curr->find_handle_of_id(exp, data);
			if (!handle)throw_scope_error(exp, data, h_curr, "undefined");
			if (handle->get_type_of_id(exp, data) == scope::variable) {
				if (can_cast_to_bool(var_list[handle->get_index(exp, data)].first.first)) {
					push_quat(qt);
					break;
				}
			}
			throw type_error(get_name_of_now(exp, data) + " is not an exp");
		}
	}break;
	case quat_op::newvar:
	{
		int id = qt.second[0], ty = qt.second[1], arr = qt.second[2];
		auto h_id = h_curr->find_handle_of_id(id, data);
		if (h_id == h_curr)throw_scope_error(id, data, h_curr, "redefined");
		if (is_struct(ty)) {
			auto h_type = h_curr->find_handle_of_id(struct_id_pos(ty), data);
			if (!h_type)throw_scope_error(struct_id_pos(ty), data, h_curr, "undefined");
		}
		if (arr <= 0) arr = 0;
		else arr = data.get_int(arr);
		h_curr->insert_new_id(get_name_of_now(id, data), new_var(ty, arr, true, h_curr), scope::variable);
		if (curr_struct >= 0) {
			struct_list[curr_struct].add_member(get_name_of_now(id, data), { ty,arr }, *this);
		}
	}
	break;
	case quat_op::func:
	{
		int id = qt.second[0], ty = qt.second[1];
		if (h_curr->find_handle_of_id(id, data)) {
			throw_scope_error(id, data, h_curr, "redefined");
		}
		if (is_struct(ty)) {
			auto h_type = h_curr->find_handle_of_id(struct_id_pos(ty), data);
			if (!h_type)throw_scope_error(struct_id_pos(ty), data, h_curr, "undefined");

		}
		h_curr->insert_new_id(get_name_of_now(id, data), new_func(ty, quat_pos), scope::func);
		h_curr = h_curr->create_new_scope("function " + get_name_of_now(id, data));
		push_quat(qt);
	}
	break;
	case quat_op::funcparam:
	{
		int id = qt.second[0], ty = qt.second[1], pt = qt.second[2];
		if (h_curr->find_handle_of_id(id, data))
			throw_scope_error(id, data, h_curr, "redefined");
		if (is_struct(ty)) {
			auto h_type = h_curr->find_handle_of_id(struct_id_pos(ty), data);
			if (!h_type)throw_scope_error(struct_id_pos(ty), data, h_curr, "undefined");
		}
		h_curr->insert_new_id(get_name_of_now(id, data), new_var(ty, pt, true, h_curr), scope::variable);
		func_list[func_list.size() - 1].add_param(id, ty, pt, *this);
	}
	break;
	case quat_op::funcend:
	{
		h_curr = h_curr->father;
		push_quat(qt);
		break;
	}
	//incomplete !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	case quat_op::structdef: 
	{
		int id = qt.second[0];
		if (h_curr->find_handle_of_id(id, data))
			throw_scope_error(id, data, h_curr, "redefined");
		push_quat(qt);
		curr_struct = new_struct(qt.second[1]);
		h_curr->insert_new_id(get_name_of_now(id, data), curr_struct, scope::struct_type);
		h_curr = h_curr->create_new_scope((qt.second[1]?"union ":"struct ") + get_name_of_now(id, data));
		break;
	}
	case quat_op::structend:
	{
		curr_struct = -1;
		h_curr = h_curr->father;
	}		break;
	case quat_op::cblock:
	{
		h_curr = h_curr->create_new_scope("_");
	}break;
	case quat_op::cend:
	{
		h_curr = h_curr->father;
	}break;
	case quat_op::push:
	{
		int id = qt.second[0];
		type ty;
		get_var_or_const_type(ty, id);
		auto param_ty = func_list[curr_call_id].params[curr_push_order++];
		if (!ty.second && !param_ty.second) {
			if (ty.first != param_ty.first) {
				assign_type_check(param_ty, ty, assign_type::init);
				type_cast(param_ty.first, ty.second, id, false, h_curr, tmp_var_cnt);
				push_quat({ quat_op::push, std::array<int, 3> { tmp_var_cnt, 0, 0 } });
				tmp_var_cnt++;
			} else { push_quat(qt); }
		} else if (ty.second&& param_ty.second) {
			if (ty.first != param_ty.first)throw type_error("param type mismatch : cannot convert array of types");
			push_quat(qt);
		} else {
			throw type_error("param type mismatch : cannot convert with arrays and vars");
		}
	}break;
	case quat_op::call:
	{
		int id = qt.second[0];
		auto handle = h_curr->find_handle_of_id(id, data);
		if (!handle)throw_scope_error(id, data, h_curr, "undefined");
		if (handle->get_type_of_id(id, data) != scope::func)
			throw type_error("call op used on symbol " + get_name_of_now(id, data));
		curr_call_id = handle->get_index(id, data);
		curr_push_order = 0;
		push_quat(qt);
	}break;
	case quat_op::callend:
	{
		int id = qt.second[0];
		h_curr->insert_new_id(get_name_of_now(id, data),
			new_var(func_list[curr_call_id].return_type, 0, false, h_curr), scope::variable);
		push_quat(qt);
	}break;
	case quat_op::ret:
	{
		int func_type = func_list[func_list.size() - 1].return_type;
		if (func_type != void_type)throw type_error("function needs return value");
	}break;
	case quat_op::retval:
	{
		int func_type = func_list[func_list.size() - 1].return_type;
		if (func_type == void_type)throw type_error("function cannot return value");
		int id = qt.second[2];
		type ty;
		get_var_or_const_type(ty, id);
		if (ty.second)throw type_error("cannot return an array");
		if (ty.first != func_type) {
			if (is_basic_type(ty.first) && is_basic_type(func_type)) {
				type_cast(func_type, 0, id, false, h_curr, tmp_var_cnt);
				tmp_var_cnt++;
			} else throw type_error("cannot convert struct types");
		}
		push_quat(qt);
	}break;
	case quat_op::arrayval:
	{
		int id1 = qt.second[0], id2 = qt.second[1], idres = qt.second[2];
		type ty1, ty2;
		get_var_or_const_type(ty1, id1);
		get_var_or_const_type(ty2, id2);
		if (!ty1.second || ty2.second || !is_int_or_char(ty2.first)) {
			throw type_error("array subscription with wrong param :" + get_type_name(ty1.first, data) + " , " + get_type_name(ty2.first, data));
		}
		h_curr->insert_new_id(get_name_of_now(idres, data), new_var(ty1.first, 0, true, h_curr), scope::variable);
		push_quat(qt);

	}break;
	case quat_op::structval:
	{
		int id1 = qt.second[0], id2 = qt.second[1], idres = qt.second[2];
		type ty1, tyres;
		get_var_or_const_type(ty1, id1);
		if (!is_struct(ty1.first) || ty1.second)
			throw type_error(". operator needs struct");
		int index1 = root_scope->get_index(struct_id_pos(ty1.first), data);

		int memb = struct_list[index1].find_member(get_name_of_now(id2, data));
		if (memb < 0) {
			throw_scope_error(id2, data, h_curr, "undefined");
		}
		tyres = struct_list[index1].members[memb];
		h_curr->insert_new_id(get_name_of_now(idres, data), new_var(tyres.first, tyres.second, true, h_curr), scope::variable);
		push_quat(qt);
	}break;
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
	{
		int id1 = qt.second[0], id2 = qt.second[1], idres = qt.second[2];
		type ty1, ty2, tyres;
		get_var_or_const_type(ty1, id1);
		get_var_or_const_type(ty2, id2);
		int cast = binocular_type_cast(ty1, ty2, qt.first);
		switch (cast) {
		case tya_to_tyb:
		{
			type_cast(ty2.first, ty2.second, id1, false, h_curr, tmp_var_cnt);
			push_quat({ qt.first, {tmp_var_cnt,id2,idres} });
			tyres = ty2;
			tmp_var_cnt++;
		}
		case tyb_to_tya:
		{
			type_cast(ty1.first, ty1.second, id2, false, h_curr, tmp_var_cnt);
			push_quat({ qt.first,{ id1,tmp_var_cnt,idres } });
			tyres = ty1;
			tmp_var_cnt++;
		}
		case no_type_cast:
		{
			tyres = ty1;
		}
		}
		h_curr->insert_new_id(get_name_of_now(idres, data), new_var(tyres.first, tyres.second, false, h_curr), scope::variable);
	}break;
	case quat_op::inc:
	case quat_op::dec:
	{
		int id = qt.second[0];
		if (is_const(id, data)) throw type_error("++/-- called to constexpr");
		type ty;
		get_var_or_const_type(ty, id);//just for check scope
		push_quat(qt);
	} break;
	case quat_op::bnot:
	case quat_op::lnot:
	case quat_op::pos:
	case quat_op::neg:
	{
		int id = qt.second[0];
		type ty;
		get_var_or_const_type(ty, id);
		monocular_type_check(ty, qt.first);
		push_quat(qt);
	} break;
	case quat_op::assign:
	{
		int id1 = qt.second[0], id2 = qt.second[1], atype = qt.second[2];
		type ty1, ty2;
		get_var_or_const_type(ty2, id2);
		if (is_const(id1, data))throw type_error("cannot assign value to constexpr.");
		else {
			auto handle = h_curr->find_handle_of_id(id1, data);
			if (!handle) {
				if (is_tmp_var(id1)) {
					h_curr->insert_new_id(get_name_of_now(id1, data), new_var(ty2.first, ty2.second, true, h_curr), scope::variable);
					handle = h_curr;
				} else throw_scope_error(id1, data, h_curr, "undefined");
			}if (handle->get_type_of_id(id1, data) != scope::variable)
				throw type_error("symbol mismatch, need variable or constexpr :" + get_name_of_now(id1, data));
			ty1 = var_list[handle->get_index(id1, data)].first.first;
		}
		int index1 = h_curr->find_handle_of_id(id1, data)->get_index(id1, data);
		if (var_list[index1].first.second) {
			assign_type_check(ty1, ty2, atype);
			push_quat(qt);
		} else throw type_error("cannot assign rvalue : ", get_name_of_now(id1, data));
	} break;
	case quat_op::initlst:
	{
		int id = qt.second[0];
		curr_init_list = new_var(none, 0, false, h_curr);
		h_curr->insert_new_id(get_name_of_now(id, data), curr_init_list, scope::variable);
	}
	break;
	case quat_op::initlstend:
	{
		curr_init_list = -1;
		push_quat(qt);
	}break;
	case quat_op::initlstitem:
	{
		int id = qt.second[1];
		type ty, &tylist = var_list[curr_init_list].first.first;
		get_var_or_const_type(ty, id);
		if (tylist.first == none) {
			tylist.first = ty.first;
			push_quat({ quat_op::initlst,{ qt.second[0], 0, 0 } });
		} else {
			if (tylist.first != ty.first) throw type_error("init list with multiple type");
		}
		var_list[curr_init_list].first.first.second++;
		push_quat(qt);
	}break;
	}

}

symbols::symbols(parser const& p)
	:data(p.data),
	root_scope(std::make_shared<scope>(nullptr, "GLOBAL")),
	curr_call_id(-1), curr_struct(-1), curr_push_order(0), curr_init_list(-1),
	tmp_var_cnt(p.tmp_var_cnt + p.input_data_cnt), tmp_var_begin(p.input_data_cnt) {
	h_curr = root_scope;
	int cnt = 0;
	for (auto &&qt : p.quats) {
		//debug_single_quat(qt, p.label_stack, data);
		handle_single_quat(qt, data, cnt++);
	}
	//curr_call_id, curr_struct, curr_push_order, curr_init_list, tmp_var_cnt;
}

bool struct_def::add_member(std::string const & str, std::pair<int, int> type_id, symbols & sym) {
	if (is_union) {
		member_offset.push_back(0);
	} else { member_offset.push_back(struct_size); }
	int curr_var_size = sym.get_type_size(type_id);
	if (curr_var_size < 0)throw type_error("struct member type error");
	if (is_union)struct_size = std::max(struct_size, curr_var_size);
	else struct_size += curr_var_size;
	if (set_contains(id_to_member, str))return false;
	members.push_back(type_id);
	id_to_member[str] = members.size() - 1;
	return true;
}

void struct_def::debug(symbols & sym) {
	using std::cout; 
	cout << (is_union ? "union" : "struct") << ", size:"
		<<struct_size<<", members cnt:"<<members.size()<< " [" << std::endl;
	for (auto&& x:id_to_member) {
		cout << "\t" << x.first << ":" << get_type_name(members[x.second].first, sym.data)
			<< '[' << members[x.second].second << "], offset=" << member_offset[x.second] << std::endl;
	}
	cout << "]" << std::endl;
}

bool func_def::add_param(int str, int type_id, bool arr, symbols const & sym) {
	if (set_contains(id_to_param, str))return false;
	params.emplace_back(type_id, arr);
	param_offset.push_back(stack_size);
	int curr_var_size = arr ? sym.pointer_size : sym.get_type_size({ type_id,0 });
	if (curr_var_size < 0)throw type_error("function param type error");
	stack_size += curr_var_size;
	id_to_param[str] = params.size() - 1;
	return true;
}

void func_def::debug(symbols & sym) {
	using std::cout;
	cout <<"function" << ", size:"
		<< stack_size << ", params cnt:" << params.size() << " (" << std::endl;
	for (auto&& x : id_to_param) {
		cout<<"\t" << x.first << ":" << get_type_name(params[x.second].first, sym.data)
			<< '[' << params[x.second].second << "], offset=" << param_offset[x.second] << std::endl;
	}
	cout << ")" << std::endl;
}
