
#include <ansi.h>
#include <cmd.h>
#include <equip.h>
#include <skill.h>
#include <task.h>

// 函数:生成二进制码
void SAVE_BINARY() { }

private void do_reincarnation_init( object who );

// 函数:对话处理
void do_look( object who, object me )
{
        string cmd = sprintf( "talk %x# life.?\n", getoid(me) );
        send_user( who, "%c%s", ':', me->get_name() + ":\n" + who->get_name() + " Ái khanh, ngươi tìm ta có chuyện gì?\n" 
                ESC "Ta muốn tự sát.\n" + cmd +
                ESC "Cáo lui.\nCLOSE\n" );
}

// 函数:转生处理
void do_reincarnation( object who, object me, string arg )
{
        object *inv;
        string cmd, name, result;
        int life, level, level2, point;
        int flag, i, size;

        life = who->get_reincarnation();
        level = who->get_level();

        flag = 0;

        if( level<120 )
        {
                send_user( who, "%c%s", ':', me->get_name() + ":\nCấp bậc của ngươi vẫn chưa đủ 120." );
                return;
        }

        if( who->get_pk() )
        {
                send_user( who, "%c%s", ':', me->get_name() + ":\nNgươi tàn sát quá nhiều người, ta không thể giúp ngươi tự sát." );
                return;
        }
        if( who->get_potential()>=1000 )
        {
                send_user( who, "%c%s", ':', me->get_name() + ":\nĐiểm tiềm năng của ngươi vẫn còn 1000 điểm trở lên, không thể sự sát." );
                return;
        }
        if( who->get_reincarnation()>=2 )
        {
                send_user( who, "%c%s", ':', me->get_name() + ":\nTa không đủ năng lực giúp ngươi tự sát đâu." );
                return;
        }        
        if( objectp( who->get("soldier") ) || arrayp( who->get("zombie") ) )
        {
                send_user( who, "%c%s", ':', me->get_name() + ":\nNgươi không muốn xa rời thú cưng của ngươi ư ? Ta không thể giúp ngươi được rồi." );
                return;
        }

        inv = who->get_all_equip();
        for( i = 0, size = sizeof(inv); i < size; i ++ ) if( inv[i] && inv[i]->get_equip_type()!=FAMILY_TYPE)
        {
                send_user( who, "%c%s", ':', me->get_name() + ":\nNgươi muốn tự sát, trước hết tháo hết đồ đang mặc xuống rồi nói." );
                return;
        }

        if( who->get_fam_name() == "" )
        {
                send_user( who, "%c%s", ':', me->get_name() + ":\nNgươi còn chưa gia nhập Môn phái, ta không thể giúp ngươi được." );
                return;
        }

        if( !arg || arg == "" || arg == "!" )
        {
                name = who->get_fam_name();

                flag = 0;

                if( !arg || arg == "" ) switch( name )
                {
        case FAMILY_1 : if(     who->get_skill(0211) < level2
                        ||      who->get_skill(0212) < level2
                        ||      who->get_skill(0316) < level2
                        ||      who->get_skill(0317) < level2
                        ||      who->get_skill(0319) < level2 )
                                flag = 1;
                        break;

        case FAMILY_2 : if(     who->get_skill(0221) < level2
                        ||      who->get_skill(0231) < level2
                        ||      who->get_skill(0222) < level2
//                        ||      who->get_skill(0232) < level2
//                        ||      who->get_skill(0324) < level2
                        ||      who->get_skill(0325) < level2
                        ||      who->get_skill(0329) < level2 )
                                flag = 1;
                        break;

        case FAMILY_3 : if(     who->get_skill(0241) < level2
                        ||      who->get_skill(0251) < level2
                        ||      who->get_skill(0242) < level2
//                        ||      who->get_skill(0252) < level2
                        ||      who->get_skill(0348) < level2
                        ||      who->get_skill(0349) < level2 )
                                flag = 1;
                        break;

        case FAMILY_4 : if(     who->get_skill(0261) < level2
                        ||      who->get_skill(0363) < level2
                        ||      who->get_skill(0364) < level2
                        ||      who->get_skill(0365) < level2
                        ||      who->get_skill(0368) < level2 )
                                flag = 1;
                        break;

        case FAMILY_5 : if(     who->get_skill(0271) < level2
//                        ||      who->get_skill(0411) < level2
                        ||      who->get_skill(0413) < level2
                        ||      who->get_skill(0414) < level2
                        ||      who->get_skill(0417) < level2
                        ||      who->get_skill(0418) < level2 )
                                flag = 1;
                        break;

        case FAMILY_6 : if(     who->get_skill(0421) < level2
                        ||      who->get_skill(0422) < level2
                        ||      who->get_skill(0423) < level2
                        ||      who->get_skill(0424) < level2
                        ||      who->get_skill(0425) < level2 )
//                        ||      who->get_skill(0429) < level2 )
                                flag = 1;
                        break;

        case FAMILY_7 : if(     who->get_skill(0281) < level2
                        ||      who->get_skill(0501) < level2
                        ||      who->get_skill(0511) < level2
//                        ||      who->get_skill(0513) < level2
//                        ||      who->get_skill(0521) < level2
                        ||      who->get_skill(0531) < level2
                        ||      who->get_skill(0591) < level2 )
                                flag = 1;
                        break;

              default : 
                        break;
                }
                if( flag )
                {
                        cmd = sprintf( "talk %x# life.!\n", getoid(me) );
                        send_user( who, "%c%s", ':', "\nNgươi muốn tự sát không?\n"
                                ESC "Ta muốn tự sát.\n" + cmd +
                                ESC "Ta còn phải suy nghĩ\nCLOSE\n" );
                        return;
                }

                switch( life )    // 记录转生前技能(师门)
                {
               case 0 : switch( name )
                        {
                        case FAMILY_1 : // Đào Hoa Nguyên
                                        who->set_skill_0( 0211, who->get_skill(0211) );
                                        who->set_skill_0( 0212, who->get_skill(0212) );
                                        who->set_skill_0( 0316, who->get_skill(0316) );
                                        who->set_skill_0( 0317, who->get_skill(0317) );
                                        who->set_skill_0( 0319, who->get_skill(0319) );
                                        break;

                        case FAMILY_2 : // Thục Sơn
                                        who->set_skill_0( 0221, who->get_skill(0221) );
                                        who->set_skill_0( 0231, who->get_skill(0231) );
                                        who->set_skill_0( 0222, who->get_skill(0222) );
                                        who->set_skill_0( 0232, who->get_skill(0232) );
                                        who->set_skill_0( 0324, who->get_skill(0324) );
                                        who->set_skill_0( 0325, who->get_skill(0325) );
                                        who->set_skill_0( 0329, who->get_skill(0329) );
                                        break;

                        case FAMILY_3 : // Cấm Vệ Quân
                                        who->set_skill_0( 0241, who->get_skill(0241) );
                                        who->set_skill_0( 0251, who->get_skill(0251) );
                                        who->set_skill_0( 0242, who->get_skill(0242) );
                                        who->set_skill_0( 0252, who->get_skill(0252) );
                                        who->set_skill_0( 0348, who->get_skill(0348) );
                                        who->set_skill_0( 0349, who->get_skill(0349) );
                                        break;

                        case FAMILY_4 : // Đường Môn
                                        who->set_skill_0( 0261, who->get_skill(0261) );
                                        who->set_skill_0( 0363, who->get_skill(0363) );
                                        who->set_skill_0( 0364, who->get_skill(0364) );
                                        who->set_skill_0( 0365, who->get_skill(0364) );
                                        who->set_skill_0( 0368, who->get_skill(0368) );
                                        break;

                        case FAMILY_5 : // Mao Sơn
                                        who->set_skill_0( 0271, who->get_skill(0271) );
                                        who->set_skill_0( 0411, who->get_skill(0411) );
                                        who->set_skill_0( 0413, who->get_skill(0413) );
                                        who->set_skill_0( 0414, who->get_skill(0414) );
                                        who->set_skill_0( 0417, who->get_skill(0417) );
                                        who->set_skill_0( 0418, who->get_skill(0418) );
                                        break;

                        case FAMILY_6 : // Côn Luân
                                        who->set_skill_0( 0421, who->get_skill(0421) );
                                        who->set_skill_0( 0422, who->get_skill(0422) );
                                        who->set_skill_0( 0423, who->get_skill(0423) );
                                        who->set_skill_0( 0424, who->get_skill(0424) );
                                        who->set_skill_0( 0425, who->get_skill(0425) );
//                                        who->set_skill_0( 0429, who->get_skill(0429) );
                                        break;

                        case FAMILY_7 : // Vân Mộng Cốc
                                        who->set_skill_0( 0281, who->get_skill(0281) );
                                        who->set_skill_0( 0501, who->get_skill(0501) );
                                        who->set_skill_0( 0511, who->get_skill(0511) );
                                        who->set_skill_0( 0513, who->get_skill(0513) );
//                                        who->set_skill_0( 0521, who->get_skill(0521) );
//                                        who->set_skill_0( 0531, who->get_skill(0531) );
                                        who->set_skill_0( 0591, who->get_skill(0591) );
                                        break;
                        }
                        break;

               case 1 : switch( name )
                        {
                        case FAMILY_1 : // Đào Hoa Nguyên
                                        who->set_skill_1( 0211, who->get_skill(0211) );
                                        who->set_skill_1( 0212, who->get_skill(0212) );
                                        who->set_skill_1( 0316, who->get_skill(0316) );
                                        who->set_skill_1( 0317, who->get_skill(0317) );
                                        who->set_skill_1( 0319, who->get_skill(0319) );
                                        break;

                        case FAMILY_2 : // Thục Sơn
                                        who->set_skill_1( 0221, who->get_skill(0221) );
                                        who->set_skill_1( 0231, who->get_skill(0231) );
                                        who->set_skill_1( 0222, who->get_skill(0222) );
                                        who->set_skill_1( 0232, who->get_skill(0232) );
                                        who->set_skill_1( 0324, who->get_skill(0324) );
                                        who->set_skill_1( 0325, who->get_skill(0325) );
                                        who->set_skill_1( 0329, who->get_skill(0329) );
                                        break;

                        case FAMILY_3 : // Cấm Vệ Quân
                                        who->set_skill_1( 0241, who->get_skill(0241) );
                                        who->set_skill_1( 0251, who->get_skill(0251) );
                                        who->set_skill_1( 0242, who->get_skill(0242) );
                                        who->set_skill_1( 0252, who->get_skill(0252) );
                                        who->set_skill_1( 0348, who->get_skill(0348) );
                                        who->set_skill_1( 0349, who->get_skill(0349) );
                                        break;

                        case FAMILY_4 : // Đường Môn
                                        who->set_skill_1( 0261, who->get_skill(0261) );
                                        who->set_skill_1( 0363, who->get_skill(0363) );
                                        who->set_skill_1( 0364, who->get_skill(0364) );
                                        who->set_skill_1( 0365, who->get_skill(0364) );
                                        who->set_skill_1( 0368, who->get_skill(0368) );
                                        break;

                        case FAMILY_5 : // Mao Sơn
                                        who->set_skill_1( 0271, who->get_skill(0271) );
                                        who->set_skill_1( 0411, who->get_skill(0411) );
                                        who->set_skill_1( 0413, who->get_skill(0413) );
                                        who->set_skill_1( 0414, who->get_skill(0414) );
                                        who->set_skill_1( 0417, who->get_skill(0417) );
                                        who->set_skill_1( 0418, who->get_skill(0418) );
                                        break;

                        case FAMILY_6 : // Côn Luân
                                        who->set_skill_1( 0421, who->get_skill(0421) );
                                        who->set_skill_1( 0422, who->get_skill(0422) );
                                        who->set_skill_1( 0423, who->get_skill(0423) );
                                        who->set_skill_1( 0424, who->get_skill(0424) );
                                        who->set_skill_1( 0425, who->get_skill(0425) );
//                                        who->set_skill_1( 0429, who->get_skill(0429) );
                                        break;

                        case FAMILY_7 : // Vân Mộng Cốc
                                        who->set_skill_1( 0281, who->get_skill(0281) );
                                        who->set_skill_1( 0501, who->get_skill(0501) );
                                        who->set_skill_1( 0511, who->get_skill(0511) );
                                        who->set_skill_1( 0513, who->get_skill(0513) );
                                        who->set_skill_1( 0521, who->get_skill(0521) );
                                        who->set_skill_1( 0531, who->get_skill(0531) );
                                        who->set_skill_1( 0591, who->get_skill(0591) );
                                        break;
                        }
                        break;

              default : break;
                }
                
                switch( life )
                {
               case 0 : who->set_reincarnation(1);
                        result = "Lần đầu tiên";
                        point = 60 + 10 * who->get_gift_point_times();
                        break;

               case 1 : who->set_reincarnation(2);
                        result = "Lần thứ hai";
                        point = 260 + 10 * who->get_gift_point_times();
                        break;

              default : break;
                }                
                send_user( get_scene_object_2(who, USER_TYPE), "%c%d%c%c", 0x24, getoid(who), who->get_reincarnation(), who->get_reincarnation() );

                who->set_gift_point(point);

                who->set_con_2(0);
                who->set_spi_2(0);
                who->set_str_2(0);
                who->set_cps_2(0);
                who->set_dex_2(0);

                USER_INVENTORY_D->send_max_carry_flag(who);

                do_reincarnation_init(who);    // 转生处理(初始化)

                result = sprintf( HIY "Bạn %s đã tự sát thành công!", result );
                send_user( who, "%c%s", '!', result );
                write_user(who, result);

                return;
        }
        else
        {
                cmd = sprintf( "talk %x# life\n", getoid(me) );
                send_user( who, "%c%s", ':', sprintf( "\nNgươi muốn tự sát?"
                        "Nếu tự sát ngươi sẽ mất đi tất cả võ công."
                        "Bất quá sau khi ngươi tự sát, thăng cấp sẽ nhận được tiềm năng lớn hơn."
                        "Vậy ngươi còn muốn tự sát %d nữa không?\n", life + 1 ) +
                        ESC "Xin hãy giúp ta chuyển sang kiếp khác.\n" + cmd +
                        ESC "Ta còn phải suy nghĩ\nCLOSE\n" );
        }
}

