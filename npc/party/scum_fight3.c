
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <ansi.h>
inherit BADMAN;
#define SCUM_NPC "npc/party/scum_fight3"
int *nxy = ({080034,087040,094046,101051,109057,116063,074040,081046,089051,097056,105062,111067,069046,077052,085056,092061,100067,107071,064051,072056,081061,087065,096071,0102075,059055,067060,075066,082070,091076,097079,054059,063066,071071,077075,084080,089085,048066,055071,062076,068081,074086,080091,});

// 函数：远程攻击的怪
// int is_caster() { return 1; }

// 函数：是否允许移动
// int is_moveable() { return 0; }    // 禁止使用 go 命令

// 函数：跟随对手(心跳之中调用)
// void follow_user() { }    // 禁止跟随敌人
int generate_copy_npc(int tId,int z,int level);
void init_npc(object npc);
// 函数：获取人物造型
int get_char_picid() { return 1001; }

// 函数：构造处理
void create()
{
        set_name("Võ Lâm Bại Hoại");

        set_char_type(FIGHTER_TYPE);    // init_level 要用到
        
        set_head_color(0x0);

//        NPC_ENERGY_D->init_level( this_object(), 22+ random(3) );    // 
        set_max_seek(4);

        setup();
	set("anti_05311",1);	//不能迷魂
        set_char_type(FIGHTER_TYPE);    // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action( object who ) { return 0; }    // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：自动战斗(遇玩家时调用)
// void auto_fight( object who ) { }

// 函数：任务处理(有任务时调用)
// void check_legend_task( object who ) { USER_TASK_D->kill_legend_npc( who, this_object() ); }

// 函数：掉宝奖励
void drop_items( object who ) 
{
//	"npc/copy/9999"->npc_die( this_object(), who ); 
	 __FILE__ ->drop_items_callout( this_object(), who ); 
}

// 函数：掉宝奖励(在线更新)
void drop_items_callout( object me, object who )
{
        object item, leader,map,*member,npc1;
        string file, owner, id;
        int p, rate, i, size, gold, equip, rate1 ,tId,level;
        int z, x, y;


	tId = me->get("team_id");
//	name = npc->get_name();
//	map = TEAM_D->get_copy_scene(tId,COPY_SCUM);
	map = get_map_object(get_z(me));
	if ( !map )
		return ;
	map->add("copy_npc_die",1);
	z = map->get_id();
	//出现新的怪
	if ( map->get("scene_npc_amount") < map->get("copy_npc_amount") )
	{
		generate_copy_npc(tId,map->get_id(),map->get("copy_level"));
		if (map->get("copy_npc_die")%100==0)
		{
			member = "inh/std/scum_map"->get_all_user( map );
			member -= ({0});
			size=sizeof(member);
			for(i=0;i<size;i++)
			{
				if ( get_z(member[i]) != z )
					continue;
				send_user( member[i], "%c%s", ';', sprintf(HIY"Còn %d tên Võ Lâm Bại Hoại" ,500-map->get("copy_npc_die")));
			}
		}
	}
	//大BOSS出现
/*	if ( !map->get("big_copy_boss") && (map->get("copy_npc_die")==map->get("copy_npc_amount")) )
	{
		npc1 = new("npc/party/scum_ringleader2");

		if ( !npc1 )
			return ;
		level=map->get("copy_level")+10;
		if (level>149) level=149;
		NPC_ENERGY_D->init_level(npc1,level);
		init_npc(npc1);
		npc1->set_max_seek(8);
		npc1->set("team_id",tId);

		member = "inh/std/scum_map"->get_all_user( map );
//		member = who->get_team();
		member -= ({0});
		size=sizeof(member);
		i=random(size);
		x=get_x(member[i]);y=get_y(member[i]);
		npc1->add_to_scene(z,x,y);
		for(i=0;i<size;i++)
		{
			if ( get_z(member[i]) != z )
				continue;
			send_user( member[i], "%c%s", ';', HIY"Oa!Oa!Oa! Thủ lĩnh Võ Lâm Bại Hoại xuất hiện。" );
		}

		map->set("big_copy_boss",1);
	}*/
	//掉师门物品
/*	z = get_z(me);  x = get_x(me);  y = get_y(me);
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
        rate1 = me->correct_drop_rate( me->get_level() - who->get_level() ) * who->get_online_rate() / 100;
	p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
	if ( !p )
		return;
	rate = random(100);

	if ( rate < 50 * rate1 / 100 )	//师门物品
	{
                if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                {
			item = new(sprintf("item/40/40%d",random(72)+11));
			TEAM_D->drop_item(item,who);
			item->set_user_id(owner);
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }
	}*/

}

int can_fight( object who ) 
{ 
	if(!get_map_object(get_z(who))->is_scum_map())
	        return 0;
        return 1;
}

//生成一只怪
int generate_copy_npc(int tId,int z,int level)
{
	int i,size,iShape,*nShape,rand,iLev,p,x,y,iAtt,iCast;
	object npc,map,*nObj=({});
	string name,*attrib,*nKind;
	mapping mpTmp;
	
	if( !objectp( map = get_map_object(z) ) || !map->is_virtual_scene() ) 
		return 0;
	npc = new(SCUM_NPC);
	npc->set("team_id",tId);
	npc->set_level(level);

        NPC_ENERGY_D->init_level( npc, level );    

	if( !( p = efun::get_xy_point( 151, IS_CHAR_BLOCK ) ) )
		return 0;
	x = ( p % 1000000 ) / 1000;  y = p % 1000;
	npc->add_to_scene(z,x,y);

//	npc->add_to_scene(z,nxy[random(sizeof(nxy))]/1000,nxy[random(sizeof(nxy))]%1000);
//	npc->add_to_scene(z,80,60);

	map->add("scene_npc_amount",1);
	return 1;
}


//大BOSS
void init_npc(object npc)
{
	int p,level;
	
	level = npc->get_level();
	p = random(100);
	if ( p < 20)	//低物防高敏型
	{
		npc->set_skill(348,level);
		npc->set_skill(251,level);
		npc->set_skill(241,level);
		npc->set_char_picid(8011);
                npc->set_walk_speed(3);
                npc->set_attack_speed(10);	
                npc->add_dp(-1*npc->get_dp()/4);
                npc->add_max_hp(npc->get_max_hp()*20);	
                npc->add_sp(npc->get_sp()*2);
                npc->add_ap(npc->get_ap()*4/5);
                npc->add_mp(npc->get_mp()/2);  
                npc->set("scum.type",1);              		
	}
	else if ( p < 40 )	//高物防低法防型
	{
		npc->set_skill(221,level);
		npc->set_skill(231,level);
		npc->set_char_picid(0252);
                npc->set_walk_speed(3);
                npc->set_attack_speed(10);	
                npc->add_dp(npc->get_dp()*3);
                npc->add_max_hp(npc->get_max_hp()*10); 	
                npc->add_pp(-1*npc->get_pp()*3/10);                
                npc->add_ap(npc->get_ap()*4/5);                
                npc->add_mp(npc->get_mp()/2);  
                npc->set("scum.type",2);              		
	}
	else if ( p < 60 )	//高法防低物防型
	{
		npc->set_skill(423,level);
		npc->set_skill(424,level);
		npc->set_skill(425,level);
		npc->set_char_picid(8010);
                npc->set_walk_speed(3);
                npc->set_attack_speed(10);	
                npc->add_dp(-1*npc->get_dp()/4);
                npc->add_max_hp(npc->get_max_hp()*10); 	
                npc->add_sp(npc->get_sp());  
                npc->add_pp(npc->get_pp()*3/2);                
                npc->add_cp(npc->get_cp());
		npc->add_mp(npc->get_mp()*6);
                npc->set("scum.type",3);              		
	}	
	else if ( p < 70 )	//长血型：拳脚类
	{
		npc->set_skill(211,level);
		npc->set_skill(317,level);
		npc->set_char_picid(8000);
                npc->set_walk_speed(3);
                npc->set_attack_speed(10);	
                npc->add_dp(-1*npc->get_dp()/5);        
                npc->add_max_hp(npc->get_max_hp()*40); 
                npc->add_pp(-1*npc->get_pp()/5);                
                npc->add_mp(npc->get_mp()/2);                 
                npc->add_ap(npc->get_ap()*9/10);  
                npc->set("scum.type",4);              		
	}
	else if ( p < 90 )	//长血高物防高法防型：远程暗器类
	{
		npc->set_skill(261,level);
		npc->set_char_picid(8012);
                npc->set_walk_speed(3);
                npc->set_attack_speed(10);	
		npc->add_dp(npc->get_dp()*9/20);
		npc->add_max_hp(npc->get_max_hp()*12); 
 		npc->add_sp(npc->get_sp()*3);
 		npc->add_pp(npc->get_pp()*9/5);
 		npc->add_mp(npc->get_mp());
 		npc->add_ap(npc->get_ap()/2);
                npc->set("scum.type",5);              		
	}
	else 	//强攻型加召唤
	{
		npc->set_skill(414,level);
		npc->set_char_picid(8013);
                npc->set_walk_speed(3);
                npc->set_attack_speed(8);	
                npc->add_dp(npc->get_dp()*9/20);
                npc->add_ap(npc->get_ap()); 
                npc->add_max_hp(npc->get_max_hp()*12);                 
                npc->add_sp(npc->get_sp()*3);  
                npc->add_pp(npc->get_pp()*9/20);      
                npc->add_mp(npc->get_mp()*3/2);  
                npc->set("scum.type",6);              		
	}	
}

