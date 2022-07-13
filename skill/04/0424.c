
inherit SKILL;

// 函数：构造处理
void create()
{
        set_number(0424);
        set_name("Kim Cang Pháp Chú");
}

// 函数：能否特殊技
void can_perform(object me)
{
        __DIR__ "04241"->can_perform(me);
        __DIR__ "04242"->can_perform(me);
        __DIR__ "04243"->can_perform(me);
        __DIR__ "04244"->can_perform(me);
        // __DIR__ "04245"->can_perform(me);
        //	__DIR__ "04246"->can_perform(me);
}

// 函数：删除特殊技
void remove_perform(object me)
{
        send_user(me, "%c%w%w", 0x50, 0xffff, 04241);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04242);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04243);
        send_user(me, "%c%w%w", 0x50, 0xffff, 04244);
        //	send_user( me, "%c%w%w", 0x50, 0xffff, 04246 );
}

// 函数：获取描述
string get_desc()
{
        return "[Kim Cang Pháp Chú]Đạo pháp thượng thừa lấy tấn công làm chủ đạo, có thể chọc trời khuấy biển hay hàng yêu phục ma. Thiên về các pháp thuật tấn công tập thể.\n";
}
