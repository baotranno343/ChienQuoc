
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <cmd.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：师父识别
int is_master() { return 1; }

// 函数：获取门派名称
string get_fam_name() { return "Vân Mộng Cốc"; }

// 函数：获取人物造型
int get_char_picid() { return 9715; }

// 函数：获取升级顺序
int get_fam_order() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 有自己的do_look函数
int is_self_look() { return 1; }

int get_level() { return 150; }

void do_skill();
void do_quest();
void do_giveup();
void do_giveup2();
void do_apprentice(string arg);
void accept_quest();
void task_info();
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name( "Quỷ Cốc Tử" );
        set_skill(0281, 150);
        set_skill(0541, 150);
        set_skill(0501, 150);
        set_skill(0543, 150);
        set_skill(0511, 150);
        set_skill(0542, 150);
//        set_skill(0513, 150);
//        set_skill(0521, 150);
        set_skill(0531, 150);
        set_skill(0544, 150);
        set_skill(0591, 150);
        set_skill(0545, 150);
        set_2( "talk", ([
                "skills"                : (: do_skill :),
                "quest"                 : (: do_quest :),
                "giveup"                : (: do_giveup :),
                "giveup2"               : (: do_giveup2 :),
                "apprentice"            : (: do_apprentice :),    
                "accept_quest"            : (: accept_quest :), 
                "task_info"             : (: task_info :),                    
                "welcome"		: (: do_welcome :),
        ]));
       set_2( "good", ([
       		"01" : "/item/79/1010",
       		"02" : "/item/79/1020",                
       		"03" : "/item/60/0010",
       		"04" : "/item/60/7020",
       		"05" : "/item/61/0010",
       		"06" : "/item/61/7020",
       		"07" : "/item/65/0010",
       		"08" : "/item/65/7020",
       		"09" : "/item/66/0010",
       		"10" : "/item/66/7020",                
       		"11" : "/item/88/0010",
       		"12" : "/item/88/7020",
       		"13" : "/item/87/7010",
       		"14" : "/item/87/7020",              
        ]) );
	set("mpLegend2",([0:({32*45+22,32*45+25,32*45+28,}),]));
        setup();
}

