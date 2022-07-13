
inherit SKILL;

// 函数：基本技能
int is_vita_skill() { return 1; }

// 函数：构造处理
void create() 
{ 
        set_number(0650);
        set_name( "Điêu Khắc" );
}

// 函数：能否特殊技
void can_perform( object me )
{
	int number, i, j, size, pf ;
	object file;
	int * vita, *vita2;
	__DIR__ "06501"->can_perform(me);
	number = get_number();
	vita = me->get_save_2(sprintf("vita.%d", number));
	vita2 = me->get_save_2(sprintf("vita2.%d", number));	
	if (sizeof(vita)==0) vita = ({ });
	if (sizeof(vita2)==0) vita2 = ({ });
	size = sizeof(vita);
	while (sizeof(vita2)<size) vita2 += ({ 0 });
	for (i=0;i<size;i++)
	{
		if (vita[i]==0 && vita2[i]==0 ) continue;
		for(j=0;j<32;j++)
		{
			if ((vita[i]&(1<<j))||(j==31&&vita2[i]==1))
			{
				pf = number * 100 + i*32+j;
				if(   file = load_object( SKILL->get_perform_file(pf) ) )
				{
					file->can_perform(me);
				}
			}
		}
	}
}

// 函数：获取描述
string get_desc() 
{
        return "[Điêu Khắc]Có thể bảo người chơi khảm nạm trang bị. cũng có thể tạo các vòng xuyến phân biệt với trang bị.\n";
}
