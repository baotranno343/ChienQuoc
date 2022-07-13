#include <map.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

#define LT_SEC 0
#define LT_MIN 1
#define LT_HOUR 2
#define LT_MDAY 3
#define LT_MON 4
#define LT_YEAR 5
#define LT_WDAY 6
#define LT_YDAY 7
#define LT_GMTOFF 8
#define LT_ZONE 9

void generate_baobao(object map);

// 函数：取出生地坐标
int get_birth_xy(object who)
{
        int z;
        if (who->get_level() < 30)
        {
                z = get_z(who);
                if (z >= 1 && z <= 9) //新手村死亡的
                {
                        switch (z)
                        {
                        case 1..3:
                                z = 1;
                                break;
                        case 4..6:
                                z = 4;
                                break;
                        case 7..9:
                                z = 7;
                                break;
                        }
                        return z * 1000000 + get_jumpin(z, 32);
                }
                else
                        return 1 * 1000000 + get_jumpin(1, 32);
        }
        else
                return 80 * 1000000 + get_jumpin(80, 30);
}

// 函数：在安全区内
int is_inside_safe_zone(int z, int x, int y)
{
        return inside_jumpin(z, x, y, 28); // 跳入点 27: 新手区；28: 城内区
        //      return inside_jumpin(z, x, y, 28) || inside_jumpin(z, x, y, 30);    // 跳入点 28: 城内区；30: 出生地
        //      return inside_jumpin(z, x, y, 30) || inside_jumpin(z, x, y, 31);    // 跳入点 30: 出生地；31: 摆摊区
}

// 函数：坐标在城内
int is_inside_city(int z, int x, int y)
{
        return inside_jumpin(z, x, y, 28); // 跳入点 28: 城内区
}

// 函数：坐标在战场
int is_inside_battle(int z)
{
        return z / 1000 == 9;
}

// 函数：坐标在副本内
int is_inside_copy(int z)
{
        return (z >= COPY_MAP_BEGIN && z <= COPY_MAP_END);
}
//是否门派偷袭战活动的地图
int is_scum_map(int z)
{
        object map;
        map = get_map_object(z);
        if (!map)
                return 0;
        return map->is_scum_map();
}
//是否可以跳转
int can_jump(object who, int z0, int z)
{
        int iTime;
        object map, item5;
        mixed *mixTime;
        iTime = time();
        mixTime = localtime(iTime);

        if (is_inside_copy(z0) || is_scum_map(z0))
                return 0;
        map = get_map_object(z);
        if (get_z(who) != 889)
        {
                if (map && map->is_wushuang())
                        return 0;
        }
        /*	if ( get_z(who)==888 && objectp( item5 = present("Cờ Hiệu Vô Song Thành", who, 1, MAX_CARRY*4) ) ){
	if ( map && map->get_client_id()==80 )
		return 0;
		}*/
        if (map && map->is_wushuang_palace())
                return "/sys/party/vstfix"->can_enter_palace(who, map);
        return 1;
}
// -------------------------------------------------------------

// 函数：移入 VOID 场景
void add_to_void(object me)
{
        int z, p;
        object map;

        //	if ( me->is_pet() )	是否跟DOWN机有关，试试看
        //	{
        //		z = get_z(me);
        //		if ( !z )
        //		{
        //			return ;
        //		}
        //		if( objectp( map = get_map_object(z)) && !map->is_virtual_scene() )
        //			return ;
        //	}

        if ((p = MAP_D->get_birth_xy(me)) // 出生地
            && (z = p / 1000000) && (p = get_valid_xy(z, (p % 1000000) / 1000, p % 1000, IS_MAP_BLOCK)))
        {
                me->add_to_scene(z, p / 1000, p % 1000, 3);
        }
        else if ((p = get_jumpin(80, 31)) // 跳入点 31: 摆摊区
                 && (z = 80) && (p = get_valid_xy(z, p / 1000, p % 1000, IS_CHAR_BLOCK)))
        {
                me->add_to_scene(z, p / 1000, p % 1000, 3);
        }
}

// -------------------------------------------------------------

// 函数：载入NPC 文件
void load_npc_file(object map, string file)
{
        string *line, path;
        int xyd, i, size;

        if (!file_exist(file))
                return;

        line = explode(read_file(file), "\n");

        for (i = 0, size = sizeof(line); i < size; i++)
        {
                if (line[i][0] == '#' || line[i] == "")
                        continue;
                if (line[i][ < 1] <= ' ')
                        line[i] = line[i][0.. < 2]; // UNIX 格式
                if (line[i][0] == '#' || line[i] == "")
                        continue;

                if (!sscanf(line[i], "%s:%s", xyd, path))
                {
                        log_file(ERROR, sprintf("错误: %s 第 %d 行人物定义错。\n", file, i + 1));
                        continue;
                }

                map->set_xy_define(xyd, path);
        }
}

