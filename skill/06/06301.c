
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0630);
        set_name( "Luyện Đơn" );
}

// 函数：能否特殊技
void can_perform( object me )
{
	send_user( me, "%c%c%w%w%c%w%w%s", 0x60, 3, 630, 6301, 0, 0, 0, "Luyện chế đơn dược" );
	send_user( me, "%c%c%w%w%s", 0x60, 4, get_number(), 1, "Chế tạo đơn dược" );	
}
