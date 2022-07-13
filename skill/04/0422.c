
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0422);
        set_name("Âm Dương Ngũ Hành");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "04221"->can_perform(me);
        __DIR__ "04222"->can_perform(me);
        // __DIR__ "04223"->can_perform(me);
        // __DIR__ "04224"->can_perform(me);
        // __DIR__ "04225"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 04221);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04222);
}

// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_cp(me);
        //	USER_ENERGY_D->count_ap(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Âm Dương Ngũ Hành]Đạo gia ai cũng tinh thông âm dương, thấu hiểu ngũ hành tương sinh tương khắc. Mỗi cấp tăng 0,20% điểm Nội Công.\n";
}
