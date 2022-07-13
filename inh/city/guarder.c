// guarder 守卫，城门守卫

#include <ansi.h>
#include <action.h>

// 函数：对话处理
void do_look( object who, object me )
{
        object city;
        string name1, name2;
        string cmd, cmd2, result;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        if( stringp(name1) && stringp(name2) && name1 == name2 )
        {
                cmd = sprintf( "talk %x# enter\n", getoid(me) );
                cmd2 = sprintf( "talk %x# record\n", getoid(me) );
                send_user( who, "%c%s", ':', me->get_name() + " :\n "+"/quest/word"->get_country_word(me)+"\n " + who->get_name() + "，您有什么事情？\n" 
                        ESC "Ta muốn vào thành.\n" + cmd +
                        ESC "Lấy "+name2+" làm nơi trở lại thành.\n" + cmd2 +
                        ESC "Rời khỏi.\nCLOSE\n" );
        }
        else if( city = CITY_D->get_city_object(me) )
        {
                cmd = sprintf( "talk %x# enter\n", getoid(me) );
                cmd2 = sprintf( "talk %x# record\n", getoid(me) );
                result = sprintf( "%s :\n "+"/quest/word"->get_country_word(me)+"\n", me->get_name());
                send_user( who, "%c%s", ':', result +
                        ESC "Ta muốn vào thành.\n" + cmd +
                        ESC "Lấy "+name2+" làm nơi trở lại thành.\n" + cmd2 +
                        ESC "Rời khỏi.\nCLOSE\n" );
        }
}

// 函数：对话处理
void do_look_2( object who, object me )
{
        string cmd = sprintf( "talk %x# out\n", getoid(me) );
        string cmd2 = sprintf( "talk %x# record\n", getoid(me) );
        send_user( who, "%c%s", ':', me->get_name() + "：\n    "+"/quest/word"->get_country_word(me)+"\n    " + who->get_name() + "，您有什么事情？\n" 
                ESC "我要出城.\n" + cmd +
                ESC "将"+me->get_city_name()+"作为我的回城点.\n" + cmd2 +
                ESC "离开.\nCLOSE\n" );
}

// 函数：对话处理
void do_look_3( object who, object me )
{
        string name;
        int z, x, y, p;

        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      stringp( name = who->get_quest("escort.name") )    // 镖主姓名
        &&    ( p = QUEST_ESCORT->get_xy_point(name) ) )    // 确有此人
        {
                z = p / 1000000;  x = ( p % 1000000 ) / 1000;  y = p % 1000;

                if( get_z(me) == z )    // 同一城市
                {
                        send_user( who, "%c%s", ':', sprintf( me->get_name() + 
                                "：\n哈哈，你问对人了，我来的时候，看到%s在(%d,%d)附近，好像在盼望什么似的.\n", name, x, y ) );

                        send_user( who, "%c%c%d%w%w", 0x54, 12, getoid(who), x, y );    // 借用 getoid(who)
                        who->set_task_xy(p);

                        return;
                }
        }

        send_user( who, "%c%s", ':', me->get_name() + "\n    "+"/quest/word"->get_country_word(me) );
}

// 函数：入城处理
void do_enter( object who, object me )
{
        object city, npc;
        string name1, name2;
        int z, x, y, p;

        name1 = who->get_city_name();
        name2 = me->get_city_name();

        switch( name2 )
        {
  case "Tề Quốc" : z = 10;  p = get_jumpin( z, me->get("in") );  break;
  case "Hàn Quốc" : z = 20;  p = get_jumpin( z, me->get("in") );  break;
  case "Triệu Quốc" : z = 30;  p = get_jumpin( z, me->get("in") );  break;
  case "Ngụy Quốc" : z = 40;  p = get_jumpin( z, me->get("in") );  break;
  case "Tần Quốc" : z = 50;  p = get_jumpin( z, me->get("in") );  break;
  case "Sở Quốc" : z = 60;  p = get_jumpin( z, me->get("in") );  break;
  case "Yên Quốc" : z = 70;  p = get_jumpin( z, me->get("in") );  break;
      default :
  case "Chu Quốc" : z = 80;  p = get_jumpin( z, me->get("in") );  break;
        }

        if( !p )
        {
                send_user(who, "%c%s", '!', "城里好象太多人了……");
                return;
        }
        if( objectp( npc = who->get_quest("escort.robber#") ) && npc->is_escort_robber() )    // 寻找蒙面人
        {
                send_user(who, "%c%s", '!', npc->get_name()+"出现，您的行动受到影响.");
                return;
        }

        if( stringp(name1) && stringp(name2) && name1 == name2 )
        {
                x = p / 1000;  y = p % 1000;

                if(   ( npc = who->get_quest("escort.npc") )    // 运镖人物
                &&      npc->get_owner() == who
                &&      inside_screen_2(me, npc) )    // 卫兵距离
                        npc->add_to_scene( z, x, y, get_d(who) );

                if( p = get_valid_xy( z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK ) )
                {
                        who->add_to_scene( z, p / 1000, p % 1000, get_d(who) );
                }
        }
        else if( city = CITY_D->get_city_object(me) )
        {

                x = p / 1000;  y = p % 1000;

                if(   ( npc = who->get_quest("escort.npc") )    // 运镖人物
                &&      npc->get_owner() == who
                &&      inside_screen_2(me, npc) )    // 卫兵距离
                        npc->add_to_scene( z, x, y, get_d(who) );

                if( p = get_valid_xy( z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK ) )
                {
                        who->add_to_scene( z, p / 1000, p % 1000, get_d(who) );
                }
        }
}

