
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0503);
        set_name( "Luyện Đơn Thuật" );
}

// 函数：能否特殊技
void can_perform( object me )
{
        __DIR__ "05031"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 05031 );
}

// 函数：获取描述
string get_desc() 
{
        return "［Luyện Đơn Thuật］按配方炼制药物\n";
}
