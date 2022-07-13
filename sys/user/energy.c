
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <cmd.h>
#include <ansi.h>

#define COUND_d "/sys/sys/count"

// 函数：生成二进制码
void SAVE_BINARY() {}

void count_hit_rate(object me);

void count_ap(object me);

// 函数：统计最大ＨＰ
void count_max_hp(object me)
{
        object *equip, pet;
        int hp, i, p, add, cent, milli, rate;
        string *nTmp;

        me->init_temp_hp_dbase();

        if (get_effect(me, EFFECT_CHAR_KING_2))
        {
                hp = me->set_temp_hp("king", 1);
                me->set_max_hp(hp);
                me->set_hp(hp);
                return;
        }

        switch (me->get_fam_name())
        {
        default:
                hp = me->set_temp_hp("con", me->get_con() * COUND_d->get_1(0, 0) / COUND_d->get_2(0, 0));
                break;
        case "Đào Hoa Nguyên":
                hp = me->set_temp_hp("con", me->get_con() * COUND_d->get_1(0, 1) / COUND_d->get_2(0, 1));
                break;
        case "Thục Sơn":
                hp = me->set_temp_hp("con", me->get_con() * COUND_d->get_1(0, 2) / COUND_d->get_2(0, 2));
                break;
        case "Cấm Vệ Quân":
                hp = me->set_temp_hp("con", me->get_con() * COUND_d->get_1(0, 3) / COUND_d->get_2(0, 3));
                break;
        case "Đường Môn":
                hp = me->set_temp_hp("con", me->get_con() * COUND_d->get_1(0, 4) / COUND_d->get_2(0, 4));
                break;
        case "Mao Sơn":
                hp = me->set_temp_hp("con", me->get_con() * COUND_d->get_1(0, 5) / COUND_d->get_2(0, 5));
                break;
        case "Côn Luân":
                hp = me->set_temp_hp("con", me->get_con() * COUND_d->get_1(0, 6) / COUND_d->get_2(0, 6));
                break;
        case "Vân Mộng Cốc":
                hp = me->set_temp_hp("con", me->get_con() * COUND_d->get_1(0, 7) / COUND_d->get_2(0, 7));
                break;
        }
        rate = 0;
        if (p = me->get_mascot("hp"))
                hp += me->set_temp_hp("mascot", p * 150);

        add = 0;
        cent = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("hp") + equip[i]->get("hp+") + equip[i]->get("hpp") + equip[i]->get("hp2"))
                                add += p;
                        if (p = equip[i]->get("hp%") + equip[i]->get("hp%+") + equip[i]->get("hp3"))
                                cent += p;
                        if (p = equip[i]->get("hp‰") + equip[i]->get("hp‰+"))
                                milli += p;
                }
        rate = rate + me->set_temp_hp("equip%", cent) + me->set_temp_hp("equip‰", milli) / 10;
        hp += me->set_temp_hp("equip", add);
        add = 0;

        if (p = me->get_skill(SKILL_0109))
                add += p * 5; // 经络学说

        if (p = me->get_skill(SKILL_0319))
                add += p * 6; // 周天运转
        else if (p = me->get_skill(SKILL_0329))
                add += p * 4; // 周天运转
        else if (p = me->get_skill(SKILL_0349))
                add += p * 5; // 磨练

        if (p = me->get_skill(SKILL_0375))
                add += p * 6; // 强化周天运转（桃花）
        if (p = me->get_skill(SKILL_0334))
                add += p * 4; // 强化周天运转（Thục Sơn）
        if (p = me->get_skill(SKILL_0354))
                add += p * 6; // 强化磨练
        if (p = me->get_skill(SKILL_0464))
                add += p * 4; // 强化顺天法咒
        if (p = me->get_skill(SKILL_0501))
                add += p * 6; // 中医药理
        if (p = me->get_skill(SKILL_0543))
                add += p * 4; // 强化中医药理
        if (p = me->get_skill(SKILL_0384))
                add += p * 3; // 强化踏雪无痕
        if (p = me->get_skill(SKILL_0442))
                add += p * 5; // 强化金罡法咒
        if (p = me->get_skill(SKILL_0445))
                add += p * 15 / 10; // 强化大乘道法
        hp += me->set_temp_hp("skill", add);

        if (get_effect(me, EFFECT_USER_HP))
                rate = rate + me->set_temp_hp("hp18%", 18);

        if (get_effect(me, EFFECT_RENSHEN))
        {
                if (me->get_save("rs_hp"))
                        hp += me->get_save("rs_hp");
                else
                        hp += 600;
        }

        if (get_effect(me, EFFECT_CHAR_KING))
                rate = rate + me->set_temp_hp("king%", 45);

        if (get_effect(me, EFFECT_1808))
                rate = rate + 10;
        if (get_effect(me, EFFECT_CHAR_POWERUP3))
                hp += me->get_save("05014"); // 强体术
        if (p = me->get_skill(0404))
                rate += p; // 健身
        if (p = me->get_skill(0438))
                rate += 1.5 * p;
        rate += me->get_2("jiguan.hp");
        rate += me->get_2("jiguan_huyenthu.hp");
        if (me->get_save_2("marry_fashion.time") > time())
        {
                rate += me->get_save_2("marry_fashion.hp");
        }
        hp = hp + hp * rate / 100;
        pet = me->get("showbeast");
        if (objectp(pet))
                hp += pet->get("sk74220");
        hp += me->get_2("magic_card.hp");         //Thẻ Biến Thân
        if (mapp(me->get_2("suit_effect.maxhp"))) //套装
        {
                nTmp = keys(me->get_2("suit_effect.maxhp"));
                for (i = 0, p = sizeof(nTmp); i < p; i++)
                {
                        hp += me->get_2(sprintf("suit_effect.maxhp.%s", nTmp[i]));
                }
        }
        if (get_effect(me, EFFECT_USER_EXCHANGE_HP))
                hp += me->set_temp_hp("exchange_hp", 200);
        if (i = me->get_save_2("online_rank.level")) //修为等级
                hp += 5 * i;
        hp += me->get_2("thucuoi.hp");
        //-------------------------------------------------------------------------------------------------------
        hp += me->get_2("shenshou.hp");
        //-------------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------------

        //-------------------------------------------------------------------------------------------------------
        me->set_max_hp(hp);
}

