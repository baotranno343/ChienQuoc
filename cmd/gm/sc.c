
#include <ansi.h>
#include <city.h>

// 函数：命令处理
int main( object me, string arg )
{
        object who = me;
        string city, relation;
        string result;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        // 查看国家状态

        switch( arg )
        {
        case "齐" : case "01" : city = CITY_QI;  break;
        case "韩" : case "02" : city = CITY_HAN;  break;
        case "赵" : case "03" : city = CITY_ZHAO;  break;
        case "魏" : case "04" : city = CITY_WEI;  break;
        case "秦" : case "05" : city = CITY_QIN;  break;
        case "楚" : case "06" : city = CITY_CHU;  break;
        case "燕" : case "07" : city = CITY_YAN;  break;
                      default : city = "";  break;
        }

        if( city != "" )
        {
                result = sprintf( "国家：%-8s  等级：%8d  城主：%s %s，%s %s，%s %s\n", 
                        city->get_name(), city->get_level(),
                        city->get_master_name(), city->get_master(),
                        city->get_master_name_2(), city->get_master_2(),
                        city->get_master_name_3(), city->get_master_3() );
                result += sprintf( "城防：%8d  士兵：%8d  装备：%8d  训练：%8d  贡献：[%6d]\n", 
                        city->get_defence(), city->get_soldier(), city->get_armor(), city->get_training(), city->get_contribute() );
                result += sprintf( "资金：%10d  累积：%10d  税收：%10d  粮草：%10d\n", 
                        city->get_cash(), city->get_money(), city->get_tax(), city->get_food() );
                result += sprintf( "农业：%8d  渔业：%8d  矿业：%8d  工业：%8d  商业：%8d\n", 
                        city->get_agriculture(), city->get_fishculture(), city->get_mining(), 
                        city->get_industry(), city->get_commercial() );
                result += sprintf( "艺术：%8d  教育：%8d  宗教：%8d  安定：[%6d]  疾病：[%6d]\n", 
                        city->get_arts(), city->get_education(), city->get_religion(),
                        city->get_stability(), city->get_disease() );

                tell_user(me, result);

                result = "外交：";

                if( arg != "齐" && arg != "01" ) result += sprintf( "齐：(%d)%s  ", city->get_friend(1), city->get_relation_name(1) );
                if( arg != "韩" && arg != "02" ) result += sprintf( "韩：(%d)%s  ", city->get_friend(2), city->get_relation_name(2) );
                if( arg != "赵" && arg != "03" ) result += sprintf( "赵：(%d)%s  ", city->get_friend(3), city->get_relation_name(3) );
                if( arg != "魏" && arg != "04" ) result += sprintf( "魏：(%d)%s  ", city->get_friend(4), city->get_relation_name(4) );
                if( arg != "秦" && arg != "05" ) result += sprintf( "秦：(%d)%s  ", city->get_friend(5), city->get_relation_name(5) );
                if( arg != "楚" && arg != "06" ) result += sprintf( "楚：(%d)%s  ", city->get_friend(6), city->get_relation_name(6) );
                if( arg != "燕" && arg != "07" ) result += sprintf( "燕：(%d)%s  ", city->get_friend(7), city->get_relation_name(7) );

                tell_user(me, result);

                result = "税率：";

                result += sprintf( "本城购买：%2d%%%%  销售：%2d%%%%  外人购买：%2d%%%%  销售：%2d%%%%  分红：%2d%%%%\n", 
                        city->get_buy_tax(), city->get_sell_tax(), 
                        city->get_buy_tax_2(), city->get_sell_tax_2(), city->get_tax_2_cash() );

                tell_user(me, result);

		return 1;
        }

        // 查看人物状态

        if( arg && !( who = find_player(arg) ) ) 
        {
                notify( "您无法找到这个人。" );
		return 1;
        }

        result = sprintf( "玩家：%s(%d)  帮派：%s  %s\n", who->get_name(), who->get_number(), who->get_org_name(), 
                who->get_save("channel_manager") ? HIY "频道管理员" : "" );

        result += sprintf( "国家：%-8s  职业：%-8s  声望：%8d  贡献：%8d  体力：%8d\n",
                who->get_city_name(), who->get_occupation(), 
                who->get_repute(), who->get_contribute(), who->get_strength() );
        result += sprintf( "仁爱：%8d  正义：%8d  忠实：%8d  诚信：%8d  勇敢：%8d  智谋：%8d\n",
                who->get_gift_ra(), who->get_gift_zy(), who->get_gift_zs(), 
                who->get_gift_cx(), who->get_gift_yg(), who->get_gift_zm() );

        result += sprintf( "艺人：%3d 级 %10d 经验    农夫：%3d 级 %10d 经验\n", 
                who->get_occupation_level(JOB_ACTOR), who->get_occupation_exp(JOB_ACTOR),
                who->get_occupation_level(JOB_FARMER), who->get_occupation_exp(JOB_FARMER) );
        result += sprintf( "书生：%3d 级 %10d 经验    军官：%3d 级 %10d 经验    商人：%3d 级 %10d 经验\n", 
                who->get_occupation_level(JOB_SCHOLAR), who->get_occupation_exp(JOB_SCHOLAR),
                who->get_occupation_level(JOB_SOLDIER), who->get_occupation_exp(JOB_SOLDIER),
                who->get_occupation_level(JOB_TRADER), who->get_occupation_exp(JOB_TRADER) );

        tell_user(me, result);

        return 1;
}
