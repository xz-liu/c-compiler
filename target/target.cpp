#include "target.h"

std::string target::return_value_of(int curr_call_id) {
	return return_value_names[sym.func_list[sym.root_scope->get_index(curr_call_id, data)].function_scope];
}

void target::work() {
	for (int i = 0; i < sym.quats.size(); i++) {
		symbols::quat &qt = sym.quats[i];
		auto &qv = qt.first.second;
		auto hscope = qt.second;
		auto op = qt.first.first;
		switch (op) {
		case quat_op::input: {
			cseg += "xor edx,edx\nmov ah,1\nint 21h\nmov dl,al\nmov " + name_of(qv[0], hscope) + ",edx\n";
		}break;
		case quat_op::output: {
			cseg += "mov edx," + name_of(qv[0], hscope) + "\nmov ah,5\nint 21h\n";
		}break;
		case quat_op::func:
		{
			curr_funcdef_id = qv[0];
			cseg += get_name_of_now(qv[0], data) + " PROC\n";
			if (get_name_of_now(qv[0], data) == "main") {
				cseg += ".startup\n";
			}
			//insert_param(hscope);

		}break;
		case quat_op::funcparam: {
			name_of(qv[0], hscope);
		}break;
		case quat_op::funcend:
		{
			if(!has_return_command[curr_funcdef_id]) {
				cseg += "ret\n";
			}
			cseg += get_name_of_now(qv[0], data) + " ENDP\n";
		}break;
		case quat_op::retval:{
			has_return_command[curr_funcdef_id] = true;
			auto v= insert_retval(hscope);
			auto n = name_of(qv[2],hscope);
			cseg += "mov eax," + n + "\nmov " + v + ",eax\n";
			cseg += "ret\n";
		}break;
		case quat_op::ret: {
			has_return_command[curr_funcdef_id] = true;
			cseg += "ret\n";
		}break;
		case quat_op::call: {
			curr_call_id = qv[0];
			curr_push_pos = 0;
		}break;
		case quat_op::callend: {
			auto func_retval = sym.func_list[sym.root_scope->get_index(curr_call_id, data)].return_type;
			cseg += "call " + get_name_of_now(curr_call_id, data) + "\n";
			if (func_retval != symbols::void_type) {
				auto rto = name_of(qv[0], hscope);
				auto rfrom = return_value_of(curr_call_id);
				cseg += "mov eax," + rfrom + "\nmov " + rto + ",eax\n";
			}
		}break;
		case quat_op::push: {
			auto &func = sym.func_list[sym.root_scope->get_index(curr_call_id, data)];
			auto rto = name_of(func.id_pos[curr_push_pos++], func.function_scope);
			auto rfrom = name_of(qv[0],hscope);
			cseg += "mov eax," + rfrom + "\nmov " + rto + ",eax\n";
		}break;
		case  quat_op::structdef: {
			int index = sym.get_id_index(qv[0], hscope);
			struct_def += get_name_of_now(qv[0], data) + " STRUCT\n";
			auto &str = sym.struct_list[index];
			for(auto &&v :str.id_to_member) {
				struct_def += v.first + " ";
				auto ty = str.members[v.second];
				switch (sym.get_type_size({ty.first,0 })) {
				case 1:struct_def += "BYTE "; break;
				case 2:struct_def += "WORD "; break;
				case 4: struct_def += "DWORD "; break;
				case 8:struct_def += "QWORD "; break;
				}
				if (ty.second >= 1) {
					//array
					struct_def += std::to_string(ty.second) + " DUP(?)\n";
				} else {
					struct_def += " ?\n";
				}
			}
			struct_def += get_name_of_now(qv[0], data) + " ENDS\n";

		}break;
		case quat_op::label:
		{
			cseg += "LABEL_" + std::to_string(qv[0]) + ":\n";
		}break;
		case quat_op::jmp:
		{
			cseg += "jmp LABEL_" + std::to_string(qv[0]) + "\n";
		}break;
		case quat_op::assign:
		{
			switch (qv[2]) {
			case assign_type::normal:
			case assign_type::init:
			{
				auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope);
				cseg += "mov eax," + rhs + "\nmov " + lhs + ",eax\n";
			}break;
			}
		}break;
		case quat_op::btrue:
		{
			auto v = name_of(qv[1], hscope);
			cseg += "mov eax," + v + "\nand eax,eax\njnz LABEL_" + std::to_string(qv[0])+"\n";
		}break;
		case quat_op::bfalse:
		{
			auto v = name_of(qv[1], hscope);
			cseg += "mov eax," + v + "\nand eax,eax\njz LABEL_" + std::to_string(qv[0]) + "\n";
		}break;
		case quat_op::add: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			auto ty = sym.get_var_type(qv[0], hscope);
			switch (ty.first) {
			case symbols::int32:
				cseg += "mov eax," + lhs + "\nadd eax," + rhs + "\nmov " + to + ",eax\n";
				break;
			case symbols::float32:
			case symbols::float64:
				cseg += "fld " + lhs + "\nfld " + rhs + "\nfadd\nfst " + to + "\n";
				break;
			}
		} break;
		case quat_op::sub:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			auto ty = sym.get_var_type(qv[0], hscope);
			switch (ty.first) {
			case symbols::int32:
				cseg += "mov eax," + lhs + "\nsub eax," + rhs + "\nmov " + to + ",eax\n";
				break;
			case symbols::float32:
			case symbols::float64:
				cseg += "fld " + lhs + "\nfld " + rhs + "\nfsub\nfst " + to + "\n";
				break;
			}
		} break;
		case quat_op::mul:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			auto ty = sym.get_var_type(qv[0], hscope);
			switch (ty.first) {
			case symbols::int32:
				cseg += "mov eax," + lhs + "\nimul eax," + rhs + "\nmov " + to + ",eax\n";
				break;
			case symbols::float32:
			case symbols::float64:
				cseg += "fld " + lhs + "\nfld " + rhs + "\nfmul\nfst " + to + "\n";
				break;
			}
		} break;
		case quat_op::div: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			auto ty = sym.get_var_type(qv[0], hscope);
			switch (ty.first) {
			case symbols::int32:
				cseg += "mov eax," + lhs + "\nidiv eax," + rhs + "\nmov " + to + ",eax\n";
				break;
			case symbols::float32:
			case symbols::float64:
				cseg += "fld " + lhs + "\nfld " + rhs + "\nfdiv\nfst " + to + "\n";
				break;
			}
		} break;
		case quat_op::mod:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov edx,0\nmov eax," + lhs + "\nmov ecx," + rhs + "\nidiv ecx\nmov " + to + ",edx\n";
		}  break;
		case quat_op::shl: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\nmov ecx," + rhs + "\nshl eax,cl\nmov " + to + ",eax\n";
		}break;
		case quat_op::shr: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\nmov ecx," + rhs + "\nshr eax,cl\nmov " + to + ",eax\n";
		}  break;
		case quat_op::e: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\nsub eax," + rhs + "\nnot eax\nmov " + to + ",eax\n";
		}break;
		case quat_op::ne:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\nsub eax," + rhs + "\nmov " + to + ",eax\n";
		} break;
		case quat_op::ge: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\nsub eax," + rhs + "\n";
			cseg += "shr eax,31\nnot eax\nmov " + to + ",eax\n";
		} break;
		case quat_op::le:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\nsub eax," + lhs + "\n";
			cseg += "shr eax,31\nnot eax\nmov " + to + ",eax\n";
		} break;
		case quat_op::l:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\nsub eax," + rhs + "\n";
			cseg += "shr eax,31\nmov " + to + ",eax\n";
		}  break;
		case quat_op::g:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\nsub eax," + lhs + "\n";
			cseg += "shr eax,31\nmov " + to + ",eax\n";
		} break;
		case quat_op::bxor: {
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\nxor eax," + lhs + "\nmov " + to + ",eax\n";
		} break;
		case quat_op::bor:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\nor eax," + lhs + "\nmov " + to + ",eax\n";
		}  break;
		case quat_op::band:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\nand eax," + lhs + "\nmov " + to + ",eax\n";
		} break;
		case quat_op::lor:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\nor eax," + lhs + "\nmov " + to + ",eax\n";
		} break;
		case quat_op::land:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\nmov ebx," + lhs+"\n";
			cseg += R"(
			test eax,eax
			mov ecx,eflags
			test ebx,ebx
			and ecx,eflags
			and ecx,0040h  ;ZF == 0x0040
			not ecx
			)";//ZF == 0x0040
			cseg += "mov " + to + ",ecx\n";
		} break;
		case quat_op::inc: 
		{
			auto v = name_of(qv[0], hscope);
			cseg += "inc " + v + "\n";
		}break;
		case quat_op::dec:
		{
			auto v = name_of(qv[0], hscope);
			cseg += "dec " + v + "\n";
		} break;
		case quat_op::bnot:
		{
			auto v = name_of(qv[0], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + v + "\nnot eax\nmov " + to + ",eax\n";
		}  break;
		case quat_op::lnot:
		{// not true
			auto v = name_of(qv[0], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + v + "\nnot eax\nmov " + to + ",eax\n";
		}  break;
		case quat_op::pos: 
		{

			auto v = name_of(qv[0], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + v + "\nmov " + to + ",eax\n";
		} break;
		case quat_op::neg: 
		{

			auto v = name_of(qv[0], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + v + "\nneg eax\nmov " + to + ",eax\n";
		} break;
			//before type check 
		case quat_op::type_cast: 
		{
			auto v = name_of(qv[0], hscope), to = name_of(qv[2], hscope);
			auto dty = qv[1], sty = sym.get_var_type(qv[0], hscope).first;
			if(sym.is_float(dty)) {
				cseg += "fild " + v + "\nfst " + to + "\n";
			}
			else {
				if(sym.is_float(sty)) {
					cseg += "fld " + v + "\nfist eax\n";
				}else {
					cseg += "mov eax," + v + "\n";
				}
				switch (dty) {
				case symbols::int32:
				case symbols::int64:
				case symbols::uint32:
				case symbols::uint64:
					cseg += "mov " + to + ",eax\n";
					break;
				case symbols::uint16:
				case symbols::int16:
					cseg += "mov " + to + ",ax\n";
					break;
				case symbols::char8:
				case symbols::uchar8:
					cseg += "mov " + to + ",al\n";
					break;
				}
			}
		} break;
		}
	}
}
std::string target::insert_retval( scope::handle_scope h_curr) {
	auto real_scope = h_curr->find_handle_of_id("$return_value");
	int index = real_scope->id_map["$return_value"].second;
	std::string vname = "$return_value_" + std::to_string(index);
	dseg += vname + " ";
	auto ty = sym.var_list[index].first.first;
	switch (sym.get_type_size({ ty.first,0 })) {
	case 1:dseg += "BYTE "; break;
	case 2:dseg += "WORD "; break;
	case 4: dseg += "DWORD "; break;
	case 8:dseg += "DWORD "; break;
	}
	if (ty.second >= 1) {
		//array
		dseg += std::to_string(ty.second) + " DUP(?)\n";
	} else {
		dseg += " ?\n";
	}
	return_value_names.emplace(real_scope, vname);
	return vname;
}
std::string target::name_of(int id, scope::handle_scope h_curr) {
	auto r_scope = h_curr;
	while (r_scope) {
		auto it = id_name.find({ id,r_scope });
		if (it != id_name.end())return it->second;
		r_scope = r_scope->father;
	}
	auto it_const = const_name.find(id);
	if (it_const != const_name.end())return it_const->second;
	if (sym.is_const(id)) {
		std::string cname = "CONST_" + std::to_string(id);
		auto ty = sym.get_const_type(id);
		switch (ty.first) {
		case symbols::int64:
		{
			dseg += cname + " DWORD " + get_name_of_now(id, data) + "\n";
		}break;
		case symbols::char8:
		{
			if (ty.second >= 1) {
				dseg += cname + " BYTE \"" + get_name_of_now(id, data) + "\",0\n";
			} else {
				dseg += cname + " BYTE '" + get_name_of_now(id, data) + "'\n";
			}
		}break;
		case symbols::float64:
		{
			dseg += cname + " DWORD " + get_name_of_now(id, data) + "\n";
		}
		}
		const_name.emplace(id, cname);
		return  cname;
	} 
	else 
	{
		auto real_scope = h_curr->find_handle_of_id(id, data);
		int index =real_scope->get_index(id, data);
		std::string vname = get_name_of_now(id, data) + "_" + std::to_string(index);
		dseg += vname + " ";
		auto ty = sym.var_list[index].first.first;
		switch (sym.get_type_size({ ty.first,0 })) {
		case 1:dseg += "BYTE "; break;
		case 2:dseg += "WORD "; break;
		case 4: dseg += "DWORD "; break;
		case 8:dseg += "DWORD "; break;
		}
		if (ty.second >= 1) {
			//array
			dseg += std::to_string(ty.second) + " DUP(?)\n";
		} 
		else {
			dseg += " ?\n";
		}
		id_name.insert(std::make_pair(std::make_pair( id,real_scope), vname));
		return vname;
	}
}

target::target(lex_data const & d, symbols & sy)
	:sym(sy), data(d) {
	
	dseg = ".data\n";
	cseg_begin = R"(
.code
)";
	cseg_end = R"(
END main
		)";
	incl = R"(includelib kernel32.lib  
.model flat,stdcall 
)";
	work();
}