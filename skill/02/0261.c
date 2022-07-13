
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0261);
        set_name("Mãn Thiên Hoa Vũ");
}

// 函数：能否特殊技
void can_perform(object me)
{
        me->set_attack_move(1);
        //        __DIR__ "02611"->can_perform(me);
        __DIR__ "02612"->can_perform(me);
        __DIR__ "02614"->can_perform(me);
        __DIR__ "02615"->can_perform(me);
        __DIR__ "02616"->can_perform(me);
        __DIR__ "02617"->can_perform(me);
        __DIR__ "02613"->can_perform(me);
        __DIR__ "02618"->can_perform(me);
        // __DIR__ "02619"->can_perform(me);
        //	__DIR__ "02610"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        //        send_user( me, "%c%w%w", 0x50, 0xffff, 02611 );
        send_user(me, "%c%w%w", 0x50, 0xffff, 02612);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02613);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02614);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02615);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02616);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02617);
        send_user(me, "%c%w%w", 0x50, 0xffff, 02618);
        //    send_user( me, "%c%w%w", 0x50, 0xffff, 02610 );
}

// 函数：重计属性
void recount_char(object me) { USER_ENERGY_D->count_ap(me); }

// 函数：获取描述
string get_desc()
{
        return "[Mãn Thiên Hoa Vũ] Bí kíp ám khí độc nhất vô nhị của Đường Môn. Mỗi cấp tăng 1.4 Ngoại Công.\n";
}
