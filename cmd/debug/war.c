
#include <ansi.h>
#include <map.h>
#include <city.h>
#include <time.h>

// 函数：命令处理
int main( object me, string arg )
{
        object map, orgnpc, npc;
        string name1, name2, name, cmd;
        int z, p, i, size;
	mixed *mxTime;    
	int iTime, time;
	iTime = time();
	mxTime = localtime(iTime);
	
	
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        

        if( me->get_org_name() == "" )
	{
                notify( "您得加入一个帮派！" );
                return 1;
	}
	if( !arg || arg == "" ) 
	{
                notify( "您打算同哪个帮派开战？" );
                return 1;
	}
	if(     arg == me->get_org_name()
        ||     !objectp( npc = CITY_ZHOU->get_2( sprintf( "org.%s", arg ) ) ) )
        {
                notify( "请重新输入合法的帮派。" );
                return 1;
        }
        orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", me->get_org_name() ) );
        if (!orgnpc)
        {
                notify( "请加入合法的帮派。" );
                return 1;
        }        

                                        if( !( z = find_map_flag(BATTLE_MAP_BEGIN, BATTLE_MAP_END, 0) ) )    // 查找空白战场
                                        {
                                                send_user( me, "%c%s", '!', "不能向“" + arg + "”发动战争。" );
                                                return;
                                        }
/*                                        
                                        switch( get_z(npc) )    // 查找对应战场
                                        {
                                      case 10 : p = 910;  break;
                                      case 20 : p = 920;  break;
                                      case 30 : p = 930;  break;
                                      case 40 : p = 940;  break;
                                      case 50 : p = 950;  break;
                                      case 60 : p = 960;  break;
                                      case 70 : p = 970;  break;
                                      default : send_user( me, "%c%s", '!', "不能向“" + arg + "”发动战争。" );
                                                return;
                                        }
*/
					p = 910;
                                        init_virtual_map(z, p);    // 生成虚拟地图

                                        map = new(BATTLE);    // 生成虚拟对象
                                        map->set_client_id(p);
                                        set_map_object( map, map->set_id(z) );

					if (time%2==1) time += 3;
					else time += 2;
                                        orgnpc->set_war( time() + 60 );  npc->set_war( time() + 60 );    // 记录战争时间

                                        orgnpc->set_battle(z);  npc->set_battle(z);    // 记录战场编号
                                        orgnpc->set_enemy_95(npc);  npc->set_enemy_95(orgnpc);    // 记录敌方总管
                                        me->set_wood(0); npc->set_wood(0);
                                        orgnpc->set_level1(1); npc->set_level1(1);
                                        orgnpc->set_level2(1); npc->set_level2(1);
                                        orgnpc->set_level3(1); npc->set_level3(1);                                        
                                        map->set_war_attack( me->get_org_name() );  map->set_war_defense(arg);    // 记录战争双方
                                        map->set_heart_sec(0);    // 校正时钟
                                        map->set_war(WAR_READY);    // 记录战争准备

                                        NPC_BATTLE_D->war_ready_notice(map);
                                        map->set_starttime( time() + 60 );

        map->set_heart_sec(595);

//        tell_user(me, "战场位置：%d", z);

        return 1;
}
