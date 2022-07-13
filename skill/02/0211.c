
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0211);
        set_name("Thái Cổ Thần Quyền");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "02110"->can_perform(me);
        __DIR__ "02111"->can_perform(me);
        __DIR__ "02117"->can_perform(me);
        __DIR__ "02112"->can_perform(me);
        __DIR__ "02115"->can_perform(me);
        __DIR__ "02113"->can_perform(me);
        __DIR__ "02116"->can_perform(me);
        __DIR__ "02114"->can_perform(me);
        __DIR__ "02118"->can_perform(me);
        __DIR__ "02119"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 02111);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02112);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02113);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02114);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02115);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02116);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02117);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02118);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02119);
}

// 函数：重计属性
void recount_char(object me) { USER_ENERGY_D->count_ap(me); }

// 函数：获取描述
string get_desc()
{
        return "[Thái Cổ Thần Quyền] Bộ quyền pháp thượng cổ chí tôn. Người luyện có thể dùng nội khí trong huyết mạch để khai sơn phá thiên. Mỗi cấp tăng 1 điểm sát thương.\n";
}
