#include "target.h"

target::univ_var &target::return_value_of(int curr_call_id) {
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
		case quat_op::output:
		{
			cseg += "invoke StdOut, addr " + name_of(qv[0], hscope) + "\n";
		}break;
		case quat_op::func:
		{
			curr_funcdef_id = qv[0];
			cseg += get_name_of_now(qv[0], data) + " PROC\n";
			//if (get_name_of_now(qv[0], data) == "main") {
			//	cseg += ".startup\n";
			//}
			//insert_param(hscope);

		}break;
		case quat_op::funcparam: {
			name_of(qv[0], hscope,true);
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
				cseg += "mov eax," + rfrom + "\n";
				cseg +="mov " + rto + ",eax\n";
			}
		}break;
		case quat_op::push: {
			auto &func = sym.func_list[sym.root_scope->get_index(curr_call_id, data)];
			auto rto = name_of(func.id_pos[curr_push_pos], func.function_scope);
			auto rfrom = name_of(qv[0],hscope);
			if (func.params[curr_push_pos].second) {
				cseg += "mov eax,offset " + rfrom + "\n";
				cseg += "mov " + rto + ",eax\n";
			}
			else {
				cseg += "mov eax," + rfrom + "\n";
				cseg += "mov " + rto + ",eax\n";
			}
			curr_push_pos++;
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
				default:
				{
					if(sym.is_struct(ty.first)) {
						struct_def += sym.get_struct_name(ty.first)+" ";
					}
				}
				}
				if (ty.second >= 1) {
					//array
					if (sym.is_struct(ty.first))
						struct_def += std::to_string(ty.second) + " DUP(<>)\n";
					else
						struct_def += std::to_string(ty.second) + " DUP(?)\n";
				} else {
					if (sym.is_struct(ty.first))
						struct_def += " <>\n";
					else
						struct_def += " ?\n";
				}
			}
			struct_def += get_name_of_now(qv[0], data) + " ENDS\n";

		}break;
		case quat_op::label:
		{
			cseg += "LABEL_" + std::to_string(qv[0]) + ":nop\n";
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
				int ty = sym.get_type_size(sym.get_var_type(qv[0], hscope));
				std::string reg;
				switch (ty) {
				case 1:reg = "al"; break;
				case 2:reg = "ax"; break;
				case 4:
				case 8:
					reg = "eax"; break;
				}
				cseg += "mov " + reg +"," + rhs + "\n";
				cseg += "mov " + lhs + "," + reg + "\n";
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
			case symbols::int64:
				cseg += "mov eax," + lhs + "\n";
				cseg += "add eax," + rhs + "\n";
				cseg += "mov " + to + ",eax\n";
				break;
			case symbols::float32:
			case symbols::float64:
				cseg += "fld " + lhs + "\n";
				cseg += "fld " + rhs + "\nfadd\n";
				cseg += "fst " + to + "\n";
				break;
			}
		} break;
		case quat_op::sub:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			auto ty = sym.get_var_type(qv[0], hscope);
			switch (ty.first) {
			case symbols::int32:
				cseg += "mov eax," + lhs + "\n";
				cseg += "sub eax," + rhs + "\n";
				cseg += "mov " + to + ",eax\n";
				break;
			case symbols::float32:
			case symbols::float64:
				cseg += "fld " + lhs + "\n";
				cseg += "fld " + rhs + "\nfsub\n";
				cseg += "fst " + to + "\n";
				break;
			}
		} break;
		case quat_op::mul:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			auto ty = sym.get_var_type(qv[0], hscope);
			switch (ty.first) {
			case symbols::int32:
				cseg += "mov eax," + lhs + "\n";
				cseg += "imul eax," + rhs + "\n";
				cseg+="mov " + to + ",eax\n";
				break;
			case symbols::float32:
			case symbols::float64:
				cseg += "fld " + lhs + "\n";
				cseg += "fld " + rhs + "\nfmul\n";
				cseg+="fst " + to + "\n";
				break;
			}
		} break;
		case quat_op::div: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			auto ty = sym.get_var_type(qv[0], hscope);
			switch (ty.first) {
			case symbols::int64:
			case symbols::int32:
				cseg += "mov eax," + lhs + "\n";
				cseg += "cdq\n";
				cseg += "idiv " + rhs + "\n";
				cseg+="mov " + to + ",eax\n";
				break;
			case symbols::float32:
			case symbols::float64:
				cseg += "fld " + lhs + "\n";
				cseg += "fld " + rhs + "\nfdiv\n";
				cseg+="fst " + to + "\n";
				break;
			}
		} break;
		case quat_op::mod:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "\nmov eax," + lhs + "\ncdq\n";
			cseg += "mov ecx," + rhs + "\nidiv ecx\n";
			cseg += "mov " + to + ",edx\n";
		}  break;
		case quat_op::shl: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\n";
			cseg += "mov ecx," + rhs + "\nshl eax,cl\n";
			cseg+="mov " + to + ",eax\n";
		}break;
		case quat_op::shr: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\n";
			cseg += "mov ecx," + rhs + "\nshr eax,cl\n";
			cseg += "mov " + to + ",eax\n";
		}  break;
		case quat_op::e: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\n";
			cseg+="sub eax," + rhs + "\n";
			cseg += R"(
