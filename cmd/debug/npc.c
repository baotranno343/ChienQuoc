
// 函数：命令处理
int main( object me, string arg )
{
        object map;
        string name;
        int *id, time;
        int i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg )
        {
                id = ({ get_z(me) });
        }
        else switch( to_int(arg) )
        {
     case   0 : id = ({ 001, 002, 003,  });  break;
     case   5 : id = ({ 161, 162, 061, 062, 063,  });  break;
     case  10 : id = ({ 281, 282, 283, 284,  });  break;
     case  15 : id = ({ 081, 082, 251,  });  break;
     case  20 : id = ({ 021, 041, 042, 043, 089, 141, 142, 211,  });  break;
     case  25 : id = ({ 241, 242, 243, 271, 272, 131, 132, 231, 181, 182, 155,  });  break;
     case  30 : id = ({ 163, 164, 261, 262, 263, 264,  });  break;
     case  35 : id = ({ 265, 266, 111, 112,  });  break;
     case  40 : id = ({ 011, 012, 013, 014, 015,  });  break;
     case  45 : id = ({ 151, 152, 153,  });  break;
     case  50 : id = ({ 171, 172, 173, 174,  });  break;
     case  55 : id = ({ 071, 072, 073,  });  break;
     case  60 : id = ({ 031, 032, 033,  });  break;
     case  65 : id = ({ 051, 052, 053,  });  break;
     case  70 : id = ({ 321, 322, 323,  });  break;
     case  75 : id = ({ 311, 312, 313,  });  break;
     case  80 : id = ({ 331, 332, 333, 334, 335,  });  break;
     case  85 : id = ({ 341, 342, 343, 344, 345,  });  break;
     case  90 : id = ({ 291, 292, 293,  });  break;
     case  95 : id = ({ 381, 382, 383, 384, 385,  });  break;
     case 100 : id = ({ 371, 372, 373, 374,  });  break;
     case 105 : id = ({ 091, 092, 093, 095,  });  break;
      default : id = ({ 391, 392, 393,  });  break;
        }

        for( i = 0, size = sizeof(id); i < size; i ++ )
        {
                map = get_map_object( id[i] );
                name = map ? map->get_name() : "Bản đồ vô danh";

                time = 60 * map->get_clean_time() - time() % 100 + map->get_reset_order();

                tell_user( me, "%s(%03d) %d[%d]/%d + %d 个怪，余 %d分%d秒 /%d分 刷新。怪点: %d, 人物: %d, 刷新: %d。", name, id[i], 
                        map->sizeof_fighter_dbase(), map->sizeof_caster_dbase(), map->get_fighter_amount(), map->sizeof_boss_dbase(), 
                        time / 60, time % 60, map->get_clean_time(), 
                        sizeof_xy_point( id[i] ), map->sizeof_npc_dbase(), map->sizeof_reset_dbase() );
        }

        return 1;
}
