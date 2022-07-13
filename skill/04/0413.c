
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0413);
        set_name("Đạo Pháp Thần Thông");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "04130"->can_perform(me);
        __DIR__ "04131"->can_perform(me);
        __DIR__ "04132"->can_perform(me);
        //        __DIR__ "04133"->can_perform(me);
        __DIR__ "04134"->can_perform(me);
        //__DIR__ "04135"->can_perform(me);
        //	__DIR__ "04137"->can_perform(me); // Thu hồi
        //__DIR__ "04136"->can_perform(me); // Gọi T.Nhi
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 04130);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04131);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04132);
        //        send_user( me, "%c%w%w", 0x50, 0xffff, 04133 );
        send_user(me, "%c%w%w", 0x50, 0xffff, 04134);
        //	 send_user( me, "%c%w%w", 0x50, 0xffff, 04137 ); // Thu hồi
        //	send_user( me, "%c%w%w", 0x50, 0xffff, 04136 );  // Gọi T.Nhi
}

// 函数：获取描述
string get_desc()
{
        return "[Đạo Pháp Thần Thông] Sử dụng Bùa Giấy triệu hồi âm binh thần tướng hỗ trợ có Quỷ Tốt, Thiên Binh, Thần Tướng, Cương Thi.\n";
}