// 函数：统计最大ＭＰ
void count_max_mp(object me)
{
        object *equip;
        int mp, i, p, add, cent, milli, rate;
        string *nTmp;

        me->init_temp_mp_dbase();

        if (get_effect(me, EFFECT_CHAR_KING_2))
        {
                mp = me->set_temp_mp("king", 1);
                me->set_max_mp(mp);
                me->set_mp(mp);
                return;
        }

        switch (me->get_fam_name())
        {
        default:
                mp = me->set_temp_mp("spi", me->get_spi() * COUND_d->get_1(1, 0) / COUND_d->get_2(1, 0));
                break;
        case "Đào Hoa Nguyên":
                mp = me->set_temp_mp("spi", me->get_spi() * COUND_d->get_1(1, 1) / COUND_d->get_2(1, 1));
                break;
        case "Thục Sơn":
                mp = me->set_temp_mp("spi", me->get_spi() * COUND_d->get_1(1, 2) / COUND_d->get_2(1, 2));
                break;
        case "Cấm Vệ Quân":
                mp = me->set_temp_mp("spi", me->get_spi() * COUND_d->get_1(1, 3) / COUND_d->get_2(1, 3));
                break;
        case "Đường Môn":
                mp = me->set_temp_mp("spi", me->get_spi() * COUND_d->get_1(1, 4) / COUND_d->get_2(1, 4));
                break;
        case "Mao Sơn":
                mp = me->set_temp_mp("spi", me->get_spi() * COUND_d->get_1(1, 5) / COUND_d->get_2(1, 5));
                break;
        case "Côn Luân":
                mp = me->set_temp_mp("spi", me->get_spi() * COUND_d->get_1(1, 6) / COUND_d->get_2(1, 6));
                break;
        case "Vân Mộng Cốc":
                mp = me->set_temp_mp("spi", me->get_spi() * COUND_d->get_1(1, 7) / COUND_d->get_2(1, 7));
                break;
        }
        rate = 0;
        if (p = me->get_mascot("mp"))
                mp += me->set_temp_mp("mascot", p * 200);

        add = 0;
        cent = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("mp") + equip[i]->get("mp+") + equip[i]->get("mpp") + equip[i]->get("mp2"))
                                add += p;
                        if (p = equip[i]->get("mp%") + equip[i]->get("mp%+"))
                                cent += p;
                        if (p = equip[i]->get("mp‰") + equip[i]->get("mp‰+"))
                                milli += p;
                }
        rate = rate + me->set_temp_mp("equip%", cent) + me->set_temp_mp("equip‰", milli) / 10;
        mp += me->set_temp_mp("equip", add);

        add = 0;

        if (p = me->get_skill(SKILL_0401))
                add += p * 5; // 道家学说
        if (p = me->get_skill(SKILL_0325))
                add += p * 2; // 混元真气
        if (p = me->get_skill(SKILL_0333))
                add += p * 25 / 10; // 强化混元真气
        if (p = me->get_skill(0368))
                add += p * 16 / 10; // 潜隐心法
        if (p = me->get_skill(0383))
                add += p * 30 / 10; // 强化潜隐心法
        if (p = me->get_skill(0418))
                add += p * 4; // 大乘道法
        else if (p = me->get_skill(SKILL_0421))
                add += p * 4; // 大乘道法
        if (p = me->get_skill(0445))
                add += p * 6; // 强化大乘道法
        if (p = me->get_skill(SKILL_0465))
                add += p * 5; // 强化玄学正道
        if (p = me->get_skill(SKILL_0542))
                add += p * 4; // 强化医术
        if (p = me->get_skill(SKILL_0511))
                add += p * 3; // 道家学说
        mp += me->set_temp_mp("skill", add);

        if (get_effect(me, EFFECT_USER_MP))
                rate = rate + me->set_temp_mp("mp20%", 20);

        if (get_effect(me, EFFECT_CHAR_KING))
                rate = rate + me->set_temp_mp("king%", 45);
        if (get_effect(me, EFFECT_1809))
                rate = rate + 10;
        if (p = me->get_skill(0405))
                rate += p; // 冥思
        mp = mp + mp * rate / 100;
        mp += me->get_2("magic_card.mp");         //Thẻ Biến Thân
        if (mapp(me->get_2("suit_effect.maxmp"))) //套装
        {
                nTmp = keys(me->get_2("suit_effect.maxmp"));
                for (i = 0, p = sizeof(nTmp); i < p; i++)
                {
                        mp += me->get_2(sprintf("suit_effect.maxmp.%s", nTmp[i]));
                }
        }
        if (get_effect(me, EFFECT_USER_EXCHANGE_MP))
                mp += me->set_temp_mp("exchange_mp", 200);
        mp += me->get_2("thucuoi.mp");
        //-------------------------------------------------------------------------------------------------------
        mp += me->get_2("shenshou.mp");
        //-------------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------------
        /*   if ( me->get_save_2("marry_fashion.time") > time() )
        {
			rate += me->get_save_2("marry_fashion.mp");
			mp = mp + mp * rate/100;
		}*/
        //-------------------------------------------------------------------------------------------------------
        me->set_max_mp(mp);
}

