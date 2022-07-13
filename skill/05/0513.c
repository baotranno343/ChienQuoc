
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0513);
        set_name( "Kim Đơn Pháp Môn" );
}

// 函数：能否特殊技
void can_perform( object me )
{
        __DIR__ "05131"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 05131 );
}

// 函数：获取描述
string get_desc() 
{
        return "［Kim Đơn Pháp Môn］按配方炼制药物\n";
}
