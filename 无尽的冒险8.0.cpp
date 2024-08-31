#include <iostream>
#include <windows.h>
#include <conio.h>
using std::cout;
void SetConsoleTextColor(long long a);
void DelayPrint(char *p);
void Pause();
void SetConsoleCursor(int x, int y);
void SetWindowPosition(int x, int y);
void in(int &a);
void read();
void write();
void out();
void sprint(char *p);
int SuiJi(int a, int b);
/*************************************************/
struct Display
{
	char name[50];
	long long attack;
	long long defense;
	long long level;
	long long max_xp;
	bool active; // 是否为主动技能
}; // 测试阶段，代码不知道怎么实现
struct Monster
{
	char name[30];
	char display[20];
	long long health;
	long long max_health;
	long long attack;
	long long defense;
	long long level;
	char fang[20];
	char gong[20];
	long long money;
	long long xp;
	void sx()
	{
		printf("\n怪物名字：%s\n", name);
		printf("怪物技能：%s\n", display);
		printf("生命：%lld\n", health);
		printf("攻击力：%lld*%lld=*%lld\n", attack, level, attack * level);
		printf("防御力：%lld*%lld=*%lld\n", defense, level, defense * level);
		printf("等级：%lld\n", level);
	}
	bool alive()
	{
		//		alive=>true
		//		die=>false
		if (health <= 0)
		{
			return false;
		}
		return true;
	}
};
struct pet
{
	char name[30];
	char display1[20];
	char display2[20];
	long long health;
	long long max_health;
	long long xp;
	long long max_xp;
	long long attack;
	long long defense;
	long long level;
	char fang[20];
	char gong[20];
	long long money;
	long long displayd;
	void sx()
	{
		printf("\n宠物名字：%s\n", name);
		printf("宠物技能：(%s,%s)\n", display1, display2);
		printf("生命：%lld\n", health);
		printf("最大生命：%lld\n", max_health);
		printf("攻击力：%lld\n", attack);
		printf("防御力：%lld\n", defense);
		printf("等级：%lld\n", level);
		printf("经验:%lld\n升级所需经验：%lld\n", xp, max_xp);
	}
	void level_up()
	{
		if (xp >= max_xp)
		{
			displayd += xp / max_xp;
			printf("\n你的宠物升级啦！！\n");
			printf("等级：%lld==>%lld\n", level, level + xp / max_xp);
			level += xp / max_xp;
			printf("攻击力：%lld==>%lld\n", attack, attack * 1.5);
			attack *= 1.5;
			printf("防御力：%lld==>%lld\n", defense, defense * 1.5);
			defense *= 1.5;
			printf("最大生命：%lld==>%lld\n", max_health, max_health + (xp / max_xp) * 4);
			max_health += (xp / max_xp) * 4;
			printf("技能点:%lld==>%lld\n", displayd - xp / max_xp, displayd);
			xp %= max_xp;
		}
		else
			return;
	}
	bool alive()
	{
		//		alive=>true
		//		die=>false
		if (health <= 0)
		{
			return false;
		}
		if (health < max_health * 0.5)
		{
			cout << "\n注意，您的宠物血量已不足50%\n";
			return true;
		}
		if (health < max_health * 0.3)
		{
			cout << "\n注意！您的宠物血量已不足30%\n";
			return true;
		}
		if (health < max_health * 0.1)
		{
			cout << "\n警告！您的宠物血量已不足10%,请治疗TA!\n";
			return true;
		}
		return true;
	}
};
struct plant
{
	char name[200];	 // 任务名
	long long money; // 奖励的金币
	bool finish;	 // 是否完成
	bool get;		 // 是否领取
};
struct Cloths
{
	char name[25];
	long long attack_up;
	long long defense_up;
	long long num;
	long long money; // 售价
	void sx()
	{
		printf("\n名字[%s]\n", name);
		printf("攻击增强:%lld\n", attack_up);
		printf("防御增强:%lld\n", defense_up);
		printf("价格:%lld\n", money);
	}
};
struct cloths_slot
{
	Cloths head, body, leg, foot;
};
struct cloths_fight
{
	Cloths hand, arm;
};
struct wuping
{
	// 用来合成
	// 如果有效果也可以像道具那样用一次
	char name[20];
	char hecheng[100];
	char texiao[100];
	long long need_money;
	void sx()
	{
		printf("\n物品名字:[%s]\n", name);
		if (strcmp(hecheng, "") == 0)
			printf("无法合成\n");
		else
			printf("合成方式:[%s]\n", hecheng);
		if (strcmp(texiao, "") == 0)
			printf("无特效\n");
		else
			printf("特效:[%s]\n", texiao);
		printf("价值:%lld\n", need_money);
	}
};
struct daoju
{
	// 像药水一样使用一次就用完了...
	char name[20];
	long long attack;
	long long defense;
	char hecheng[100];
	char texiao[100];
	long long need_money;
	void sx()
	{
		printf("\n道具名字:[%s]\n", name);
		printf("攻击增加: %lld\n", attack);
		printf("防御增加: %lld\n", defense);
		if (strcmp(hecheng, "") == 0)
			printf("无法合成\n");
		else
			printf("合成方式:[%s]\n", hecheng);
		if (strcmp(texiao, "") == 0)
			printf("无特效\n");
		else
			printf("特效:[%s]\n", texiao);
		printf("价值:%lld\n", need_money);
	}
	void operator=(const wuping a)
	{
		strcpy(name, a.name);
		strcpy(hecheng, a.hecheng);
		strcpy(texiao, a.texiao);
		need_money = a.need_money;
		attack = defense = 0;
	}
};
struct PLAYER
{
	char name[100];
	char display[20];
	long long health;
	long long max_health;
	long long xp;
	long long max_xp;
	long long attack;
	long long defense;
	long long level;
	long long money;
	/********/
	pet p_pet[9]; // 玩家拥有8只宠物【8只为宠物上限】
	plant player_plant[100];
	cloths_slot slot;
	cloths_fight fight;
	/********/
	void sx()
	{
		printf("\n名字：%s\n", name);
		printf("初始技能：%s\n", display);
		printf("生命：%lld\n", health);
		printf("最大生命：%lld\n", max_health);
		printf("攻击力：%lld\n", attack);
		printf("防御力：%lld\n", defense);
		printf("等级：%lld\n", level);
		printf("经验:%lld\n升级所需经验：%lld\n", xp, max_xp);
		printf("金币:%lld\n", money);
	}
	void level_up()
	{
		if (xp >= max_xp)
		{
			printf("升级！！\n");
			printf("等级：%lld==>%lld\n", level, level + xp / max_xp);
			level += xp / max_xp;
			printf("攻击力：%lld==>%lld\n", attack, (long long)attack * 1.5);
			attack *= 1.5;
			printf("防御力：%lld==>%lld\n", defense, (long long)defense * 1.5);
			defense *= 1.5;
			printf("最大生命：%lld==>%lld", max_health, max_health + (xp / max_xp) * 4);
			max_health += (xp / max_xp) * 4;
			xp /= max_xp;
		}
		else
			return;
	}
	bool alive()
	{
		//		alive=>true
		//		die=>false
		if (health <= 0)
		{
			return false;
		}
		if (health < max_health * 0.5)
		{
			cout << "\n注意，您的血量已不足50%\n";
			return true;
		}
		if (health < max_health * 0.3)
		{
			cout << "\n注意！您的血量已不足30%\n";
			return true;
		}
		if (health < max_health * 0.1)
		{
			cout << "\n警告！血量已不足10%,请速速离开!\n";
			return true;
		}
		return true;
	}
	int display_sx()
	{
		// 冰封1  电击2  灼烧3
		// 狂暴4  自由搏击5  连击6
		if (strcmp(display, "冰封") == 0)
		{
			return 1;
		}
		if (strcmp(display, "电击") == 0)
		{
			return 2;
		}
		if (strcmp(display, "灼烧") == 0)
		{
			return 3;
		}
		if (strcmp(display, "狂暴") == 0)
		{
			return 4;
		}
		if (strcmp(display, "自由搏击") == 0)
		{
			return 5;
		}
		if (strcmp(display, "连击") == 0)
		{
			return 6;
		}
	}
};
struct world
{
	// 游戏变量
	bool hou_o; // 冒险家小屋的主人
	SYSTEMTIME now;
	SYSTEMTIME last;
};
/*******************变量定义**********************/
int i, j, k, n, m, bb;
PLAYER player;
pet Pet[20] = {
	{}, {"小恐龙", "喷火", "冲撞", 50, 50, 0, 90, 15, 9, 1, "凌甲", "钢爪", 150, 0}, {"大鹏鸟", "高鸣", "俯冲", 70, 70, 0, 120, 23, 14, 1, "羽盾", "尖嘴", 200, 0}, {"史莱姆", "粘丝", "分身level_up", 69, 69, 0, 300, 50, 73, 1, "主角甲", "主角盾", 960, 0}, {"\0", "\0", "\0", 0, 0, 0, 0, 0, 0, 0, "\0", "\0", 0, 0}};