// 函数：统计物理攻击
void count_ap(object me)
{
        object *equip, pet, item;
        int ap, i, p, add, cent, milli, rate;
        string *nTmp;

        me->init_temp_ap_dbase();
        // Code khóa nv khi bug chỉ số
        if (!me->get_save("khoanhanvat"))
        {
                if (me->get_ap_0() > 30000)
                {
                        me->set_save("khoanhanvat", 1);
                        QUIT_CMD->main(me, "");
                }
        }
        switch (me->get_fam_name())
        {
        default:
                ap = me->set_temp_ap("str", me->get_str() * COUND_d->get_1(2, 0) / COUND_d->get_2(2, 0));
                break;
        case "Đào Hoa Nguyên":
                ap = me->set_temp_ap("str", me->get_str() * COUND_d->get_1(2, 1) / COUND_d->get_2(2, 1));
                break;
        case "Thục Sơn":
                ap = me->set_temp_ap("str", me->get_str() * COUND_d->get_1(2, 2) / COUND_d->get_2(2, 2));
                break;
        case "Cấm Vệ Quân":
                ap = me->set_temp_ap("str", me->get_str() * COUND_d->get_1(2, 3) / COUND_d->get_2(2, 3));
                break;
        case "Đường Môn":
                ap = me->set_temp_ap("str", me->get_str() * COUND_d->get_1(2, 4) / COUND_d->get_2(2, 4));
                //  ap += me->get_dex() / 2;
                break;
        case "Mao Sơn":
                ap = me->set_temp_ap("str", me->get_str() * COUND_d->get_1(2, 5) / COUND_d->get_2(2, 5));
                break;
        case "Côn Luân":
                ap = me->set_temp_ap("str", me->get_str() * COUND_d->get_1(2, 6) / COUND_d->get_2(2, 6));
                break;
        case "Vân Mộng Cốc":
                ap = me->set_temp_ap("str", me->get_str() * COUND_d->get_1(2, 7) / COUND_d->get_2(2, 7));
                break;
        }
        rate = 0;
        if (p = me->get_mascot("ap"))
                ap += me->set_temp_ap("mascot", p * 16);

        if (get_effect(me, EFFECT_CHAR_WOUND))
                rate = rate + me->set_temp_ap("wound%", -20); // 负伤

        add = 0;
        cent = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("ap") + equip[i]->get("ap+") + equip[i]->get("app") + equip[i]->get("ap3") + equip[i]->get("ap2"))
                                add += p;
                        if (p = equip[i]->get("ap%") + equip[i]->get("ap%+"))
                                cent += p;
                        if (p = equip[i]->get("ap‰") + equip[i]->get("ap‰+"))
                                milli += p;
                }
        rate = rate + me->set_temp_ap("equip%", cent) + me->set_temp_ap("equip‰", milli) / 10;
        ap += me->set_temp_ap("equip", add);

        switch (me->get_weapon_code())
        {
        default:
                if (p = me->get_skill(SKILL_0111))
                        ap += me->set_temp_ap("0111", p); // 基本拳脚
                if (p = me->get_skill(SKILL_0211))
                        ap += me->set_temp_ap("0211", p); // 太古神拳
                if (p = me->get_skill(SKILL_0371))
                        ap += me->set_temp_ap("0371", p * 4); // 强化太古神拳
                break;

        case THROWING:
                if (p = me->get_skill(SKILL_0161))
                        ap += me->set_temp_ap("0161", p * 3 / 2); // 暗器投射
                if (p = me->get_skill(SKILL_0261))
                        ap += me->set_temp_ap("0261", p * 14 / 10); // 漫天花雨
                if (p = me->get_skill(SKILL_0381))
                        ap += me->set_temp_ap("0381", p * 20 / 10); // 强化漫天花雨
                break;                                              // 注意改 fight_d.c

        case BLADE:
                if (p = me->get_skill(SKILL_0121))
                        ap += me->set_temp_ap("0121", p); // 基本刀法
                if (p = me->get_skill(SKILL_0221))
                        rate += p * 2 / 10; // 天罗刀法
                if (p = me->get_skill(SKILL_0331))
                        ap += me->set_temp_ap("0331", p * 3); // 强化天罗刀法
                break;

        case SPEAR:
                if (p = me->get_skill(SKILL_0141))
                        ap += me->set_temp_ap("0141", p); // 基本枪法
                                                          //                if( p = me->get_skill(SKILL_0241) ) ap += me->set_temp_ap( "0241", p * 6 / 5 );    // 霸王枪法
                if (p = me->get_skill(SKILL_0349))
                        ap += p * 3; // 磨练
                if (p = me->get_skill(SKILL_0354))
                        ap += p * 4; // 强化磨练
                break;

        case STICK:
                if (p = me->get_skill(SKILL_0151))
                        ap += me->set_temp_ap("0151", p); // 基本棍法
                                                          //                if( p = me->get_skill(SKILL_0251) ) ap += me->set_temp_ap( "0251", p * 6 / 5 );    // 疯魔棍法
                if (p = me->get_skill(SKILL_0349))
                        ap += p * 3; // 磨练
                if (p = me->get_skill(SKILL_0354))
                        ap += p * 4; // 强化磨练
                if (p = me->get_skill(SKILL_0251))
                        rate += p * 2 / 10;
                break;
        }

        //      if( get_effect(me, EFFECT_USER_AP) ) rate = rate + me->set_temp_ap( "ap10%", 10 ) ;
        if (get_effect(me, EFFECT_USER_AP))
                rate = rate + me->set_temp_ap("ap10", me->get_save("ap10#"));
        if (get_effect(me, EFFECT_CHAR_POWERUP))
                ap += me->get_save("05011"); // 银针渡厄

        if (get_effect(me, EFFECT_CHAR_KING))
                rate = rate + me->set_temp_ap("king%", 45);

        if (get_effect(me, EFFECT_CHAR_5215))
                ap += me->set_temp_ap("5215", -me->get_save("5215")); // 软筋散

        if (get_effect(me, EFFECT_03484))
                ap += me->set_temp_ap("3484", me->get_save("3484_1")); // 破釜沉舟

        if (me->get_perform("03191"))
        {
                ap += me->get_perform("03191");
                rate += 10;
        }
        if (me->get_perform("03192"))
                rate -= 50;
        rate += me->get_2("jiguan.ap");
        rate += me->get_2("jiguan_huyenthu.ap");

        ap = ap + ap * rate / 100;
        /*	if ( rate = me->get_2("thucuoi.ap") )//;
	{
	ap = ap + rate;
	}*/
        ap += me->get_2("thucuoi.ap");
        pet = me->get("showbeast");
        if (objectp(pet))
                ap += pet->get("sk74216");
        ap += me->get_2("magic_card.ap");      //Thẻ Biến Thân
        if (mapp(me->get_2("suit_effect.ap"))) //套装
        {
                nTmp = keys(me->get_2("suit_effect.ap"));
                for (i = 0, p = sizeof(nTmp); i < p; i++)
                {
                        ap += me->get_2(sprintf("suit_effect.ap.%s", nTmp[i]));
                }
        }
        if (get_effect(me, EFFECT_USER_EXCHANGE_AP))
                ap += me->set_temp_ap("exchange_ap", 100);
        //-------------------------------------------------------------------------------------------------------
        if (item = me->get_equip(HAND_TYPE))
                if (item->get("time_item"))
                {
                        rate = item->get("ap_power");
                        ap = ap + ap * rate / 100;
                        ap = ap + item->get("ap_power_2");
                }
        //-------------------------------------------------------------------------------------------------------
        if (me->get_vip() == 1) //vip包
                ap += 50;
        //--------------------------------------------------------------------------------------------------
        /*******************************名人堂加成*************************************/
        if (me->get("add_mingren_power"))
                ap = ap + me->get_ap() * 2 / 100;
        /******************************名人堂加成*************************************/
        //-------------------------------------------------------------------------------------------------------
        ap += me->get_2("shenshou.ap");
        //-------------------------------------------------------------------------------------------------------
        /*		if ( me->get_save_2("marry_fashion.time") > time() )
        {
			rate += me->get_save_2("marry_fashion.ap");
			ap = ap + ap * rate / 100;
		}*/
        //-------------------------------------------------------------------------------------------------------
        if (me->have_title("P001"))
                ap += 10;
        if (me->have_title("P002"))
                ap += 20;
        if (me->have_title("P003"))
                ap += 30;
        if (me->have_title("P004"))
                ap += 40;
        if (me->have_title("P005"))
                ap += 150;
        if (me->have_title("P006"))
                ap += 200;
        if (me->have_title("P007"))
                ap += 250;
        if (me->have_title("P008"))
                ap += 300;
        if (me->have_title("P009"))
                ap += 350;
        if (me->have_title("P010"))
                ap += 450;
        if (me->have_title("P011"))
                ap += 600;

        //-------------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------------
        // if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191") && me->get_hp() <= me->get_max_hp() * 9 / 10)
        // {
        //         ap += me->get_ap() / 25;
        // } // 90%
        // if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191") && me->get_hp() <= me->get_max_hp() * 8 / 10)
        // {
        //         ap += me->get_ap() / 25;
        // } // 80%
        // if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191") && me->get_hp() <= me->get_max_hp() * 7 / 10)
        // {
        //         ap += me->get_ap() / 25;
        // } // 70%
        // if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191") && me->get_hp() <= me->get_max_hp() * 6 / 10)
        // {
        //         ap += me->get_ap() / 25;
        // } // 60%
        if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191") && me->get_hp() <= me->get_max_hp() * 6 / 10)
        {
                ap += me->get_ap() / 20;
        } // 50%
        if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191") && me->get_hp() <= me->get_max_hp() * 5 / 10)
        {
                ap += me->get_ap() / 20;
        } // 40%
        if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191") && me->get_hp() <= me->get_max_hp() * 4 / 10)
        {
                ap += me->get_ap() / 20;
        } // 30%
        if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191") && me->get_hp() <= me->get_max_hp() * 3 / 10)
        {
                ap += me->get_ap() / 20;
        } // 20%
        if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191") && me->get_hp() <= me->get_max_hp() * 2 / 10)
        {
                ap += me->get_ap() / 20;
        } // 10%
          //-------------------------------------------------------------------------------------------------------
        if (me->get_fam_name() == "Đào Hoa Nguyên" && me->get_perform("03191"))
        {
                me->set_ap_dhn(ap);
        }
        else
        {
                me->set_ap(ap);
        }
}

