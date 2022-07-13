
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0610);
        set_name( "Đầu Bếp" );
}

// 函数：能否特殊技
void can_perform( object me )
{
	send_user( me, "%c%c%w%w%c%w%w%s", 0x60, 3, 610, 6101, 0, 0, 0, "Tửu Thực chế tác" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 1, "Tửu Thực chế tác" );
}
