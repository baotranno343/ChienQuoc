
#include <ansi.h>
#include <map.h>
#include <city.h>
#include <skill.h>

inherit "/inh/std/virtual";

private static int War;                 // 战争状态

private static int *BattleXY = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
private static int *BattleD = ({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 });

private static string Attack;           // 战场攻击方
private static string Defense;          // 战场防守方

private static int StartTime;		// 开始战争的时间

private static object Manager;          // 攻击方总管
private static object Manager2;         // 防守方总管

private static int iWiner;		// 0 防守方胜 1 攻方胜

private static object *dbTower = ({ });         // 攻击方箭塔
private static object *dbTower2 = ({ });        // 防守方箭塔

private static object *dbComrade = ({ });       // 攻击方士兵
private static object *dbComrade2 = ({ });      // 防守方士兵

private static object *dbUser = ({ });          // 攻击方玩家
private static object *dbUser2 = ({ });         // 防守方玩家

private static object * dbHire = ({ });		// 攻击方的佣兵
private static object * dbHire2 = ({ });	// 防守方的佣兵

private static object * dbPower = ({ });	// 攻击方的战斗傀儡
private static object * dbPower2 = ({ });	// 防守方的战斗傀儡

// -------------------------------------------------------------

// 函数：获取地型类别
int get_map_type() { return BATTLE_MAP; }

// 函数：构造处理
void create() 
{ 
        object me = this_object();

        set_client_id(901);
        set_name("Chiến Trường");

        if( !clonep(me) ) return;

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 50);    // 循环心跳：５秒钟
        me->heart_beat();
        set_heart_beat(1);
}

// -------------------------------------------------------------

// 函数：获取战争开始时间
int get_starttime() { return StartTime; }

// 函数：设置战争开始时间
int set_starttime( int flag ) { return StartTime = flag; }

// 函数：获取战争状态
int get_war() { return War; }

// 函数：设置战争状态
int set_war( int flag ) { return War = flag; }

// 函数：获取战争胜利方
int get_winer() { return iWiner; }

// 函数：设置战争状态
int set_winer( int flag ) { return iWiner = flag; }

// 函数：获取出怪点坐标
int get_battle_x( int flag ) 
{ 
        switch( flag )
        {
      case 10 : return BattleXY[0];    // 实线１
      default : return BattleXY[2];    // 实线２
      case 12 : return BattleXY[4];    // 实线３

      case 15 : return BattleXY[6];
      case 16 : return BattleXY[8];
      case 17 : return BattleXY[10];

      case 13 : return BattleXY[12];    // 虚线１
      case 14 : return BattleXY[14];    // 虚线２
      case 18 : return BattleXY[16];
      case 19 : return BattleXY[18];
        }
}

// 函数：获取出怪点坐标
int get_battle_y( int flag ) 
{ 
        switch( flag )
        {
      case 10 : return BattleXY[1];    // 实线１
      default : return BattleXY[3];    // 实线２
      case 12 : return BattleXY[5];    // 实线３

      case 15 : return BattleXY[7];
      case 16 : return BattleXY[9];
      case 17 : return BattleXY[11];

      case 13 : return BattleXY[13];    // 虚线１
      case 14 : return BattleXY[15];    // 虚线２
      case 18 : return BattleXY[17];
      case 19 : return BattleXY[19];
        }
}

// 函数：设置出怪点坐标
int set_battle_x( int flag, int point ) 
{ 
        switch( flag )
        {
      case 10 : return BattleXY[0] = point;
      default : return BattleXY[2] = point;
      case 12 : return BattleXY[4] = point;

      case 15 : return BattleXY[6] = point;
      case 16 : return BattleXY[8] = point;
      case 17 : return BattleXY[10] = point;
        }
}

// 函数：设置出怪点坐标
int set_battle_y( int flag, int point ) 
{ 
        switch( flag )
        {
      case 10 : return BattleXY[1] = point;
      default : return BattleXY[3] = point;
      case 12 : return BattleXY[5] = point;

      case 15 : return BattleXY[7] = point;
      case 16 : return BattleXY[9] = point;
      case 17 : return BattleXY[11] = point;
        }
}

/* 
 * 假定直线上两点 (x1, y1), (x2, y2), 那么直线方程是：(x - x1) / (y - y1) = (x1 - x2) / (y1 - y2)
 * 即是：y = (x - x1) * (y1 - y2) / (x1 - x2) + y1
 *       x = (y - y1) * (x1 - x2) / (y1 - y2) + x1
 * 注意：左下角是攻击方，右上角是防守方
 */

