
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0680);
        set_name( "Dược Sư" );
}

// 函数：能否特殊技
void can_perform( object me )
{
	send_user( me, "%c%c%w%w%c%w%w%s", 0x60, 3, 680, 6801, 0, 0, 0, "Gia công dược liệu" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 1, "Gia công dược liệu" );
}