// 函数：统计物理防御
void count_dp(object me)
{
        object *equip, pet, item;
        int dp, i, p, add, cent, milli, rate;
        string *nTmp;

        me->init_temp_dp_dbase();
        // Code khóa nv khi bug chỉ số
        if (!me->get_save("khoanhanvat"))
        {
                if (me->get_dp_0() > 30000)
                {
                        me->set_save("khoanhanvat", 1);
                        QUIT_CMD->main(me, "");
                }
        }
        switch (me->get_fam_name())
        {
        default:
                dp = me->set_temp_dp("cps", me->get_cps() * COUND_d->get_1(3, 0) / COUND_d->get_2(3, 0));
                break;
        case "Đào Hoa Nguyên":
                dp = me->set_temp_dp("cps", me->get_cps() * COUND_d->get_1(3, 1) / COUND_d->get_2(3, 1));
                break;
        case "Thục Sơn":
                dp = me->set_temp_dp("cps", me->get_cps() * COUND_d->get_1(3, 2) / COUND_d->get_2(3, 2));
                break;
        case "Cấm Vệ Quân":
                dp = me->set_temp_dp("cps", me->get_cps() * COUND_d->get_1(3, 3) / COUND_d->get_2(3, 3));
                break;
        case "Đường Môn":
                dp = me->set_temp_dp("cps", me->get_cps() * COUND_d->get_1(3, 4) / COUND_d->get_2(3, 4));
                break;
        case "Mao Sơn":
                dp = me->set_temp_dp("cps", me->get_cps() * COUND_d->get_1(3, 5) / COUND_d->get_2(3, 5));
                break;
        case "Côn Luân":
                dp = me->set_temp_dp("cps", me->get_cps() * COUND_d->get_1(3, 6) / COUND_d->get_2(3, 6));
                break;
        case "Vân Mộng Cốc":
                dp = me->set_temp_dp("cps", me->get_cps() * COUND_d->get_1(3, 7) / COUND_d->get_2(3, 7));
                break;
        }
        rate = 0;
        if (p = me->get_mascot("dp"))
                dp += me->set_temp_dp("mascot", p * 20);

        if (get_effect(me, EFFECT_CHAR_WOUND))
                rate = rate + me->set_temp_dp("wound%", -20); // 负伤

        if (get_effect(me, EFFECT_CHAR_ADD_DP))
                rate = rate + me->set_temp_dp("03251%", 10 + (me->get_skill(316) - 5) / 11 * 2); // 金钟罩(＋防御)

        add = 0;
        cent = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("dp") + equip[i]->get("dp+") + equip[i]->get("dpp") + equip[i]->get("dp3") + equip[i]->get("dp2"))
                                add += p;
                        if (p = equip[i]->get("dp‰") + equip[i]->get("dp‰+"))
                                milli += p;
                }
        rate = rate + me->set_temp_dp("equip‰", milli) / 10;
        dp += me->set_temp_dp("equip", add);

        add = 0;

        switch (me->get_weapon_code())
        {
        default:
                if (p = me->get_skill(SKILL_0212))
                        add += p * 3; // 拳脚招架
                if (p = me->get_skill(SKILL_0372))
                        add += p * 3; // 强化拳脚招架
                break;

        case THROWING:
                if (p = me->get_skill(SKILL_0212))
                        add += p * 3; // 拳脚招架
                if (p = me->get_skill(SKILL_0363))
                        add += p * 4 / 5; // 唐门心法
                if (p = me->get_skill(SKILL_0382))
                        add += p * 20 / 10; // 强化唐门毒经
                break;

        case BLADE:
        case SWORD:
                if (p = me->get_skill(SKILL_0222))
                        add += p * 11 / 10; // 刀剑格挡
                if (p = me->get_skill(SKILL_0335))
                        add += p * 15 / 10; // 强化刀剑格挡
                break;

        case SPEAR:
        case STICK:
                //   		if( p = me->get_skill(SKILL_0252) ) add += p * 4 / 5;    // 棍法格挡
                if (p = me->get_skill(SKILL_0242))
                        add += p * 3 / 5;
                if (p = me->get_skill(SKILL_0353))
                        add += p * 3; // 强化枪棍步法
                break;
        }
        if (p = me->get_skill(SKILL_0202))
                add += p; // 招架之术

        if (p = me->get_skill(SKILL_0348))
                add += p * 3 / 5; // 兵法
        if (p = me->get_skill(SKILL_0463))
                add += p * 3; // 强化逆天法咒
        if (p = me->get_skill(SKILL_0417))
                add += p / 4; // 神打

        if (p = me->get_skill(SKILL_0501))
                add += p * 9 / 10; // 中医药理
        if (p = me->get_skill(SKILL_0543))
                add += p * 20 / 10; // 强化中医药理
        if (p = me->get_skill(SKILL_0443))
                add += p * 20 / 10; // 强化乾坤挪移
        if (p = me->get_skill(SKILL_0545))
                add += p * 2; // 强化奇门遁甲
        dp += me->set_temp_dp("skill", add);

        if (get_effect(me, EFFECT_USER_DP))
                dp += me->set_temp_dp("03291", me->get_save("03291#"));
        if (get_effect(me, EFFECT_02614))
                dp += me->set_temp_dp("02614", me->get_save("02614"));

        if (get_effect(me, EFFECT_CHAR_HALFGOD2))
                dp += me->set_temp_dp("04171", me->get_save("04171")); // 神打
        if (get_effect(me, EFFECT_CHAR_ARMORFALL))
                dp += me->get_save_2("pf.armorfall"); // 蚀甲
        if (get_effect(me, EFFECT_03484))
                dp += me->set_temp_dp("3484", me->get_save("3484_2")); // 破釜沉舟

        if (get_effect(me, EFFECT_CHAR_KING))
                rate = rate + me->set_temp_dp("king%", 45);
        if (get_effect(me, EFFECT_2123_ARMORFALL))
                rate = rate + me->set_temp_dp("02123", -10);
        if (get_effect(me, EFFECT_1811))
                rate = rate + 10;
        if (me->get_perform("03191"))
                rate -= 50;
        if (me->get_perform("03192"))
                rate += 35;
        rate += me->get_2("jiguan.dp");
        rate += me->get_2("jiguan_huyenthu.dp");
        if (me->get_save_2("marry_fashion.time") > time())
        {
                rate += me->get_save_2("marry_fashion.dp");
        }
        dp = dp + dp * rate / 100;
        /*	if ( rate = me->get_2("thucuoi.dp") )//;
	{
	dp = dp + rate;
	}*/
        dp += me->get_2("thucuoi.dp");
        pet = me->get("showbeast");
        if (objectp(pet))
                dp += pet->get("sk74218");
        dp += me->get_2("magic_card.dp");      //Thẻ Biến Thân
        if (mapp(me->get_2("suit_effect.dp"))) //套装
        {
                nTmp = keys(me->get_2("suit_effect.dp"));
                for (i = 0, p = sizeof(nTmp); i < p; i++)
                {
                        dp += me->get_2(sprintf("suit_effect.dp.%s", nTmp[i]));
                }
        }
        //-------------------------------------------------------------------------------------------------------
        if (item = me->get_equip(HAND_TYPE))
                if (item->get("time_item"))
                {
                        dp = dp + item->get("dp_power_2");
                }
        //-------------------------------------------------------------------------------------------------------
        if (me->get_vip() == 1) //vip包
                dp += 50;
        if (me->get_title_code() == "A018")
        { //	真假虎王活动奖励
                dp += 10;
        }
        /*	if(me->get_title_code() == "Y020") {	//	真假虎王活动奖励
		dp += 50;
	}
	if(me->get_title_code() == "Y025") {	//	真假虎王活动奖励
		dp += 200;
	}*/
        //-------------------------------------------------------------------------------------------------------
        dp += me->get_2("shenshou.dp");
        //-------------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------------

        //-------------------------------------------------------------------------------------------------------
        me->set_dp(dp);
}