test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			)";
			cseg += "mov " + to + ",eax\n";
		}break;
		case quat_op::ne:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\n";
			cseg += "sub eax," + rhs + "\n";
			cseg += R"(
test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
xor eax,1
			)";
			cseg += "mov " + to + ",eax\n";
		} break;
		case quat_op::ge: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\n";
			cseg += "sub eax," + rhs + "\n";
			cseg += "shr eax,31\nxor eax,1\n";
			cseg += "mov " + to + ",eax\n";
		} break;
		case quat_op::le:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\n";
			cseg += "sub eax," + lhs + "\n";
			cseg += "shr eax,31\n";
			cseg += "xor eax,1\n";
			cseg += "mov " + to + ",eax\n";
		} break;
		case quat_op::l:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\n";
			cseg += "sub eax," + rhs + "\n";
			cseg += "shr eax,31\n";
			cseg += "mov " + to + ",eax\n";
		}  break;
		case quat_op::g:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\n";
			cseg += "sub eax," + lhs + "\n";
			cseg += "shr eax,31\nmov " + to + ",eax\n";
		} break;
		case quat_op::bxor: {
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\n";
			cseg += "xor eax," + lhs + "\n";
			cseg += "mov " + to + ",eax\n";
		} break;
		case quat_op::bor:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\n";
			cseg += "or eax," + lhs + "\n";
			cseg += "mov " + to + ",eax\n";
		}  break;
		case quat_op::band:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\n";
			cseg += "and eax," + lhs + "\n";
			cseg += "mov " + to + ",eax\n";
		} break;
		case quat_op::lor:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\n";
			cseg += "or eax," + lhs + "\n";
			cseg += R"(
test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
xor eax,1
			)";
			cseg += "mov " + to + ",eax\n";
		} break;
		case quat_op::land:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + rhs + "\n";
			cseg += "mov ebx," + lhs+"\n";
			cseg += R"(
