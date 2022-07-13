#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }
int get_item_value() { return 100; }
int get_item_value_2() { return 100; }

// 函数：构造处理
void create()
{
	set_name("Túi Quà Tân Thủ Vip");
	set_picid_1(9913);
	set_picid_2(9913);
	set_level(10);
	set_value(10000);
	set_no_give(1);
	set_no_sell(1);
	set_no_drop(1);
}

// 函数：获取描述
string get_desc(object me)
{
	return "Túi quà hỗ trợ tân thủ tham gia Chiến Quốc.\n Sau khi sử dụng sẽ nhận được :\n" HIC " Túi Hoàng Kim Tân Thủ (Cấp 60)\n 3.000.000 ngân lượng\n 3 Chén Bạc Vip\n 150knb\n Thú Cưỡi Kiến Chiến Binh \n 10 Túi Pháp Bảo ";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int gender, family, type, i, q;
	object item, item1, item2, item3, item4, item5;
	string cTmp, cFile, p;
	gender = who->get_gender() == 1 ? 1 : 2;
	if (who->get_level() < 10)
	{
		send_user(who, "%c%s", '!', "Cấp 10 có thể sử dụng.");
		return 0;
	}
	if (USER_INVENTORY_D->get_free_count(who) < 6)
	{
		send_user(who, "%c%s", '!', "Hành trang không đủ chỗ.");
		return 0;
	}
	gift->remove_from_user();
	destruct(gift);
	//    TASK_LEGEND_D->check_task_item5(who,"Túi Quà Tân Thủ",1);

	who->add_cash(3000000);
	"sys/sys/test_db"->add_yuanbao(who, 1500);
	//	who->set_level(10);
	/*cFile = "item/tuiquatanthuhieu/TanThuKiNang";
		item = new(cFile);
			i = item->move2(who,-1);
			item->add_to_user(i); */

	/*	item1 = new(sprintf("item/ngoai_trang/ngoaitrang%d",gender));
	k = item1->move2(who,-1);
	item1->add_to_user(k); */

	/*	item2 = new("item/tuiquatanthuhieu/0008");
	item2->set_amount(20);
	l = item2->move2(who,-1);
	item2->add_to_user(l);
	item2->set_no_give(1);		

	item3 = new("item/tuiquatanthuhieu/0010");
	item3->set_amount(20);
	m = item3->move2(who,-1);
	item3->add_to_user(m);
	send_user(who,"%c%s",';',"Bạn nhận được "HIR "20 Trị Dược + Phục Dược.");
	item3->set_no_give(1);	

	item4 = new("kainz/ppvacanh");
	item4->set_amount(0);	
	n = item4->move2(who,-1);
	item4->add_to_user(n);
	send_user(who,"%c%s",';',"Bạn nhận được "HIR "Túi Trang Bị Vai).");*/

	item5 = new ("item/test/tuihoangkimtanthucap60");
	q = item5->move2(who, -1);
	item5->set_no_give(1);
	item5->add_to_user(q);
	//send_user(who, "%c%s", ';', "Bạn nhận được " HIR "Túi Hoàng Kim Tân Thủ Cấp 60.");

	item5 = new ("item/ride/042");
	q = item5->move2(who, -1);
	item5->set_no_give(1);
	item5->add_to_user(q);
	//send_user(who, "%c%s", ';', "Bạn nhận được " HIR "Kiến Chiến Binh.");

	item5 = new ("item/test/chenbacvip");
	item5->set_amount(3);
	q = item5->move2(who, -1);
	item5->add_to_user(q);
	//send_user(who, "%c%s", ';', "Bạn nhận được " HIR "3 Chén Bạc Vip.");

	item5 = new ("item/test2/tuiphapbao");
	item5->set_amount(10);
	q = item5->move2(who, -1);
	item5->set_no_give(1);
	item5->add_to_user(q);

	//send_user(who, "%c%s", ';', "Bạn nhận được " HIR "10 Túi Pháp Bảo.");
	return 0;
}
