//Cracked by Roath
// Room: /d/xixia/xiaolu3.c

inherit ROOM;

void create()
{
	set("short", "林中小路");
	set("long", @LONG
这是陡坡上的一条杂草丛生的羊肠小路，看起来平时没什么人迹，路边开着
不知名的野花，两边的松树依然高大、挺拔。阳光透下来照的你身上是斑斑驳驳
的影子。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"bianmen",
  "east" : __DIR__"xiaolu2",
]));
	set("no_clean_up", 0);
	set("outdoors", "xixia");

	setup();
	replace_program(ROOM);
}
