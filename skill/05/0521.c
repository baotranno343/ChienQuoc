
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0521);
        set_name( "Độc Kinh" );
}

// 函数：能否特殊技
void can_perform( object me )
{
        __DIR__ "05211"->can_perform(me);
        __DIR__ "05212"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 05211 );
        send_user( me, "%c%w%w", 0x50, 0xffff, 05212 );
}

// 函数：获取描述
string get_desc() 
{
        return "［Độc Kinh］对目标下毒，制作涂在武器上的毒粉\n";
}