test eax,eax
pushfd
pop ecx
test ebx,ebx		
pushfd
pop edx
or ecx,edx
and ecx,0040h  ;ZF == 0x0040
shr ecx,6
xor ecx,1
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
			cseg += "mov eax," + v + "\n";
			cseg += "not eax\nmov " + to + ",eax\n";
		}  break;
		case quat_op::lnot:
		{// not true
			auto v = name_of(qv[0], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + v + "\n";
			cseg += R"(
test eax,eax
pushfd
pop eax
and eax,0040h  ;ZF == 0x0040
shr eax,6
			)";
			cseg += "mov " + to + ",eax\n";
		}  break;
		case quat_op::pos: 
		{

			auto v = name_of(qv[0], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + v + "\n";
			cseg += "mov " + to + ",eax\n";
		} break;
		case quat_op::neg: 
		{

			auto v = name_of(qv[0], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + v + "\n";
			cseg += "neg eax\n";
			cseg += "mov " + to + ",eax\n";
		} break;
		case quat_op::arrayval: {
			name_of_array_member(qv[2], qv[0], qv[1], hscope);
		}break;
		case quat_op::structval: {
			name_of_struct_member(qv[2], qv[0], qv[1], hscope);
		}break;
			//before type check 
		case quat_op::type_cast: 
		{
			auto v = name_of(qv[0], hscope), to = name_of(qv[2], hscope);
			auto dty = qv[1], sty = sym.get_var_type(qv[0], hscope).first;
			if(sym.is_float(dty)) {
				cseg += "fild " + v + "\n";
				cseg += "fst " + to + "\n";
			}
			else {
				if(sym.is_float(sty)) {
					cseg += "fld " + v + "\n";
					cseg += "fist eax\n";
				}else {
					cseg += "xor eax,eax\n";
					switch (sym.get_type_size({ sty,0 })) {
					case 1:
						cseg += "mov al," + v + "\n";
						break;
					case 2:
						cseg += "mov ax," + v + "\n";
						break;
					case 4:
					case 8:
						cseg += "mov eax," + v + "\n";
						break;
					}
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
target::univ_var &target::insert_retval( scope::handle_scope h_curr) {
	auto real_scope = h_curr->find_handle_of_id("$return_value");
	int index = real_scope->id_map["$return_value"].second;
	std::string vname = "$return_value_" + std::to_string(index);
	dseg += vname + " ";
	auto ty = sym.var_list[index].first.first;
	switch (sym.get_type_size({ ty.first,0 })) {
	case -1:
	case 0:break;
	case 1:dseg += "BYTE "; break;
	case 2:dseg += "WORD "; break;
	case 4: dseg += "DWORD "; break;
	case 8:dseg += "DWORD "; break;
	default:{
		if (sym.is_struct(ty.first)) {
			dseg += sym.get_struct_name(ty.first) + " ";
		}
	}
	}
	if (ty.second >= 1) {
		//array
		if (sym.is_struct(ty.first))
			dseg += std::to_string(ty.second) + " DUP(<>)\n";
		else 
			dseg += std::to_string(ty.second) + " DUP(?)\n";
	} else {
		if (sym.is_struct(ty.first))
			dseg += " <>\n";
		else
			dseg += " ?\n";
	}
	return return_value_names[real_scope]= vname;
}
target::univ_var &target::name_of(int id, scope::handle_scope h_curr, bool is_array_param) {
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
		return const_name[id] = cname;
	} 
	else 
	{
		auto real_scope = h_curr->find_handle_of_id(id, data);
		int index =real_scope->get_index(id, data);
		std::string vname = get_name_of_now(id, data) + "_" + std::to_string(index);
		dseg += vname + " ";
		if (is_array_param) {
			dseg += "DWORD ?\n";
		}
		else {
			auto ty = sym.var_list[index].first.first;
			switch (sym.get_type_size({ ty.first,0 })) {
			case 1:dseg += "BYTE "; break;
			case 2:dseg += "WORD "; break;
			case 4: dseg += "DWORD "; break;
			case 8:dseg += "DWORD "; break;
			default:{
				if (sym.is_struct(ty.first)) {
					dseg += sym.get_struct_name(ty.first) + " ";
				}
			}
			}
			if (ty.second >= 1) {
				//array
				if (sym.is_struct(ty.first))
					dseg += std::to_string(ty.second) + " DUP(<>)\n";
				else
					dseg += std::to_string(ty.second) + " DUP(?)\n";
			} else {
				if (sym.is_struct(ty.first))
					dseg += " <>\n";
				else
					dseg += " ?\n";
			}
		}
		return id_name[std::make_pair(id, real_scope)] = vname;
	}
}

target::univ_var &target::name_of_struct_member(int id,int s_id, int f_id, scope::handle_scope h_curr) {
	return id_name[{id, h_curr}] = name_of(s_id, h_curr) + "." + get_name_of_now(f_id,data);
}

target::univ_var &target::name_of_array_member(int id, int arr_id, int pos_id, scope::handle_scope h_curr) {
	bool is_param = (h_curr->find_handle_of_id(arr_id, data))->s_type == scope::function;
	auto ty = sym.get_var_type(arr_id,h_curr);
	
	return id_name[{id, h_curr}] = univ_var(this, name_of(pos_id, h_curr), name_of(arr_id, h_curr),is_param,sym.get_type_size({ty.first,0}));
}

target::target(lex_data const & d, symbols & sy)
	:sym(sy), data(d) {

	dseg = ".data\n";
	cseg_begin = R"(
.stack 100
.code
)";
	cseg_end = R"(
END main
		)";
	incl = R"(includelib kernel32.lib  
.model flat,stdcall 
	
option casemap :none
 
includelib kernel32.lib
includelib masm32.lib
 
ExitProcess PROTO STDCALL:DWORD
StdOut		PROTO STDCALL:DWORD

)";
	work();
}

std::string operator+(std::string const & lhs, target::univ_var & rhs) {
	return lhs + std::string(rhs);
}

std::string operator+(target::univ_var & lhs, std::string const & rhs) {
	return std::string(lhs) + rhs;
}
