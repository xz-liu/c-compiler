# compiler

A simple C compiler with limited grammar supported


## Frontend 

*  lex 
     * regex match
*  parser
     *  reads string as grammar
     *  terminator
          *  str surronded with ' '
          *  int_const
          *  float_const
          *  char_const
          *  string
          *  id    
     *  semantic action 
          *  str surronded with {} 
          *  function param
               *  action id
               *  now  
     *  parse algorithm
          *  LL1
          *  multiple productions for one LL1 table item
          *  sort productions to avoid loop 
*  literals
     *  int literal (int64)
     *  float literal (float64)
     *  char literal (char8)
     *  string literal (char8[]) 
*  scopes
     *  function scope
     *  code block scope
     *  struct scope
*  id type     
     *  variable
     *  function
     *  struct  
*  supported grammar
     *  types
          *  char8
          *  uchar8
          *  int16
          *  uint16
          *  int32
          *  uint32
          *  int64
          *  uint64
          *  float32
          *  float64
          *  void
          *  struct id
     *  statements
          *  if 
          *  else
          *  switch
          *  case
          *  for
          *  while
          *  break
          *  continue
          *  return
          *  expression
               *  = (+=, -=, *=, /=, %=, |=, &=, ^=, >>=, <<=)
               *  \+ -
               *  \* / %
               *  << >>
               *  || && 
               *  | & ^ 
               *  ++ --
               *  ~ ! - +
               *  [] . ()
     *  function
     *  struct
### basic type id
```
none = -1,
void_type = 0,
char8 = 1,
uchar8 = 2,
int16 = 3,
uint16 = 4,
int32 = 5,
uint32 = 6,
float32 = 7,
int64 = 8,
uint64 = 9,
float64 = 10,
struct_type = 11; 
```
### quat op definition
```
enum class quat_op {
	label ,
	jmp,
	btrue ,
	bfalse, 
	newvar ,
	func ,
	funcparam ,
	funcend, 
	structdef,
	structend,
	cblock,
	cend,
	push ,
	call,
	callend,
	ret,
	retval,
	arrayval, structval , 
	add, sub,mul, div, mod ,
	shl, shr, 
	e, ne, ge, le, l,g,
	bxor,bor,band,lor,land, 
	inc ,dec, bnot, lnot, pos, neg, 
	assign,
	initlst,initlstend,initlstitem,
	//before type check 
	type_cast;
};
//sample 
vector<quat> symbols::quats;
quat qt= quats[i];
quat_op op= qt.first.first;
array<int,3> &qv = qt.first.second;
 if(op == quat_op::label){
         //label 
        int pos= qv[0];
 }else if(op== quat_op::add){
        // lhs,rhs,to 
 }
```
* quat format
     * <<quat_op,<int,int,int>>,scope_pointer>
     * bool sym.is_const(int) 
     * type sym.get_const_type(int) 
        * <int,int>
        * first-> type id
        * second->array size

* symbol table
     * var 
     * 
     * <<<TYPE(int),ARRAY_SIZE(int)>,CAN_ASSIGN(bool)>,SCOPE_POINTER(handle_scope)>
*  
### intermediate representation 
|QUAT TYPE | VAL1 | VAL2 | VAL3 | OPERATION|
|----------|------|------|------|----------|
|label | pos | 0 | 0|定义一个叫做pos的label|
|jmp | pos| 0 | 0|无条件跳转到名叫pos的label|
|btrue | pos| (id)pred | 0|若pred为真 跳转到pos|
|bfalse | pos| (id)pred | 0|若pred为假 跳转到pos|
|newvar | id | type | (id)array |新建一个type类型的名字叫id的变量 若array为0是变量，array不为0是长度为array的数组|
|func | id | type | 0|名字为id 返回值为type的函数|
|funcparam | id | type | array|  func的参数，类型是type，array不为零为数组|
|funcend | id | 0| 0 | 函数的结束|
|structdef | id | is_union | 0 |    名字为id的struct, is_union为1代表是union|
|structend| id |  0 | 0   |   名字为id的struct定义结束 |
|cblock | 0 |  0  |   0|  标记一个代码块的开始|
|cend | 0 | 0  |  0|      ~~~~~~~~~~~~~~结束|
|call | id | 0 |    |  调用id函数|        
|push | val | 0 |0  |     val为参数|
|callend | to | 0 |   |  返回值存在to中|
|ret| 0 | 0 |0 |   函数返回|
|retval| 0| 0 |to |  函数返回，返回值存在to中|
|op | (id)lhs|(id)rhs| (id)to | 双目运算符，运算结果存入to中|
|op | val| 0| to |单目运算符，运算结果存入to中|
|inc/dec|val | 0 | 0 | 自增/自减
|assign | lhs| rhs| type | lhs ?= rhs  |
|initlst|id|0|0 |  初始化列表|
|initend|id|0|0| 初始化列表结束|
|initlstitem | val | 0 |0 | 初始化列表元素|
|type_cast|id|type|to| |

