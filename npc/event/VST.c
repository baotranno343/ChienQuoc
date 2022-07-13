#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <skill.h>
#include <time.h>


inherit OFFICER;
inherit DBASE_F;

int WarId;
int *nRankScore = ({ 25,63,156,400,1000,2500,6250,15500,38250,95500,238500 });
// 函数:获取人物造型
int get_char_picid() { return 5109; }
void do_welcome( string arg );
//void do_nhanthuong( string arg );
//void do_bonus( string arg );
void player_sign_up(object me,object who);
void team_sign_up(object me, object who);
int init_npc(object npc,int level);
void check_war_begin(int level,int wId);
void enter_changping(object who);
int check_valid_user(object who);
int count_sign_up(int level,int wId);
void refuse_changping(object who);
void abort_changping(object who);
int change_score(int score);
int kill_score(object who,object map);
void give_title(object me,object who,int iFlag);
int BatDau, KetThuc;

// 函数:构造处理
void create()
{
	int i,size;
	string *nKey;
	mapping mpTmp;
        set_name("Vô Song Thành Thủ Vệ");
        set_city_name("Chu Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
        setup();

	if ( clonep(this_object()) )
		return ;
}

// 函数:对话处理
void do_look( object who )
{
	int level,z,wId,iTime;
	object me = this_object();
	int id=getoid(me);
	mixed *mixTime;
	iTime = time();
	mixTime = localtime(iTime);
	if ( mixTime[TIME_WDAY] == 0 )
	{
		send_user(who,"%c%s",':',sprintf( "%s:\n    Vô Song Thành là tượng trưng cho địa vị và quyền lực, nếu như muốn giành lấy quyền nắm giữ Vô Song Thành thì phải là Bang Chủ dẫn dắt toàn Bang chiến đấu...\n"
			ESC"Tiến vào Vô Song Thành\ntalk %x# welcome.3\n"
			ESC HIG"Những điều cần biết\ntalk %x# welcome.9\n"
			ESC HIC"Đổi thưởng Vô Song Thành\ntalk %x# welcome.4\n"
			ESC"Thoát", get_name(),id,id,id,id ) 
				);
	}
	else {
		send_user(who,"%c%s",':',sprintf( "%s:\n    Hôm nay không thể tiến vào Vô Song Thành, Chủ Nhật hãy quay lại đây !\n"
			ESC"Ta biết rồi\ntalk %x# welcome.1000\n"
			ESC HIC"Đổi thưởng Vô Song Thành\ntalk %x# welcome.4\n"
			ESC"Thoát", get_name(),id,id,id,id ) 
				);
	}	
	
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p,z,level,x,y,wId,score,iTime;
        object who,item,obj;  
        string cmd1;
		
	mixed *mixTime;
	iTime = time();
	mixTime = localtime(iTime);
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	break;
        case 2:
        	break;
        case 3:
		if ( who->get_org_name()=="" )
		{
			notify("Chưa vào Bang Hội không thể tiến vào Vô Song Thành");
			return ;
		}
		if ( mixTime[TIME_WDAY] != 0 ) 
		{
			notify("Thời gian tranh đoạt Vô Song Thành chưa tới");
			return ;
		}
		if ( mixTime[TIME_HOUR] < 18 || (mixTime[TIME_HOUR] == 18 && mixTime[TIME_MIN] > 45) )
		{
			notify("Thời gian tranh đoạt Vô Song Thành chưa tới hoặc đã qua");
			return ;
		}
		enter_changping(who);
        	break;
        case 4:	
		send_user(who,"%c%s",':',sprintf( "%s:\n    Ngươi hiện đang có "HIR "%d "NOR "điểm tích luỹ Vô Song Thành, ngươi muốn đổi giải thưởng gì ?\n"
			//ESC"Đổi Danh Hiệu Vô Song Thành\ntalk %x# welcome.7\n"
			ESC"Đổi Kinh nghiệm\ntalk %x# welcome.13\n"
			ESC"Đổi Kim Nguyên Bảo\ntalk %x# welcome.17\n"
			ESC"Đổi Ngân Lượng\ntalk %x# welcome.21\n"
			ESC"Hủy", me->get_name(),who->get_save_2("vst.score"),getoid(me),getoid(me),getoid(me),getoid(me) ) 
				);        	
        	break;
        case 5:	        	
        	break;
        case 6:
        	break;
        case 7:
        	break;
        case 8:
        	break;
        case 9:
		send_user(who,"%c%s",':',sprintf( "%s:\n    Trận chiến Vô Song Thành giữa các Bang hội sẽ diễn ra vào lúc 19h30 Chủ Nhật hàng tuần, khi giết càng nhiều kẻ địch điểm Tích luỹ nhận được càng nhiều, điểm Tích luỹ có thể dùng để đổi các phần thưởng rất phong phú. \nLưu ý : Phải gia nhập Bang Hội mới có thể tiến vào Vô Song Thành !\n"
			ESC"Ta đã hiểu\ntalk %x# welcome.1000\n"
			ESC"Thoát", me->get_name(),getoid(me) ) 
				);         	
        	break;
        case 10:        	
        	break;
        case 11:        	
        	break;
        case 12:         	
        	break;
        case 13:
		send_user(who,"%c%s",':',sprintf( "%s :\n    Ngươi muốn dùng bao nhiêu điểm Tích luỹ để đổi lấy Kinh Nghiệm ?\n"
			ESC"Sử dụng 20 điểm Tích luỹ\ntalk %x# welcome.14\n"
			ESC"Sử dụng 100 điểm Tích luỹ\ntalk %x# welcome.15\n"
			ESC"Sử dụng 1000 điểm Tích luỹ\ntalk %x# welcome.16\n"
			ESC"Hủy", me->get_name(),getoid(me),getoid(me),getoid(me) ) 
				);         	
        	break;
        case 14:
			if ( who->get_save_2("vst.score") < 20 )
				{
				notify( "Không đủ 20 điểm Tích luỹ" );
				return ;	
				}
				
		who->add_exp(who->get_level()*815);
		who->add_save_2("vst.score",-20) ;
        	break;
        case 15:
			if ( who->get_save_2("vst.score") < 100 )
				{
				notify( "Không đủ 100 điểm Tích luỹ" );
				return ;	
				}
				
		who->add_exp(who->get_level()*3572);
		who->add_save_2("vst.score",-100) ;
        	break;
        case 16:
			if ( who->get_save_2("vst.score") < 1000 )
				{
				notify( "Không đủ 1000 điểm Tích luỹ" );
				return ;	
				}
				
		who->add_exp(who->get_level()*35720);
		who->add_save_2("vst.score",-1000) ;
        	break;
        case 17:
			send_user(who,"%c%s",':',sprintf( "%s :\n    Ngươi muốn dùng bao nhiêu điểm Tích luỹ để đổi lấy Kim Nguyên Bảo ?\n"
			ESC"Sử dụng 20 điểm Tích luỹ\ntalk %x# welcome.18\n"
			ESC"Sử dụng 100 điểm Tích luỹ\ntalk %x# welcome.19\n"
			ESC"Sử dụng 1000 điểm Tích luỹ\ntalk %x# welcome.20\n"
			ESC"Hủy", me->get_name(),getoid(me),getoid(me),getoid(me) ) 
				);
        	break;
        }
}

