#include <ansi.h>
#include <city.h>
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <cmd.h>

inherit BADMAN;

int is_caster() { return 1; }

// 函数:构造处理
void create()
{
        set_name("Đào Loạn Giả");
	set_level(20);
        set_max_hp(100);  set_max_mp(0);
        set_ap(400);  set_dp(300);
        set_cp(  0);  set_pp(300);
        set_sp(0);

        set_walk_speed(3);  set_attack_speed(15);
        set_max_seek(4);
	set_char_picid(10);
	set_walk_step(1);
        setup();

        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数:获取装备代码
int get_weapon_code() { return THROWING; }

// 函数:特技攻击对手
int perform_action( object who ) { return PF_FILE_01611->perform_action_npc( this_object(), who ); }


// 函数:掉宝奖励
void win_bonus( object who ) { __FILE__ ->win_bonus2( this_object(), who ); }

// 函数:掉宝奖励(在线更新)
void win_bonus2( object me, object who )
{
	string name, result, id, owner;
	object orgnpc, map, item, leader;
	int z, p, x, y, number, add;
	int drop = 1;
	"/sys/npc/npc"->win_bonus(me, who);

	// 先掉钱
	if (who->is_npc())
	{
		who = who->get_owner();
	}
	if (!who) return;
	if (who->is_npc()) return;
	z = get_z(me), x = get_x(me), y = get_y(me);
	if (random100()<5*who->get_online_rate()/100)
        {
	        if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
	        {       		        
	        	id = who->get_leader();
		        if (!id) owner = who->get_id();
		        else
		        {
		        	if ( leader = find_player(id ) )
		        	{
		        		owner = leader->get_id();
				}      
				else
					owner = who->get_id();  		
			}		        
	                item = new( "/item/std/0001" );
	                TEAM_D->drop_item(item,who);
	                item->set_user_id(owner);
	                item->set_value( me->get_level()*5 );
	                item->add_to_scene(z, p / 1000, p % 1000);
	                item->set("winner", who);
	                item->set( "time", time() );
	        }
	}
	map = get_map_object(z);
	if (!map) return;
        name = map->get_name();
        if (name=="") return;
        if (who->get_org_name()!=name) return;
        if (who->get_org_position()==0) return;
	orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
	if (!objectp(orgnpc)) return;
	add = who->add_save("warlevel", me->get_level());
	if (add >= 30)
	{
		number = who->get_number();
		orgnpc->set_member_contribute(number, orgnpc->get_member_contribute(number)+add/30);
		orgnpc->save();
		who->set_save("warlevel", add % 30);
		result = sprintf("Bạn tiêu diệt %s, nhận được %d Cống hiến Bang phái.", me->get_name(), add/30);
		tell_user( who, ECHO + result );
	}
}

void heart_beat_walk()
{
        object map, who, *see, *char, me, orgnpc;
        string cmd, name;
        int z, x, y, x1, y1, dx, p, p2;
        int walk, seek, flag, *dir, i, size;
        me = this_object();

        if(     get_effect(me, EFFECT_CHAR_BUSY)
        ||      get_effect(me, EFFECT_CHAR_FAINT)
        ||      get_effect(me, EFFECT_SLEEP)
        ||      get_effect(me, EFFECT_CHAR_FAINT_2)
        ||      get_effect(me, EFFECT_CHAR_FREEZE) )
                return;

        if( !me->get_action() ) return;

        z = get_z(me);  x = get_x(me);  y = get_y(me);
        // 判断是否进入跳转点5
        if( inside_jumpin( z, x, y, 5 ))
        {
        	map = get_map_object(z);
        	if (map)
        	{
        		name = map->get_name();
        		orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
        		if (orgnpc)
        		{
        			orgnpc->add_wardamage(1);
        			if (orgnpc->get_wardamage()>=100)
        			{
			        	CHAT_D->rumor_channel( 0, sprintf(HIR "听说%s受到了怪物地猛烈攻打, 帮派设施受到严重损害." , name));
			        	orgnpc->add_train(-2);
			        	orgnpc->add_stable(-300);
			        	orgnpc->add_favour(-100);
			        	orgnpc->set_gradewartime(0);
			        	orgnpc->set_wardamage(0);
			        	orgnpc->save();
			        	FAMILY_D->org_channel( name, 0, HIR "本帮因为受到怪物的侵袭, 帮派设施受到的严重损伤.帮派提升规模失败, 帮派安定度下降300点, 人气度下降100点, 训练度下降2点." );
        			}
        			else
        				FAMILY_D->org_channel( name, 0, sprintf(HIR "捣乱份子在进行破坏, 帮派当前损害度为:%d/100." , orgnpc->get_wardamage()));
        				
        		}
        		send_user( get_scene_object_2(me, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(me), get_y(me), 32411, 1, OVER_BODY, PF_ONCE );
        		me->remove_from_scene();
        		destruct(me);
        		return;
        	}
        }
        if( who = me->get_main_enemy() )    // 搜索何人攻击(最重要的敌人)
                me->set_enemy(who);
        else
        {
        	if (!me->get_enemy())
        	{
	                seek = me->get_max_seek();	
	                see = get_range_object(z, x, y, seek, USER_TYPE) +  get_range_object(z, x, y, seek, CHAR_TYPE);
	                char = filter_array( see, (: objectp($1) && $1->get_org_name() != $2->get_org_name() :), me );    // 所在不同帮派    // get_org_name() 是字串运算
	                see = filter_array( char, (: $1->can_fight($2) :), me );    // 所在不同帮派    // get_org_name() 是字串运算
	                if( objectp(who = get_near_char(see, z, x, y) ) ) me->auto_fight(who);
		}	               
        }

        if( gone_time( me->get_attack_time() ) > 10 ) me->init_enemy_damage(0, 0);    // 清除伤害状态

        z = get_z(me);  x = get_x(me);  y = get_y(me);

        if( objectp( who = me->get_enemy() ) )
        {
                if( who->is_die() )
                {
                        me->set_enemy(0);  flag = 1;
                }
                else    me->follow_user();
        }
        else    flag = 1;

        if( flag && objectp( map = get_map_object(z) ) )    // 跟随指定路线
        {
                p = 0;
		p2 = get_jumpin(z, 5);
		p = get_valid_path(z, x, y, p2/1000, p2%1000);
                if( p )    // 找到可走路径
                {
                        cmd = sprintf("%d", p);

                        switch( me->get_walk_step() )
                        {
                      default : if( strlen(cmd) > 1 ) cmd = cmd[0..0];  break;
                       case 2 : if( strlen(cmd) > 2 ) cmd = cmd[0..1];  break;
                        }
                        GO_CMD->main_npc(me, cmd);
                }
                else if( sizeof_range_object(z, x, y, 1, CHAR_TYPE) + sizeof_range_object(z, x, y, 1, USER_TYPE) < 9 )    // 随机乱走
                {
                        dir = ({ });
                        if( !( get_block(z, x + 1, y    ) & IS_CHAR_BLOCK ) ) dir += ({ 111 });
                        if( !( get_block(z, x + 1, y - 1) & IS_CHAR_BLOCK ) ) dir += ({ 222 });
                        if( !( get_block(z, x    , y - 1) & IS_CHAR_BLOCK ) ) dir += ({ 333 });
                        if( !( get_block(z, x - 1, y - 1) & IS_CHAR_BLOCK ) ) dir += ({ 444 });
                        if( !( get_block(z, x - 1, y    ) & IS_CHAR_BLOCK ) ) dir += ({ 555 });
                        if( !( get_block(z, x - 1, y + 1) & IS_CHAR_BLOCK ) ) dir += ({ 666 });
                        if( !( get_block(z, x    , y + 1) & IS_CHAR_BLOCK ) ) dir += ({ 777 });
                        if( !( get_block(z, x + 1, y + 1) & IS_CHAR_BLOCK ) ) dir += ({ 888 });

                        if( ( size = sizeof(dir) ) && ( p = dir[ random(size) ] ) )    // 找到可走路径
                        {
                                cmd = sprintf("%d", p);

                                switch( me->get_walk_step() )
                                {
                              default : if( strlen(cmd) > 1 ) cmd = cmd[0..0];  break;
                               case 2 : if( strlen(cmd) > 2 ) cmd = cmd[0..1];  break;
                                }
                                GO_CMD->main_npc(me, cmd);
                        }
                }
        }

        x = abs( x - get_x(me) );  y = abs( y - get_y(me) );
        walk = ( x > y ) ? x : y;

        if( walk > 0 )
        {
                set_heart_state(me, 0);
                set_heart_count_2(me, 3 * walk + 1);    // walk * 10 / 4
        }
}