
inherit SKILL;

// 函数：构造处理
void create() 
{ 
        set_number(0232);
        set_name( "Tâm Pháp Vận Khí" );
}

// 函数：能否特殊技
void can_perform( object me )
{
        __DIR__ "02321"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform( object me )
{
        send_user( me, "%c%w%w", 0x50, 0xffff, 02321 );
}

// 函数：重计属性
void recount_char( object me ) { USER_ENERGY_D->count_dp(me); }

// 函数：获取描述
string get_desc() 
{
        return "［Tâm Pháp Vận Khí］Tăng lực phòng ngự khi sử dụng Kiếm(Haizzz)..mỗi cấp tăng 1.2 điểm\n";
}