// 函数：出城处理
void do_out( object who, object me )
{
        object npc;
        int z, x, y, p;

        switch( me->get_city_name() )
        {
  case "Tề Quốc" : z = 10;  p = get_jumpin( z, me->get("out") ); 
//                who->set_latest_city( z * 100 + me->get("out") ); 
                break;
  case "Hàn Quốc" : z = 20;  p = get_jumpin( z, me->get("out") );  
//                who->set_latest_city( z * 100 + me->get("out") ); 
                break;
  case "Triệu Quốc" : z = 30;  p = get_jumpin( z, me->get("out") );  
//                who->set_latest_city( z * 100 + me->get("out") ); 
                break;
  case "Ngụy Quốc" : z = 40;  p = get_jumpin( z, me->get("out") );  
//                who->set_latest_city( z * 100 + me->get("out") ); 
                break;
  case "Tần Quốc" : z = 50;  p = get_jumpin( z, me->get("out") );  
//                who->set_latest_city( z * 100 + me->get("out") ); 
                break;
  case "Sở Quốc" : z = 60;  p = get_jumpin( z, me->get("out") );  
//                who->set_latest_city( z * 100 + me->get("out") ); 
                break;
  case "Yên Quốc" : z = 70;  p = get_jumpin( z, me->get("out") );  
//                who->set_latest_city( z * 100 + me->get("out") ); 
                break;
      default :
  case "Chu Quốc" : z = 80;  p = get_jumpin( z, me->get("out") );  
//                who->set_latest_city( z * 100 + me->get("out") );    // 回城符
                break;
        }

        if( !p )
        {
                send_user(who, "%c%s", '!', "城门口好象太多人了……");
                return;
        }
        if( objectp( npc = who->get_quest("escort.robber#") ) && npc->is_escort_robber() )    // 寻找蒙面人
        {
                send_user(who, "%c%s", '!', npc->get_name()+"出现，您的行动受到影响.");
                return;
        }

        x = p / 1000;  y = p % 1000;

        if(   ( npc = who->get_quest("escort.npc") )    // 运镖人物
        &&      npc->get_owner() == who
        &&      inside_screen_2(me, npc) )    // 卫兵距离
                npc->add_to_scene( z, x, y, get_d(who) );

        if( p = get_valid_xy( z, x + random(3) - 1, y + random(3) - 1, IS_CHAR_BLOCK ) )
        {
                who->add_to_scene( z, p / 1000, p % 1000, get_d(who) );
        }
}

// 函数：出城处理
void do_record( object who, object me )
{
        object npc;
        int z, x, y, p;

        switch( me->get_city_name() )
        {
	  case "Tề Quốc" : z = 10;  p = get_jumpin( z, me->get("out") ); 
	                who->set_latest_city( z * 100 + me->get("out") ); 
	                break;
	  case "Hàn Quốc" : z = 20;  p = get_jumpin( z, me->get("out") );  
	                who->set_latest_city( z * 100 + me->get("out") ); 
	                break;
	  case "Triệu Quốc" : z = 30;  p = get_jumpin( z, me->get("out") );  
	                who->set_latest_city( z * 100 + me->get("out") ); 
	                break;
	  case "Ngụy Quốc" : z = 40;  p = get_jumpin( z, me->get("out") );  
	                who->set_latest_city( z * 100 + me->get("out") ); 
	                break;
	  case "Tần Quốc" : z = 50;  p = get_jumpin( z, me->get("out") );  
	                who->set_latest_city( z * 100 + me->get("out") ); 
	                break;
	  case "Sở Quốc" : z = 60;  p = get_jumpin( z, me->get("out") );  
	                who->set_latest_city( z * 100 + me->get("out") ); 
	                break;
	  case "Yên Quốc" : z = 70;  p = get_jumpin( z, me->get("out") );  
	                who->set_latest_city( z * 100 + me->get("out") ); 
	                break;
	      default :
	  case "Chu Quốc" : z = 80;  p = get_jumpin( z, 10 );  
	                who->set_latest_city( z * 100 + 10 );    // 回城符
	                break;
        }	
        write_user( who, ECHO "您设置了新的回城点.\n" );
}	