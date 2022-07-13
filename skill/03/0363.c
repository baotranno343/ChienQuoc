
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0363);
        set_name("Đường Môn Độc Kinh");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "03636"->can_perform(me);
        __DIR__ "03634"->can_perform(me);
        __DIR__ "03633"->can_perform(me);
        __DIR__ "03637"->can_perform(me);
        //__DIR__ "03632"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 03636);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03634);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03633);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03637);
}

// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_dp(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Đường Môn Độc Kinh] Tâm pháp hướng dẫn cách dùng độc của Đường gia. Mỗi cấp tăng 0.8 điểm phòng thủ khi trang bị Ám khí.\n";
}
