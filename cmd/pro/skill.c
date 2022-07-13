
#include <cmd.h>

int * basic_skill = ({ 0111, 0121, 0131, 0141, 0151, 0161, 0104, 0109, 0202, 0401, 0402, 0403, 0408, 0409, 0503, });
int * spec_skill = ({ 0211, 0212, 0316, 0317, 0319, 0221, 0231, 0222, 0325, 0329, 0241, 0251, 0242, 0348, 0349, 0261, 0363, 0364, 0365, 0368, 0271, 0413, 0414, 0417, 0418, 0421, 0422, 0423, 0424, 0425, 0281, 0501, 0511, 0531, 0591, });
int * strong_skill = ({ 430, 431, 432, 433, 434, 435, 436, 437, 438, });
int get_order(string id);

void send_skill_msg(object me, object who, int skill, int type);

// 函数：命令处理
int main( object me, string arg2 )
{
        object *user, char, who = me;
        string *ids = ({ }), id, result, result2;
        int i, size, len, order, flag, z, begin, end, type, level;
        string arg;
        int time, number, *all;
        if( is_player(me) )
        {
                notify( "您没有足够的权限。" );
		return 1;
        }
        if (!arg2) return 1;
        ids = explode(arg2, " ");
        arg = ids[0];
        if(!( who = find_player(arg) ) )
        {
                id = strlwr(arg);
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
        number = who->get_number();
        if (sizeof(ids)==1 ||sizeof(ids)==2 )
        {
        	order = get_order(arg);
        	if (sizeof(ids)==1) type = 0;
        	else
        	type = to_int(ids[1]);
        	switch(type)
        	{
        	case 0:
        		all = basic_skill;
        		size = sizeof(all);
        		for (i=0;i<size;i++)
        		{
        			send_skill_msg(me, who, all[i], 0);
        		}
        		all = spec_skill;
        		size = sizeof(all);
        		begin = end = 0;
        		if (who->get_fam_type()>0)
        		{
        			begin = (who->get_fam_type()-1)*5;
        			end = who->get_fam_type()*5;
        		}
        		for (i=begin;i<end;i++)
        		{
        			send_skill_msg(me, who, all[i], 0);
        		}
        		all = strong_skill;
        		size = sizeof(all);
        		for (i=0;i<size;i++)
        		{
        			send_skill_msg(me, who, all[i], 0);
        		}
        	}
        	destruct(who);
        	return 1;
        }
        if (sizeof(ids)==3)
        {
        	if (ids[1]=="3")
        	{
        		type = to_int(ids[2]);
        		if (who->get_skill(type))
        		{
        			result2 = sprintf("原等级 %d", who->get_skill(type));
log_file("gm/op.dat", sprintf("%s %s(%d) 删除技能 %s(%d) %s %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), ids[2], result2 ));
        			who->delete_skill(type);
        			send_user(me, "%c%c%d%d", 0x76, 3, who->get_number(), type );
        			who->save();
        			destruct(who);
        		}
        	}
        	return 1;
        }
        if (sizeof(ids)==4)
        {
        	if (ids[1]=="2")
        	{
        		type = to_int(ids[2]);
        		level = to_int(ids[3]);
        		if (level==0 && who->get_skill(type))
        		{
        			result2 = sprintf("原等级 %d", who->get_skill(type));
log_file("gm/op.dat", sprintf("%s %s(%d) 删除技能 %s(%d) %s %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), ids[2], result2 ));
        			who->delete_skill(type);
        			send_user(me, "%c%c%d%d", 0x76, 3, who->get_number(), type );
        			who->save();
        			destruct(who);      
        			return 1;  			
        		}
        		// 检查技能是否有效
        		if (type<610||type>680)
        		{
        			if (type>=430&&type<440)
        			{
        				if (type==436&&level>5)
        				{
        					send_user(me, "%c%s", '!', "药物强化技能不能超过5级。");
        					destruct(who);      
        					return 1;
        				}
        				if (level>10)
        				{
        					send_user(me, "%c%s", '!', "强化技能不能超过10级。");
        					destruct(who);      
        					return 1;
        				}        				
        			}
        			else
        			if (level>who->get_level())
        			{
        				send_user(me, "%c%s", '!', "技能等级不能超过人物等级。");
        				destruct(who);      
        				return 1;
        			}         			
        		}
        		// 检查技能是否有效
        		result2 = sprintf("原等级 %d", who->get_skill(type));
        		who->set_skill(type, level);
log_file("gm/op.dat", sprintf("%s %s(%d) 修改技能 %s(%d) %s %s %s\n", short_time(), me->get_id(), me->get_number(), who->get_id(), who->get_number(), ids[2], result2, ids[3] ));
        		send_skill_msg(me, who, type, 1);
        		who->save();
        		destruct(who);
        	}
        }
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

void send_skill_msg(object me, object who, int skill, int type)
{
	string file, result, name, desc;
        file = SKILL->get_skill_file(skill);
        if (load_object(file))
        {
        	name = file->get_name();
        	desc = file->get_desc();
        	result = sprintf("%-12s%s", name, desc);
        }
        else return;
        if (type==1)
        	send_user(me, "%c%c%d%d%d%s", 0x76, 2, who->get_number(), skill, who->get_skill(skill), result );
        else
        if (who->get_skill(skill))
        	send_user(me, "%c%c%d%d%d%s", 0x76, 1, who->get_number(), skill, who->get_skill(skill), result );
        else
        	send_user(me, "%c%c%d%d%s", 0x76, 0, who->get_number(), skill, result );

}