// 函数:转生处理(初始化)
private void do_reincarnation_init( object who )
{
        mapping skls;
        string *name, file;
        int skill, level, i, size;

        if( mapp( skls = who->get_skill_dbase() ) && sizeof(skls) )
        {
                name = keys(skls);
                for( i = 0, size = sizeof(name); i < size; i ++ )
                {
                        skill = to_int( name[i] );
                        file = SKILL->get_skill_file(skill);
                        if( load_object(file) && file->is_basic_skill() ) continue;    // 不删基本技能

                        who->delete_skill(skill);
                }
        }
//      who->init_skill_dbase();    // 删除所有技能

        who->init_fly_dbase();    // 瞬移数据集

/*      who->set_fam_name(0);    // 删除门派资料
        who->set_fam_position(0);
        who->set_fam_title(0);
        who->set_fam_master(0);
        who->set_fam_time( time() );    */

        for( i = 0; i < 20; i ++ ) who->init_legend(i, 0);    // 删除传奇记录(新手)(部分!)
        who->init_legend(TASK_NEWBIE_00, 0xffffffff);    // 禁止新手任务(初级)

        level = 10;    // 等级经验清空
        who->set_level(level);
        who->set_max_level(level);
        who->set_exp( USER_EXP_D->get_level_exp_low( who->get_reincarnation(), level - 1 ),
                      USER_EXP_D->get_level_exp_high( who->get_reincarnation(), level - 1 ) );
        who->set_potential( range_value( who->get_potential(), 0, 1000 ) );

	who->count_gift();
	USER_ENERGY_D->count_all_prop(who);
	USER_ENERGY_D->count_max_yuan(who);

//      who->set_hp( who->get_max_hp() );    // 加满气血、法力,防止血条超长
//      who->set_mp( who->get_max_mp() );
        who->add_hp(-1);    // 前条达不到效果
        who->add_mp(-1);
}