/*
char name[25];
	long long attack_up;
	long long defense_up;
	long long num;
	long long money;//售价
	*/
Cloths c_std[100] = {
	{}, {"破旧的小刀", 10, 0, 0, 30}, {"破木盾", 0, 13, 0, 30}, {"铁剑", 17, 2, 0, 50}, {"铁甲", 0, 19, 0, 50}, {"滑石刀", 30, 6, 0, 390}, {"轻质石衣", 2, 35, 0, 390}, {"长勾", 25, 10, 0, 400}, {"圣骑士的盾", 13, 40, 0, 400}, {"雪山激光剑", 60, 35, 0, 1600}, {"冰玉石", 10, 90, 0, 1600}, {"光辉-0", 98, 80, 0, 2800}, {"结界", 30, 100, 0, 3220}};
world wor;
pet empity = {};
// wuping & daoju
// 见：我的世界图鉴大全
wuping things[100] =
	{
		{}, {"草", "1*dirt", "", 1}, {"土", "1*grass", "", 1}, {"石头", "1*cobblestone", "", 3}, {"圆石", "1*stone", "", 3}, {"空气", "", "Doomsday Lord", 9223372036854775800}, // 效果：末日之主
		{"花岗岩", "", "", 3},
		{"磨制花岗岩", "9*granite", "", 27},
		{"闪长岩", "", "", 3},
		{"磨制闪长岩", "9*diorite", "", 27},
		{"安山岩", "", "", 3},
		{"磨制安山岩", "9*andesite", "", 27},
		{"沙子", "", "", 1},
		{"木头", "", "", 16},
		{"木板", "1/4*log", "", 4}};
#define grass things[1]
#define dirt things[2]
#define stone things[3]
#define cobblestone things[4]
#define air things[5]
#define granite things[6]
#define polished_granite things[7]
#define diorite things[8]
#define polished_diorite things[9]
#define andesite things[10]
#define polished_andesite things[11]
#define sand things[12]
#define log things[13]
#define planks things[14]
daoju prop[100] =
	{
		{}, {}};
// fight
Monster *guai;
Monster monster[100] = {
	{}, {"炒鸡玛丽", "", 200, 200, 100, 80, 1, "玛丽刀", "玛丽甲", 100, 30}, {"超级蘑菇", "", 300, 300, 40, 60, 1, "孢刃", "孢盾", 130, 40}, {"国王", "control", 500, 500, 100, 100, 1, "国王的新枪", "国王的皇冠", 500, 80}, {"克鲁斯之眼", "", 1000, 1000, 400, 130, 1, "", "", 1000, 300}, {"[毁灭]上帝", "上帝之手", 5e3, 5e3, 3000, 3000, 1, "", "", 1e5, 1e3}, {"人类", "生命回复", 100, 100, 5, 3000, 1, "", "", 5e3, 90}, {"森林女王", "森林控制", 3000, 3000, 400, 800, 1, "藤鞭", "至圣金盾", 10000, 8000}, {"梦之守卫", "威压", 240, 240, 80, 120, 1, "梦境匕首", "云制衣", 300, 70}, {"神秘老人", "开挂", 400, 400, 300, 1000, 1, "[氪金道具]法杖", "[氪金道具]防护罩", 10, 1000}, {"[至圣]欧几里得", "几何构建", 1000, 1000, 400, 400, 1, "[几何原本]角", "[几何原本]图", 10000, 100000}, {"粉红羊先生", "", 200, 200, 50, 40, 1, "", "", 1000, 1000}, {"猪先生", "", 200, 200, 80, 20, 1, "", "", 800, 1200}, {"Steve", "世界编辑者", 800, 800, 130, 200, 1, "", "", 1000, 2000}};
