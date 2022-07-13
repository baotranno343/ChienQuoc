
#include <ansi.h>
#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
    inherit COMBINED;


int * allexp = ({ 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 11891, 500000, 500000, 14010, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, });

// 函数：可对目标使用的物品
int get_max_combined() { return 10000; }
int get_item_type_2() { return ITEM_TYPE_2_USABLE2; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name( "Hoa Hồng" );
        set_picid_1(3005);
        set_picid_2(3005);
        set_value(2000000);
        set_amount(1);
}

// 函数：获取描述
string get_desc()
{
        return "Hoa hồng dùng để tặng cho người mà bạn yêu nhất \nNếu có thể thì Nữ giới tặng hoa cho Nam giới hoặc \nGay tặng hoa cho Gay";
}

// 函数：使用效果
int get_use_effect( object me, object who ) { return __FILE__ ->get_use_effect_callout(me, who); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object who )
{
	int p,level,exp,gender,tId,tId1;
	object *team,user;
    string *nTmp,tmp,cTmp,leader,result="";
	me = this_player();
	tId = me->get_team_id();
	tId1 = who->get_team_id();
	if ( !who->is_user() )
	{
		send_user(me,"%c%s",'!',"Bạn chỉ có thể tặng Hoa cho người chơi!");
		return 0;
	}
	if ( who == me )
	{
		send_user(me,"%c%s",'!',"Không thể tự tặng hoa cho chính mình!");
		return 0;
	}
	if ( who->get_gender() == 2 )
	{
		send_user(me,"%c%s",'!',"Không thể tặng Hoa cho Nữ giới!");
		return 0;
	}
/*	if( tId != tId1 )
	{
		send_user(me,"%c%s",'!',"Không thể tặng Hoa cho người bạn không yêu!");
		return 0;
	}
	if(  !arrayp( team = me->get_team() ) || sizeof(team) == 1 )
	{
		send_user(me,"%c%s",'!',"Hãy lập tổ đội với 1 người mà bạn yêu thương!");
		return 0;
	}
	if( sizeof(team) > 2 )
	{
		send_user(me,"%c%s",'!',"Rốt cuộc thì bạn yêu ai?!");
		return 0;
	}
	if ( !stringp(leader=me->get_leader()) || to_int(leader) != me->get_number() )
	{
		send_user(me,"%c%s",'!',"Bạn không phải là đội trưởng!");
		return 0;
	}*/
	level = who->get_level();
	exp = allexp[level];
//	me->add_cash(200000);
	who->add_exp(exp);
	who->add_cash(200000);
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 5914, 1, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 5916, 1, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 5917, 2, OVER_BODY, PF_ONCE );
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 5915, 3, OVER_BODY, PF_ONCE );
//	send_user( me,"%c%s",';', sprintf("Bạn đã tặng Hoa Hồng cho %s, và nhận được %d điểm kinh nghiệm.", who->get_name(), exp) );
	send_user( me,"%c%s",';', sprintf("Bạn đã tặng Hoa Hồng cho %s, gửi kèm ngàn lời yêu thương.", who->get_name()) );
	send_user( who,"%c%s",';', sprintf("%s đã tặng bạn Hoa Hồng, gửi kèm ngàn lời yêu thương đồng thời bạn nhận được %d điểm kinh nghiệm và 200.000 lượng.", me->get_name(), exp) );
//	USER_D->user_channel(sprintf("Nghe nói: %s (%d) : đã tặng 1 đoá Hoa Hồng cho: %s (%d) : Kèm theo ngàn lời yêu thương..! Thật khiến người ta ghen ghét !!! . ", me->get_name(), me->get_number(), who->get_name(), who->get_number() ));
	cTmp = sprintf(HIY "Nghe nói "HIG"%s "HIY" đã tặng 1 đoá Hoa Hồng cho "HIG"%s "HIY " gửi kèm theo ngàn lời yêu thương từ tận đáy lòng！！！", me->get_name(), who->get_name() );
	send_user( CHAT_D->get_chat(), "%c%s", 0xA3, cTmp );
/*	switch( random(5) )
	{
	case 1 :
		set_effect(who, EFFECT_USER_AP, 1800);
		who->set_save( "ap10#", 10 );
		USER_ENERGY_D->count_ap(who);
		send_user( who, "%c%w%w%c", 0x81, 5015, 1800, EFFECT_GOOD );
		send_user( who, "%c%w%s", 0x82, 5015, "Ngoại Công +10%" );
		break;
	case 2 :
		set_effect(who, EFFECT_USER_CP, 1800);
		who->set_save( "cp10#", 10 );
		USER_ENERGY_D->count_cp(who);
		send_user( who, "%c%w%w%c", 0x81, 5310, 1800, EFFECT_GOOD );
		send_user( who, "%c%w%s", 0x82, 5310, "Nội Công +10%" );
		break;
	case 3:
		set_effect(who, EFFECT_USER_DP, 1800);
		who->set_save( "03291#", 20 );
		USER_ENERGY_D->count_dp(who);
		send_user( who, "%c%w%w%c", 0x81, 4236, 1800, EFFECT_GOOD );
		send_user( who, "%c%w%s", 0x82, 4236, "Ngoại Kháng +20%" );
		break;
	case 4 :
		set_effect(who, EFFECT_USER_PP, 1800);
		who->set_save( "9165#", 20 );
		USER_ENERGY_D->count_pp(who);
		send_user( who, "%c%w%w%c", 0x81, 9165, 1800, EFFECT_GOOD );
		send_user( who, "%c%w%s", 0x82, 9165, "Nội Kháng +20%" );
		break;
	default :
		set_effect(who, EFFECT_USER_HP, 1800);
		who->set_save( "05014", who->get_max_hp()*30/100 );
		USER_ENERGY_D->count_max_hp(who);
		send_user( who, "%c%w%w%c", 0x81, 5116, 1800, EFFECT_GOOD );
		send_user( who, "%c%w%s", 0x82, 5116, "khí huyết +30%" );
		break;
	}*/
	return 1;
}
