
inherit SKILL;

// 函数：基本技能
int is_basic_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0408);
        set_name( "Kỳ Môn Độn Giáp" );
}

// 函数：能否特殊技
void can_perform( object me )
{
        __DIR__ "04081"->can_perform(me);
        __DIR__ "04082"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 04081 );
        send_user( me, "%c%w%w", 0x50, 0xffff, 04082 );
}

// 函数：获取描述
string get_desc() 
{
        return "［Kỳ Môn Độn Giáp］设置导标，快速移动到目标地点。每 20 级增加 1 个导标\n";
}
