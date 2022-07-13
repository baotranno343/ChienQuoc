#include <npc.h>
#include <skill.h>
#include <item.h>
#include <action.h>
#include <effect.h>
#include <equip.h>
#include <cmd.h>

class Health
{
        int Point;    // 当前数值
        int MaxPoint; // 最大数值
}

private class Health HP = new (class Health); // 生命点数("hp", "hp%")
private
class Health MP = new (class Health); // 法力点数("mp", "mp%")

private
static int HP_Cent; // 气血比例(注意：0/50～50/50)

private
int AP0, AP; // 物理攻击("ap", "ap%")
private
int DP0, DP; // 物理防御("dp")
private
int CP0, CP; // 法术攻击("cp", "cp%")
private
int PP0, PP; // 法术防御("pp", "pp%")
private
int SP; // 腾挪躲闪("sp")

private
int MaxYuan = 1, Yuan = 1; // 元气点数

private
int DamageCount; // 累积伤害  // 护体金罡－集气

private
int Poison; // 中毒点数
private
int Poison2; // 中毒点数(暗器)

private
int Die; // 死亡标志

int get_login_flag();
int get_skill(int skill);

// -------------------------------------------------------------

// 函数：获取当前ＨＰ
int get_hp() { return HP->Point; }

// 函数：获取当前ＭＰ
int get_mp() { return MP->Point; }

// 函数：获取最大ＨＰ
int get_max_hp() { return HP->MaxPoint; }

// 函数：获取最大ＭＰ
int get_max_mp() { return MP->MaxPoint; }

// 函数：获取气血比例
int get_hp_cent() { return HP_Cent; }

// 函数：设置当前ＨＰ
int set_hp(int point)
{
        object me = this_object();
        object *team;
        int i, size;
        int old_hp_cent = HP_Cent;
        if (get_login_flag() == 2)
                return HP->Point; // 未准备就绪
        point = range_value(point, -1, HP->MaxPoint);
        if (point < 1 && get_effect(me, EFFECT_CHAR_IMMORTAL))
                point = 1;
        if (HP->Point != point && get_login_flag() > 1)
                send_user(me, "%c%c%w", 0x3d, 20, point);
        HP_Cent = (point < 1 || HP->MaxPoint < 1) ? 0 : point * 50 / HP->MaxPoint;
        if (old_hp_cent != HP_Cent && get_login_flag() > 1)
        {
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%c", 0x2a, getoid(me), HP_Cent);
        }
        HP->Point = point;
        if (me->get_leader())
        {
                team = me->get_team();
                size = sizeof(team);
                if (size > 0)
                {
                        for (i = 0; i < size; i++)
                        {
                                if (team[i])
                                        send_user(team[i], "%c%c%d%w%w", 0x54, 3, me->get_number(), me->get_hp(), me->get_max_hp());
                        }
                }
        }
        return HP->Point;
}

// 函数：设置当前ＭＰ
int set_mp(int point)
{
        object me = this_object();
        object *team;
        int i, size;
        if (get_login_flag() == 2)
                return MP->Point; // 未准备就绪
        point = range_value(point, 0, MP->MaxPoint);
        if (MP->Point != point && get_login_flag() > 1)
                send_user(me, "%c%c%w", 0x3d, 22, point);
        MP->Point = point;
        if (me->get_leader())
        {
                team = me->get_team();
                size = sizeof(team);
                if (size > 0)
                {
                        for (i = 0; i < size; i++)
                        {
                                if (team[i])
                                        send_user(team[i], "%c%c%d%w%w", 0x54, 4, me->get_number(), me->get_mp(), me->get_max_mp());
                        }
                }
        }
        return MP->Point;
}

// 函数：设置最大ＨＰ
int set_max_hp(int point)
{
        object me = this_object();
        int old_hp_cent = HP_Cent;
        point = range_value(point, 1, MAX_NUMBER);
        if (point < HP->Point)
                HP->Point = point;
        if (HP->MaxPoint != point && get_login_flag() > 1)
                send_user(me, "%c%c%w", 0x3d, 21, point);
        HP_Cent = (HP->Point < 1) ? 0 : HP->Point * 50 / point;
        if (old_hp_cent != HP_Cent && get_login_flag() > 1)
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%c", 0x2a, getoid(me), HP_Cent);
        return HP->MaxPoint = point;
}

