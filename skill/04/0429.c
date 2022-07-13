
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0429);
        set_name( "Long Du Tứ Hải" );
}

// 函数：能否特殊技
void can_perform( object me )
{
        __DIR__ "04291"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 04291 );
}

// 函数：获取描述
string get_desc() 
{
        return "［Long Du Tứ Hải］ có khả năng di chuyển nhanh đến bên người khác, đối phương pháp lực càng thấp tỷ lệ thành công càng cao \n";
}
