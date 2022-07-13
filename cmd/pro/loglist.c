
#include <equip.h>

#define LIST_LOG        "list.txt"

// 函数：命令处理
int main( object me, string arg )
{
        mixed *dfile;
        mapping *quest;
        string *name, path, file;
        int i, j, size, total, flag;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg ) arg = "";

        if( arg == "emote" )
        {
                name = EMOTE_D->get_all_emote();

                for( i = 0, size = sizeof(name); i < size; i ++ )
                        log_file( LIST_LOG, sprintf("%s %s\n", name[i], EMOTE_D->get_emote_note( name[i] ) ) );

                return 1;
        }

        path = absolute_path(me, arg);    // 获取绝对路径
        if( directory_exist(path) && path[<1] != '/' ) path += "/";

        dfile = get_dir(path, -1);    // 获取文件列表

        if( !( size = sizeof(dfile) ) )    // 路径合法判断
        {
                if( path[<1] != '/' ) 
		{
                        notify( "无法找到这个文件。" );
		        return 1;
		}
                if( directory_exist( path[ 1..<2 ] ) ) 
		{
                        notify( "这个目录没有东西。" );
		        return 1;
                }
                else
		{
                        notify( "无法找到这个目录。" );
		        return 1;
		}
        }

        path = path[ 0 .. strchr( path, '/', -1 ) + 1 ];    // 运算绝对路径

        for( i = 0; i < size; i ++ )    // 生成列示内容
        {
                file = path + dfile[i][0];    // 取绝对路径名

                if( directory_exist(file) || dfile[i][0] == "." || dfile[i][0] == ".." ) continue;

                if( strlen(file) > 2 && file[<2..<1] != ".c" ) continue;

                if( file->is_skill() )
                {
                        log_file( LIST_LOG, sprintf( "%s", file->get_desc() ) );
                        continue;
                }
                else if( file->get_perform_type() )
                {
                        log_file( LIST_LOG, sprintf( "　　%s", file->get_desc(me) ) );
                        continue;
                }

                if( file->is_quest_list() )
                {
                        log_file( LIST_LOG, sprintf( "\n名称 经验 (%s级)\n", dfile[i][0][0..<3] ) );

                        quest = file->get_quest_list();
                        total = sizeof(quest);

                        for( j = 0; j < total; j ++ )
                                log_file( LIST_LOG, sprintf("%s %d\n", quest[j]["name"], quest[j]["exp"] ) );

                        continue;
                }

                if( !file->is_item() && !file->is_npc() ) continue;

                if( file->get_equip_type() == ARMOR_TYPE )
                {
                        if( !flag )
                        {
                                log_file( LIST_LOG, "\n编号 名称 地表图 道具图 量词 性别 等级\n" );
                                flag = 1;
                        }
                        log_file( LIST_LOG, sprintf("%s %s %d %d %s %d %d %s\n", dfile[i][0][0..<3],
                                file->get_name(), file->get_picid_1(), file->get_picid_2(), 
                                file->get_unit(), file->get_gender(), file->get_level(), file->get_desc() ) );
                }
                else if( file->is_equip() )
                {
                        if( !flag )
                        {
                                log_file( LIST_LOG, "\n编号 名称 地表图 道具图 量词 等级\n" );
                                flag = 1;
                        }
                        log_file( LIST_LOG, sprintf("%s %s %d %d %s %d %s\n", dfile[i][0][0..<3],
                                file->get_name(), file->get_picid_1(), file->get_picid_2(), 
                                file->get_unit(), file->get_level(), file->get_desc() ) );
                }
                else if( file->is_item() )
                {
                        if( !flag )
                        {
                                log_file( LIST_LOG, "\n编号 名称 地表图 道具图 量词 价格\n" );
                                flag = 1;
                        }
                        log_file( LIST_LOG, sprintf("%s %s %d %d %s %d %s\n", dfile[i][0][0..<3],
                                file->get_name(), file->get_picid_1(), file->get_picid_2(), 
                                file->get_unit(), file->get_value(), file->get_desc() ) );
                }
                else if( file->is_badman() )
                {
                        if( !flag )
                        {
                                log_file( LIST_LOG, "\n编号 名称 类型 性别 走速 攻速 武器\n" );
                                flag = 1;
                        }
                        log_file( LIST_LOG, sprintf("%s %s %s %s %d %d %d\n", dfile[i][0][0..<3],
                                file->get_name(), file->get("figure"), 
                                file->get_gender() == 1 ? "男" : "女",
                                file->get_walk_speed(), file->get_attack_speed(), file->get_weapon_code() ) );
                }
                else if( file->is_npc() )
                {
                        if( !flag )
                        {
                                log_file( LIST_LOG, "\n编号 名称 种类\n" );
                                flag = 1;
                        }
                        log_file( LIST_LOG, sprintf("%s %s %s\n", dfile[i][0][0..<3],
                                file->get_name(), file->is_officer() ? "---" : "NPC" ) );
                }
        }

        tell_user( me, "请查看 list.txt 文件。" );

        return 1;       
}
