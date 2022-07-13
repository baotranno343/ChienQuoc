#include <item.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
//inherit COMBINED;

int get_item_value() {return 5000 ;} 
int get_item_value_2() {return 5000 ;}
int get_item_color() {return 2 ;}
int is_ghepthucuoi() { return 1; }
// 修理道具
int is_repair() {return 1 ;} 

// 函数：构造处理
void create()
{
        set_name( "Chiến Thú Lệnh Cấp 1" );
        set_picid_1(4984);
        set_picid_2(4984);
		set_no_give(1);
        set_value(50);
		set_save("ghep",400);
		//set_amount(1);
        set_record(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Sử dụng kéo tới Thú Cưỡi Tiểu."; 
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
	int p;
	string result;
	object equip1;
    
	if ( equip->get_name()!="Tiểu Hồ Ly" &&
		equip->get_name()!="Tiểu Cá Voi" &&
		equip->get_name()!="Tiểu Đà Điểu" &&
		equip->get_name()!="Tiểu Gấu" &&
		equip->get_name()!="Tiểu Kiến" &&
		equip->get_name()!="Tiểu Mã" &&
		equip->get_name()!="Tiểu Rùa" &&
		equip->get_name()!="Tiểu Thần Thảm" &&
		equip->get_name()!="Tiểu Tuần Lộc" &&
		equip->get_name()!="Tiểu Thiên Ưng" &&
		equip->get_name()!="Tiểu Voi Địa" &&		
		equip->get_name()!="Đại Hồ Ly" &&
		equip->get_name()!="Đại Cá Voi" &&
		equip->get_name()!="Đại Đà Điểu" &&
		equip->get_name()!="Đại Gấu" &&
		equip->get_name()!="Đại Kiến" &&
		equip->get_name()!="Đại Mã" &&
		equip->get_name()!="Đại Rùa" &&
		equip->get_name()!="Đại Thần Thảm" &&
		equip->get_name()!="Đại Tuần Lộc" &&
		equip->get_name()!="Đại Thiên Ưng" &&
		equip->get_name()!="Đại Voi Địa" ) 
	{
		write_user(me, ECHO "Chỉ có thể Nâng Cấp Thú Cưỡi và Tiểu!");
		return 1;
	}
	if ( equip->get_lock_time() && equip->get_lock_time() < time() ) 
	{
		write_user(me, ECHO "Đã hết hạn sử dụng, không thể nâng cấp !");
		return 1;
	}
			if(USER_INVENTORY_D->get_free_count(me) < 2 )
			{
				write_user(me, ECHO "Hành trang của bạn không đủ 2 chỗ trống!");
				return 1;
			}
if ( equip->get_name()=="Tiểu Hồ Ly" )
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/cao/5");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Cá Voi" )
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/cavoi/2");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Đà Điểu" )
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/chim/8");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Gấu" )	
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/gau/11");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Kiến" )	
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/kien/14");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Mã" )	
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/ngua/17");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Rùa" )
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/rua/20");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Thần Thảm" )	
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/tham/23");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Tuần Lộc" )	
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/tuanloc/26");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Thiên Ưng" )	
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/ung/29");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
if ( equip->get_name()=="Tiểu Voi Địa" )	
{
	if (type==1)
	{
		result = sprintf("Bạn muốn nâng cấp "HIB"%s"NOR " không?\n"
			ESC "%c\n" ESC "\nmove ! %x# %d\n"
			, equip->get_name(), 1, getoid(item), get_d(equip) );
		send_user(me, "%c%c%s", 0x59, 1, result);
		return 1;
	}
	equip1 = new("item/chienthulenh/voi/32");
	p = equip1->move2(me,-1);
	equip1->add_to_user(p);
	
	USER_D->user_channel(sprintf("Bằng hữu "HIY "%s" NOR " vừa Nâng Cấp thành công "HIR "%s"NOR " và nhận được "HIY"%s "NOR ". ", me->get_name(),equip->get_name(),equip1->get_name() ));
	
	equip->remove_from_user();
	destruct( equip );
	 
    //item->add_amount(-1);
    item->remove_from_user();
    destruct( item );
	send_user(me,"%c%s",';',sprintf("Bạn nhận được "HIY"%s "NOR " !!!",equip1->get_name() ));
	return 1;
}
	return 1;
}