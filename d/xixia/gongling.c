//Cracked by Roath
// Room: /d/xixia/gongling.c

inherit ROOM;

void create()
{
	set("short", "恭陵");
	set("long", @LONG
这是西夏先主拓跋思恭的陵墓，拓跋思恭当年率党项羌族归顺唐太
宗李世民而被赐姓为李，这李思恭在唐初也是极有名的大将。如今因为
年代久远他的陵墓也不复当年的雄伟而看上去有点破败。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"deling",
]));
	set("cost", 2);
	set("outdoors", "xixia");

	setup();
	replace_program(ROOM);
}
