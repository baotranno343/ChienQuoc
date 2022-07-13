
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0131);
        set_name( "Cơ Bản Kiếm Pháp" );
}

// 函数：能否特殊技
void can_perform( object me )
{
		__DIR__ "01312"->can_perform(me);
		__DIR__ "01313"->can_perform(me);
		__DIR__ "01314"->can_perform(me);
		__DIR__ "01315"->can_perform(me);
		__DIR__ "01316"->can_perform(me);
		__DIR__ "01317"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 01311 );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_cp(me); }

// 函数：获取描述
string get_desc() 
{
        return "[Cơ Bản Kiếm Pháp] Kiếm pháp nhập môn chiêu thức. Mỗi cấp tăng 1 điểm sát thương khi sử dụng Kiếm.\n";
}
