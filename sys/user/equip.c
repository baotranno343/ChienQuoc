
#include <item.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

varargs void count_equip_apply(object me, object equip, object equip2);

// 函数：设置装备对象
int use_equip(object me, object equip)
{
        object item, file;
        int index, id, d, x, y, z, level, flag, type;
        int iSuit;

        if (!equip || !(index = equip->get_equip_type()) || index == FAMILY_TYPE)
                return 0;
        if (equip->get_lasting() < 100 && equip->get_max_lasting() > 100)
                return 0;

        if (me->get_equip(index) == equip)
                return 0; // 重复装备物品

        if (flag = equip->get_gender())
        {
                if (flag != me->get_gender())
                {
                        send_user(me, "%c%s", '!', sprintf("%s là trang bị %s", equip->get_name(), flag == 1 ? "Nam" : "Nữ"));
                        return 0;
                }
        }
        flag = equip->get_family();
        if (flag == 8)
                flag = 0;
        if (flag)
        {
                switch (index)
                {
                default:
                        switch (me->get_fam_name())
                        {
                        default:
                                if (flag != 8)
                                        flag = -1;
                                break;
                        case "Đào Hoa Nguyên":
                                if (flag != 1)
                                        flag = -1;
                                break;
                        case "Thục Sơn":
                                if (flag != 2 && flag != 9)
                                        flag = -1;
                                break;
                        case "Cấm Vệ Quân":
                                if (flag != 3)
                                        flag = -1;
                                break;
                        case "Đường Môn":
                                if (flag != 4)
                                        flag = -1;
                                break;
                        case "Mao Sơn":
                                if (flag != 5 && flag != 9)
                                        flag = -1;
                                break;
                        case "Côn Luân":
                                if (flag != 6 && flag != 9)
                                        flag = -1;
                                break;
                        case "Vân Mộng Cốc":
                                if (flag != 7 && flag != 9)
                                        flag = -1;
                                break;
                        }
                        break;

                case WEAPON_TYPE:
                        switch (me->get_fam_name())
                        {
                        default:
                                if (flag != 8)
                                        flag = -1;
                                break;
                        case "Đào Hoa Nguyên":
                                if (flag != 1)
                                        flag = -1;
                                break;
                        case "Thục Sơn":
                                if (flag != 2 && flag != 9)
                                        flag = -1;
                                break;
                        case "Cấm Vệ Quân":
                                if (flag != 3)
                                        flag = -1;
                                break;
                        case "Đường Môn":
                                if (flag != 4)
                                        flag = -1;
                                break;
                        case "Mao Sơn":
                                if (flag != 5 && flag != 9)
                                        flag = -1;
                                break;
                        case "Côn Luân":
                                if (flag != 6 && flag != 9)
                                        flag = -1;
                                break;
                        case "Vân Mộng Cốc":
                                if (flag != 7 && flag != 9)
                                        flag = -1;
                                break;
                        }
                        break;

                case HAND_TYPE:
                        switch (me->get_fam_name())
                        {
                        default:
                                flag = -1;
                                break;
                        case "Vân Mộng Cốc":
                                if (flag != 7)
                                        flag = -1;
                                break;
                        case "Côn Luân":
                                if (flag != 6)
                                        flag = -1;
                                break;
                        case "Mao Sơn":
                                if (flag != 5)
                                        flag = -1;
                                break;
                        case "Đường Môn":
                                if (flag != 4)
                                        flag = -1;
                                break;
                        case "Cấm Vệ Quân":
                                if (flag != 3)
                                        flag = -1;
                                break;
                        case "Thục Sơn":
                                if (flag != 2)
                                        flag = -1;
                                break;
                        case "Đào Hoa Nguyên":
                                if (flag != 1)
                                        flag = -1;
                                break;
                        }
                        break;
                }
                if (flag < 0)
                {
                        send_user(me, "%c%s", '!', equip->get_name() + " không phải trang bị Môn phái");
                        return 0;
                }
        }
        else
        {
                if (index == WEAPON_TYPE)
                {
                        type = equip->get_weapon_type();
                        switch (me->get_fam_name())
                        {
                        case "Đào Hoa Nguyên":
                                if (type != UNARMED)
                                        flag = -1;
                                break;
                        case "Thục Sơn":
                                if (type != SWORD && type != BLADE)
                                        flag = -1;
                                break;
                        case "Cấm Vệ Quân":
                                if (type != STICK && type != SPEAR)
                                        flag = -1;
                                break;
                        case "Đường Môn":
                                if (type != THROWING)
                                        flag = -1;
                                break;
                        case "Mao Sơn":
                                if (type != SWORD)
                                        flag = -1;
                                break;
                        case "Côn Luân":
                                if (type != SWORD)
                                        flag = -1;
                                break;
                        case "Vân Mộng Cốc":
                                if (type != SWORD)
                                        flag = -1;
                                break;
                        }
                }
                if (flag < 0)
                {
                        send_user(me, "%c%s", '!', "Bạn không thể trang bị " + equip->get_name() + ".");
                        return 0;
                }
        }

        level = equip->get_level() - me->get_equip_less_level() - equip->get("-1-");
        if (level > me->get_level() && equip->get_stuff_type() == 0)
        {
                if (level < 0)
                        level = 0;
                send_user(me, "%c%s", '!', sprintf("Trang bị %s phải ở cấp %d .", equip->get_name(), level));
                return 0;
        }
        if (equip->get_level() >= 30 && equip->get_hide() && equip->get_equip_type() != HAND_TYPE)
        {
                send_user(me, "%c%s", '!', "Trang bị chưa giám định");
                return 0;
        }
        if (equip->get("time_item") && equip->get_lock_time() && equip->get_lock_time() < time()) //有效期限至物品  到期处理
        {
                send_user(me, "%c%s", '!', "Trang bị đã hết hạn sử dụng");
                return 0;
        }
        flag = 0; // 现在用于：法宝判断

        if (objectp(item = me->get_equip(index))) // 交换旧的装备
        {
                if (item->get_talisman_type() == 11 && sizeof_inventory(me, MAX_CARRY * 3 + 1, MAX_CARRY * 4)) // 混元乾坤袋
                {
                        send_user(me, "%c%s", '!', item->get_name() + " bên trong trang bị có cái gì");
                        return 0;
                }

                if (item->get_item_type() == ITEM_TYPE_TALISMAN)
                        flag = 1; // 取下法宝

                d = get_d(equip);
                remove_item(equip);

                item->set_owner(0);
                item->remove_equip(me, d);
                //			me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
                if (item->is_suit())
                        iSuit = 1;
        }
        else
        {
                d = get_d(equip);
                remove_item(equip);
        }
        me->set_equip(index, equip);
        set_d(equip, index);
        equip->set_owner(me);
        send_user(me, "%c%c%c", 0x5c, d, index);
        count_equip_apply(me, equip, item);

        switch (index)
        {
        default:
                break;

        case ARMOR_TYPE:
                //                        if (MAIN_D->get_host_type()!=1000)
                if (0)
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%c%d%d", 0x23, getoid(me),
                                  me->get_armor_code(), me->get_armor_color_1(), me->get_armor_color_2());
                else
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                                  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
                //send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%c%d%d%w", 0x23, getoid(me),
                //		me->get_armor_code(), me->get_armor_color_1(), me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me)) );
                //	equip->start_loop_perform(me);
                //	equip->get_equip_effect(me);

                break;
        case HEAD_TYPE: //send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%d", 0x7e, getoid(me), me->get_head_code(), me->get_head_color() );
                break;
        case WEAPON_TYPE:
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%w%w", 0x7c, getoid(me), me->get_weapon_code_2(), me->get_weapon_color(), me->get_weapon_color_2());
                break;

        case HAND_TYPE:
                if (equip->get_item_type() == ITEM_TYPE_TALISMAN) // 装备法宝
                {
                        if (!flag)
                                if (file = load_object(SKILL->get_skill_file(SKILL_TALISMAN)))
                                        file->can_perform(me); // 增加法宝指令
                                                               //                        	if(equip->get("time_item"))   //特效法宝物品 崔月之环
                                                               //                        	{
                                                               //                        		equip->start_loop_perform(me);
                                                               //                        		USER_ENERGY_D->count_ap(me);
                                                               //                        		USER_ENERGY_D->count_cp(me);
                                                               //                        	}
                        equip->start_loop_perform(me);
                        equip->get_equip_effect(me);
                        /*
                                if( equip->get_talisman_type() != 11 )    // 混元乾坤袋
                                        me->set_have_bag( me->have_bag() & (~ BAG_TYPE_3) );    // 取消
                                else    me->set_have_bag( me->have_bag() | BAG_TYPE_3 );    // 加上
*/
                }
                else
                {
                        if (flag)
                                if (file = load_object(SKILL->get_skill_file(SKILL_TALISMAN)))
                                        file->remove_perform(me); // 删除法宝指令

                        //                                me->set_have_bag( me->have_bag() & (~ BAG_TYPE_3) );    // 取消混元乾坤袋
                }
                break;
        case BACK_TYPE:
                equip->get_equip_effect(me);
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                          me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
                break;
        case FASHION_TYPE:
                equip->get_equip_effect(me);
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                          me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
                break;
        }
        USER_INVENTORY_D->send_lasting_tips(me);
        if (equip->get_bind() == 1)
        {
                equip->set_bind(2);
                send_user(me, "%c%d%c", 0x31, getoid(equip), 0);
        }

        if (equip->is_suit() || iSuit)
                "sys/user/suit"->check_suit_equip(me);
        return 1;
}

