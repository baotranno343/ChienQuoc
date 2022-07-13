
#include <map.h>

// 说明：以下定义来自 f_others.c (GSE)
#define DEFAULT_STATUS                  0
#define OBJECT_HASH_STATUS              1
#define LIVING_OBJECT_STATUS            2
#define HEART_BEAT_STATUS               3
#define CALL_OUT_STATUS                 4
#define CACHE_STATUS                    5

// 函数：命令处理
int main( object me, string arg )
{
        int i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        switch( arg )
        {
      default : arg = game_status(DEFAULT_STATUS, 1);  break;
case "object" : arg = game_status(OBJECT_HASH_STATUS, 1);  break;
case "living" : arg = game_status(LIVING_OBJECT_STATUS, 1);  break;
 case "heart" : arg = game_status(HEART_BEAT_STATUS, 1);  break;
  case "call" : arg = game_status(CALL_OUT_STATUS, 1);  break;
 case "cache" : arg = game_status(CACHE_STATUS, 1);  break;

   case "all" : arg = game_status(DEFAULT_STATUS, 1) + "\n";
                arg += game_status(OBJECT_HASH_STATUS, 1) + "\n";
                arg += game_status(LIVING_OBJECT_STATUS, 1) + "\n";
                arg += game_status(HEART_BEAT_STATUS, 1) + "\n";
                arg += game_status(CALL_OUT_STATUS, 1) + "\n";
                arg += game_status(CACHE_STATUS, 1);  
                break;

case "newbie" : for( i = NEWBIE_MAP_BEGIN, size = 0; i <= NEWBIE_MAP_END; i ++ )
                        if( get_map_max_x(i) && get_map_max_y(i) ) size ++;
                arg = sprintf("NEWBIE: %d", size);
                break;

   case "war" : for( i = BATTLE_MAP_BEGIN, size = 0; i <= BATTLE_MAP_END; i ++ )
                        if( get_map_max_x(i) && get_map_max_y(i) ) size ++;
                arg = sprintf("WAR: %d", size);
                break;
        }

        tell_user(me, "%s", arg);

        return 1;
}
