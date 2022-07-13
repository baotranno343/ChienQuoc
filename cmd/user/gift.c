
// 函数：命令处理
int main(object me, string arg)
{
        int con, spi, str, cps, dex;
        int con0, spi0, str0, cps0, dex0;
        int con2, spi2, str2, cps2, dex2;
        int gift;

        if (arg == "upgrade")
        {
                if (me->get_upgrade_exp() < USER_EXP_D->get_level_exp(me->get_reincarnation(), me->get_level()))
                {
                        notify("Kinh nghiệm của bạn không đủ để thăng cấp.");
                        return 1;
                }
                if (gone_time(me->get_time("upgrade")) < 2)
                {
                        notify("Không nên thăng cấp quá nhanh");
                        return 1;
                }
                me->set_time("upgrade", time());
                me->Upgrade();
                return 1;
        }
        if (!arg || sscanf(arg, "%d %d %d %d %d", con, spi, str, cps, dex) != 5)
                return 1;

        con0 = me->get_con();
        spi0 = me->get_spi();
        str0 = me->get_str();
        cps0 = me->get_cps();
        dex0 = me->get_dex();

        if (con < con0 || spi < spi0 || str < str0 || cps < cps0 || dex < dex0)
                return 1; // 不能回调
        if (con == con0 && spi == spi0 && str == str0 && cps == cps0 && dex == dex0)
                return 1; // 没有改变

        con2 = con - con0;
        spi2 = spi - spi0;
        str2 = str - str0;
        cps2 = cps - cps0;
        dex2 = dex - dex0;

        //        if( con2 > 1 || spi2 > 1 || str2 > 1 || cps2 > 1 || dex2 > 1 ) return 1;    // 一点点来

        gift = con2 + spi2 + str2 + cps2 + dex2;

        if (gift > me->get_gift_point())
                return 1; // 点数过多
        if (gift < 0)
                return 1;

        me->add_gift_point(-gift);
        me->add_con_2(con2);
        me->add_spi_2(spi2);
        me->add_str_2(str2);
        me->add_cps_2(cps2);
        me->add_dex_2(dex2);

        USER_ENERGY_D->count_max_hp(me); // 更新，没有用 count_all_prop
        USER_ENERGY_D->count_max_mp(me);
        USER_ENERGY_D->count_cp(me); // cp/pp 影响 ap/dp, 所以放前
        USER_ENERGY_D->count_pp(me);
        USER_ENERGY_D->count_ap(me);
        USER_ENERGY_D->count_dp(me);
        USER_ENERGY_D->count_sp(me);

        return 1;
}

// 函数：道行重设
void init_gift_point(object me)
{
        int con, spi, str, cps, dex;
        int con2, spi2, str2, cps2, dex2;
        int gift, i, j, size;

        /*      con = me->get_con_1();
        spi = me->get_spi_1();
        str = me->get_str_1();
        cps = me->get_cps_1();
        dex = me->get_dex_1();  */

        con2 = me->get_con_2();
        spi2 = me->get_spi_2();
        str2 = me->get_str_2();
        cps2 = me->get_cps_2();
        dex2 = me->get_dex_2();

        gift = con2 + spi2 + str2 + cps2 + dex2;

        me->set_con_2(0);
        me->set_spi_2(0);
        me->set_str_2(0);
        me->set_cps_2(0);
        me->set_dex_2(0);
        me->add_gift_point(gift);

        USER_ENERGY_D->count_max_hp(me); // 更新，没有用 count_all_prop
        USER_ENERGY_D->count_max_mp(me);
        USER_ENERGY_D->count_cp(me); // cp/pp 影响 ap/dp, 所以放前
        USER_ENERGY_D->count_pp(me);
        USER_ENERGY_D->count_ap(me);
        USER_ENERGY_D->count_dp(me);
        USER_ENERGY_D->count_sp(me);
}
