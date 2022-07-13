#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg) 
{

    int p, diem;
	string result,arg2;
    object item, item1, who;
    
		if( is_player(me) ) 
        {
            write_user(me, ECHO "Bạn không đủ quyền hạn !");
			return 1;
        }

		if( !arg ) return 1;
		if (arg==0) return 1;
		if( sscanf(arg, "%s %d", arg2, diem) == 2 )
		{
			if( arg2 && !( who = find_any_char(arg2) ) )
			{
                write_user(me, ECHO "Không tìm thấy người này !");
				return 1;
			}
			who->set_fam_contribute(diem);
			tell_user(me, sprintf("%s (%d) bây giờ có %d Cống hiến Môn Phái", who->get_name(), who->get_number(), diem));
			tell_user(who, sprintf("Bạn bây giờ có %d Cống hiến Môn Phái", diem ));
		}
		
	return 1;
} 