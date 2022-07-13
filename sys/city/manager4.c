
#include <ansi.h>
#include <city.h>

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：帮派公告
void do_note( object who, object me, string arg )
{
        string text;
        string name1, name2;
        int id, level;

        id = getoid(me);

        name1 = who->get_org_name();
        name2 = me->get_org_name();

        if( stringp(name1) && stringp(name2) && name1 == name2 )    // 本帮帮众
        {
                if( !arg || arg == "" || arg == "1" )
                        send_user( who, "%c%c%d%c%s", 0x95, 40, id, who->get_org_position(), me->get_bulletin() );
                else if( arg == "2" )
                        send_user( who, "%c%c%d%c%s", 0x95, 41, id, who->get_org_position(), me->get_note() );
                else if( who->get_org_position() > ORG_PRESBYTER && sscanf( arg, "%d.%s", level, text ) == 2 )
                {
                        if( strlen(text) > 1000 ) text = text[0..999];

                        if( level == 1 ) me->set_bulletin(text);
                        else if( level == 2 ) me->set_note(text);
                }
        }
}
