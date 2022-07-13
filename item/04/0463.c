#include <ansi.h>
#include <equip.h>
inherit ITEM;
inherit COMBINED;

int get_item_color() { return 1; }

// 函数：构造处理
void create()
{
        set_name("重阳礼包");
        set_picid_1(4982);
        set_picid_2(4982);
        set_amount(1);
        set_value(200);
}

int is_usable() {return 1;}

// 函数：获取描述
string get_desc() 
{ 
        return "重阳老人在重阳节赠送的礼物"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash,level;
	object item;
       	string *nTmp,tmp,cTmp;
	string *nFamily = ({"桃花源","蜀山","禁卫军","唐门","茅山","昆仑山","云梦泽"});
	if(USER_INVENTORY_D->get_free_count(who) < 1 )
	{
	        send_user(who,"%c%s",';',"你的道具栏空间不足够哦，请整理一下吧。");
    		return 0;
	}
	
	rate = random(100);
	if (rate<30) 
		item = 0;
	else if (rate<40)
	{
		item = new ("item/91/9102");//造化丹
		item->set_amount(5);
	}
	else if (rate<50)
	{
		item = new ("item/91/9121");//活心丹
		item->set_amount(5);
	}
	else if (rate<60)
	{
		item = new ("/item/01/0200");//红木宝箱
		item->set_amount(5);
	}
	else if (rate<70)
	{
		item = new ("/item/01/0201");//青铜宝箱
		item->set_amount(5);
	}
	else if (rate<90)
		item = new ("item/44/4488");//宠物技能丹
	else if (rate<97)
	{
		cTmp = BOOK_FILE->get_book_file();
		item = new (cTmp);//随机门派技能进阶书
	}
	else if (rate<100)//蓝装
	{
		if ((level=who->get_level()+10)>120) level=120;
		nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)],0,level,101+random(6));
		tmp = nTmp[random(sizeof(nTmp))];
		if ( !stringp(tmp) )
			return 0;
		item = new(tmp);
		ITEM_EQUIP_D->init_equip_prop_1(item);
	}
	if ( item )
	{
		send_user(who,"%c%s",'!',"恭喜您！您打开重阳礼包得到了"+item->get_name());
		p = item->move2(who);
		item->add_to_user(p);	
	}
	else
	{
		who->add_cash(5000);
		send_user(who,"%c%s",'!',"恭喜您！您打开重阳礼包得到了5000金");
	}
	gift->add_amount(-1);
	return 0;
}

