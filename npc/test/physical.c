/*------------------------------------
	Tái Tạo by Ben
------------------------------------*/	
#include <npc.h>
#include <item.h>
#include <ansi.h>
#include <task.h>
#include <music.h>
#include <equip.h>
void taitao( object item, int abc );
void giamngoc( object item );

int * ben_vukhi = ({ 20, 0, 56, 0, 180, 0, 0, 50, 0, 40,
					 0, 56, 0, 180, 0, 0, 50, 0, 22, 0,
					 60, 0, 240, 0, 60, 0, 0, 44, 0, 60,
					 0, 240, 0, 60, 0, 0, 20, 0, 0, 60,
					 0, 0, 72, 51, 0, 40, 0, 0, 40, 0,
					 0, 72, 51, 0, 24, 0, 63, 0, 240, 0,
					 0, 0, 22, 48, 0, 63, 0, 240, 0, 0,
					 0, 22, 20, 0, 52, 0, 220, 0, 72, 0,
					 0, 40, 0, 52, 0, 220, 0, 72, 0, 0,
					 18, 0, 40, 0, 0, 80, 0, 70, 0, 36,
					 0, 32, 0, 0, 80, 0, 70, 0, 20, 0,
					 0, 50, 140, 0, 0, 50, 0, 40, 0, 0,
					 50, 140, 0, 0, 50, 0, 20, 0, 0, 65,
					 0, 160, 0, 50, 0, 40, 0, 0, 58, 0,
					 160, 0, 50, 0, 20, 0, 0, 48, 140, 140, 
					 0, 0, 0, 40, 0, 0, 48, 140, 140, 0,
					 0, 0, 22, 20, 63, 58, 0, 0, 0, 0,
					 0, 44, 40, 63, 53, 0, 0, 0, 0, 0, });
int * ben_ao = ({ 22, 14, 400, 0, 100, 0, 35, 44, 28, 400,
				   0, 100, 0, 35, 22, 14, 0, 0, 110, 40, 
				   40, 44, 28, 0, 0, 110, 40, 40, 24, 12, 
				   450, 0, 80, 0, 20, 48, 24, 450, 0, 80,
				   0, 20, 20, 14, 0, 0, 60, 50, 72, 40, 28,
				   0, 0, 60, 50, 72, 12, 24, 0, 480, 40, 68,
				   0, 24, 48, 0, 480, 40, 68, 0, 12, 24, 0,
				   400, 45, 75, 0, 24, 48, 0, 400, 45, 75, 
				   0, 14, 24, 200, 0, 55, 70, 0, 28, 48, 
				   200, 0, 55, 70, 0, 24, 24, 0, 0, 110, 
				   75, 0, 48, 48, 0, 0, 110, 75, 0, });
int * ben_non = ({ 12, 6, 200, 0, 60, 40, 0, 24, 12, 200,
				   0, 60, 40, 0, 12, 6, 0, 0, 62, 48, 40,
				   26, 14, 0, 0, 62, 48, 40, 14, 4, 280,
				   0, 55, 25, 0, 28, 10, 280, 0, 55, 25,
				   0, 8, 6, 0, 0, 40, 50, 60, 16, 12, 0,
				   0, 40, 50, 60, 6, 10, 0, 250, 30, 60,
				   0, 12, 20, 0, 250, 30, 60, 0, 6, 10, 
				   100, 0, 30, 64, 0, 12, 20, 100, 0, 30,
				   64, 0, 8, 10, 100, 200, 35, 0, 0, 16,
				   20, 100, 200, 35, 0, 0, 14, 10, 0, 0,
				   62, 64, 0, 28, 20, 0, 0, 62, 64, 0,  });
int * ben_giay = ({ 6, 6, 0, 180, 0, 50, 0, 50, 12, 12,
					0, 180, 0, 50, 0, 50, 6, 8, 0, 0,
					0, 54, 30, 55, 12, 16, 0, 0, 0, 54,
					30, 55, 6, 6, 0, 220, 0, 46, 20, 0,
					12, 12, 0, 270, 0, 46, 20, 0, 2, 12,
					0, 130, 0, 35, 0, 80, 4, 24, 0, 130,
					0, 35, 0, 80, 2, 4, 0, 0, 200, 30,
					60, 0, 4, 8, 0, 0, 200, 30, 60, 0,
					2, 4, 0, 0, 180, 30, 65, 0, 4, 8,
					0, 0, 180, 30, 65, 0, 2, 4, 0, 80,
					180, 50, 60, 0, 4, 8, 0, 80, 180, 50,
					60, 0, 6, 0, 6, 0, 0, 54, 65, 0,
					12, 0, 12, 0, 0, 54, 65, 0,  });
