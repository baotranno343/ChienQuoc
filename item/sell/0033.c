#include <item.h>
#include <ansi.h>

inherit ITEM;
inherit "/inh/item/diamond";
inherit COMBINED;

int get_item_value() {return 20 ;}
int get_item_value_2() {return 20 ;}
//int get_item_number() {return 10001028 ;}

// 函数：可使用物品
int get_item_type_2() { return ITEM_TYPE_2_DIAMOND; }
// 函数：需要确认卖出
int confirm_sell_item() { return 1; }

int get_item_color() {return 1 ;}

int is_luban() {return 1;}

// 函数：构造处理
void create()
{
        set_name("Lỗ Ban Bảo Thạch");
        set_picid_1(8973);
        set_picid_2(8973);
        set_unit("块");
        set_value(2000);
	//	set_save("knb2",5);
        set_level(1);
        set_amount(1);
}

string get_loop_desc(object me)
{
	return "Lỗ Ban Bảo Thạch chỉ sử dụng cho chế tạo kỹ năng nghề nghiệp. \n Khi làm thành phẩm xong cất trong “Phẩm vật phụ gia”, \n Có thể tăng thuộc tính của trang bị ngoài định mức. \n Mỗi lần làm chỉ có thể cất một Bảo Thạch. \n Bất luận có thành công hay không,";
}

// 函数：获取描述
string get_desc() 
{
	return "Lỗ Ban Bảo Thạch chỉ sử dụng cho chế tạo kỹ năng nghề nghiệp. \n Khi làm thành phẩm xong cất trong “Phẩm vật phụ gia”, \n Có thể tăng thuộc tính của trang bị ngoài định mức. \n Mỗi lần làm chỉ có thể cất một Bảo Thạch. \n Bất luận có thành công hay không,";
}

//生活技能附加
int init_equip(object item)
{
	return __FILE__->init_equip2(item);
}

//生活技能附加
int init_equip2(object item)
{
	int rate;
	object me;
	if ( !item->is_equip() )
		return 0;
	rate = random(100000);
	if( (me = this_player()) && is_god(me))
	{
		if ( me->get("lb") )
			rate = me->get("lb");
		tell_user(me,"Lỗ Ban Bảo Thạch %d ",rate);
	}
	if ( rate < 7000 )		//物理攻击提升40点
	{
		item->add("ap",40);
	}
	else if ( rate < 14000 )	//法术攻击提升40点
	{
		item->add("cp",40);
	}
	else if ( rate < 21000 )	//物理防御提高50点
	{
		item->add("dp",50);
	}
	else if ( rate < 28000 )	//法术防御提高50点
	{
		item->add("pp",50);
	}
	else if ( rate < 35000 )	//气血上限增加50点
	{
		item->add("hp",50);
	}    
	else if ( rate < 41000 )	//法力上限增加100点
	{
		item->add("mp",100);
	} 
	else if ( rate < 44000 )	//使命中目标的几率提高1%
	{
		item->add( "!%",100);
		item->add( "c!%",1);
		item->add( "t!%",1);
	} 	
	else if ( rate < 50000 )	//使暴击率提高1%
	{
		item->add( "double",100);
	} 	
	else if ( rate < 53000 )	//增加法术所造成的伤害效果12点
	{
		item->add( "cp+@",12);
	}
	else if ( rate < 56000 )	//增加法术所造成的治疗效果12点
	{
		item->add( "heal+@",12);
	}
	else if ( rate < 59000 )	//吸取给予对方物理伤害的1%做为自己的血气恢复
	{
		item->add( "hp*",1);
	}		
	else if ( rate < 62000 )	//吸取给予对方法术伤害的1%做为自己的法力恢复
	{
		item->add( "mp*",1);
	}
	else if ( rate < 69000 )	//每5秒回5点气血
	{
		item->add( "hp+@",5);
	}
	else if ( rate < 75000 )	//每5秒回5点法力
	{
		item->add( "mp+@",5);
	}
	else if ( rate < 79000 )	//物理攻击提升80点
	{
		item->add("ap",80);
	}
	else if ( rate < 83000 )	//法术攻击提升80点
	{
		item->add("cp",80);
	}
	else if ( rate < 86000 )	//物理防御提高100点
	{
		item->add("dp",100);
	}
	else if ( rate < 89000 )	//法术防御提高100点
	{
		item->add("pp",100);
	}
	else if ( rate < 92000 )	//气血上限增加100点
	{
		item->add("hp",100);
	}    
	else if ( rate < 95000 )	//法力上限增加200点
	{
		item->add("mp",200);
	} 		
	else if ( rate < 98000 )	//使命中目标的几率提高2%
	{
		item->add( "!%",200);
		item->add( "c!%",2);
		item->add( "t!%",2);
	} 
	else if ( rate < 99000 )	//使暴击率提高2%
	{
		item->add( "double",200);
	} 
	else if ( rate < 99499 )	//增加法术所造成的伤害效果33点
	{
		item->add( "cp+@",33);
	}
	else if ( rate < 99998 )	//增加法术所造成的治疗效果33点
	{
		item->add( "heal+@",33);
	}
	else if ( rate < 99999 )	//吸取给予对方物理伤害的5%做为自己的血气恢复
	{
		item->add( "hp*",5);
	}		
	else if ( rate < 100000 )	//吸取给予对方法术伤害的5%做为自己的法力恢复
	{
		item->add( "mp*",5);
	}
	return 1;	
}