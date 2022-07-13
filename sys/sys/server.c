/********************
控制游戏服务器的关闭
**********************/
#include <ansi.h>

private static int game_status; //0 正常运行；1 重启中；2 马上关闭
// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：构造处理
void create() 
{
	call_out("check_server",3);	
}

// 函数：重启处理
private void do_reboot( int min )
{
        remove_call_out( "do_reboot" );

	if( (-- min)>0 ) 
	{
                USER_D->user_channel( sprintf( HIR "Trò chơi khởi động lại sau %d phút.", min ) );
		call_out( "do_reboot", 60, min );
	} 
	else 
	{
                USER_D->user_channel( HIR "Trời chơi khởi động lại." );

                USER_D->save_all_data();    // 保存所有数据

                shutdown(0);
	}
}

//游戏服务器状态检查
void check_server()
{
	int i;
	string cTmp,file;
	
	if ( game_status == 0 )
	{	//准备重启
		if ( file_size("/game.reboot") >= 0 )
			file = "/game.reboot";
		else if  ( file_size("/game.shutdown") >= 0 )
			file = "/game.shutdown";
		if ( file )
		{
			cTmp = read_file(file);
			rm(file);
			i = to_int(cTmp);
			if ( i < 1 )
				i = 1;
			game_status = 1;
			do_reboot(i+1);
		}
	}
	if ( game_status == 1 && file_size("/game.cancel.reboot") >= 0 )	//取消重启
	{
		rm("/game.cancel.reboot");
		game_status = 0;
		remove_call_out( "do_reboot" );
	}
	if ( file_size("/game.shutdown.now") >= 0 )	//马上重启
	{
		rm("/game.shutdown.now");
		game_status = 2;
		do_reboot(0);
	}
	call_out("check_server",60);
}

void start_it()
{
	rm("/game.reboot");	
	rm("/game.shutdown");	
	rm("/game.cancel.reboot");	
	rm("/game.shutdown.now");
	check_server();	
}