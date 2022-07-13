
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0640);
        set_name( "Kĩ năng May Mặc" );
}

// 函数：能否特殊技
void can_perform( object me )
{
	send_user( me, "%c%c%w%w%c%w%w%s", 0x60, 3, 640, 6401, 0, 0, 0, "May" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 1, "Y Phục" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 2, "Nón" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 3, "Hài" );
//	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 4, "项链" );
//	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 5, "腰带" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 6, "Nguyên Liệu" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 7, "Bao Bố" );
}
