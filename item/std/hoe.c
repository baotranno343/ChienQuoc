#include <ansi.h>
#include <item.h>
#include <equip.h>
#include <effect.h>
#include <task.h>
#include <skill.h>

#define MONSTER "npc/task/robber"

inherit ITEM;
inherit USABLE;

int get_item_color(){return 1;}

int is_usable() {return 1;}

private int xx,yy,zz;

void set_map_x(int x){xx = x;}
int get_map_x(){return xx;}

void set_map_y(int y){yy = y;}
int get_map_y(){return yy;}

void set_map_z(int z){zz = z;}
int get_map_z(){return zz;}

int get_item_type(){return ITEM_TYPE_TREASURE;}

void begin_hoe(object player);//开始挖宝
void hoe_work_break(object player);//挖宝工作中断。

void use_bonus(object player);//挖宝对应的效果。
void create()
{
	set_name("挖宝小锄头");
	set_picid_1(3402);
	set_picid_2(3402);
	set_unit("把");
	set_no_give(1);
        set_no_sell(1);
}

string get_desc()
{
	object map;
	int p;
	if(!clonep()) return "挖宝总动员特有的挖宝专用小锄头，右击使用。";
	if(!(map = get_map_object(zz)))
	{
		if(p = XY_D->get_city_point(-1,IS_ITEM_BLOCK))
		{
			set_map_z(p/1000000);
			set_map_x((p%1000000)/1000);
			set_map_y(p%1000);
		}
		else
		{
			return "你好呀地图出错了!";
		}
	}
	return "挖宝总动员特有的挖宝专用小锄头，右击使用。";
}

