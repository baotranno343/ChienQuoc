
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <ansi.h>
inherit BADMAN;
#define SCUM_NPC "tran/phuban/creep"
int *nxy = ({
    080034,
    087040,
    094046,
    101051,
    109057,
    116063,
    074040,
    081046,
    089051,
    097056,
    105062,
    111067,
    069046,
    077052,
    085056,
    092061,
    100067,
    107071,
    064051,
    072056,
    081061,
    087065,
    096071,
    0102075,
    059055,
    067060,
    075066,
    082070,
    091076,
    097079,
    054059,
    063066,
    071071,
    077075,
    084080,
    089085,
    048066,
    055071,
    062076,
    068081,
    074086,
    080091,
});

// 函数：跟随对手(心跳之中调用)
// void follow_user() { }    // 禁止跟随敌人
int generate_copy_npc(int tId, int z, int level);
void init_npc(object npc);
// 函数：获取人物造型
//int get_char_picid() { return 1001; }

// 函数：构造处理
void create()
{
    set_name("Võ Lâm Bại Hoại");

    set_char_type(FIGHTER_TYPE); // init_level 要用到

    set_head_color(0x0);

    //        NPC_ENERGY_D->init_level( this_object(), 22+ random(3) );    //
    set_max_seek(4);

    setup();
    set("anti_05311", 1);        //不能迷魂
    set_char_type(FIGHTER_TYPE); // 重设类型
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// 函数：特技攻击对手
int perform_action(object who) { return 0; } // XXXXX->perform_action_npc( this_object(), who ); }

// 函数：掉宝奖励
void drop_items(object who)
{

    __FILE__->drop_items_callout(this_object(), who);
}

// 函数：掉宝奖励(在线更新)
void drop_items_callout(object me, object who)
{
    object item, leader, map, *member, npc1;
    string file, owner, id;
    int p, rate, i, size, gold, equip, rate1, tId, level;
    int z, x, y;
    z = get_z(me);
    x = get_x(me);
    y = get_y(me);
    tId = me->get("team_id");

    map = get_map_object(get_z(me));
    if (!map)
        return;
    map->add("copy_npc_die", 1);
    z = map->get_id();
    member = "tran/phuban/map"->get_all_user(map);
    rate = random(100);

    //出现新的怪
    if (map->get("copy_npc_die") == map->get("scene_npc_amount") - 50 && map->get("scene_npc_amount") != map->get("copy_npc_amount")) // gốc -50
    {

        map->add("copy_level", 1);

        for (i = 0; i < sizeof(member); i++)
        {
            if (get_z(member[i]) != z)
                continue;
            send_user(member[i], "%c%c%s", 0xA5, 1, sprintf("| TẦNG %d - ĐỢT %d", map->get("copy_npc_amount") / 2000, map->get("copy_npc_die") / 200 + 2)); //Gốc 10000 Và 1000+2
        }

        generate_copy_npc(tId, map->get_id(), map->get("copy_level"));
    }
    //大BOSS出现
    if (!map->get("big_copy_boss") && (map->get("copy_npc_die") == map->get("copy_npc_amount")))
    {
        npc1 = new ("tran/phuban/boss");

        if (!npc1)
            return;
        level = map->get("copy_level");
        // if (level > 30)
        //     level = 30;
        NPC_ENERGY_D->init_level(npc1, level);
        init_npc(npc1);
        npc1->set_max_seek(8);
        npc1->set("team_id", tId);

        //		member = who->get_team();
        member -= ({0});
        size = sizeof(member);
        i = random(size);
        x = get_x(member[i]);
        y = get_y(member[i]);
        npc1->add_to_scene(z, x, y);
        for (i = 0; i < size; i++)
        {
            if (get_z(member[i]) != z)
                continue;
            send_user(member[i], "%c%s", ';', sprintf(HIY "BOSS %d Đã Xuât Hiện", map->get("copy_npc_amount") / 2000)); //gốc 10000
        }
    }
}

int can_fight(object who)
{
    if (!get_map_object(get_z(who))->is_scum_map())
        return 0;
    return 1;
}

//生成一只怪
int generate_copy_npc(int tId, int z, int level)
{
    int i, size, iShape, *nShape, rand, iLev, p, x, y, iAtt, iCast;
    object npc, map, *nObj = ({});
    string name, *attrib, *nKind;
    mapping mpTmp;

    if (!objectp(map = get_map_object(z)) || !map->is_virtual_scene())
        return 0;
    for (i = 0; i < 200; i++) //Gốc 1000
    {
        npc = new (SCUM_NPC);
        npc->set("team_id", tId);
        npc->set_level(level);
        if (level < 51)
        {
            npc->set_name("Âm Binh");
            npc->set_char_picid(1264);
        }
        else if (level < 101)
        {
            npc->set_name("Thiên Tà");
            npc->set_char_picid(1280);
        }

        NPC_ENERGY_D->init_level(npc, level);
        // Tăng Chỉ Số Creep

        npc->add_dp(npc->get_dp() * 2);
        npc->add_max_hp(npc->get_max_hp() * 2);
        npc->add_sp(npc->get_sp() * 2);
        npc->add_ap(npc->get_ap() * 2);
        npc->add_mp(npc->get_mp() * 2);
        if (!(p = efun::get_xy_point(910, IS_CHAR_BLOCK))) // gốc 910
            return 0;
        x = (p % 1000000) / 1000;
        y = p % 1000;
        npc->add_to_scene(z, x, y);
    }
    //	npc->add_to_scene(z,nxy[random(sizeof(nxy))]/1000,nxy[random(sizeof(nxy))]%1000);
    //	npc->add_to_scene(z,80,60);

    map->add("scene_npc_amount", 200); // Gốc 1000
    return 1;
}

//大BOSS
void init_npc(object npc)
{
    int p, level;

    level = npc->get_level();
    // p = random(100);
    if (level == 10 || level == 20) //低物防高敏型
    {
        npc->set_skill(348, level);
        npc->set_skill(251, level);
        npc->set_skill(241, level);
        npc->set_name("Thập Phá Thiên Đầu Lĩnh");
        npc->set_char_picid(1264);
        npc->set_walk_speed(3);
        npc->set_attack_speed(10);

        npc->set("scum.type", 1);
    }
    else if (level == 30 || level == 40) //高物防低法防型
    {
        npc->set_skill(221, level);
        npc->set_skill(231, level);
        npc->set_name("Nhị Thập Phá Thiên Đầu Lĩnh");
        npc->set_char_picid(1280);
        npc->set_walk_speed(3);
        npc->set_attack_speed(10);

        npc->set("scum.type", 2);
    }
    else if (level == 50 || level == 60) //高法防低物防型
    {
        npc->set_skill(423, level);
        npc->set_skill(424, level);
        npc->set_skill(425, level);
        npc->set_name("Tam Thập Phá Thiên Đầu Lĩnh");
        npc->set_char_picid(1284);
        npc->set_walk_speed(3);
        npc->set_attack_speed(10);

        npc->set("scum.type", 3);
    }
    else if (level == 70 || level == 80) //长血型：拳脚类
    {
        npc->set_skill(211, level);
        npc->set_skill(317, level);
        npc->set_name("Tứ Thập Phá Thiên Đầu Lĩnh");
        npc->set_char_picid(1286);
        npc->set_walk_speed(3);
        npc->set_attack_speed(10);

        npc->set("scum.type", 4);
    }
    else if (level == 90 || level == 100) //长血高物防高法防型：远程暗器类
    {
        npc->set_skill(261, level);
        npc->set_name("Ngũ Thập Phá Thiên Đầu Lĩnh");
        npc->set_char_picid(1238);
        npc->set_walk_speed(3);
        npc->set_attack_speed(10);

        npc->set("scum.type", 5);
    }
    else //强攻型加召唤
    {
        npc->set_skill(414, level);
        npc->set_name("Vô Danh Tiểu Tốt");
        npc->set_char_picid(8013);
        npc->set_walk_speed(3);
        npc->set_attack_speed(8);
        npc->set("scum.type", 6);
    }
    npc->set_max_hp(1000000 * level / 8);
    npc->set_max_mp(1000000 * level / 10);
    npc->set_double_rate(1000 * level / 10);
    npc->set_ap(1000 * level / 10);
    npc->set_cp(1000 * level / 10);
    npc->set_dp(1000 * level / 10);
    npc->set_pp(1000 * level / 10);
    npc->set_sp(1000 * level / 10);
}
