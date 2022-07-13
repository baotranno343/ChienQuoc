// 怪物攻城升级规模
#include <ansi.h>
#include <map.h>
#include <city.h>
#include <skill.h>

private static int War;                 // 战争状态
private static int z;                 	// 战争地图
private static int grade;               // 帮派等级

private static string orgname;           // 帮派名字

private static object *dbComrade = ({ });       // 怪物

string get_org_name() {return orgname;}
string set_org_name(string name) {return orgname = name;}

// 函数：构造处理
void create()
{
        object me = this_object();

        if( !clonep(me) ) return;

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 20);    // 循环心跳：５秒钟
        me->heart_beat();
        set_heart_beat(1);
        War = WAR_READY;
}

// 函数：获取战争状态
int get_war() { return War; }

// 函数：设置战争状态
int set_war( int flag ) { return War = flag; }

int get_z() { return z;}

int set_z(int i) {return z=i;}

int get_grade() { return grade;}

int set_grade(int i) {return grade=i;}// 函数：心跳处理

void heart_beat() { }

private static int HeartSec = 0;        // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec( int point ) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec( int point ) { return set_heart_sec(HeartSec + point); }

// 函数：获取攻击方士兵
object *get_comrade_dbase() { dbComrade -= ({ 0 });  return copy(dbComrade); }

// 函数：获取攻击方士兵
int sizeof_comrade_dbase() { dbComrade -= ({ 0 });  return sizeof(dbComrade); }

// 函数：增加攻击方士兵
void add_comrade( object npc ) { dbComrade = dbComrade + ({ npc }) - ({ 0 }); }

