
#include <ansi.h>
#include <city.h>

// 函数：命令处理
int main( object me, string arg )
{
        object who = me;
        string city;
        string result;
        int i, cash, exp, pot, times, cash2, exp2, pot2, times2;

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
                result = sprintf( "%s分红记录：分红(剩余)/贡献", city->get_name() );
                for( i = 1; i <= 30; i ++ ) result = sprintf( "%s%s%d(%d)/%d, ", result, (i - 1) % 5 ? "" : "\n", 
                        city->get_salary_0(i), city->get_salary_2(i), city->get_contribute_0(i) );

                tell_user(me, result);

		return 1;
        }

        if( arg && !( who = find_player(arg) ) ) 
        {
                notify( "无法找到这位玩家。" );
		return 1;
        }

        result = sprintf( "奖励经验：%s(%d)  %d\n", who->get_name(), who->get_number(), who->get_exp() );

        times = who->get_log("#task");  exp = who->get_log("&task");
        times2 = who->get_log("#task2");  exp2 = who->get_log("&task2");  pot2 = who->get_log("*task2");

        result += sprintf( "使命(%d)：%d *%d ＝ 物品(%d)：%d ＋人物(%d)：%d *%d  打怪(%d)：%d *%d\n",
                times + times2, exp + exp2, pot2, times, exp, times2, exp2, pot2,
                who->get_log("#npc"), who->get_log("&npc"), who->get_log("*npc") );
        result += sprintf( "剿匪(%d)：%d *%d  师爷(%d)：%d *%d\n",
                who->get_log("#banditi"), who->get_log("&banditi"), who->get_log("*banditi"),
                who->get_log("#robber"), who->get_log("&robber"), who->get_log("*robber") );

        times = who->get_log("#monster");  exp = who->get_log("&monster");  pot = who->get_log("*monster");
        times2 = who->get_log("#monster2");  exp2 = who->get_log("&monster2");  pot2 = who->get_log("*monster2");

        result += sprintf( "重犯(%d)：%d *%d  宝图(%d)：%d *%d ＝ 杀图(%d)：%d *%d ＋ 放图(%d)：%d *%d\n",
                who->get_log("#criminal"), who->get_log("&criminal"), who->get_log("*criminal"),
                times + times2, exp + exp2, pot + pot2, times, exp, pot, times2, exp2, pot2 );

        times = who->get_log("#escort");  cash = who->get_log("$escort");  exp = who->get_log("&escort");
        times2 = who->get_log("#escort2");  cash2 = who->get_log("$escort2");  exp2 = who->get_log("&escort2");

        result += sprintf( "失窃(%d)：$%d %d *%d  运镖(%d)：$%d %d ＝ 成功(%d)：$%d %d ＋失败(%d)：$%d %d\n",
                who->get_log("#thief"), who->get_log("$thief"), who->get_log("&thief"), who->get_log("*thief"),
                times + times2, cash + cash2, exp + exp2, times, cash, exp, times2, cash2, exp2 );

        tell_user(me, result);

        result = sprintf( "丢下：%d %09d  拣起：%d %09d  给人：%d %09d  人给：%d %09d\n", 
                who->get_log("$drop$H"), who->get_log("$drop$L"), who->get_log("$get$H"), who->get_log("$get$L"),
                who->get_log("$give$H"), who->get_log("$give$L"), who->get_log("$give2$H"), who->get_log("$give2$L") );

        result += sprintf( "交易给：%d %09d  交易收：%d %09d\n", 
                who->get_log("$exchange$H"), who->get_log("$exchange$L"), who->get_log("$exchange2$H"), who->get_log("$exchange2$L") );

        result += sprintf( "买进：%d %09d  卖出：%d %09d  摊买：%d %09d  摊卖：%d %09d\n", 
                who->get_log("$buy$H"), who->get_log("$buy$L"), who->get_log("$sell$H"), who->get_log("$sell$L"),
                who->get_log("$buy2$H"), who->get_log("$buy2$L"), who->get_log("$sell2$H"), who->get_log("$sell2$L") );

        result += sprintf( "节日：%d %09d  任务：%d %09d  运镖：%d %09d  经商：%d %09d\n", 
                who->get_log("$date$H"), who->get_log("$date$L"), who->get_log("$task$H"), who->get_log("$task$L"), 
                who->get_log("$biao$H"), who->get_log("$biao$L"), who->get_log("$trade$H"), who->get_log("$trade$L") );

        result += sprintf( "修理：%d %09d  合成：%d %09d  捐赠：%d %09d\n", 
                who->get_log("$repair$H"), who->get_log("$repair$L"), who->get_log("$make$H"), who->get_log("$make$L"),
                who->get_log("$org$H"), who->get_log("$org$L") );

        result += sprintf( "学习：%d %09d  系统：%d %09d  其它：%d %09d\n", 
                who->get_log("$learn$H"), who->get_log("$learn$L"), who->get_log("$pay$H"), who->get_log("$pay$L"),
                who->get_log("$????$H"), who->get_log("$????$L") );

        tell_user(me, result);

	result = USER_TASK_D->get_task_done(who);
	if (result!="" && result!=0) tell_user( me, result );

        return 1;
}
