
#include <ansi.h>

string status_color( int num, int max );

// 函数：命令处理
int main( object me, string arg )
{
        object who = me;
        string result, *prop = ({ });
        int hp, mp, ap, dp, cp, pp, sp;
        int i, size, len;

        if( is_player(me) ) 
        {
                notify( "Bạn không đủ quyền。" );
		return 1;
        }

        if( arg && !( who = find_any_char(arg) ) )
        {
                notify( "Không tìm thấy người này。" );
		return 1;
        }

        len = who->get_reincarnation();

        hp = who->get_hp();  mp = who->get_mp();  
        ap = who->get_ap();  dp = who->get_dp();  
        cp = who->get_cp();  pp = who->get_pp();  
        sp = who->get_sp();

        if( who->is_npc() )
                tell_user( me, "Trạng thái khí huyết：%s", who->get_name() );
        else    tell_user( me, "Trạng thái khí huyết：%s(%d) %s %s", who->get_name(), who->get_number(), 
                        len > 0 ? sprintf("[%d 转]", len) : "", get_invisible(who) ? "[Ẩn]" : "" );

        result = sprintf( "ＨＰ：%s%4d / %4d" NOR " (%+5d %+3d%%%%)  ", status_color( hp, who->get_max_hp() ), 
                hp, who->get_max_hp(), who->get_temp_hp("equip"), who->get_temp_hp("equip%") );
        result += sprintf( "Thể chất：%3d =%3d+%3d", who->get_con(), who->get_con_1(), who->get_con_2() );
        result += sprintf( "  Kinh nghiệm：(%d)%9d - %d", who->get_billion_exp(), who->get_exp(), who->get_upgrade_exp() );

        tell_user(me, result);

        result = sprintf( "ＭＰ：%s%4d / %4d" NOR " (%+5d %+3d%%%%)  ", status_color( mp, who->get_max_mp() ), 
                mp, who->get_max_mp(), who->get_temp_mp("equip"), who->get_temp_mp("equip%") );
        result += sprintf( "Tinh thần：%3d =%3d+%3d", who->get_spi(), who->get_spi_1(), who->get_spi_2() );
        result += sprintf( "  Tiềm năng：%10d", who->get_potential() );

        tell_user(me, result);

        result = sprintf( "Tấn công：%4d -%5d (%+5d     )  ", who->get_ap_0(), ap, who->get_temp_ap("equip") );
        result += sprintf( "Lực lượng：%3d =%3d+%3d", who->get_str(), who->get_str_1(), who->get_str_2() );
        result += sprintf( "  Đánh giá：%3d / %4d  Nguyên khí：%2d/%2d", who->get_level(), who->get_max_level(), who->get_yuan(), who->get_max_yuan() );

        tell_user(me, result);

        result = sprintf( "Phòng thủ：%4d -%5d (%+5d     )  ", who->get_dp_0(), dp, who->get_temp_dp("equip") );
        result += sprintf( "Độ bền：%3d =%3d+%3d", who->get_cps(), who->get_cps_1(), who->get_cps_2() );
        result += sprintf( "  Thuộc tính：%10d  Công đức：%4d.%d", who->get_gift_point(), who->get_bonus() / 10, who->get_bonus() % 10 );

        tell_user(me, result);

        result = sprintf( "Pháp công：%4d -%5d (%+5d %+3d%%%%)  ", who->get_cp_0(), cp, who->get_temp_cp("equip"), who->get_temp_cp("equip%") );
        result += sprintf( "Nhanh nhẹn：%3d =%3d+%3d", who->get_dex(), who->get_dex_1(), who->get_dex_2() );
        result += sprintf( "  Tiền mặt：%10d", who->get_cash() );

        tell_user(me, result);

        result = sprintf( "Phòng thủ：%4d -%5d (%+5d %+3d%%%%)  Tránh né：%4d (%+5d)  TIền gửi：%10d", 
                who->get_pp_0(), pp, who->get_temp_pp("equip"), who->get_temp_pp("equip%"), sp, who->get_temp_sp("equip"), who->get_savings() );

        tell_user(me, result);

        if( who->is_user() || who->is_boss() ) 
        {
                if( who->get_temp_hp("mascot") || who->get_temp_hp("hp18%") ) 
                        prop += ({ sprintf( "ＨＰ：%+d %+d%%", who->get_temp_hp("mascot"), who->get_temp_hp("hp18%") ) });
                if( who->get_temp_mp("mascot") || who->get_temp_mp("mp20%") ) 
                        prop += ({ sprintf( "ＭＰ：%+d %+d%%", who->get_temp_mp("mascot"), who->get_temp_mp("mp20%") ) });

                if( who->get_temp_ap("mascot") || who->get_temp_ap("ap10%") ) 
                        prop += ({ sprintf( "Công kích：%+d %+d%%", who->get_temp_ap("mascot"), who->get_temp_ap("ap10%") ) });
                if( who->get_temp_dp("mascot") || who->get_temp_dp("dp12%") ) 
                        prop += ({ sprintf( "Phòng thủ：%+d %+d%%", who->get_temp_dp("mascot"), who->get_temp_dp("dp12%") ) });
                if( who->get_temp_cp("mascot") || who->get_temp_cp("cp10%") ) 
                        prop += ({ sprintf( "Pháp công：%+d %+d%%", who->get_temp_cp("mascot"), who->get_temp_cp("cp10%") ) });
                if( who->get_temp_pp("mascot") || who->get_temp_pp("pp12%") ) 
                        prop += ({ sprintf( "pháp phòng：%+d %+d%%", who->get_temp_pp("mascot"), who->get_temp_pp("pp12%") ) });

                if( who->get_temp_sp("mascot") ) prop += ({ sprintf( "Tốc độ：%+5d", who->get_temp_sp("mascot") ) });

                if( who->get_hit_rate() ) prop += ({ sprintf( "Chính xác：%+3d%%", who->get_hit_rate() ) });
                if( who->get_hit_rate_2() ) prop += ({ sprintf( "Chính xác phép：%+3d%%", who->get_hit_rate_2() ) });
                if( who->get_hit_rate_3() ) prop += ({ sprintf( "Chính xác ám khí：%+3d%%", who->get_hit_rate_3() ) });

                if( who->get_dodge_rate() ) prop += ({ sprintf( "Né tránh：%+3d%%", who->get_dodge_rate() ) });
                if( who->get_dodge_rate_2() ) prop += ({ sprintf( "Né tránh pháp thuật：%+3d%%", who->get_dodge_rate_2() ) });

                if( who->get_poison() ) prop += ({ sprintf( "Trúng độc：%4d", who->get_poison() ) });
                if( who->get_poison_rate() ) prop += ({ sprintf( "Tăng cường độc tính：%+3d%%", who->get_poison_rate() ) });
                if( who->get_anti_poison() ) prop += ({ sprintf( "Kháng độc：%+3d%%", who->get_anti_poison() ) });
                if( who->get_lost_poison() ) prop += ({ sprintf( "Bỏ qua độc tố：%+3d%%", who->get_lost_poison() ) });

                if( who->get_anti_hurt() ) prop += ({ sprintf( "Miễn sát thương vật lí：%4d", who->get_anti_hurt() ) });
                if( who->get_anti_hurt_2() ) prop += ({ sprintf( "Miễn phép thuật tấn công：%4d", who->get_anti_hurt_2() ) });
                if( who->get_anti_hurt_rate() ) prop += ({ sprintf( "Miễn sát thương vật lí：%+3d%%", who->get_anti_hurt_rate() ) });
                if( who->get_anti_hurt_rate_2() ) prop += ({ sprintf( "Miễn phép thuật tấn công：%+3d%%", who->get_anti_hurt_rate_2() ) });

                if( who->get_hurt() ) prop += ({ sprintf( "Phản đòn：%4d", who->get_hurt() ) });
                if( who->get_hurt_rate() ) prop += ({ sprintf( "Tỷ số phản：%4d", who->get_hurt_rate() ) });
                if( who->get_hurt_rand() ) prop += ({ sprintf( "Phát sinh phản：%4d", who->get_hurt_rand() ) });
                if( who->get_hurt_2() ) prop += ({ sprintf( "Phản pháp thuật：%4d", who->get_hurt_2() ) });
                if( who->get_hurt_rate_2() ) prop += ({ sprintf( "Tỷ lệ chắn pháp thuật：%4d", who->get_hurt_rate_2() ) });
                if( who->get_hurt_rand_2() ) prop += ({ sprintf( "Chắn pháp phát sinh：%4d", who->get_hurt_rand_2() ) });

                if( who->get_absorb_hp() ) prop += ({ sprintf( "Hấp thụ máu：%+3d%%", who->get_absorb_hp() ) });
                if( who->get_absorb_mp() ) prop += ({ sprintf( "Hấp thụ pháp lực：%+3d%%", who->get_absorb_mp() ) });
                if( who->get_immunity() ) prop += ({ sprintf( "Miễn dịch：%+3d%%", who->get_immunity() ) });
                if( who->get_lucky() ) prop += ({ sprintf( "Vận khí：%+3d%%", who->get_lucky() ) });
                if( who->get_less_prop() ) prop += ({ sprintf( "Miễn kháng：%+3d%%", who->get_less_prop() ) });
        }

        size = sizeof(prop);  result = "";
        for( i = 0, len = 0; i < size; i ++ ) 
        {
                len += strlen( prop[i] ) + 3;
                if( len >= OUTPUT_WIDTH )
                {
                        len = strlen( prop[i] );
//                      tell_user(me, "%s", result);    // 注意：字串有 % 
//                      result = prop[i] + "  ";
                        result = sprintf( "%s\n%s  ", result, prop[i] );
                }
                else    result = sprintf( "%s%s  ", result, prop[i] );
        }
//      if( result != "" ) tell_user(me, "%s", result);    // 注意：字串有 % 
        if( result != "" ) tell_user(me, "%s", result);    // 注意：字串有 % 

        return 1;
}

// 函数：获取状态颜色
string status_color( int num, int max )
{
        int p = ( max > 0 ) ? num * 100 / max : 100;
        if( p > 100 ) return HIC;
        if( p >= 90 ) return HIG;
        if( p >= 60 ) return HIY;
        if( p >= 30 ) return YEL;
        if( p >= 10 ) return HIR;
        return RED;
}