// 函数：读取装备对象(用于 inventory.c)
int restore_equip(object me, object equip)
{
        object file;
        int index, id;

        if (!equip || !(index = equip->get_equip_type()))
                return 0;

        //      if( equip->get_level() - equip->get("-1-") > me->get_level() ) return 0;
        if (index == FAMILY_TYPE)
                equip->init_familyobj();
        me->set_equip(index, equip);
        set_d(equip, index);
        equip->set_owner(me);
        equip->add_to_user(index);
        // count_equip_apply( ??? );

        return 1;
}

// 函数：移除装备对象
int remove_equip(object me, int index)
{
        object item, file;
        int id;
        int bag, b, c, d, allcount;
        bag = me->have_bag();
        b = bag % 100;
        c = (bag / 100) % 100;
        d = bag / 10000;
        if (b > 0 && me->get_bag1_time() > 0 && time() > me->get_bag1_time())
                b = 0;
        if (c > 0 && me->get_bag2_time() > 0 && time() > me->get_bag2_time())
                c = 0;
        if (d > 0 && me->get_bag3_time() > 0 && time() > me->get_bag3_time())
                d = 0;
        if (me->get_reincarnation())
                b = MAX_CARRY;
        allcount = MAX_CARRY + b + c + d;
        if (!objectp(item = me->get_equip(index)))
        {
                send_user(me, "%c%s", '!', "Bạn vẫn chưa trang bị vật này.");
                return 0;
        }
        if (sizeof_inventory(me, 1, MAX_CARRY * 4) >= allcount)
        {
                send_user(me, "%c%s", '!', "Đồ vật trên người Bạn quá nhiều, không thể lấy " + item->get_name() + " .");
                return 0;
        }
        if (item->get_talisman_type() == 11 && sizeof_inventory(me, MAX_CARRY * 3 + 1, MAX_CARRY * 4)) // 混元乾坤袋
        {
                send_user(me, "%c%s", '!', item->get_name() + " bên trong trang bị có cái gì");
                return 0;
        }

        d = item->remove_equip(me, -1);
        send_user(me, "%c%c%c", 0x5c, index, d);
        item->set_owner(0);
        me->set_equip(index, 0);
        count_equip_apply(me, item);

        switch (index)
        {
        default:
                break;

        case ARMOR_TYPE:
                //                        if (MAIN_D->get_host_type()!=1000)
                if (0)
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%c%d%d", 0x23, getoid(me),
                                  me->get_armor_code(), me->get_armor_color_1(), me->get_armor_color_2());
                else
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                                  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
                //send_user( get_scene_object_2(me, USER_TYPE), "%c%d%d%w%c%d%d%w", 0x23, getoid(me),
                //		me->get_armor_code(), me->get_armor_color_1(), me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me)) );
                //	item->stop_loop_perform(me);
                break;
        case HEAD_TYPE: //send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%d", 0x7e, getoid(me), me->get_head_code(), me->get_head_color() );
                break;
        case WEAPON_TYPE:
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%w%w", 0x7c, getoid(me), me->get_weapon_code_2(), me->get_weapon_color(), me->get_weapon_color_2());
                break;

        case HAND_TYPE:
                if (item->get_item_type() == ITEM_TYPE_TALISMAN)
                {
                        if (file = load_object(SKILL->get_skill_file(SKILL_TALISMAN)))
                                file->remove_perform(me); // 删除法宝指令
                                                          //                                if(item->get("time_item")) item->stop_loop_perform(me);   //特效法宝物品 崔月之环
                        item->stop_loop_perform(me);
                        //                                me->set_have_bag( me->have_bag() & (~ BAG_TYPE_3) );    // 取消混元乾坤袋
                }
                break;
        case BACK_TYPE:
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                          me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
                break;
        case FASHION_TYPE:
                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                          me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
                break;
        }
        USER_INVENTORY_D->send_lasting_tips(me);
        if (item->is_suit())
                "sys/user/suit"->check_suit_equip(me);
        return 1;
}

