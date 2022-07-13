
#include <ansi.h>
#include <effect.h>

// 函数：帮派发展(ＩＴＥＭ)
void into_effect_3( object org )
{
        object *user;
        string name;
        int skill, level;
        int time;

        if( !org->is_org_officer() ) return;

        if(   ( skill = org->get_research() )
        &&    ( level = org->get_research_level() ) )
        {
                name = org->get_org_name();
                if( !name || name == "" ) name = "无名帮派";

                switch( level )
                {
              default : if( org->get_gold() >= 24000 )
                        {
                                org->add_gold( -24000 );
                                org->improve_skill(skill, 800);
                        }
                        else    FAMILY_D->org_channel( name, 0, sprintf( HIR "%s已经没有钱研究技能了！", org->get_name() ) );
                        break;
               case 2 : if( org->get_gold() >= 48000 )
                        {
                                org->add_gold( -48000 );
                                org->improve_skill(skill, 1200);
                        }
                        else    FAMILY_D->org_channel( name, 0, sprintf( HIR "%s已经没有钱研究技能了！", org->get_name() ) );
                        break;
               case 3 : if( org->get_gold() >= 96000 )
                        {
                                org->add_gold( -96000 );
                                org->improve_skill(skill, 1600);
                        }
                        else    FAMILY_D->org_channel( name, 0, sprintf( HIR "%s已经没有钱研究技能了！", org->get_name() ) );
                        break;
                }
        }

        time = ( 3600 - time() % 3600 ) / 60;    // 3600, 3600 - time() % 3600
        set_effect( org, EFFECT_ITEM_ORG, range_value(time, 1, MAX_NUMBER) );

        org->save();
}
