
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0670);
        set_name( "Thái Dã" );
}

// 函数：能否特殊技
void can_perform( object me )
{
	send_user( me, "%c%c%w%w%c%w%w%s", 0x60, 3, 670, 6701, 0, 0, 0, "Gia công Khoáng Thạch" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 1, "Gia công Khoáng Thạch" );
}
