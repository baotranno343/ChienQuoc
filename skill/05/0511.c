
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0511);
        set_name("Y Thuật");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "05111"->can_perform(me);
        __DIR__ "05112"->can_perform(me);
        __DIR__ "05115"->can_perform(me);
        __DIR__ "05114"->can_perform(me);
        __DIR__ "05113"->can_perform(me);
        __DIR__ "05116"->can_perform(me);
        // 	__DIR__ "05117"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 05111);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05112);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05113);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05114);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05115);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05116);
}

// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_max_mp(me);
        USER_ENERGY_D->count_pp(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Y Thuật]Vân Mộng lừng danh thiên hạ về y thuật cao minh. Mỗi cấp tăng 3 điểm Pháp Lực và tăng 0.9 điểm Nội Kháng.\n";
}
