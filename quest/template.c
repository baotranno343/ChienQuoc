#include <ansi.h>
#include <time.h>

int question_number_number;//问题的个数,相当于几题。
int content_size;//文件大小。
mixed str=({});
int *temp_order =({});
void create()
{
	int size,index;
	string* content=({});	
	string* info = ({});
	string file = read_file("quest/answer.dat");
	if(!file)
	{
		return;
	}
	content = explode(file,"\n");
	if(!content)
	{
		return;
	}
	size = sizeof(content); 
	if(!size)
	{
		return;
	}//读问题以及选项
	content_size = size;
	for(index = 0; index < size; index++)
	{
		if(index != size - 1)
		{
			info = explode(content[index],"|");
			if(!info)
			{
				return;
			}
			str+= ({info});
		}
		else 
		{
			question_number_number = to_int(content[size-1]);//这里保存要回答问题的个数.
		}
	}
	for(index = 0; index < content_size - 1; index++)//这里减去选题数所占用的位。
	{
		temp_order +=({index});
	}
}
//做一些合法性检查,并且传回实际的题目序号。
int validate_question(object player)
{
	int question_number,actual_order,size,str_size;
	int* question_order = ({}); 		
	question_order = player->get_save_2("question.order");
	if(!(size = sizeof(question_order)))//没有问题次序。
	{
		return -1;
	}
	question_number = player->get_save_2("question.number");//获得第几题。	
	if(question_number >= size)//回答题目数超过或者等于选择题目数,这里检查数组索引是否越界。
	{
		return -1;
	}
	actual_order = question_order[question_number];//获得实际的题目序号。
	if(!(str_size = sizeof(str)))//这里检查str是否有效。
	{
		return -1;
	}
	if(actual_order >= str_size)//实际的题目序号大于或者等于最大的题目数,这里检查数组索引是否越界。
	{
		return -1;
	}
	return actual_order;	
}
//给予选项
void select_choice(object player)
{
	int size,index,actual_order,i;		
	string * res = ({});
	string* tmp = ({});
	actual_order = validate_question(player);//一些合法性判断。
	if(actual_order == -1)
	{
		return;
	}
	size = sizeof(str[actual_order]);
	if(size == 0) //问题和对应的选项内容为空。
	{
		return;
	}
	//打乱选项。
	for(index = 1; index < size; index++)//这里除掉第一项(该项为问题)
	{
		res += ({str[actual_order][index]});
	}
	for(index = 1; index < size; index++)//同上
	{
		i = random(sizeof(res));
		tmp += ({ res[i] });
		//这里是使用一个默认数组,并且抽取一个就减一个,并且从剩余的里面进行再次随机
		res -= ({ res[i] });
	}
	player->set_save_2("question.choices",tmp);//保存选项。			
}
//给予题目函数
void give_question(object player,object npc)
{
	int question_number,size,index,actual_order,choice_size;
	string dailogue;
	int* question_order = ({}); 
	string* tmp = ({});		
	actual_order = validate_question(player);//进行合法性判断。
	if(actual_order == -1)
	{
		return;
	}
	question_number = player->get_save_2("question.number");
	size = sizeof(str[actual_order]);
	if(size == 0) //问题和对应的选项内容为空。
	{
		return;
	}
	player->set_save_2("question.answer",str[actual_order][1]);//保存对应问题的正确答案
	tmp = player->get_save_2("question.choices");
	if(!(choice_size = sizeof(tmp)))
	{
		return;
	}
	//取得目标问题信息并且得到目标问题
	dailogue = npc->get_name()+"：		\n"+sprintf("第%d题：",question_number+1)+str[actual_order][0]+"\n";//这里获得问题描述以及问题次序。
	for(index = 0; index < choice_size; index++)//这里将显示有sizeof(tmp)个选项。
	{
		dailogue += sprintf(ESC"%s\ntalk %x# answer.%d\n",tmp[index],getoid(npc),11+index);
	}
	dailogue += ESC "离开\n";	
	send_user(player,"%c%s",':',dailogue);	
}
//选择答题的顺序 
void select_question(object player)
{
	int index,i,question_number;
	int *nTemp =({});
	int *question_order=({});//这里要将它清空,在之前没有初始化
	question_number = player->get_save_2("question.number");
	if(!content_size||!question_number_number)
	{
		return;
	}
	nTemp = temp_order;
	for(index = 0; index < question_number_number - question_number; index++)
	{
		i = nTemp[random(sizeof(nTemp))];
		question_order += ({ i });
		//这里是使用一个默认数组,并且抽取一个就减一个,并且从剩余的里面进行再次随机
		nTemp -= ({ i });
	}
	player->set_save_2("question.order",question_order);//保存选题次序		
}
//每次回答正确以后给予的经验和潜能奖励
void exp_potential_bonus(object player)
{
	int level,exp_bonus,potential_bonus;
	int times = player->get_save_2("question.number");//现在完成的题目数。
	if(0 ==(level = player->get_level()))
	{
		level = 1;
	}
	if ( player->get_online_rate() == 50 )//三小时到五小时
	{
		exp_bonus = (level*times*times+level*20)/2;
		potential_bonus = (level * times)/2;
		player->add_exp(exp_bonus);
		player->add_potential(potential_bonus);
		send_user( player, "%c%s", ';', sprintf("由于你正确作答，获得了%d经验，%d潜能的奖励！",exp_bonus,potential_bonus)); 
	}
	if(player->get_online_rate() == 100)//正常情况 3小时内
	{
		exp_bonus = (level*times*times+level*20);
		potential_bonus = (level * times);
		player->add_exp(exp_bonus);
		player->add_potential(potential_bonus);
		send_user( player, "%c%s", ';', sprintf("由于你正确作答，获得了%d经验，%d潜能的奖励！",exp_bonus,potential_bonus)); 		
	}
	if ( player->get_online_rate() == 0 )//不健康时间内
	{
		send_user(player,"%c%s",';',"不健康游戏时间无经验和潜能。");	
	}
	player->delete_save_2("question.answer");////在答对以后，也清除本次选题的标志。
	player->delete_save_2("question.choices");
}
//在回答问题以后给出的提示,并且继续给题。
void feed_back(object player, object npc,int fail_tags)
{
	mixed mixTime;
	int times,day;
	mixTime = localtime(time());
	times = player->get_save_2("question.number");//现在完成的题目数。
	day = player->get_save_2("question.day");
	if(!question_number_number)
	{
		return;
	}
	if(times == question_number_number)
	{
		//send_user(player,"%c%s",':',npc->get_name()+"：\n你今天已经接受了本神10道问题的考验，若想本神继续考验你，请明天再来找我吧！ \n"+ESC "离开\n");
		__FILE__->answer_bonus(player,npc);
		return;
	}
	if(!fail_tags)
	{
		__FILE__->exp_potential_bonus(player);
	}
	if(day != mixTime[TIME_YDAY])
	{
		send_user(player,"%c%s",'!',npc->get_name()+"：\n开始新一天的答题了！");
		return;
	}
	__FILE__->select_choice(player);//错误的也要重新给出选题。
	__FILE__->give_question(player,npc);
}


