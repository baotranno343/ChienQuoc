#include <ansi.h>
#include <equip.h>
inherit ITEM;
inherit COMBINED;

// 函数：物品叠加上限
int get_max_combined() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Anh Hùng Phù Văn");
        set_picid_1(4952);
        set_picid_2(4952);
        set_amount(1);
        set_unit("块");
        set_value(20);
//        set_no_give(1);
//        set_no_sell(1); 
}

int is_usable() {return 1;}

int get_item_color() {return 1;}

// 函数：获取描述
string get_desc() 
{ 
        return "Trang sức đặc biệt của Chiến Quốc, sử dụng sẽ đạt được kinh nghiệm theo cấp độ người chơi";
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object gift) 
{
	int rate,p,level,exp,cash,limit_exp;
	object item;
       	string *nTmp,tmp,cTmp,result="";
	if ( (level=who->get_level() )<=10 )
	{
		send_user(who,"%c%s",';',"Cấp bậc của ngươi phải trên 10 mới được sử dụng");
		return 0;
	}
	exp = 10000+level*level*50;
	limit_exp=USER_EXP_D->get_upgrade_exp_limit(who);
	if (exp+who->get_upgrade_exp()>limit_exp)
	{
		send_user(who,"%c%s",';',"Bạn đạt được kinh nghiệm, sẽ vượt qua hạn mức cao nhất, vui lòng xử lý kinh nghiệm." );
		return 0;
	}
	result += sprintf("Bạn đạt được %d điểm Kinh nghiệm.",exp);
	who->add_exp(exp);
	send_user(who,"%c%s",';',result);
	gift->add_amount(-1);
	return 0;
}