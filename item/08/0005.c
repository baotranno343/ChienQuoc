#include <ansi.h>
#include <item.h>
#include <skill.h>

inherit COMBINED;
inherit ITEM;

int get_item_type() { return ITEM_TYPE_SPECIAL; }

// 函数：构造处理
void create()
{
        set_name("Hỷ Đường");
        set_picid_1(4253);
        set_picid_2(4253);
        set_value(1000);
        set_amount(1);
        set_record(1);
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{
	string name1,name2,x,y,z;
	int iLast;
	string tmp = HIY"Kết hôn Hỷ Đường.\n Sau khi sử dụng toàn bộ Khí Huyết và Pháp Lực sẽ được phục hồi, sau đó nhất định sẽ được các giải thưởng khác.";
	name1 = get("special");
	if ( !stringp(name1) || sscanf(name1,"%s|%s|%s|%s|%s",name1,name2,x,y,z) != 5 )
		return tmp;
		
	return sprintf(HIY" %s với %s vu %s niên %s nguyệt %s nhật kết hôn Hỷ Đường.\n Sau khi sử dụng toàn bộ Khí Huyết và Pháp Lực sẽ được phục hồi, sau đó nhất định sẽ được các giải thưởng khác.",name1,name2,x,y,z);
}
string get_special_desc(string cSpecial) 
{
	string name1,name2,x,y,z;
	int iLast;
	string tmp = "[Có thể sử dụng]"HIY"Kết hôn Hỷ Đường.\n Sau khi sử dụng toàn bộ Khí Huyết và Pháp Lực sẽ được phục hồi, sau đó nhất định sẽ được các giải thưởng khác.";
	name1 = cSpecial;
	if ( !stringp(name1) || sscanf(name1,"%s|%s|%s|%s|%s",name1,name2,x,y,z) != 5 )
		return tmp;
		
	return sprintf("[Có thể sử dụng]"HIY" %s với %s vu %s niên %s nguyệt %s nhật kết hôn Hỷ Đường.\n Sau khi sử dụng toàn bộ Khí Huyết và Pháp Lực sẽ được phục hồi, sau đó nhất định sẽ được các giải thưởng khác.",name1,name2,x,y,z);
}
int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,cash;
	string name1,name2,x,y,z,cSpecial;
	object item;
	
	if ( gone_time(who->get_save("xitang")) < 3600 )
	{
		send_user(who,"%c%s",'!',"Ngươi đã dùng Hỷ Đường trước đó nhưng chưa đủ 1 giờ, hãy dùng tiếp sau !");
		return 0;	
	}
	who->set_hp(who->get_max_hp());
	who->set_mp(who->get_max_mp());
	who->set_save("xitang",time());
        send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9154, 1, OVER_BODY, PF_ONCE );      
	cSpecial = gift->get("special");
	gift->add_amount(-1);
	rate = random(100);
	if ( rate < 30 )
		cash = 10000;
	else if ( rate < 55 )	//Tàng Bảo Đồ
	{
		item = new("item/std/8000");
	}
	else if ( rate < 58 )	//Phục Sinh Đơn
	{
		item = new("item/91/9178");
	}
	else if ( rate < 59 )	//Huyết Thạch
	{
		item = new("item/08/0003");
	}
	else if ( rate < 60 )	//Pháp Lực Thạch
	{
		item = new("item/08/0004");
	}
	
	if ( item )
	{
		p = item->move(who,-0);
		if ( !p )
		{
			destruct(item);
		}
		else
		{
			item->add_to_user(p);	
			if ( stringp(cSpecial) && sscanf(cSpecial,"%s|%s|%s|%s|%s",name1,name2,x,y,z) == 5 )
				CHAT_D->sys_channel(0,sprintf(HIY" %s "HIG"Ngoạn gia sử dụng Hỷ Đường đạt được "HIY" %s "HIG" với "HIY" %s "HIG" chúc phúc, đồng thời đạt được "HIR" %s "HIG" sự vui mừng ngoài ý muốn!",who->get_name(),name1,name2,item->get_name()));
			
		}
	}
	else if (  cash )
	{
		who->add_cash(cash);
		if ( stringp(cSpecial) && sscanf(cSpecial,"%s|%s|%s|%s|%s",name1,name2,x,y,z) == 5 )
			CHAT_D->sys_channel(0,sprintf(HIY" %s "HIG"Ngoạn gia sử dụng Hỷ Đường đạt được "HIY" %s "HIG" với "HIY" %s "HIG" chúc phúc, đồng thời đạt được "HIR" %d lượng "HIG" sự vui mừng ngoài ý muốn!",who->get_name(),name1,name2,cash));

	}	
	return 0;
}
