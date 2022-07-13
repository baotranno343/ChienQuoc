#include <ansi.h>
#include <skill.h>
inherit COMBINED;
inherit ITEM;

int get_item_value() {return 450 ;}
int get_item_value_2() {return 380 ;}
int get_item_number() {return 13 ;}
int get_item_color() {return 1 ;}

// 函数：构造处理
void create()
{
        set_name("Chiến Quốc Lệnh");	//绑定的
        set_picid_1(0096);
        set_picid_2(0096);
        set_value(10);
        set_no_give(1);		
        set_no_sell(1); 
        set_amount(1);
        set_record(1);
}
int is_usable() {return 1;}
// 函数：获取描述
string get_desc() 
{ 
        return "Lệnh bài thần kì, sau khi sử dụng có thể tiếp tục duy trì trong vòng 1 tiếng đồng hồ mới mất đi\n giết quái vật có thể đạt được gấp bốn Kinh nghiệm. (Hiệu quả của lệnh bài không thể lặp lại)"; 
}
// 函数：获取描述(持续)加血
string get_loop_desc( object me )
{
	return "Trong một tiếng đồng hồ có thể đạt được Kinh nghiệm nhân bốn.";
}
int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me,this_object());	
}

int get_use_effect_callout( object who,object item) 
{
	int i,iWeek;
	if ( gone_time( who->get_login_time() )+ who->get_game_time()<who->get_extra_double_time())
	{
		send_user( who, "%c%c%w%s", ':', 3, 0,sprintf("你身上已经有一个战国令在产生作用，你确定要覆盖它的效果吗？\n"ESC"确定\nuse ! %x#\n"ESC"取消",getoid(item))); 
		return 0;
	}
	iWeek = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
	if (who->get_save_2("double_time.week")!=iWeek)
	{
		who->set_save_2("double_time.week", iWeek);
		who->set_save_2("double_time.time", 0);		//双
		who->set_save_2("double_time.time1", 0);	//战国令
		who->set_save_2("double_time.time2", 0);	//战国号角
	}
	if ( who->get_save_2("double_time.time1") >= 25 )
	{
		send_user(who,"%c%s",'!',"你本周可使用战国令已经达到了使用上限。");
		return 0;	
	}
	who->add_save_2("double_time.time1",1);
	i = gone_time( who->get_login_time() );	
	who->set_extra_double_time(i+ who->get_game_time()+3600);
	send_user( who, "%c%w%w%c", 0x81, 9998, 3600, EFFECT_GOOD );
	return 1;
}

// 函数：使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me, this_object() ); }

// 函数：使用效果(在线更新)
int confirm_use_callout( object who, object item )
{
	int i,iWeek;

	iWeek = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
	if (who->get_save_2("double_time.week")!=iWeek)
	{
		who->set_save_2("double_time.week", iWeek);
		who->set_save_2("double_time.time", 0);		//双
		who->set_save_2("double_time.time1", 0);	//战国令
		who->set_save_2("double_time.time2", 0);	//战国号角
	}
	if ( who->get_save_2("double_time.time1") >= 25 )
	{
		send_user(who,"%c%s",'!',"你本周可使用战国令已经达到了使用上限。");
		return 0;	
	}
	who->add_save_2("double_time.time1",1);
	i = gone_time( who->get_login_time() );	
	who->set_extra_double_time(i+ who->get_game_time()+3600);
	send_user( who, "%c%w%w%c", 0x81, 9998, 3600, EFFECT_GOOD );
	return 1;
}