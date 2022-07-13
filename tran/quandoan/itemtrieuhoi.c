#include <ansi.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;
int is_trieuHoiQuanDoan() { return 1; }
// 函数：构造处理
void create()
{
	set_name("Bùa Triệu Hồi Hình Nhân");
	set_picid_1(0008);
	set_picid_2(0008);
	set_value(500);
}

// 函数：获取描述
string get_desc()
{
	return "Triệu Hồi Hình Nhân.";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	// int p, z, x, y;
	// object npc;
	// z = get_z(who);
	// x = get_x(who);
	// y = get_y(who);

	// npc = new ("npc/npc/0111_test");
	// if (!npc)
	// {

	// 	return 0;
	// }
	// if (!(p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)))
	// {

	// 	return 0;
	// }
	// x = p / 1000;
	// y = p % 1000;
	// npc->set_name(who->get_name() + "> Quân Đoàn");
	// // npc->set_owner(who);
	// npc->set_idChuQuanDoan(who->get_number());
	// npc->destroy_time(3600);
	// npc->add_to_scene(z, x, y);
	// "/map/city/08"->set_2(sprintf("quanDoan.%d.sl", who->get_number()), 1);
	// send_user(who, "%c%s", ';', "Bạn triệu hồi " HIY "Quân Đoàn");

	"cmd/user/itemtrieuhoi"->main(who, 0);
	return 0;
}