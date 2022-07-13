int * base;
int * current;

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：构造处理
void create() 
{ 
	int i;
	current = ({ });
	for (i=0;i<50;i++) current += ({ i, i+50 });
	base = ({ });
}

int get_random_100()
{
	int ret;
	if (sizeof(current)==0) 
	{
		current = copy(base);
		base = ({ });
	}
	ret = current[random(sizeof(current))];
	current -= ({ ret });
	base += ({ ret });
	return ret;
}