// 函数：复位NPC 对象
void reset_npc(int id)
{
        mapping officer;
        object map, *char, npc;
        string *key;
        int z, x, y, d, p, i, size;

        if (!objectp(map = get_map_object(id)) || !map->is_scene())
                return;

        if (mapp(officer = map->get_xy_dbase()))
        {
                for (i = 0, size = sizeof(key = keys(officer)); i < size; i++)
                {
                        if (npc = map->get_npc_object(key[i]))
                        {
                                npc->reset();
                                continue;
                        }

                        if (!sscanf(key[i], "%d-%d,%d,%d", z, x, y, d) || !(p = get_valid_xy(z, x, y, IS_CHAR_BLOCK)) || !load_object(officer[key[i]]))
                                continue;

                        npc = new (officer[key[i]]);
                        npc->add_to_scene(z, p / 1000, p % 1000, d);
                        set_block(z, get_x(npc), get_y(npc), FLY_BLOCK);
                        npc->set_start_place(sprintf("%d", p));
                        map->add_npc(key[i], npc);
                }
        }

        if (arrayp(char = map->get_reset_dbase()))
        {
                for (i = 0, size = sizeof(char); i < size; i++)
                        if (char[i])
                                char[i]->reset();
                map->add_reset(0); // 重要：RESET 清理
        }
        //生成怪物宝宝
        generate_baobao(map);
}

// 函数：复位物品对象
void reset_item(int z)
{
        object *item;
        int x, y, max_x, max_y;

        reset_eval_cost();

        max_x = get_map_max_x(z);
        max_y = get_map_max_y(z);

        for (x = 0; x < max_x; x += AREA_SIZE)
                for (y = 0; y < max_y; y += AREA_SIZE)
                {
                        if (have_scene_object(z, x, y, ITEM_TYPE, 1))
                        {
                                item = get_scene_object(z, x, y, ITEM_TYPE, 1);
                                item -= ({0});
                                item->reset();
                        }
                }
}

// -------------------------------------------------------------
/*	从前的暂时注释掉
// 函数：刷出 NPC 对象
void clone_npc( object map )
{
        object *char, npc;
        string *file;
        int total, caster;
        int z, p, i, size, size2, size3;

        reset_eval_cost();
        
//        map->set_clean_time(100);
//        set_heart_loop(map, 600);

        z = map->get_id();

        total = map->sizeof_fighter_dbase();
        caster = map->sizeof_caster_dbase();

        size = map->get_fighter_amount();

        if( map->sizeof_fighter_file() > 0 )    // 复制 NPC
        {
                file = map->get_fighter_file();
                size2 = sizeof(file);  size3 = size2 - map->get_caster_amount();

                for( i = 0; i < size && total < size; i ++, total ++ )
                {
                        if( !( p = get_xy_point(z, IS_CHAR_BLOCK) ) ) continue;

                        //npc = new( file[ random( caster < 20 ? size2 : size3 ) ] );
                        npc = new( file[ random( size2 ) ] );

                        npc->add_to_scene(z, p / 1000, p % 1000, 3);
                        map->add_fighter(npc);
                        npc->set_start_place(sprintf("%d",p ));
                        if( npc->is_caster() ) { map->add_caster(npc);  caster ++; }
                }

                map->set_add_amount( range_value( map->get_fighter_amount() - map->sizeof_fighter_dbase(), 0, MAX_NUMBER ) );
        }
}
*/
// 函数：刷出 NPC 对象 -- 增加了定点刷怪的模式（怪物回收）
void clone_npc(object map)
{
        object *char, npc;
        string *file;
        int total, caster;
        int z, p, i, size, size2, size3, size4, x, y;
        int *reflash_now;

        reset_eval_cost();

        //        map->set_clean_time(100);
        //        set_heart_loop(map, 600);
        z = map->get_id();
        total = map->sizeof_fighter_dbase();
        caster = map->sizeof_caster_dbase();
        size = map->get_fighter_amount();

        if (map->sizeof_fighter_file() > 0) // 复制 NPC
        {
                map->set("reflash_time", time());
                reflash_now = map->get("reflash_now");
                file = map->get_fighter_file();
                size2 = sizeof(file);
                size3 = sizeof(reflash_now);
                for (i = 0; i < size3 && total < size; i++, total++)
                {
                        if (reflash_now[i])
                        {
                                x = (reflash_now[i] / 1000) + pow(-1, random(2) + 1) * (random(5) + 5);
                                y = (reflash_now[i] % 1000) + pow(-1, random(2) + 1) * (random(5) + 5);
                                if (get_block(z, x, y))
                                {
                                        if (random(2))
                                        {
                                                p = reflash_now[i];
                                        }
                                        else
                                        {
                                                if (!(p = get_xy_point(z, IS_CHAR_BLOCK)))
                                                {
                                                        p = reflash_now[i];
                                                }
                                        }
                                }
                                else
                                {
                                        p = x * 1000 + y;
                                }
                        }
                        else
                        {
                                if (!(p = get_xy_point(z, IS_CHAR_BLOCK)))
                                {
                                        continue;
                                }
                                reflash_now[i] = p;
                        }
                        npc = new (file[random(size2)]);
                        npc->add_to_scene(z, p / 1000, p % 1000, 3);
                        map->add_fighter(npc);
                        npc->set_start_place(sprintf("%d", p));
                        npc->set("I_need_reflash", 1);
                        if (npc->is_caster())
                        {
                                map->add_caster(npc);
                                caster++;
                        }
                }
                map->delete ("reflash_now");
                map->set("reflash_now", map->get("reflash_next"));
                map->delete ("reflash_next");
                size4 = sizeof(map->get("reflash_now"));
                if (size4 <= 0 || size4 + total < size)
                {
                        size3 = size2 - map->get_caster_amount();
                        for (i = 0; i < size && total < size - size4; i++, total++)
                        {
                                if (!(p = get_xy_point(z, IS_CHAR_BLOCK)))
                                        continue;

                                //npc = new( file[ random( caster < 20 ? size2 : size3 ) ] );
                                npc = new (file[random(size2)]);

                                npc->add_to_scene(z, p / 1000, p % 1000, 3);
                                map->add_fighter(npc);
                                npc->set_start_place(sprintf("%d", p));
                                npc->set("I_need_reflash", 1);
                                if (npc->is_caster())
                                {
                                        map->add_caster(npc);
                                        caster++;
                                }
                        }
                }
                //map->set_add_amount( range_value( map->get_fighter_amount() - map->sizeof_fighter_dbase(), 0, MAX_NUMBER ) );
                map->set_add_amount(0);
        }
}
// 函数：刷出 BOSS 对象
void clone_boss(object map)
{
        object npc;
        string *file;
        int total;
        int z, p, size, size2, time, time2, count;
        int level;
        mixed local;

        reset_eval_cost();
        time = map->get_reset_time();
        if (map->sizeof_boss_file() == 0)
                return;
        level = map->get("boss_level");
        if (level == 0)
        {
                file = map->get_boss_file();
                npc = new (file[0]);
                level = npc->get_level();
                map->set("boss_level", level);
                destruct(npc);
        }
        local = localtime(time());
        time = map->get("reset_hour");
        time2 = local[LT_HOUR];
        if (level <= 50)
                count = 4;
        else if (level <= 80)
                count = 6;
        else
                count = 8;
        count = 1;
        //	if ( (time2+21)%count==0)
        {
                if (time == time2 + 21)
                        return;
                map->set("reset_hour", time2 + 21);
        }
        if (map->sizeof_boss_file() > 0)
        {
                total = map->sizeof_boss_dbase();
                file = map->get_boss_file();
                size2 = sizeof(file);
                z = map->get_id();

                for (size = 1; total < size; total++) // 只出现一个boss
                {
                        if (!(p = get_xy_point(z, IS_CHAR_BLOCK)))
                                continue;

                        npc = new (file[random(size2)]);

                        npc->add_to_scene(z, p / 1000, p % 1000, 3);
                        map->add_boss(npc);
                        npc->set_start_place(sprintf("%d", p));
                }
        }
}

