
#define SAVE_FILE "data/id" SAVE_EXTENSION

private
int Id;
private
int ItemId;

private
int NewUser;
private
int CharNumber;
private
int LoginPlayer;

private
int UserCount;
private
int CountTime;
private
int MaxUser;

private
int Buyer;
private
int BuyCount;
private
int BuyPoint;

private
int CardCount;

private
int QuitCount; // 正常退出
private
int ReconnectCount; // 重连
private
int NetdeadCount; // 超时没响应
private
int KickCount; // 踢出游戏

private
int TransId = 10000; // 新马的传输ID

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：构造处理
void create()
{
	restore_object(SAVE_FILE);
	if (TransId < 10000)
		TransId = 10000;
}

// 函数：更新最大标识
int add_max_id(int number)
{
	// restore_object(SAVE_FILE);

	if (number > Id)
	{
		Id = number;
		save_object(SAVE_FILE);
	}
	return Id;
}

int zero_max_id()
{
	return Id = 0;
}

// 函数：获取最大标识
int get_max_id()
{
	restore_object(SAVE_FILE);
	return Id;
}

// 函数：更新最大标识
int add_max_itemid(int number)
{
	//	restore_object(SAVE_FILE);
	ItemId += number;
	//	save_object(SAVE_FILE);
	return ItemId;
}

int zero_max_itemid()
{
	return ItemId = 0;
}

// 函数：获取最大标识
int get_max_itemid()
{
	//restore_object(SAVE_FILE);
	return ItemId;
}

int add_newuser(int flag)
{
	return NewUser += flag;
}

int add_charnumber(int flag)
{
	return CharNumber += flag;
}

int add_loginplayer(int flag)
{
	return LoginPlayer += flag;
}

int get_newuser()
{
	return NewUser;
}

int get_charnumber()
{
	return CharNumber;
}

int get_loginplayer()
{
	return LoginPlayer;
}

int add_usercount(int flag)
{
	UserCount += flag;
	CountTime++;
	if (MaxUser < flag)
		MaxUser = flag;
	return flag;
}

int get_avguser()
{
	if (CountTime == 0)
		return 0;
	else
		return UserCount / CountTime;
}

int get_maxuser() { return MaxUser; }

int add_buy(int count, int point)
{
	Buyer++;
	BuyCount += count;
	BuyPoint += point;
	return Buyer;
}

int get_buyer() { return Buyer; }

int get_buycount() { return BuyCount; }

int get_buypoint() { return BuyPoint; }

int add_cardcount(int count)
{
	CardCount += count;
	return CardCount;
}

int get_cardcount() { return CardCount; }

int init_login() // 清除玩家记录
{
	NewUser = 0;
	CharNumber = 0;
	LoginPlayer = 0;
	return 1;
}

int init_count() // 清除玩家统计
{
	UserCount = 0;
	CountTime = 0;
	MaxUser = 0;
	CardCount = 0;
	return 1;
}

int init_buy()
{
	Buyer = 0;
	BuyCount = 0;
	BuyPoint = 0;
}

int set_quit_count(int i) { return QuitCount = i; }

int add_quit_count(int i) { return QuitCount += i; }

int get_quit_count() { return QuitCount; }

int set_reconnect_count(int i) { return ReconnectCount = i; }

int add_reconnect_count(int i) { return ReconnectCount += i; }

int get_reconnect_count() { return ReconnectCount; }

int set_netdead_count(int i) { return NetdeadCount = i; }

int add_netdead_count(int i) { return NetdeadCount += i; }

int get_netdead_count() { return NetdeadCount; }

int set_kick_count(int i) { return KickCount = i; }

int add_kick_count(int i) { return KickCount += i; }

int get_kick_count() { return KickCount; }

int get_transid() { return TransId; }
int add_transid(int i)
{
	TransId += i;
	//save_object(SAVE_FILE);
	return TransId;
}
