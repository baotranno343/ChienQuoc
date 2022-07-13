
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0329);
        set_name("Chu Thiên Vạn Chuyển");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "03291"->can_perform(me);
        __DIR__ "03292"->can_perform(me);
        __DIR__ "03293"->can_perform(me);
        __DIR__ "03294"->can_perform(me);
        // __DIR__ "03295"->can_perform(me);
        // 	__DIR__ "03296"->can_perform(me);
        // 	__DIR__ "03297"->can_perform(me);
        // 	__DIR__ "03298"->can_perform(me);
        // 	__DIR__ "03299"->can_perform(me);
        // 	__DIR__ "03290"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 03291);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03292);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03293);
        send_user(me, "%c%w%w", 0x50, 0xffff, 03294);
}

// 函数：重计属性
void recount_char(object me) { USER_ENERGY_D->count_max_hp(me); }

// 函数：获取描述
string get_desc()
{
        return "[Chu Thiên Vạn Chuyển]Bộ tâm pháp rèn luyện nâng cao điểm Khí Huyết tối đa. Mỗi cấp tăng thêm 4 điểm Khí Huyết\n";
}
