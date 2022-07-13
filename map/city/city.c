
#include <effect.h>

// 函数：构造处理
void create() 
{
        object map1, map2, map3, map4, map5, map6, map7, map8;
        int time;

        map1 = load_object( __DIR__ "01" );
        map2 = load_object( __DIR__ "02" );
        map3 = load_object( __DIR__ "03" );
        map4 = load_object( __DIR__ "04" );
        map5 = load_object( __DIR__ "05" );
        map6 = load_object( __DIR__ "06" );
        map7 = load_object( __DIR__ "07" );
        map8 = load_object( __DIR__ "08" );

        time = range_value( ( 3600 - time() % 3600 ) / 60, 1, MAX_NUMBER );    // 3600, 3600 - time() % 3600

        if( objectp( map1 ) ) set_effect(map1, EFFECT_ITEM_CITY, time);
        if( objectp( map2 ) ) set_effect(map2, EFFECT_ITEM_CITY, time);
        if( objectp( map3 ) ) set_effect(map3, EFFECT_ITEM_CITY, time);
        if( objectp( map4 ) ) set_effect(map4, EFFECT_ITEM_CITY, time);
        if( objectp( map5 ) ) set_effect(map5, EFFECT_ITEM_CITY, time);
        if( objectp( map6 ) ) set_effect(map6, EFFECT_ITEM_CITY, time);
        if( objectp( map7 ) ) set_effect(map7, EFFECT_ITEM_CITY, time);
//      if( objectp( map8 ) ) set_effect(map8, EFFECT_ITEM_CITY, time);
}