// 函数：丢弃装备对象
int drop_equip(object me, int index) // 用于 perform 类, 死亡也用到
{
        object *inv, item, file;
        int z, x, y, p;
        int i, size;

        if (!objectp(item = me->get_equip(index)))
                return 0;

        // send_user( me, "%c%c%c", 0x5c, index, -1 );

        if ((z = get_z(me)) && (p = get_valid_xy(z, get_x(me) + random(3) - 1, get_y(me) + random(3) - 1, IS_ITEM_BLOCK)))
        {
                x = p / 1000;
                y = p % 1000;
                item->set_bind(5);
                item->set_owner(0);
                send_user(me, "%c%d", 0x2d, getoid(item));
                item->add_to_scene(z, x, y);

                me->set_equip(index, 0);
                count_equip_apply(me, item);

                switch (index)
                {
                default:
                        break;

                case ARMOR_TYPE:
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                                  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
                        break;
                case HEAD_TYPE: //send_user( get_scene_object_2(me, USER_TYPE), "%c%d%w%d", 0x7e, getoid(me), me->get_head_code(), me->get_head_color() );
                        break;
                case WEAPON_TYPE:
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%w%w", 0x7c, getoid(me), me->get_weapon_code_2(), me->get_weapon_color(), me->get_weapon_color_2());
                        break;

                case HAND_TYPE:
                        if (item->get_item_type() == ITEM_TYPE_TALISMAN)
                        {
                                if (file = load_object(SKILL->get_skill_file(SKILL_TALISMAN)))
                                        file->remove_perform(me); // 删除法宝指令
                                                                  //                                        me->set_have_bag( me->have_bag() & (~ BAG_TYPE_3) );    // 取消混元乾坤袋

                                if (item->get_talisman_type() == 11) // 混元乾坤袋
                                {
                                        inv = all_inventory(me, MAX_CARRY * 3 + 1, MAX_CARRY * 4); // 丢出袋里所有东西
                                        for (i = 0, size = sizeof(inv); i < size; i++)
                                        {
                                                if (inv[i]->get_no_drop() || inv[i]->get_no_get() || inv[i]->get_no_give())
                                                        continue;

                                                if (!(p = get_valid_xy(z, x + random(3) - 1, y + random(3) - 1, IS_ITEM_BLOCK)))
                                                        continue;

                                                inv[i]->remove_from_user();
                                                inv[i]->add_to_scene(z, p / 1000, p % 1000);
                                        }
                                }
                        }
                        break;
                case BACK_TYPE:
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                                  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
                        break;
                case FASHION_TYPE:
                        send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%w%w%w%w%w", 0x23, getoid(me),
                                  me->get_armor_code(), me->get_armor_color_1(), me->get_back(), me->get_back_color(), me->get_back2(), me->get_back2_color());
                        break;
                }
        }

        USER_INVENTORY_D->send_lasting_tips(me);

        return 1;
}

