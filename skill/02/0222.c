
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0222);
        set_name("Đao Kiếm Tâm Pháp");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "02221"->can_perform(me);
        __DIR__ "02222"->can_perform(me);
        //	__DIR__ "02223"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 02221);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02222);
}

// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_dp(me);
        USER_ENERGY_D->count_hit_rate(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Đao Kiếm Tâm Pháp]Bộ tâm pháp rèn luyện chiêu thế khi sử dụng Đao Kiếm. Mỗi cấp tăng thêm 1.1 điểm phòng thủ và tăng 0.05% điểm Bạo Kích khi sử dụng Đao hoặc Kiếm\n";
}