// 函数：三条实线生成两条虚线
void make_virtual_line()
{
        BattleXY[12] = BattleXY[2] + ( BattleXY[0] - BattleXY[2] ) / 2;
        BattleXY[14] = BattleXY[4] + ( BattleXY[2] - BattleXY[4] ) / 2;
        BattleXY[16] = BattleXY[8] + ( BattleXY[6] - BattleXY[8] ) / 2;
        BattleXY[18] = BattleXY[10] + ( BattleXY[8] - BattleXY[10] ) / 2;

        BattleXY[13] = BattleXY[1] + ( BattleXY[3] - BattleXY[1] ) / 2;
        BattleXY[15] = BattleXY[3] + ( BattleXY[5] - BattleXY[3] ) / 2;
        BattleXY[17] = BattleXY[7] + ( BattleXY[9] - BattleXY[7] ) / 2;
        BattleXY[19] = BattleXY[9] + ( BattleXY[11] - BattleXY[9] ) / 2;
}

// 函数：生成直线坐标距离
void make_battle_d()
{
        BattleD[0] = BattleXY[0] - BattleXY[4];
        BattleD[1] = BattleXY[1] - BattleXY[5];

        BattleD[2] = BattleXY[6] - BattleXY[10];
        BattleD[3] = BattleXY[7] - BattleXY[11];

        BattleD[4] = BattleXY[12] - BattleXY[16];
        BattleD[5] = BattleXY[13] - BattleXY[17];
        BattleD[6] = BattleXY[14] - BattleXY[18];
        BattleD[7] = BattleXY[15] - BattleXY[19];

        BattleD[8] = BattleXY[0] - BattleXY[6];
        BattleD[9] = BattleXY[1] - BattleXY[7];
        BattleD[10] = BattleXY[2] - BattleXY[8];
        BattleD[11] = BattleXY[3] - BattleXY[9];
        BattleD[12] = BattleXY[4] - BattleXY[10];
        BattleD[13] = BattleXY[5] - BattleXY[11];

        if( !BattleD[0] ) BattleD[0] = 1;    // 除数非零
        if( !BattleD[1] ) BattleD[1] = 1;
        if( !BattleD[2] ) BattleD[2] = 1;
        if( !BattleD[3] ) BattleD[3] = 1;
        if( !BattleD[4] ) BattleD[4] = 1;
        if( !BattleD[5] ) BattleD[5] = 1;
        if( !BattleD[6] ) BattleD[6] = 1;
        if( !BattleD[7] ) BattleD[7] = 1;
        if( !BattleD[8] ) BattleD[8] = 1;
        if( !BattleD[9] ) BattleD[9] = 1;
        if( !BattleD[10] ) BattleD[10] = 1;
        if( !BattleD[11] ) BattleD[11] = 1;
        if( !BattleD[12] ) BattleD[12] = 1;
        if( !BattleD[13] ) BattleD[13] = 1;
}

// 函数：是否在攻击方阵地
int is_inside_attack( int z, int x, int y ) { return y < ( x - BattleXY[0] ) * BattleD[1] / BattleD[0] + BattleXY[1]; }

// 函数：是否在防守方阵地
int is_inside_defense( int z, int x, int y ) { return y > ( x - BattleXY[6] ) * BattleD[3] / BattleD[2] + BattleXY[7]; }

// 函数：是否在路线１内
int is_inside_road_1( int z, int x, int y ) { return y < ( x - BattleXY[12] ) * BattleD[5] / BattleD[4] + BattleXY[13]; }

// 函数：是否在路线２内
int is_inside_road_2( int z, int x, int y )
{
        return y >= ( x - BattleXY[12] ) * BattleD[5] / BattleD[4] + BattleXY[13]
            && y <= ( x - BattleXY[14] ) * BattleD[7] / BattleD[6] + BattleXY[15];
}

// 函数：是否在路线３内
int is_inside_road_3( int z, int x, int y ) { return y > ( x - BattleXY[14] ) * BattleD[7] / BattleD[6] + BattleXY[15]; }

