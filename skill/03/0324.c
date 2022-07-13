
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0324);
        set_name( "Lạc Tuyết Vô Ngân" );
}

// 函数：能否特殊技
void can_perform( object me )
{
//        __DIR__ "03241"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 03241 );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_sp(me); }

// 函数：获取描述
string get_desc() 
{
        return "［Lạc Tuyết Vô Ngân］提升躲闪，每级提升躲闪 1.5 点\n";
}