// 函数：设置最大ＭＰ
int set_max_mp(int point)
{
        object me = this_object();
        point = range_value(point, 1, MAX_NUMBER);
        if (point < MP->Point)
                MP->Point = point;
        if (MP->MaxPoint != point && get_login_flag() > 1)
                send_user(me, "%c%c%w", 0x3d, 23, point);
        return MP->MaxPoint = point;
}

// 函数：增添当前ＨＰ
int add_hp(int point)
{
        object me = this_object();
        if (me->get_save("no_hurt"))
        {
                if (point < 0)
                        return get_hp();
        }
        if (point < 0)
                "/quest/help"->send_help_tips(me, 47);
        if (me->get_perform("03191"))
        {

                USER_ENERGY_D->count_ap(me);
        }
        return set_hp(HP->Point + point);
}

// 函数：增添当前ＭＰ
int add_mp(int point)
{
        object me = this_object();
        if (get_effect_3(me, EFFECT_DOUBLE_USE) && point < 0)
                point *= 2;
        return set_mp(MP->Point + point);
}

// 函数：增添最大ＨＰ
int add_max_hp(int point) { return set_max_hp(HP->MaxPoint + point); }

// 函数：增添最大ＭＰ
int add_max_mp(int point) { return set_max_mp(MP->MaxPoint + point); }

// -------------------------------------------------------------
// 函数：获取物理攻击(基值)
int get_ap_0() { return range_value(AP - 35, 10, AP); }

// 函数：获取物理防御(基值)
int get_dp_0() { return range_value(DP - 35, 10, DP); }

// 函数：获取法术攻击(基值)
int get_cp_0() { return range_value(CP - 35, 5, CP); }

// 函数：获取法术防御(基值)
int get_pp_0() { return range_value(PP - 35, 8, PP); }
/*
// 函数：获取物理攻击(基值)
int get_ap_0() { return AP0; }

// 函数：获取物理防御(基值)
int get_dp_0() { return DP0; }

// 函数：获取法术攻击(基值)
int get_cp_0() { return CP0; }

// 函数：获取法术防御(基值)
int get_pp_0() { return PP0; }

// 函数：设置物理攻击(基值)
int set_ap_0( int point ) { return AP0 = range_value(point, 0, AP); }

// 函数：设置物理防御(基值)
int set_dp_0( int point ) { return DP0 = range_value(point, 0, DP); }

// 函数：设置法术攻击(基值)
int set_cp_0( int point ) { return CP0 = range_value(point, 0, CP); }

// 函数：设置法术防御(基值)
int set_pp_0( int point ) { return PP0 = range_value(point, 0, PP); }
*/
// 函数：获取物理攻击
int get_ap() { return AP; }

// 函数：获取物理防御
int get_dp() { return DP; }

// 函数：获取法术攻击
int get_cp() { return CP; }

// 函数：获取法术防御
int get_pp() { return PP; }

// 函数：获取腾挪躲闪
int get_sp()
{
        object who = this_object();
        if (get_effect(who, EFFECT_MAGIC_4243))
                return SP * 3; // 变身状态下临时增加2倍躲闪
        return SP;
}

// 函数：设置物理攻击
int set_ap(int point)
{
        object me = this_object();
        if (point < 1)
                point = 1;
        else if (point > 555555)
                point = 555555;
        if (AP != point && get_login_flag() > 1)
        {
                AP = point;
                send_user(me, "%c%c%w%w", 0x3d, 24, get_ap_0(), point);
                send_user(me, "%c%c%s", 0x3d, 35, USER_RANK_D->get_rank(me));
                me->delete_title("X");
                me->add_title("X");
                return point;
        }
        return AP = point;
}

int set_ap_dhn(int point)
{
        object me = this_object();
        if (point < 1)
                point = 1;
        else if (point > 555555)
                point = 555555;
        if (AP != point && get_login_flag() > 1)
        {
                AP = point;
                send_user(me, "%c%c%w%w", 0x3d, 24, get_ap_0(), point);
                return point;
        }
        return AP = point;
}