/* -------------------------------------

// 函数：是否在路线１下面
int is_inside_road_a( int z, int x, int y ) { return y < ( x - BattleXY[0] ) * BattleD[9] / BattleD[8] + BattleXY[1]; }

// 函数：是否在路线１、２之间
int is_inside_road_b( int z, int x, int y )
{
        return y >= ( x - BattleXY[0] ) * BattleD[9] / BattleD[8] + BattleXY[1]
            && y <= ( x - BattleXY[2] ) * BattleD[11] / BattleD[10] + BattleXY[3];
}

// 函数：是否在路线２、３之间
int is_inside_road_c( int z, int x, int y )
{
        return y >= ( x - BattleXY[2] ) * BattleD[11] / BattleD[10] + BattleXY[3]
            && y <= ( x - BattleXY[4] ) * BattleD[13] / BattleD[12] + BattleXY[5];
}

// 函数：是否在路线３上面
int is_inside_road_d( int z, int x, int y ) { return y > ( x - BattleXY[4] ) * BattleD[13] / BattleD[12] + BattleXY[5]; }

------------------------------------- */

// 函数：计算路线１的Ｘ值
int get_road_1_x( int y ) { return ( y - BattleXY[1] ) * BattleD[8] / BattleD[9] + BattleXY[0]; }

// 函数：计算路线２的Ｘ值
int get_road_2_x( int y ) { return ( y - BattleXY[3] ) * BattleD[10] / BattleD[11] + BattleXY[2]; }

// 函数：计算路线３的Ｘ值
int get_road_3_x( int y ) { return ( y - BattleXY[5] ) * BattleD[12] / BattleD[13] + BattleXY[4]; }

// -------------------------------------------------------------

// 函数：获取战场攻击方
string get_war_attack() { return Attack ? Attack : "－－"; }

// 函数：设置战场攻击方
string set_war_attack( string name ) { return Attack = name; }

// 函数：获取战场防守方
string get_war_defense() { return Defense ? Defense : "－－"; }

// 函数：设置战场防守方
string set_war_defense( string name ) { return Defense = name; }

// 函数：获取攻击方总管
object get_manager() { return Manager; }

// 函数：设置攻击方总管
object set_manager( object who ) { return Manager = who; }

// 函数：获取防守方总管
object get_manager_2() { return Manager2; }

// 函数：设置防守方总管
object set_manager_2( object who ) { return Manager2 = who; }

// -------------------------------------------------------------

// 函数：获取攻击方箭塔
object *get_tower_dbase() { dbTower -= ({ 0 });  return copy(dbTower); }

// 函数：获取防守方箭塔
object *get_tower_2_dbase() { dbTower2 -= ({ 0 });  return copy(dbTower2); }

// 函数：获取攻击方箭塔
int sizeof_tower_dbase() { dbTower -= ({ 0 });  return sizeof(dbTower); }

// 函数：获取防守方箭塔
int sizeof_tower_2_dbase() { dbTower2 -= ({ 0 });  return sizeof(dbTower2); }

// 函数：增加攻击方箭塔
void add_tower( object npc ) { dbTower = dbTower + ({ npc }) - ({ 0 }); }

// 函数：增加防守方箭塔
void add_tower_2( object npc ) { dbTower2 = dbTower2 + ({ npc }) - ({ 0 }); }

// 函数：删除攻击方箭塔
void sub_tower( object npc ) { dbTower -= ({ npc, 0 }); }

// 函数：删除防守方箭塔
void sub_tower_2( object npc ) { dbTower2 -= ({ npc, 0 }); }

// -------------------------------------------------------------

// 函数：获取攻击方佣兵
object *get_hire_dbase() { dbHire -= ({ 0 });  return copy(dbHire); }

// 函数：获取防守方佣兵
object *get_hire_2_dbase() { dbHire2 -= ({ 0 });  return copy(dbHire2); }

// 函数：获取攻击方佣兵
int sizeof_hire_dbase() { dbHire -= ({ 0 });  return sizeof(dbHire); }

// 函数：获取防守方佣兵
int sizeof_hire_2_dbase() { dbHire2 -= ({ 0 });  return sizeof(dbHire2); }

// 函数：增加攻击方佣兵
void add_hire( object npc ) { dbHire = dbHire + ({ npc }) - ({ 0 }); }

// 函数：增加防守方佣兵
void add_hire_2( object npc ) { dbHire2 = dbHire2 + ({ npc }) - ({ 0 }); }

// 函数：删除攻击方佣兵
void sub_hire( object npc ) { dbHire -= ({ npc, 0 }); }

// 函数：删除防守方佣兵
void sub_hire_2( object npc ) { dbHire2 -= ({ npc, 0 }); }

// 函数：获取攻击方战斗傀儡
object *get_power_dbase() { dbPower -= ({ 0 });  return copy(dbPower); }

