
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0620);
        set_name( "Kĩ năng Rèn Đúc" );
}

// 函数：能否特殊技
void can_perform( object me )
{
	send_user( me, "%c%c%w%w%c%w%w%s", 0x60, 3, 620, 6201, 0, 0, 0, "Rèn" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 1, "Quyền Sáo" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 2, "Đao" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 3, "Thương" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 4, "Kiếm" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 5, "Côn" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 6, "Ám Khí" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 7, "Nguyên Liệu" );
}