//清除任务标志
void clear_tags(object player)
{
	player->set_save_2("question.number",0);//题目数
	player->delete_save_2("question.order");//选题次序
	player->delete_save_2("question.totalfail");//10道题是否全部正确标志
	player->delete_save_2("question.choices");//这里要将选项清除。之前没有将他清除。
}
//检查题目是否正确函数
void check_question(object player,object npc,int flag)
{
	int question_number,actual_order,size,choice_size,fail_tags;
	int *tmp =({});
	if(!player->get_save_2("question.answer"))//没有正确答案
	{
		return;
	}
	tmp =player->get_save_2("question.choices");
	if(!(choice_size = sizeof(tmp)))//没有选择项。
	{
		return;
	}
	if(flag >= 11 +  choice_size)//flag不能超过11+选项数。
	{
		return;
	}
	if(player->get_save_2("question.answer")!= tmp[flag-11])//玩家点击选项与正确答案不符。
	{
		fail_tags = 1;
		send_user( player, "%c%s", ';', "由于你回答错误，因而无法获得相应的奖励，你最好按Alt+H打开帮助界面进行查询！");
		player->delete_save_2("question.answer");////在答错以后，也清除本次选题的标志。
		player->delete_save_2("question.choices");
	}
	else
	{
		fail_tags = 0;
	}
	player->add_save_2("question.totalfail",fail_tags);
	player->add_save_2("question.number",1);
	__FILE__->feed_back(player, npc,fail_tags);//对于这个检查后问题的反馈。		
}
void move_to_user(object player,string filename,int flag)
{
	 int move_result;
	 object item;
	 item = new( filename );
         if(!item)
         {
                   return;
         }
         if(flag)
         {
         	item->set_level(1);
         }
         if( move_result = item->move(player, -1) ) 
         {
                  item->add_to_user(move_result);
                  send_user(player,"%c%s",'!',sprintf(HIY"%s在与AYA狮子的问答对决中略胜一筹，获得了%s的奖励！",player->get_name(),item->get_name()));	                         
         }
         else
         {
         	 destruct(item);
         }   
}
//连续正确回答10道题后给予的额外奖励
void extra_bonus(object player)
{
	string filename;
	int move_result;
	object item;
	int rand = random100();
	if(sizeof_inventory(player, 1, MAX_CARRY) >= MAX_CARRY )
	{
		send_user(player,"%c%s",'!',HIY"由于你的包包已满，无法获得相应奖品！");
		return;
	}
	if(rand < 1)//随机1级晶石。
	{
		 if( load_object( filename = STONE_FILE->get_diamond_file() ) )
                {
	 		move_to_user(player,filename,1);
                }
	}
	else if(rand < 2)//随机进阶书
	{
		if( load_object( filename= BOOK_FILE->get_book_file() ) )
		{
			move_to_user(player,filename,0);
		}
	}
	else if(rand < 4)//随机宠物技能丹(精元丹)
	{
		move_to_user(player,"item/44/4488",0);
	}
	else  if(rand < 5)//紫参丹
	{
		move_to_user(player,"item/91/9167",0);		
	}
	else if(rand < 15)//藏宝图
	{
		move_to_user(player,"item/std/8000",0);		
	}
	else if(rand < 16)//残图左上角
	{
		move_to_user(player,"/item/std/8001",0);		
	}
	else if(rand < 17)//残图右上角
	{
		move_to_user(player,"/item/std/8002",0);
	}
	else if(rand < 18)//残图左下角
	{
		move_to_user(player,"/item/std/8003",0);
	}
	else if(rand < 19)//残图右下角
	{
		move_to_user(player,"/item/std/8004",0);
	}
	else if(rand < 23)//地瓜粥。
	{
		move_to_user(player,"item/final/33/1702",0);
	}
	else if(rand < 29)//豆腐干
	{
		move_to_user(player,"item/final/33/1703",0);
	}
	else if(rand < 35)//荷包蛋
	{
		move_to_user(player,"item/final/33/1704",0);
	}
	else if(rand < 39)//粘糊糊的饭
	{
		move_to_user(player,"item/final/33/1705",0);
	}
	else if(rand < 43)//特大荷包蛋
	{
		move_to_user(player,"item/final/33/1706",0);
	}
	else if(rand < 47)//水果拼盘
	{
		move_to_user(player,"item/final/33/1707",0);
	}
	else if(rand < 51)//生煮温蔬菜
	{
		move_to_user(player,"item/final/33/1708",0);
	}
	else if(rand < 55)//萝卜棒
	{
		move_to_user(player,"item/final/33/1709",0);
	}
	else if(rand < 59)//水煮大南瓜
	{
		move_to_user(player,"item/final/33/1710",0);
	}
	else if(rand < 63)//绿豆汤
	{
		move_to_user(player,"item/final/33/1750",0);
	}
	else if(rand < 70 )//玉米汤
	{
		move_to_user(player,"item/final/33/1751",0);
	}
	else if(rand < 76)//黄瓜汤
	{
		move_to_user(player,"item/final/33/1752",0);
	}
	else if(rand < 80)//生姜汤
	{
		move_to_user(player,"item/final/33/1753",0);
	}
	else if(rand < 84)//豆浆
	{
		move_to_user(player,"item/final/33/1754",0);
	}
	else if(rand < 88)//好喝的水
	{
		move_to_user(player,"item/final/33/1755",0);
	}
	else if(rand < 92)//高粱酒
	{
		move_to_user(player,"item/final/33/1756",0);
	}
	else if(rand < 96)//山药酒
	{
		move_to_user(player,"item/final/33/1757",0);
	}
	else//珍露酒
	{
		move_to_user(player,"item/final/33/1758",0);
	}
}
//给予question_number_number道题的玩家奖励
void answer_bonus(object player, object npc)
{  
	int level,exp_bonus,potential_bonus,times;
	times = player->get_save_2("question.number");
	if(!question_number_number)
	{
		return;
	}
	if( times != question_number_number)
	{
		return;
	}
	__FILE__->exp_potential_bonus(player);
	if(!player->get_save_2("question.totalfail"))//正确回答10道题的奖励。
	{
		__FILE__->extra_bonus(player);
	}
}
/*这个函数将统一管理前面所有的分信息*/
void do_answer2(object npc,string arg)
{
	int flag;
	object player = this_player();
	if(arg)
	{
		flag = to_int(arg);	
	}	
	switch(flag)
	{
	case 2:	
		if(question_number_number ==player->get_save_2("question.number") )
		{
			send_user(player,"%c%s",':',npc->get_name()+"：\n你今天已经接受了本神10道问题的考验，若想本神继续考验你，请明天再来找我吧！ \n"+ESC "离开\n");
			return;
		}
		if(!player->get_save_2("question.order"))//获得选题次序,只有在没有选题次序的时候 才去选题和给题。
		{
			__FILE__->select_question(player);
		}//而且在这里将选题和选项都打乱并且分开的。所以要在这里加上判断，如果将选题和选项连接在一起的话，就可以只在select_question里面加上判断就可以了。
		if(!player->get_save_2("question.choices"))//在这保存题目选项。
		{
			__FILE__->select_choice(player);
		}
		__FILE__->give_question(player,npc);		
		break;
	case 10..21:
		__FILE__->check_question(player,npc,flag);
		break;	
	}
}
