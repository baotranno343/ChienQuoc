#include <ansi.h>
#include <skill.h>
inherit COMBINED;
inherit ITEM;

int get_item_value() {return 175 ;}
int get_item_value_2() {return 140 ;}
int get_item_number() {return 10001005 ;}
int get_item_color() {return 1 ;}

// 函数:构造处理
void create()
{
        set_name("Tù Và Chiến Quốc");
        set_picid_1(0095);
        set_picid_2(0095);
        set_value(100);
        set_amount(1);
        set_record(1);
}
int is_usable() {return 1;}
// 函数:获取描述
string get_desc() 
{ 
        return "Tù và thần kỳ chỉ có tác dụng khi Trưởng nhóm sử dụng.\n Tất cả thành viên trong nhóm đều được nhận thêm 20 %  điểm Kinh nghiệm khi tiêu diệt quái vật trong suốt 1 tiếng."; 
}
// 函数:获取描述(持续)加血
string get_loop_desc( object me )
{
	return "Trong 1 giờ tất cả thành viên trong nhóm tăng 20% kinh nghiệm.";
}
int get_use_effect( object me ) 
{
	return __FILE__->get_use_effect_callout(me, this_object());	
}

int get_use_effect_callout( object who, object item) 
{
	int iWeek;
	
	if ( time() < who->get_extra_exp_time() )
	{
		send_user( who,  "%c%c%w%s",  ':',  3,  0, sprintf("Ngươi vẫn còn thời gian sử dụng Tù Và Chiến Quốc, Muốn dùng đè lên không?\n"ESC"Chấp nhận\nuse ! %x#\n"ESC"Huỷ bỏ", getoid(item))); 
		return 0;
	}
	
	iWeek = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
	if (who->get_save_2("double_time.week")!=iWeek)
	{
		who->set_save_2("double_time.week",  iWeek);
		who->set_save_2("double_time.time",  0);		//双
		who->set_save_2("double_time.time1",  0);	//战国令
		who->set_save_2("double_time.time2",  0);	//战国号角
	}
	if ( who->get_save_2("double_time.time2") >= 25 )
	{
		send_user(who, "%c%s", '!', "Ngươi đã sử dụng tới giới hạn cao nhất.");
		return 0;	
	}
	if ( who->get_online_rate() == 50 )
	{
		send_user(who, "%c%s", '!', "Ngươi đã mệt, Không được sử dụng nữa.");
		return 0;	
	}
	else if ( who->get_online_rate() == 0 )
	{
		send_user(who, "%c%s", '!', "Ngươi không khoẻ, Không được sử dụng nữa.");
		return 0;	
	}
	who->add_save_2("double_time.time2", 1);
	who->set_extra_exp_time(time()+3600);
	send_user( who,  "%c%w%w%c",  0x81,  9999,  3600,  EFFECT_GOOD );
	return 1;
}
// 函数:使用效果
int confirm_use( object me ) { return __FILE__ ->confirm_use_callout( me,  this_object() ); }

// 函数:使用效果(在线更新)
int confirm_use_callout( object who,  object item )
{
	int iWeek;
	
	iWeek = (time() - 4 * 24*3600+8*3600) / (7*24*3600);
	if (who->get_save_2("double_time.week")!=iWeek)
	{
		who->set_save_2("double_time.week",  iWeek);
		who->set_save_2("double_time.time",  0);		//双
		who->set_save_2("double_time.time1",  0);	//战国令
		who->set_save_2("double_time.time2",  0);	//战国号角
	}
	if ( who->get_save_2("double_time.time2") >= 25 )
	{
		send_user(who, "%c%s", '!', "Ngươi đã sử dụng tới giới hạn cao nhất.");
		return 0;	
	}
	if ( who->get_online_rate() == 50 )
	{
		send_user(who, "%c%s", '!', "Ngươi đã mệt, Không được sử dụng nữa.");
		return 0;	
	}
	else if ( who->get_online_rate() == 0 )
	{
		send_user(who, "%c%s", '!', "Ngươi không khoẻ, Không được sử dụng nữa.");
		return 0;	
	}
	who->add_save_2("double_time.time2", 1);
	who->set_extra_exp_time(time()+3600);
	send_user( who,  "%c%w%w%c",  0x81,  9999,  3600,  EFFECT_GOOD );
	return 1;
}