// 函数：删除攻击方士兵
void sub_comrade( object npc ) { dbComrade -= ({ npc, 0 }); }

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object map, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每2秒处理
{
        int sec = map->add_heart_sec(2);
        int time, count, value, i, j, p, x, y, z, color;
        string name, *attrib, *attrib2;
        object npc, orgnpc;
        name = map->get_org_name();
        orgnpc = CITY_ZHOU->get_2( sprintf( "org.%s", name ) );
        if (!orgnpc)
        	return;
        if (sec<540) return;
        // 第9分钟公告

        if (sec==540)
        {
        	FAMILY_D->org_channel( name, 0, HIR "Bang phái đã bị quái vật xâm nhập, tất cả thành viên trong Bang hãy về hỗ trợ" );
        	FAMILY_D->org_channel( name, 0, HIR "Quái vật 60 giây sau sẽ bắt đầu tấn công !" );
        	return;
        }
        // 刷41批怪物
        	// 是否全部清理干净
        if (map->sizeof_comrade_dbase()>=300 )
        {
        	CHAT_D->rumor_channel( 0, sprintf(HIR "Nghe nói %s đã bị quái vật tấn công, thương tổn nghiêm trọng" , name));
        	orgnpc->add_train(-2);
        	orgnpc->add_stable(-300);
        	orgnpc->add_favour(-100);
        	orgnpc->set_gradewartime(0);
        	orgnpc->set_wardamage(0);
        	orgnpc->save();
        	FAMILY_D->org_channel( name, 0, HIR "Bởi vì quái vật đã xâm chiếm thành công bổn bang với số lượng 300 con, nhiệm vụ thất bại" );
        	FAMILY_D->org_channel( name, 0, HIR "Bởi vì quái vật đã xâm chiếm thành công bổn bang với số lượng 300 con, nhiệm vụ thất bại, Độ yên ổn giảm 300 điểm,  Nhân khí giảm 100 điểm, Độ huấn luyện giảm 2 điểm" );
        	map->before_destruct();
        	destruct(map);
        	return;
        }
        // 因为怪物攻击超过100，战争消失，自行检测
        if (orgnpc->get_gradewartime()==0)
        {
        	map->before_destruct();
        	destruct(map);
        	return;        	
        }
        if (sec<600) return;
        sec -= 600;
        if (sec<=90*40+32)
        {
        	time = sec / 90;	// 第几拨怪物
        	count = (sec % 90)/2;
        	time ++;
        	attrib = "/quest/upgrade"->get_npc_attrib(map->get_grade(), sprintf("%d", time));
        	if (attrib==0) return;
        	value = to_int(attrib[6]);
        	if (value<16)
        	{
        		if (count>0) return;
        	}
        	else
        	{
        		if (count >= value/6) return;
        		value = value/16;
        	}
        	if (count==0)
        	{
        		FAMILY_D->org_channel( name, 0, HIR "Bang phái đã bị quái vật xâm nhập, tất cả thành viên trong Bang hãy về hỗ trợ" );
        		FAMILY_D->org_channel( name, 0, sprintf(HIR "%d quái vật bắt đầu tấn công !" , time));
        		if (time==1)
        			CHAT_D->rumor_channel( 0, sprintf(HIR "Nghe nói %s viện chủ đã bị tấn công !" , name));
        		else
        			FAMILY_D->org_channel( name, 0, sprintf(HIR "Đã có %d chỉ phát động tấn công !" , map->sizeof_comrade_dbase()));
        	}
        	value = value/3;
//log_file("test.dat", sprintf("%s sec=%d time=%d, count=%d attrib=%s value=%d npc=%d\n", short_time(), sec, time, count, attrib[6], value, map->sizeof_comrade_dbase() ));
        	z = map->get_z();
		for (i=0;i<3;i++)
		{
			p = get_jumpin(z, i+2);
                        x = ( p % 1000000 ) / 1000;
                        y = p % 1000;
			for (j=0;j<value;j++)
			{
				p = get_valid_xy( z, x + random(5), y + random(5), IS_CHAR_BLOCK );
				if (p)
				{
		                        x = ( p % 1000000 ) / 1000;
		                        y = p % 1000;
				}
				switch(attrib[5])
				{
				case "空手":
				case "武器":
					npc = new ("/npc/war/0100");
					break;
				case "暗器":
					npc = new ("/npc/war/0101");
					break;			
				default:
					npc = new ("/npc/war/0102");
					break;					
				}
				npc->set_name("Bang Phái Đào Loạn Phần Tử");
				npc->set_level(to_int(attrib[4]));
				npc->set_char_picid(to_int(attrib[0]));
				if (attrib[1]=="－") color = 0;
				else sscanf(attrib[1], "%x", color);
				npc->set_head_color(color);
				attrib2 = ({attrib[2], attrib[3], attrib[5] });
				"/sys/npc/energy"->init_npc(npc, npc->get_level(), attrib2);
				npc->add_to_scene(z, x, y, 6);
				map->add_comrade(npc);
			}
		}
        }
        else
        {
        	// 是否全部清理干净
        	if (map->sizeof_comrade_dbase()==0)
        	{
        		CHAT_D->rumor_channel( 0, sprintf(HIR "Nghe nói %s thành công chống đỡ quái vật xâm nhập" , name));
        		orgnpc->set_gradetime(time()+24*3600);
        		orgnpc->add_train(-1);
        		orgnpc->add_stable(300);
        		orgnpc->add_favour(150);
        		orgnpc->set_gradewartime(0);
        		orgnpc->set_wardamage(0);
        		orgnpc->save();
        		FAMILY_D->org_channel( name, 0, HIR "Bổn bang đồng tâm hiệp lực cuối cùng đã lui quái vật, độ yên ổn tăng 300 điểm, nhân khí tăng 150 điểm, độ huấn luyện giảm 1 điểm. 24h sau quy mô sẽ tăng lên một bậc" );
	        	map->before_destruct();
	        	destruct(map);
        	}
        }
}

// 函数：消除之前处理
void before_destruct()
{
        object map, *char, npc;
        int i, size;

        map = this_object();

        if( arrayp( char = map->get_comrade_dbase() ) )
        {
                for( i = 0, size = sizeof(char); i < size; i ++ ) if( objectp( npc = char[i] ) )
                {
                        npc->remove_from_scene();
                        destruct(npc);
                }
        }
}