// 函数：统计法术攻击
void count_cp(object me)
{
        object *equip, pet, item;
        int cp, i, p, add, cent, milli, rate;
        string *nTmp;

        me->init_temp_cp_dbase();
        // Code khóa nv khi bug chỉ số
        if (!me->get_save("khoanhanvat"))
        {
                if (me->get_cp_0() > 30000)
                {
                        me->set_save("khoanhanvat", 1);
                        QUIT_CMD->main(me, "");
                }
        }
        switch (me->get_fam_name())
        {
        default:
                cp = me->set_temp_cp("spi", me->get_spi() * COUND_d->get_1(4, 0) / COUND_d->get_2(4, 0));
                break;
        case "Đào Hoa Nguyên":
                cp = me->set_temp_cp("spi", me->get_spi() * COUND_d->get_1(4, 1) / COUND_d->get_2(4, 1));
                break;
        case "Thục Sơn":
                cp = me->set_temp_cp("spi", me->get_spi() * COUND_d->get_1(4, 2) / COUND_d->get_2(4, 2));
                break;
        case "Cấm Vệ Quân":
                cp = me->set_temp_cp("spi", me->get_spi() * COUND_d->get_1(4, 3) / COUND_d->get_2(4, 3));
                break;
        case "Đường Môn":
                cp = me->set_temp_cp("spi", me->get_spi() * COUND_d->get_1(4, 4) / COUND_d->get_2(4, 4));
                break;
        case "Mao Sơn":
                cp = me->set_temp_cp("spi", me->get_spi() * COUND_d->get_1(4, 5) / COUND_d->get_2(4, 5));
                break;
        case "Côn Luân":
                cp = me->set_temp_cp("spi", me->get_spi() * COUND_d->get_1(4, 6) / COUND_d->get_2(4, 6));
                break;
        case "Vân Mộng Cốc":
                cp = me->set_temp_cp("spi", me->get_spi() * COUND_d->get_1(4, 7) / COUND_d->get_2(4, 7));
                break;
        }
        rate = 0;
        if (me->get_weapon_code() == SWORD && (p = me->get_skill(SKILL_0231)))
                cp += me->set_temp_cp("0231", p * 5 / 2); // 飞仙剑法
        if (me->get_weapon_code() == SWORD && (p = me->get_skill(SKILL_0332)))
                cp += me->set_temp_cp("0332", p * 3);             // 强化飞仙剑法
        cp += me->set_temp_cp("0402", me->get_skill(SKILL_0402)); // 诵经

        //     cp += me->set_temp_cp("0422", me->get_skill(SKILL_0422) * 2); // 阴阳五行
        cp += me->set_temp_cp("0441", me->get_skill(SKILL_0441) * 2); // 强化金仙符咒
        cp += me->set_temp_cp("0444", me->get_skill(SKILL_0444) * 3); // 强化阴阳五行
                                                                      //        cp += me->set_temp_ap( "0281", me->get_skill(SKILL_0281) );    		// 御风心法
        cp += me->set_temp_ap("0541", me->get_skill(SKILL_0541) * 2); // 强化御风心法
        if (p = me->get_mascot("cp"))
                cp += me->set_temp_cp("mascot", p * 15);

        add = 0;
        cent = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("cp") + equip[i]->get("cp+") + equip[i]->get("cpp") + equip[i]->get("cp3") + equip[i]->get("cp2"))
                                add += p;
                        if (p = equip[i]->get("cp%") + equip[i]->get("cp%+"))
                                cent += p;
                        if (p = equip[i]->get("cp‰") + equip[i]->get("cp‰+"))
                                milli += p;
                }
        rate = rate + me->set_temp_cp("equip%", cent) + me->set_temp_cp("equip‰", milli) / 10;
        cp += me->set_temp_cp("equip", add);

        switch (me->get_weapon_code())
        {
        case SWORD:
                if (p = me->get_skill(SKILL_0131))
                        cp += me->set_temp_cp("0131", p); // 基本剑法
                break;
        }

        if (p = me->get_skill(SKILL_0271))
                cp += me->set_temp_cp("0271", p * 2); // 降魔法咒
        if (p = me->get_skill(SKILL_0461))
                cp += me->set_temp_cp("0461", p * 4); // 强化降魔法咒
        if (p = me->get_perform("05016#"))
                cp += me->set_temp_cp("05016#", p); //

        //      if( get_effect(me, EFFECT_USER_CP) ) rate = rate + me->set_temp_cp( "cp10%", 10 ) ;
        if (get_effect(me, EFFECT_USER_CP))
                rate = rate + me->set_temp_cp("cp10", me->get_save("cp10#"));
        if (get_effect(me, EFFECT_CHAR_POWERUP2))
                cp += me->get_save("05012"); // 金针渡厄

        if (get_effect(me, EFFECT_CHAR_KING))
                rate = rate + me->set_temp_cp("king%", 45);
        if (p = me->get_skill(SKILL_0422))
                rate += p * 2 / 10;
        rate += me->get_2("jiguan.cp");
        rate += me->get_2("jiguan_huyenthu.cp");
        cp = cp + cp * rate / 100;
        /*	if ( rate = me->get_2("thucuoi.cp") )//;
	{
	cp = cp + rate;
	}*/
        cp += me->get_2("thucuoi.cp");
        pet = me->get("showbeast");
        if (objectp(pet))
                cp += pet->get("sk74217");
        cp += me->get_2("magic_card.cp");      //Thẻ Biến Thân
        if (mapp(me->get_2("suit_effect.cp"))) //套装
        {
                nTmp = keys(me->get_2("suit_effect.cp"));
                for (i = 0, p = sizeof(nTmp); i < p; i++)
                {
                        cp += me->get_2(sprintf("suit_effect.cp.%s", nTmp[i]));
                }
        }
        if (get_effect(me, EFFECT_USER_EXCHANGE_CP))
                cp += me->set_temp_cp("exchange_cp", 100);
        //-------------------------------------------------------------------------------------------------------
        if (item = me->get_equip(HAND_TYPE))
                if (item->get("time_item"))
                {
                        rate = item->get("cp_power");
                        cp = cp + cp * rate / 100;
                        cp = cp + item->get("cp_power_2");
                }
        //-------------------------------------------------------------------------------------------------------
        if (me->get_vip() == 1) //vip包
                cp += 50;
        /*******************************名人堂加成*************************************/
        if (me->get("add_mingren_power"))
                cp = cp + me->get_cp() * 2 / 100;
        /******************************名人堂加成*************************************/
        //-------------------------------------------------------------------------------------------------------
        cp += me->get_2("shenshou.cp");
        //-------------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------------

        if (me->have_title("P001"))
                cp += 10;
        if (me->have_title("P002"))
                cp += 20;
        if (me->have_title("P003"))
                cp += 30;
        if (me->have_title("P004"))
                cp += 40;
        if (me->have_title("P005"))
                cp += 150;
        if (me->have_title("P006"))
                cp += 200;
        if (me->have_title("P007"))
                cp += 250;
        if (me->have_title("P008"))
                cp += 300;
        if (me->have_title("P009"))
                cp += 350;
        if (me->have_title("P010"))
                cp += 450;
        if (me->have_title("P011"))
                cp += 600;

        //-------------------------------------------------------------------------------------------------------
        /*	if ( me->get_save_2("marry_fashion.time") > time() )
        {
			rate += me->get_save_2("marry_fashion.cp");
			cp = cp + cp * rate / 100;
		}*/
        //-------------------------------------------------------------------------------------------------------
        /*        if ( me->get_save_2("marry_fashion.time") > time() )
        {
			rate += me->get_save_2("marry_fashion.cp");
			cp = cp + cp * rate/100;
		}*/
        //-------------------------------------------------------------------------------------------------------

        me->set_cp(cp);
}