// 函数：统计装备影响
varargs void count_equip_apply(object me, object equip, object equip2)
{
        object item;
        int hp, mp, ap, dp, cp, pp, sp, spp;
        int poison, absorb, hit_rate, dodge_rate, anti_hurt, hurt, other;

        if (item = equip)
        {
                if (item->get("hp") || item->get("hp%") || item->get("hpp") || item->get("hp3") || item->get("hp+") || item->get("hp2"))
                        hp = 1;
                if (item->get("mp") || item->get("mp%") || item->get("mpp") || item->get("mp+") || item->get("mp2"))
                        mp = 1;
                if (item->get("ap") || item->get("ap%") || item->get("app") || item->get("ap3") || item->get("ap+") || item->get("ap2"))
                        ap = 1;
                if (item->get("dp") || item->get("dpp") || item->get("dp3") || item->get("dp+") || item->get("dp2"))
                        dp = 1;
                if (item->get("cp") || item->get("cp%") || item->get("cpp") || item->get("cp3") || item->get("cp+") || item->get("cp2"))
                        cp = 1;
                if (item->get("pp") || item->get("ppp") || item->get("pp3") || item->get("pp+") || item->get("pp2"))
                        pp = 1;
                if (item->get("sp") || item->get("sp+") || item->get("sp2"))
                        sp = 1;

                if (item->get("@%") || item->get("X@%") || item->get("-@%") || item->get("/%"))
                        poison = 1;
                if (item->get("hp*") || item->get("mp*"))
                        absorb = 1;
                if (item->get("!%") || item->get("c!%") || item->get("t!%"))
                        hit_rate = 1;
                if (item->get("!%+") || item->get("c!%+") || item->get("t!%+"))
                        hit_rate = 1;
                if (item->get("double"))
                        hit_rate = 1;
                if (item->get("double2"))
                        hit_rate = 1;
                if (item->get("?%") || item->get("c?%"))
                        dodge_rate = 1;
                if (item->get("-*") || item->get("-c*") || item->get("-*%") || item->get("-c*%"))
                        anti_hurt = 1;
                if (item->get("??%") || item->get("#%") || item->get("cp+@") || item->get("heal+@"))
                        other = 1;

                switch (item->get_equip_type())
                {
                case WEAPON_TYPE:
                        ap = 1;
                        cp = 1;
                        dp = 1;
                        break;
                case ARMOR_TYPE:
                        dp = 1;
                        pp = 1;
                        break;
                case BACK_TYPE:
                        if (item->is_nangcap())
                                spp = 1;
                        break;
                default:
                        break;
                }
        }

        if (item = equip2)
        {
                if (item->get("hp") || item->get("hp%") || item->get("hpp") || item->get("hp3") || item->get("hp+") || item->get("hp2"))
                        hp = 1;
                if (item->get("mp") || item->get("mp%") || item->get("mpp") || item->get("mp+") || item->get("mp2"))
                        mp = 1;
                if (item->get("ap") || item->get("ap%") || item->get("app") || item->get("ap3") || item->get("ap+") || item->get("ap2"))
                        ap = 1;
                if (item->get("dp") || item->get("dpp") || item->get("dp3") || item->get("dp+") || item->get("dp2"))
                        dp = 1;
                if (item->get("cp") || item->get("cp%") || item->get("cpp") || item->get("cp3") || item->get("cp+") || item->get("cp2"))
                        cp = 1;
                if (item->get("pp") || item->get("ppp") || item->get("pp3") || item->get("pp+") || item->get("pp2"))
                        pp = 1;
                if (item->get("sp") || item->get("sp+") || item->get("sp2"))
                        sp = 1;

                if (item->get("@%") || item->get("X@%") || item->get("-@%") || item->get("/%"))
                        poison = 1;
                if (item->get("hp*") || item->get("mp*"))
                        absorb = 1;
                if (item->get("!%") || item->get("c!%") || item->get("t!%"))
                        hit_rate = 1;
                if (item->get("!%+") || item->get("c!%+") || item->get("t!%+"))
                        hit_rate = 1;
                if (item->get("double"))
                        hit_rate = 1;
                if (item->get("double2"))
                        hit_rate = 1;
                if (item->get("?%") || item->get("c?%"))
                        dodge_rate = 1;
                if (item->get("-*") || item->get("-c*") || item->get("-*%") || item->get("-c*%"))
                        anti_hurt = 1;
                if (item->get("??%") || item->get("#%") || item->get("cp+@") || item->get("heal+@"))
                        other = 1;

                switch (item->get_equip_type())
                {
                case WEAPON_TYPE:
                        ap = 1;
                        cp = 1;
                        dp = 1;
                        break;
                case ARMOR_TYPE:
                        dp = 1;
                        pp = 1;
                        break;
                case BACK_TYPE:
                        if (item->is_nangcap())
                                spp = 1;
                        break;
                default:
                        break;
                }
        }
        if (spp)
        {
                CHAR_CHAR_D->init_loop_perform(me);
                me->add_to_scene(get_z(me), get_x(me), get_y(me), get_d(me));
        }
        if (hp)
                USER_ENERGY_D->count_max_hp(me);
        if (mp)
                USER_ENERGY_D->count_max_mp(me);
        if (cp)
                USER_ENERGY_D->count_cp(me); // cp/pp 影响 ap/dp, 所以放前
        if (pp)
                USER_ENERGY_D->count_pp(me);
        if (ap)
                USER_ENERGY_D->count_ap(me);
        if (dp)
                USER_ENERGY_D->count_dp(me);
        if (sp)
                USER_ENERGY_D->count_sp(me);

        if (poison)
                USER_ENERGY_D->count_poison(me);
        if (absorb)
                USER_ENERGY_D->count_absorb(me);
        if (hit_rate)
                USER_ENERGY_D->count_hit_rate(me);
        if (dodge_rate)
                USER_ENERGY_D->count_dodge_rate(me);
        if (anti_hurt)
                USER_ENERGY_D->count_anti_hurt(me);
        if (hurt)
                USER_ENERGY_D->count_hurt(me);
        if (other)
                USER_ENERGY_D->count_other(me);
}