#define ml monster[1]
#define mg monster[2]
#define king monster[3]
#define krous_eye monster[4]
#define God monster[5]
#define Human monster[6]
#define slnw monster[7]
#define mzsw monster[8]
#define smlr monster[9]
#define ojld monster[10]
#define sheep monster[11]
#define pig monster[12]
#define steve monster[13]
bool fighting;
bool can_use_display;
Cloths _empity;
Cloths canin[100];
//......................其它应用变量
int strpla(plant a[])
{
	for (int i = 1;; i++)
	{
		if (strcmp(a[i].name, "\0") == 0)
			return i - 1;
	}
}
int strpet(pet Pet[])
{ // 宠物数量统计
	for (int i = 1;; i++)
	{
		if (strcmp(Pet[i].name, "\0") == 0)
			return i - 1;
		if (i >= 1000)
			return -1;
	}
}
int strclo(Cloths a[])
{
	for (int i = 1; i <= 1000; i++)
	{
		//		cout<<"出不去\n";
		if (strcmp(a[i].name, "\0") == 0)
			return i - 1;
		if (i >= 1000)
			return -1;
	}
}
int jiazaic()
{ // 载入装备
	int a = 0;
	for (int i = 1; i <= strclo(c_std); i++)
	{
		if (c_std[i].num > 0)
			canin[++a] = c_std[i];
	}
	return a;
	// 统计可装备装备数量
	// 并加入数组
}
void number_of_cloth(char a[], int number)
{
	int l = strclo(c_std);
	for (i = 1; i <= l; i++)
	{
		if (strcmp(c_std[i].name, a) == 0)
			c_std[i].num += number;
	}
}
void sale(Cloths &a)
{
	a.sx();
	printf("是否卖出%s?1.yes 2.no\n", a.name);
	int bb;
mai:
	in(bb);
	if (bb == 2)
		return;
	if (bb != 1)
	{
		cout << "输入错误\n";
		goto mai;
	}
	player.money += a.money;
	number_of_cloth(a.name, -1);
	printf("成功卖出%s!,你获得了%lld金币\n", a.name, a.money);
}
int displayxz(int x)
{
	if (x == 1)
		while (1)
		{
			in(bb);
			switch (bb)
			{
			case 1:
				strcpy(player.display, "冰封");
				return 0;
			case 2:
				strcpy(player.display, "电击");
				return 0;
			case 3:
				strcpy(player.display, "灼烧");
				return 0;
			case 0:
				return 1;
			default:
				cout << "输入错误\n";
				break;
			}
		}
	if (x == 2)
		while (1)
		{
			in(bb);
			switch (bb)
			{
			case 1:
				strcpy(player.display, "狂暴");
				return 0;
			case 2:
				strcpy(player.display, "自由搏击");
				return 0;
			case 3:
				strcpy(player.display, "连击");
				return 0;
			case 0:
				return 1;
			default:
				cout << "输入错误\n";
				break;
			}
		}
}
void cs()
{
	player.health = 100 + abs(player.name[rand() % strlen(player.name) + 1]) / 3;
	player.xp = 0;
	player.max_health = player.health;
	player.attack = 100;
	player.defense = 50;
	player.level = 1;
	player.max_xp = 150;
	player.money = 8110;
	strcpy(player.player_plant[1].name, "asdasd");
	player.player_plant[1].finish = true;
	player.player_plant[1].money = 100;
	player.p_pet[1] = Pet[1];
	player.p_pet[1].xp = 1000000;
	player.p_pet[1].health -= 10;
	for (int i = 1; i <= strclo(c_std); i++)
	{
		c_std[i].num++;
	}
	player.sx();
	write();
	Pause();
	system("cls");
}
void zdy_player()
{
	sprint("玩家，请输入您的名字\n");
	cin >> player.name;
a:
	sprint("请选择你的角色:\n\n1.元素法师     2.狂战士     3.驯兽师");
	in(bb);
	int cccc;
	switch (bb)
	{
	case 1:
		sprint("\n玩家，请选择您的技能：\n(1.冰封     2.电击     3.灼烧)请选择：0.退出\n");
		cccc = displayxz(1);
		if (cccc == 1)
			goto a;
		break;
	case 2:
		sprint("\n玩家，请选择您的技能：\n(1.狂暴     2.自由搏击     3.连击)请选择：0.退出\n");
		cccc = displayxz(2);
		if (cccc == 1)
			goto a;
		break;
	case 3:
		sprint("\n未设置\n");
		goto a;
		break;
	default:
		cout << "\n输入错误\n";
		goto a;
	}
	if (strcmp(player.name, "jimmy96b") == 0)
	{
		cs();
		return;
	}
	player.health = 100 + abs(player.name[rand() % strlen(player.name) + 1]) / 3;
	player.xp = 0;
	player.max_health = player.health;
	player.attack = 100;
	player.defense = 50;
	player.level = 1;
	player.max_xp = 150;
	player.money = 80;
	player.sx();
	write();
	Pause();
	system("cls");
}
void banquan()
{
	system("cls");
	sprint("此游戏由");
	DelayPrint("【水墨工作室】");
	printf("创作\n\n");
	DelayPrint("未经允许，不得转载\n");
	Pause();
	system("cls");
}
/*预计编写：(更新完空着)
1.初步添加[物品]及[道具]功能---
2.完善其存档及获得途径---
3.添加合成---


*/
void about_us()
{
	system("cls");
	sprint("----\n此游戏为作者8.0版：\n相对于上版本，代码进行了一些改进，变得更加容易明白\n1.添加[游戏商店]中的一些怪物2.添加[物品]及[道具]功能(No!)\n若有不足之处，请玩家大大们原谅\n-----");
	Pause();
	system("cls");
}
int fight()
{
	// 1战斗胜利 0战斗失败 2其他
	fighting = true;
	can_use_display = true;								   // 玩家可使用技能
	int display_time = 0;								   // 技能使用次数
	bool guai_can_attack = true, player_can_attack = true; // 玩家及怪物可攻击
	//	player_can_attack=false;
	//	guai_can_attack=false;
	long long health = guai->health;
fnn:
	if (player_can_attack == false)
	{
		cout << "\n您无法操作\n";
		player_can_attack = true;
	}
	else
	{
		sprint("\n==========================================================\n");
		printf("[%s]你要如何战胜%s?\n", player.name, guai->name);
		sprint("1.普通攻击(不建议)     2.道具     3.查看人物此时以及对手此时属性\n\n4.宠物     5.逃跑(因该是怂了)\n");
		sprint("==========================================================\n");
		in(bb);
		switch (bb)
		{
		case 1:
		{
			int shanghai;
			shanghai = player.attack + rand() % 10 + 1 - guai->defense * guai->level / 2;
			if (shanghai < 0)
				shanghai = 1;
			health -= shanghai;
			if (health < 0)
				health = 0;
			printf("你发动了攻击,敌方受到%d点伤害\n\n敌方还剩%lld点血\n", shanghai, health);
			write();
			Pause();
			break;
		}
		case 2:
		{
			sprint("\n本功能尚未实现\n");
			goto fnn;
			break;
		}
		case 3:
		{
			SetConsoleTextColor(14);
			printf("------您的属性：------");
			SetConsoleTextColor(15);
			player.sx();
			SetConsoleTextColor(11);
			printf("------对方属性：------");
			SetConsoleTextColor(15);
			guai->sx();
			puts("");
			goto fnn;
			break;
		}
		case 4:
		{
			sprint("\n本功能尚未实现\n");
			goto fnn;
			break;
		}
		case 5:
		{
			int go = SuiJi(1, 10);
			if (go <= 4)
			{
				cout << "逃跑成功!\n";
				write();
				return 2;
			}
			else
			{
				cout << "逃跑失败(原因:你太怂了)\n";

				goto fnn;
			}
			break;
		}
		default:
			cout << "输入错误\n";
			goto fnn;
			break;
		}
		Sleep(100);
	}
	if (health <= 0)
	{
		system("cls");
		SetConsoleTextColor(10);
		printf("您战胜了%s\n\n", guai->name);
		printf("您获得了%lld*%lld=%lld金币\n您", guai->money, guai->level, guai->money * guai->level);
		bool cw = false; // 是否有宠物：初始默认无
		if (strpet(player.p_pet) > 0)
			cout << "以及您的宠物", cw = true;
		printf("获得了%lld*%lld=%lld点经验\n", guai->xp, guai->level, guai->xp * guai->level);
		player.xp += guai->xp * guai->level;
		player.money += guai->money * guai->level;
		if (cw == true)
			for (int i = 1; i <= strpet(player.p_pet); i++)
				player.p_pet[i].xp += guai->xp * guai->level;
		SetConsoleTextColor(15);
		Pause();
		fighting = false;
		guai->level++;
		write();
		return 1;
	}
	else
	{
		if (guai_can_attack == false)
		{
			cout << "\n对方无法操作\n";
			guai_can_attack = true;
		}
		else
		{
			// 怪物反击时有20%触发技能
			int shanghai = guai->attack * guai->level + rand() % 10 + 1 - player.defense / 2;
			if (shanghai < 0)
				shanghai = 1;
			player.health -= shanghai;
			if (player.health < 0)
				player.health = 0;
			printf("[%s]", guai->name);
			sprint("发起了反击,你受到");
			printf("%d", shanghai);
			sprint("点伤害,还剩");
			printf("%lld", player.health);
			sprint("点血量\n");
			write();
			Pause();
		}
	}
	if (!player.alive())
	{
		system("cls");
		write();
		SetConsoleTextColor(12);
		printf("战死!,金币掉落10%\n\n复活时血量为最高血量的50%\n\n");
		SetConsoleTextColor(15);
		player.money *= 0.9;
		if (player.money < 0)
			player.money = 0;
		if (player.max_health <= 140)
		{
			sprint("但由于您的生命值太低，直接恢复至最大生命\n");
			player.health = player.max_health;
		}
		else
			player.health = player.max_health / 2;
		Pause();
		fighting = false;
		return 0;
	}
	else
		goto fnn;
}
//....................
//-----------
void join()
{
	SetConsoleCursor(40, 10);
	sprint("===============================");
	SetConsoleCursor(40, 15);
	sprint("================================");
	SetConsoleCursor(40, 11);
	DelayPrint("此游戏为【水墨工作室】制作");
	SetConsoleCursor(40, 14);
	DelayPrint("未经允许,不得转载");
	Sleep(800);
	system("cls");
}
/*****/
void chou()
{
	char s[5] = " orz";
	sprint("\n[抽奖规则]:\n");
	sprint("ooo 300金币\n");
	sprint("rrr 150金币\n");
	sprint("zzz 100金币\n");
	sprint("有两个字母相同 110金币\n");
	sprint("【orz】--->800金币\n");
	sprint("其它：10金币\n");
cnn:
	sprint("\n-=-=-=-(^oo^)\n");
	sprint("您是否愿意花100金币进行抽奖？1.yes/2.no\n");
	sprint("-=-=-=-=-=-=-\n");
	in(bb);
	if (bb == 1)
		if (player.money >= 100)
		{
			player.money -= 100;
			int a, b, c;
			system("cls");
			for (float i = 1; i >= 0; i -= 0.01)
			{
				printf("1.[正在加载]%.2f", i);
				if (i - 0.01 > 0)
					cout << "\r";
				Sleep(1);
			}
			a = rand() % 3 + 1;
			puts("");
			for (float i = 1; i >= 0; i -= 0.01)
			{
				printf("2.[正在加载]%.2f\r", i);
				if (i - 0.01 > 0)
					cout << "\r";
				Sleep(1);
			}
			b = rand() % 3 + 1;
			puts("");
			for (float i = 1; i >= 0; i -= 0.01)
			{
				printf("3.[正在加载]%.2f\r", i);
				if (i - 0.01 > 0)
					cout << "\r";
				Sleep(1);
			}
			c = rand() % 3 + 1;
			puts("");
			sprint("您的抽奖结果是:【");
			printf("%c,%c,%c", s[a], s[b], s[c]);
			sprint("】\n");
			int p;
			if (s[a] == s[b] && s[b] == s[c])
			{
				if (s[a] == 'o')
					p = 300;
				if (s[a] == 'r')
					p = 150;
				if (s[a] == 'z')
					p = 130;
			}
			else if (s[a] == 'o' && s[b] == 'r' && s[c] == 'z')
				p = 800;
			else if (s[a] == s[b] || s[a] == s[c] || s[c] == s[b])
				p = 110;
			else
				p = 10;
			printf("\n获得%d金币", p);
			player.money += p;
		}
		else
		{
			sprint("\n金币不够\n");
		}
}
void house()
{
hnn:
	sprint("\n===============================\n");
	sprint("【探险家的小屋】:\n1.装备售出    2.抽奖     3.与房子的主人对话\n\n0.退出  (请选择:)\n");
	sprint("===============================\n");
	in(bb);
	switch (bb)
	{
	case 1:
	{
	mai1:
		int n = jiazaic();
		if (n == 0)
		{
			sprint("您没有可用装备...\n");
			goto hnn;
		}
		sprint("您的可用装备:\n");
		for (int i = 1; i <= n; i++)
		{
			printf("%d.[%s]    ", i, canin[i].name);
			if (i % 3 == 0 && i + 1 <= n)
				puts("");
		}
		sprint("0.退出\n");
	salec:
		in(bb);
		if (bb < 0 || bb > n)
		{
			cout << "choose error\n";
			goto salec;
		}
		else if (bb == 0)
			goto hnn;
		else
			sale(canin[bb]);
		goto mai1;
		break;
	}
	case 2:
	{
		chou();
		break;
	}
	case 3:
	{
		if (wor.hou_o == false)
		{
			wor.hou_o = true;
			DelayPrint("亲爱的");
			printf("[%s]\n\n", player.name);
			DelayPrint("你是第一次来到这里吧！\n给你一些装备，去冒险吧！\n");
			sprint("\n[提示]:您获得了[破旧的小刀]*1[破木盾]*1\n\n");
			number_of_cloth("破旧的小刀", 1);
			number_of_cloth("破木盾", 1);
			write();
		}
		else
		{
			DelayPrint("亲爱的");
			printf("[%s]\n", player.name);
			DelayPrint("你又来了！随便看看吧\n");
		}
		Pause();
		goto hnn;
		break;
	}
	case 0:
		return;
	default:
	{
		cout << "\n输入错误！\n";
		goto hnn;
		break;
	}
	}
}
void game_sell()
{
	Monster cho;
	cho.attack = cho.defense = cho.max_health = cho.health = cho.money = cho.xp = 1e9;
	cho.level = 1;
gnn0:
	sprint("\n欢迎来到游戏专卖店!\n	这里有应有尽有的游戏供您玩耍\n");
	sprint("\n~~~~~~~~~~~~~~~~~~~~\n");
	sprint("1.超级玛丽     2.泰拉瑞亚     3.沙盒2\n\n4.Minecraft     5.物理沙盘     6.元气骑士\n\n0.退出(请选择:)\n");
	sprint("~~~~~~~~~~~~~~~~~~~~\n");
gnn:
	in(bb);
	if (bb < 0 || bb > 6)
	{
		cout << "\n输入错误！\n";
		goto gnn;
	}
	if (bb == 0)
		return;
	int t;
	t = rand() % 3 + 1;
	switch (t)
	{
	case 1:
		DelayPrint("\n在一阵耀眼的光芒下,你遇见了:");
		break;
	case 2:
		DelayPrint("\n在天旋地转的眩晕下,你遇见了:");
		break;
	case 3:
		DelayPrint("\n只听'轰'的一声,你遇见了:");
		break;
	}
	int i;
	if (bb == 1)
	{
		t = SuiJi(1, 2);
		if (t == 1)
			guai = &ml;
		else
			guai = &mg;
	}
	else if (bb == 2)
	{
		t = SuiJi(1, 2);
		if (t == 1)
			guai = &king;
		else
			guai = &krous_eye;
	}
	else if (bb == 3)
	{
		t = SuiJi(1, 10);
		if (t < 3)
		{
			DelayPrint("一阵强烈的妖风吹来，你全身一抖...\n");
			guai = &God;
		}
		else
			guai = &Human;
	}
	else if (bb == 4)
	{
		t = SuiJi(1, 10);
		if (t < 4)
			guai = &pig;
		else if (t < 7)
			guai = &sheep;
		else
			guai = &steve;
	}
	else
		guai = &cho;
	guai->sx();
funn:
	printf("[%s]向你发出了挑战,是否接受？？	(1.yes,2.no)\n", guai->name);
	in(bb);
	if (bb == 2)
		goto gnn0;
	if (bb != 1)
	{
		cout << "输入错误!\n";
		goto funn;
	}
	fight(); // 战斗函数
}
void magic_forest()
{
	sprint("\nWelcome to the'Magic Forest'\n");
mnn:
	sprint("======================================\n");
	sprint("choose:1.观赏风景     2.静坐     3.随便看看\n\n0.退出\n");
	sprint("======================================\n");
	in(bb);
	switch (bb)
	{
	case 1:
	{
		int sj = SuiJi(1, 100);
		if (sj <= 70)
		{
			DelayPrint("\n啊~风景真好");
			sprint("	经验+2;\n");
			player.xp += 2;
			goto mnn;
		}
		else
		{
			sprint("\n你看见了[森林女王]，她朝你走来:\n\n");
			DelayPrint("是谁那么大胆?敢冒犯此地！\n");
			DelayPrint("	原来是亲爱的");
			printf("[%s]", player.name);
			DelayPrint("呀!\n");
		mqnn:
			sprint("===================================\n");
			sprint("你要做什么:\n1.对话     2.战斗     3.(null)\n\n0.退出\n");
			sprint("===================================\n");
			in(bb);
			switch (bb)
			{
			case 1:
				break;
			case 2:
			{
				sprint("[森林女王]接受了你的挑战!\n\n");
				guai = &slnw;
				int sao = fight();
				if (sao == 1)
				{
					sprint("\n[森林女王]:");
					DelayPrint("\n都多久没有人能打败我啦,你胜利了,这些是给你的奖励：\n");
				}
				else if (sao == 0)
				{
					sprint("\n[森林女王]:");
					DelayPrint("\n要继续加油呀!\n");
				}
				break;
			}
			case 3:
				break;
			case 0:
				goto mnn;
			default:
				cout << "输入错误\n";
				goto mqnn;
			}
		}
		break;
	}
	case 2:
	{
		int id;
		sprint("你只是静静地坐着...\n");
		int zuo = SuiJi(1, 100);
		if (zuo >= 60)
		{
			sprint("你不知不觉地睡着了\n\n");
			Pause();
			sprint("在梦的幻境中,你遇见了:");
			int mon = SuiJi(1, 3);
			switch (mon)
			{
			case 1:
				guai = &mzsw;
				break;
			case 2:
				guai = &smlr;
				break;
			case 3:
				guai = &ojld;
				break;
			}
		fuck:
			SetConsoleTextColor(14);
			printf("[%s]", guai->name);
			SetConsoleTextColor(15);
			sprint("\nta向你发起了挑战,是否接受(1.yes,2.no)\n");
			guai->sx();
			int bbb;
			in(bbb);
			if (bbb == 2)
				goto mnn;
			if (bbb != 1)
			{
				cout << "输入错误\n";
				goto fuck;
			}
			sprint("ta接受了你的挑战！\n");
			int ans = fight();
			if (ans == 1)
			{
				DelayPrint("\n你醒来了\n");
			}
			else
			{
				DelayPrint("\n挑战失败,你醒了\n");
			}
			goto mnn;
		}
		else
		{
			sprint("		你好像感悟到了什么,[经验]+4\n");
			player.xp += 4;
			Pause();
			goto mnn;
		}
		break;
	}
	case 3:
		break;
	case 0:
		return;
	default:
		cout << "输入错误!!!\n";
		goto mnn;
		break;
	}
}
/*****/
void mov()
{
	sprint("\n-----------------------------------------------\n");
	SetConsoleTextColor(11);
	sprint("1.探险家的小屋    2.游戏专卖店    3.祈愿求签\n\n");
	sprint("4.魔法森林    5.冰雪平原    6.(NULL)\n\n");
	sprint("7.深海古战场    8.云之顶峰    0.退出\n\n请选择：\n");
	SetConsoleTextColor(15);
	sprint("-----------------------------------------------\n");
	in(bb);
	switch (bb)
	{
	case 1:
		house();
		break;
	case 2:
		game_sell();
		break;
	case 3:
		break;
	case 4:
		magic_forest();
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 0:
		break;
	default:
		cout << "输入错误\n";
		break;
	}
}
void daoju()
{
	sprint("\n++++++++++++++++++++++++++++++++++++\n");
	SetConsoleTextColor(14);
	sprint("选择类型：\n1.治愈类     2.辅助类     3.buff类     0.退出\n");
	SetConsoleTextColor(15);
	sprint("++++++++++++++++++++++++++++++++++++\n");
	in(bb);
	switch (bb)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 0:
		break;
	default:
		cout << "\n输入错误";
		getch();
		cout << "\r";
		break;
	}
}
void shop()
{
buy:
	sprint("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	sprint("【选择类别】\n");
	sprint("1.宠物类     2.人物类     3.道具类     4.装备类\n\n0.退出\n");
	sprint("~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	in(bb);
	switch (bb)
	{
	case 1:
	{
	bp:
		int l = strpet(Pet);
		printf("\n-----\n");
		for (i = 1; i <= l; i++)
		// 循环打出宠物名，添加选项
		{
			cout << i << ":   " << Pet[i].name << endl;
		}
		cout << "0.退出     请选择：\n";
		printf("-----\n");
	buy_pet:
		in(bb); // 选择：输出宠物属性，是否购买
		if (bb == 0)
			goto buy;
		if (bb < 1 || bb > l)
		{
			cout << "\n输入错误";
			goto buy_pet;
		}
		Pet[bb].sx();
		cout << "\n是否购买？ 1.yes/2.no\n";
		int cc;
		in(cc);
		if (cc == 1)
		{

			if (strpet(player.p_pet) == -1)
			{
				cout << "\n抱歉，您的宠物已达到上限，无法进行购买..\n";
				goto buy;
			}
			else
				for (i = 1; i <= strpet(player.p_pet); i++)
				{
					if (strcmp(player.p_pet[i].name, Pet[bb].name) == 0)
					{
						cout << "\n您已拥有此宠物!\n";
						goto buy;
					}
				}
			if (player.money < Pet[bb].money)
			{
				cout << "\n抱歉，您钱币不足，无法进行购买..\n";
				goto buy;
			}
			else
			{
				player.money -= Pet[bb].money;
				player.p_pet[strpet(player.p_pet) + 1] = Pet[bb];
				cout << "\n成功获得宠物[" << Pet[bb].name << "]\n";
				goto buy;
			}
		}
		else
			goto bp;
		// 【不能购买原因�毘栉锫�了or钱不够
	}
	case 2:
	{
		while (1)
		{
			printf("\n(1)人物技能     (2)其他     0.返回上一级\n");
			in(bb);
			switch (bb)
			{
			case 1:
				break;
			case 2:
				break;
			case 0:
				goto buy;
			default:
				cout << "\n输入错误\n";
				break;
			}
		}
		break;
	}
	case 3:
		break;
	case 4:
	{
	clo:
		int l = strclo(c_std);
		printf("可供购买装备:\n");
		for (int i = 1; i <= l; i++)
		{
			printf("%d.(%s)     ", i, c_std[i].name);
			if (i % 3 == 0 && i + 1 <= l)
				puts("");
		}
		printf("0.退出\n");
	inc:
		in(bb);
		if (bb == 0)
			goto buy;
		if (bb < 0 || bb > l)
		{
			cout << "choose error\n";
			goto inc;
		}
		c_std[bb].sx();
		printf("是否选择购买？1.yes 其他键.no\n");
		int cc;
		in(cc);
		if (cc != 1)
			goto clo;
		if (player.money >= c_std[bb].money)
		{
			player.money -= c_std[bb].money;
			number_of_cloth(c_std[bb].name, 1);
			sprint("\n---购买成功---\n");
			goto buy;
		}
		else
		{
			cout << "对不起，您的金币数量不足...\n";
			goto clo;
		}
	}
	case 0:
		return;
	default:
		cout << "\n输入错误\n";
		goto buy;
		break;
	}
}
void plant()
{
	sprint("\n==========================\n");
	int l = strpla(player.player_plant);
	for (int i = 1; i <= l; i++)
	{
		sprint("\n----------------------------\n");
		printf("第【%d】条任务:%s\n", i, player.player_plant[i].name);
		sprint("\n是否完成：");
		if (player.player_plant[i].finish == true)
			cout << "Yes!\n";
		else
			cout << "No!\n";
		cout << "\n奖励：" << player.player_plant[i].money << endl;
		if (player.player_plant[i].get == false)
			cout << "未领取\n";
		else
			cout << "已领取\n";
		sprint("----------------------------\n");
	}
	sprint("==========================\n");
	// 循环输出任务;
	cout << "请选择：(0.退出)\n";
pc:
	in(bb);
	if (bb < 0 || bb > l)
	{
		cout << "\n输入错误！！\n";
		goto pc;
	}
	else if (bb == 0)
		return;
	else
	{
		if (player.player_plant[bb].finish == false)
		{
			cout << "\n此任务未完成\n";
			goto pc;
		}
		if (player.player_plant[bb].get == false)
		{
			cout << "\n领取成功！\n";
			player.player_plant[bb].get = true;
			player.money += player.player_plant[bb].money;
		}
		else
		{
			cout << "\n您已领取！\n";
			goto pc;
		}
	}
	// 选择领取奖励
	// 完成即可领取
}
void about_pet()
{
sp:
	int l = strpet(player.p_pet);
	if (l == 0)
	{
		cout << "\n您并没有宠物..\n";
		return;
	}
	sprint("\n~_~_~_~_~_~_~_~_~_~_~_~\n");
	for (int i = 1; i <= l; i++)
	{
		cout << i << ": " << player.p_pet[i].name << "     ";
		if (i % 3 == 0 && i + 1 <= l)
			puts("\n");
	}
	cout << "\n请选择(0.退出)\n";
	sprint("\n~_~_~_~_~_~_~_~_~_~_~_~\n");
apc:
	in(bb);
	if (bb == 0)
		return;
	if (bb < 0 || bb > l)
	{
		cout << "输入错误\n";
		goto apc;
	}
pnn:
	sprint("\n----your pet----(^_^)\n");
	printf("【%s】:\n", player.p_pet[bb].name);
	sprint("1.恢复     2.升级     3.装备\n\n4.属性     5.放生     0.返回上一级\n");
	sprint("---------------------\n");
	int cc;
pnn1:
	in(cc);
	switch (cc)
	{
	case 1:
	{
		if (player.p_pet[bb].health == player.p_pet[bb].max_health)
		{
			cout << "\n[系统]:宠物'完好无损',无需恢复,自动返回上级\n";
			goto pnn;
		}
	pnn2:
		cout << "\n[系统]:是否花费100金币恢复该宠物？1.yes/2.no\n       (按下按键即选择)\n";
		int x = getch() - '0';
		if (x != 1 && x != 2)
		{
			cout << "choose erro\n";
			goto pnn2;
		}
		if (x == 2)
		{
			goto pnn1;
		}
		if (x == 1)
		{
			if (player.money < 100)
			{
				cout << "\n钱不够\n";
				goto pnn1;
			}
			else
			{
				player.money -= 100;
				player.p_pet[bb].health = player.p_pet[bb].max_health;
				cout << "\n您为宠物【氪金】成功\n";
				goto pnn;
			}
		}
		break;
	}
	case 2:
	{
		printf("该宠物拥有经验数：%lld\n该宠物升级需要经验数:%lld\n宠物等级：%lld\n", player.p_pet[bb].xp, player.p_pet[bb].max_xp, player.p_pet[bb].level);
		sprint("是否升级？1.yes/2.no\n");
		int cc;
	pnn3:
		in(cc);
		if (cc != 1 && cc != 2)
		{
			cout << "\n输入错误\n";
			goto pnn3;
		}
		else if (cc == 1)
		{
			if (player.p_pet[bb].xp < player.p_pet[bb].max_xp)
			{
				cout << "\n经验不足\n";
				goto pnn;
			}
			else
			{
				cout << "\n升级成功\n";
				player.p_pet[bb].level_up();
				player.p_pet[bb].health = player.p_pet[bb].max_health;
				goto pnn;
			}
		}
		else
			goto pnn;
		break;
	}
	case 3:
	{
		break;
	}
	case 4:
	{
		player.p_pet[bb].sx();
		break;
	}
	case 5:
	{
	pnn_:
		sprint("\n是否放生您的宠物(请慎重!)1.yes/2.no\n");
		int dd;
		in(dd);
		if (dd != 1 && dd != 2)
		{
			cout << "\n输入错误！！\n";
			goto pnn_;
		}
		if (dd == 1)
		{
			swap(player.p_pet[strpet(player.p_pet)], player.p_pet[bb]);
			player.p_pet[strpet(player.p_pet)] = empity;
			sprint("[系统]:该宠物放生成功");
		}
		goto sp;
		break;
	}
	case 0:
	{
		goto sp;
		break;
	}
	default:
	{
		cout << "\n输入错误\n";
		goto pnn1;
		break;
	}
	}
}
void change_cloths(Cloths &ac)
{
	if (strcmp(ac.name, "\0") == 0)
	{
		sprint("\n此栏并没有任何装备\n	请选择你要替换的装备:\n");
	}
	else
	{
		ac.sx();
		sprint("您要将[");
		printf("%s", ac.name);
		sprint("]替换成什么:\n");
	}
	int sum = jiazaic();
	if (sum == 0)
	{
		cout << "\n您一件装备也没有\n";
		printf("是否脱下此装备？？？1.yes 其它.no\n");
		in(bb);
		if (bb == 1)
		{
			player.attack -= ac.attack_up;
			player.defense -= ac.defense_up;
			for (int i = 1; i <= strclo(c_std); i++)
			{
				if (strcmp(c_std[i].name, ac.name) == 0)
				{
					c_std[i].num++;
				}
			}
			ac = _empity;
			printf("成功脱下\n");
		}
		Pause();
		puts("\n");
		return;
	}
	SetConsoleTextColor(13);
	printf("\n================================\n");
	for (int i = 1; i <= sum; i++)
	{
		printf("%d.[%s] ", i, canin[i].name);
		if (i % 3 == 0 && i + 1 != sum)
			puts("");
	}
	printf("\n请选择:999.脱下此装备     (0.退出)\n");
	printf("================================\n");
	SetConsoleTextColor(15);
ccnn:
	in(bb);
	if ((bb < 0 || bb > sum) && bb != 999)
	{
		cout << "\nchoose error\n";
		goto ccnn;
	}
	if (bb == 0)
	{
		return;
	}
	else if (bb != 999)
	{
		player.attack -= ac.attack_up;
		player.defense -= ac.defense_up;
		player.attack += canin[bb].attack_up;
		player.defense += canin[bb].defense_up;
		for (int i = 1; i <= strclo(c_std); i++)
		{
			if (strcmp(c_std[i].name, ac.name) == 0)
			{
				c_std[i].num++;
			}
			if (strcmp(c_std[i].name, canin[bb].name) == 0)
			{
				c_std[i].num--;
			}
		}
		ac = canin[bb];
	}
	else
	{
		player.attack -= ac.attack_up;
		player.defense -= ac.defense_up;
		for (int i = 1; i <= strclo(c_std); i++)
		{
			if (strcmp(c_std[i].name, ac.name) == 0)
			{
				c_std[i].num++;
			}
		}
		ac = _empity;
	}
}
void myself1()
{
	player.sx();
ms1:
	sprint("---------------\n");
	sprint("你要做什么:\n1.切换装备     0.退出\n");
	sprint("---------------\n");
	Cloths now;
	int jjj;
	in(bb);
	switch (bb)
	{
	case 1:
	{
	zbnn:
		printf("\n1.头部:[%s]	2.身体:[%s]\n\n3.腿部:[%s]	4.脚部:[%s]\n\n5.手部[%s]	6.肩膀[%s]\n0.退出\n", player.slot.head, player.slot.body, player.slot.leg, player.slot.foot, player.fight.hand, player.fight.arm);
		in(bb);
		switch (bb)
		{
		case 1:
			change_cloths(player.slot.head);
			break;
		case 2:
			change_cloths(player.slot.body);
			break;
		case 3:
			change_cloths(player.slot.leg);
			break;
		case 4:
			change_cloths(player.slot.foot);
			break;
		case 5:
			change_cloths(player.fight.hand);
			break;
		case 6:
			change_cloths(player.fight.arm);
			break;
		case 0:
			goto ms1;
		default:
			cout << "choose error!\n";
			goto zbnn;
			break;
		}
		break;
	}
	case 0:
		return;
	default:
		sprint("输入错误\n");
		goto ms1;
	}
	goto zbnn;
}
void myself()
{
msn:
	sprint("-------------------------------------\n");
	printf("[%s]你要做什么?\n", player.name);
	sprint("1.查看基本属性     2.升级     3.恢复\n\n0.退出\n");
	sprint("-------------------------------------\n");
	in(bb);
	switch (bb)
	{
	case 1:
		myself1();
		break;
	case 2:
	{
		printf("您拥有经验:[%lld]\n升级所需经验:[%lld]\n您的等级:[%lld]\n是否升级?(1.yes,2.no)", player.xp, player.max_xp, player.level);
	shit:
		int bbbb;
		in(bbbb);
		if (bbbb == 2)
			goto msn;
		if (bbbb != 1)
		{
			cout << "输入错误!\n";
			goto shit;
		}
		if (player.xp < player.max_xp)
		{
			cout << "经验不足\n";
			goto msn;
		}
		else
		{
			player.level_up();
			player.health = player.max_health;
			cout << "\n升级成功！\n";
		}
		goto msn;
		break;
	}
	case 3:
	{
		if (player.health == player.max_health)
		{
			sprint("您血量已满,无需恢复\n");
			goto msn;
		}
		int huafei = (player.max_health - player.health) / 2;
		printf("\n您的生命[%lld]\n生命上限[%lld]\n恢复至上限需要[%lld]金币\n", player.health, player.max_health, huafei);
		printf("\n请输入您想恢复的生命(0退出):");
		int xx;
		in(xx);
		if (xx == 0)
			goto msn;
		if (xx > player.max_health - player.health)
		{
			cout << "这个值已经超过最高值!自动回满\n";
		}
		else
		{
			huafei = xx / 2;
		}
		Pause();
		if (player.money < huafei)
		{
			cout << "\n金币不足       \n";
			goto msn;
		}
		else
		{
			player.health += xx;
			player.money -= huafei;
			cout << "恢复成功         \r";
			goto msn;
		}
		break;
	}
	case 0:
		return;
	default:
		cout << "choose error\n";
		goto msn;
		break;
	}
}
//-----------
void news()
{
	SYSTEMTIME sys = wor.last;
	SYSTEMTIME sys2 = wor.now;
	GetLocalTime(&wor.now);
	printf("\n您现在时间:%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d\n\n\n", sys2.wYear, sys2.wMonth, sys2.wDay, sys2.wHour, sys2.wMinute, sys2.wSecond, sys2.wMilliseconds, sys2.wDayOfWeek);
	if (sys.wDay != sys2.wDay)
	{
		printf("\n您获得[新的一天]奖励:1000金币，100经验,自动更新登录日期\n");
		player.money += 1000;
		player.xp += 100;
		wor.last = wor.now;
		write();
		Pause();
	}
	else
		printf("\n您没有登录奖励\n");
	printf("\n-----\n");
	printf("其它功能敬请期待...\n");
	printf("-----\n");
	Pause();
}
void start()
{
	cout << "【" << player.name << "】要干什么？";
	sprint("\n================================\n");
	SetConsoleTextColor(13);
	sprint("1.移动    2.道具    3.查看个人属性    4.背包\n\n");
	sprint("5.宠物    6.商店    7.神话专区    8.系统消息\n\n");
	sprint("9.任务    10.功能\n\n");
	sprint("11.版本更新    12.游戏版权    13.版本介绍    0.退出游戏\n");
	SetConsoleTextColor(15);
	sprint("请选择:\n");
	sprint("================================\n");
	in(bb);
	switch (bb)
	{
	case 1:
		mov();
		break;
	case 2:
		daoju();
		break;
	case 3:
		myself();
		break;
	case 4:
		break;
	case 5:
		about_pet();
		break;
	case 6:
		shop();
		break;
	case 7:
		break;
	case 8:
		news();
		break;
	case 9:
		plant();
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		banquan();
		break;
	case 13:
		about_us();
		break;
	case 0:
		out();
		break;
	default:
		cout << "输入错误\n";
		break;
	}
}
//********************************
int main()
{
	system("title 无尽の冒险");
	SetWindowPosition(0, 0);
	system("mode con lines=60 cols=188");
	join(); // 146
	read(); // 读取存档
	while (1)
	{
		start();
	}
	return 0;
}
//***********主函数***************
//.................==============================
void SetConsoleTextColor(long long a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
}
void DelayPrint(char *p)
{
	while (1)
	{
		if (*p != 0)
		{
			printf("%c", *p++);
			Sleep(100);
		}
		else
			break;
	}
}
void SetConsoleCursor(int x, int y)
{
	COORD p;
	p.X = x - 1;
	p.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
void SetWindowPosition(int x, int y)
{
	HWND hwnd;
	hwnd = GetForegroundWindow();
	MoveWindow(hwnd, x, y, 0, 0, true);
}
void in(int &a)
{
	a = 0;
	bool c = false;
	char s;
	while (1)
	{
		s = getchar();
		if (s >= '0' && s <= '9')
			a = a * 10 + (s - '0'), c = true;
		if (s == '\n' && c == true)
			return;
	}
}
void Pause()
{
	DelayPrint("");
	printf("按任意键继续喔~");
	getch();
	cout << "\r";
}
void sprint(char *p)
{
	while (1)
	{
		if (!*p)
			break;
		SetConsoleTextColor(15);
		if (*p == '-' || *p == '=' || *p == '~' || *p == '_' || *p == '+')
			SetConsoleTextColor(14);
		else if (*p >= 'a' && *p <= 'z' || *p >= 'A' && *p <= 'Z')
			SetConsoleTextColor(11);
		else if (*p >= '0' && *p <= '9')
			SetConsoleTextColor(6);
		else if (*p == '(' || *p == ')' || *p == '[' || *p == ']' || *p == '【' || *p == '】')
			SetConsoleTextColor(12);
		else if (*p < 0)
			SetConsoleTextColor(11);
		printf("%c", *p++);
		SetConsoleTextColor(15);
	}
}
int SuiJi(int a, int b)
{
	// 随机函数，从数a~b之间随机取数
	return rand() % b + a;
}
void write()
{
	ofstream w;
	ofstream outfile;
	w.open("无尽の冒险（请勿删除否则导致游戏崩溃）.egame");
	w.write((const char *)(&player), sizeof(player));
	w.write((const char *)(&wor), sizeof(wor));
	w.write((const char *)(&c_std), sizeof(c_std));
	w.write((const char *)(&monster), sizeof(monster));
	w.close();
}
void read()
{
	ifstream r;
	r.open("无尽の冒险（请勿删除否则导致游戏崩溃）.egame");
	if (!r.is_open())
	{
		//          自定义人物
		zdy_player();
		return;
	}
	r.read((char *)(&player), sizeof(player));
	r.read((char *)(&wor), sizeof(wor));
	r.read((char *)(&c_std), sizeof(c_std));
	r.read((char *)(&monster), sizeof(monster));
	r.close();
}
void out()
{
	if (MessageBox(NULL, "\1是否退出\1", "无尽の冒险", MB_ICONQUESTION | MB_YESNO) == IDNO)
		return;
	write();
	DelayPrint("感谢各位玩家大大的支持！拜拜~");
	exit(0);
}
//...配置 ..........==============================
