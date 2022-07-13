#include <npc.h>
#include <ansi.h>
#include <public.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 1291; }
// 函数：构造处理
void create()
{
        set_name("Quán Yêu Noel");
        setup();
}

void do_look(object who)
{
	object me=this_object();
	send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s：\n    Bình bên ngoài người nghe, các ngươi đã bị vây quanh, buông các ngươi vũ khí, đem sở hữu quà Giáng Sinh ném vào ta bình! Ha ha ha ha ～～",me->get_name()));
}