int * ben_yeudoi = ({ 10, 10, 250, 0, 60, 35, 0, 20, 20, 250,
					  0, 60, 35, 0, 10, 10, 0, 0, 66, 40,
					  15, 20, 20, 0, 0, 66, 40, 15, 10, 10,
					  300, 0, 55, 25, 0, 20, 20, 300, 0, 55,
					  25, 0, 10, 10, 0, 0, 40, 45, 30, 20,
					  20, 0, 0, 40, 45, 30, 10, 10, 0, 300, 
					  40, 55, 0, 20, 20, 0, 300, 40, 55, 0,
					  10, 10, 0, 250, 40, 57, 0, 20, 20, 0,
					  250, 40, 57, 0, 10, 10, 100, 250, 0, 57,
					  0, 10, 10, 0, 0, 66, 57, 0, 20, 20, 
					  0, 0, 66, 57, 0, });
int * ben_hanglien = ({ 0, 10, 0, 0, 0, 400, 0, 0, 50, 10,
						0, 20, 0, 0, 0, 400, 0, 0, 50, 10, 
						0, 10, 0, 0, 30, 400, 0, 0, 54, 0, 
						0, 20, 0, 0, 30, 400, 0, 0, 54, 0, 
						0, 10, 0, 0, 0, 400, 0, 0, 50, 10, 
						0, 20, 0, 0, 0, 400, 0, 0, 50, 10, 
						0, 10, 0, 0, 0, 300, 0, 0, 50, 20, 
						0, 20, 0, 0, 0, 300, 0, 0, 50, 20, 
						20, 12, 0, 0, 30, 0, 400, 0, 70, 0, 
						40, 24, 0, 0, 30, 0, 400, 0, 70, 0, 
						20, 10, 0, 0, 0, 200, 350, 0, 80, 0, 
						40, 20, 0, 0, 0, 200, 350, 0, 80, 0, 
						20, 10, 0, 0, 10, 250, 400, 0, 75, 0, 
						40, 20, 0, 0, 10, 250, 400, 0, 75, 0, 
						20, 0, 20, 30, 30, 0, 0, 0, 0, 0, 
						40, 0, 40, 30, 30, 0, 0, 0, 0, 0,  });

