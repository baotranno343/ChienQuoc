#include <npc.h>
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

// 函数：命令处理
int main(object me, string arg)
{
	object who, item;
	int i, size, a1, a2, a3, a4, p, phai, sao, cap, gioitinh;
	string *nTmp, cFile, result, arg2, arg3, forge = "";

	if (is_player(me))
	{
		write_user(me, ECHO "Không đủ quyền hạn");
		return 1;
	}
	if (USER_INVENTORY_D->get_free_count(me) < 1)
	{
		write_user(me, ECHO "Hành trang của bạn không đủ 1 chỗ trống!");
		return 1;
	}
	if (arg == 0)
		return 1;
	if (sscanf(arg, "%s %d %d %d", arg2, phai, cap, sao) != 4)
		return 1;

	switch (arg2)
	{
	case "ao":
		item = new (sprintf("item/60/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "ao2":
		item = new (sprintf("item/61/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "non":
		item = new (sprintf("item/65/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "non2":
		item = new (sprintf("item/66/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "hanglien":
		item = new (sprintf("item/86/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "yeudoi":
		item = new (sprintf("item/87/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "giay":
		item = new (sprintf("item/88/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "trienthu":
		item = new (sprintf("item/70/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "amkhi":
		item = new (sprintf("item/71/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "dao":
		item = new (sprintf("item/72/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "thuong":
		item = new (sprintf("item/74/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "bong":
		item = new (sprintf("item/75/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "kiemts":
		item = new (sprintf("item/76/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "kiemms":
		item = new (sprintf("item/77/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "kiemcl":
		item = new (sprintf("item/78/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	case "kiemvmc":
		item = new (sprintf("item/79/%d%03d", phai, cap));
		"/sys/item/equip"->init_equip_prop_3(item);
		for (i = 0; i < sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(2);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me, -1);
		item->add_to_user(p);
		send_user(me, "%c%s", ';', sprintf("Bạn nhận được " HIY "%s %d sao", item->get_name(), sao));
		return 1;
		break;
	}
	return 1;
}
