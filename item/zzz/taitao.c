#include <item.h>
#include <ansi.h>
#include <task.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
//inherit COMBINED;

int get_item_value() {return 200 ;}
int get_item_value_2() {return 200 ;}
//int get_item_number() {return 10001029 ;}
int get_item_color() {return 2 ;}

// 修理道具
int is_repair() {return 1 ;} 

// 函数：构造处理
void create()
{
        set_name( "Ngọc Tái Tạo" );
        set_picid_1(8900);
        set_picid_2(8900);
        set_value(50);
		//set_amount(1);
        set_record(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sử dụng kéo tới trang bị Lam Kim hoặc Hoàng Kim sẽ\ntái tạo lại chỉ số của Trang bị đó \nMỗi lần tái tạo đều phải tiêu hao một số ngân lượng nhất định. \n."; 
}

int move_item(object me, object item, object equip)
{
	return __FILE__->move_item_callout(me, item, equip, 1);
}

int move_item2(object me, object item, object equip)
{
	return __FILE__->move_item_callout(me, item, equip, 2);
}

int move_item_callout(object me, object item, object equip, int type)
{
	int p, i, rate;
	string result;
	object equip1;
	if( !equip->is_equip() ) return 0;     
	if( equip->is_equip())
	{
		i=equip->get_equip_type();
		if ( i!=WEAPON_TYPE&&i!=ARMOR_TYPE&&i!=HEAD_TYPE&&i!=BOOTS_TYPE&&i!=WAIST_TYPE&&i!=NECK_TYPE)
			return 0;
	}
		if ( equip->get_item_color()<1 || equip->get_item_color()>=3 )
		{
		write_user(me, ECHO"Không phải trang bị Lam Kim hoặc Hoàng Kim, không thể tái tạo");
		return 1;
		}
	rate = random(100);	
if ( equip->get_equip_type()==WEAPON_TYPE )	
{	
	if (me->get_cash() < equip->get_level()*12833 )
	{
		write_user(me, sprintf(ECHO"Ngân lượng không đủ %d, không thể tái tạo",equip->get_level()*12833 ));
		return 1;
	}
	if (type==1)
	{
		result = sprintf("Bạn muốn dùng "HIR "%d "NOR "lượng tái tạo "HIB"%s "NOR "không ?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_level()*12833, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	if ( equip->get_item_color()==1 ) 
	{
		if ( rate < 8 )
		{
		equip->set_item_color(2);
		"/sys/item/equip"->init_equip_prop_3(equip);
		}
		else
		{
		equip->delete( "ap+"  );
		equip->delete( "cp+"  );
		equip->add("ap+",random(200));
		equip->add("cp+",random(200));
		"/sys/item/equip"->init_equip_prop_1(equip);
		}
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	else if ( equip->get_item_color()==2 ) 
	{
		equip->delete( "ap+"  );
		equip->delete( "cp+"  );
		equip->add("ap+",random(200));
		equip->add("cp+",random(200));
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	me->add_cash(-equip->get_level()*12833);
	send_user(me,"%c%s",';',sprintf("Bạn đã tái tạo chỉ số của "HIY"%s "NOR " thành công!!!",equip->get_name() ));
	return 1;
}
else if ( equip->get_equip_type()==ARMOR_TYPE )	
{	
	if (me->get_cash() < equip->get_level()*12833 )
	{
		write_user(me, sprintf(ECHO"Ngân lượng không đủ %d, không thể tái tạo",equip->get_level()*12833 ));
		return 1;
	}
	if (type==1)
	{
		result = sprintf("Bạn muốn dùng "HIR "%d "NOR "lượng tái tạo "HIB"%s "NOR "không ?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_level()*12833, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	if ( equip->get_item_color()==1 ) 
	{
		if ( rate < 8 )
		{
		equip->set_item_color(2);
		"/sys/item/equip"->init_equip_prop_3(equip);
		}
		else
		{
		equip->delete( "dp+"  );
		equip->delete( "pp+"  );
		equip->delete( "hp+"  );
		equip->delete( "mp+"  );
		equip->delete( "sp+"  );
		equip->add("dp+",random(200));
		equip->add("pp+",random(200));
		equip->add("hp+",random(1000));
		equip->add("mp+",random(1000));
		equip->add("sp+",random(200));
		"/sys/item/equip"->init_equip_prop_1(equip);
		}
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	else if ( equip->get_item_color()==2 ) 
	{
		equip->delete( "dp+"  );
		equip->delete( "pp+"  );
		equip->delete( "hp+"  );
		equip->delete( "mp+"  );
		equip->delete( "sp+"  );
		equip->add("dp+",random(200));
		equip->add("pp+",random(200));
		equip->add("hp+",random(1000));
		equip->add("mp+",random(1000));
		equip->add("sp+",random(200));
		"/sys/item/equip"->init_equip_prop_3(equip);
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	me->add_cash(-equip->get_level()*12833);
	send_user(me,"%c%s",';',sprintf("Bạn đã tái tạo chỉ số của "HIY"%s "NOR " thành công!!!",equip->get_name() ));
	return 1;
}
else if ( equip->get_equip_type()==HEAD_TYPE )	
{	
	if (me->get_cash() < equip->get_level()*12833 )
	{
		write_user(me, sprintf(ECHO"Ngân lượng không đủ %d, không thể tái tạo",equip->get_level()*12833 ));
		return 1;
	}
	if (type==1)
	{
		result = sprintf("Bạn muốn dùng "HIR "%d "NOR "lượng tái tạo "HIB"%s "NOR "không ?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_level()*12833, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	if ( equip->get_item_color()==1 ) 
	{
		if ( rate < 8 )
		{
		equip->set_item_color(2);
		"/sys/item/equip"->init_equip_prop_3(equip);
		}
		else
		{
		equip->delete( "dp+"  );
		equip->delete( "pp+"  );
		equip->delete( "hp+"  );
		equip->delete( "mp+"  );
		equip->delete( "sp+"  );
		equip->add("dp+",random(200));
		equip->add("pp+",random(200));
		equip->add("hp+",random(500));
		equip->add("mp+",random(500));
		equip->add("sp+",random(150));
		"/sys/item/equip"->init_equip_prop_1(equip);
		}
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	else if ( equip->get_item_color()==2 ) 
	{
		equip->delete( "dp+"  );
		equip->delete( "pp+"  );
		equip->delete( "hp+"  );
		equip->delete( "mp+"  );
		equip->delete( "sp+"  );
		equip->add("dp+",random(200));
		equip->add("pp+",random(200));
		equip->add("hp+",random(500));
		equip->add("mp+",random(500));
		equip->add("sp+",random(150));
		"/sys/item/equip"->init_equip_prop_3(equip);
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	me->add_cash(-equip->get_level()*12833);
	send_user(me,"%c%s",';',sprintf("Bạn đã tái tạo chỉ số của "HIY"%s "NOR " thành công!!!",equip->get_name() ));
	return 1;
}
else if ( equip->get_equip_type()==NECK_TYPE )	
{	
	if (me->get_cash() < equip->get_level()*12833 )
	{
		write_user(me, sprintf(ECHO"Ngân lượng không đủ %d, không thể tái tạo",equip->get_level()*12833 ));
		return 1;
	}
	if (type==1)
	{
		result = sprintf("Bạn muốn dùng "HIR "%d "NOR "lượng tái tạo "HIB"%s "NOR "không ?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_level()*12833, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	if ( equip->get_item_color()==1 ) 
	{
		if ( rate < 8 )
		{
		equip->set_item_color(2);
		"/sys/item/equip"->init_equip_prop_3(equip);
		}
		else
		{
		equip->delete( "ap+"  );
		equip->delete( "cp+"  );
		equip->delete( "pp+"  );
		equip->delete( "sp+"  );
		equip->add("ap+",random(150));
		equip->add("cp+",random(150));
		equip->add("pp+",random(100));
		equip->add("sp+",random(100));
		"/sys/item/equip"->init_equip_prop_1(equip);
		}
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	else if ( equip->get_item_color()==2 ) 
	{
		equip->delete( "ap+"  );
		equip->delete( "cp+"  );
		equip->delete( "pp+"  );
		equip->delete( "sp+"  );
		equip->add("ap+",random(150));
		equip->add("cp+",random(150));
		equip->add("pp+",random(100));
		equip->add("sp+",random(100));
		"/sys/item/equip"->init_equip_prop_3(equip);
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	me->add_cash(-equip->get_level()*12833);
	send_user(me,"%c%s",';',sprintf("Bạn đã tái tạo chỉ số của "HIY"%s "NOR " thành công!!!",equip->get_name() ));
	return 1;
}
else if ( equip->get_equip_type()==WAIST_TYPE )	
{	
	if (me->get_cash() < equip->get_level()*12833 )
	{
		write_user(me, sprintf(ECHO"Ngân lượng không đủ %d, không thể tái tạo",equip->get_level()*12833 ));
		return 1;
	}
	if (type==1)
	{
		result = sprintf("Bạn muốn dùng "HIR "%d "NOR "lượng tái tạo "HIB"%s "NOR "không ?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_level()*12833, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	if ( equip->get_item_color()==1 ) 
	{
		if ( rate < 8 )
		{
		equip->set_item_color(2);
		"/sys/item/equip"->init_equip_prop_3(equip);
		}
		else
		{
		equip->delete( "dp+"  );
		equip->delete( "pp+"  );
		equip->delete( "hp+"  );
		equip->delete( "mp+"  );
		equip->delete( "sp+"  );
		equip->add("dp+",random(100));
		equip->add("pp+",random(100));
		equip->add("hp+",random(1500));
		equip->add("mp+",random(1500));
		equip->add("sp+",random(150));
		"/sys/item/equip"->init_equip_prop_1(equip);
		}
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	else if ( equip->get_item_color()==2 ) 
	{
		equip->delete( "dp+"  );
		equip->delete( "pp+"  );
		equip->delete( "hp+"  );
		equip->delete( "mp+"  );
		equip->delete( "sp+"  );
		equip->add("dp+",random(100));
		equip->add("pp+",random(100));
		equip->add("hp+",random(1500));
		equip->add("mp+",random(1500));
		equip->add("sp+",random(150));
		"/sys/item/equip"->init_equip_prop_3(equip);
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	me->add_cash(-equip->get_level()*12833);
	send_user(me,"%c%s",';',sprintf("Bạn đã tái tạo chỉ số của "HIY"%s "NOR " thành công!!!",equip->get_name() ));
	return 1;
}
else if ( equip->get_equip_type()==BOOTS_TYPE )	
{	
	if (me->get_cash() < equip->get_level()*12833 )
	{
		write_user(me, sprintf(ECHO"Ngân lượng không đủ %d, không thể tái tạo",equip->get_level()*12833 ));
		return 1;
	}
	if (type==1)
	{
		result = sprintf("Bạn muốn dùng "HIR "%d "NOR "lượng tái tạo "HIB"%s "NOR "không ?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_level()*12833, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	if ( equip->get_item_color()==1 ) 
	{
		if ( rate < 8 )
		{
		equip->set_item_color(2);
		"/sys/item/equip"->init_equip_prop_3(equip);
		}
		else
		{
		equip->delete( "dp+"  );
		equip->delete( "pp+"  );
		equip->delete( "hp+"  );
		equip->delete( "mp+"  );
		equip->delete( "sp+"  );
		equip->add("dp+",random(50));
		equip->add("pp+",random(50));
		equip->add("hp+",random(200));
		equip->add("mp+",random(200));
		equip->add("sp+",random(300));
		"/sys/item/equip"->init_equip_prop_1(equip);
		}
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	else if ( equip->get_item_color()==2 ) 
	{
		equip->delete( "dp+"  );
		equip->delete( "pp+"  );
		equip->delete( "hp+"  );
		equip->delete( "mp+"  );
		equip->delete( "sp+"  );
		equip->add("dp+",random(50));
		equip->add("pp+",random(50));
		equip->add("hp+",random(200));
		equip->add("mp+",random(200));
		equip->add("sp+",random(300));
		"/sys/item/equip"->init_equip_prop_3(equip);
		send_user( me, "%c%d%c", 0x31, getoid(equip), 0 );
	}
	me->add_cash(-equip->get_level()*12833);
	send_user(me,"%c%s",';',sprintf("Bạn đã tái tạo chỉ số của "HIY"%s "NOR " thành công!!!",equip->get_name() ));
	return 1;
}
	return 1;
}