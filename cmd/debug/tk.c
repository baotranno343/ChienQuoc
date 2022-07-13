#include <npc.h>
#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>
#include <equip.h>

// 函数：命令处理
int main( object me, string arg )
{
	object who, item;
        int i, size, a1, a2, a3, a4, p, phai, sao, cap;
		string *nTmp,cFile,result,arg2,arg3,forge="";

        if( is_player(me) ) 
        {
                write_user(me, ECHO"Không đủ quyền hạn");
				return 1;
        }
			if(USER_INVENTORY_D->get_free_count(me) < 1 )
			{
				write_user(me, ECHO "Hành trang của bạn không đủ 1 chỗ trống!");
				return 1;
			}
	if ( arg==0 )
	{
                return 1;
	}
	if (sscanf(arg, "%s %d", arg2, sao)!=2) return 1;
	/*else */if (sscanf(arg, "%s %d %d", arg3, phai, sao)!=3) return 1;
	switch(arg2)
{
    case "trienthu":
		item = new("item/70/9075");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Anh Kiệt Quyền Nhẫn %d sao",sao ));
		return 1;
        break;
	case "trienthu2":
		item = new("item/70/9100");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Ngọc La Quyền Thủ %d sao",sao ));
		return 1;
        break;
	case "trienthu3":
		item = new("item/70/9130");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Trụ Thiên Quyền Thủ %d sao",sao ));
		return 1;
        break;	
	case "dao":
		item = new("item/72/9075");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Thiên Tôn Bảo Đao %d sao",sao ));
		return 1;
        break;
	case "dao2":
		item = new("item/72/9100");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Đao Tử Vân %d sao",sao ));
		return 1;
        break;
	case "dao3":
		item = new("item/72/9130");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Càn Khôn Vân Đao %d sao",sao ));
		return 1;
        break;	
	case "kiem":
		item = new("item/73/9075");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Ngọc Thần Bảo Kiếm %d sao",sao ));
		return 1;
        break;
	case "kiem2":
		item = new("item/73/9100");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Lục Tiên Kiếm %d sao",sao ));
		return 1;
        break;
	case "kiem3":
		item = new("item/73/9130");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Huyết Lệ %d sao",sao ));
		return 1;
        break;	
	case "thuong":
		item = new("item/74/9075");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Chân Quân Xí Diệm Thương %d sao",sao ));
		return 1;
        break;
	case "thuong2":
		item = new("item/74/9100");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Lục Thần Thương %d sao",sao ));
		return 1;
        break;
	case "thuong3":
		item = new("item/74/9130");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Phá Thiên Thương %d sao",sao ));
		return 1;
        break;	
	case "bong":
		item = new("item/75/9075");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Càn Khôn Vô Cấp Côn %d sao",sao ));
		return 1;
        break;
	case "bong2":
		item = new("item/75/9100");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Phàn Thiên Côn %d sao",sao ));
		return 1;
        break;
	case "bong3":
		item = new("item/75/9130");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Hoả Thiên Côn %d sao",sao ));
		return 1;
        break;	
	case "amkhi":
		item = new("item/71/9075");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Bích Hoả Hàn Nguyệt Hoàn %d sao",sao ));
		return 1;
        break;
	case "amkhi2":
		item = new("item/71/9100");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Thần Tiên Hạc Kim %d sao",sao ));
		return 1;
        break;
	case "amkhi3":
		item = new("item/71/9130");
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"Đoạt Mệnh Ma Khí %d sao",sao ));
		return 1;
        break;	
		
}
switch(arg3)
{
    case "ao":
		item = new(sprintf("item/56/%d085", phai ));
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"%s %d sao", item->get_name(), sao ));
		return 1;
        break;
	case "non":
		item = new(sprintf("item/55/%d085", phai ));
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"%s %d sao", item->get_name(), sao ));
		return 1;
        break;
	case "hanglien":
		item = new(sprintf("item/57/%d085", phai ));
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"%s %d sao", item->get_name(), sao ));
		return 1;
        break;
	case "yeudoi":
		item = new(sprintf("item/58/%d085", phai ));
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"%s %d sao", item->get_name(), sao ));
		return 1;
        break;
	case "giay":
		item = new(sprintf("item/59/%d085", phai ));
		for (i = 0; i< sao; i++)
		{
			"/sys/item/equip"->init_equip_prop_5(item);
			forge += "1";
			item->set("forge", forge);
		}
		item->set_item_color(3);
		item->set_hide(0);
		item->set_bind(1);
		p = item->move2(me,-1);
		item->add_to_user(p);
		send_user(me,"%c%s",';', sprintf("Bạn nhận được "HIY"%s %d sao", item->get_name(), sao ));
		return 1;
        break;
		
}		
        return 1;
}
