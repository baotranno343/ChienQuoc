
private int Con;                 // 体魄，根骨   Constitution
private int Spi;                 // 精神，灵性   Spirituality
private int Str;                 // 力量         Strength
private int Cps;                 // 耐力，定力   Composure
private int Dex;                 // 敏捷，机敏   Dexterity

// -------------------------------------------------------------

// 函数：获取体魄属性
int get_con() { return Con; }

// 函数：获取精神属性
int get_spi() { return Spi; }

// 函数：获取力量属性
int get_str() { return Str; }

// 函数：获取耐力属性
int get_cps() { return Cps; }

// 函数：获取敏捷属性
int get_dex() { return Dex; }

// 函数：设置体魄属性
int set_con( int gift ) { return Con = gift; }

// 函数：设置精神属性
int set_spi( int gift ) { return Spi = gift; }

// 函数：设置力量属性
int set_str( int gift ) { return Str = gift; }

// 函数：设置耐力属性
int set_cps( int gift ) { return Cps = gift; }

// 函数：设置敏捷属性
int set_dex( int gift ) { return Dex = gift; }

// 函数：增添体魄属性
int add_con( int gift ) { return set_con( Con + gift ); }

// 函数：增添精神属性
int add_spi( int gift ) { return set_spi( Spi + gift ); }

// 函数：增添力量属性
int add_str( int gift ) { return set_str( Str + gift ); }

// 函数：增添耐力属性
int add_cps( int gift ) { return set_cps( Cps + gift ); }

// 函数：增添敏捷属性
int add_dex( int gift ) { return set_dex( Dex + gift ); }
