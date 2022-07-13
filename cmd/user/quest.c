
#include <ansi.h>
#include <task.h>
int quest_other(object me, string arg);
// 函数：命令处理
int main( object me, string arg )
{	
	string com,arg1;
	
	if ( !stringp(arg) || ( sscanf(arg,"%s %s", com,arg1) != 2 && arg != "list" ) )
	{
		return quest_other(me,arg);
	}
	
	if ( arg == "list" || com == "list" )
		USER_TASK_D->get_task_list(me);
	else if ( com == "intro")
		USER_TASK_D->get_task_intro(me,arg1);
	else if ( com == "giveup" )
		USER_TASK_D->task_giveup(me,arg1);
		
	
}
int quest_other(object me, string arg)
{
        object map, city, npc, who = me;
        string id, name, result, result2;
        int z, x, y, time, index = 0, status;

        result = "";  result2 = "";
        
        if( arg && arg != "" )
        {
                if( arg == "?" )    // 收集任务
                {
                        send_user( me, "%c%c%c", 0x51, '2', 0 );
                        result = USER_TASK_D->get_task_desc_2(who, me );                

                        if( result == "" ) 
                        {                                
                                result = "您现在没有剧情任务。\n";
                                send_user( me, "%c%c%s", 0x51, '2', result );
                        }
                        return 1;
                }

                if( is_player(me) )    // ＧＭ查看任务
                {
                        notify( "您没有足够的权限。" );
        		return 1;
                }

                if( sscanf(arg, "? %s", id) )
                {
                        send_user( me, "%c%c%c", 0x51, '2', 0 );
                        if( !( who = find_player(id) ) )
                        {
                                notify( "您无法找到这个人。" );
        		        return 1;
                        }

                        tell_user(me, "列示%s(%d)的任务。", who->get_name(), who->get_number() );
                
                        result = USER_TASK_D->get_task_desc_2(who, me);

                        if( result == "" ) 
                        {                                
                                result = "对方没有剧情任务。\n";
                                send_user( me, "%c%c%s", 0x51, '2', result );
                        }

                        return 1;
                }

                if( !( who = find_player(arg) ) )
                {
                        notify( "您无法找到这个人。" );
        		return 1;
                }

                tell_user(me, "列示%s(%d)的任务。", who->get_name(), who->get_number() );
        }
       send_user( me, "%c%c%s", 0x51, '1' , 0 );

//        result = USER_TASK_D->get_task_desc(who);
//        send_user( me, "%c%c%s", 0x51, '1', result );

	if ( who->get_task("criminal.bonus") )
	{
                result = sprintf("［挖宝任务］\n"BLK"追捕逃犯\n\n"BLK" nhiệm vụ：\n"BLK"    剿灭因监狱墙壁破损而出逃的逃犯。\n"BLK"    剿灭%s： 1/1（已经完成）。\n"BLK" nhiệm vụ miêu tả：\n"BLK"    前些日子因暴风雨的缘故，监狱墙壁破损严重，导致小部phút逃犯趁机逃跑，听闻探子回报，"HIR "%s"BLK"就藏匿于"HIR "%s"BLK"一带，若你能顺利剿灭此逃犯，大王定会重重有赏。\n"BLK"奖励：1500金\n",
                        who->get_task("criminal.name"),who->get_task("criminal.name"),  who->get_task("criminal.map"));
                send_user( me, "%c%c%s", 0x51, '1', result );                        
        }
        else if(     stringp( id = who->get_task("criminal") ) 
        &&    ( npc = find_char(id) ) && npc->is_criminal() )    // 30 phút钟
        {
                time = 1800 - gone_time( npc->get("birthday") );
                map = get_map_object( get_z(npc) );
                name = map ? map->get_name() : "Bản đồ vô danh";
                result = sprintf("［挖宝任务］\n"BLK"追捕逃犯\n\n"BLK" nhiệm vụ：\n"BLK"    剿灭因监狱墙壁破损而出逃的逃犯。\n"BLK"    剿灭%s： 0/1（thặng余时间%dphút钟）。\n"BLK" nhiệm vụ miêu tả：\n"BLK"    前些日子因暴风雨的缘故，监狱墙壁破损严重，导致小部phút逃犯趁机逃跑，听闻探子回报，"HIR "%s"BLK"就藏匿于"HIR "%s"BLK"一带，若你能顺利剿灭此逃犯，大王定会重重有赏。\n"BLK"奖励：1500金\n",
                        npc->get_name(),range_value( time / 60, 0, MAX_NUMBER ),  npc->get_name(),name);
                send_user( me, "%c%c%s", 0x51, '1', result );                        
        }
	
	if ( who->get_task("robber.bonus") )
	{
		result = sprintf("［师爷任务］\n"BLK"剿灭%s（第%d环）\n"BLK" nhiệm vụ：\n"BLK"    助周国衙门的师爷剿灭"HIR "%s"BLK"。\n"BLK"    消灭%s： 1/1（已经完成）\n"BLK" nhiệm vụ miêu tả：\n"BLK"    据报说最近有一个悍匪"HIR "%s"BLK"在"HIR "%s"BLK"一带活动，他杀人越货无恶不作，十phút猖獗。\n"BLK"    现在衙门人手严重不足，只希望少侠能出手相助。如果能成功剿灭这贼，本师爷会给少侠丰厚报酬的。\n"BLK"任务奖励："HIR "500金",
                	who->get_task("robber.name"),who->get_task("robber#") + 1,who->get_task("robber.name"),who->get_task("robber.name"),who->get_task("robber.name"),who->get_task("robber.map"));
                send_user( me, "%c%c%s", 0x51, '1', result ); 
	}
        else if(     stringp( id = who->get_task("robber") ) 
        &&    ( npc = find_char(id) ) && npc->is_robber() )    // 30 phút钟
        {
                time = 3600 - gone_time( npc->get("birthday") );
                map = get_map_object( get_z(npc) );
                name = map ? map->get_name() : "Bản đồ vô danh";
                result = sprintf("［师爷任务］\n"BLK"剿灭%s（第%d环）\n"BLK" nhiệm vụ：\n"BLK"    助周国衙门的师爷剿灭"HIR "%s"BLK"。\n"BLK"    消灭%s： 0/1（thặng余时间%dphút钟）\n"BLK" nhiệm vụ miêu tả：\n"BLK"    据报说最近有一个悍匪"HIR "%s"BLK"在"HIR "%s"BLK"一带活动，他杀人越货无恶不作，十phút猖獗。\n"BLK"    现在衙门人手严重不足，只希望少侠能出手相助。如果能成功剿灭这贼，本师爷会给少侠丰厚报酬的。\n"BLK"任务奖励："HIR "500金",
                	npc->get_name(),who->get_task("robber#") + 1,npc->get_name(),npc->get_name(),
                        range_value( time / 60, 0, MAX_NUMBER ),npc->get_name(),name );
                send_user( me, "%c%c%s", 0x51, '1', result );                        
        }
        if( stringp( id = who->get_task("banditi") ) 
        &&    ( npc = find_char(id) ) && npc->is_banditi() )    // 30 phút钟
        {
                z = npc->get("xy.z");
                x = npc->get("xy.x");
                y = npc->get("xy.y");
                time = 3600 - gone_time( npc->get("birthday") );
                map = get_map_object( get_z(npc) );
                name = map ? map->get_name() : "Bản đồ vô danh";
                result = sprintf("［剿匪任务］\n"BLK" nhiệm vụ：\n"BLK"    消灭在" HIR "%s(%d,%d)" BLK "附近出没的" HIR "%s"BLK"。\n" BLK "%s : 0/1  （thặng余时间：%dphút钟）。\n"BLK" nhiệm vụ miêu tả：\n"BLK"    近期听闻在"HIR "%s(%d,%d)"BLK"附近有匪徒%s正纠结同伙，打算对我村进行洗劫，希望大侠能仗义剿匪。",
                        name, x, y, npc->get_name(), npc->get_name(),range_value( time / 60, 0, MAX_NUMBER ),name,x,y,npc->get_name() );

                send_user( me, "%c%c%s", 0x51, '1', result );                        
        }
	if(  who->get_task("banditi_bonus") )
	{
                result = sprintf("［剿匪任务］\n"BLK" nhiệm vụ：\n"BLK"    消灭在" HIR "%s(%d,%d)" BLK "附近出没的" HIR "%s" BLK "。\n" BLK "%s : 1/1  （已经完成）。\n"BLK" nhiệm vụ miêu tả：\n"BLK"    近期听闻在"HIR "%s(%d,%d)"BLK"附近有匪徒"HIR "%s"BLK"正纠结同伙，打算对我村进行洗劫，希望大侠能仗义剿匪。",
                        who->get_task("banditi_map"), who->get_task("banditi_x"), who->get_task("banditi_y"), who->get_task("banditi_name"), who->get_task("banditi_name"),who->get_task("banditi_map"), who->get_task("banditi_x"), who->get_task("banditi_y"), who->get_task("banditi_name"));
		if ( stringp(result) )
			send_user( me, "%c%c%s", 0x51, '1', result );
	}	

	if( time = who->get_quest("thief.time") )
	{
		if ( 1800 < gone_time(time) )
		{
			who->delete_quest("thief.bonus");
			who->delete_quest("thief.task");
			who->delete_quest("thief.flag");
			who->delete_quest("thief.time");		
		}
		else if( time = who->get_quest("thief.bonus") ) 
		{
			switch( time )
			{
				case 1:
					result = sprintf("[老村长任务]\n"BLK"教训小偷\n"BLK" nhiệm vụ：\n"BLK"    到" HIR "%s" BLK "的" HIR "%d，%d" BLK "一带，把" HIR "%s" BLK "教训一顿后回报新手村的老村长。(已经完成)\n" BLK "教训%s：1/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    昨天晚上%s又光顾了我们的村子。尽管村子没有损失什么贵重的东西，但是就这样饶过了那贼，老夫实在不甘心。刚才有村民说见到%s在%s的（%d，%d）附近出现。如果%s能助老夫一臂之力，教训一下%s。让他知道村子的厉害就好了。",
							who->get_quest("thief.map"),x,y,who->get_quest("thief.name"),who->get_quest("thief.name"),who->get_quest("thief.name"),who->get_quest("thief.name"),who->get_quest("thief.map"),x,y,NPC_RANK_D->get_respect_2(who),who->get_quest("thief.name"));        
					if ( stringp(result) )
						send_user( me, "%c%c%s", 0x51, '1', result );      	
					break;
				case 4:
					result = sprintf("[老村长任务]\n"BLK"追捕窃贼\n"BLK" nhiệm vụ：\n"BLK"    追捕逃窜到" HIR "%s(%d，%d)" BLK "附近的" HIR "%s" BLK "，并将被窃的贵重品交还给新手村老村长。任务已经完成。\n" BLK "失窃的贵重品：1/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    那个可恶的%s昨天晚上又光顾了我们的村子！竟将村中的贵重物品洗劫一空！据村民回报最后一次见到%s是在%s的（%d，%d）附近。 如今村卫团人手实在不足，实在无法phút派出更多的人手了。如果%s能帮忙夺回失窃的物品，老夫定会重重有赏。",who->get_quest("thief.map"),who->get_quest("thief.x"),who->get_quest("thief.y"),who->get_quest("thief.name"),who->get_quest("thief.name"),who->get_quest("thief.name"),who->get_quest("thief.map"),who->get_quest("thief.x"),who->get_quest("thief.y"),NPC_RANK_D->get_respect_2(who));
					if ( stringp(result) )
						send_user( me, "%c%c%s", 0x51, '1', result );  
					break;	
			}
		}
		else if( time = who->get_quest("thief.flag") ) 		
		{
			switch( time )
			{
			       	case 1 : // 2. 失窃任务(人物)
			                if(     stringp( id = who->get_quest("thief.thief") ) 
			                &&    ( npc = find_char(id) ) && npc->is_thief() )    // 30 phút钟
			                {
			                        z = who->get_quest("thief.z");
			                        x = who->get_quest("thief.x");
			                        y = who->get_quest("thief.y");
			                        time = 1800 - gone_time( who->get_quest("thief.time") );
			                        map = get_map_object(z);
			                        name = map ? map->get_name() : "Bản đồ vô danh";
						result = sprintf("[老村长任务]\n"BLK"教训小偷\n"BLK" nhiệm vụ：\n"BLK"    到" HIR "%s" BLK "的" HIR "%d，%d" BLK "一带，把" HIR "%s" BLK "教训一顿后回报新手村的老村长。任务thặng余时间%dphút钟。\n" BLK "教训%s：0/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    昨天晚上%s又光顾了我们的村子。尽管村子没有损失什么贵重的东西，但是就这样饶过了那贼，老夫实在不甘心。刚才有村民说见到%s在%s的（%d，%d）附近出现。如果%s能助老夫一臂之力，教训一下%s。让他知道村子的厉害就好了。",
							name,x,y,npc->get_name(),range_value( time / 60, 0, MAX_NUMBER ),npc->get_name(),npc->get_name(),npc->get_name(),name,x,y,NPC_RANK_D->get_respect_2(who),npc->get_name());                        	
			                        send_user( me, "%c%c%s", 0x51, '1', result );                                
			                }
			                break;
			                
			       	case 2 : // 1. 失窃任务(物品)
			                if( ( time = 1800 - gone_time( who->get_quest("thief.time") ) ) > 0 )    // 15 phút钟
			                {
			                        z = who->get_quest("thief.z");
			                        x = who->get_quest("thief.x");
			                        y = who->get_quest("thief.y");
			//                      time = 1800 - gone_time( who->get_quest("thief.time") );
			                        map = get_map_object(z);
			                        name = map ? map->get_name() : "Bản đồ vô danh";
						result = sprintf("[老村长任务]\n"BLK"找回丢失的物品\n"BLK" nhiệm vụ:\n"BLK"    到" HIR "%s" BLK "的" HIR "%d，%d" BLK "一带，找回八姑丢失的" HIR "%s" BLK "，并带回给老村长。任务thặng余时间%dphút钟。\n" BLK "%s：0/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    昨天八姑又来我这诉苦，说自己的东西又丢了。实话说，老夫实在不想管这些鸡婆的事，但是又不能坐视不理……这次八姑丢失了一%s%s，据她描述应该是在%s的（%d，%d）一带丢失的。怎样？%s是否愿意帮老夫这个忙，将八姑丢失的东西找回来呢？"
							,name,x,y,who->get_quest("thief.thief"),range_value( time / 60, 0, MAX_NUMBER ),who->get_quest("thief.thief"),who->get_quest("thief.unit"),who->get_quest("thief.thief"),name,x,y,NPC_RANK_D->get_respect_2(who)); 
			                        send_user( me, "%c%c%s", 0x51, '1', result );                                
			                }
			                break;
			
			       	case 3 : // 5. 寻物任务
			                if( ( time = 1800 - gone_time( who->get_quest("thief.time") ) ) > 0 )    // 15 phút钟
			                {
						result = sprintf("[老村长任务]\n"BLK"物品采购\n"BLK" nhiệm vụ：\n"BLK"    帮老村长买一%s"HIR "%s"BLK"。回来后记得用给予指令（快捷键G）将物品交给老村长。\n"BLK"%s：0/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    %s，见到你刚好。老夫原本想今天出门买些东西，没想到一把年纪，老毛病风湿又犯了。现在腰疼得实在受不了。不知道%s是否愿意帮老夫跑一趟，买%s%s回来呢？\n", who->get_quest("thief.unit"), who->get_quest("thief.thief"), who->get_quest("thief.thief"),NPC_RANK_D->get_respect_2(who),NPC_RANK_D->get_respect_2(who),who->get_quest("thief.unit"),who->get_quest("thief.thief")); 			                        
			                        send_user( me, "%c%c%s", 0x51, '1', result );                                
			                }
			                break;
			
			       	case 4 : // 3. 失窃任务(人物)
			                if(     stringp( id = who->get_quest("thief.thief") ) 
			                &&    ( npc = find_char(id) ) && npc->is_thief() )    // 15 phút钟
			                {
			                        z = who->get_quest("thief.z");
			                        x = who->get_quest("thief.x");
			                        y = who->get_quest("thief.y");
			                        time = 1800 - gone_time( who->get_quest("thief.time") );
			                        map = get_map_object(z);
			                        name = map ? map->get_name() : "Bản đồ vô danh";
			                        result = sprintf("[老村长任务]\n"BLK"追捕窃贼\n"BLK" nhiệm vụ：\n"BLK"    追捕逃窜到" HIR "%s(%d，%d)" BLK "附近的" HIR "%s" BLK "，并将被窃的贵重品交还给新手村老村长。任务thặng余时间%dphút钟。\n" BLK "失窃的贵重品：0/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    那个可恶的%s昨天晚上又光顾了我们的村子！竟将村中的贵重物品洗劫一空！据村民回报最后一次见到%s是在%s的（%d，%d）附近。 如今村卫团人手实在不足，实在无法phút派出更多的人手了。如果%s能帮忙夺回失窃的物品，老夫定会重重有赏。",map->get_name(),x,y,npc->get_name(),range_value( time / 60, 0, MAX_NUMBER ),npc->get_name(),npc->get_name(),map->get_name(),x,y,NPC_RANK_D->get_respect_2(who));                        
			                        send_user( me, "%c%c%s", 0x51, '1', result );                                
			                }
			                break;
			        }			
		}
	}
        
        if( time = who->get_quest("escort.flag") )
        {
                if( time == 1 )    // 1. Nhiệm vụ áp tiêu(物品)
                {
                        time = 2400 - gone_time( who->get_quest("escort.time") );    // 40 phút钟

                        if( who->get_quest("escort.id") && who->get_quest("escort.member") )
                                result = sprintf("［Nhiệm vụ áp tiêu］\n"BLK"thặng %d phút\n" BLK "Cùng đội hữu %s hộ tống vật phẩm đến " HIR "%s" BLK " chỗ\n",
                                        range_value( time / 60, 0, MAX_NUMBER ), who->get_quest("escort.member"), who->get_quest("escort.name") );
                        else    result = sprintf("［Nhiệm vụ áp tiêu］\n"BLK"thặng %d phút\n" BLK "Hộ tống vật phẩm đến " HIR "%s" BLK " chỗ\n", 
                                        range_value( time / 60, 0, MAX_NUMBER ), who->get_quest("escort.name") );
                        send_user( me, "%c%c%s", 0x51, '1', result );                                        

                        if(     objectp( npc = me->get_quest("escort.robber#") )    // 寻找蒙面人
                        &&      npc->is_escort_robber_2()    // 被动乞丐
                        &&      npc->get("gold") )
                        {
                                result = sprintf("［突发任务］\n"BLK"把" HIR " %d " BLK "金给" HIR "%s" BLK "。\n",
                                        npc->get("gold"), npc->get_name() );
                                send_user( me, "%c%c%s", 0x51, '1', result );         
                        }                               
                }
                else if( time == 2 )    // 2. Nhiệm vụ áp tiêu(人物)
                {
                        time = 2400 - gone_time( who->get_quest("escort.time") );

                        if( time < 0 )
                                result = sprintf("［Nhiệm vụ áp tiêu］\n"BLK"thất bại, quay về báo với " HIR "Vận Tiêu Lão Đầu" BLK "。\n");
                        else if( who->get_quest("escort.id") && who->get_quest("escort.member") )
                                result = sprintf("［Nhiệm vụ áp tiêu］\n"BLK"thặng %d phút\n" BLK "Cùng đội hữu %s hộ tống đến" HIR "%s" BLK " chỗ\n",
                                        range_value( time / 60, 0, MAX_NUMBER ), who->get_quest("escort.member"), who->get_quest("escort.name") );
                        else    result = sprintf("［Nhiệm vụ áp tiêu］\n"BLK"thặng %d phút\n" BLK "Hộ tống đến" HIR "%s" BLK " chỗ\n", 
                                        range_value( time / 60, 0, MAX_NUMBER ), who->get_quest("escort.name") );
                        send_user( me, "%c%c%s", 0x51, '1', result );                                        
                }
        }

        if(     stringp( id = who->get_task("rascal") ) 
        &&    ( npc = find_char(id) ) && npc->is_rascal() )    // 40 phút钟
        {
                z = npc->get("xy.z");
                x = npc->get("xy.x");
                y = npc->get("xy.y");
                time = 2400 - gone_time( npc->get("birthday") );
                map = get_map_object( get_z(npc) );
                name = map ? map->get_name() : "Bản đồ vô danh";
                result = sprintf("［巡逻任务］\n"BLK"thặng %d phút\n" BLK "去" HIR "%s(%d,%d)" BLK "教训" HIR "%s" BLK "。\n",
                        range_value( time / 60, 0, MAX_NUMBER ), name, x, y, npc->get_name() );
                send_user( me, "%c%c%s", 0x51, '1', result );                        
        }

        if( time = who->get_save_2("build.flag") ) switch( time )    // 40 phút钟
        {
      default : if(     stringp( id = who->get_task("rascal2") ) 
                &&    ( npc = find_char(id) ) && npc->is_rascal_2() )
                {
                        z = npc->get("xy.z");
                        x = npc->get("xy.x");
                        y = npc->get("xy.y");
                        time = 2400 - gone_time( npc->get("birthday") );
                        map = get_map_object( get_z(npc) );
                        name = map ? map->get_name() : "Bản đồ vô danh";
                        result = sprintf("［建设任务］\n"BLK"thặng %d phút\n" BLK "去" HIR "%s(%d,%d)" BLK "教训" HIR "%s" BLK "。\n",
                                range_value( time / 60, 0, MAX_NUMBER ), name, x, y, npc->get_name() );
                        send_user( me, "%c%c%s", 0x51, '1', result );                                
                }
                break;
       case 2 : if( ( time = gone_time( who->get_save_2("build.time") ) ) < 2400 )
                {
                        result = sprintf("［建设任务］\n"BLK"thặng %d phút\n" BLK "去财政官那儿帮手" HIR "算几天帐" BLK "。\n", ( 2400 - time ) / 60 );
                        send_user( me, "%c%c%s", 0x51, '1', result );
                }
                break;
       case 3 : if( ( time = gone_time( who->get_save_2("build.time") ) ) < 2400 )
                {
                        result = sprintf("［建设任务］\n"BLK"thặng %d phút\n" BLK "将食物送给城中四处的" HIR "工匠" BLK "。\n", ( 2400 - time ) / 60 );
                        send_user( me, "%c%c%s", 0x51, '1', result );
                }
                break;
       case 4 : if( ( time = gone_time( who->get_save_2("build.time") ) ) < 2400 )
                {
                        result = sprintf("［建设任务］\n"BLK"thặng %d phút\n" BLK "寻“" HIR "%s" BLK "”给内政官。\n", 
                                ( 2400 - time ) / 60, who->get_save_2("build.item") );
                        send_user( me, "%c%c%s", 0x51, '1', result );                                
                }
                break;
        }

        if(   ( time = gone_time( who->get_save_2("relation.time") ) ) < 2400    // 40 phút钟
        &&    ( x = who->get_save_2("relation.city") ) && ( y = who->get_save_2("relation.city2") ) )
        {
                switch( who->get_save_2("relation.flag") )
                {
              default : result = sprintf("［外交任务］\n"BLK"thặng %d phút\n" BLK "作为%s使节同" HIR "%s" BLK "进行" HIR "友好" BLK "外交。\n", 
                                ( 2400 - time ) / 60, CITY_D->get_city_name(x), CITY_D->get_city_name(y) );
                        break;
               case 2 : result = sprintf("［外交任务］\n"BLK"thặng %d phút\n" BLK "作为%s使节同" HIR "%s" BLK "进行" HIR "交恶" BLK "外交。\n", 
                                ( 2400 - time ) / 60, CITY_D->get_city_name(x), CITY_D->get_city_name(y) );
                        break;
                }
                send_user( me, "%c%c%s", 0x51, '1', result );
        }
        if(     who->is_scholar()
        &&    ( x = who->get_save_2("advice.city") ) && ( y = who->get_save_2("advice.city2") ) )
        {
                switch( who->get_save_2("advice.type") )
                {
              default : result = sprintf("［纵横任务］\n"BLK"作为%s使节同" HIR "%s" BLK "共商" HIR "结盟" BLK "大计。\n",
                                CITY_D->get_city_name(x), CITY_D->get_city_name(y) );
                        break;
               case 2 : result = sprintf("［纵横任务］\n"BLK"作为%s使节对" HIR "%s" BLK "提出" HIR "警告" BLK "。\n",
                                CITY_D->get_city_name(x), CITY_D->get_city_name(y) );
                        break;
                }
                send_user( me, "%c%c%s", 0x51, '1', result );
        }
        if (me->get_fam_name())
        {	
		if (me->get_save_2("mastertask.type")>0)
		{

			switch(me->get_save_2("mastertask.type"))
			{
			case 1:
				if (me->get_save_2("mastertask.status")!=99)
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Bắt yêu quái (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Bắt "HIR " %s "BLK" rồi trở về.\n"BLK"%s  0/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Hiện nay thiên hạ đại loạn, yêu ma quỷ quái hoành hành bốn bể. Sư phụ muốn ta đi bắt một con yêu quái về giao nộp. Nghe nói ở %s , đi tìm thử xem \nTrước khi đi bắt yêu quái hãy nhớ đến chủ tiệm tạp hóa mua Dây Càn Khôn. Sử dụng dụng kỹ năng “Bắt Bảo Thú” để hoàn thành nhiệm vụ. huyết khí của quái vật càng thấp, tỷ lệ bắt được càng cao.",me->get_save_2("mastertask.time")+1,me->get_save_2("mastertask.targetname"),me->get_save_2("mastertask.targetname"),me->get_save_2("mastertask.target"));
				else
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Bắt yêu quái (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Bắt "HIR " %s "BLK" rồi trở về.\n"BLK"%s  1/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Hiện nay thiên hạ đại loạn, yêu ma quỷ quái hoành hành bốn bể. Sư phụ muốn ta đi bắt một con yêu quái về giao nộp. Nghe nói ở %s , đi tìm thử xem \nTrước khi đi bắt yêu quái hãy nhớ đến chủ tiệm tạp hóa mua Dây Càn Khôn. Sử dụng dụng kỹ năng “Bắt Bảo Thú” để hoàn thành nhiệm vụ. huyết khí của quái vật càng thấp, tỷ lệ bắt được càng cao.",me->get_save_2("mastertask.time")+1,me->get_save_2("mastertask.targetname"),me->get_save_2("mastertask.targetname"),me->get_save_2("mastertask.target"));
				break;				
			case 2:
				if (me->get_save_2("mastertask.status")!=99)					
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Rèn luyện (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Sư phụ muốn ta tăng lên %d điểm Kinh nghiệm rồi mới được trở về. Tiêu diệt quái vật, hoàn thành những nhiệm vụ khác để có được kinh nghiệm cũng sẽ hoàn thành nhiệm vụ này.\n"BLK"Tăng lên kinh nghiệm:  %d/%d\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Ngươi phải Sư phụ muốn ta tăng lên %d điểm Kinh nghiệm rồi mới được trở về. Tiêu diệt quái vật, hoàn thành những nhiệm vụ khác để có được kinh nghiệm cũng sẽ hoàn thành nhiệm vụ này rồi mới được trở về.\n", me->get_save_2("mastertask.time")+1,me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetxy"),me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetpic")    );
				else
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Rèn luyện (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Sư phụ muốn ta tăng lên %d điểm Kinh nghiệm rồi mới được trở về. Tiêu diệt quái vật, hoàn thành những nhiệm vụ khác để có được kinh nghiệm cũng sẽ hoàn thành nhiệm vụ này.\n"BLK"Tăng lên kinh nghiệm:  %d/%d\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Ngươi phải Sư phụ muốn ta tăng lên %d điểm Kinh nghiệm rồi mới được trở về. Tiêu diệt quái vật, hoàn thành những nhiệm vụ khác để có được kinh nghiệm cũng sẽ hoàn thành nhiệm vụ này rồi mới được trở về.\n", me->get_save_2("mastertask.time")+1,me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetpic")    );
				break;
			case 3:
				if (me->get_save_2("mastertask.status")!=99)					
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Du lịch (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Tăng lên %d điểm Tiềm Năng.\n"BLK"Tăng lên Tiềm Năng:  %d/%d\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Nếu muốn đạt đến đỉnh cao trong võ học, ngươi phải biết khổ luyện cho nhiều.Vi sư hy vọng ngươi ra ngoài vừa đi vừa khổ luyện.\n", me->get_save_2("mastertask.time")+1,me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetxy"),me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetpic")    );
				else
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Du lịch (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Tăng lên %d điểm Tiềm Năng.\n"BLK"Tăng lên Tiềm Năng:  %d/%d\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Nếu muốn đạt đến đỉnh cao trong võ học, ngươi phải biết khổ luyện cho nhiều.Vi sư hy vọng ngươi ra ngoài vừa đi vừa khổ luyện.\n", me->get_save_2("mastertask.time")+1, me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetpic"),me->get_save_2("mastertask.targetpic")    );
				break;
			case 4:
				if (me->get_save_2("mastertask.status")==0)
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Thu mua (Lượt thứ %d )\n"BLK" nhiệm vụ：\n"BLK"    Đi tìm %s .\n"BLK" nhiệm vụ miêu tả：\n:"BLK"    Dạo gần đây một số vật phẩm của bổn môn dự trữ không đủ, cần gấp phải ra ngoài đi thu mua một số vật phẩm về. %s bảo ta đi tìm %s hỏi rõ tình hình, xem có thể giúp được gì không.\n", 
						me->get_save_2("mastertask.time")+1, name ="/sys/task/quest1"->get_manager_name(me->get_fam_name()),name,name );
				else					
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Thu mua (Lượt thứ %d )\n"BLK" nhiệm vụ：\n"BLK"    Đi tìm %s mua %s , và giao cho %s\n"BLK" nhiệm vụ miêu tả：\n"BLK"    %s dạo gần đây báo rằng một số vật phẩm của bổn môn dự trữ không đủ, cần gấp phải ra ngoài đi thu mua một số vật phẩm về. Sư phụ bảo ta đi tìm hỏi rõ tình hình, xem có thể giúp được gì không.\n"BLK"    Do ngày thường không cẩn thận lưu ý, bổn môn có một số vật phẩm dự trữ rõ ràng không đủ, nếu như không tranh thủ thời gian giải quyết, sẽ làm cho bổn môn gặp không ít rắc rồi. Nhưng lúc này ngươi làm việc không đủ, %s nhờ ta đi %s thu mua %s về giao cho ông ta. Lúc giao cho ông ta dùng dùng chỉ lệnh dành cho thì được rồi(Alt＋G).\n", 
						me->get_save_2("mastertask.time")+1, me->get_save_2("mastertask.giftname"), me->get_save_2("mastertask.targetname"),name ="/sys/task/quest1"->get_manager_name(me->get_fam_name()),name,name,me->get_save_2("mastertask.giftname"), me->get_save_2("mastertask.targetname")  );					
				break;		
			case 5:
				if (me->get_save_2("mastertask.status")==0)
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Thu thập (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Đi tìm %s .\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Sư phụ bảo ta đi tìm %s xem có giúp đỡ được chuyện gì hay không.\n", 
						me->get_save_2("mastertask.time")+1, name ="/sys/task/quest1"->get_manager_name(me->get_fam_name()),name );
				else
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Thu thập (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Thu thập 5 %s , và giao cho %s .\n"BLK" nhiệm vụ miêu tả：\n"BLK"    %s khi tìm được ta, %s vội vàng bảo ta đi thu thập %s . Nghe nói ở %s , ta phải đi tìm thử.\n", 
						me->get_save_2("mastertask.time")+1, me->get_save_2("mastertask.targetname") ,name ="/sys/task/quest1"->get_manager_name(me->get_fam_name()),name,name,me->get_save_2("mastertask.targetname"),me->get_save_2("mastertask.targetpic")  );
				break;
			case 6:
				result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Thăm viếng (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Thăm viếng %s\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Sư phụ bế quan tu hành đã mấy hôm rồi, cũng không biết tình hình mấy người bạn già của sư phụ như thế nào. Trước đây họ thường đến thăm viếng sư phụ, nếu lâu quá sư phụ không đi thăm hỏi lại họ thì cũng có phần thất lễ. Do đó sư phụ bảo ta đi tới %s để hỏi thăm sức khoẻ %s giùm sư phụ.",me->get_save_2("mastertask.time")+1,me->get_save_2("mastertask.targetname"),me->get_save_2("mastertask.targetcity"),me->get_save_2("mastertask.targetname"));
				break;	
			case 7:
				if (me->get_save_2("mastertask.status")==99)
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Tìm tung tích (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"  Tìm tung tích Vân Du Thương Nhân\n"BLK"Linh dược：1/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Vân Du Thương Nhân đã cho tinh Linh dược, ta phải về bẩm báo với sư phụ .",
					me->get_save_2("mastertask.time")+1);
				else
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Tìm tung tích (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Tìm kiếm Vân Du Thương Nhân\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Gần đây sư phụ muốn thử luyện chế một loại đơn dược, nhưng luyện chế loại đơn dược này cần phải có linh dược làm dược dẫn, Nghe nói ở chỉ có Vân Du Thương Nhân mới có loại linh dược này. Sư phụ sai ta thử đi tìm Vân Du Thương Nhân, nếu như tìm được ông ta thì xin ông ta loại linh dược này\n",
						me->get_save_2("mastertask.time")+1);
				break;
			case 8:
				status = me->get_save_2("mastertask.status");
				if ( status == 2 || status == 99 )
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Hiệp trợ trị an (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Tiêu diệt lưu manh ngoài thành.\n"BLK"Lưu manh：1/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"%s Giám Ngục Quan gửi thư nhờ vả, khi ta đi vào %s Nghe nói ở có tên lưu manh ngoài thành sinh sự. ",
						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.targetname"),name);
				else if ( status == 0 )
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Hiệp trợ trị an (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Tìm %s Giám Ngục Quan\n"BLK" nhiệm vụ miêu tả：\n"BLK"    %s Giám Ngục Quan gửi thư, nói %s tình hình càng ngày càng ác liệt, một tên lưu manh sinh sự đã làm náo loạn cả lên, mong ta đến hỗ trợ.\n", 
						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.targetname"),name,name);
				else if( stringp( id = who->get_save_2("mastertask.target") ) && ( npc = find_char(id) ) && npc->get("user")==who->get_number() )
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Hiệp trợ trị an (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Tiêu diệt lưu manh ngoài thành.\n"BLK"Lưu manh：0/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"%s Giám Ngục Quan gửi thư nhờ vả, khi ta đi vào %s Nghe nói ở có tên lưu manh ngoài thành sinh sự. ",
						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.targetname"),name);
				break;		
			case 9:
				if ((status=me->get_save_2("mastertask.status"))==99 || status == 2)
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Tuần sơn (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Tuần tra ở bổn môn, bắt hết kẻ khả nghi\n"BLK"Kẻ khả nghi：1/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Có đệ tử bẩm báo ở Sư môn xuất hiện kẻ khả nghi.\n", 
						me->get_save_2("mastertask.time")+1   );
				else if( stringp( id = who->get_save_2("mastertask.target") ) && ( npc = find_char(id) ) && npc->get("user")==who->get_number() )
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Tuần sơn (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Tuần tra ở bổn môn, bắt hết kẻ khả nghi\n"BLK"Kẻ khả nghi：0/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    Có đệ tử bẩm báo ở Sư môn xuất hiện kẻ khả nghi.\n", 
						me->get_save_2("mastertask.time")+1   );					
				break;				
//			case 10:
			default:
				if ( me->get_save_2("mastertask.status")==99 )
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Môn phái tỷ thý (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Đi tới %s phái tỷ thý võ công.\n"BLK"%s đệ tử：1/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    %s Chưởng môn đã sai người đến đây phát thư mời đệ tử của bổn môn ra tỷ thí võ công, tự bổ sung vào những điểm khiếm khuyết của võ học, sư phụ lệnh cho ta đi, ta không thể bỏ lỡ cơ hội lần này, thời gian có hạn, ta phải lập tức đi ngay. Đến mục tiêu, nói chuyện với đệ tử của môn phái này, bạn sẽ được chuyển đến võ trường, đánh bại đối thủ để hoàn thành nhiệm vụ.\n", 
						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.targetname"),name,name  );
				else
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Môn phái tỷ thý (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Đi tới %s phái tỷ thý võ công.\n"BLK"%s đệ tử：0/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    %s Chưởng môn đã sai người đến đây phát thư mời đệ tử của bổn môn ra tỷ thí võ công, tự bổ sung vào những điểm khiếm khuyết của võ học, sư phụ lệnh cho ta đi, ta không thể bỏ lỡ cơ hội lần này, thời gian có hạn, ta phải lập tức đi ngay. Đến mục tiêu, nói chuyện với đệ tử của môn phái này, bạn sẽ được chuyển đến võ trường, đánh bại đối thủ để hoàn thành nhiệm vụ.\n", 
						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.targetname"),name,name  );
				break;	
/*			case 11:
				status = me->get_save_2("mastertask.status");
				if (status==0)
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Trù tập (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Tìm %s hỏi hắn rồi giải quyết vấn đề.\n"BLK" nhiệm vụ miêu tả：\n"BLK"    %s như đang bị tâm thần, hãy đến hỏi hắn thử xem.\n", 
						me->get_save_2("mastertask.time")+1, name="/sys/task/quest1"->get_manager_name(me->get_fam_name()),name );	
				else
				if (status!=99)				
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Trù tập (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    Kiếm %d mang về cho tư khố\n"BLK" nhiệm vụ miêu tả：\n"BLK"    %s như đang bị tâm thần, ngươi hãy qua hỏi hắn thử xem.Cùng %s trò chuyện mới biết tiền bạc đang thiếu trầm trọng.Ở %s , ngươi hãy xuống núi kiếm thêm tiền về.\n", 
						me->get_save_2("mastertask.time")+1, me->get_save_2("mastertask.targetxy"), name="/sys/task/quest1"->get_manager_name(me->get_fam_name()),name,name );	
				else
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Lượt thứ"HIR " %d "BLK" nhiệm vụ Trù tập hoàn thành，quay về bẩm báo sư phụ.\n", 
						me->get_save_2("mastertask.time")+1 );								
				break;	
			case 12:
				status = me->get_save_2("mastertask.status");
				if (status==0)
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Truy sát phản đồ (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    速去%s找王府总管，帮助其解决困难。\n"BLK" nhiệm vụ miêu tả：\n"BLK"    师傅刚刚收到了一封来自%s王府总管的紧急求助信，看来是发生了什么大事。在师傅的命令下，我整装前往%s。\n", 
						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.targetname"),name,name );	
				else
				if (status<4)				
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Truy sát phản đồ (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"  追杀%s的%s\n"BLK"%s    0/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    师傅刚刚收到了一封来自%s王府总管的紧急求助信，看来是发生了什么大事。在师傅的命令下，我整装往%s出发。\n"BLK"    与%s总管见面之后，我也了解到了事态的严重性。对于叛国之徒是绝对不能轻饶的！\n"BLK"    %s总管的手下已经送来了确切信报，%s正在"HIR "%s(%d,%d)"BLK"一带逃窜。而且%s买通了那一带的山贼流氓做他的贴身保镖。\n"BLK"    为了%s的机密不被泄漏出去，权宜之计只有杀了他。\n", 
						me->get_save_2("mastertask.time")+1,id=me->get_save_2("mastertask.targetname"), name=me->get_save_2("mastertask.targetpic"),name,id,id,id,id,name,me->get_save_2("mastertask.giftname"),((z=me->get_save_2("mastertask.targetxy"))/1000),z%1000,name,id);	
				else
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Truy sát phản đồ (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"  追杀%s的叛徒%s\n"BLK"%s    1/1\n"BLK" nhiệm vụ miêu tả：\n"BLK"    师傅刚刚收到了一封来自%s王府总管的紧急求助信，看来是发生了什么大事。在师傅的命令下，我整装往%s出发。\n"BLK"    与%s总管见面之后，我也了解到了事态的严重性。对于叛国之徒是绝对不能轻饶的！\n"BLK"    %s总管的手下已经送来了确切信报，%s正在"HIR "%s(%d,%d)"BLK"一带逃窜。而且%s买通了那一带的山贼流氓做他的贴身保镖。\n"BLK"    为了%s的机密不被泄漏出去，权宜之计只有杀了他。\n", 
						me->get_save_2("mastertask.time")+1,id=me->get_save_2("mastertask.targetname"), name=me->get_save_2("mastertask.targetpic"),name,id,id,id,id,name,me->get_save_2("mastertask.giftname"),((z=me->get_save_2("mastertask.targetxy"))/1000),z%1000,name,id);	
				break;	
			default:
				status = me->get_save_2("mastertask.status");
				if (status==0)
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Truy bắt Thích khách (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    去%s找到王府总管，并听从其命令协助追捕刺客。\n"BLK" nhiệm vụ miêu tả：\n"BLK"    师傅刚刚收到了一封来自%s王府总管的来信，信中说昨晚有刺客潜入了王府企图行刺王爷。尽管最后暗杀失败，王爷也没受伤，但刺客却逃掉了。总管希望我们协助他抓拿刺客，以免后患。\n", 
						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.targetname"),name);	
				else
					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Truy bắt Thích khách (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    追捕已经逃窜到%s的蒙面刺客。\n"BLK"刺客首领	%d/1\n"BLK"蒙面刺客	%d/4\n"BLK" nhiệm vụ miêu tả：\n"BLK"    师傅刚刚收到了一封来自%s王府总管的来信，信中说昨晚有刺客潜入了王府企图行刺王爷。尽管最后暗杀失败，王爷也没受伤，但刺客却逃掉了。总管希望我们协助他抓拿刺客，以免后患。\n"BLK"    来到%s后，得知行刺者已经逃窜到%s后便失去了踪影。总管大人相信他们仍潜藏在%s。\n"BLK"    大人已经颁发了追杀令，一旦发现目标，格杀无论！\n", 
						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.giftname"),me->get_save_2("mastertask.y"),me->get_save_2("mastertask.x"),id=me->get_save_2("mastertask.targetname"),id,name,name);	
//				else
//					result = sprintf("Nhiệm Vụ Sư Môn\n"BLK"Truy bắt Thích khách (Lượt thứ %d)\n"BLK" nhiệm vụ：\n"BLK"    追捕已经逃窜到%s的蒙面刺客。\n"BLK"刺客首领	1/1\n"BLK"蒙面刺客	4/4\n"BLK" nhiệm vụ miêu tả：\n"BLK"    师傅刚刚收到了一封来自%s王府总管的来信，信中说昨晚有刺客潜入了王府企图行刺王爷。尽管最后暗杀失败，王爷也没受伤，但刺客却逃掉了。总管希望我们协助他抓拿刺客，以免后患。\n"BLK"    来到%s后，得知行刺者已经逃窜到%s后便失去了踪影。总管大人相信他们仍潜藏在%s。\n"BLK"    大人已经颁发了追杀令，一旦发现目标，格杀无论！\n", 
//						me->get_save_2("mastertask.time")+1, name=me->get_save_2("mastertask.giftname"),id=me->get_save_2("mastertask.targetname"),id,name,name);	
				break;	*/																									
			}

//			if (time()<me->get_save_2("mastertask.endtime"))
//				result = result + BLK + sprintf("任务thặng余 %d phút钟\n", (me->get_save_2("mastertask.endtime") - time()) / 60);
//			else
//				result = result + BLK + "超时未完成，任务失败。\n";
                        send_user( me, "%c%c%s", 0x51, '1', result );				
				
		}
		if (me->get_save_2("masterfight.status")>0)
                {		        
		        result = "［师门进级任务］\n"BLK"Sư môn Khiêu chiến, đánh bại sư thúc.\n";
		        send_user( me, "%c%c%s", 0x51, '1', result );
		}
	}


        if( result == "" ) 
        {                        
                result = "Bạn hiện tại không có nhiệm vụ.\n";
                send_user( me, "%c%c%s", 0x51, '1', result );
        }

	return 1;
}
