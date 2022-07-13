#include <ansi.h>
inherit ITEM;

int get_item_value() {return 5 ;}
int get_item_value_2() {return 5 ;}
int get_item_number() {return 10001100 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("Võ Lâm Bại Hoại Lễ Bao");
        set_picid_1(3025);
        set_picid_2(3025);
        set_value(198);
        
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Giết Võ Lâm Bại Hoại gia tăng 50% kinh nghiệm \nSau khi tiến vào trong bản đồ Tập Kích Môn Phái \nhãy mua 1 cái để tăng thêm 50% kinh nghiệm";
}

string get_short()
{
	return "Giết Võ Lâm Bại Hoại gia tăng 50% kinh nghiệm \nSau khi tiến vào trong bản đồ Tập Kích Môn Phái \nhãy mua 1 cái để tăng thêm 50% kinh nghiệm";
}
	
string get_loop_desc(object me)
{
	return "Giết Võ Lâm Bại Hoại gia tăng 50% kinh nghiệm";
}

int give_item_to_user( object who) 
{
	who->set("wg_bl_15",1);
	send_user(who, "%c%s", ';', "Bạn sẽ nhận thêm 50% kinh nghiệm khi giết Võ Lâm Bại Hoại");
	return 1;
}
//购买前提示
/*int question_before_buy(object who,string arg)
{
	if ( stringp(who->get("buy_vip_package")) )
	{
		who->delete("buy_vip_package");	
		return 0;
	}
	who->set("buy_vip_package",arg);
	send_user(who,"%c%c%w%s",':',3,0,sprintf("你是否确定对当前角色ID：%s（%d）绑定VIP包？\n"ESC"确定\nvip 1\n"ESC"取消\nvip 1\n",who->get_name(),who->get_number()));
	return 1;
}*/
//每次允许出售的数量
int get_sell_amount() { return 1;}