// 函数：设置物理防御
int set_dp(int point)
{
        object me = this_object();
        if (point < 10)
                point = 10;
        else if (point > 23000)
                point = 23000;
        if (DP != point && get_login_flag() > 1)
        {
                DP = point;
                send_user(me, "%c%c%w%w", 0x3d, 25, get_dp_0(), point);
                return point;
        }
        return DP = point;
}

// 函数：设置法术攻击
int set_cp(int point)
{
        object me = this_object();
        if (point < 5)
                point = 5;
        else if (point > 555555)
                point = 555555;
        if (CP != point && get_login_flag() > 1)
        {
                CP = point;
                send_user(me, "%c%c%w%w", 0x3d, 26, get_cp_0(), point);
                send_user(me, "%c%c%s", 0x3d, 35, USER_RANK_D->get_rank(me));
                me->delete_title("X");
                me->add_title("X");
                return point;
        }
        return CP = point;
}

// 函数：设置法术防御
int set_pp(int point)
{
        object me = this_object();
        if (point < 8)
                point = 8;
        else if (point > 30500)
                point = 30500;
        if (PP != point && get_login_flag() > 1)
        {
                PP = point;
                send_user(me, "%c%c%w%w", 0x3d, 27, get_pp_0(), point);
                return point;
        }
        return PP = point;
}

// 函数：设置腾挪躲闪
int set_sp(int point)
{
        object me = this_object();
        if (point < 1)
                point = 1;
        else if (point > 200000)
                point = 200000;
        if (SP != point && get_login_flag() > 1)
                send_user(me, "%c%c%w", 0x3d, 28, point);
        return SP = point;
}

// 函数：增添物理攻击
int add_ap(int point) { return set_ap(AP + point); }

// 函数：增添物理防御
int add_dp(int point) { return set_dp(DP + point); }

// 函数：增添法术攻击
int add_cp(int point) { return set_cp(CP + point); }

// 函数：增添法术防御
int add_pp(int point) { return set_pp(PP + point); }

// 函数：增添腾挪躲闪
int add_sp(int point) { return set_sp(SP + point); }

// -------------------------------------------------------------

// 函数：获取当前元气
int get_yuan() { return Yuan; }

// 函数：获取最大元气
int get_max_yuan() { return MaxYuan; }

// 函数：设置当前元气
int set_yuan(int point)
{
        point = range_value(point, 0, MaxYuan);
        if (Yuan != point && get_login_flag() > 1)
                send_user(this_object(), "%c%c%c", 0x3d, 30, point);
        return Yuan = point;
}

// 函数：设置最大元气
int set_max_yuan(int point)
{
        point = range_value(point, 1, MAX_NUMBER);
        if (point < Yuan)
                Yuan = point;
        if (MaxYuan != point && get_login_flag() > 1)
                send_user(this_object(), "%c%c%c", 0x3d, 31, point);
        return MaxYuan = point;
}

// 函数：增添当前元气
int add_yuan(int point)
{
        object me = this_object();
        if (get_effect_3(me, EFFECT_DOUBLE_USE) && point < 0)
                point *= 2;
        return set_yuan(Yuan + point);
}

// 函数：增添最大元气
int add_max_yuan(int point) { return set_max_yuan(MaxYuan + point); }

// -------------------------------------------------------------

// 函数：获取累积伤害
int get_damage_count() { return DamageCount; }

// 函数：设置累积伤害
int set_damage_count(int point) { return DamageCount = range_value(point, 1, MAX_NUMBER); }

// 函数：增添累积伤害
int add_damage_count(int point) { return set_damage_count(DamageCount + point); }

// 函数：获取中毒点数
int get_poison() { return Poison; }

// 函数：获取中毒点数(暗器)
int get_poison_2() { return Poison2; }

// 函数：设置中毒点数
int set_poison(int point) { return Poison = range_value(point, 1, MAX_NUMBER); }

// 函数：设置中毒点数(暗器)
int set_poison_2(int point) { return Poison2 = range_value(point, 1, MAX_NUMBER); }

// 函数：增添中毒点数
int add_poison(int point) { return set_poison(Poison + point); }

// 函数：增添中毒点数(暗器)
int add_poison_2(int point) { return set_poison_2(Poison2 + point); }

