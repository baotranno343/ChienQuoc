
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0425);
        set_name("Càn Khôn Na Di");
}

// 函数：能否特殊技
void can_perform(object me)
{
        //  __DIR__ "04251"->can_perform(me);
        __DIR__ "04252"->can_perform(me);
        __DIR__ "04253"->can_perform(me);
        __DIR__ "04254"->can_perform(me);
        //		__DIR__ "04255"->can_perform(me);
        // __DIR__ "04256"->can_perform(me);
        // __DIR__ "04257"->can_perform(me);
        // __DIR__ "04258"->can_perform(me);
        // __DIR__ "04259"->can_perform(me);
        // __DIR__ "04250"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 04252);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04253);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04254);
        //		send_user( me, "%c%w%w", 0x50, 0xffff, 04255 );
}

// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_pp(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Càn Khôn Na Di]Độc môn phòng vệ tâm pháp có khả năng gia tăng công lực cho người luyện. Mỗi cấp tăng 1 điểm Nội Kháng.\n";
}
