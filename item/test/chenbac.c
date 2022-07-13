
#include <item.h>
#include <effect.h>
#include <skill.h>
inherit ITEM;
inherit COMBINED;

//int * allexp = ({ 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, 444385, });
int * allexp = ({ 400, 900, 1123, 2123, 3123, 4123, 5123, 6123, 7123, 8123, 9123, 10123, 15123, 20123, 25123, 30123, 35123, 40123, 45123, 50123, 55123, 60123, 65123, 70123, 75123, 80123, 85123, 90123, 95123, 100123, 110123, 125123, 132123, 133123, 134123, 135123, 140123, 141123, 142123, 143123, 144123, 145123, 146123, 147123, 148123, 149123, 150123, 155123, 160123, 161123, 162123, 163123, 164123, 165123, 170123, 171123, 172123, 173123, 174123, 175123, 180123, 181123, 182123, 183123, 184123, 185123, 186123, 187123, 188123, 189123, 190123, 191123, 192123, 193123, 194123, 195123, 200123, 205123, 210123, 215123, 220123, 225123, 231123, 232123, 233123, 234123, 235123, 240123, 241123, 242123, 243123, 244123, 245123, 250123, 251123, 252123, 243123, 254123, 255123, 260123, 264123, 265123, 270123, 271123, 272123, 273123, 274123, 275123, 280123, 281123, 282123, 283123, 284123, 285123, 286123, 287123, 289123, 290123, 291123, 292123, 293123, 294123, 295123, 300123, 301123, 302123, 303123, 304123, 305123, 306123, 307123, 308123, 309123, 310123, 311123, 312123, 313123, 314123, 315123, 325123, 335123, 345123, 355123, 365123, 375123, 385123, 395123, 405123, 415123, 425123, 435123, });
// 函数：可对目标使用的物品
int get_max_combined() { return 10000; }
int get_item_type_2() { return ITEM_TYPE_2_USABLE2; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
        set_name( "Chén Bạc" );
        set_picid_1(3507);
        set_picid_2(3507);
        set_value(100);
        set_amount(1);
}

// 函数：获取描述
string get_desc()
{
        return "Lễ Té nước sử dụng loại máy móc bằng bạc, có thể chúc phúc cho mục tiêu,\n không thể sử dụng cho bản thân.";
}

// 函数：使用效果
int get_use_effect( object me, object who ) { return __FILE__ ->get_use_effect_callout(me, who); }

// 函数：使用效果(在线更新)
int get_use_effect_callout( object me, object who )
{
	int p,level,exp;
       	string *nTmp,tmp,cTmp,result="";
	me = this_player();
	if ( !who->is_user() )
	{
		send_user(me,"%c%s",'!',"Bạn chỉ có thể chúc phúc cho người chơi!");
		return 0;
	}
	if ( who == me )
	{
		send_user(me,"%c%s",'!',"Không thể chúc phúc cho bản thân!");
		return 0;
	}
	level = who->get_level();
	exp = allexp[level];
	me->add_exp(exp);
//	who->add_exp(exp);
	send_user( get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 51131, 1, OVER_BODY, PF_ONCE );
	send_user( me,"%c%s",';', sprintf("Bạn đã chúc phúc cho %s, và nhận được %d điểm kinh nghiệm.", who->get_name(), exp) );
	send_user( who,"%c%s",';', sprintf("%s đã dùng Chén Bạc chúc phúc cho bạn !", me->get_name()) );
	switch( random(5) )
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
		send_user( who, "%c%w%s", 0x82, 5116, "Khí Huyết +30%" );
		break;
	}
	return 1;
}
