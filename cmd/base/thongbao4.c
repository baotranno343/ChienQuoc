#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg) 
{

    int skill = to_int(arg), p;
	string result,thongbao,tb,tb1,tb2,tb3;
    object item, item1, who;
	me = this_player();
    
		if( is_player(me) ) 
        {
            write_user(me, ECHO "Bạn không đủ quyền hạn !");
			return 1;
        }

		if( !arg ) return 1;
		if (arg==0) return 1;
		if( sscanf(arg, "+%s +%s +%s +%s +%s", tb, tb1, tb2, tb3, thongbao) == 5 )
		{
			USER_D->user_channel(sprintf(HIY"%s "HIC "%s"HIY" %s "HIG "%s "HIY"%s", tb, tb1, tb2, tb3, thongbao ) );
		}
		
		
	return 1;
} 