// 函数：刷出 Fish 对象
void clone_fish(object map, string city)
{
        object *char, npc;
        string name;
        int p, total;

        return; // ############################################

        reset_eval_cost();

        if (city->get_2("fish") && city->get_2("fish.total") < city->get_2("fish.kill") * 2)
                city->add_fishculture(-1);

        if (!arrayp(char = map->get_2("fish")))
        {
                char = ({});
                total = 0;
        }
        else
        {
                char -= ({0});
                total = sizeof(char);
        }

        for (; total < 10; total++)
        {
                if (!(p = QUEST_FISHER->get_fisher_xy(IS_CHAR_BLOCK - 1)))
                        continue; // 鱼在水里(永久阻挡)

                npc = new ("/npc/std/9220");
                npc->add_to_scene(p / 1000000, (p % 1000000) / 1000, p % 1000, 3);
                char += ({npc});
        }

        if (sizeof(char))
        {
                total = city->get_fishculture() / 50;
                city->set_2("fish.total", total);
                city->set_2("fish.kill", 0);
                name = city->get_name();
                char->set_city_name(name);
                char->set("fish", total / 10);
        }

        map->set_2("fish", char);
}

//场景生成怪物宝宝
void generate_baobao(object map)
{
        int i, size, p;
        string *nTmp, file;
        object baobao;

        if (map->get("baobao"))
                return;
        i = map->get("baobao_time");
        if (i == 99)
        {
                map->set("baobao_time", time());
                return;
        }
        if (gone_time(i) < 3600)
                return;
        if (!(p = get_xy_point(map->get_id(), IS_CHAR_BLOCK)))
                return;
        nTmp = map->get_fighter_file();
        if (!(size = sizeof(nTmp)))
                return;
        file = nTmp[random(sizeof(nTmp))];
        baobao = new (file);
        if (!baobao)
                return;
        baobao->set("is_baobao", 1);
        baobao->add_to_scene(map->get_id(), p / 1000, p % 1000);
        map->set("baobao_time", 99);
        map->set("baobao", baobao);
        //log_file("scene_baobao",sprintf("%s %d %d %d\n",short_time(),map->get_id(),p/1000,p%1000));
}