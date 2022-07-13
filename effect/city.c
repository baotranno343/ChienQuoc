
#include <effect.h>

// 函数：城市发展(ＩＴＥＭ)
void into_effect_3( object city )
{
        int time;

        if( !city->is_city() ) return;

        CITY_D->city_everyday(city);    // 每天处理

        CITY_D->city_vote(city);    // 城市选举
        CITY_D->city_policy(city);    // 城市政令(24小时过期)

        time = ( 3600 - time() % 3600 ) / 60;    // 3600, 3600 - time() % 3600
        set_effect( city, EFFECT_ITEM_CITY, range_value(time, 1, MAX_NUMBER) );

        city->save();
}
