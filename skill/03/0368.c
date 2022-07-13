
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0368);
        set_name("Cực Tà Sát Pháp");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "03683"->can_perform(me);
        __DIR__ "03684"->can_perform(me);
        __DIR__ "03685"->can_perform(me);
        __DIR__ "03686"->can_perform(me);
        // __DIR__ "03687"->can_perform(me);
        // __DIR__ "03688"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 03683);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03684);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03685);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03686);
}
// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_max_mp(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Cực Tà Sát Pháp] Tâm pháp ám sát, là tuyệt học bí truyền của Đường Môn đã từng gây sóng gió trên giang hồ. Mỗi cấp tăng thêm 1.6 điểm Pháp Lực tối đa.\n";
}