int get_use_effect(object player)
{
	__FILE__->get_use_effect_callout(player,this_object());
}
int get_use_effect_callout(object player, object item)
{
	if(get_z(player)!= item->get_map_z()
	||abs(get_x(player) - item->get_map_x())>2
	||abs(get_y(player) - item->get_map_y())>2
	)
	{
		send_user(player, "%c%s", '!', "您挖宝的位置不对。");
		return 0;
	}
	use_bonus(player);//开始挖宝
	return 0;
}
/*
void begin_hoe(object player)
{
	set_effect_2(player, EFFECT_HOE_WORK, 1,12);
	send_user(player, "%c%c%w%s", 0x5a, 0, 12, "挖宝活动中……");
	send_user( get_scene_object_2(player, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(player), 02011, 10, OVER_BODY, PF_LOOP );
}

void hoe_work_break(object player)
{
	set_effect(player, EFFECT_HOE_WORK, 0);
	send_user(player, "%c%c%c", 0x5a, 1, 0);
	send_user( get_scene_object_2(player, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(player), 02011, 0, OVER_BODY, PF_STOP );
}
*/
void use_bonus(object player)
{
	int rand,level,move_result,picid,citypoint,index,gender;
	int z,x,y,p,size,flag;
	string name,result,filename,family_name;
	object goods,npc,map,item;
	object* monster_list;
	string* gold_equip;
	int *decoration = ({HEAD_TYPE,NECK_TYPE,ARMOR_TYPE,WAIST_TYPE,BOOTS_TYPE});
	rand = random(10000);
	flag = 0;//这个标志用来标识是否获得物品。

	if(objectp(item = present("挖宝小锄头",player,1,MAX_CARRY)))
	{
		item->remove_from_user();
		destruct(item);
	}
	else
	{
//		hoe_work_break(player);
		return;
	}
	if(rand < 2000)///item/91/9101,活络丸
	{
		goods = new("item/91/9101");
		if(!goods)
		{
			return ;
		}
		goods->set_amount(15);
		if(move_result = goods->move(player,-1))
		{
			flag = 1;
		}
		else
		{
			destruct(goods);
		}
	}
	else if(rand < 4000)//安神丸 /item/91/9111
	{
		goods = new("item/91/9111");
		if(!goods)
		{
			return ;
		}
		goods->set_amount(15);
		if(move_result = goods->move(player,-1))
		{
			flag = 1;
		}
		else
		{
			destruct(goods);
		}
	}
	else if(rand < 6000)//放劫匪出来
	{
		switch(level = 35+random(8)*10)
		{
			default:
				name = "洞庭劫匪";picid = 8010; citypoint = 6;break;
			case 45:
				name = "山西劫匪";picid = 0251; citypoint = 2;break;
			case 55:
				name = "太行劫匪";picid = 8011; citypoint = 4;break;
			case 65:
				name = "中原劫匪";picid = 0252; citypoint = 8;break;
			case 75:
				name = "山东劫匪";picid = 8012; citypoint = 10;break;
			case 85:
				name = "关外劫匪";picid = 8012; citypoint = 3;break;
			case 95:
				name = "长白劫匪";picid = 8011; citypoint = 7;break;
			case 105:
				name = "关外劫匪";picid = 8013; citypoint = 5; break;
		}
		size = 5;
		for(index = 0; index < size; index++)
		{
			if(!(p = XY_D->get_city_point(citypoint,IS_CHAR_BLOCK)))continue;
			z = p/1000000; x = p%1000000/1000;y = p%1000;
			npc =new(MONSTER);
			if(!npc)
			{
				return ;
			}
			if(!objectp(map = get_map_object(z))||!map->is_scene())
			{
				destruct(npc);continue;
			}
			monster_list = map->get("monster");
			if(arrayp(monster_list))
			{
				monster_list -= ({0});//去掉已经死亡的怪。
				if(sizeof(monster_list)>100)
				{
					destruct(npc); continue;
				}

			}
			else
			{
				monster_list = ({});
			}
			npc->set_name(name);
			npc->set_char_picid(picid);
			NPC_ENERGY_D->init_level(npc,level);
			npc->add_max_hp(npc->get_max_hp()*21);
                        npc->add_dp( level * 15 / 10 );
                        npc->add_pp( level * 8 / 10 );
                        npc->add_ap( level * 2 );
                        npc->add_to_scene(z, x, y, 3);
		        npc->set_walk_speed(4);
		        npc->set_attack_speed(15);
                        npc->set( "task", player->get_number() );
			map->add_reset(npc);    // 加入复位列表
                        monster_list += ({ npc });  map->set("monster", monster_list);
		}
		if(map)
		{
			result = sprintf("%s挖宝时放出%s了，%s已经逃窜到"HIR"%s国",player->get_name(),name,name,map->get_name());
			USER_D->user_channel(result);
		}

	}
	else if(rand < 7000)//item/final/15/1502初级物攻
	{
		goods = new("item/final/15/1502");
		if(!goods)
		{
			return ;
		}
		if(move_result = goods->move(player,-1))
		{
			flag = 1;
		}
		else
		{
			destruct(goods);
		}

	}
	else if(rand < 8000)//item/final/15/1504 初级法功
	{
		goods = new("item/final/15/1504");
		if(!goods)
		{
			return ;
		}

		if(move_result = goods->move(player,-1))
		{
			flag = 1;
		}
		else
		{
			destruct(goods);
		}
	}
	else if(rand < 8900)//50000游戏币.
	{
		player->add_cash(50000);

		flag = 1;
		send_user(player, "%c%s", ';', "您获得 50000 金。");
		USER_D->user_channel("恭喜"+player->get_name()+"在挖宝总动员活动中获得 50000 金。");
	}
	else if(rand < 9180)//50-90级随机白色图纸,item/product/62070-62080.
	{
		switch(random(7))
		{
			default:
				filename = "item/product/62070";break;
			case 1:
				filename = "item/product/62071";break;
			case 2:
				filename = "item/product/62073";break;
			case 3:
				filename = "item/product/62076";break;
			case 4:
				filename = "item/product/62084";break;
			case 5:
				filename = "item/product/62087";break;
			case 6:
				filename = "item/product/62091";break;
		}
		goods = new(filename);
		if(!goods)
		{
			return ;
		}
		if(move_result = goods->move(player,-1))
		{
			flag = 1;
		}
		else
		{
			destruct(goods);
		}
	}
	else if(rand < 9380)//随机进阶书 /quest/book
	{
		if( load_object( filename = BOOK_FILE->get_book_file() ) )
		{
			goods = new(filename);
			if(!goods)
			{
				return ;
			}
			if(move_result = goods->move(player,-1))
			{
				flag = 1;
				USER_D->user_channel("恭喜"+player->get_name()+"玩家在挖宝总动员活动中获得"+goods->get_name()+"。");
			}
			else
			{
				destruct(goods);
			}
		}
	}
	else if(rand < 9580)//随机蓝色精元丹 item/44/4488
	{
		goods = new("item/44/4488");
		if(!goods)
		{
			return ;
		}

		if(move_result = goods->move(player,-1))
		{
			flag = 1;
			USER_D->user_channel("恭喜"+player->get_name()+"玩家在挖宝总动员活动中获得"+goods->get_name()+"。");
		}
		else
		{
			destruct(goods);
		}
	}
	else if(rand < 9730)//中级物攻 item/final/15/1507
	{
		goods = new("item/final/15/1507");
		if(!goods)
		{
			return ;
		}

		if(move_result = goods->move(player,-1))
		{
			flag = 1;
		}
		else
		{
			destruct(goods);
		}
	}
	else if(rand < 9880)//中级法功 item/final/15/1510
	{
		goods = new("item/final/15/1510");
		if(!goods)
		{
			return ;
		}

		if(move_result = goods->move(player,-1))
		{
			flag = 1;
		}
		else
		{
			destruct(goods);
		}

	}
	else if(rand < 9980)//50—90级随机蓝色图纸
	{
		switch(random(7))//62312, 62313, 62318, 62324
		{
			default:
				filename = "item/product/62312";break;
			case 1:
				filename = "item/product/62313";break;
			case 2:
				filename = "item/product/62318";break;
			case 3:
				filename = "item/product/62324";break;
			case 4:
				filename = "item/product/62330";break;
			case 5:
				filename = "item/product/62325";break;
			case 6:
				filename = "item/product/62321";break;
		}
		goods = new(filename);
		if(!goods)
		{
			return ;
		}

		if(move_result = goods->move(player,-1))
		{
			flag = 1;
			USER_D->user_channel("恭喜"+player->get_name()+"玩家在挖宝总动员活动中获得"+goods->get_name()+"。");
		}
		else
		{
			destruct(goods);
		}
	}
	else if(rand < 9985)//残图一角 item/std/8001,item/std/8002,item/std/8003,item/std/8004
	{
		switch(random(4))
		{
			default:
				filename = "item/std/8001";break;
			case 0:
				filename = "item/std/8002";break;
			case 1:
				filename = "item/std/8003";break;
			case 3:
				filename = "item/std/8004";break;
		}
		goods = new(filename);
		if(!goods)
		{
			return ;
		}

		if(move_result = goods->move(player,-1))
		{
			flag = 1;
			USER_D->user_channel("恭喜"+player->get_name()+"玩家在挖宝总动员活动中获得"+goods->get_name()+"。");
		}
		else
		{
			destruct(goods);
		}
	}
	else if(rand < 9990)//随机初级法宝
	{
		if(load_object(filename = TALISMAN_FILE->get_talisman_file()))
		{
			goods = new(filename);
			if(!goods)
			{
				return ;
			}

			if(move_result = goods->move(player,-1))
			{
				flag = 1;
				USER_D->user_channel("恭喜"+player->get_name()+"玩家在挖宝总动员活动中获得"+goods->get_name()+"。");
			}
			else
			{
				destruct(goods);
			}
		}

	}
	else if(rand < 9995)//金色装备/item/01/0202
	{
		level = player->get_level();
		if(level < 0)
		{
			level = 1;
		}
		gender = player->get_gender();
		family_name = player->get_fam_name();
		gold_equip = WEAPON_FILE->get_family_equip(family_name,gender,level,decoration[random(sizeof(decoration))]);
		if(sizeof(gold_equip)> 0)
		{
			goods = new(gold_equip[random(sizeof(gold_equip))]);
			if(!goods)
			{
				return;
			}
			ITEM_EQUIP_D->init_equip_prop_3(goods);
			if( move_result = goods->move(player, -1) )
	        	{
	                	goods->add_to_user(move_result);
	                	USER_D->user_channel("恭喜"+player->get_name()+"玩家在挖宝总动员活动中获得"+goods->get_name()+"。");
	        	}
	        	else
	        	{
	        		destruct(goods);
	        	}
		}
	}
	else////随机金色精元丹 item/44/4489
	{
		goods = new("item/44/4489");
		if(!goods)
		{
			return ;
		}

		if(move_result = goods->move(player,-1))
		{
			flag = 1;
			USER_D->user_channel("恭喜"+player->get_name()+"玩家在挖宝总动员活动中获得"+goods->get_name()+"。");
		}
		else
		{
			destruct(goods);
		}
	}
	if(flag == 1 && goods)
	{
		goods->add_to_user(move_result);
		send_user(player, "%c%s", ';', "您获得"+goods->get_name()+"。");
	}
}