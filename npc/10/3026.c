
// è‡ªåŠ¨ç”Ÿæˆï¼š/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>
#include <equip.h>

inherit OFFICER;

void do_task();

// å‡½æ•°ï¼šè·å–äººç‰©é€ å‹
int get_char_picid() { return 5505; }
void do_welcome(string arg);

// å‡½æ•°ï¼šæ„é€ å¤„ç†
void create()
{
        set_name("ç¨‹å¼º");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",41);
//        set("legend",({32*11+1}));    
	set("mpLegend",([40:({32*11+1})]));
	set("mpLegend2",([0:({32*46+20,32*46+23,}),40:({32*11+3,32*11+10}),]));
        setup();
}

// å‡½æ•°ï¼šå¯¹è¯å¤„ç†
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 40 && !who->get_legend(TASK_11,1)) || (who->get_legend(TASK_11,1)&&!who->get_legend(TASK_11,3)) ) 
		tmp += sprintf(ESC HIY "å¯»æ‰¾ä¿¡ç‰©\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_11,3) && !who->get_legend(TASK_11,4)) || (who->get_legend(TASK_11,4)&&!who->get_legend(TASK_11,5)) ) 
		tmp += sprintf(ESC HIY "é€å»ä¿¡ç‰©\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_11,9)&&!who->get_legend(TASK_11,10) ) 
		tmp += sprintf(ESC HIY "é€å»ä¿¡ç‰©\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_46,19)&&!who->get_legend(TASK_46,20) ) 
		tmp += sprintf(ESC HIY "é™¤æ‰æ¶åŒª\ntalk %x# welcome.6\n",getoid(this_object())); 
         if ( who->get_legend(TASK_46,20)&&!who->get_legend(TASK_46,23) ) 
		tmp += sprintf(ESC HIY "å¯»å›èµƒç‰©\ntalk %x# welcome.6\n",getoid(this_object())); 
         if ( who->get_legend(TASK_46,23)&&!who->get_legend(TASK_46,24) ) 
		tmp += sprintf(ESC HIY "è½¬äº¤ä¿¡å‡½\ntalk %x# welcome.6\n",getoid(this_object())); 
 
        send_user( who, "%c%s", ':', sprintf( "%sï¼š\n    æˆ‘åªæ˜¯ä¸€ä»‹ç©·è‹¦ä¹¦ç”Ÿï¼Œå®¶å¢ƒè´«å¯’ï¼Œä¸€æ¬¡å¶ç„¶çœ‹è§äº†ç§¦å®«çš„è´è´å°å§ï¼Œå¯¹å¥¹äº§ç”Ÿäº†ä¸€ç§å‰æ‰€æœªæœ‰çš„æ€œçˆ±ä¸çˆ±æ€œã€‚\n", get_name())
        + tmp +
        ESC"ç¦»å¼€"
         );
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
       	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if (who->get_level() >= 40 && !who->get_legend(TASK_11,1))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    è‡ªä»æˆ‘è§è¿‡è´è´å°å§åï¼Œå°±ä¸€ç›´æœæ€æš®æƒ³ï¼Œæ— å¥ˆå®¶å¢ƒè´«å¯’ï¼Œæƒ³é€ç‚¹ä¸œè¥¿ç»™è´è´å°å§è¡¨è¾¾æˆ‘çš„å¿ƒæ„ï¼Œå¯æ˜¯å®åœ¨æ²¡æœ‰ä»€ä¹ˆèƒ½æ‹¿å¾—å‡ºæ‰‹çš„ã€‚\n    æˆ‘ä¸€ç›´å°±æƒ³é€å¥¹ä¸€æ¡çç é¡¹é“¾ï¼Œå¯ä½ çœ‹æˆ‘è¿™æ ·å­ï¼Œå°±çŸ¥é“ä¹°ä¸èµ·ï¼Œä¸è¿‡æˆ‘å¬è¯´ä¸œæµ·æ¸”æ‘çš„è™¾å…µèŸ¹å°†ä¼šæœ‰ï¼Œä½ èƒ½å»ç»™æˆ‘æ‰¾ä¸€ä¸²æ¥å—ï¼Ÿ\n"ESC"æ¥å—ä»»åŠ¡\ntalk %x# welcome.2\n"ESC"ç¦»å¼€", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_11,1) && !who->get_legend(TASK_11,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    å¦‚æœæ²¡æœ‰ä¿¡ç‰©ï¼Œé‚£è´è´å°å§åˆæ€èƒ½ä¸æˆ‘ç›¸è¯†å‘¢ï¼Ÿ\n"ESC"ç¦»å¼€", me->get_name()));
        	else if ( who->get_legend(TASK_11,2) && !who->get_legend(TASK_11,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    æ„Ÿè°¢ä½ æ›¿æˆ‘æ‰¾åˆ°äº†åˆé€‚çš„ä¿¡ç‰©ï¼Œå¯æˆ‘ä¸€ä»‹ä¹¦ç”Ÿæ€èƒ½è¿›å…¥è¿™å•åºœå‘¢ï¼Ÿ\n"ESC"å®Œæˆä»»åŠ¡\ntalk %x# welcome.3\n"ESC"ç¦»å¼€", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_11,3) && !who->get_legend(TASK_11,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    å”‰ï¼Œæˆ‘è¿å¥—è±¡æ ·çš„å‡ºé—¨è¡£æœéƒ½æ²¡æœ‰ï¼Œå¯’é…¸å•Šï½ï½è¿˜æ˜¯ä½ ç»™æˆ‘é€å»è¿™ä¿¡ç‰©å¥½å—ï¼Ÿ\n"ESC"æ¥å—ä»»åŠ¡\ntalk %x# welcome.4\n"ESC"ç¦»å¼€", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_11,4) && !who->get_legend(TASK_11,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    è´è´å°å§æ€ä¹ˆå›ç­”æˆ‘çš„ï¼Ÿä½ é€å»é¡¹é“¾äº†å—ï¼Ÿ\n"ESC"ç¦»å¼€", me->get_name()));
        	else if ( who->get_legend(TASK_11,9) && !who->get_legend(TASK_11,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    å“ˆå“ˆå“ˆå“ˆå“ˆå“ˆï¼æˆ‘å¤ªé«˜å…´äº†ï¼Œè´è´å°å§å±…ç„¶ä¼šç»™æˆ‘é€æ¥å¥¹äº²æ‰‹åˆ¶ä½œçš„ç³•ç‚¹ï¼\n"ESC"å®Œæˆä»»åŠ¡\ntalk %x# welcome.5\n"ESC"ç¦»å¼€", me->get_name(),getoid(me)));

        	break;
        case 2:
        	if(who->get_level() >= 40 && !who->get_legend(TASK_11,1))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_11,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"ç§¦å›½" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,3,"æƒ…é”ç§¦å®«ï¼ˆ1ï¼‰" );
			send_user( who, "%c%s", '!', "å¾—åˆ°ä»»åŠ¡ "HIY"æƒ…é”ç§¦å®«ï¼ˆ1ï¼‰");
        	}
        	break;
       case 3:
        	if ( who->get_legend(TASK_11,2) && !who->get_legend(TASK_11,3) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"çç é¡¹é“¾",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,3);
			who->add_exp(4500);
			who->add_potential(140);
			who->add_cash(3500);
			send_user(who,"%c%s",';',"æƒ…é”ç§¦å®«ï¼ˆ1ï¼‰ ç»éªŒ 4500 æ½œèƒ½ 140 é‡‘é’± 3500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,3,"" );
			me->do_welcome(1);
        	}
        	break;        
        case 4:
        	if( who->get_legend(TASK_11,3) && !who->get_legend(TASK_11,4) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;        		
			TASK_LEGEND_D->give_item(who,"item/98/0002",1);
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_11,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"ç§¦å›½" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,4,"æƒ…é”ç§¦å®«ï¼ˆ2ï¼‰" );
			send_user( who, "%c%s", '!', "å¾—åˆ°ä»»åŠ¡ "HIY"æƒ…é”ç§¦å®«ï¼ˆ2ï¼‰");
        	}
        	break;
       case 5:
        	if ( who->get_legend(TASK_11,9) && !who->get_legend(TASK_11,10) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"ç³•ç‚¹",1) != 1 )
        			return;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),40,HEAD_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,10);
			who->add_exp(4300);
			who->add_potential(138);
			who->add_cash(3800);
			send_user(who,"%c%s",';',sprintf("æƒ…é”ç§¦å®«ï¼ˆ4ï¼‰ ç»éªŒ 4300 æ½œèƒ½ 138 é‡‘é’± 3800 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,6,"" );
        	}
        	break;    
        case 6:
        	if ( who->get_legend(TASK_46,19)&&!who->get_legend(TASK_46,20) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    å•Šï¼å£®å£«å¯æ˜¯è¯´é‚£æ¶åŒªå±•äº”ç»ˆäºç«Ÿç„¶æ˜¯æ­»äº†ï¼çœŸæ˜¯å¤©ç†æ˜­æ˜­ï¼Œæ¶æœ‰æ¶æŠ¥ï¼Œå¤šè°¢å£®å£«ä¸ºæˆ‘æŠ¥æ­¤æ·±ä»‡ï¼å‘œå‘œå‘œâ€¦â€¦å¯æƒœæˆ‘çš„å¼Ÿå¼Ÿå†ä¹Ÿå›ä¸æ¥äº†ï¼Œæˆ‘è¦ç”¨è¿™ä¸ªæ¶è´¼çš„äººå¤´ç¥­å¥ æˆ‘äº¡å¼Ÿçš„å†¤é­‚ï¼\n"ESC"å®Œæˆä»»åŠ¡\ntalk %x# welcome.7\n"ESC"ç¦»å¼€", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,20)&&!who->get_legend(TASK_46,21) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    °¦£¬ÖÁÓÚÄÇ¶ñ·ËµÄÀ´ÀúÎÒµ¹Ò²ÂÔÖªÒ»¶ş£¬ÒòÎªµ±Äê¼Ò¸¸ÔøÓëËûÍ¬Ò»Õ½º¾×÷Õ½£¬ËäÈ»Ëû´Ó²»Í¸Â¶×Ô¼º³öÉí£¬µ«Ëû×÷Õ½ÓÂÃÍ£¬È´ÂÅÂÅ²»·şÉÏ¼¶Ö¸Áî£¬×îÖÕÉ±µôÁË¸±½«ÌÓ»ØÉ½ÖĞ£¬¼Ò¸¸Ôø¾­ÊÕÁô¹ıËû£¬È´²»Ğ¡ĞÄÈÃËûÖªµÀÁË¼Ò´«µÄ½ğÁúÖé£¬ËäÈ»´ÓÀ´²»ÖªµÀÓĞºÎ´óÓÃ£¬µ«ÊÇÈ´Ò²Ğ¡ĞÄÊÕ²Ø£¬ÄÇ¶ñ·ËÌıµ½½ğÁúÖé¼¸×ÖÑÛ¾¦·Å¹â£¬ºóÀ´ÎÒµÄ¸¸Ç×ËÀÓÚÕ½»ğ£¬ÎÒÃÇĞÖµÜÒ²Á÷Âäµ½´Ë£¬²»ÖªµÀËûÈçºÎÕÒµ½ÎÒÃÇ£¬×îÖÕÇÀ×ßÁË½ğÁúÖé£¬ÎÒµÜµÜ²»·şÏëÉÏ¸æ±»Ëû²ĞÈÌÉ±º¦£¬Ëû»¹¾Í´ËÍş±ÆÎÒ½»³öÊ²Ã´¾í£¬µ«ÊÇ ÎÒµÈ´ÓÀ´Ã»ÓĞ¼û¹ıÓÖÈçºÎµÃÖª£¬Õ¹Îå¾Í´ËÅÌ¾áÔÚÆ½Ñô¸½½üÂÅÂÅÉ§ÈÅ¾ÓÃñ£¬¶øÎÒĞÄÖĞÕæµÄ¿à²»¿°ÑÔ¡£Èç½ñ¶ñ·ËÖÕÓÚËÀÈ¥£¬ÎÒµÄ¼Ò´«ÖÁ±¦½ğÁúÖéÒ²×Ô´ËÊ§È¥×ÙÓ°£¬ÎÒÕæÊÇ¶Ô×æ×ÚÓĞÀ¢£¬Ç°ÈÕÌıÒ»¸öÌÓ³öÀ´µÄĞ¡à¶†ªËµ¶ñ·Ë³£³£ÔÚÖïÏÉÕó¶ş²ãÄÏ²¿ÉñÃØÙâÙâµÄÅÇ»²£¬¹À¼ÆÄÇ½ğÁúÖé¾Í²ØÔÚÄ³¸öÏä×ÓÀï£¬¿ÒÇó×³Ê¿ÔÙÅÜÒ»ÌË£¬°ïÎÒÑ°»Ø´«¼ÒÖÁ±¦¡£\n"ESC"½ÓÊÜÈÎÎñ\ntalk %x# welcome.8\n"ESC"Àë¿ª", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,21)&&!who->get_legend(TASK_46,22) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    è«éé‡‘é¾™ç ç«Ÿç„¶çœŸçš„å°±æ­¤é—å¤±äº†ä¹ˆï¼Œæˆ‘ç¨‹å¼ºçœŸçš„å¯¹ä¸èµ·ç¨‹å®¶çš„å…ˆç¥–å•Šã€‚\n"ESC"ç¦»å¼€", me->get_name(),));
		else if ( who->get_legend(TASK_46,22)&&!who->get_legend(TASK_46,23) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    å¤§ä¾ ä½ å°±æ˜¯æˆ‘ä»¬ç¨‹å®¶çš„å¤§æ©äººå“ªï¼Œä»Šåæœ‰ä½•äº‹ä½†å‡­å©å’ï¼Œå“ªæ€•ä¸Šåˆ€å±±ä¸‹ç«æµ·ä¹Ÿå†³ä¸çš±çœ‰ã€‚\n"ESC"å®Œæˆä»»åŠ¡\ntalk %x# welcome.9\n"ESC"ç¦»å¼€", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_46,23)&&!who->get_legend(TASK_46,24) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    å¹³é˜³é•‡å¦‚ä»Šç¥¸å®³å·²é™¤ï¼Œå¤§å®¶åˆå¯ä»¥å®‰å±…ä¹ä¸šäº†ï¼Œæˆ‘å°†æœ€è¿‘å‘ç”Ÿçš„äº‹æƒ…å†™äº†æ¡é™ˆï¼ŒåŠ³çƒ¦å£®å£«é€ç»™æœ¬å›½å¾¡å²å¤§äººï¼Œè®©ä»–å®½å¿ƒå§ã€‚\n"ESC"æ¥å—ä»»åŠ¡\ntalk %x# welcome.10\n"ESC"ç¦»å¼€", me->get_name(),getoid(me)));
			
        	break;
        case 7:
        	if( who->get_legend(TASK_46,19)&&!who->get_legend(TASK_46,20) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,20);
			who->add_exp(92000);
			who->add_potential(980);
			who->add_cash(93000);
			send_user(who,"%c%s",';',"å¹³é˜³ä¹‹ä¹±3 ç»éªŒ 92000 æ½œèƒ½ 980 é‡‘é’± 93000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,71,"" );
			me->do_welcome(6);
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_46,20)&&!who->get_legend(TASK_46,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_46,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"ç§¦å›½" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,72,"å¹³é˜³ä¹‹ä¹±4" );
			send_user( who, "%c%s", '!', "å¾—åˆ°ä»»åŠ¡ "HIY"å¹³é˜³ä¹‹ä¹±4");
       		}
        	break;
        case 9:
        	if( who->get_legend(TASK_46,22)&&!who->get_legend(TASK_46,23) )
        	{
			if (TASK_LEGEND_D->check_task_item(who,"é‡‘é¾™ç ",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/64187",1);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_46,23);
			who->add_exp(92000);
			who->add_potential(980);
			who->add_cash(93000);
			send_user(who,"%c%s",';',"å¹³é˜³ä¹‹ä¹±4 ç»éªŒ 92000 æ½œèƒ½ 980 é‡‘é’± 93000 é¾™é³æˆ˜ç”²å›¾çº¸ 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,72,"" );
			me->do_welcome(6);
        	}
        	break;
        case 10:
        	if ( who->get_legend(TASK_46,23)&&!who->get_legend(TASK_46,24) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0230",1); 
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_46,24);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"ç§¦å›½" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,73,"å¹³é˜³ä¹‹ä¹±5" );
			send_user( who, "%c%s", '!', "å¾—åˆ°ä»»åŠ¡ "HIY"å¹³é˜³ä¹‹ä¹±5");
       		}
        	break;
        }
}