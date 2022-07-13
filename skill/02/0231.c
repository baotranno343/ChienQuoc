
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0231);
        set_name("Phi Tiên Kiếm Pháp");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "02310"->can_perform(me);
        __DIR__ "02311"->can_perform(me);
        __DIR__ "02312"->can_perform(me);
        __DIR__ "02315"->can_perform(me);
        __DIR__ "02313"->can_perform(me);
        __DIR__ "02314"->can_perform(me);
        __DIR__ "02316"->can_perform(me);
        // __DIR__ "02317"->can_perform(me);
        // __DIR__ "02318"->can_perform(me);
        // __DIR__ "02319"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 02310);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02311);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02312);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02313);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02314);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02315);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02316);
}

// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_cp(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Phi Tiên Kiếm Pháp] Tiên kiếm tuyệt thế của Thục Sơn do Nhất Tâm Đạo Trưởng sáng lập, Mỗi cấp tăng 2.5 điểm Nội Công khi sử dụng Kiếm.\n";
}
