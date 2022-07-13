
inherit SKILL;

// 函数：构造处理
void create()
{
    set_number(0317);
    set_name("Hộ Thể Kim Cang");
}

// 函数：能否特殊技
void can_perform(object me)
{
    //    __DIR__ "03171"->can_perform(me);
    __DIR__ "03172"->can_perform(me);
    __DIR__ "03173"->can_perform(me);
    // __DIR__ "03174"->can_perform(me);
    // __DIR__ "03175"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
    //    send_user( me, "%c%w%w", 0x50, 0xffff, 03171 );
    send_user(me, "%c%w%w", 0x50, 0xffff, 03172);
    send_user(me, "%c%w%w", 0x50, 0xffff, 03173);
}

// 函数：重计属性
void recount_char(object me) { USER_ENERGY_D->count_hurt(me); }

// 函数：获取描述
string get_desc()
{
    return "[Hộ Thể Kim Cang]Tâm pháp lấy việc chiến đấu liên tục để sản sinh Nguyên Khí; khi đẳng cấp võ công tăng cao còn có thể tự động phản hồi sát thương Ngoại Công từ địch thủ\n";
}
