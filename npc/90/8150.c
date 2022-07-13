
#include <npc.h>
#include <ansi.h>
#include <skill.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

#define CUR_VERSION	1

void do_betrayer( string arg );
void do_getback( string arg );
void do_abandon( string arg );
void do_welcome(string arg);
int get_level_potential(int level);

// 函数：获取人物造型
int get_char_picid() { return 9815; }

// 函数：构造处理
void create()
{
        set_name("Thân Công Báo");

        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
                "betrayer"      : (: do_betrayer :),
                "getback"      : (: do_getback :),
                "abandon"      : (: do_abandon :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
        int id = getoid( this_object() );
	string tmp="";
 	if ( who->get_legend(TASK_2_00,23) && !who->get_legend(TASK_2_00,24) && who->get_save("baifang_ms_3") != 1)
		tmp = sprintf(ESC HIY "Bái sư\ntalk %x# welcome.1\n",id);
        more_look_menu( who, sprintf( " %s :\n Làm chuyện hấp dẫn càng thêm hấp dẫn, đây là nguyên tắc hành sự của chúng ta từ xưa đến nay.\n"
//                ESC "叛离师门。\n" + sprintf( "talk %x# betrayer.?\n", id ) +
//                ESC "领回潜能和金钱。\n" + sprintf( "talk %x# getback.?\n", id ) +
                ESC "Bỏ kỹ năng nghề.\n" + sprintf( "talk %x# abandon.?\n", id ) +
		tmp +
                ESC "Rời khỏi.\nCLOSE\n", get_name() ) );
}

// 函数：叛师处理
void do_betrayer( string arg )
{
	int i,size, count;
        object me, who, *inv,oFamily,npc;
        string name,cTitle;
return;
        me = this_object();  who = this_player();

        if( ( name = who->get_fam_name() ) == "" ) return;

	if ( "sys/school/shouxi"->can_betray(who) == 0 )
		return ;
        if( who->get_reincarnation() )
        {
                send_user( who, "%c%s", ':', sprintf( "%s：\n你跟我开玩笑吧？名满天下的%s大侠竟会背叛师门？恕在下没办法帮你这个忙了。\n",
                        me->get_name(), who->get_name() ) );
                return;
        }
        if (time() - who->get_save("betray_time")<24*3600)
        {
                send_user( who, "%c%s", ':', sprintf( "%s：\n    您距离上次背叛师门的时间不足一天，还请多加考虑。\n",
                        me->get_name() ) );
                return;
        }
        if (who->get_save_2("betray.pot")>0)
        {
                send_user( who, "%c%s", ':', sprintf( "%s：\n    您上次叛师所返回的经验和潜能还没有取回，不能再叛师。\n",
                        me->get_name() ) );
                return;
        }
        if( arg == "?" )
        {
                send_user( who, "%c%s", ':', sprintf( "%s：\n    脱离“%s”将会失去所有师门技能，您考虑清楚了吗？\n"
                        ESC "是的。\ntalk %x# betrayer\n"
                        ESC "我再想想……\nCLOSE\n", me->get_name(), name, getoid(me) ) );
        }
        else
        {
                inv = who->get_all_equip();
                oFamily = inv[FAMILY_POSITION];
                inv -= ({ 0,oFamily});
                if (sizeof(inv)>0)
                {
                        send_user( who, "%c%s", ':', sprintf( "%s：\n    背叛师门必须将身上的所有装备卸载下来。\n" ,
                                me->get_name() ) );
                        return ;
                }
		if (who->get_perform("03191") )
		{
			send_user( who, "%c%s", ':', sprintf( "%s：\n    狂暴状态下不能更换师门。\n" ,
	                                me->get_name() ) );
			return;                               
		}     
		if (who->get_perform("03192") )
		{
			send_user( who, "%c%s", ':', sprintf( "%s：\n    防御状态下不能更换师门。\n" ,
	                                me->get_name() ) );
			return; 
		} 
		if ( who->get_perform("02221#") )
		{
			send_user( who, "%c%s", ':', sprintf( "%s：\n    封魔免疫状态下不能更换师门。\n" ,
	                                me->get_name() ) );
			return; 
		}	
		if (who->get_perform("02222#") )
		{
			send_user( who, "%c%s", ':', sprintf( "%s：\n    眩晕免疫状态下不能更换师门。\n" ,
	                                me->get_name() ) );
			return; 
		}                
                FAMILY_D->family_channel( name, 0, sprintf( HIY "%s(%d)决定脱离“%s”门下！！！",
                        who->get_name(), who->get_number(), name ) );

                who->log_legend( sprintf( "您决定脱离“%s”门下！", name ) );
		cTitle = who->get_fam_title();
		if ( cTitle )
		{
			who->delete_title(cTitle);
			who->set_fam_title("");	
		}
		count = 0;
                switch( name )
                {
        case FAMILY_1 :
        		count += get_level_potential(who->get_skill(0211));
        		who->delete_skill(0211);
        		count += get_level_potential(who->get_skill(0212));
                        who->delete_skill(0212);
                        count += get_level_potential(who->get_skill(0316));
                        who->delete_skill(0316);
                        count += get_level_potential(who->get_skill(0317));
                        who->delete_skill(0317);
                        count += get_level_potential(who->get_skill(0319));
                        who->delete_skill(0319);
                        break;

        case FAMILY_2 :
        		count += get_level_potential(who->get_skill(0221));
        		who->delete_skill(0221);
        		count += get_level_potential(who->get_skill(0231));
                        who->delete_skill(0231);
                        count += get_level_potential(who->get_skill(0222));
                        who->delete_skill(0222);
                        count += get_level_potential(who->get_skill(0232));
                        who->delete_skill(0232);
                        count += get_level_potential(who->get_skill(0324));
                        who->delete_skill(0324);
                        count += get_level_potential(who->get_skill(0325));
                        who->delete_skill(0325);
                        count += get_level_potential(who->get_skill(0329));
                        who->delete_skill(0329);
                        break;

        case FAMILY_3 :
        		count += get_level_potential(who->get_skill(0241));
        		who->delete_skill(0241);
        		count += get_level_potential(who->get_skill(0251));
                        who->delete_skill(0251);
                        count += get_level_potential(who->get_skill(0242));
                        who->delete_skill(0242);
                        count += get_level_potential(who->get_skill(0252));
                        who->delete_skill(0252);
                        count += get_level_potential(who->get_skill(0348));
                        who->delete_skill(0348);
                        count += get_level_potential(who->get_skill(0349));
                        who->delete_skill(0349);
                        break;

        case FAMILY_4 :
        		count += get_level_potential(who->get_skill(0261));
        		who->delete_skill(0261);
        		count += get_level_potential(who->get_skill(0363));
                        who->delete_skill(0363);
                        count += get_level_potential(who->get_skill(0364));
                        who->delete_skill(0364);
                        count += get_level_potential(who->get_skill(0365));
                        who->delete_skill(0365);                        
                        count += get_level_potential(who->get_skill(0368));
                        who->delete_skill(0368);
                        break;

        case FAMILY_5 :
        		count += get_level_potential(who->get_skill(0271));
        		who->delete_skill(0271);
        		count += get_level_potential(who->get_skill(0411));
                        who->delete_skill(0411);
                        count += get_level_potential(who->get_skill(0413));
                        who->delete_skill(0413);
                        count += get_level_potential(who->get_skill(0414));
                        who->delete_skill(0414);
                        count += get_level_potential(who->get_skill(0417));
                        who->delete_skill(0417);
                        count += get_level_potential(who->get_skill(0418));
                        who->delete_skill(0418);
                        break;

        case FAMILY_6 :
        		count += get_level_potential(who->get_skill(0421));
        		who->delete_skill(0421);
        		count += get_level_potential(who->get_skill(0422));
                        who->delete_skill(0422);
                        count += get_level_potential(who->get_skill(0423));
                        who->delete_skill(0423);
                        count += get_level_potential(who->get_skill(0424));
                        who->delete_skill(0424);
                        count += get_level_potential(who->get_skill(0425));
                        who->delete_skill(0425);
                        count += get_level_potential(who->get_skill(0429));
                        who->delete_skill(0429);
                        break;

        case FAMILY_7 :
        		count += get_level_potential(who->get_skill(0281));
        		who->delete_skill(0281);
        		count += get_level_potential(who->get_skill(0501));
                        who->delete_skill(0501);
                        count += get_level_potential(who->get_skill(0511));
                        who->delete_skill(0511);
                        count += get_level_potential(who->get_skill(0513));
                        who->delete_skill(0513);
                        count += get_level_potential(who->get_skill(0521));
                        who->delete_skill(0521);
                        count += get_level_potential(who->get_skill(0531));
                        who->delete_skill(0531);
                        count += get_level_potential(who->get_skill(0591));
                        who->delete_skill(0591);
                        break;
                }
                who->set_fam_name(0);
                who->set_fam_position(0);
                who->set_fam_title(0);
                who->set_fam_order(0);
                who->set_fam_master(0);
                who->set_fam_time( time() );

                "/sys/sys/count"->add_family(name, -1);
                who->set_save("famrec", 1);

                "/cmd/user/gift"->init_gift_point(who);
                who->set_save("betray_time", time());

                USER_ENERGY_D->count_all_prop(who);
	        USER_ENERGY_D->count_max_yuan(who);
	        if ( oFamily )	//拿走门派信物
	        {
	        	oFamily->remove_from_user();
                	destruct( oFamily );
                	USER_ENERGY_D->count_all_prop(who);
	        }

		if( npc = who->get("soldier") )
		{
			npc->remove_from_scene();
			destruct(npc);
			who->delete("soldier");
		}

	        if( arrayp( inv = who->get("zombie") ) && (size = sizeof(inv) ) )
	        {
	                for( i = 0; i < size; i ++ ) if( inv[i] )
	                {
				inv[i]->remove_from_scene();
				destruct(inv[i]);
	                }
	                who->delete("zombie");
	        }
	        //给予新手信物
		oFamily = new("/item/09/0908");
		if ( oFamily && !who->restore_equip(oFamily) )
		{
			destruct(oFamily);
		}
		who->set_save_2("betray.time", CUR_VERSION);
//		who->set_save_2("betray.pot", count);
//		send_user( who, "%c%s", ':', sprintf( "%s：\n    您这次背叛，积累下%d点潜能和%d金，您可以向我领取。\n",
//			me->get_name(), count, count*20 ) );	
		who->set_attack_move(0);	
		send_user( get_scene_object_2(who, USER_TYPE), "%c%d%d%w", 0x23, getoid(who), 
                                who->get_armor_code(), who->get_armor_color_1() ); 		
        }
}

int get_level_potential(int level)
{
	int i, ret;
	ret = 0;
	for (i=0;i<level;i++)
	{
		ret += ((i+1)*(i+1)+1);
	}
	return ret;
}

// 函数：取回潜能
void do_getback( string arg )
{
	int money, pot, get, less;
        object me, who;
        string result;

        me = this_object();  who = this_player();

        if (who->get_save_2("betray.pot")<=0)
        {
                send_user( who, "%c%s", ':', sprintf( "%s：\n    你跟我开玩笑吧？我这里并没有什么东西可以让你领取的。\n",
                        me->get_name()  ) );
                return;
        }
        if (arg=="?")
        {
        	result = sprintf("%s：\n    因为这次官方的门派调整所对阁下造成不便，我们特别为您提供了一次潜能和金钱的补偿机会。记住，补偿的机会只有一次，当你把所有的补偿都领取完毕之后，我不会再给予你任何的补偿，一定要好好把握应用。\n"
                	ESC "确定\ntalk %x# getback\n"
                	ESC "取消。\nCLOSE\n",
        		me->get_name(), getoid(me));
        	send_user( who, "%c%s", ':', result);
        	return;
        }
	pot = who->get_max_potential() - who->get_potential();
	money = who->get_max_cash() - who->get_cash();
	money /= 20;
	get = who->get_save_2("betray.pot");
	if (get>pot) get = pot;
	if (get>money) get = money;
	who->add_save_2("betray.pot", -get);
	who->add_potential(get);
	who->add_cash(get*20);
	less = who->get_save_2("betray.pot");
	if (less>0)
		result = sprintf("%s：\n    您领取了%d潜能%d金，尚余%d潜能%d金没有领取。\n", me->get_name(), get, get*20, less, less*20);
	else
		result = sprintf("%s：\n    您领取了%d潜能%d金，全部领取完毕。\n", me->get_name(), get, get*20);
	send_user( who, "%c%s", ':', result);
}


// 函数：放弃生活技能
void do_abandon( string arg )
{
	int skill, i, id;
        object me, who;
        string result;
        string * name = ({ "Đầu Bếp", "Rèn Đúc", "Luyện Đơn", "May Mặc", "Điêu Khắc", "Cơ Quan", "Thái Dã", "Dược Sư",  });

        me = this_object();  who = this_player();
	id = getoid( me );
        if (arg=="?")
        {
        	if (who->get_skill(610)+who->get_skill(620)+who->get_skill(630)+who->get_skill(640)+who->get_skill(650)+who->get_skill(660)+who->get_skill(670)+who->get_skill(680)==0)
        	{
        		result = sprintf("%s：\n    Bạn không có kĩ năng cuộc sống\n", me->get_name());
        		send_user( who, "%c%s", ':', result);
        		return ;        		
        	}
        	result = sprintf(" %s :\n Ngươi muốn bỏ đi kỹ năng nghề nào?\n", me->get_name());
        	for (i=610;i<=680;i+= 10)
        	{
        		if (who->get_skill(i))
        		{
        			result += sprintf(ESC "Bỏ đi %s \ntalk %x# abandon.%d\n", name[(i-610)/10], id, i);
        		}
        		
        	}
        	result += ESC "Hủy Bỏ.\nCLOSE\n",
        	send_user( who, "%c%s", ':', result);
        	return;
        }
        skill = to_int(arg);
        if (who->get_skill(skill)==0)
        {
        	result = sprintf("%s：\n    Bạn không có kĩ năng này\n", me->get_name());
        	send_user( who, "%c%s", ':', result);
        	return ;        		
        }        
        who->delete_skill(skill);
        result = sprintf("%s：\n    Bạn đã huỷ bỏ kĩ năng này\n", me->get_name());
	send_user( who, "%c%s", ':', result);
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p;
        object who,item,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
		if ( who->get_legend(TASK_2_00,23) && !who->get_legend(TASK_2_00,24) && who->get_save("baifang_ms_3") != 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大王叫你来拜访我吗？你可以看看现在和将来在我这会有什么需要的，呵呵。年轻人，有朝气，真好啊。\n", me->get_name()));
			who->set_save("baifang_ms_3",1);
			USER_TASK_D->send_task_intro(who,2,TID_ZHOUGUO,21);
		}
		if ( who->get_save("baifang_ms_1") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_2") == 1 && who->get_save("baifang_ms_3") == 1 && who->get_save("baifang_ms_4") == 1 && who->get_save("baifang_ms_5") == 1 )
		{
			who->set_legend(TASK_2_00,24);
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHOUGUO,21,"访问周国名士(完成)" );
		}
        	break;
        }
}