//活动结束
void game_over(object map,string cWin )
{
	int i,size,score,total,*nTmp=({});
	object who,*nPlayer;
	mapping mpTmp=([]);
		
	send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIR "Trận tử chiến Vô Song Thành đã kết thúc !!!") );
	send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIR "Trận tử chiến Vô Song Thành đã kết thúc !!!") );
	send_user( CHAT_D->get_chat(), "%c%s", 0xA3, sprintf(HIR "Trận tử chiến Vô Song Thành đã kết thúc !!!") );
	nPlayer = map->get_all_user();
	map->set("finish",1);
	map->set("win",cWin);
	//map->game_over();
	for(i=0,size=sizeof(nPlayer);i<size;i++)
	{
		who = nPlayer[i];
		if ( !objectp(who) )
			continue;
		if ( who->get_2("vst.warid") != map->get("warid") )
			continue;
		score = map->get_2(sprintf("score.%d",who->get_number()));
		score += 450;
		if ( score < 0 )
			score = 0;
		score = change_score(score);		//转换成战绩
		score += kill_score(who,map);
		who->add_to_scene(80, 280+random(50), 120+random(50), 3);
		who->add_save_2("vst.score",score);
		"sys/sys/test_db"->add_yuanbao(who,1);
		who->add_save_2("vst.totalscore",score);
		send_user(who,"%c%s",';',sprintf("Tích luỹ của bạn ở trong Vô Song Thành là %d điểm",score));
		//log_file("vst.txt",sprintf("%s %d Tổng quát %d giết %d Tích luỹ người 1 %d Tích luỹ 2 %d Tổng Tích luỹ %d \n",short_time(),who->get_number(),map->get_2(sprintf("score.%d",who->get_number()))+450,map->get_2(sprintf("kill.%d",who->get_number())),score-kill_score(who,map),kill_score(who,map),score));		
	}	
}

