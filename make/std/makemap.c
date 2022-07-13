
#include <city.h>

#define CPP_FILE        __DIR__ "map.cc"
#define CPP_FILE_2      __DIR__ "map2.cc"
#define CPP_FILE_3      __DIR__ "map3.cc"
#define TEXT_FILE       __DIR__ "map.txt"
#define LIST_LOG        "list.txt"
#define LIST_LOG_2      "list2.txt"

// 函数：命令处理
int main( object me, string arg )
{
        string cpp, cpp2, cpp3, *line, file, name, map, city, result, result2;
        int id, id2, order, type, *npc = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
        int cast1, cast2, r1, r2, i, j, size;

        cpp = read_file( CPP_FILE );
        cpp2 = read_file( CPP_FILE_2 );
        cpp3 = read_file( CPP_FILE_3 );
        line = explode( read_file( TEXT_FILE ), "\n" );

                        log_file( LIST_LOG_2, "--- 以下放入 /map/map/map.c ---\n");

        size = sizeof(line);
        for( i = 0; i < size; i ++ ) 
        {
                if( line[i][0] == '#' || line[i] == "" ) continue;
                if( sscanf( line[i], "%d %d %d %s %d %d %d %d %d %d %d %d %d %d %d %d %d", 
                        id, id2, order, name, type, npc[1], npc[2], npc[3], npc[4], npc[5], cast1, npc[6], npc[7], npc[8], npc[9], npc[10], cast2 ) )
                {
                        file = sprintf("make/%03d.c", id );
                        rm( LOG_DIR + file );    // 清除旧文件(WINDOWS)

                        r1 = (npc[1] > 0) + (npc[2] > 0) + (npc[3] > 0) + (npc[4] > 0) + (npc[5] > 0);
                        r2 = (npc[6] > 0) + (npc[7] > 0) + (npc[8] > 0) + (npc[9] > 0) + (npc[10] > 0);

                        for( j = 0, result = ""; j < 5; j ++ )
                        {
                                if (npc[j+1]>0) 
                                {                                                                                        
                                        result += sprintf( "\"/npc/npc/%04d\", ", npc[j+1] );
//                                        if (file_size(sprintf("/npc/npc/%04d.c", npc[j+1]))==-1) tell_user(me, "ERR: %03d 地图 %04d npc不存在", id, npc[j+1]);
                                }
                        }

                        for( j = 0, result2 = ""; j < 5; j ++ )
                        {
                                if (npc[j+6]>0) 
                                {                                                                                        
                                        result2 += sprintf( "\"/npc/npc/%04d\", ", npc[j+6] );
//                                        if (file_size(sprintf("/npc/npc/%04d.c", npc[j+6]))==-1) tell_user(me, "ERR: %03d 地图 %04d npc不存在", id, npc[j+6]);
                                }                                
                        }

                        switch( id )
                        {
                      case 10 : city = "CITY_QI";  break;
                      case 20 : city = "CITY_HAN";  break;
                      case 30 : city = "CITY_ZHAO";  break;
                      case 40 : city = "CITY_WEI";  break;
                      case 50 : city = "CITY_QIN";  break;
                      case 60 : city = "CITY_CHU";  break;
                      case 70 : city = "CITY_YAN";  break;
                      default : city = "CITY_ZHOU";  break;
                        }
                        switch( type )
                        {
                       case 1 : map = "CITY_MAP";  break;
                      default : map = "FIELD_MAP";  break;
                       case 3 : map = "CAVE_MAP";  break;
                        }
			if (id>=500 && id<600)
				log_file( file, sprintf( cpp3, "SCENE", id, id2, name, order, map, cast1, id, result, result2 ) );
			else
                        if( type != 1 )
                                log_file( file, sprintf( cpp, "SCENE", id, id2, name, order, map, cast1, id, result, result2 ) );
                        else    log_file( file, sprintf( cpp2, "SCENE_2", id, id2, name, order, map, id, city ) );

//                        log_file( LIST_LOG, sprintf("%03d map/blk/%03d.blk map/ini/%03d.ini map/xy/%03d.xy\n", id, id, id, id ) );

                        log_file( LIST_LOG_2, sprintf( @LONG
        load_object( __DIR__ "%03d" );
LONG
, id) );
                }
        }

        tell_user( me, "请查看 /log/make/ 下的文件，及 list.txt, list2.txt, 重要！" );

        return 1;       
}