// 函数：获取防守方战斗傀儡
object *get_power_2_dbase() { dbPower2 -= ({ 0 });  return copy(dbPower2); }

// 函数：获取攻击方战斗傀儡
int sizeof_power_dbase() { dbPower -= ({ 0 });  return sizeof(dbPower); }

// 函数：获取防守方战斗傀儡
int sizeof_power_2_dbase() { dbPower2 -= ({ 0 });  return sizeof(dbPower2); }

// 函数：增加攻击方战斗傀儡
void add_power( object npc ) { dbPower = dbPower + ({ npc }) - ({ 0 }); }

// 函数：增加防守方战斗傀儡
void add_power_2( object npc ) { dbPower2 = dbPower2 + ({ npc }) - ({ 0 }); }

// 函数：删除攻击方战斗傀儡
void sub_power( object npc ) { dbPower -= ({ npc, 0 }); }

// 函数：删除防守方战斗傀儡
void sub_power_2( object npc ) { dbPower2 -= ({ npc, 0 }); }


// 函数：获取攻击方士兵
object *get_comrade_dbase() { dbComrade -= ({ 0 });  return copy(dbComrade); }

// 函数：获取防守方士兵
object *get_comrade_2_dbase() { dbComrade2 -= ({ 0 });  return copy(dbComrade2); }

// 函数：获取攻击方士兵
int sizeof_comrade_dbase() { dbComrade -= ({ 0 });  return sizeof(dbComrade); }

// 函数：获取防守方士兵
int sizeof_comrade_2_dbase() { dbComrade2 -= ({ 0 });  return sizeof(dbComrade2); }

// 函数：增加攻击方士兵
void add_comrade( object npc ) { dbComrade = dbComrade + ({ npc }) - ({ 0 }); }

// 函数：增加防守方士兵
void add_comrade_2( object npc ) { dbComrade2 = dbComrade2 + ({ npc }) - ({ 0 }); }

// 函数：删除攻击方士兵
void sub_comrade( object npc ) { dbComrade -= ({ npc, 0 }); }

// 函数：删除防守方士兵
void sub_comrade_2( object npc ) { dbComrade2 -= ({ npc, 0 }); }

// -------------------------------------------------------------

// 函数：获取攻击方玩家
object *get_user_dbase() { dbUser -= ({ 0 });  return copy(dbUser); }

// 函数：获取防守方玩家
object *get_user_2_dbase() { dbUser2 -= ({ 0 });  return copy(dbUser2); }

// 函数：获取攻击方玩家
int sizeof_user_dbase() { dbUser -= ({ 0 });  return sizeof(dbUser); }

// 函数：获取防守方玩家
int sizeof_user_2_dbase() { dbUser2 -= ({ 0 });  return sizeof(dbUser2); }

// 函数：清空攻击方玩家
void init_user_dbase() { dbUser = ({ }); }

// 函数：清空防守方玩家
void init_user_2_dbase() { dbUser2 = ({ }); }

// 函数：增加攻击方玩家
void add_user( object who ) { dbUser = dbUser - ({ who }) + ({ who }) - ({ 0 }); }

// 函数：增加防守方玩家
void add_user_2( object who ) { dbUser2 = dbUser2 - ({ who }) + ({ who }) - ({ 0 }); }

// 函数：删除攻击方玩家
void sub_user( object who ) { dbUser -= ({ who, 0 }); }

// 函数：删除防守方玩家
void sub_user_2( object who ) { dbUser2 -= ({ who, 0 }); }

// -------------------------------------------------------------

// 函数：列示给新玩家(对方进场景)
void show_to_user( object who )
{
        object npc;
        int i, size;

        if( who->get_manager() == Manager )    // 攻击方
        {
                if( objectp( npc = Manager ) ) 
                        send_user( who, "%c%c%d%w%w", 0x54, 20, getoid(npc), get_x(npc), get_y(npc) );

                for( i = 0, size = sizeof(dbTower); i < size; i ++ ) if( objectp( npc = dbTower[i] ) )
                        send_user( who, "%c%c%d%w%w", 0x54, 21, getoid(npc), get_x(npc), get_y(npc) );

                for( i = 0, size = sizeof(dbUser); i < size; i ++ ) if( objectp( npc = dbUser[i] ) )
                        send_user( who, "%c%c%d%w%w", 0x54, 10, npc->get_number(), get_x(npc), get_y(npc) );
        }
        else if( who->get_manager() == Manager2 )    // 防守方
        {
                if( objectp( npc = Manager2 ) ) 
                        send_user( who, "%c%c%d%w%w", 0x54, 20, getoid(npc), get_x(npc), get_y(npc) );

                for( i = 0, size = sizeof(dbTower2); i < size; i ++ ) if( objectp( npc = dbTower2[i] ) )
                        send_user( who, "%c%c%d%w%w", 0x54, 21, getoid(npc), get_x(npc), get_y(npc) );

                for( i = 0, size = sizeof(dbUser2); i < size; i ++ ) if( objectp( npc = dbUser2[i] ) )
                        send_user( who, "%c%c%d%w%w", 0x54, 10, npc->get_number(), get_x(npc), get_y(npc) );
        }
}

