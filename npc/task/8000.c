
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <music.h>
#include <task.h>

#define TREASURE "/item/std/8000"

inherit NPC;
// 函数：通辑罪犯
int is_criminal() { return 1; }

// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Trọng Phạm" + NPC_NAME_D->get_criminal_name());
        set_char_picid(8000); // 蒙面人
        set_walk_speed(WALK_SPEED_4);
        set_attack_speed(ATTACK_SPEED_4);

        setup();

        set("birthday", time());
        set_char_type(FIGHTER_TYPE);
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：复位处理
void reset()
{
        object who;
        string *member, id;
        int i, size;

        if (gone_time(get("birthday")) >= 1800) // 30 分钟
        {
                i = get("task");
                who = find_player(sprintf("%d", i));
                if (objectp(who))
                        send_user(who, "%c%s", ';', get_name() + "Đã chạy trốn không thấy tăm hơi.Nhiệm vụ thất bại……");
                remove_from_scene();
                destruct(this_object());
        }
        else
        {
                member = get("user");
                for (i = 0, size = sizeof(member); i < size; i++)
                        if (!(who = find_player(member[i])))
                                member[i] = "";
                if (sizeof(member - ({""})) < 1)
                {
                        remove_from_scene();
                        destruct(this_object());
                }
        }
}

// 函数：可以接受战斗
int can_be_fighted(object who)
{
        object owner;
        string leader, id;

        if (who->get_enemy() == this_object())
                return 1;

        if (owner = who->get_owner())
                who = owner;
        if (who->is_npc())
                return 0;

        if (stringp(id = who->get_task("criminal")) && id == sprintf("%x#", getoid(this_object())))
                return 1;
        send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), get_name() + "：\n    Ta đã vất vả mới chạy trốn được,không ai có thể giữ ta lại ha ha !!");
        return 0;
}

int can_fight(object who)
{
        object owner;
        string leader, id;
        if (who->is_npc() && objectp(owner = who->get_owner()))
                who = owner;
        if (who->is_npc())
        {
                set_enemy(0);
                return 0;
        }
        if (who->get_enemy() == this_object())
                return 1;

        if (stringp(id = who->get_task("criminal")) && id == sprintf("%x#", getoid(this_object())))
                return 1;
        set_enemy(0);
        return 0;
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus(object who)
{
        ::win_bonus(who);
        __FILE__->win_bonus_callout(this_object(), who);
}

// 函数：死亡奖励(在线更新)
void win_bonus_callout(object me, object who)
{
        int id, level;
        object map;

        if (!objectp(map = get_map_object(get_z(me))) || !map->is_scene())
                return;
        id = me->get("task");
        if (!(who = find_player(sprintf("%d", id))))
                return;

        level = me->get_level();
        // who->delete_task("criminal.time");
        who->set_task("criminal.bonus", 1);
        who->set_task("criminal.level", me->get("level"));
        who->set_task("criminal.name", me->get_name());
        who->set_task("criminal.map", map->get_name());
        "/sys/sys/count"->add_task("王捕头", 1);
        send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CRIMINAL, 1, "");
        send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_CRIMINAL, "Nhiệm vụ lấy trong Bảo Khố");
        send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CRIMINAL, 1, "Truy Bắt Đào Phạm(Đã hoàn thành)");
}

/*
void heart_beat_walk()
{
	string robber;
	object *member,who,owner;
	object me = this_object();
	owner =  me->get_enemy();
	if ( objectp(owner) )
		return ;	
	member = get_range_object_2(me, me->get_max_seek(), CHAR_TYPE)+get_range_object_2(me, me->get_max_seek(), USER_TYPE)-({me});
	if ( sizeof(member) != 0 )
	{
		robber = sprintf( "%x#", getoid(me) );
		foreach(who in member)
		{
				
			if ( who->is_die() ) 
				continue;
			if( (owner = who->get_owner()) && (owner->get_task("criminal") != robber) ) 
			{
				continue;	
			}
			else if (  !(owner = who->get_owner()) && who->get_task("criminal") != robber )
				continue;			
			me->set_main_enemy(who);
			::heart_beat_walk();
			return;
		}		
	}
	owner =  me->get_enemy();
	if ( !objectp(owner) )
		return ;
        if( get_z(owner)!=get_z(me) || distance_between(me, owner) > 20 )  
        {
		me->set_enemy(0);
		return ;
	}

}
*/

/*
void heart_beat_attack( )
{
	string robber;
	object who;
	object me = this_object();
	
	who = me->get_enemy();
	if ( !objectp(who) )
		return ;
        if( get_z(who)!=get_z(me) || distance_between(me, who) > 20 )  
        {
		me->set_enemy(0);
		return ;
	}	

	::heart_beat_attack();

}
*/

// 函数：掉宝奖励
void drop_items(object who)
{
        object item;
        int p, rate, level;
        int z, x, y;
        object me = this_object();

        z = get_z(me);
        x = get_x(me);
        y = get_y(me);

        p = random(100);
        level = me->get_level();

        rate = me->correct_drop_rate(level - who->get_level()) * who->get_online_rate() / 100;

        if (p < 25 * rate / 100) // 金钱
        {
                if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
                {
                        item = new ("/item/std/0001");
                        TEAM_D->drop_item(item, who);
                        item->set_user_id(who->get_id());
                        item->set_value(level * 20 + 1000 + random(101));
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set("time", time());
                }
        }
        else if (p < 50 * rate / 100) // 藏宝图
        {
                if (load_object(TREASURE) && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
                {
                        item = new (TREASURE);
                        TEAM_D->drop_item(item, who);
                        item->set_user_id(who->get_id());
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set("time", time());
                        if (!(p = XY_D->get_city_point(-1, IS_ITEM_BLOCK)))
                                return; // XY_D->get_xy_point( abs( level - 10 + random(21) ), IS_ITEM_BLOCK )
                        item->set_map_z(p / 1000000);
                        item->set_map_x((p % 1000000) / 1000);
                        item->set_map_y(p % 1000);
                }
        }
}