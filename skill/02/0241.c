
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0241);
        set_name("Bá Vương Thương Pháp");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "02410"->can_perform(me);
        __DIR__ "02411"->can_perform(me);
        __DIR__ "02412"->can_perform(me);
        __DIR__ "02414"->can_perform(me);

        __DIR__ "02413"->can_perform(me);

        __DIR__ "02415"->can_perform(me);
        __DIR__ "02416"->can_perform(me);
        // __DIR__ "02417"->can_perform(me);
        // __DIR__ "02418"->can_perform(me);
        // __DIR__ "02419"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 02410);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02411);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02412);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02413);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02414);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02415);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02416);
}

// 函数：重计属性
void recount_char(object me) { USER_ENERGY_D->count_hit_rate(me); }

// 函数：获取描述
string get_desc()
{
        return "[Bá Vương Thương Pháp] Thương pháp phong nhuệ như mãnh thú của Cấm Vệ Quân. Mỗi cấp tăng 0.1% Chính Xác. và 0,15% Bạo Kích\n";
}
