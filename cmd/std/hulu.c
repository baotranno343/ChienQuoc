/**************
    济世葫芦
***************/
#include <ansi.h>
#include <item.h>
#include <city.h>
#include <chia_kenh.h>
// 函数：命令处理
int main(object me, string arg)
{
	string *nTmp;
	if (!arg)
		return 1;
	if (MAIN_D->get_kenh() != KENH_BANG)
	{
		send_user(me, "%c%s", '!', "Vui lòng sử dụng tính năng này ở Kênh Bang Phái");
		return;
	}
	nTmp = explode(arg, " ");
	switch (to_int(nTmp[0]))
	{
	default:
		break;
	case 0: //获取本身葫芦信息
		"npc/std/0003"->do_info(me);
		break;
	case 1: //同级段寄售
		"npc/std/0003"->do_agend(me);
		break;
	case 2: //高级段寄售
		"npc/std/0003"->do_advance_agend(me);
		break;
	case 3: //取回
		"npc/std/0003"->take_back(me);
		break;
	case 4: //领取葫芦
		"npc/std/0003"->pick_hulu(me, nTmp[1]);
		break;
	case 5: //扩展葫芦
		"npc/std/0003"->do_expand(me);
		break;
	case 6: //提取经验
		"npc/std/0003"->do_welcome("3");
		break;
	case 7: //归还葫芦
		"npc/std/0003"->return_hulu(me);
		break;
	case 8: //葫芦列表
		"npc/std/0003"->send_info(me);
		break;
	case 9:
		"npc/std/0003"->get_exp(me);
		break;
	case 99:
		if (is_god(me))
			"npc/std/0003"->set_exp(me, nTmp[1], to_int(nTmp[2]));
		break;
	}
}