
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0221);
        set_name("Thiên La Đao Pháp");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "02210"->can_perform(me);
        __DIR__ "02211"->can_perform(me);
        __DIR__ "02212"->can_perform(me);
        __DIR__ "02213"->can_perform(me);
        __DIR__ "02214"->can_perform(me);
        __DIR__ "02215"->can_perform(me);
        __DIR__ "02216"->can_perform(me);
        // __DIR__ "02217"->can_perform(me);
        // __DIR__ "02218"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 02210);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02211);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02212);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02213);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02214);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02215);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02216);
}

// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_ap(me);
        USER_ENERGY_D->count_hit_rate(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Thiên La Đao Pháp]Bí kíp trấn phái ghi lại những chiêu thức Đao pháp do tổ sư Thái Hư Chân Nhân,. Mỗi cấp gia tăng 0,2 % Ngoại Công và 0,1 % chính xác\n";
}
