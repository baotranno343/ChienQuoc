
#include <equip.h>
#include <skill.h>
#include <effect.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

void count_all_prop(object me);

// 函数：初始化门派
varargs void init_family(object me, int family, int level, int weapon) // BOSS专用    // famliy 命令借用
{
        object item;
        string file;
        int level2, level3, gender, armor, p, npc_flag;

        level = range_value(level, 0, NPC->get_max_skill_level());
        if (level < 70 && level > 20)
        {
                level3 = (level / 5) * 5;
        }
        else
                level3 = (level / 10) * 10;
        if (level3 > 130)
                level3 = 130;
        me->set_level(level);

        if (me->is_npc())
        {
                npc_flag = 1;

                switch (me->get_gender())
                {
                case 1:
                        gender = 1;
                        me->set_con(30 + level);
                        me->set_spi(25 + level);
                        me->set_str(25 + level);
                        me->set_cps(25 + level);
                        me->set_dex(25 + level);
                        break;
                default:
                        gender = 2;
                        me->set_con(30 + level);
                        me->set_spi(25 + level);
                        me->set_str(25 + level);
                        me->set_cps(25 + level);
                        me->set_dex(25 + level);
                        break;
                }
        }
        else
        {
                npc_flag = 0;

                switch (me->get_gender())
                {
                case 1:
                        gender = 1;
                        me->set_con_1(30);
                        me->set_con_2(0); // 清除后天属性
                        me->set_spi_1(25);
                        me->set_spi_2(0);
                        me->set_str_1(25);
                        me->set_str_2(0);
                        me->set_cps_1(25);
                        me->set_cps_2(0);
                        me->set_dex_1(25);
                        me->set_dex_2(0);
                        break;
                default:
                        gender = 2;
                        me->set_con_1(30);
                        me->set_con_2(0);
                        me->set_spi_1(25);
                        me->set_spi_2(0);
                        me->set_str_1(25);
                        me->set_str_2(0);
                        me->set_cps_1(25);
                        me->set_cps_2(0);
                        me->set_dex_1(25);
                        me->set_dex_2(0);
                        break;
                }
                me->init_mascot_dbase(); // 清除福缘数据集
                me->set_gift_point(level * me->get_gift_point_times());
        }

        switch (me->get_reincarnation())
        {
        default:
                level2 = level;
                break;
        case 1:
                level2 = level + 100;
                break;
        case 2:
                level2 = level + 200;
                break;
        }

        switch (family)
        {
        default:
                me->set_fam_name(0);
                me->set_skill(0111, level2);
                me->set_skill(0121, level2);
                me->set_skill(0131, level2);
                me->set_skill(0141, level2);
                me->set_skill(0151, level2);
                me->set_skill(0161, level2);
                me->set_skill(0104, level2);
                me->set_skill(0109, level2);
                me->set_skill(0202, level2);
                me->set_skill(0401, level2);
                me->set_skill(0402, level2);
                me->set_skill(0403, level2);
                me->set_skill(0408, level2);
                me->set_skill(0409, level2);
                me->set_skill(0503, level2);
                if (weapon < 0)
                        weapon = -4;
                else
                        weapon = -weapon;
                armor = 0;
                break;

        case 1:
        case 10:
                me->set_fam_name("Đào Hoa Nguyên");
                me->set_skill(0211, level);
                me->set_skill(0212, level);
                me->set_skill(0316, level);
                me->set_skill(0317, level);
                me->set_skill(0319, level);
                //                me->set_skill(0371, level);
                //               me->set_skill(0372, level);
                //                me->set_skill(0373, level);
                //               me->set_skill(0374, level);
                //             me->set_skill(0375, level);
                if (weapon < 0)
                        weapon = 1;
                armor = 1;
                break;

        case 2:
        case 20:
                me->set_fam_name("Thục Sơn");
                me->set_skill(0221, level);
                me->set_skill(0231, level);
                me->set_skill(0222, level);
                //                me->set_skill(0232, level);
                //                me->set_skill(0324, level);
                me->set_skill(0325, level);
                me->set_skill(0329, level);
                //               me->set_skill(0331, level);
                //             me->set_skill(0332, level);
                //           me->set_skill(0333, level);
                //         me->set_skill(0334, level);
                //       me->set_skill(0335, level);
                if (weapon < 0)
                        weapon = 4;
                armor = 1;
                break;

        case 3:
        case 30:
                me->set_fam_name("Cấm Vệ Quân");
                me->set_skill(0241, level);
                me->set_skill(0251, level);
                me->set_skill(0242, level);
                //                me->set_skill(0252, level);
                me->set_skill(0348, level);
                me->set_skill(0349, level);
                //               me->set_skill(0351, level);
                //             me->set_skill(0352, level);
                //           me->set_skill(0353, level);
                //         me->set_skill(0354, level);
                //       me->set_skill(0355, level);
                if (weapon < 0)
                        weapon = 5;
                armor = 1;
                break;

        case 4:
        case 40:
                me->set_fam_name("Đường Môn");
                me->set_skill(0261, level);
                me->set_skill(0363, level);
                me->set_skill(0364, level);
                me->set_skill(0365, level);
                me->set_skill(0368, level);
                //               me->set_skill(0381, level);
                //              me->set_skill(0382, level);
                //             me->set_skill(0383, level);
                //            me->set_skill(0384, level);
                //           me->set_skill(0385, level);
                if (weapon < 0)
                        weapon = 2;
                armor = 2;
                break;

        case 5:
        case 50:
                me->set_fam_name("Mao Sơn");
                me->set_skill(0271, level);
                //                me->set_skill(0411, level);
                me->set_skill(0413, level);
                me->set_skill(0414, level);
                me->set_skill(0417, level);
                me->set_skill(0418, level);
                //        me->set_skill(0461, level);
                //      me->set_skill(0462, level);
                //    me->set_skill(0463, level);
                //  me->set_skill(0464, level);
                //me->set_skill(0465, level);
                if (weapon < 0)
                        weapon = 7;
                armor = 3;
                break;

        case 6:
        case 60:
                me->set_fam_name("Côn Luân");
                me->set_skill(0421, level);
                me->set_skill(0422, level);
                me->set_skill(0423, level);
                me->set_skill(0424, level);
                me->set_skill(0425, level);
                //                me->set_skill(0429, level);
                //               me->set_skill(0441, level);
                //              me->set_skill(0442, level);
                //             me->set_skill(0443, level);
                //            me->set_skill(0444, level);
                //           me->set_skill(0445, level);
                if (weapon < 0)
                        weapon = 7;
                armor = 3;
                break;

        case 7:
        case 70:
                me->set_fam_name("Vân Mộng Cốc");
                me->set_skill(0281, level);
                me->set_skill(0501, level);
                me->set_skill(0511, level);
                //                me->set_skill(0513, level);
                //                me->set_skill(0521, level);
                me->set_skill(0531, level);
                me->set_skill(0591, level);
                //             me->set_skill(0541, level);
                //            me->set_skill(0542, level);
                //           me->set_skill(0543, level);
                //          me->set_skill(0544, level);
                //         me->set_skill(0545, level);
                if (weapon < 0)
                        weapon = 4;
                armor = 2;
                break;
        }
        me->set_fam_master(0); // 一律删除当前师父

        switch (family) // 增加基本技能
        {
        case 10:
        case 20:
        case 30:
        case 40:
        case 50:
        case 60:
        case 70:
                me->set_skill(0111, level2);
                me->set_skill(0121, level2);
                me->set_skill(0131, level2);
                me->set_skill(0141, level2);
                me->set_skill(0151, level2);
                me->set_skill(0161, level2);
                me->set_skill(0104, level2);
                me->set_skill(0109, level2);
                me->set_skill(0202, level2);
                me->set_skill(0401, level2);
                me->set_skill(0402, level2);
                me->set_skill(0403, level2);
                me->set_skill(0408, level2);
                me->set_skill(0409, level2);
                me->set_skill(0503, level2);
                break;
        }
        weapon = family;
        if (weapon >= 10)
                weapon /= 10;
        switch (weapon)
        {
        default:
                file = "";
                break; // 没有武器

                // Vũ khí môn phái
        case 1:
                file = sprintf("/item/70/1%03d", level3);
                break;
        case 2:
                file = sprintf("/item/76/1%03d", level3);
                break;
        case 3:
                file = sprintf("/item/74/1%03d", level3);
                break;
        case 4:
                file = sprintf("/item/71/1%03d", level3);
                break;
        case 5:
                file = sprintf("/item/77/1%03d", level3);
                break;
        case 6:
                file = sprintf("/item/78/1%03d", level3);
                break;
        case 7:
                file = sprintf("/item/79/1%03d", level3);
                break;
        }
        if (npc_flag)
        {
                if (item = load_object(file))
                        me->use_equip(item); // 复制属性
        }
        else if (load_object(file))
        {
                item = new (file);
                ITEM_EQUIP_D->init_equip_prop_3(item);
                item->set_hide(0);
                //"/sys/item/equip"->init_equip_prop_1(item);

                if (p = item->move(me, -1))
                {
                        item->add_to_user(p);
                        me->use_equip(item);
                }
                else
                        destruct(item);
        }
        armor = family;
        if (armor >= 10)
                armor /= 10;

        if (gender == 1)
                switch (armor)
                {
                case 0:
                        file = sprintf("/item/60/%04d", range_value(level3, 1, 50));
                        break; // 基本护具
                default:
                        file = sprintf("/item/60/%04d", 1000 * armor + level3);
                        break; // 门派护具
                }
        else
                switch (armor)
                {
                case 0:
                        file = sprintf("/item/61/%04d", range_value(level3, 1, 50));
                        break; // 基本护具
                default:
                        file = sprintf("/item/61/%04d", 1000 * armor + level3);
                        break; // 门派护具
                }
        if (npc_flag)
        {
                if (item = load_object(file))
                        me->use_equip(item); // 复制属性
        }
        else if (load_object(file))
        {
                item = new (file);
                ITEM_EQUIP_D->init_equip_prop_3(item);
                item->set_hide(0);
                //"/sys/item/equip"->init_equip_prop_1(item);
                if (p = item->move(me, -1))
                {
                        item->add_to_user(p);
                        me->use_equip(item);
                }
                else
                        destruct(item);
        }

        if (gender == 1)
                switch (armor)
                {
                case 0:
                        file = sprintf("/item/65/%04d", range_value(level3, 1, 50));
                        break; // 基本护具
                default:
                        file = sprintf("/item/65/%04d", 1000 * armor + level3);
                        break; // 门派护具
                }
        else
                switch (armor)
                {
                case 0:
                        file = sprintf("/item/66/%04d", range_value(level3, 1, 50));
                        break; // 基本护具
                default:
                        file = sprintf("/item/66/%04d", 1000 * armor + level3);
                        break; // 门派护具
                }
        if (npc_flag)
        {
                if (item = load_object(file))
                        me->use_equip(item); // 复制属性
        }
        else if (load_object(file))
        {
                item = new (file);
                ITEM_EQUIP_D->init_equip_prop_3(item);
                item->set_hide(0);
                //"/sys/item/equip"->init_equip_prop_1(item);
                if (p = item->move(me, -1))
                {
                        item->add_to_user(p);
                        me->use_equip(item);
                }
                else
                        destruct(item);
        }

        switch (armor)
        {
        case 0:
                file = sprintf("/item/86/%04d", range_value(level3, 1, 50));
                break; // 基本护具
        default:
                file = sprintf("/item/86/%04d", 1000 * armor + level3);
                break; // 门派护具
        }
        if (npc_flag)
        {
                if (item = load_object(file))
                        me->use_equip(item); // 复制属性
        }
        else if (load_object(file))
        {
                item = new (file);
                ITEM_EQUIP_D->init_equip_prop_3(item);
                item->set_hide(0);
                //"/sys/item/equip"->init_equip_prop_1(item);
                if (p = item->move(me, -1))
                {
                        item->add_to_user(p);
                        me->use_equip(item);
                }
                else
                        destruct(item);
        }

        switch (armor)
        {
        case 0:
                file = sprintf("/item/87/%04d", range_value(level3, 1, 50));
                break; // 基本护具
        default:
                file = sprintf("/item/87/%04d", 1000 * armor + level3);
                break; // 门派护具
        }
        if (npc_flag)
        {
                if (item = load_object(file))
                        me->use_equip(item); // 复制属性
        }
        else if (load_object(file))
        {
                item = new (file);
                ITEM_EQUIP_D->init_equip_prop_3(item);
                item->set_hide(0);
                //"/sys/item/equip"->init_equip_prop_1(item);
                if (p = item->move(me, -1))
                {
                        item->add_to_user(p);
                        me->use_equip(item);
                }
                else
                        destruct(item);
        }

        switch (armor)
        {
        case 0:
                file = sprintf("/item/88/%04d", range_value(level3, 1, 50));
                break; // 基本护具
        default:
                file = sprintf("/item/88/%04d", 1000 * armor + level3);
                break; // 门派护具
        }
        if (npc_flag)
        {
                if (item = load_object(file))
                        me->use_equip(item); // 复制属性
        }
        else if (load_object(file))
        {
                item = new (file);
                ITEM_EQUIP_D->init_equip_prop_3(item);
                item->set_hide(0);
                //"/sys/item/equip"->init_equip_prop_1(item);
                if (p = item->move(me, -1))
                {
                        item->add_to_user(p);
                        me->use_equip(item);
                }
                else
                        destruct(item);
        }

        if (npc_flag)
                count_all_prop(me);
}
varargs void init_family2(object me, int family, int level, int weapon) // BOSS专用    // famliy 命令借用
{
        object item;
        string file;
        int level2, level3, gender, armor, p, npc_flag;

        level = range_value(level, 0, NPC->get_max_skill_level());
        if (level < 70 && level > 20)
        {
                level3 = (level / 5) * 5;
        }
        else
                level3 = (level / 10) * 10;
        if (level3 > 130)
                level3 = 130;
        me->set_level(level);

        if (me->is_npc())
        {
                npc_flag = 1;

                switch (me->get_gender())
                {
                case 1:
                        gender = 1;
                        me->set_con(30 + level);
                        me->set_spi(25 + level);
                        me->set_str(25 + level);
                        me->set_cps(25 + level);
                        me->set_dex(25 + level);
                        break;
                default:
                        gender = 2;
                        me->set_con(30 + level);
                        me->set_spi(25 + level);
                        me->set_str(25 + level);
                        me->set_cps(25 + level);
                        me->set_dex(25 + level);
                        break;
                }
        }
        else
        {
                npc_flag = 0;

                switch (me->get_gender())
                {
                case 1:
                        gender = 1;
                        me->set_con_1(30);
                        me->set_con_2(0); // 清除后天属性
                        me->set_spi_1(25);
                        me->set_spi_2(0);
                        me->set_str_1(25);
                        me->set_str_2(0);
                        me->set_cps_1(25);
                        me->set_cps_2(0);
                        me->set_dex_1(25);
                        me->set_dex_2(0);
                        break;
                default:
                        gender = 2;
                        me->set_con_1(30);
                        me->set_con_2(0);
                        me->set_spi_1(25);
                        me->set_spi_2(0);
                        me->set_str_1(25);
                        me->set_str_2(0);
                        me->set_cps_1(25);
                        me->set_cps_2(0);
                        me->set_dex_1(25);
                        me->set_dex_2(0);
                        break;
                }
                me->init_mascot_dbase(); // 清除福缘数据集
                me->set_gift_point(level * me->get_gift_point_times());
        }

        switch (me->get_reincarnation())
        {
        default:
                level2 = level;
                break;
        case 1:
                level2 = level + 100;
                break;
        case 2:
                level2 = level + 200;
                break;
        }

        switch (family)
        {
        default:
                me->set_fam_name(0);
                me->set_skill(0111, level2);
                me->set_skill(0121, level2);
                me->set_skill(0131, level2);
                me->set_skill(0141, level2);
                me->set_skill(0151, level2);
                me->set_skill(0161, level2);
                me->set_skill(0104, level2);
                me->set_skill(0109, level2);
                me->set_skill(0202, level2);
                me->set_skill(0401, level2);
                me->set_skill(0402, level2);
                me->set_skill(0403, level2);
                me->set_skill(0408, level2);
                me->set_skill(0409, level2);
                me->set_skill(0503, level2);
                if (weapon < 0)
                        weapon = -4;
                else
                        weapon = -weapon;
                armor = 0;
                break;

        case 1:
        case 10:
                me->set_fam_name("Đào Hoa Nguyên");
                me->set_skill(0211, level);
                me->set_skill(0212, level);
                me->set_skill(0316, level);
                me->set_skill(0317, level);
                me->set_skill(0319, level);
                //                me->set_skill(0371, level);
                //               me->set_skill(0372, level);
                //                me->set_skill(0373, level);
                //               me->set_skill(0374, level);
                //             me->set_skill(0375, level);
                if (weapon < 0)
                        weapon = 1;
                armor = 1;
                break;

        case 2:
        case 20:
                me->set_fam_name("Thục Sơn");
                me->set_skill(0221, level);
                me->set_skill(0231, level);
                me->set_skill(0222, level);
                //                me->set_skill(0232, level);
                //                me->set_skill(0324, level);
                me->set_skill(0325, level);
                me->set_skill(0329, level);
                //               me->set_skill(0331, level);
                //             me->set_skill(0332, level);
                //           me->set_skill(0333, level);
                //         me->set_skill(0334, level);
                //       me->set_skill(0335, level);
                if (weapon < 0)
                        weapon = 4;
                armor = 1;
                break;

        case 3:
        case 30:
                me->set_fam_name("Cấm Vệ Quân");
                me->set_skill(0241, level);
                me->set_skill(0251, level);
                me->set_skill(0242, level);
                //                me->set_skill(0252, level);
                me->set_skill(0348, level);
                me->set_skill(0349, level);
                //               me->set_skill(0351, level);
                //             me->set_skill(0352, level);
                //           me->set_skill(0353, level);
                //         me->set_skill(0354, level);
                //       me->set_skill(0355, level);
                if (weapon < 0)
                        weapon = 5;
                armor = 1;
                break;

        case 4:
        case 40:
                me->set_fam_name("Đường Môn");
                me->set_skill(0261, level);
                me->set_skill(0363, level);
                me->set_skill(0364, level);
                me->set_skill(0365, level);
                me->set_skill(0368, level);
                //               me->set_skill(0381, level);
                //              me->set_skill(0382, level);
                //             me->set_skill(0383, level);
                //            me->set_skill(0384, level);
                //           me->set_skill(0385, level);
                if (weapon < 0)
                        weapon = 2;
                armor = 2;
                break;

        case 5:
        case 50:
                me->set_fam_name("Mao Sơn");
                me->set_skill(0271, level);
                //                me->set_skill(0411, level);
                me->set_skill(0413, level);
                me->set_skill(0414, level);
                me->set_skill(0417, level);
                me->set_skill(0418, level);
                //        me->set_skill(0461, level);
                //      me->set_skill(0462, level);
                //    me->set_skill(0463, level);
                //  me->set_skill(0464, level);
                //me->set_skill(0465, level);
                if (weapon < 0)
                        weapon = 7;
                armor = 3;
                break;

        case 6:
        case 60:
                me->set_fam_name("Côn Luân");
                me->set_skill(0421, level);
                me->set_skill(0422, level);
                me->set_skill(0423, level);
                me->set_skill(0424, level);
                me->set_skill(0425, level);
                //                me->set_skill(0429, level);
                //               me->set_skill(0441, level);
                //              me->set_skill(0442, level);
                //             me->set_skill(0443, level);
                //            me->set_skill(0444, level);
                //           me->set_skill(0445, level);
                if (weapon < 0)
                        weapon = 7;
                armor = 3;
                break;

        case 7:
        case 70:
                me->set_fam_name("Vân Mộng Cốc");
                me->set_skill(0281, level);
                me->set_skill(0501, level);
                me->set_skill(0511, level);
                //                me->set_skill(0513, level);
                //                me->set_skill(0521, level);
                me->set_skill(0531, level);
                me->set_skill(0591, level);
                //             me->set_skill(0541, level);
                //            me->set_skill(0542, level);
                //           me->set_skill(0543, level);
                //          me->set_skill(0544, level);
                //         me->set_skill(0545, level);
                if (weapon < 0)
                        weapon = 4;
                armor = 2;
                break;
        }
        me->set_fam_master(0); // 一律删除当前师父

        switch (family) // 增加基本技能
        {
        case 10:
        case 20:
        case 30:
        case 40:
        case 50:
        case 60:
        case 70:
                me->set_skill(0111, level2);
                me->set_skill(0121, level2);
                me->set_skill(0131, level2);
                me->set_skill(0141, level2);
                me->set_skill(0151, level2);
                me->set_skill(0161, level2);
                me->set_skill(0104, level2);
                me->set_skill(0109, level2);
                me->set_skill(0202, level2);
                me->set_skill(0401, level2);
                me->set_skill(0402, level2);
                me->set_skill(0403, level2);
                me->set_skill(0408, level2);
                me->set_skill(0409, level2);
                me->set_skill(0503, level2);
                break;
        }

        count_all_prop(me);
}
// 函数：统计所有属性
void count_all_prop(object me)
{
        int hp, mp, ap, dp, cp, pp, sp;
        int p, add, cent, cent2, rand;

        switch (me->get_fam_name())
        {
        default:
                hp = me->get_con() * 3;
                mp = me->get_spi();
                ap = me->get_str() * 12 / 10;
                dp = me->get_cps();
                cp = me->get_spi() / 2;
                pp = me->get_spi() * 6 / 10;
                sp = me->get_dex();
                break;
        case "Đào Hoa Nguyên":
                hp = me->get_con() * 55 / 10;
                mp = me->get_spi();
                ap = me->get_str() * 13 / 10;
                dp = me->get_cps() * 12 / 10;
                cp = me->get_spi() / 2;
                pp = me->get_spi() * 15 / 10;
                sp = me->get_dex();
                break;
        case "Thục Sơn":
                hp = me->get_con() * 45 / 10;
                mp = me->get_spi();
                ap = me->get_str() * 13 / 10;
                dp = me->get_cps() * 11 / 10;
                cp = me->get_spi() / 2;
                pp = me->get_spi() * 16 / 100;
                sp = me->get_dex();
                break;
        case "Cấm Vệ Quân":
                hp = me->get_con() * 6;
                mp = me->get_spi();
                ap = me->get_str() * 14 / 10;
                dp = me->get_cps();
                cp = me->get_spi() / 2;
                pp = me->get_spi() * 12 / 10;
                sp = me->get_dex();
                break;
        case "Đường Môn":
                hp = me->get_con() * 4;
                mp = me->get_spi() * 12 / 10;
                ap = me->get_str() * 12 / 10;
                dp = me->get_cps() * 11 / 10;
                cp = me->get_spi() / 2;
                pp = me->get_spi() * 18 / 10;
                sp = me->get_dex() * 18 / 10;
                break;
        case "Mao Sơn":
                hp = me->get_con() * 3;
                mp = me->get_spi() * 3;
                ap = me->get_str();
                dp = me->get_cps() * 12 / 10;
                cp = me->get_spi() * 2 / 3;
                pp = me->get_spi() * 18 / 10;
                sp = me->get_dex();
                break;
        case "Côn Luân":
                hp = me->get_con() * 3;
                mp = me->get_spi() * 3;
                ap = me->get_str() * 8 / 10;
                dp = me->get_cps();
                cp = me->get_spi() * 3 / 4;
                pp = me->get_spi() * 18 / 10;
                sp = me->get_dex() * 13 / 10;
                break;
        case "Vân Mộng Cốc":
                hp = me->get_con() * 45 / 10;
                mp = me->get_spi() * 15 / 10;
                ap = me->get_str() * 12 / 10;
                dp = me->get_cps() * 14 / 10;
                cp = me->get_spi() * 3 / 4;
                pp = me->get_spi() * 18 / 10;
                sp = me->get_dex() * 11 / 10;
                break;
        }

        // 统计最大ＨＰ

        hp += hp * me->get("hp%") / 100;
        hp += me->get("hp");

        if (p = me->get_skill(SKILL_0109))
                hp += p * 2; // 经络学说

        if (p = me->get_skill(SKILL_0319))
                hp += p * 6; // 周天运转
        else if (p = me->get_skill(SKILL_0329))
                hp += p * 4; // 周天运转
        else if (p = me->get_skill(SKILL_0349))
                hp += p * 3; // 周天运转

        if (p = me->get_skill(SKILL_0501))
                hp += p * 3; // 中医药理

        me->set_max_hp(hp);

        // 统计最大ＭＰ

        mp += mp * me->get("mp%") / 100;
        mp += me->get("mp");

        if (p = me->get_skill(SKILL_0401))
                mp += p * 2; // 道家学说

        if (p = me->get_skill(SKILL_0411))
                mp += p * 4; // 大乘道法
        else if (p = me->get_skill(SKILL_0421))
                mp += p * 4; // 大乘道法

        if (p = me->get_skill(SKILL_0501))
                mp += p * 3; // 中医药理

        me->set_max_mp(mp);

        // 统计法术攻击

        cp += me->get_skill(SKILL_0402) / 2;     // 诵经
        cp += me->get_skill(SKILL_0422) * 3 / 2; // 阴阳五行

        cp += cp * me->get("cp%") / 100;
        cp += me->get("cp");

        if (p = me->get_skill(SKILL_0411))
                cp += p; // 大乘道法
        else if (p = me->get_skill(SKILL_0421))
                cp += p * 3 / 2; // 大乘道法

        me->set_cp(cp);

        // 统计法术防御

        pp += me->get_skill(SKILL_0403) / 2; // 禅定
        pp += me->get_skill(SKILL_0422);     // 阴阳五行

        if (get_effect(me, EFFECT_CHAR_ADD_PP))
                pp += pp * 20 / 100; // 护体金光(＋法防)

        pp += pp * me->get("pp%") / 100;
        pp += me->get("pp");

        if (p = me->get_skill(SKILL_0501))
                pp += p * 9 / 10; // 中医药理

        if (get_effect(me, EFFECT_CHAR_ARMORFALL))
                pp += me->get("pf.armorfall"); // 蚀甲

        me->set_pp(pp);

        // 统计物理攻击/物理防御

        if (me->get_perform(PF_FLAG_03484) && (p = 50 - me->get_hp() * 100 / range_value(me->get_max_hp(), 1, MAX_NUMBER)) > 0)
                ap += ap * me->set_temp_ap("03484%", p * 2) / 100;

        if (me->get_perform(PF_FLAG_03485) && (p = 50 - me->get_hp() * 100 / range_value(me->get_max_hp(), 1, MAX_NUMBER)) > 0)
                dp += dp * me->set_temp_dp("03485%", p * 5) / 100;

        if (get_effect(me, EFFECT_CHAR_WOUND))
                ap -= ap * 30 / 100; // 负伤
        if (get_effect(me, EFFECT_CHAR_WOUND))
                dp -= dp * 30 / 100; // 负伤

        if (get_effect(me, EFFECT_CHAR_ADD_DP))
                dp += dp * 20 / 100; // 金钟罩(＋防御)

        ap += ap * me->get("ap%") / 100;
        ap += me->get("ap");

        dp += dp * me->get("dp%") / 100;
        dp += me->get("dp");

        switch (me->get_weapon_code())
        {
        default:
                if (p = me->get_skill(SKILL_0111))
                        ap += p / 2; // 基本拳脚
                if (p = me->get_skill(SKILL_0211))
                        ap += p; // 太古神拳
                if (p = me->get_skill(SKILL_0212))
                        dp += p; // 拳脚招架
                break;

        case THROWING:
                if (p = me->get_skill(SKILL_0161))
                        ap += p / 2; // 暗器投射
                if (p = me->get_skill(SKILL_0261))
                        ap += p; // 漫天花雨
                if (p = me->get_skill(SKILL_0212))
                        dp += p; // 拳脚招架
                if (p = me->get_skill(SKILL_0363))
                        dp += p * 4 / 10; // 唐门心法
                break;

        case BLADE:
                if (p = me->get_skill(SKILL_0121))
                        ap += p * 3 / 5; // 基本刀法
                if (p = me->get_skill(SKILL_0221))
                        ap += p * 11 / 10; // 天罗刀法
                if (p = me->get_skill(SKILL_0222))
                        dp += p * 11 / 10; // 刀法格挡
                break;

        case SWORD:
                if (p = me->get_skill(SKILL_0131))
                        ap += p / 2; // 基本剑法

                if (p = me->get_skill(SKILL_0231))
                        ap += p; // 飞仙剑法
                else if (p = me->get_skill(SKILL_0271))
                        ap += p * 4 / 5; // 降魔剑法
                else if (p = me->get_skill(SKILL_0281))
                        ap += p * 9 / 10; // 清风剑法

                if (p = me->get_skill(SKILL_0232))
                        dp += p * 12 / 10; // 剑法格挡

                break;

        case SPEAR:
                if (p = me->get_skill(SKILL_0141))
                        ap += p * 3 / 5; // 基本枪法
                if (p = me->get_skill(SKILL_0241))
                        ap += p * 6 / 5; // 霸王枪法
                if (p = me->get_skill(SKILL_0242))
                        dp += p * 4 / 5; // 枪法格挡
                break;

        case STICK:
                if (p = me->get_skill(SKILL_0151))
                        ap += p * 3 / 5; // 基本棍法
                if (p = me->get_skill(SKILL_0251))
                        ap += p * 6 / 5; // 疯魔棍法
                                         //                if( p = me->get_skill(SKILL_0252) ) dp += p * 4 / 5;    // 棍法格挡
                break;
        }
        if (p = me->get_skill(SKILL_0202))
                dp += p / 2; // 招架之术

        if (p = me->get_skill(SKILL_0348))
                dp += p * 3 / 5; // 兵法

        if (p = me->get_skill(SKILL_0417))
                dp += p / 4; // 神打

        if (p = me->get_skill(SKILL_0501))
                dp += p * 9 / 10; // 中医药理

        if (get_effect(me, EFFECT_CHAR_HALFGOD))
        {
                ap += me->set_temp_ap("04171", cp * me->get_skill(SKILL_0417) / 3 / 100); // 神打
                dp += me->set_temp_dp("04171", pp * me->get_skill(SKILL_0417) / 2 / 100); // 神打
        }
        if (get_effect(me, EFFECT_CHAR_POWERUP))
        {
                ap += me->get("pf.powerup"); // 金针渡厄
                cp += me->get("pf.powerup"); // 金针渡厄
        }

        if (get_effect(me, EFFECT_CHAR_ARMORFALL))
                dp += me->get("pf.armorfall"); // 蚀甲

        //      if( get_effect(me, EFFECT_CHAR_5215) ) ap += - me->get_save("5215");    // 软筋散

        me->set_ap(ap);
        me->set_dp(dp);

        // 统计腾挪躲闪

        sp += sp * me->get("sp%") / 100;
        sp += me->get("sp");

        if (p = me->get_skill(SKILL_0104))
                sp += p; // 腾挪躲闪

        if (p = me->get_skill(SKILL_0324))
                sp += p * 3 / 2; // 踏雪无痕
        else if (p = me->get_skill(SKILL_0364))
                sp += p * 2; // 踏雪无痕

        if (get_effect(me, EFFECT_CHAR_MOVE))
                sp += me->get_skill(SKILL_0364) * 3 / 2; // 踏雪无痕

        me->set_sp(sp);

        // 统计抗毒率/御毒率

        me->set_poison_rate(me->get("@%"));
        me->set_anti_poison(me->get("X@%"));
        me->set_lost_poison(me->get("-@%"));
        me->set_immunity(me->get("/%"));

        // 统计吸取气血/法力

        me->set_absorb_hp(me->get("hp*"));
        me->set_absorb_mp(me->get("mp*"));

        // 统计命中率

        me->set_hit_rate(me->get("!%"));
        me->set_hit_rate_2(me->get("c!%"));

        cent = me->get("t!%");
        if (p = me->get_skill(SKILL_0363))
                cent += p / 3; // 唐门心法
        me->set_hit_rate_3(cent);

        // 统计闪避率

        me->set_dodge_rate(me->get("?%"));
        me->set_dodge_rate_2(me->get("c?%"));

        // 统计免伤害

        me->set_anti_hurt(me->get("-*"));
        me->set_anti_hurt_2(me->get("-c*"));

        add = me->get("-*");
        cent = me->get("-*%");
        cent2 = me->get("-c*%");

        if (p = me->get_skill(SKILL_0325)) // 混元真气
        {
                p = p * 10 / 95;
                cent += p;
                cent2 += p;
        }
        if (p = me->get_skill(SKILL_0316))
                cent += p / 5; // 金刚不坏

        me->set_anti_hurt(add);
        me->set_anti_hurt_rate(cent);
        me->set_anti_hurt_rate_2(cent2);

        // 统计反伤害

        cent = 0;
        rand = 0;

        if (p = me->get_skill(SKILL_0317)) // 护体金罡
        {
                cent = 20 + p / 3;
                rand = 20 + p / 3;
        }
        me->set_hurt_rate(cent);
        me->set_hurt_rand(rand);

        cent = 0;
        rand = 0;

        if (p = me->get_skill(SKILL_0423)) // 天师符咒
        {
                cent = 20 + p / 3;
                rand = 40;
        }
        me->set_hurt_rate_2(cent);
        me->set_hurt_rand_2(rand);

        // 统计其它

        me->set_lucky(me->get("??%"));
        me->set_less_prop(me->get("#%"));

        cent = 0;
        if (p = me->get_skill(SKILL_0501))
                cent += p / 5 + 5; // 中医药理
        me->set_healing_rate(cent);
}
