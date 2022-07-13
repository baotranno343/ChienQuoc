
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0251);
        set_name("Phong Ma Côn Pháp");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "02510"->can_perform(me);
        __DIR__ "02514"->can_perform(me);
        __DIR__ "02513"->can_perform(me);
        __DIR__ "02516"->can_perform(me);
        __DIR__ "02517"->can_perform(me);
        __DIR__ "02512"->can_perform(me);
        __DIR__ "02515"->can_perform(me);
        //  __DIR__ "02518"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        //        send_user( me, "%c%w%w", 0x50, 0xffff, 02511 );
        send_user(me, "%c%w%w", 0x50, 0xffff, 02512);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02513);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02514);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02515);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02516);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02517);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02510);
}

// 函数：重计属性
void recount_char(object me)
{
        USER_ENERGY_D->count_ap(me);
}

// 函数：获取描述
string get_desc()
{
        return "[Phong Ma Côn Pháp] Côn pháp của Cấm Vệ Quân uy danh lừng lẫy từ hơn mấy trăm năm nay. Mỗi cấp tăng 0,2 % Ngoại Công.\n";
}
