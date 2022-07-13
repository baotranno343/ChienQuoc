#include <npc.h>
#include <ansi.h>
#include <public.h>
#include <time.h>
#include <effect.h>
#include <city.h>
inherit OFFICER;
int host_type;
int open = 0;
//int *nxy = ({080034,087040,094046,101051,109057,116063,074040,081046,089051,097056,105062,111067,069046,077052,085056,092061,100067,107071,064051,072056,081061,087065,096071,0102075,059055,067060,075066,082070,091076,097079,054059,063066,071071,077075,084080,089085,048066,055071,062076,068081,074086,080091,});
// 函数:获取人物造型
int get_char_picid() { return 8102; }
int set_open(int i) { return open = i; }
int get_open() { return open; }
void do_visit(string arg);
void outlet(int sec, object map);
//int challenge(object player,object master);
// 函数:构造处理
void create()
{
    object me = this_object();
    set_name("Vạn Thần");
    set_2("talk", (["visit":(
                                : do_visit:),
    ]));
    setup();
    host_type = MAIN_D->get_host_type();
}

void do_look(object who) { __FILE__->do_look_call(this_object(), who); }

void do_look_call(object me, object who)
{
    int i, id, tId, size;
    object *team;
    string leader;
    id = getoid(me);
    tId = who->get_team_id();
    team = who->get_team();
    if (!who->get_team())
    {
        send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Khi nào có tổ đội thì đến tìm ta !\n" ESC "Rời khỏi");
        return;
    }
    if (get_open() == 1)
    {
        send_user(who, "%c%c%w%s", ':', 3, this_object()->get_char_picid(), sprintf("Vạn Thần:\n    Phó Bản Thế Giới, liệu ngươi có đủ sức để tham gia? \n" ESC "Tiến Vào \ntalk %x# visit.2\n" ESC "Rời khỏi", id));
    }
    else
    {
        send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Phó bản chưa được mở!\n" ESC "Rời khỏi");
        return;
    }
}

void do_visit(string arg)
{
    object me = this_object();
    __FILE__->do_visit2(me, arg);
}

void do_visit2(object me, string arg)
{
    int flag, i, p, z, x, y, id, size, tId, *nXy, level, count, exit, j = 0;
    object who, npc, *team, map, leader, convey;
    who = this_player();
    tId = who->get_team_id();
    flag = to_int(arg);

    who->set_time("talk", 0);
    id = getoid(me);

    switch (flag)
    {

    case 2:
        team = who->get_team();
        if (me->get("overdue"))
            return;

        if (me->get("busy"))
        {
            who->add_to_scene(2999, 64, 54); // Gốc sửa lại đúng vị trí khi vào map
            return;
        }

        me->set("busy", tId);

        level = 1;

        if ((z = find_map_flag(1000, 2999, 0)) > 0)
        {
            //				p = 885;
            p = 910; // gốc 910
            z = 2999;
            init_virtual_map(z, p); // 生成虚拟地图
                                    //			        map = new( NEWBIE );
            map = new ("/tran/phuban/map");
            map->set_client_id(p);
            set_map_object(map, map->set_id(z));
            //				for(i=0;i<sizeof(nxy);i++)
            for (i = 0; i < 1000; i++)
            {
                npc = new ("tran/phuban/creep");
                npc->set("team_id", tId);
                npc->set_level(level);
                npc->set_name("Âm Binh");
                npc->set_char_picid(1264);
                NPC_ENERGY_D->init_level(npc, level);

                // Tăng Chỉ Số Creep

                npc->add_dp(npc->get_dp());
                npc->add_max_hp(npc->get_max_hp());
                npc->add_sp(npc->get_sp());
                npc->add_ap(npc->get_ap());
                npc->add_mp(npc->get_mp());

                if (!(p = efun::get_xy_point(910, IS_CHAR_BLOCK))) // Gốc 910
                    continue;
                x = p / 1000;
                y = p % 1000;
                npc->add_to_scene(z, x, y);
                //npc->add_to_scene(z,nxy[i]/1000,nxy[i]%1000);
                count++;
            }
            convey = new ("tran/phuban/out");
            convey->add_to_scene(z, 54, 44); // Gốc sửa lại đúng vị trí của npc out map
            map->add("scene_npc_amount", count);
            map->set("copy_npc_amount", 2000); // Gốc 10000
            map->set("copy_level", level);
            //  me->set("id_pb", z);
        }
        for (i = 0; i < sizeof(team); i++)
        {

            if (!(p = efun::get_xy_point(910, IS_CHAR_BLOCK))) // Gốc 910
                continue;
            x = (p % 1000000) / 1000;
            y = p % 1000;

            team[i]->add_to_scene(map->get_id(), x, y);
        }
        map->set_owner(me);

        break;
    }
}

//传出场景z
void outlet(int sec, object map)
{
    int i, size, tId;
    object *member, npc;
    string id;
    sec = sec - 5;
    if (!map)
        return;
    member = "tran/phuban/map"->get_all_user(map);

    if (sec > 0)
    {
        for (i = 0, size = sizeof(member); i < size; i++)
        {
            tell_user(member[i], "Sau %d giây，tự động rời khỏi", sec);
        }

        call_out("outlet", 5, sec, map);
    }
    else
    {
        // npc = map->get_owner();
        // for (i = 0, size = sizeof(member); i < size; i++)
        // {
        //     member[i]->add_to_scene(get_z(npc), get_x(npc) + random(3), get_y(npc) + random(3));
        // }

        // npc->remove_from_scene();
        // destruct(npc);
        ///
        set_open(0);

        //member = map->get_all_user(map);
        map->destruct_virtual_map(map, map->get_id());
        for (i = 0, size = sizeof(member); i < size; i++)
        {
            member[i]->add_to_scene(80, 275, 185);
        }
    }
}

//死亡处理
void scum_die(object map, object who)
{
    object owner;
    owner = map->get_owner();
    who->add_to_scene(get_z(owner), get_x(owner) + random(3), get_y(owner) + random(3), 3);
    send_user(who, "%c%s", '!', "Ngươi bị Võ Lâm Bại Hoại đánh trọng thương");
}