// 函数：点击出现界面
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_45,21) && !who->get_legend(TASK_45,22) )
		tmp += sprintf(ESC HIY "世子的病\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_45,22) && !who->get_legend(TASK_45,25) )
		tmp += sprintf(ESC HIY "药引\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_45,25) && !who->get_legend(TASK_45,28) )
		tmp += sprintf(ESC HIY "宝鼎\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_45,28) && !who->get_legend(TASK_45,29) )
		tmp += sprintf(ESC HIY "药引\ntalk %x# welcome.1\n",getoid(me));

	if ( who->get("master.type") != 69 && sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		TASK_MASTER_D->do_look( who, me ); 
	
}
// 函数：技能学习界面
void do_skill(  ) { LEARN_CMD->learn_menu( this_player(), this_object() ); }

// 函数：领取任务
void do_quest(  ) { TASK_MASTER_D->do_quest( this_player(), this_object() ); }

// 函数：取消任务
void do_giveup(  ) { TASK_MASTER_D->do_giveup( this_player(), this_object() ); }

// 函数：取消任务2
void do_giveup2(  ) { TASK_MASTER_D->do_giveup2( this_player(), this_object() ); }

// 函数：拜师
void do_apprentice( string arg  ) { TASK_APPRENTICE_D->do_apprentice( this_player(), this_object(), arg ); }
//接受任务
void accept_quest(  ) { TASK_MASTER_D->accept_quest( this_player(), this_object() ); }
//任务信息
void task_info(  ) { TASK_MASTER_D->task_info( this_player(), this_object() ); }

// 接收心爱物品
int accept_object( object player, object obj ) 
{
	object who = this_object();
	return TASK_MASTER_D->accept_object( who, player, obj ); 
}

// 函数：删除师门技能
void delete_family_skill( object who )
{
        mapping skls;
        object file;
        string *name, result;
        int skill, level, i, size;

        skls = get_skill_dbase();
        name = keys(skls);
        size = sizeof(name);
        result = sprintf( "您决定脱离“%s”门下！损失：", get_fam_name() );
        for( i = 0; i < size; i ++ )
        {
                skill = to_int( name[i] );
                if( level = who->get_skill(skill) )
                {
                        if( file = load_object( SKILL->get_skill_file(skill) ) ) 
                                result = sprintf("%s%s(%d) ", result, file->get_name(), level);
                        else    result = sprintf("%s%s(%d) ", result, name[i], level);
                }
                who->delete_skill(skill);
        }

        who->log_legend(result);
}


void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_legend(TASK_45,21) && !who->get_legend(TASK_45,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    世子这病还真有点棘手，容我考虑考虑，待会你再来找我吧。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,22) && !who->get_legend(TASK_45,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我终于找到了一张上古仙方有类似病的记载，应该说世子是中了降而非病，王侯之家这种类似的事太多频繁了，唉，不过也不是老朽能够评测的，我只尽我医师的本分吧，其他不要问我太多了。解降需要许多世间罕见的药材，其中最重要的药引是诛仙阵中凝结了诸多魂气的虎皮，此种虎皮混合魂气的极阴之气与虎本身极阳之气糅合一起，乃解此种降的最佳药引，你先去诛仙阵与虎谋皮吧……\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,23) && !who->get_legend(TASK_45,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    赵王迁吩咐你来的时候难道一点都不着急么，既然如此，那老朽也不必为你们瞎操心了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_45,24) && !who->get_legend(TASK_45,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    药引有了，可是此等秘药还需要特殊的制药容器，待会我再交代你吧，你先去周围转转休息一会。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,25) && !who->get_legend(TASK_45,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我有各种炼药的宝鼎，可惜炼解降的药的那种青云宝鼎却被紫云洞的精灵偷去了，近段时间老朽病人和弟子太多实在无暇顾及他们，既然你现在需要炼这种药，就前去紫云洞将青云宝鼎弄回来吧，我也不知道是哪个精灵身上，反正问他们要就没错了，那些精灵非常自私，是不会将宝鼎共享的，所以他们一定会随身携带的，但是他们应该不懂宝鼎大小如意之法，即使偷去了也不能用，真不知道那些小家伙老是偷我的吃饭家伙做什么，太调皮了。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,26) && !who->get_legend(TASK_45,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    宝鼎上有增加药性的苻刻，没有那种专用宝鼎，我炼丹效果会大打折扣，你还是再去找找吧。就在紫云洞那些精灵身上。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_45,27) && !who->get_legend(TASK_45,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，你居然杀了他们，你你你，唉，事已至此，我也不好多说你什么，为甚为了救得一人性命就要伤及许多人性命呢，他们只不过调皮而已，你教训教训就是了，断不至于狠心置死啊，唉，我现在需要闭关炼丹，你先走开，老朽现在不想看到你，等我炼好了你拿丹速速走人。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_45,28) && !who->get_legend(TASK_45,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你鬼鬼祟祟望什么望，过来，虽然我对你非常痛恨，但是医者父母心，该给你我还是会尽心尽力的给你做好，这盒御风丹花了老夫三天三夜炼制，终于还是成了，你送回给赵王迁，告诉他这盒中4枚丹药分别在第一日、第二日、第四日、第八日分四次都在午时阳气最旺之时服用，另外每日阴气最旺的子时给他喝千年人参为主熬成的补汤，两者相辅而成，相信不出其他意外十日内必将痊愈。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_legend(TASK_45,21) && !who->get_legend(TASK_45,22) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_45,22);
			who->add_exp(48000);
			who->add_potential(750);
			who->add_cash(50000);
			send_user(who,"%c%s",';',"求医（2）经验 48000 潜能 750 金钱 50000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,61,"" );
			me->do_welcome(1);
        	}	
		break;
	case 3:
        	if ( who->get_legend(TASK_45,22) && !who->get_legend(TASK_45,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_45,23);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YUNMENZE,"Vân Mộng Cốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YUNMENZE,1,"求医（3）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"求医（3）");
        	}
        	break;
	case 4:
		if ( who->get_legend(TASK_45,24) && !who->get_legend(TASK_45,25) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"虎皮",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_45,25);
			who->add_exp(52000);
			who->add_potential(790);
			who->add_cash(52000);
			send_user(who,"%c%s",';',"求医（3）经验 52000 潜能 790 金钱 52000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YUNMENZE,1,"" );
			me->do_welcome(1);
        	}	
		break;
	case 5:
        	if ( who->get_legend(TASK_45,25) && !who->get_legend(TASK_45,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_45,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YUNMENZE,"Vân Mộng Cốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YUNMENZE,2,"求医（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"求医（4）");
        	}
        	break;
	case 6:
		if ( who->get_legend(TASK_45,27) && !who->get_legend(TASK_45,28) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"宝鼎",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_45,28);
			who->add_exp(52000);
			who->add_potential(790);
			who->add_cash(52000);
			send_user(who,"%c%s",';',"求医（4）经验 52000 潜能 790 金钱 52000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YUNMENZE,2,"" );
			me->do_welcome(1);
        	}	
		break;		
	case 7:
        	if ( who->get_legend(TASK_45,28) && !who->get_legend(TASK_45,29) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			TASK_LEGEND_D->give_item(who,"item/98/0228",1);
        		who->set_legend(TASK_45,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YUNMENZE,"Vân Mộng Cốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YUNMENZE,3,"求医（5）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"求医（5）");
        	}
        	break;
	case 99:
		TASK_MASTER_D->do_look( who, me ); 
		break;
        }
}