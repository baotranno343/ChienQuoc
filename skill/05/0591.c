
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0591);
        set_name("Kỳ Môn Độn Giáp");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "05911"->can_perform(me);
        __DIR__ "05912"->can_perform(me);
        __DIR__ "05913"->can_perform(me);
        // __DIR__ "05914"->can_perform(me);
        // __DIR__ "05915"->can_perform(me);
        // __DIR__ "05916"->can_perform(me);
        // __DIR__ "05917"->can_perform(me);
        // __DIR__ "05918"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 05911);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05912);
        send_user(me, "%c%w%w", 0x50, 0xffff, 05913);
}

// 函数：获取描述
string get_desc()
{
        return "[Kỳ Môn Độn Giáp]Học thuật của Quỷ Cốc Tử, hàm chứa những trận pháp ảo diệu và cách luyện lấy linh khí hộ thể.\n";
}
