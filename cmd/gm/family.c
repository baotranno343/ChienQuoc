
#include <ansi.h>
#include <skill.h>
#include <equip.h>

// 函数：命令处理
int main( object me, string arg )
{
        mapping skls;
        object *inv, item;
        string cmd0, cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7;
        string cmd10, cmd20, cmd30, cmd40, cmd50, cmd60, cmd70;
        string *name, file;
        int family, level, level2, weapon, armor, skill;
        int p, i, size;
        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
	return 1;
        if( !arg )
        {
                family = -1;  level = -1;  weapon = -1;
        }
        else if( sscanf( arg, "%d %d %d", family, level, weapon ) == 3 )
                ;
        else if( sscanf( arg, "%d %d", family, level ) == 2 )
                weapon = -1;
        else 
        {
                family = -1;  level = -1;  weapon = -1;
        }

        if( family < 0 )
        {
                cmd1 = sprintf( "family 1 %d\n", level );
                cmd2 = sprintf( "family 2 %d\n", level );
                cmd3 = sprintf( "family 3 %d\n", level );
                cmd4 = sprintf( "family 4 %d\n", level );
                cmd5 = sprintf( "family 5 %d\n", level );
                cmd6 = sprintf( "family 6 %d\n", level );
                cmd7 = sprintf( "family 7 %d\n", level );
                cmd10 = sprintf( "family 10 %d\n", level );
                cmd20 = sprintf( "family 20 %d\n", level );
                cmd30 = sprintf( "family 30 %d\n", level );
                cmd40 = sprintf( "family 40 %d\n", level );
                cmd50 = sprintf( "family 50 %d\n", level );
                cmd60 = sprintf( "family 60 %d\n", level );
                cmd70 = sprintf( "family 70 %d\n", level );
                cmd0 = sprintf( "family 0 %d\n", level );
                send_user( me, "%c%s", ':', "您想把自己设为哪种门派？\n"
                        ESC "Đào Hoa Nguyên\n" + cmd1 +
                        ESC "Thục Sơn\n" + cmd2 +
                        ESC "Cấm Vệ Quân\n" + cmd3 +
                        ESC "Đường Môn\n" + cmd4 +
                        ESC "Mao Sơn\n" + cmd5 +
                        ESC "Côn Luân\n" + cmd6 +
                        ESC "Vân Mộng Cốc\n" + cmd7 +
                        ESC "Đào Hoa Nguyên (Cơ Bản)\n" + cmd10 +
                        ESC "Thục Sơn (Cơ Bản)\n" + cmd20 +
                        ESC "Cấm Vệ Quân (Cơ Bản)\n" + cmd30 +
                        ESC "Đường Môn (Cơ Bản)\n" + cmd40 +
                        ESC "Mao Sơn (Cơ Bản)\n" + cmd50 +
                        ESC "Côn Luân (Cơ Bản)\n" + cmd60 +
                        ESC "Vân Mộng Cốc (Cơ Bản)\n" + cmd70 +
                        ESC "Vô Môn Phái\n" + cmd0 );
                return 1;
        }
        else switch( family )
        {
              default : file = "Vô Môn Phái";  break;
     case 1 : case 10 : file = "Đào Hoa Nguyên";  break;
     case 2 : case 20 : file = "Thục Sơn";  break;
     case 3 : case 30 : file = "Cấm Vệ Quân";  break;
     case 4 : case 40 : file = "Đường Môn";  break;
     case 5 : case 50 : file = "Mao Sơn";  break;
     case 6 : case 60 : file = "Côn Luân";  break;
     case 7 : case 70 : file = "Vân Mộng Cốc";  break;
        }

        if( level < 0 )
        {
                send_user( me, "%c%c%d%s", '?', 1, me->get_max_skill_level_2(), sprintf( "生成“%s”技能、装备。\n\n请输入技能等级：\n"
                        ESC "family %d %%s\n", file, family ) );
                return 1;
        }

        if( mapp( skls = me->get_skill_dbase() ) && sizeof(skls) )
        {
                name = keys(skls);
                for( i = 0, size = sizeof(name); i < size; i ++ )
                {
                	skill = to_int( name[i] );
                	if (skill<610) me->delete_skill(  );
                }
        }
//      me->init_skill_dbase();    // 删除所有技能

        inv = me->get_all_equip();
        for( i = 0, size = sizeof(inv); i < size; i ++ ) if( inv[i] )
        {
                inv[i]->remove_from_user();    // 删除所有装备
                destruct( inv[i] );
        }

        me->set_exp( USER_EXP_D->get_level_exp_low( me->get_reincarnation(), level - 1 ),
                     USER_EXP_D->get_level_exp_high( me->get_reincarnation(), level - 1 ) );

//      USER_EXP_D->recount_user_level(me);

        NPC_ENERGY_2_D->init_family(me, family, level, weapon);
        USER_ENERGY_D->count_all_prop(me);
        USER_ENERGY_D->count_max_yuan(me);
        me->set_max_level(me->get_level());

        me->set_hp( me->get_max_hp() );
        me->set_mp( me->get_max_mp() );

        tell_user( me, "技能已设置好！" );

        return 1;
}