// 函数：统计法术防御
void count_pp(object me)
{

        object *equip, pet;
        int pp, i, p, add, cent, milli, rate;
        string *nTmp;

        me->init_temp_pp_dbase();
        // Code khóa nv khi bug chỉ số
        if (!me->get_save("khoanhanvat"))
        {
                if (me->get_pp_0() > 30000)
                {
                        me->set_save("khoanhanvat", 1);
                        QUIT_CMD->main(me, "");
                }
        }
        switch (me->get_fam_name())
        {
        default:
                pp = me->set_temp_pp("spi", me->get_spi() * COUND_d->get_1(5, 0) / COUND_d->get_2(5, 0));
                break;
        case "Đào Hoa Nguyên":
                pp = me->set_temp_pp("spi", me->get_spi() * COUND_d->get_1(5, 1) / COUND_d->get_2(5, 1));
                break;
        case "Thục Sơn":
                pp = me->set_temp_pp("spi", me->get_spi() * COUND_d->get_1(5, 2) / COUND_d->get_2(5, 2));
                break;
        case "Cấm Vệ Quân":
                pp = me->set_temp_pp("spi", me->get_spi() * COUND_d->get_1(5, 3) / COUND_d->get_2(5, 3));
                break;
        case "Đường Môn":
                pp = me->set_temp_pp("spi", me->get_spi() * COUND_d->get_1(5, 4) / COUND_d->get_2(5, 4));
                break;
        case "Mao Sơn":
                pp = me->set_temp_pp("spi", me->get_spi() * COUND_d->get_1(5, 5) / COUND_d->get_2(5, 5));
                break;
        case "Côn Luân":
                pp = me->set_temp_pp("spi", me->get_spi() * COUND_d->get_1(5, 6) / COUND_d->get_2(5, 6));
                break;
        case "Vân Mộng Cốc":
                pp = me->set_temp_pp("spi", me->get_spi() * COUND_d->get_1(5, 7) / COUND_d->get_2(5, 7));
                break;
        }
        rate = 0;
        if (p = me->get_skill(0418))
                pp += me->set_temp_pp("skill", p * 2);

        pp += me->set_temp_pp("0325", me->get_skill(SKILL_0325));           // 混元真气
        pp += me->set_temp_pp("0333", me->get_skill(SKILL_0333) * 15 / 10); // 强化混元真气
        pp += me->set_temp_pp("0403", me->get_skill(SKILL_0403));           // 禅定
        pp += me->set_temp_pp("0373", me->get_skill(SKILL_0373) * 3);       // 强化金刚不坏
        pp += me->set_temp_pp("0511", me->get_skill(SKILL_0511) * 9 / 10);  // 阴阳五行
        pp += me->set_temp_pp("0425", me->get_skill(0425));                 // 乾坤挪移
        pp += me->set_temp_pp("0355", me->get_skill(0355) * 4);             // 强化兵法
        pp += me->set_temp_pp("0385", me->get_skill(0385) * 30 / 10);       // 强化唐门心法
        pp += me->set_temp_pp("0462", me->get_skill(0462) * 30 / 10);       // 强化道法神通
        pp += me->set_temp_pp("0465", me->get_skill(0465) * 30 / 10);       // 强化玄学正道
        pp += me->set_temp_pp("0542", me->get_skill(0542) * 20 / 10);       // 强化医术
        pp += me->set_temp_pp("0545", me->get_skill(0545) * 2);             // 强化奇门遁甲
        if (p = me->get_mascot("pp"))
                pp += me->set_temp_pp("mascot", p * 20);

        if (get_effect(me, EFFECT_CHAR_ADD_PP))
                rate = rate + me->set_temp_pp("03252%", 20); // 护体金光(＋法防)

        add = 0;
        cent = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("pp") + equip[i]->get("pp+") + equip[i]->get("ppp") + equip[i]->get("pp3") + equip[i]->get("pp2"))
                                add += p;
                        if (p = equip[i]->get("pp%") + equip[i]->get("pp%+"))
                                cent += p;
                        if (p = equip[i]->get("pp‰") + equip[i]->get("pp‰+"))
                                milli += p;
                }
        rate = rate + me->set_temp_pp("equip%", cent) + me->set_temp_pp("equip‰", milli) / 10;
        pp += me->set_temp_pp("equip", add);

        if (get_effect(me, EFFECT_USER_PP))
                pp += me->set_temp_pp("03292", me->get_save("03292#"));

        if (get_effect(me, EFFECT_CHAR_ARMORFALL))
                pp += me->get_save_2("pf.armorfall2"); // 蚀甲

        if (get_effect(me, EFFECT_CHAR_KING))
                rate = rate + me->set_temp_pp("king%", 45);
        if (get_effect(me, EFFECT_ITEM_9165))
                rate = rate + me->set_temp_pp("9165", me->get_save("9165#"));
        rate += me->get_2("jiguan.pp");
        rate += me->get_2("jiguan_huyenthu.pp");
        pp = pp + pp * rate / 100;
        /*	if ( rate = me->get_2("thucuoi.pp") )//;#
	{
	pp = pp + rate;
	}*/
        pp += me->get_2("thucuoi.pp");
        pet = me->get("showbeast");
        if (objectp(pet))
                pp += pet->get("sk74219");
        pp += me->get_2("magic_card.pp"); //Thẻ Biến Thân
        if (mapp(me->get_2("suit_effect.pp")))
        {
                nTmp = keys(me->get_2("suit_effect.pp"));
                for (i = 0, p = sizeof(nTmp); i < p; i++)
                        pp += me->get_2(sprintf("suit_effect.pp.%s", nTmp[i]));
        }
        if (me->get_vip() == 1) //vip包
                pp += 50;
        if (me->get_title_code() == "A018")
        { //	真假虎王活动奖励
                pp += 10;
        }
        /*	if(me->get_title_code() == "Y020") {	//	真假虎王活动奖励
		pp += 50;
	}
	if(me->get_title_code() == "Y025") {	//	真假虎王活动奖励
		pp += 200;
	}*/
        //-------------------------------------------------------------------------------------------------------
        pp += me->get_2("shenshou.pp");
        //-------------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------------
        if (me->get_save_2("marry_fashion.time") > time())
        {
                rate += me->get_save_2("marry_fashion.pp");
                pp = pp + pp * rate / 100;
        }
        //-------------------------------------------------------------------------------------------------------
        me->set_pp(pp);
}

