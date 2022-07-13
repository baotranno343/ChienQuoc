
#include <ansi.h>
#define COUND_d "/sys/sys/count"

string get_type_word(int type)
{
	switch(type)
	{
	case 0: return "气血";
	case 1: return "法力";
	case 2: return "攻击";
	case 3: return "防御";
	case 4: return "法攻";
	case 5: return "法攻";
	default: return "敏捷";
	}
}

string get_fam_word(int type)
{
	switch(type)
	{
	case 0: return "Vô Môn Phái.";
	case 1: return "Đào Hoa Nguyên";
	case 2: return "Thục Sơn";
	case 3: return "Cấm Vệ Quân";
	case 4: return "Đường Môn";
	case 5: return "Mao Sơn";
	case 6: return "Côn Luân";
	default: return "Vân Mộng Cốc";
	}
}

// 函数：命令处理
int main( object me, string arg )
{
        object *zombie, soldier;
        string cmd1, cmd2, cmd3, cmd4, cmd5, cmd6, cmd7, cmd8;
        int type, type2, index, value;

        if( me != this_player(1) || is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( !arg )
        {
                send_user( me, "%c%s", ':', "您想查看哪类公式？\n"
                        ESC "气血公式\nenergy 0\n"
                        ESC "法力公式\nenergy 1\n"
                        ESC "攻击公式\nenergy 2\n"
                        ESC "防御公式\nenergy 3\n"
                        ESC "法攻公式\nenergy 4\n"
                        ESC "法防公式\nenergy 5\n"
                        ESC "敏捷公式\nenergy 6\n"                                        
                        ESC "离开\nCLOSE\n" );
                return 1;
        }
        if (sscanf(arg, "%d %d %d %d", type, type2, index, value)==4)
        {
        	if (type==0) COUND_d->set_1(type2, index, value);
        	else COUND_d->set_2(type2, index, value);
        	"/sys/user/energy"->count_all_prop(me);
        	main(me, sprintf("%d", type2));
        	return 1;
        }
        if (sscanf(arg, "%d %d %d", type, type2, index)==3)
        {
        	if (type==0)
                	send_user( me, "%c%c%d%s", '?', 1, 999999, sprintf("您想将"+get_fam_word(index)+"中的"+get_type_word(type2)+"加乘系数改为多少？\n"
                        	ESC "energy %d %d %d %%s\n", type, type2, index ) );        	
		else
                	send_user( me, "%c%c%d%s", '?', 1, 999999, sprintf("您想将"+get_fam_word(index)+"中的"+get_type_word(type2)+"除于系数改为多少？\n"
                        	ESC "energy %d %d %d %%s\n", type, type2, index ) );        	
		return 1;		                        
	}
	if (sscanf(arg, "%d %d", type2, index)==2)
	{
		cmd1 = sprintf( ESC "加乘系数\nenergy 0 %d %d\n", type2, index);
		cmd2 = sprintf( ESC "除于系数\nenergy 1 %d %d\n", type2, index);
		send_user( me, "%c%s", ':', "您想修改"+get_fam_word(index)+"的"+get_type_word(type2)+"公式的哪个数值？\n"
			+ cmd1 + cmd2+
                	ESC "离开\nCLOSE\n" );
                return 1;
	}

	type2 = to_int(arg);
	cmd1 = sprintf( ESC "Vô Môn Phái.: %d/%d\nenergy %d 0\n", COUND_d->get_1(type2, 0), COUND_d->get_2(type2, 0), type2);
	cmd2 = sprintf( ESC "Đào Hoa Nguyên: %d/%d\nenergy %d 1\n", COUND_d->get_1(type2, 1), COUND_d->get_2(type2, 1), type2);
	cmd3 = sprintf( ESC "Thục Sơn: %d/%d\nenergy %d 2\n", COUND_d->get_1(type2, 2), COUND_d->get_2(type2, 2), type2);
	cmd4 = sprintf( ESC "Cấm Vệ Quân: %d/%d\nenergy %d 3\n", COUND_d->get_1(type2, 3), COUND_d->get_2(type2, 3), type2);
	cmd5 = sprintf( ESC "Đường Môn: %d/%d\nenergy %d 4\n", COUND_d->get_1(type2, 4), COUND_d->get_2(type2, 4), type2);
	cmd6 = sprintf( ESC "Mao Sơn: %d/%d\nenergy %d 5\n", COUND_d->get_1(type2, 5), COUND_d->get_2(type2, 5), type2);
	cmd7 = sprintf( ESC "Côn Luân: %d/%d\nenergy %d 6\n", COUND_d->get_1(type2, 6), COUND_d->get_2(type2, 6), type2);
	cmd8 = sprintf( ESC "Vân Mộng Cốc: %d/%d\nenergy %d 7\n", COUND_d->get_1(type2, 7), COUND_d->get_2(type2, 7), type2);
        send_user( me, "%c%s", ':', "以下是"+get_type_word(type2)+"的公式：\n"
                + cmd1 + cmd2 + cmd3 + cmd4 + cmd5 + cmd6 + cmd7 + cmd8 +                                
                ESC "离开\nCLOSE\n" );
        return 1;	
	

        return 1;
}
