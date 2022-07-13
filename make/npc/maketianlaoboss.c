
#define CPP_FILE        __DIR__ "tianlaoboss.cc"
#define TEXT_FILE       __DIR__ "tianlaoboss.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, *line, file, name;
        string *weapon = ({ "", "", "", "", "", "", "", "", "", "" });
        string *item = ({ "", "", "", "", "", "", "", "", "", "" });
        string *result = ({ "", "", "", "", "", "", "", "", "", "" });
        int id, pic, move, level, level2, seek, money, money2;
        string sColor;
        int color;        
        int move_speed, att_speed;
        int *wlvl = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int *alvl = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int *r = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int *size = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        string *item9, result_w, result_a;
        int i, j, total;
	string cKind,strong,cWeapon;
	
        cpp = read_file( CPP_FILE );
        line = explode( read_file( TEXT_FILE ), "\n" );

        total = sizeof(line);
        for( i = 0; i < total; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %s %d %d %s %d %d %d %d %s %s %s "
                        "%d %d %d %d %d "
                        "%d %d %d %d %d %d %d %d %d %d %d %d "
                        "%d %s %d %s %d %s %d %s %d %s", 
                        id, name, pic, move, sColor, move_speed, att_speed, level, level2, weapon[1], cKind,strong,
                        r[0], r[1], r[2], money, money2, 
                        r[3], wlvl[0], r[4], alvl[0], r[5], wlvl[1], wlvl[2], wlvl[3], r[6], alvl[1], alvl[2], alvl[3], 
                        r[7], item[1], r[8], item[2], r[9], item[3], r[10], item[4], r[11], item[5] ) )
                {	
                	move_speed = 2;
                	att_speed = 10;
                        file = sprintf("make/%04d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        switch( weapon[1] )
                        {
                  case "武器" :
                  case "空手" : seek = 4;  weapon[1] = "UNARMED";  weapon[2] = "0; }    // XXXXX";  weapon[3] = "*";  break;
                  case "暗器" : seek = 6;  weapon[1] = "THROWING";  weapon[2] = "PF_FILE_01611";  weapon[3] = "X";  break;
                  case "五雷" : seek = 6;  weapon[1] = "UNARMED";  weapon[2] = "PF_FILE_04232";  weapon[3] = "X";  break;
                      default : tell_user(me, "ERR: %04d 武器: %s", id, weapon[1] );  break;
                        }

                        wlvl[9] = (wlvl[1] > 0) + (wlvl[2] > 0) + (wlvl[3] > 0);
                        alvl[9] = (alvl[1] > 0) + (alvl[2] > 0) + (alvl[3] > 0);

                        for( j = 0, result_w = ""; j < wlvl[9]; j ++ )
                        {
                                result_w += sprintf( @LONG
                       case %d : file = WEAPON_FILE->get_weapon_file_2(%d);  break;
LONG
, j, wlvl[j+1] );
                        }
                        for( j = 0, result_a = ""; j < alvl[9]; j ++ )
                        {
                                result_a += sprintf( @LONG
                       case %d : file = ARMOR_FILE->get_armor_file_2(%d);  break;
LONG
, j, alvl[j+1] );
                        }

                        item9 = ({ });  size[1] = 0;  result[1] = "";
                        if (sColor=="－") color = 0;
                        else sscanf(sColor, "%x", color );
                        if( item[1] != "－" )
                        {
                                item9 = explode( item[1], "、" );
                                item9 = sort_array( item9, 1 );
                                size[1] = sizeof(item9);

                                for( j = 0; j < size[1]; j ++ )
                                {
                                        result[0] = "/make/item/itemlist"->get_item_file( item9[j] );    // 要维护物品列表！

                                        if( result[0] == "" ) tell_user(me, "ERR: %04d 杂物1: %s", id, item9[j]);
                                        result[1] += sprintf( @LONG
                       case %d : file = %s;  break;
LONG
, j, result[0] );
                                }
                        }
                        else 
                        {
                                r[1] += r[7];  r[7] = 0;
                        }

                        item9 = ({ });  size[2] = 0;  result[2] = "";

                        if( item[2] != "－" )
                        {
                                item9 = explode( item[2], "、" );
                                item9 = sort_array( item9, 1 );
                                size[2] = sizeof(item9);

                                for( j = 0; j < size[2]; j ++ )
                                {
                                        result[0] = "/make/item/itemlist"->get_item_file( item9[j] );    // 要维护物品列表！

                                        if( result[0] == "" ) tell_user(me, "ERR: %04d 杂物2: %s", id, item9[j]);
                                        result[2] += sprintf( @LONG
                       case %d : file = %s;  break;
LONG
, j, result[0] );
                                }
                        }
                        else 
                        {
                                r[1] += r[8];  r[8] = 0;
                        }

                        item9 = ({ });  size[3] = 0;  result[3] = "";

                        if( item[3] != "－" )
                        {
                                item9 = explode( item[3], "、" );
                                item9 = sort_array( item9, 1 );
                                size[3] = sizeof(item9);

                                for( j = 0; j < size[3]; j ++ )
                                {
                                        result[0] = "/make/item/itemlist"->get_item_file( item9[j] );    // 要维护物品列表！

                                        if( result[0] == "" ) tell_user(me, "ERR: %04d 杂物3: %s", id, item9[j]);
                                        result[3] += sprintf( @LONG
                       case %d : file = %s;  break;
LONG
, j, result[0] );
                                }
                        }
                        else 
                        {
                                r[1] += r[9];  r[9] = 0;
                        }

                        item9 = ({ });  size[4] = 0;  result[4] = "";

                        if( item[4] != "－" )
                        {
                                item9 = explode( item[4], "、" );
                                item9 = sort_array( item9, 1 );
                                size[4] = sizeof(item9);

                                for( j = 0; j < size[4]; j ++ )
                                {
                                        result[0] = "/make/item/itemlist"->get_item_file( item9[j] );    // 要维护物品列表！

                                        if( result[0] == "" ) tell_user(me, "ERR: %04d 杂物4: %s", id, item9[j]);
                                        result[4] += sprintf( @LONG
                       case %d : file = %s;  break;
LONG
, j, result[0] );
                                }
                        }
                        else 
                        {
                                r[1] += r[10];  r[10] = 0;
                        }

                        item9 = ({ });  size[5] = 0;  result[5] = "";

                        if( item[5] != "－" )
                        {
                                item9 = explode( item[5], "、" );
                                item9 = sort_array( item9, 1 );
                                size[5] = sizeof(item9);

                                for( j = 0; j < size[5]; j ++ )
                                {
                                        result[0] = "/make/item/itemlist"->get_item_file( item9[j] );    // 要维护物品列表！

                                        if( result[0] == "" ) tell_user(me, "ERR: %04d 杂物5: %s", id, item9[j]);
                                        result[5] += sprintf( @LONG
                       case %d : file = %s;  break;
LONG
, j, result[0] );
                                }
                        }
                        else 
                        {
                                r[1] += r[11];  r[11] = 0;
                        }
                        log_file( file, sprintf( cpp, 
                                weapon[3] == "X" ? "  " : "//",
                                move ? "//" : "  ",  move ? "//" : "  ",
                                pic, name, 
                                "FIGHTER_TYPE_2",   // 小怪，大怪？                                                                        
                                color, move_speed, att_speed, level, level2, seek,
                                "FIGHTER_TYPE_2",   // 小怪，大怪？
                                weapon[1], weapon[2], 
                                level <= 5 ? "  " : "//",    // 0, 5 级怪不主动攻击
                                "//", "  ",   // 大怪
                                r[0], r[1], 
                                r[2] && money ? "  " : "/*", r[2] += r[1], money, money2, r[2] != r[1] && money ? "  " : "*/", 

                                r[3] ? "  " : "/*", r[3] += r[2], wlvl[0], r[3] != r[2] ? "  " : "*/", 
                                r[4] ? "  " : "/*", r[4] += r[3], alvl[0], r[4] != r[3] ? "  " : "*/",
                                r[5] ? "  " : "/*", r[5] += r[4], wlvl[9], result_w, r[5] != r[4] ? "  " : "*/",
                                r[6] ? "  " : "/*", r[6] += r[5], alvl[9], result_a, r[6] != r[5] ? "  " : "*/",

                                r[7] && size[1] ? "  " : "/*", r[7] += r[6], size[1], result[1], r[7] != r[6] && size[1] ? "  " : "*/", 
                                r[8] && size[2] ? "  " : "/*", r[8] += r[7], size[2], result[2], r[8] != r[7] && size[2] ? "  " : "*/",
                                r[9] && size[3] ? "  " : "/*", r[9] += r[8], size[3], result[3], r[9] != r[8] && size[3] ? "  " : "*/",
                                r[10] && size[4] ? "  " : "/*", r[10] += r[9], size[4], result[4], r[10] != r[9] && size[4] ? "  " : "*/",
                                r[11] && size[5] ? "  " : "/*", r[11] += r[10], size[5], result[5], r[11] != r[10] && size[5] ? "  " : "*/"
                                 ) );

                        file = LOG_DIR + file;  file->do_nothing();
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件。" );

        return 1;       
}