// 函数：统计腾挪躲闪
void count_sp(object me)
{
        object *equip;
        int sp, i, p, add, cent, rate;

        me->init_temp_sp_dbase();

        switch (me->get_fam_name())
        {
        default:
                sp = me->set_temp_sp("dex", me->get_dex() * COUND_d->get_1(6, 0) / COUND_d->get_2(6, 0));
                break;
        case "Đào Hoa Nguyên":
                sp = me->set_temp_sp("dex", me->get_dex() * COUND_d->get_1(6, 1) / COUND_d->get_2(6, 1));
                break;
        case "Thục Sơn":
                sp = me->set_temp_sp("dex", me->get_dex() * COUND_d->get_1(6, 2) / COUND_d->get_2(6, 2));
                break;
        case "Cấm Vệ Quân":
                sp = me->set_temp_sp("dex", me->get_dex() * COUND_d->get_1(6, 3) / COUND_d->get_2(6, 3));
                break;
        case "Đường Môn":
                sp = me->set_temp_sp("dex", me->get_dex() * COUND_d->get_1(6, 4) / COUND_d->get_2(6, 4));
                break;
        case "Mao Sơn":
                sp = me->set_temp_sp("dex", me->get_dex() * COUND_d->get_1(6, 5) / COUND_d->get_2(6, 5));
                break;
        case "Côn Luân":
                sp = me->set_temp_sp("dex", me->get_dex() * COUND_d->get_1(6, 6) / COUND_d->get_2(6, 6));
                break;
        case "Vân Mộng Cốc":
                sp = me->set_temp_sp("dex", me->get_dex() * COUND_d->get_1(6, 7) / COUND_d->get_2(6, 7));
                break;
        }
        rate = 0;
        if (add = me->get_mascot("sp"))
                sp += me->set_temp_sp("mascot", add * 15);

        add = 0;
        cent = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("sp") + equip[i]->get("sp+") + equip[i]->get("sp2"))
                                add += p;
                        //              if( p = equip[i]->get("sp%") + equip[i]->get("sp%+") ) cent += p;
                }
        //      sp += sp * me->set_temp_sp( "equip%", cent ) / 100;
        sp += me->set_temp_sp("equip", add);

        if (p = me->get_skill(SKILL_0324))
                sp += me->set_temp_sp("skill", p * 3 / 2); // 踏雪无痕
        else if (p = me->get_skill(SKILL_0364))
                sp += me->set_temp_sp("skill", p * 3); // 踏雪无痕

        //        if( get_effect(me, EFFECT_CHAR_MOVE) ) sp += me->set_temp_sp( "03641", me->get_save("03641") );    // 踏雪无痕
        if (get_effect(me, EFFECT_USER_SP))
                rate = rate + me->set_temp_sp("02421", me->get_save("02421#")); // 踏雪无痕
        if (get_effect(me, EFFECT_1810))
                rate = rate + 10;
        rate += me->get_2("jiguan.sp");
        rate += me->get_2("jiguan_huyenthu.sp");
        sp = sp + sp * rate / 100;
        /*	if ( rate = me->get_2("thucuoi.sp") )//;
	{
	sp = sp + rate;
	}*/
        sp += me->get_2("thucuoi.sp");
        sp += me->get_2("magic_card.sp"); //Thẻ Biến Thân
                                          //-------------------------------------------------------------------------------------------------------
        sp += me->get_2("shenshou.sp");
        //-------------------------------------------------------------------------------------------------------
        //-------------------------------------------------------------------------------------------------------
        /*        if ( me->get_save_2("marry_fashion.time") > time() )
        {
			rate += me->get_save_2("marry_fashion.sp");
			sp = sp + sp * rate/100;
		}*/
        //-------------------------------------------------------------------------------------------------------
        me->set_sp(sp);
        count_hit_rate(me);
        count_ap(me);
}

// 函数：统计抗毒率/御毒率
void count_poison(object me)
{
        object *equip;
        int i, p, cent1, cent2, cent3, cent4;

        cent1 = 0;
        cent2 = 0;
        cent3 = 0;
        cent4 = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("@%") + equip[i]->get("@%+"))
                                cent1 += p;
                        if (p = equip[i]->get("X@%") + equip[i]->get("X@%+"))
                                cent2 += p;
                        if (p = equip[i]->get("-@%") + equip[i]->get("-@%+"))
                                cent3 += p;
                        if (p = equip[i]->get("/%") + equip[i]->get("/%+"))
                                cent4 += p;
                }
        me->set_poison_rate(cent1);
        me->set_anti_poison(cent2);
        me->set_lost_poison(cent3);
        me->set_immunity(cent4);
}

// 函数：统计吸取气血/法力
void count_absorb(object me)
{
        object *equip;
        int i, p, cent1, cent2;

        cent1 = 0;
        cent2 = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("hp*") + equip[i]->get("hp*+"))
                                cent1 += p;
                        if (p = equip[i]->get("mp*") + equip[i]->get("mp*+"))
                                cent2 += p;
                }
        me->set_absorb_hp(cent1);
        me->set_absorb_mp(cent2);
}

// 函数：统计命中率
void count_hit_rate(object me)
{
        object *equip;
        int i, p, cent1, cent2, cent3, double, double2;
        string fam;

        cent1 = 0;
        cent2 = 0;
        cent3 = 0;
        double = 0;
        double2 = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("!%") + equip[i]->get("!%+"))
                                cent1 += p;
                        if (p = equip[i]->get("c!%") + equip[i]->get("c!%+"))
                                cent2 += p;
                        if (p = equip[i]->get("t!%") + equip[i]->get("t!%+"))
                                cent3 += p;
                        if (p = equip[i]->get("double"))
                        {
                                double += p;
                                double2 += p;
                        }
                        if (p = equip[i]->get("double2"))
                        {
                                double += p;
                                double2 += p;
                        }
                }
        cent1 = cent1 / 100;
        if (p = me->get_skill(0437))
        {

                cent3 += p * 1;
                cent2 += p * 1;
                cent1 += p * 1;
        }

        //-----------------------------------------------------------------------------------------------------
        if (me->get_save_2("marry_fashion.time") > time())
        {
                p = me->get_save_2("marry_fashion.double");
                double += p;
                double2 += p;
        }
        //-----------------------------------------------------------------------------------------------------
        /*	if(me->get_title_code() == "Y020") {	//	真假虎王活动奖励
		double += 100;
		double2+= 100;
	}
	if(me->get_title_code() == "Y025") {	//	真假虎王活动奖励
		double += 300;
		double2+= 300;
	}*/
        if (p = me->get_2("jiguan.do"))
        {
                double += p;
                double2 += p;
        }
        if (p = me->get_2("jiguan_huyenthu.do"))
        {
                double += p;
                double2 += p;
        }
        if (p = me->get_skill(0365))
        {
                cent3 = cent3 + p * 2 / 10;
                double += p * 10;
        }

        switch (me->get_weapon_code())
        {
        default:
                if (p = me->get_skill(0374)) //强化护体金罡
                {
                        cent1 = cent1 + p * 9 / 100;
                }
                break;
        case BLADE:

                if (p = me->get_skill(SKILL_0221))
                        cent1 += (p * 1 / 10); // 天罗刀法

                break;
        case SPEAR:
                if (p = me->get_skill(SKILL_0241))
                {
                        double += (p * 15);  // 天罗刀法
                        double2 += (p * 15); // 天罗刀法
                }

                if (p = me->get_skill(0241))
                        cent1 += p * 1 / 10;
                if (p = me->get_skill(0351)) //强化霸王枪法
                {
                        cent1 = cent1 + p * 9 / 100;
                }
                break;

        case STICK:
                if (p = me->get_skill(0352)) //强化疯魔棍法
                {
                        cent1 = cent1 + p * 9 / 100;
                }
                break;
        }
        if (p = me->get_sp())
        {
                double += p / 2;
                double2 += p / 2;
        }
        if (p = me->get_skill(0222)) //刀剑格挡
        {
                double += p * 5;
                double2 += p * 5;
        }
        if (p = me->get_skill(0335)) //强化刀剑格挡
        {
                double += p * 8;
                double2 += p * 8;
        }
        if (p = me->get_skill(0421)) //大乘道法
        {
                double2 += p * 5;
        }
        if (p = me->get_skill(0531)) //迷魂决
        {
                double2 += p * 5;
        }
        if (p = me->get_skill(0544)) //强化迷魂决
        {
                double2 += p * 9;
        }
        if (p = me->get_skill(0435))
        {
                double += p * 100;
                double2 += p * 100;
        }

        double += 200;
        double2 += 200;
        cent1 += me->get_2("magic_card.hit_rate");
        cent2 += me->get_2("magic_card.hit_rate1");
        me->set_hit_rate(cent1);
        me->set_hit_rate_2(cent2);
        me->set_hit_rate_3(cent3);
        double += me->get_2("suit_effect.double_rate");
        double2 += me->get_2("suit_effect.double_rate");
        if (double > 5000)
                double = 5000;
        if (double2 > 5000)
                double2 = 5000;
        me->set_double_rate(double);
        me->set_double_rate_2(double2);

        fam = me->get_fam_name();
        if (fam == "Côn Luân" || fam == "Vân Mộng Cốc" || fam == "Thục Sơn")
                send_user(me, "%c%c%w", 0x3d, 29, me->get_double_rate_2());
        else
                send_user(me, "%c%c%w", 0x3d, 29, me->get_double_rate());
}

