#include <equip.h>

string *FileTable1 = ({
	"cash",
	"/item/test/chenbac",

});

string *FileTable2 = ({

	"/item/60/1120",
	"/item/61/1120",
	"/item/65/1120",
	"/item/66/1120",

});

string *FileTable3 = ({

	//	"/item/test2/TuiQuaVoSong",
	//	"/item/test2/TuiPhapBao",
	"/item/test2/1001",
	"/item/test/chenbac",
	//	"/item/08/0016",
	//	"/item/08/0017",

});

object *get_item()
{
	int i, rand, size;
	string file;
	string *line;
	object *all, item;
	all = ({});
	rand = random(sizeof(FileTable3));
	file = FileTable3[rand];
	if (file == "cash")
	{
		item = new ("/item/std/0001");
		item->set_value(50000);
	}
	else if (file == "cash2")
	{
		item = new ("/item/std/0001");
		item->set_value(100000);
	}
	else if (file == "cash3")
	{
		item = new ("/item/std/0001");
		item->set_value(150000);
	}
	else if (file == "cash4")
	{
		item = new ("/item/std/0001");
		item->set_value(200000);
	}
	else if (file == "cash5")
	{
		item = new ("/item/std/0001");
		item->set_value(300000);
	}
	else if (file == "cash6")
	{
		item = new ("/item/std/0001");
		item->set_value(500000);
	}
	else if (file == "cash7")
	{
		item = new ("/item/std/0001");
		item->set_value(1000000);
	}
	else if (file == "cash8")
	{
		item = new ("/item/std/0001");
		item->set_value(2000000);
	}
	else
	{
		item = new (file);
		item->set_amount(2);
	}
	all += ({item});
	/*	line = copy(FileTable2);
	for (i=0;i<1;i++)
	{
		size = sizeof(line);
		file = line[random(size)];
		item = new (file);
		all += ({ item });
		line -= ({ file });
		if (item->get_equip_type()>0 && item->get_equip_type()!=HAND_TYPE)
		{
			"/sys/item/equip"->init_equip_prop_3(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			"/sys/item/equip"->init_equip_prop_5(item);
			item->set_item_color(2);
			item->set_hide(0);
			item->set("forge", "111111");
		}		
	}*/
	//	line = copy(FileTable1);
	for (i = 0; i < 7; i++)
	{
		rand = random(sizeof(FileTable1));
		file = FileTable1[rand];

		//		size = sizeof(line);
		//		file = line[random(size)];
		if (file == "cash")
		{
			item = new ("/item/std/0001");
			item->set_value(50000);
		}
		else if (file == "cash2")
		{
			item = new ("/item/std/0001");
			item->set_value(100000);
		}
		else if (file == "cash3")
		{
			item = new ("/item/std/0001");
			item->set_value(150000);
		}
		else if (file == "cash4")
		{
			item = new ("/item/std/0001");
			item->set_value(200000);
		}
		else if (file == "cash5")
		{
			item = new ("/item/std/0001");
			item->set_value(300000);
		}
		else if (file == "cash6")
		{
			item = new ("/item/std/0001");
			item->set_value(500000);
		}
		else if (file == "cash7")
		{
			item = new ("/item/std/0001");
			item->set_value(1000000);
		}
		else if (file == "cash8")
		{
			item = new ("/item/std/0001");
			item->set_value(2000000);
		}
		else
		{
			item = new (file);
			item->set_amount(2);
			/*	if (item->get_max_combined()>1) 
			{
				if (item->get_stuff_type()>0)
					item->set_amount(5);
			}*/
		}
		all += ({item});
		//	line -= ({ file });
	}
	return all;
}

void check_item()
{
	int i, size;
	size = sizeof(FileTable1);
	for (i = 0; i < size; i++)
	{
		if (FileTable1[i] == "cash")
			continue;
		if (!load_object(FileTable1[i]))
		{
			log_file("test.dat", FileTable1[i] + " error\n");
		}
	}
	size = sizeof(FileTable2);
	for (i = 0; i < size; i++)
	{
		if (FileTable2[i] == "cash")
			continue;
		if (!load_object(FileTable2[i]))
		{
			log_file("test.dat", FileTable2[i] + " error\n");
		}
	}
	size = sizeof(FileTable3);
	for (i = 0; i < size; i++)
	{
		if (FileTable3[i] == "cash")
			continue;
		if (!load_object(FileTable3[i]))
		{
			log_file("test.dat", FileTable3[i] + " error\n");
		}
	}
}