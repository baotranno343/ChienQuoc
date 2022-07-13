
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0414);
        set_name("Nghịch Thiên Pháp Chú");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "04147"->can_perform(me);
        __DIR__ "04143"->can_perform(me);
        __DIR__ "04144"->can_perform(me);
        __DIR__ "04145"->can_perform(me);
        __DIR__ "04148"->can_perform(me);
        __DIR__ "04141"->can_perform(me);
        //    __DIR__ "04140"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 04141);
        //   send_user(me, "%c%w%w", 0x50, 0xffff, 04140);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04143);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04144);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04145);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04147);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04148);
        // send_user( me, "%c%w%w", 0x50, 0xffff, 04140 );
}

// 函数：获取描述
string get_desc()
{
        return "[Nghịch Thiên Pháp Chú] Loại tà thuật nghịch lại thiên đạo, chuyên dùng để nguyền rủa trù ếm đối phương.\n";
}