//杀死NPC的奖励和惩罚
void win_bonus( object me, object who )
{
	int iRank,iAdd,iSub,i,size,z,iTime;
	object *nPlayer,map,owner;
	string cCountry1,cCountry2,cTmp,cName,cWin;
	mixed *mixTime;
	iTime = time();
	mixTime = localtime(iTime);
	
	owner = who->get_owner();
	if ( owner && owner->is_user() )
		who = owner;
	iRank = me->get("rank");
		if ( iRank >= 1 && iRank < 6 )
		iAdd = 1;
	cName = me->get_name();
	z = get_z(me);
	map = get_map_object(z);
	if ( !map || !map->is_wushuang() )
		return ;
	nPlayer = map->get_all_user();
	nPlayer -= ({0});
	if ( mixTime[TIME_HOUR]==18 && mixTime[TIME_MIN]==45 )
	{
		game_over(map,cWin);
	}
}

//杀死对方玩家的奖励
void kill_player_bonus(object me,object who)
{
	int exp;
	object owner,map;
	if ( !who->is_user() )
		return ;
	owner = me->get_owner();
	if ( owner )
		me = who;
	if ( !me->is_user() )
		return ;
	map = get_map_object(get_z(me));
	if (map && map->is_wushuang() )
	{
		if ( me->get_online_rate() == 100 )
		{
			map->add_2(sprintf("kill.%d",me->get_number()),1);
			me->add_save_2("vst.kill",1);
		}
		if ( who->get_online_rate() == 100 )
		{
			map->add_2(sprintf("killed.%d",who->get_number()),1);
			who->add_save_2("vst.killed",1);
		}
	}
}

//进入长平战场
void enter_changping(object who)
{
	int level,wId,z,x,y,p;
	object map;
	z = 888;
	level = who->get_2("vst.level");
	wId = who->get_2("vst.warid");
	if( p = get_valid_xy(z, x, y, IS_CHAR_BLOCK) )
        {	
                x = p/1000, y = p % 1000;
                who->add_to_scene(z, x, y, 3);
		CHAR_CHAR_D->init_loop_perform(who);
        }	
	
}
//按积分转换成战绩
int change_score(int score)
{
	if ( score < 451 )
		score = 10;
	else if ( score < 452 )
		score = 15;
	else if ( score < 453 )
		score = 21;
	else if ( score < 454 )
		score = 28;
	else if ( score < 455 )
		score = 36;
	else if ( score < 456 )
		score = 45;
	else if ( score < 460 )
		score = 21;
	else if ( score < 470 )
		score = 31;
	else if ( score < 480 )
		score = 43;
	else if ( score < 490 )
		score = 57;
	else if ( score < 500 )
		score = 73;
	else 
		score = 91;	

	return score;
}
//杀玩家的战绩兑换
int kill_score(object who,object map)
{
	int i;
	
	if ( !map )
		return 0;
	i = map->get_2(sprintf("kill.%d",who->get_number()));
	if ( i < 4 )
		i = 10;
	else if ( i < 9 )
		i = 30;
	else if ( i < 15 )
		i = 60;
	else if ( i < 22 )
		i = 90;
	else if ( i < 30 )
		i = 120;
	else if ( i < 39 )
		i = 150;
	else if ( i < 51 )
		i = 180;
	else
		i = 250;
	return i;
}