// 函数：统计闪避率
void count_dodge_rate(object me)
{
        object *equip;
        int i, p, cent1, cent2;

        cent1 = 0;
        cent2 = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("?%") + equip[i]->get("?%+"))
                                cent1 += p;
                        if (p = equip[i]->get("c?%") + equip[i]->get("c?%+"))
                                cent2 += p;
                }
        if (p = me->get_skill(SKILL_0104))
                cent1 += p * 15; // 腾挪躲闪
        if (p = me->get_skill(0434))
                cent1 += p * 150; // 腾挪躲闪    	// 腾挪躲闪
        me->set_dodge_rate(cent1 / 100);
        me->set_dodge_rate_2(cent2 / 100);
}

// 函数：统计免伤害
void count_anti_hurt(object me)
{
        object *equip;
        int i, p, add1, add2, cent1, cent2;

        add1 = 0;
        add2 = 0;
        cent1 = 0;
        cent2 = 0;
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("-*") + equip[i]->get("-*+"))
                                add1 += p;
                        if (p = equip[i]->get("-c*") + equip[i]->get("-c*+"))
                                add2 += p;
                        if (p = equip[i]->get("-*%") + equip[i]->get("-*%+"))
                                cent1 += p;
                        if (p = equip[i]->get("-c*%") + equip[i]->get("-c*%+"))
                                cent2 += p;
                }

        if (p = me->get_skill(SKILL_0316))
                cent1 += p / 5; // 金刚不坏
        me->set_anti_hurt(add1);
        me->set_anti_hurt_2(add2);
        me->set_anti_hurt_rate(cent1);
        me->set_anti_hurt_rate_2(cent2);
}

// 函数：统计反伤害
void count_hurt(object me)
{
        /*	
        int p, rate1, rand1, rate2, rand2;

        rate1 = 0;  rand1 = 0;
        rate2 = 0;  rand2 = 0;

        if( me->get_perform(PF_FLAG_03173) && ( p = me->get_skill(SKILL_0317) ) )    // 护体金罡
        {
                rate1 = me->set_temp_other( "03173 rate", 10 + p / 5 );
                rand1 = me->set_temp_other( "03173 rand", 20 + p / 3 );
        }
        me->set_hurt_rate(rate1);  me->set_hurt_rand(rand1);
        me->set_hurt_rate_2(rate2);  me->set_hurt_rand_2(rand2);
*/
}

// 函数：统计其它
void count_other(object me)
{
        object *equip, item2;
        int i, p, cent1, cent2, hurt1, heal1, trilieu;

        cent1 = 0;
        cent2 = 0;
        hurt1 = 0;
        heal1 = 0;
        item2 = me->get_equip(FAMILY_TYPE);
        equip = me->get_all_equip();
        for (i = 0; i < MAX_EQUIP; i++)
                if (equip[i] && equip[i]->get_lasting() >= 100)
                {
                        if (i == 2 && get_effect(me, EFFECT_NO_WEAPON))
                                continue;
                        if (i == 3 && get_effect(me, EFFECT_NO_CLOTH))
                                continue;
                        if (p = equip[i]->get("??%") + equip[i]->get("??%+"))
                                cent1 += p;
                        if (p = equip[i]->get("#%") + equip[i]->get("#%+"))
                                cent2 += p;
                        if (p = equip[i]->get("cp+@"))
                                hurt1 += p; //加法术伤害效果
                        if (p = equip[i]->get("heal+@"))
                                heal1 += p; //加法术治疗效果
                        if (p = equip[i]->get("trilieu"))
                                trilieu += p;
                }
        me->set_lucky(cent1);
        me->set_less_prop(cent2);
        me->set("add_magic_damage", hurt1);
        me->set("add_magic_heal", heal1);
        me->set("trilieu", trilieu);
        if (me->get_2("suit_effect.trilieu"))
        {
                me->add("trilieu", me->get_2("suit_effect.trilieu"));
        }
        cent1 = 0;
        if (p = me->get_skill(0436))
                cent1 += p * 4;
        if (p = me->get_save("mayman.ben"))
                cent1 += p;
        me->set_healing_rate(cent1);

        if (me->get_save_2("chuyensinh.score"))
        {
                if (item2)
                {
                        item2->set_tinvat_desc(sprintf(HIR "Chuyển Sinh: %d", me->get_save_2("chuyensinh.score")));
                        send_user(me, "%c%d%c", 0x31, getoid(item2), 0);
                }
        }
}

// 函数：统计所有属性
void count_all_prop(object me)
{
        USER_ENERGY_D->count_max_hp(me);
        USER_ENERGY_D->count_max_mp(me);
        USER_ENERGY_D->count_cp(me); // cp/pp 影响 ap/dp, 所以放前
        USER_ENERGY_D->count_pp(me);
        USER_ENERGY_D->count_ap(me);
        USER_ENERGY_D->count_dp(me);
        USER_ENERGY_D->count_sp(me);

        USER_ENERGY_D->count_poison(me);
        USER_ENERGY_D->count_absorb(me);
        USER_ENERGY_D->count_hit_rate(me);
        USER_ENERGY_D->count_dodge_rate(me);
        USER_ENERGY_D->count_anti_hurt(me);
        USER_ENERGY_D->count_hurt(me);
        USER_ENERGY_D->count_other(me);
}

// 函数：统计最大元气
void count_max_yuan(object me)
{
        switch (me->get_fam_name())
        {
        default:
                me->set_max_yuan(1);
                break;

        case "Đào Hoa Nguyên":
        case "Cấm Vệ Quân":
                me->set_max_yuan(12);
                break;
        }
}
