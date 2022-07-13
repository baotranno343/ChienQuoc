
#include <cmd.h>

int get_order(string id);

// 函数：命令处理
int main( object me, string arg2 )
{
        object *user, char, who = me;
        string *ids = ({ }), id, result, result2;
        int i, size, len, order, flag, z, x, y;
        string arg, name;
        int time, number;

        if( is_player(me) )
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        if (!arg2) return 1;
        ids = explode(arg2, " ");        
        arg = ids[0];
        arg2 = arg;
        if(!( who = find_player(arg) ) )
        {
                id = strlwr(arg);
/*
                if( !CHECK_D->is_legal_id(me, id) )
                {
	        	return 1;
                }
*/
                if( !user_exist(id) )
                {
                        notify( "这个用户并不存在！" );
		        return 1;
                }

                who = new( USER );
                who->set_id(id);
                if( !who->restore() )
                {
                        send_user(me, "%c%s", '!', "这个用户并不存在！");
                        destruct(who);  
                        return 1;
                }

                if( char = find_player( sprintf( "%d", who->get_number() ) ) )
                {
                	destruct(who);
	        	send_user(me, "%c%s", '!', "该用户处于在线状态！");
	        	return 1;
                }
                else    flag = 1;
        }
        else
        {
        	send_user(me, "%c%s", '!', "该用户处于在线状态！");
        	return 1;
        }        
        arg = ids[0];
        if (sizeof(ids)==1)
        {
        	order = get_order(arg);
        	number = who->get_number();
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 3, sprintf("%d", who->get_level()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 4, who->get_name());
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 7, sprintf("%d", who->get_gift_point()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 8, who->get_title());
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 9, sprintf("%d", who->get_hp()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 10, sprintf("%d", who->get_max_hp()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 11, sprintf("%d", who->get_mp()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 12, sprintf("%d", who->get_max_mp()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 13, sprintf("%d", who->get_ap_0()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 14, sprintf("%d", who->get_ap()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 15, sprintf("%d", who->get_dp_0()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 16, sprintf("%d", who->get_dp()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 17, sprintf("%d", who->get_cp_0()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 18, sprintf("%d", who->get_cp()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 19, sprintf("%d", who->get_pp_0()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 20, sprintf("%d", who->get_pp()));
        	if( stringp( result = who->get_start_place() )
        	&& sscanf( result, "%d:(%d,%d)%d", z, x, y, i ) == 4 )
        	{
        		send_user(me, "%c%d%c%c%s", 0xbc, number, order, 21, sprintf("%d", z));
        		send_user(me, "%c%d%c%c%s", 0xbc, number, order, 22, sprintf("%d", x));
        		send_user(me, "%c%d%c%c%s", 0xbc, number, order, 23, sprintf("%d", y));
        	}
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 24, sprintf("%d", who->get_strength()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 25, "200");
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 26, sprintf("%d", who->get_con_1()+who->get_con_2()+who->get_level()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 27, sprintf("%d", who->get_spi_1()+who->get_spi_2()+who->get_level()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 28, sprintf("%d", who->get_str_1()+who->get_str_2()+who->get_level()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 29, sprintf("%d", who->get_cps_1()+who->get_cps_2()+who->get_level()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 30, sprintf("%d", who->get_dex_1()+who->get_dex_2()+who->get_level()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 31, sprintf("%d", who->get_sp()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 32, sprintf("%d", who->get_double_rate()));
        	send_user(me, "%c%d%c%c%s", 0xbc, number, order, 33, sprintf("%d", who->get_upgrade_exp()));
		send_user(me, "%c%d%c%c%s", 0xbc, number, order, 34, sprintf("%d", who->get_potential()));
		send_user(me, "%c%d%c%c%s", 0xbc, number, order, 35, sprintf("%d", who->get_bonus()));
		send_user(me, "%c%d%c%c%s", 0xbc, number, order, 36, sprintf("%d", who->get_fam_contribute()));
		send_user(me, "%c%d%c%c%s", 0xbc, number, order, 37, sprintf("%d", who->get_yuan()));
		if ( sizeof(who->get_fam_name()) )
			send_user(me, "%c%d%c%c%s", 0xbc, number, order, 38, "4");
		else
			send_user(me, "%c%d%c%c%s", 0xbc, number, order, 38, "3");
		send_user(me, "%c%c", 0xa1, 2);
		if (flag==1) destruct(who);
        	return 1;
        }
        if (sizeof(ids)!=3) 
        {
        	if (flag==1) destruct(who);  
        	return 1;
        }
        i = to_int(ids[2]);
        switch(to_int(ids[1]))
        {
        case 3: 
        	if (i!=who->get_level())
        	{
	        	result2 = sprintf("Đẳng cấp %d ", who->get_level());
	        	who->set_level(i); 
	        	who->set_max_level(who->get_level());
	        	"/cmd/user/gift"->init_gift_point(who);
	        	who->set_gift_point( i * who->get_gift_point_times() );
	        	send_user(me, "%c%s", '!', "请关闭窗口重新打开属性窗口刷新属性"); 
	        }
        	break;
        case 4: 
        	result2 = "名字 "+who->get_name();
        	who->set_name(ids[2]); 
        	break;
        case 7: 
        	result2 = sprintf("属性点 %d", who->get_gift_point());
        	who->set_gift_point(i); 
        	break;
        case 8: 
        	result2 = "头衔 "+who->get_title();
        	who->set_title(ids[2]); 
        	break;
        case 9: 
        	result2 = sprintf("气血 %d", who->get_hp());
        	who->set_hp(i); 
        	break;
        case 11: 
        	result2 = sprintf("法力 %d", who->get_mp());
        	who->set_mp(i); 
        	break;
        case 24: 
        	result2 = sprintf("体力 %d", who->get_strength());
        	who->set_strength(i); 
        	break;
        case 33: 
        	result2 = sprintf("升级经验 %d", who->get_upgrade_exp());
        	who->set_upgrade_exp(i); 
        	break;
        case 34: 
        	result2 = sprintf("潜能 %d", who->get_potential());
        	who->set_potential(i); 
        	break;
        case 35: 
        	result2 = sprintf("功德 %d", who->get_bonus());
        	who->set_bonus(i); 
        	break;
        case 36: 
        	result2 = sprintf("门贡 %d", who->get_fam_contribute());
        	who->set_fam_contribute(i); 
        	break;
        case 37: 
        	result2 = sprintf("元气 %d", who->get_yuan());
        	who->set_yuan(i); 
        	break;
        default: 
//        	send_user(me, "%c%s", '!', "不能修改对应项目的值"); 
        	if (flag==1) destruct(who);
        	return 1;
	}
log_file("gm/op.dat", sprintf("%s %s(%d) 修改 %s(%d) %s %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), result2, ids[2] ));

        who->save();
        if (flag==1) destruct(who);
        return 1;
}

int get_order(string id)
{
	int i, size;
	size = strlen(id);
	if (size==0) return 1;
	for (i=0;i<size;i++)
	{
		if (id[i]=='#'&& i<size-1)
			return to_int(id[<1..<1]);
	}
	return 1;
}