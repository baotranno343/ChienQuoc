
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0111);
        set_name( "Cơ Bản Quyền Cước" );
}

// 函数：能否特殊技
void can_perform( object me )
{
}

// 函数：删除特殊技
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 01111 );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_ap(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Cơ Bản Quyền Cước] Hướng dẫn nhập môn võ công quyền cước. Mỗi cấp tăng 1 điểm Ngoại công khi sử dụng quyền thuật.\n";
}
