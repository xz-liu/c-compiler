#include "target.h"

void target::work() {
	for (int i = 0; i < sym.quats.size(); i++) {
		symbols::quat &qt = sym.quats[i];
		auto &qv = qt.first.second;
		auto hscope = qt.second;
		auto op = qt.first.first;
		switch (op) {
		case quat_op::func:
		{
			cseg += get_name_of_now(qv[0], data) + " PROC\n";
		}break;
		case quat_op::funcend:
		{
			if(get_name_of_now(qv[0],data)=="main") {
				cseg += "exit\n";
			}
			cseg += get_name_of_now(qv[0], data) + " ENDP\n";
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
				cseg += "fld " + lhs + "\nfld" + rhs + "\nfadd\nfst " + to + "\n";
				break;
			}
		} break;
		case quat_op::sub:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\nsub eax," + rhs + "\nmov " + to + ",eax\n";
		} break;
		case quat_op::mul:
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov eax," + lhs + "\nimul " + rhs + "\nmov " + to + ",eax\n";
		}break;
		case quat_op::div: 
		{
			auto lhs = name_of(qv[0], hscope), rhs = name_of(qv[1], hscope), to = name_of(qv[2], hscope);
			cseg += "mov edx,0\nmov eax," + lhs + "\nmov ecx," + rhs + "\nidiv ecx\nmov " + to + ",eax\n";
		}  break;
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
std::string target::name_of(int id, scope::handle_scope h_curr) {
	auto it = id_name.find({id,h_curr});
	if (it != id_name.end())return it->second;
	auto it_const = const_name.find(id);
	if (it_const != const_name.end())return it_const->second;
	if (sym.is_const(id)) {
		std::string cname = "CONST_" + std::to_string(id);
		auto ty = sym.get_const_type(id);
		switch (ty.first) {
		case symbols::int64:
		{
			dseg += cname + " QWORD " + get_name_of_now(id, data) + "\n";
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
			dseg += cname + " QWORD " + get_name_of_now(id, data) + "\n";
		}
		}
		const_name.emplace(id, cname);
		return  cname;
	} 
	else 
	{
		int index = h_curr->find_handle_of_id(id, data)->get_index(id, data);
		std::string vname = get_name_of_now(id, data) + "_" + std::to_string(index);
		dseg += vname + " ";
		auto ty = sym.var_list[index].first.first;
		switch (sym.get_type_size({ ty.first,0 })) {
		case 1:dseg += "BYTE "; break;
		case 2:dseg += "WORD "; break;
		case 4: dseg += "DWORD "; break;
		case 8:dseg += "QWORD "; break;
		}
		if (ty.second >= 1) {
			//array
			dseg += std::to_string(ty.second) + " DUP(?)\n";
		} 
		else {
			dseg += " ?\n";
		}
		id_name.insert(std::make_pair(std::make_pair( id,h_curr ), vname));
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
	work();
}
