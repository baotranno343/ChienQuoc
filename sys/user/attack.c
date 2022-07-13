
#include <equip.h>
#include <skill.h>
#include <effect.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：特技攻击对手
int perform_action(object me, object who)
{
        string file;

        if (stringp(file = me->get_perform_file()) && load_object(file) && file->perform_action(me, who) == 2) // 有特技出招
                return 1;

        // 自动法术
        if (me->get_attack_move())
        {
                switch (me->get_fam_name())
                {
                case "Vân Mộng Cốc":
                case "Mao Sơn":
                case "Côn Luân":
                case "Thục Sơn":
                        if ("/skill/02/02810"->perform_action(me, who) == 2)
                                return 1;
                        break;
                case "Đường Môn":
                default:
                        if ("/skill/02/02611"->perform_action(me, who) == 2)
                        {
                                return 1;
                        }
                        break;
                }
        }
        me->set_perform_file(0); // 重要：清除非法特技
        switch (me->get_weapon_code())
        {
        case BLADE:
                if (me->get_perform(PF_FLAG_02214))
                {
                        if (PF_FILE_02214->perform_action(me, who) == 2)
                                return 1;
                }
                break;
        case STICK:
                if (me->get_perform(PF_FLAG_02514))
                {
                        if (PF_FILE_02514->perform_action(me, who) == 2)
                                return 1;
                }
                break;
        }

        return 0;
}

// 函数：判断可以战斗
int can_fight(object me, object who)
{
        object owner, map;
        string name1, name2;
        int z, z1;
        if (me->is_die() || me->is_store_open())
                return 0;
        if (is_gm(me))
                return 0;
        //    if( me->get_no_fight() && !who->cannot_enter_city() ) return 0;    // 在安全区，且NPC 能进城(使玩家能打本不应进城的怪)
        if (me->get_no_fight())
                return 0; // 在安全区不能打安全区以外的

        if (me == who)
                return 0; // 禁止攻击自己
        if (get_effect(me, EFFECT_MAGIC_4243))
                return 0;
        z1 = get_z(me);
        map = get_map_object(z1);
        if (!map)
                return 0; // 如果地图出错的话
        if (get_z(me) == 704)
                return 0;
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
                return 0;
        /*	if ( map->is_pvp() )	//pvp地图
        {
                if( objectp( owner = who->get_owner() ) ) who = owner;
                if (who==me) return 0;
                if ( who->is_user() )
                {
                        if ( (z=who->get_team_id()) && z == me->get_team_id()  )	//队伍保护
                                return 0;
                        if ( (z=who->get_group_id()) && z == me->get_group_id()  )	//队伍保护
                                return 0;
                }
                return 1;
        }*/
        if (map->is_wushuang() || map->is_wushuang_palace()) //无双城
        {
                if (objectp(owner = who->get_owner()))
                        who = owner;
                if (who->is_user())
                {
                        if (sizeof(name1 = me->get_org_name()) &&
                            sizeof(name2 = who->get_org_name()) &&
                            name1 == name2) //帮派保护
                                return 0;
                }
                return 1;
        }
        if (map->is_changping()) //长平之战
        {
                if (objectp(owner = who->get_owner()))
                        who = owner;
                if (who->is_user())
                {
                        if ((z = who->get_2("changping.warid")) && z != me->get_2("changping.warid")) //战场ID
                                return 0;
                        if (who->get_2("changping.country") == me->get_2("changping.country")) //国家
                                return 0;
                }
                return 1;
        }
        if (MAP_D->is_inside_battle(z1))
        {
                if (me->get_manager() == who->get_manager())
                        return 0; // 禁止攻击帮众    // get_org_name() 是字串运算

                return 1;
        }
        else
        {
                z = get_z(who);
                if (objectp(owner = who->get_owner()))
                        who = owner;
                if (who == me)
                        return 0;
                if (map->get_no_fight() && who->is_user())
                        return 0;
                if (map->is_virtual_scene() && (me->get("no_fight") || who->get("no_fight")))
                        return 0;
                if (map->is_virtual_scene() && map->get_forbbit())
                        return 0;
                if (map->is_virtual_scene() == 2)
                        return 1;
                if (who->is_user() // 队友保护：攻击ＮＰＣ及非队友玩家
                    && ((name1 = me->get_leader()) && (name2 = who->get_leader()) && name1 != "" && name1 != 0 && name1 == name2))
                        return 0;
                if (is_gm3(me))
                        return 1;
                if (map->get_client_id() == 885)
                        return 1;
                //                if(     who->is_user() && who->get_attack_mode()!=3 ) return 0;
                //		if(     who->is_user()    // 同城保护：攻击ＮＰＣ及非本城玩家
                //                        &&  ( ( name1 = me->get_city_name() ) && ( name2 = who->get_city_name() )
                //                        &&  name1!="" &&   name1 == name2 ) ) return 0;
                //               	if (who->is_user() && abs(me->get_level()-who->get_level())>20) return 0;
                if (who->is_user() && (who->get_level() < 40 || me->get_level() < 40) &&
                    ((me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1) ||
                     (who->get_save("passhanhtrang") && who->get_save("ndmkhtk") < 1)) &&
                    ((who->get_attack_mode() != 0 || who->get_attack_mode() != 2 || who->get_attack_mode() != 3) || (me->get_attack_mode() != 0 || me->get_attack_mode() != 2 || me->get_attack_mode() != 3)))
                        return 0;
                switch (me->get_attack_mode())
                {
                case 0:
                        if (who->is_user() && who->get_level() < 40 || (who->get_save("passhanhtrang") && who->get_save("ndmkhtk") < 1))
                                return 0;
                        break;
                        // 		{

                        //   		}
                        //   		return 1;  break;    // 无限制攻击：攻击ＮＰＣ及所有玩家

                default:
                        if (who->is_user() /*&& who->get_attack_mode() == 0*/)
                                return 0;
                        break; // 玩家保护：仅攻击ＮＰＣ

                case 2:
                        if (who->is_user() // 伏击模式，攻击无限制攻击的人
                            && (who->get_level() < 40 || (me->get_org_name() == who->get_org_name()) || (who->get_save("passhanhtrang") && who->get_save("ndmkhtk") < 1)))
                                return 0;
                        break;
                case 3:
                        if (who->is_user() // 伏击模式，攻击无限制攻击的人
                            && (who->get_level() < 40 || (me->get_city_name() == who->get_city_name()) || (who->get_save("passhanhtrang") && who->get_save("ndmkhtk") < 1)))
                                return 0;
                        break;
                        //
                }

                return 1;
        }
}