// 函数：列示给玩家看(新进入场景)
void show_to_scene( object who )
{
        if( who->get_manager() == Manager )    // 攻击方
                send_user( dbUser, "%c%c%d%w%w", 0x54, 10, who->get_number(), get_x(who), get_y(who) );
        else if( who->get_manager() == Manager2 )    // 防守方
                send_user( dbUser2, "%c%c%d%w%w", 0x54, 10, who->get_number(), get_x(who), get_y(who) );
}

// -------------------------------------------------------------

// 函数：心跳处理
void heart_beat() { }

private static int HeartSec = 0;        // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec( int point ) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec( int point ) { return set_heart_sec(HeartSec + point); }

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object map, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每５秒处理
{
        int sec = map->add_heart_sec(5);
        int time;

        switch( map->get_war() )
        {
       case WAR_READY : 
       			time = map->get_starttime() - time();
       			if (time<30)
       			{       				
                                map->set_war(WAR_READY_2);    // 开始３０秒倒计时
                                map->set_heart_sec(0);    // 校正时钟
                                NPC_BATTLE_D->war_begin_count_down_notice(map, 30);
       				
       			}
       			else 
       			if( time % 300 == 0 )    // 每５分处理
                        {
                                NPC_BATTLE_D->war_ready_notice(map);
                        }
                        break;

     case WAR_READY_2 : if( sec % 5 == 0 ) NPC_BATTLE_D->war_begin_count_down_notice(map, 30 - sec);    // 每５秒处理
                        break;

       case WAR_BEGIN : if( sec % 60 == 0 )    // 每分钟处理
                        {
                                if( sec < WAR_TIME - 600 )
                                {
                                        if( sec % 180 == 0 ) NPC_BATTLE_D->war_begin_notice(map);    // 每３分处理
                                }
                                else
                                {
                                        if( sec == WAR_TIME - 600 ) NPC_BATTLE_D->war_end_notice(map);    // 最后１０分钟

                                        if( sec == WAR_TIME - 300 ) NPC_BATTLE_D->war_end_notice_2(map);    // 最后５分钟

                                        if( sec >= WAR_TIME )
                                        {
                                                map->set_war(WAR_TIMEOUT);    // 开始３０秒倒计时
                                                map->set_heart_sec(0);    // 校正时钟
                                                NPC_BATTLE_D->war_end_count_down_notice(map, 30);
                                        }
                                }
                        }
                        if( sec % 5 == 0 )    // 注意：80, 95, 110 可被 5 整除
                        {
                                if( sec % 80 == 0 ) NPC_BATTLE_D->add_comrade_to_battle(map, 1);    // 每８０秒处理
                                if( sec % 95 == 0 ) NPC_BATTLE_D->add_comrade_to_battle(map, 2);    // 每９５秒处理
                                if( sec % 110 == 0 ) NPC_BATTLE_D->add_comrade_to_battle(map, 3);    // 每１１０秒处理
                        }
                        break;

     case WAR_TIMEOUT : if( sec % 5 == 0 ) NPC_BATTLE_D->war_end_count_down_notice(map, 30 - sec);    // 每５秒处理
                        break;

         case WAR_END : NPC_BATTLE_D->war_end(map);
                        break;
        }
}

// -------------------------------------------------------------

