
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0501);
        set_name("Trung Y Dược Lý");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "05011"->can_perform(me);
        __DIR__ "05012"->can_perform(me);
        __DIR__ "05013"->can_perform(me);
        __DIR__ "05014"->can_perform(me);
        __DIR__ "05015"->can_perform(me);
        __DIR__ "05016"->can_perform(me);
        // __DIR__ "05017"->can_perform(me);
        // __DIR__ "05018"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 05011);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05012);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05013);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05014);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05015);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05016);
}

// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_max_hp(me);
        USER_ENERGY_D->count_dp(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Trung Y Dược Lý]Kỹ năng đặc biệt của bang phái, có thể gia tăng mỗi cấp thêm 6 điểm Khí Huyết và thêm 0.9 điểm Ngoại Kháng.\n";
}
