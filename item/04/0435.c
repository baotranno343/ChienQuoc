
#include <ansi.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;   
int ch,bb,*bb3,*bb4;
int card_id;
int card_time;

//设置变身卡ID
int set_card_id(int i) { return card_id = i;}
//获取变身卡ID
int get_card_id() { return card_id;}
//设置变身卡时间
int set_card_time(int i) { return card_time = i;}
//获取变身卡时间
int get_card_time() { return card_time;}
// 函数：叠加上限
int get_max_combined() { return 1; }
// 函数：构造处理
void create()
{
	bb3 = ({800,8010,8011,8012,8013,402,352,4143});
	bb4 = ({954,953,952,951,950});
        ch=random(100);
        if (ch>70) bb=bb3[random(sizeof(bb3))];else if (ch>40) bb=bb4[random(sizeof(bb4))];else bb=351;
        set_name("Sừng Niên Thú");
        set_picid_1(9986);
        set_picid_2(9986);
        set_value(100);
        set_card_id(bb);
        set_card_time(3600);
        set_amount(1);
}
// 函数：获取描述
string get_desc() 
{ 
        return "Đánh bại Niên Thú có được Sừng Niên Thú \nĐem tới Thần Tiên Gia Gia đổi lấy lì xì năm mới……"; 
}

int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}
//使用后的影响
int get_use_effect_callout( object who,object item) 
{
	send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("Ngươi muốn sử dụng %s không ? \n"ESC"Chấp nhận\nuse ! %x#\n"ESC"Huỷ bỏ",item->get_name(),getoid(item))); 
	return 0;
}

// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	int hp,pp,dp,zz;

	if ( "sys/sys/magic_card"->change_shape(who,item->get_card_id(),item->get_card_time()) != 1 )
		return 0;

	who->set_2("magic_card.id",9999);
	if(item->get_card_id()==351)
	{
		zz=random(2);
		if (zz==1)
		{
			hp = who->get_max_hp()/5;
			hp= -hp;
			who->set_2("magic_card.hp",hp);
			USER_ENERGY_D->count_max_hp(who);
		}
		if (zz==0)
		{
			pp = who->get_pp()/10;
			pp= -pp;
			who->set_2("magic_card.pp",pp);
			USER_ENERGY_D->count_pp(who);
		
			dp = who->get_dp()/10;
			dp= -dp;
			who->set_2("magic_card.dp",dp);
			USER_ENERGY_D->count_dp(who);
		}
	}
	if(item->get_card_id()==800||item->get_card_id()==8010||item->get_card_id()==8011||item->get_card_id()==8012||item->get_card_id()==8013||item->get_card_id()==402||item->get_card_id()==352||item->get_card_id()==4143)
	{
		hp = who->get_max_hp()/10;
		who->set_2("magic_card.hp",hp);
		USER_ENERGY_D->count_max_hp(who);
	}
	if(item->get_card_id()==954||item->get_card_id()==953||item->get_card_id()==952||item->get_card_id()==951||item->get_card_id()==950)
	{
		pp = who->get_pp()/10;
		who->set_2("magic_card.pp",pp);
		USER_ENERGY_D->count_pp(who);
	
		dp = who->get_dp()/10;
		who->set_2("magic_card.dp",dp);
		USER_ENERGY_D->count_dp(who);
	}
	return 1;
}