// 函数：可以接受战斗
int can_be_fighted(object me, object who)
{
        if (me->is_die() || me->is_store_open() || me->get_no_fight() || get_z(me) == 704)
                return 0;
        if (is_gm3(me))
                return 1;
        if (is_gm(me))
                return 0;
        return 1;
}

// 判断法术是否可用
int can_use_help(object me, object who)
{
        object owner, map;
        string name1, name2;
        int z;
        map = get_map_object(get_z(me));
        if (!map)
                return 1; // 如果地图出错的话
        if (me->is_die() || me->is_store_open())
                return 1;
        if (is_gm(me))
                return 1;
        if (!who)
                return 0;

        if (who->can_be_fighted(me) && me->can_fight(who))
                return 0;
        z = get_z(who);
        if (objectp(owner = who->get_owner()))
                who = owner;
        if (who == me)
                return 1;
        if (MAP_D->is_inside_battle(get_z(me)))
        {
                if (me->get_manager() == who->get_manager())
                        return 1; // 禁止攻击帮众    // get_org_name() 是字串运算
                return 0;
        }
        if (map->is_changping())
        {
                if (me->get_2("changping.country") && who->get_2("changping.country") &&
                    me->get_2("changping.country") == who->get_2("changping.country"))
                        return 1;
                return 0;
        }
        if (z == 885)
        {
                if (who->is_user() // 队友保护：攻击ＮＰＣ及非队友玩家
                    && ((name1 = me->get_leader()) && (name2 = who->get_leader()) && name1 != "" && name1 == name2))
                        return 1;
                return 0;
        }
        if (who->get_attack_mode() == 0)
        {
                if (me->get_attack_mode() != 0)
                        return 0;
        }
        return 1;
}