// 函数：清除所有物体
void cleanup_char_and_item( object map )
{
        object *item, who, npc, *all, *all2;
        string name;
        int z, x, y, p, max_x, max_y;
        int i, size;

        reset_eval_cost();

        z = map->get_id();  max_x = get_map_max_x(z);  max_y = get_map_max_y(z);
        
//        log_file("test", sprintf("%s 清理物品、NPC和人物\n", short_time()));
        all = ({ });
        all2 = ({ });
        for( x = 0; x < max_x; x += AREA_SIZE ) for( y = 0; y < max_y; y += AREA_SIZE )
        {
                if( have_scene_object(z, x, y, ITEM_TYPE, 1) )
                {
                        item = get_scene_object(z, x, y, ITEM_TYPE, 1);

                        for( i = 0, size = sizeof(item); i < size; i ++ ) if( who = item[i] )
                        {
                                all2 += ({ item[i] });
                        }
                }                
                if( have_scene_object(z, x, y, CHAR_TYPE, 1) )
                {
                        item = get_scene_object(z, x, y, CHAR_TYPE, 1);

                        for( i = 0, size = sizeof(item); i < size; i ++ ) if( who = item[i] )
                        {
                                all2 += ({ item[i] });
                        }
                }                
                if( have_scene_object(z, x, y, USER_TYPE, 1) )
                {
                        item = get_scene_object(z, x, y, USER_TYPE, 1);

                        for( i = 0, size = sizeof(item); i < size; i ++ ) if( who = item[i] )
                        {
                                all += ({ item[i] });
                        }
                }
        }
        all -= ({ 0 });
        for( i = 0, size = sizeof(all); i < size; i ++ ) if( who = all[i] )
        {
//                log_file("test", sprintf("%s 地图里面有%s %d %d\n", short_time(), who->get_name(), get_x(who), get_y(who)));
                if(   ( name = who->get_org_name() ) != "" 
                &&      objectp( npc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) ) )
                &&    ( z = get_z(npc) )
                &&    ( p = get_valid_xy( z, get_x(npc) + random(11) - 5, get_y(npc) + random(11) - 5, IS_CHAR_BLOCK) ) )
                {
                	if (who->is_die()) who->set_die(0);
/*                      map->sub_user(who);
                        map->sub_user_2(who);*/			
                        who->add_to_scene(z, p / 1000, p % 1000, 3);
                        CHAR_CHAR_D->init_loop_perform(who);
                        send_user( who, "%c%d%w%c%c%c", 0x6f, getoid(who), 9005, 1, OVER_BODY, PF_STOP );
                        send_user( who, "%c%d%w%c%c%c", 0x6f, getoid(who), 9006, 1, OVER_BODY, PF_STOP );

                        switch( who->get_level() )    // 设置玩家种类
                        {
                    case 0..9 : USER_D->add_level_a_user(who);  break;
                  case 10..29 : USER_D->add_level_b_user(who);  break;
                      default : USER_D->add_level_c_user(who);  break;
                        }
                        USER_D->sub_battle_user(who);
//                        log_file("test", sprintf("%s %s移出场景\n", short_time(), who->get_name()));
                }
                else
                {
                        MAP_D->add_to_void(who);
//                        log_file("test", sprintf("%s %s移至周国\n", short_time(), who->get_name()));
                }                   
        }
        all2 -= ({ 0 });
        for( i = 0, size = sizeof(all2); i < size; i ++ ) if( who = all2[i] )
        {
                who->remove_from_scene();
                destruct(who);
        }                                                      
//        log_file("test", sprintf("%s cleanup_char_and_item执行完毕\n", short_time()));

        map->init_user_dbase();    // 省略循环中 map->sub_user(who);
        map->init_user_2_dbase();    // 省略循环中 map->sub_user_2(who);
}

// 函数：消除之前处理
void before_destruct()
{
        object map, *char, npc;
        int i, size;

        map = this_object();

        if( arrayp( char = map->get_comrade_dbase() ) )
        {
                for( i = 0, size = sizeof(char); i < size; i ++ ) if( objectp( npc = char[i] ) )
                {
                        npc->remove_from_scene();
                        destruct(npc);
                }
        }
        if( arrayp( char = map->get_comrade_2_dbase() ) )
        {
                for( i = 0, size = sizeof(char); i < size; i ++ ) if( objectp( npc = char[i] ) )
                {
                        npc->remove_from_scene();
                        destruct(npc);
                }
        }

        if( objectp( npc = map->get_manager() ) )
        {
                npc->remove_from_scene();
                destruct(npc);
        }
        if( objectp( npc = map->get_manager_2() ) )
        {
                npc->remove_from_scene();
                destruct(npc);
        }
}

// 函数：删除虚拟场景
void destruct_virtual_map( object map, int id )
{
        if( !map->is_virtual_scene() ) return;

	cleanup_char_and_item(map);
	free_virtual_map(id);
//	log_file("test", sprintf("%s 删除虚拟场景\n", short_time()));
	destruct(map);	
}