// -------------------------------------------------------------

// 函数：获取死亡标志
int is_die() { return Die; }

// 函数：设置死亡标志
// 参数：0 复活；1 死亡；2 有人解救；9 战场死亡
int set_die(int flag)
{
        object *char, me, who, *inv, *trangbi, item, owner;
        int z, x, y, x1, y1, p;
        int pk, i, k, n, size, size2, o, rate, j, rd_item;

        me = this_object();
        "/quest/help"->send_help_tips(me, 13);
        if (me->get_perform("05016#"))
        {
                me->set_perform("05016#", 0);
                me->set_perform("05016", 0);
                send_user(me, "%c%w%w%c", 0x81, 5016, 0, EFFECT_GOOD);
                send_user(get_scene_object_2(me, USER_TYPE) - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 5016, 0, EFFECT_GOOD);
                USER_ENERGY_D->count_cp(me);
        }
        switch (flag)
        {
        case 1: // 正常死亡状态

                pk = me->get_pk();
                z = get_z(me);
                x = get_x(me);
                y = get_y(me);

                //   if( pk < 100 ) k = random(3) + 1;
                //  else k = pk * ( random(4) + 2 );
                if (pk < 500)
                        k = 0;
                else
                        k = pk;

                rate = random(10);
                if (k > 0)
                        for (i = 0; i < 1; i++)
                        {
                                if (rate < 1)
                                {
                                        me->drop_equip(WEAPON_TYPE);
                                }
                                else if (rate < 2)
                                {
                                        me->drop_equip(ARMOR_TYPE);
                                }
                                else if (rate < 3)
                                {
                                        me->drop_equip(HEAD_TYPE);
                                }
                                else if (rate < 4)
                                {

                                        me->drop_equip(NECK_TYPE);
                                }
                                else if (rate < 5)
                                {

                                        me->drop_equip(WAIST_TYPE);
                                }
                                else if (rate < 6)
                                {
                                        me->drop_equip(BOOTS_TYPE);
                                }

                                // else if (rate < 15)
                                // {
                                //         me->drop_equip(BACK_TYPE);
                                // }
                                inv = all_inventory(me, 1, MAX_CARRY * 4);
                                if (!(size = sizeof(inv)))
                                        break;
                                if (!(p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_ITEM_BLOCK)))
                                        continue;
                                {

                                        x1 = p / 1000;
                                        y1 = p % 1000;

                                        n = random(size);
                                        j = inv[n]->get_equip_type();
                                        if (inv[n]->get_no_drop() || inv[n]->get_no_get() || inv[n]->get_no_give())
                                                continue;
                                        if (!inv[n]->is_equip() ||
                                            (j != WEAPON_TYPE && j != ARMOR_TYPE && j != HEAD_TYPE &&
                                             j != BOOTS_TYPE && j != WAIST_TYPE && j != NECK_TYPE))
                                                continue;
                                        inv[n]->set_bind(5);
                                        inv[n]->set_owner(0);
                                        inv[n]->remove_from_user();
                                        inv[n]->add_to_scene(z, x1, y1);
                                }
                        }
                /*	if ( pk >= 100 ) {
					//	me->add_cash(-me->get_cash());
					send_user( me, "%c%w%w%c", 0x81, 9150, 0, EFFECT_GOOD );
					send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9150, 0, EFFECT_GOOD );

					set_effect(me, EFFECT_CHAR_KING_2, 300 );
					send_user( me, "%c%w%w%c", 0x81, 9152, get_effect_3(me, EFFECT_CHAR_KING_2), EFFECT_BAD );
					send_user( get_scene_object_2(me, USER_TYPE) - ({ me }), "%c%d%w%c%c", 0x83, getoid(me), 9152, 1, EFFECT_BAD );

					USER_ENERGY_D->count_max_hp(me);
					USER_ENERGY_D->count_max_mp(me);
					USER_ENERGY_D->count_cp(me);
					USER_ENERGY_D->count_pp(me);
					USER_ENERGY_D->count_ap(me);
					USER_ENERGY_D->count_dp(me);
						tell_user(me, "Do ngươi giết người không gớm tay nên đã bị trừng phạt.");
						}

                    /*    p = random(1000);

                        if( pk < 100 )
                        {
                                if( p < 5 ) k = 2;
                                else if( p < 50 ) k = 1;
                                else k = 0;
                        }
                        else if( pk < 600 )
                        {
                                if( p < pk * 20 ) k = random(3) + 2;
                                else if( p < pk * 100 ) k = 1;
                                else k = 0;
                        }
                        else 
                        {
                                if( p < pk * 100 ) k = random(7) + 1;
                                else if( p < pk * 100 ) k = 1;
                                else k = 0;
                        }*/
                if (me->get_save("userkill") == 0)
                {
                        inv = me->get_all_equip(me); // 减少耐久度 10%
                        if (objectp(inv[0]))
                                inv[0]->add_lasting(-inv[0]->get_max_lasting() / 10);
                        if (objectp(inv[1]))
                                inv[1]->add_lasting(-inv[1]->get_max_lasting() / 10);
                        if (objectp(inv[2]))
                                inv[2]->add_lasting(-inv[2]->get_max_lasting() / 10);
                        if (objectp(inv[3]))
                                inv[3]->add_lasting(-inv[3]->get_max_lasting() / 10);
                        if (objectp(inv[4]))
                                inv[4]->add_lasting(-inv[4]->get_max_lasting() / 10);
                        if (objectp(inv[5]))
                                inv[5]->add_lasting(-inv[5]->get_max_lasting() / 10);
                        if (objectp(inv[6]) && inv[6]->get_item_type() == ITEM_TYPE_TALISMAN)
                        {
                                if (inv[6]->get_item_number() != 10001023 && inv[6]->get_item_number() != 10001024 && inv[6]->get_item_number() != 10001110 && inv[6]->get_item_number() != 10001109)
                                        inv[6]->add_lasting(-inv[6]->get_max_lasting() / 10);
                        }
                }

                if (objectp(who = me->get_quest("escort.robber#")) && who->is_escort_robber())
                {
                        who->win_bonus(me); // 清除蒙面人
                        who->remove_from_scene();
                        destruct(who);
                }

                me->set_cast_file(0); // 清除法术特技
                me->set_cast_arg("");

                char = get_scene_object_2(me, USER_TYPE);
                send_user(char, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END); // 结束施法动作
                send_user(char, "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me),
                          41100, 1, UNDER_FOOT, 42100, 1, UNDER_FOOT, PF_STOP); // 结束符法效果  get_cast_seal()

                me->set_perform_file(0); // 清除非法特技
                                         //                me->init_perform_dbase();    // 清除随机特技

                CHAR_CHAR_D->stop_loop_perform(me);   // 中断持续效果
                CHAR_CHAR_D->stop_loop_perform_4(me); // 中断持续效果(不良)
                CHAR_CHAR_D->stop_loop_perform_5(me); // 中断持续效果(神打)
                CHAR_CHAR_D->stop_loop_perform_9(me); // 中断持续效果(其它)
                CHAR_CHAR_D->stop_poison_effect(me);  // 中断毒药效果

                me->set_char_action(DIE_ACT);

                //                set_effect(me, EFFECT_USER_DIE, 600);
                send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%c", 0x3d, 2, getoid(me), flag);

                break;

        case 5: // 比武场、战场死亡状态

                me->set_cast_file(0); // 清除法术特技
                me->set_cast_arg("");

                char = get_scene_object_2(me, USER_TYPE);
                send_user(char, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END); // 结束施法动作
                send_user(char, "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me),
                          41100, 1, UNDER_FOOT, 42100, 1, UNDER_FOOT, PF_STOP); // 结束符法效果  get_cast_seal()

                me->set_perform_file(0); // 清除非法特技
                                         //                me->init_perform_dbase();    // 清除随机特技

                CHAR_CHAR_D->stop_loop_perform(me);   // 中断持续效果
                CHAR_CHAR_D->stop_loop_perform_4(me); // 中断持续效果(不良)
                CHAR_CHAR_D->stop_loop_perform_5(me); // 中断持续效果(神打)
                CHAR_CHAR_D->stop_loop_perform_9(me); // 中断持续效果(其它)
                CHAR_CHAR_D->stop_poison_effect(me);  // 中断毒药效果

                me->set_char_action(DIE_ACT);

                set_effect(me, EFFECT_USER_DIE_5, 3);
                send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%c", 0x3d, 2, getoid(me), flag);

                break;
        case 6: // PVP死亡

                me->set_cast_file(0); // 清除法术特技
                me->set_cast_arg("");

                char = get_scene_object_2(me, USER_TYPE);
                send_user(char, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END); // 结束施法动作
                send_user(char, "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me),
                          41100, 1, UNDER_FOOT, 42100, 1, UNDER_FOOT, PF_STOP); // 结束符法效果  get_cast_seal()

                me->set_perform_file(0); // 清除非法特技
                                         //                me->init_perform_dbase();    // 清除随机特技

                CHAR_CHAR_D->stop_loop_perform(me);   // 中断持续效果
                CHAR_CHAR_D->stop_loop_perform_4(me); // 中断持续效果(不良)
                CHAR_CHAR_D->stop_loop_perform_5(me); // 中断持续效果(神打)
                CHAR_CHAR_D->stop_loop_perform_9(me); // 中断持续效果(其它)
                CHAR_CHAR_D->stop_poison_effect(me);  // 中断毒药效果

                me->set_char_action(DIE_ACT);

                send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%c", 0x3d, 2, getoid(me), flag);

                break;
        case 9: // 战场死亡状态(回魂符)

                me->set_cast_file(0); // 清除法术特技
                me->set_cast_arg("");

                char = get_scene_object_2(me, USER_TYPE);
                send_user(char, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END); // 结束施法动作
                send_user(char, "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me),
                          41100, 1, UNDER_FOOT, 42100, 1, UNDER_FOOT, PF_STOP); // 结束符法效果  get_cast_seal()

                me->set_perform_file(0); // 清除非法特技
                                         //                me->init_perform_dbase();    // 清除随机特技

                CHAR_CHAR_D->stop_loop_perform(me);   // 中断持续效果
                CHAR_CHAR_D->stop_loop_perform_4(me); // 中断持续效果(不良)
                CHAR_CHAR_D->stop_loop_perform_5(me); // 中断持续效果(神打)
                CHAR_CHAR_D->stop_loop_perform_9(me); // 中断持续效果(其它)
                CHAR_CHAR_D->stop_poison_effect(me);  // 中断毒药效果

                me->set_char_action(DIE_ACT);

                set_effect(me, EFFECT_USER_DIE_9, 15);
                send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%c", 0x3d, 2, getoid(me), flag);

                break;
        case 10: // 战场死亡状态(回魂符)

                me->set_cast_file(0); // 清除法术特技
                me->set_cast_arg("");

                char = get_scene_object_2(me, USER_TYPE);
                send_user(char, "%c%d%d%c", 0x40, getoid(me), time2(), MAGIC_ACT_END); // 结束施法动作
                send_user(char, "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me),
                          41100, 1, UNDER_FOOT, 42100, 1, UNDER_FOOT, PF_STOP); // 结束符法效果  get_cast_seal()

                me->set_perform_file(0); // 清除非法特技
                                         //                me->init_perform_dbase();    // 清除随机特技

                CHAR_CHAR_D->stop_loop_perform(me);   // 中断持续效果
                CHAR_CHAR_D->stop_loop_perform_4(me); // 中断持续效果(不良)
                CHAR_CHAR_D->stop_loop_perform_5(me); // 中断持续效果(神打)
                CHAR_CHAR_D->stop_loop_perform_9(me); // 中断持续效果(其它)
                CHAR_CHAR_D->stop_poison_effect(me);  // 中断毒药效果

                me->set_char_action(DIE_ACT);

                set_effect(me, EFFECT_USER_DIE_9, 5);
                send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%c", 0x3d, 2, getoid(me), flag);

                break;

        case 0: // 非死亡状态

                me->set_char_action(DEFAULT_ACT);
                send_user(get_scene_object_2(me, USER_TYPE), "%c%c%d%c", 0x3d, 2, getoid(me), flag);

                break;
        }
        if (flag)
                me->save_limit_time();
        else
                me->restore_limit_time();

        return Die = flag;
}
