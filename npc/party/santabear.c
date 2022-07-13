#include <npc.h>
#include <ansi.h>
#include <public.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 1289; }
// 函数：构造处理
void create()
{
        set_name("Gấu Ngốc Noel");
        setup();
}

void do_look(object who)
{
	object me=this_object();
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    Đánh… Đánh… Đánh cướp ～ đem các ngươi IC, IP, IQ tạp hết thảy lấy tới! Quan trọng nhất chính là quà Giáng Sinh chạy nhanh cho ta!",me->get_name()));
}