void taitao( object item, int abc )
{
	int pos, family, level, ran, i, j, less, value, value1, value2, value3, value4, value5, point, mau;
	object me = this_player(),ben;
        if( !clonep(item) ) return;  
        family = item->get_family();
        if (family==9) family = 2;
        if (family>8) family = 8;
        if (family<=0) family = 8;        
        level = item->get_level();
        point = level/6+ random(3+level/24); 
		mau = item->get_item_color();	
		ben = new(get_file_name(item));	
        switch(item->get_equip_type())
        {
        case WEAPON_TYPE:
        	switch(family)
        	{
        	case 1: pos = 8*9; break;
        	case 2: 
        		if (item->get_weapon_type()==SWORD) pos = 4*9; 
        		else pos = 0;
        		break;
        	case 3: 
        		if (item->get_weapon_type()==SPEAR) pos = 2*9; 
        		else pos = 6*9;
        		break;      
        	case 4: pos = 10*9; break;  		
        	case 5: pos = 12*9; break;
        	case 6: pos = 14*9; break;
               	case 7: pos = 16*9; break;
               default: pos = 18*9; break;
        	}
        	if (level>=80) pos += 9;
        	if (pos>= sizeof(ben_vukhi)) return;
        	if (item->get_weapon_type()==SWORD) { item->set("ap", ben->get("ap")); item->set("cp", ben->get("cp")); item->add("cp", ben_vukhi[pos+1]); }
       		else { item->set("cp", ben->get("cp")); item->set("ap", ben->get("ap")); item->add("ap", ben_vukhi[pos]); }
			item->set("hp", ben->get("hp"));
			item->set("mp", ben->get("mp"));
			item->set("dp", ben->get("dp"));
			item->set("pp", ben->get("pp"));
			item->set("sp", ben->get("sp"));
        	ran = random(10000);
        	less = 10000;       
        	j = 0;	
        	for (i=2;i<9;i++)
        	{
        		if (ben_vukhi[pos+i]!=0)
        		{
        			value = ben_vukhi[pos+i] * point * ran / 100000;
        			less -= ran;
        			j++;
        			if (j>=2)
        				ran = less;
        			else
        				ran = random(less);
        			switch(i)
        			{
        			case 2: 
					if (item->get_weapon_type()!=SWORD) 
					{
					if (abc==1) item->add("ap", value);
					else if (abc==2) item->add("ap", value*2); 
					}
					break;
        			case 3: 
					if (item->get_weapon_type()==SWORD) 
					{
					if ( abc==1 ) item->add("cp", value);
					else if (abc==2) item->add("cp", value*2); 
					} 
					break;
        			case 4: 
					item->add("hp", value);
					break;
        			case 5:
					item->add("mp", 0);
					break;
        			case 6: 
					item->add("dp", 0);
					break;
        			case 7: 
					item->add("pp", 0);
					break;
        			case 8: 
					item->add("sp", value/5);
					break;
        			}
        			if (less<=0) break;
        		}
        	}		     	
        	break; 
		case ARMOR_TYPE:
        	pos = (family-1) * 14;
        	if (pos<0) pos = 0;
        	if (level>=80) pos += 7;
        	if (pos>= sizeof(ben_ao)) return;
        	item->set("hp", ben->get("hp"));
			item->set("mp", ben->get("mp"));
			item->set("dp", ben->get("dp"));
			item->add("dp", ben_ao[pos]);
			item->set("pp", ben->get("pp"));			
        	item->add("pp", ben_ao[pos+1]);	
			item->set("sp", ben->get("sp"));
        	ran = random(10000);
        	less = 10000;
			for (i=2;i<7;i++)
        	{
        		if (ben_ao[pos+i]!=0)
        		{
        			value = ben_ao[pos+i] * point * ran / 100000;
        			less -= ran;
        			j++;
        			if (j>=2)
        				ran = less;
        			else
        				ran = random(less);
        			switch(i)
        			{
        			case 2: 
					if(family!=6&&family!=4)
					{	
					if(abc==1) 										
						{
							if ( mau==1 ) item->add("hp", value);
							else if ( mau==2 ) item->add("hp", value);
                            else if ( mau==5 ) item->add("hp", value*2);							
						}				
					else if(abc==2)
					  {
							if ( mau==1 ) item->add("hp", value*2);
							else if ( mau==2 ) item->add("hp", value*2);
                            else if ( mau==5 ) item->add("hp", value*3);							
						}
					}	
					break;
        			case 3: 
					if(family==6||family==7) item->add("mp", value);
					break;
        			case 4: 
					if(abc==1)
					 {
							if ( mau==1 ) item->add("dp", value);
							else if ( mau==2 ) item->add("dp", value);
                            else if ( mau==5 ) item->add("dp", value*2);							
						}
					else if(abc==2)
                         {
							if ( mau==1 ) item->add("dp", value*2);
							else if ( mau==2 ) item->add("dp", value*2);
                            else if ( mau==5 ) item->add("dp", value*3);							
						}						
					break;
        			case 5: 
					if(abc==1) 
					 {
							if ( mau==1 ) item->add("pp", value);
							else if ( mau==2 ) item->add("pp", value);
                           else if ( mau==5 ) item->add("pp", value*2);							
						}
					else if(abc==2) 
						{
							if ( mau==1 ) item->add("pp", value*2);
							else if ( mau==2 ) item->add("pp", value*2);
                            else if ( mau==5 ) item->add("pp", value*3);							
						}
					break;
        			case 6: 
					if(family==4) {
						if(abc==1) 
						 {
							if ( mau==1 ) item->add("sp", value);
							else if ( mau==2 ) item->add("sp", value);
                           else if ( mau==5 ) item->add("sp", value*2);							
						}
						else if(abc==2)
							{
							if ( mau==1 ) item->add("sp", value*2);
							else if ( mau==2 ) item->add("sp", value*2);
                            else if ( mau==5 ) item->add("sp", value*5/2);							
						}
					}
					break;
        			}
        			if (less<=0) break;
        		}
        	}
        	break;
		case HEAD_TYPE:
        	pos = (family-1) * 14;
        	if (pos<0) pos = 0;
        	if (level>=80) pos += 7;
        	if (pos>= sizeof(ben_non)) return;
			item->set("hp", ben->get("hp"));
			item->set("mp", ben->get("mp"));
			item->set("dp", ben->get("dp"));
        	item->add("dp", ben_non[pos]);	
			item->set("pp", ben->get("pp"));	
        	item->add("pp", ben_non[pos+1]);	
			item->set("sp", ben->get("sp"));
        	ran = random(10000);
        	less = 10000;       
        	j = 0;	
        	for (i=2;i<7;i++)
        	{
        		if (ben_non[pos+i]!=0)
        		{
        			value = ben_non[pos+i] * point * ran / 100000;
        			less -= ran;
        			j++;
        			if (j>=2)
        				ran = less;
        			else
        				ran = random(less);
        			switch(i)
        			{
        			case 2: 
					if (family!=6&&family!=4)
					{	
					if(abc==1) 
                       {
							if ( mau==1 ) item->add("hp", value);
							else if ( mau==2 ) item->add("hp", value);
                           else if ( mau==5 ) item->add("hp", value*2);							
						}				
					else if(abc==2)
					  {
							if ( mau==1 ) item->add("hp", value*2);
							else if ( mau==2 ) item->add("hp", value*2);
                            else if ( mau==5 ) item->add("hp", value*3);							
						}
					}
					break;
        			case 3: 
					if (family==6||family==7) item->add("mp", value);
					break;
        			case 4: 
					if (abc==1) 
					{
							if ( mau==1 ) item->add("dp", value);
							else if ( mau==2 ) item->add("dp", value);
                            else if ( mau==5 ) item->add("dp", value*2);							
						}
					else if (abc==2) 
						{
							if ( mau==1 ) item->add("dp", value*2);
							else if ( mau==2 ) item->add("dp", value*2);
                            else if ( mau==5 ) item->add("dp", value*3);							
						}
					break;
        			case 5: 
					if (abc==1) 
						{
							if ( mau==1 ) item->add("pp", value);
							else if ( mau==2 ) item->add("pp", value);
                            else if ( mau==5 ) item->add("pp", value*2);							
						}
					else if (abc==2) 
					 {
							if ( mau==1 ) item->add("pp", value*2);
							else if ( mau==2 ) item->add("pp", value*2);
                            else if ( mau==5 ) item->add("pp", value*3);							
						}
					break;
        			case 6: 
					if(family==4) {
						if(abc==1) 
							{
							if ( mau==1 ) item->add("sp", value);
							else if ( mau==2 ) item->add("sp", value);
                           else if ( mau==5 ) item->add("sp", value*2);							
						}
						else if(abc==2) 
							{
							if ( mau==1 ) item->add("sp", value*2);
							else if ( mau==2 ) item->add("sp", value*2);
                            else if ( mau==5 ) item->add("sp", value*5/2);							
						}
					}
					break;
        			}
        			if (less<=0) break;
        		}
        	}
        	break;	
		case NECK_TYPE:    
        	pos = (family-1) * 20;
        	if (pos<0) pos = 0;
        	if (level>=80) pos += 10;
        	if (pos>= sizeof(ben_hanglien)) return;
			item->set("hp", ben->get("hp"));	
			item->set("mp", ben->get("mp"));	
			item->set("dp", ben->get("dp"));	
			item->set("cp", ben->get("cp"));	
			item->add("cp", ben_hanglien[pos]);
			item->set("pp", ben->get("pp"));
        	item->add("pp", ben_hanglien[pos+1]);
			item->set("ap", ben->get("ap"));			
        	item->add("ap", ben_hanglien[pos+2]);
			item->set("sp", ben->get("sp"));
        	ran = random(10000);
        	less = 10000;       
        	j = 0;	
        	for (i=3;i<10;i++)
        	{
        		if (ben_hanglien[pos+i]!=0)
        		{
        			value = ben_hanglien[pos+i] * point * ran / 100000;
        			less -= ran;
        			j++;
        			if (j>=2)
        				ran = less;
        			else
        				ran = random(less);
        			switch(i)
        			{
        			case 3: 
					if (family==8)
					{
						if (abc==1) 
							{
							if ( mau==1 ) item->add("ap", value);
							else if ( mau==2 ) item->add("ap", value);
                            else if ( mau==5 ) item->add("ap", value*2);							
						}
						else if (abc==2) 
							{
							if ( mau==1 ) item->add("ap", value*5/2);
							else if ( mau==2 ) item->add("ap", value*5/2);
                            else if ( mau==5 ) item->add("ap", value*7/2);							
						}
					} 
					break;
        			case 4: // THêm ngoại công cho TS
					if(family==2) {
						if(abc==1) 
                        {
							 if ( mau==5 ) item->add("ap", value*7/2);								
						}							
						else if(abc==2) 
						{
							if ( mau==5 ) item->add("ap", value*7/2);							
						}
					}
					if (abc==1) 
						{
							if ( mau==1 ) item->add("cp", value);
							else if ( mau==2 ) item->add("cp", value);
                            else if ( mau==5 ) item->add("cp", value*2);											
						}
					else if (abc==2) 
						{
							if ( mau==1 ) item->add("cp", value*2);
							else if ( mau==2 ) item->add("cp", value*2);
                            else if ( mau==5 ) item->add("cp", value*3);							
						}					
					break;
        			case 5:
					// THêm ngoại công cho CL
					if(family==6) {
						if(abc==1) 
                        {
							 if ( mau==5 ) { 
							 item->add("ap", value/3);
							 item->add("cp", value/3); 
							 }
						}							
						else if(abc==2) 
						{
							if ( mau==5 ) { 
							 item->add("ap", value/3);
							 item->add("cp", value/3); }						
						}
					}
					if (abc==1) 
						{
							if ( mau==1 ) item->add("hp", value);
							else if ( mau==2 ) item->add("hp", value);
                            else if ( mau==5 ) item->add("hp", value*2);							
						}
					else if (abc==2) 
						{
							if ( mau==1 ) item->add("hp", value*2);
							else if ( mau==2 ) item->add("hp", value*2);
                            else if ( mau==5 ) item->add("hp", value*3);							
						}
					break;
        			case 6:
					item->add("mp", 0);
					break;
        			case 7: 
					item->add("dp", 0);
					break;
        			case 8: 
					if (abc==1) 
						{
							if ( mau==1 ) item->add("pp", value);
							else if ( mau==2 ) item->add("pp", value);
                            else if ( mau==5 ) item->add("pp", value*2);							
						}
					else if (abc==2) 
                       {
							if ( mau==1 ) item->add("pp", value*2);
							else if ( mau==2 ) item->add("pp", value*2);
                            else if ( mau==5 ) item->add("pp", value*2);							
						}						
					break;
        			case 9: 
					if(family==4) {
						if(abc==1) 
                           {
							if ( mau==1 ) item->add("sp", value);
							else if ( mau==2 ) item->add("sp", value);
                            else if ( mau==5 ) item->add("sp", value*5/2);							
						}							
						else if(abc==2) 
							{
							if ( mau==1 ) item->add("sp", value*2);
							else if ( mau==2 ) item->add("sp", value*2);
                            else if ( mau==5 ) item->add("sp", value*5/2);							
						}
					}
					break;
	
        			}        			
        			if (less<=0) break;
        		}
        	}
        	break;
		case WAIST_TYPE:   	
			pos = (family-1) * 14;
        	if (pos<0) pos = 0;
        	if (level>=80&&family!=7) pos += 7;
        	if (pos>= sizeof(ben_yeudoi)) return;
			item->set("hp", ben->get("hp"));
			item->set("mp", ben->get("mp")); 
			item->set("dp", ben->get("dp"));
        	item->add("dp", ben_yeudoi[pos]);
			item->set("pp", ben->get("pp"));
        	item->add("pp", ben_yeudoi[pos+1]);	
			item->set("sp", ben->get("sp"));
        	ran = random(10000);
        	less = 10000;       
        	j = 0;	
        	for (i=2;i<7;i++)
        	{
        		if (ben_yeudoi[pos+i]!=0)
        		{
        			value = ben_yeudoi[pos+i] * point * ran / 100000;
        			less -= ran;
        			j++;
        			if (j>=2)
        				ran = less;
        			else
        				ran = random(less);
        			switch(i)
        			{
        			case 2: 
					if(abc==1) 
						{
							if ( mau==1 ) item->add("hp", value);
							else if ( mau==2 ) item->add("hp", value);
                            else if ( mau==5 ) item->add("hp", value*2);							
						}
					else if(abc==2) 
						{
							if ( mau==1 ) item->add("hp", value*2);
							else if ( mau==2 ) item->add("hp", value*2);
                           else if ( mau==5 ) item->add("hp", value*3);							
						}
					break;
        			case 3: 
					if(abc==1) 
                       {
							if ( mau==1 ) item->add("mp", value);
							else if ( mau==2 ) item->add("mp", value);
                            else if ( mau==5 ) item->add("mp", value*2);							
						}						
					else if(abc==2) 
						{
							if ( mau==1 ) item->add("mp", value*2);
							else if ( mau==2 ) item->add("mp", value*2);
                            else if ( mau==5 ) item->add("mp", value*3);							
						}
					break;
        			case 4: 
					if(abc==1) 
						{
							if ( mau==1 ) item->add("dp", value);
							else if ( mau==2 ) item->add("dp", value);
                           else if ( mau==5 ) item->add("dp", value*2);							
						}
					else if(abc==2) 
						{
							if ( mau==1 ) item->add("dp", value*2);
							else if ( mau==2 ) item->add("dp", value*2);
                            else if ( mau==5 ) item->add("dp", value*3);							
						}
					break;
        			case 5: 
					if(abc==1) 
                        {
							if ( mau==1 ) item->add("pp", value);
							else if ( mau==2 ) item->add("pp", value);
                           else if ( mau==5 ) item->add("pp", value*2);							
						}						
					else if(abc==2) 
                       {
							if ( mau==1 ) item->add("pp", value*2);
							else if ( mau==2 ) item->add("pp", value*2);
                            else if ( mau==5 ) item->add("pp", value*3);							
						}						
					break;
        			case 6: 
					if(family==4) {
						if(abc==1)
							{
							if ( mau==1 ) item->add("sp", value);
							else if ( mau==2 ) item->add("sp", value);
                            else if ( mau==5 ) item->add("sp", value*5/2);							
						}
						else if(abc==2) 
							{
							if ( mau==1 ) item->add("sp", value*2);
							else if ( mau==2 ) item->add("sp", value*2);
                            else if ( mau==5 ) item->add("sp", value*5/2);							
						}
					}
					break;
        			}
        			if (less<=0) break;
        		}
        	}
        	break;	
		case BOOTS_TYPE:      	
        	pos = (family-1) * 16;
        	if (pos<0) pos = 0;
        	if (level>=80) pos += 8;
        	if (pos>= sizeof(ben_giay)) return;
			item->set("hp", ben->get("hp"));
			item->set("mp", ben->get("mp")); 
			item->set("dp", ben->get("dp"));
			item->add("dp", ben_giay[pos]);	
			item->set("pp", ben->get("pp")); 
			item->add("pp", ben_giay[pos+2]);
			item->set("sp", ben->get("sp"));
        	item->add("sp", ben_giay[pos+1]);			
        	ran = random(10000);
        	less = 10000;       
        	j = 0;	
        	for (i=3;i<8;i++)
        	{
        		if (ben_giay[pos+i]!=0)
        		{
        			value = ben_giay[pos+i] * point * ran / 100000;
        			less -= ran;        			
        			j++;
        			if (j>=2)
        				ran = less;
        			else
        				ran = random(less);
        			switch(i)
        			{
        			case 3: 					
					item->add("hp", value*3/2);
					break;
        			case 4: 
					item->add("mp", 0); 
					break;
        			case 5: 
					if (family!=4)
					{
						if(abc==1) 
							{
							if ( mau==1 ) item->add("dp", value);
							else if ( mau==2 ) item->add("dp", value);
                           else if ( mau==5 ) item->add("dp", value*2);							
						}
						else if(abc==2) 
							{
							if ( mau==1 ) item->add("dp", value*2);
							else if ( mau==2 ) item->add("dp", value*2);
                            else if ( mau==5 ) item->add("dp", value*3);							
						}
					}					
					else
					{
						if(abc==1) 
                          {
							if ( mau==1 ) item->add("dp", value/3);
							else if ( mau==2 ) item->add("dp", value/3);
                            else if ( mau==5 ) item->add("dp", value);							
						}							
						else if(abc==2)
							{
							if ( mau==1 ) item->add("dp", value);
							else if ( mau==2 ) item->add("dp", value);
                            else if ( mau==5 ) item->add("dp", value*2);							
						}
					} 
					break;
        			case 6: 
					item->add("pp", 0);
					break;
        			case 7: 
					if(family==4) 
					{
					if(abc==1) 
						{
							if ( mau==1 ) item->add("sp", value/2);
							else if ( mau==2 ) item->add("sp", value);
                            else if ( mau==5 ) item->add("sp", value*5/2);							
						}
					else if(abc==2) 
						{
							if ( mau==1 ) item->add("sp", value);	
							else if ( mau==2 ) item->add("sp", value*2);
                           else if ( mau==5 ) item->add("sp", value*5/2);							
						}
					}
					break;
        			}        			
        			if (less<=0) break;
        		}
        	}		
        	break;	
        }
}
