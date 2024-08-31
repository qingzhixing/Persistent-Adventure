#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <locale>
using std::endl;
using std::locale;
using std::wcin;
using std::wcout;
void SetConsoleTextColor(long long a);
void DelayPrint(wchar_t *p);
void Pause();
void SetConsoleCursor(int x, int y);
void SetWindowPosition(int x, int y);
void FastReadInteger(int &a);
void ReadSave();
void WriteSave();
void Exit();
void GameColoredPrint(const wchar_t p[]);
int GenerateRandomNumber(int a, int b);
/*************************************************/
struct Display
{
	wchar_t name[50];
	long long attack;
	long long defense;
	long long level;
	long long max_xp;
	bool active; // 是否为主动技能
}; // 测试阶段，代码不知道怎么实现
struct Monster
{
	wchar_t name[30];
	wchar_t abilityName[20];
	long long health;
	long long max_health;
	long long attack;
	long long defense;
	long long level;
	wchar_t fang[30];
	wchar_t gong[30];
	long long money;
	long long xp;
	void DisplayInfo()
	{
		wprintf(L"\n怪物名字：%s\n", name);
		wprintf(L"怪物技能：%s\n", abilityName);
		wprintf(L"生命：%lld\n", health);
		wprintf(L"攻击力：%lld*%lld=*%lld\n", attack, level, attack * level);
		wprintf(L"防御力：%lld*%lld=*%lld\n", defense, level, defense * level);
		wprintf(L"等级：%lld\n", level);
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
struct Pet
{
	wchar_t name[30];
	wchar_t display1[20];
	wchar_t display2[20];
	long long health;
	long long max_health;
	long long xp;
	long long max_xp;
	long long attack;
	long long defense;
	long long level;
	wchar_t fang[20];
	wchar_t gong[20];
	long long money;
	long long displayd;
	void sx()
	{
		wprintf(L"\n宠物名字：%s\n", name);
		wprintf(L"宠物技能：(%s,%s)\n", display1, display2);
		wprintf(L"生命：%lld\n", health);
		wprintf(L"最大生命：%lld\n", max_health);
		wprintf(L"攻击力：%lld\n", attack);
		wprintf(L"防御力：%lld\n", defense);
		wprintf(L"等级：%lld\n", level);
		wprintf(L"经验:%lld\n升级所需经验：%lld\n", xp, max_xp);
	}
	void level_up()
	{
		if (xp >= max_xp)
		{
			displayd += xp / max_xp;
			wprintf(L"\n你的宠物升级啦！！\n");
			wprintf(L"等级：%lld==>%lld\n", level, level + xp / max_xp);
			level += xp / max_xp;
			wprintf(L"攻击力：%lld==>%lld\n", attack, attack * 1.5);
			attack *= 1.5;
			wprintf(L"防御力：%lld==>%lld\n", defense, defense * 1.5);
			defense *= 1.5;
			wprintf(L"最大生命：%lld==>%lld\n", max_health, max_health + (xp / max_xp) * 4);
			max_health += (xp / max_xp) * 4;
			wprintf(L"技能点:%lld==>%lld\n", displayd - xp / max_xp, displayd);
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
			wcout << "\n注意，您的宠物血量已不足50%\n";
			return true;
		}
		if (health < max_health * 0.3)
		{
			wcout << "\n注意！您的宠物血量已不足30%\n";
			return true;
		}
		if (health < max_health * 0.1)
		{
			wcout << "\n警告！您的宠物血量已不足10%,请治疗TA!\n";
			return true;
		}
		return true;
	}
};
struct plan
{
	wchar_t name[200]; // 任务名
	long long money;   // 奖励的金币
	bool finish;	   // 是否完成
	bool get;		   // 是否领取
};
struct Cloths
{
	wchar_t name[25];
	long long attack_up;
	long long defense_up;
	long long num;
	long long money; // 售价
	void sx()
	{
		wprintf(L"\n名字[%s]\n", name);
		wprintf(L"攻击增强:%lld\n", attack_up);
		wprintf(L"防御增强:%lld\n", defense_up);
		wprintf(L"价格:%lld\n", money);
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
	wchar_t name[20];
	wchar_t hecheng[100];
	wchar_t texiao[100];
	long long need_money;
	void sx()
	{
		wprintf(L"\n物品名字:[%s]\n", name);
		if (wcscmp(hecheng, L"") == 0)
			wprintf(L"无法合成\n");
		else
			wprintf(L"合成方式:[%s]\n", hecheng);
		if (wcscmp(texiao, L"") == 0)
			wprintf(L"无特效\n");
		else
			wprintf(L"特效:[%s]\n", texiao);
		wprintf(L"价值:%lld\n", need_money);
	}
};
struct Item
{
	// 像药水一样使用一次就用完了...
	wchar_t name[20];
	long long attack;
	long long defense;
	wchar_t hecheng[100];
	wchar_t texiao[100];
	long long need_money;
	void sx()
	{
		wprintf(L"\n道具名字:[%s]\n", name);
		wprintf(L"攻击增加: %lld\n", attack);
		wprintf(L"防御增加: %lld\n", defense);
		if (wcscmp(hecheng, L"") == 0)
			wprintf(L"无法合成\n");
		else
			wprintf(L"合成方式:[%s]\n", hecheng);
		if (wcscmp(texiao, L"") == 0)
			wprintf(L"无特效\n");
		else
			wprintf(L"特效:[%s]\n", texiao);
		wprintf(L"价值:%lld\n", need_money);
	}
	void operator=(const wuping a)
	{
		wcscpy(name, a.name);
		wcscpy(hecheng, a.hecheng);
		wcscpy(texiao, a.texiao);
		need_money = a.need_money;
		attack = defense = 0;
	}
};
struct PLAYER
{
	wchar_t name[100];
	wchar_t display[20];
	long long health;
	long long max_health;
	long long xp;
	long long max_xp;
	long long attack;
	long long defense;
	long long level;
	long long money;
	/********/
	Pet p_pet[9]; // 玩家拥有8只宠物【8只为宠物上限】
	plan player_plan[100];
	cloths_slot slot;
	cloths_fight fight;
	/********/
	void sx()
	{
		wprintf(L"\n名字：%s\n", name);
		wprintf(L"初始技能：%s\n", display);
		wprintf(L"生命：%lld\n", health);
		wprintf(L"最大生命：%lld\n", max_health);
		wprintf(L"攻击力：%lld\n", attack);
		wprintf(L"防御力：%lld\n", defense);
		wprintf(L"等级：%lld\n", level);
		wprintf(L"经验:%lld\n升级所需经验：%lld\n", xp, max_xp);
		wprintf(L"金币:%lld\n", money);
	}
	void level_up()
	{
		if (xp >= max_xp)
		{
			wprintf(L"升级！！\n");
			wprintf(L"等级：%lld==>%lld\n", level, level + xp / max_xp);
			level += xp / max_xp;
			wprintf(L"攻击力：%lld==>%lld\n", attack, (long long)attack * 1.5);
			attack *= 1.5;
			wprintf(L"防御力：%lld==>%lld\n", defense, (long long)defense * 1.5);
			defense *= 1.5;
			wprintf(L"最大生命：%lld==>%lld", max_health, max_health + (xp / max_xp) * 4);
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
			wcout << L"\n注意，您的血量已不足50%\n";
			return true;
		}
		if (health < max_health * 0.3)
		{
			wcout << L"\n注意！您的血量已不足30%\n";
			return true;
		}
		if (health < max_health * 0.1)
		{
			wcout << L"\n警告！血量已不足10%,请速速离开!\n";
			return true;
		}
		return true;
	}
	int display_sx()
	{
		// 冰封1  电击2  灼烧3
		// 狂暴4  自由搏击5  连击6
		if (wcscmp(display, L"冰封") == 0)
		{
			return 1;
		}
		if (wcscmp(display, L"电击") == 0)
		{
			return 2;
		}
		if (wcscmp(display, L"灼烧") == 0)
		{
			return 3;
		}
		if (wcscmp(display, L"狂暴") == 0)
		{
			return 4;
		}
		if (wcscmp(display, L"自由搏击") == 0)
		{
			return 5;
		}
		if (wcscmp(display, L"连击") == 0)
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
int i, j, k, n, m, inputVarible;
PLAYER player;
Pet petInstance[20] = {
	{},
	{L"小恐龙", L"喷火", L"冲撞", 50, 50, 0, 90, 15, 9, 1, L"凌甲", L"钢爪", 150, 0},
	{L"大鹏鸟", L"高鸣", L"俯冲", 70, 70, 0, 120, 23, 14, 1, L"羽盾", L"尖嘴", 200, 0},
	{L"史莱姆", L"粘丝", L"分身level_up", 69, 69, 0, 300, 50, 73, 1, L"主角甲", L"主角盾", 960, 0},
	{L"\0", L"\0", L"\0", 0, 0, 0, 0, 0, 0, 0, L"\0", L"\0", 0, 0}};
/*
wchar_t name[25];
	long long attack_up;
	long long defense_up;
	long long num;
	long long money;//售价
	*/
Cloths c_std[100] = {
	{},
	{L"破旧的小刀", 10, 0, 0, 30},
	{L"破木盾", 0, 13, 0, 30},
	{L"铁剑", 17, 2, 0, 50},
	{L"铁甲", 0, 19, 0, 50},
	{L"滑石刀", 30, 6, 0, 390},
	{L"轻质石衣", 2, 35, 0, 390},
	{L"长勾", 25, 10, 0, 400},
	{L"圣骑士的盾", 13, 40, 0, 400},
	{L"雪山激光剑", 60, 35, 0, 1600},
	{L"冰玉石", 10, 90, 0, 1600},
	{L"光辉-0", 98, 80, 0, 2800},
	{L"结界", 30, 100, 0, 3220}};
world wor;
Pet empity = {};
// wuping & Item
// 见：我的世界图鉴大全
wuping things[100] =
	{
		{},
		{L"草", L"1*dirt", L"", 1},
		{L"土", L"1*grass", L"", 1},
		{L"石头", L"1*cobblestone", L"", 3},
		{L"圆石", L"1*stone", L"", 3},
		{L"空气", L"", L"Doomsday Lord", 9223372036854775800}, // 效果：末日之主
		{L"花岗岩", L"", L"", 3},
		{L"磨制花岗岩", L"9*granite", L"", 27},
		{L"闪长岩", L"", L"", 3},
		{L"磨制闪长岩", L"9*diorite", L"", 27},
		{L"安山岩", L"", L"", 3},
		{L"磨制安山岩", L"9*andesite", L"", 27},
		{L"沙子", L"", L"", 1},
		{L"木头", L"", L"", 16},
		{L"木板", L"1/4*log", L"", 4}};
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
Item prop[100] =
	{
		{}, {}};
// fight
Monster *currentEnemy;
Monster monster[100] = {
	{},
	{L"炒鸡玛丽", L"", 200, 200, 100, 80, 1, L"玛丽刀", L"玛丽甲", 100, 30},
	{L"超级蘑菇", L"", 300, 300, 40, 60, 1, L"孢刃", L"孢盾", 130, 40},
	{L"国王", L"control", 500, 500, 100, 100, 1, L"国王的新枪", L"国王的皇冠", 500, 80},
	{L"克鲁斯之眼", L"", 1000, 1000, 400, 130, 1, L"", L"", 1000, 300},
	{L"[毁灭]上帝", L"上帝之手", 5000, 5000, 3000, 3000, 1, L"", L"", 100000, 1000},
	{L"人类", L"生命回复", 100, 100, 5, 3000, 1, L"", L"", 5000, 90},
	{L"森林女王", L"森林控制", 3000, 3000, 400, 800, 1, L"藤鞭", L"至圣金盾", 10000, 8000},
	{L"梦之守卫", L"威压", 240, 240, 80, 120, 1, L"梦境匕首", L"云制衣", 300, 70},
	{L"神秘老人", L"开挂", 400, 400, 300, 1000, 1, L"[氪金道具]法杖", L"[氪金道具]防护罩", 10, 1000},
	{L"[至圣]欧几里得", L"几何构建", 1000, 1000, 400, 400, 1, L"[几何原本]角", L"[几何原本]图", 10000, 100000},
	{L"粉红羊先生", L"", 200, 200, 50, 40, 1, L"", L"", 1000, 1000},
	{L"猪先生", L"", 200, 200, 80, 20, 1, L"", L"", 800, 1200},
	{L"Steve", L"世界编辑者", 800, 800, 130, 200, 1, L"", L"", 1000, 2000}};
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
int strpla(plan a[])
{
	for (int i = 1;; i++)
	{
		if (wcscmp(a[i].name, L"\0") == 0)
			return i - 1;
	}
}
int PetArraySize(Pet pet[])
{ // 宠物数量统计
	for (int i = 1;; i++)
	{
		if (wcscmp(pet[i].name, L"\0") == 0)
			return i - 1;
		if (i >= 1000)
			return -1;
	}
}
int strclo(Cloths a[])
{
	for (int i = 1; i <= 1000; i++)
	{
		//		wcout<<"出不去\n";
		if (wcscmp(a[i].name, L"\0") == 0)
			return i - 1;
		if (i >= 1000)
			return -1;
	}
	return -1;
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
void number_of_cloth(wchar_t a[], int number)
{
	int l = strclo(c_std);
	for (i = 1; i <= l; i++)
	{
		if (wcscmp(c_std[i].name, a) == 0)
			c_std[i].num += number;
	}
}
void sale(Cloths &a)
{
	a.sx();
	wprintf(L"是否卖出%s?1.yes 2.no\n", a.name);
	int inputVarible;
mai:
	FastReadInteger(inputVarible);
	if (inputVarible == 2)
		return;
	if (inputVarible != 1)
	{
		wcout << "输入错误\n";
		goto mai;
	}
	player.money += a.money;
	number_of_cloth(a.name, -1);
	wprintf(L"成功卖出%s!,你获得了%lld金币\n", a.name, a.money);
}
int displayxz(int x)
{
	if (x == 1)
		while (1)
		{
			FastReadInteger(inputVarible);
			switch (inputVarible)
			{
			case 1:
				wcscpy(player.display, L"冰封");
				return 0;
			case 2:
				wcscpy(player.display, L"电击");
				return 0;
			case 3:
				wcscpy(player.display, L"灼烧");
				return 0;
			case 0:
				return 1;
			default:
				wcout << "输入错误\n";
				break;
			}
		}
	if (x == 2)
		while (1)
		{
			FastReadInteger(inputVarible);
			switch (inputVarible)
			{
			case 1:
				wcscpy(player.display, L"狂暴");
				return 0;
			case 2:
				wcscpy(player.display, L"自由搏击");
				return 0;
			case 3:
				wcscpy(player.display, L"连击");
				return 0;
			case 0:
				return 1;
			default:
				wcout << "输入错误\n";
				break;
			}
		}

	throw std::runtime_error("displayxz error");
}
void cs()
{
	player.health = 100 + abs(player.name[rand() % wcslen(player.name) + 1]) / 3;
	player.xp = 0;
	player.max_health = player.health;
	player.attack = 100;
	player.defense = 50;
	player.level = 1;
	player.max_xp = 150;
	player.money = 8110;
	wcscpy(player.player_plan[1].name, L"asdasd");
	player.player_plan[1].finish = true;
	player.player_plan[1].money = 100;
	player.p_pet[1] = petInstance[1];
	player.p_pet[1].xp = 1000000;
	player.p_pet[1].health -= 10;
	for (int i = 1; i <= strclo(c_std); i++)
	{
		c_std[i].num++;
	}
	player.sx();
	WriteSave();
	Pause();
	system("cls");
}
void zdy_player()
{
	GameColoredPrint(L"玩家，请输入您的名字\n");
	std::wcin >> player.name;
a:
	GameColoredPrint(L"请选择你的角色:\n\n1.元素法师     2.狂战士     3.驯兽师");
	FastReadInteger(inputVarible);
	int cccc;
	switch (inputVarible)
	{
	case 1:
		GameColoredPrint(L"\n玩家，请选择您的技能：\n(1.冰封     2.电击     3.灼烧)请选择：0.退出\n");
		cccc = displayxz(1);
		if (cccc == 1)
			goto a;
		break;
	case 2:
		GameColoredPrint(L"\n玩家，请选择您的技能：\n(1.狂暴     2.自由搏击     3.连击)请选择：0.退出\n");
		cccc = displayxz(2);
		if (cccc == 1)
			goto a;
		break;
	case 3:
		GameColoredPrint(L"\n未设置\n");
		goto a;
		break;
	default:
		wcout << "\n输入错误\n";
		goto a;
	}
	if (wcscmp(player.name, L"jimmy96b") == 0)
	{
		cs();
		return;
	}
	player.health = 100 + abs(player.name[rand() % wcslen(player.name) + 1]) / 3;
	player.xp = 0;
	player.max_health = player.health;
	player.attack = 100;
	player.defense = 50;
	player.level = 1;
	player.max_xp = 150;
	player.money = 80;
	player.sx();
	WriteSave();
	Pause();
	system("cls");
}
void banquan()
{
	system("cls");
	GameColoredPrint(L"此游戏由");
	DelayPrint(L"【水墨工作室】");
	wprintf(L"%s", L"创作\n\n");
	DelayPrint(L"未经允许，不得转载\n");
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
	GameColoredPrint(L"----\n此游戏为作者8.0版：\n相对于上版本，代码进行了一些改进，变得更加容易明白\n1.添加[游戏商店]中的一些怪物2.添加[物品]及[道具]功能(No!)\n若有不足之处，请玩家大大们原谅\n-----");
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
	long long health = currentEnemy->health;
fnn:
	if (player_can_attack == false)
	{
		wcout << "\n您无法操作\n";
		player_can_attack = true;
	}
	else
	{
		GameColoredPrint(L"\n==========================================================\n");
		wprintf(L"[%s]你要如何战胜%s?\n", player.name, currentEnemy->name);
		GameColoredPrint(L"1.普通攻击(不建议)     2.道具     3.查看人物此时以及对手此时属性\n\n4.宠物     5.逃跑(因该是怂了)\n");
		GameColoredPrint(L"==========================================================\n");
		FastReadInteger(inputVarible);
		switch (inputVarible)
		{
		case 1:
		{
			int shanghai;
			shanghai = player.attack + rand() % 10 + 1 - currentEnemy->defense * currentEnemy->level / 2;
			if (shanghai < 0)
				shanghai = 1;
			health -= shanghai;
			if (health < 0)
				health = 0;
			wprintf(L"你发动了攻击,敌方受到%d点伤害\n\n敌方还剩%lld点血\n", shanghai, health);
			WriteSave();
			Pause();
			break;
		}
		case 2:
		{
			GameColoredPrint(L"\n本功能尚未实现\n");
			goto fnn;
			break;
		}
		case 3:
		{
			SetConsoleTextColor(14);
			wprintf(L"------您的属性：------");
			SetConsoleTextColor(15);
			player.sx();
			SetConsoleTextColor(11);
			wprintf(L"------对方属性：------");
			SetConsoleTextColor(15);
			currentEnemy->DisplayInfo();
			puts("");
			goto fnn;
			break;
		}
		case 4:
		{
			GameColoredPrint(L"\n本功能尚未实现\n");
			goto fnn;
			break;
		}
		case 5:
		{
			int go = GenerateRandomNumber(1, 10);
			if (go <= 4)
			{
				wcout << "逃跑成功!\n";
				WriteSave();
				return 2;
			}
			else
			{
				wcout << "逃跑失败(原因:你太怂了)\n";

				goto fnn;
			}
			break;
		}
		default:
			wcout << "输入错误\n";
			goto fnn;
			break;
		}
		Sleep(100);
	}
	if (health <= 0)
	{
		system("cls");
		SetConsoleTextColor(10);
		wprintf(L"您战胜了%s\n\n", currentEnemy->name);
		wprintf(L"您获得了%lld*%lld=%lld金币\n您", currentEnemy->money, currentEnemy->level, currentEnemy->money * currentEnemy->level);
		bool cw = false; // 是否有宠物：初始默认无
		if (PetArraySize(player.p_pet) > 0)
			wcout << "以及您的宠物", cw = true;
		wprintf(L"获得了%lld*%lld=%lld点经验\n", currentEnemy->xp, currentEnemy->level, currentEnemy->xp * currentEnemy->level);
		player.xp += currentEnemy->xp * currentEnemy->level;
		player.money += currentEnemy->money * currentEnemy->level;
		if (cw == true)
			for (int i = 1; i <= PetArraySize(player.p_pet); i++)
				player.p_pet[i].xp += currentEnemy->xp * currentEnemy->level;
		SetConsoleTextColor(15);
		Pause();
		fighting = false;
		currentEnemy->level++;
		WriteSave();
		return 1;
	}
	else
	{
		if (guai_can_attack == false)
		{
			wcout << "\n对方无法操作\n";
			guai_can_attack = true;
		}
		else
		{
			// 怪物反击时有20%触发技能
			int shanghai = currentEnemy->attack * currentEnemy->level + rand() % 10 + 1 - player.defense / 2;
			if (shanghai < 0)
				shanghai = 1;
			player.health -= shanghai;
			if (player.health < 0)
				player.health = 0;
			wprintf(L"[%s]", currentEnemy->name);
			GameColoredPrint(L"发起了反击,你受到");
			wprintf(L"%d", shanghai);
			GameColoredPrint(L"点伤害,还剩");
			wprintf(L"%lld", player.health);
			GameColoredPrint(L"点血量\n");
			WriteSave();
			Pause();
		}
	}
	if (!player.alive())
	{
		system("cls");
		WriteSave();
		SetConsoleTextColor(12);
		wprintf(L"战死!,金币掉落10%\n\n复活时血量为最高血量的50%\n\n");
		SetConsoleTextColor(15);
		player.money *= 0.9;
		if (player.money < 0)
			player.money = 0;
		if (player.max_health <= 140)
		{
			GameColoredPrint(L"但由于您的生命值太低，直接恢复至最大生命\n");
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
	GameColoredPrint(L"===============================");
	SetConsoleCursor(40, 15);
	GameColoredPrint(L"================================");
	SetConsoleCursor(40, 11);
	DelayPrint(L"此游戏为【水墨工作室】制作");
	SetConsoleCursor(40, 14);
	DelayPrint(L"未经允许,不得转载");
	Sleep(800);
	system("cls");
}
/*****/
void chou()
{
	wchar_t s[5] = L" orz";
	GameColoredPrint(L"\n[抽奖规则]:\n");
	GameColoredPrint(L"ooo 300金币\n");
	GameColoredPrint(L"rrr 150金币\n");
	GameColoredPrint(L"zzz 100金币\n");
	GameColoredPrint(L"有两个字母相同 110金币\n");
	GameColoredPrint(L"【orz】--->800金币\n");
	GameColoredPrint(L"其它：10金币\n");
cnn:
	GameColoredPrint(L"\n-=-=-=-(^oo^)\n");
	GameColoredPrint(L"您是否愿意花100金币进行抽奖？1.yes/2.no\n");
	GameColoredPrint(L"-=-=-=-=-=-=-\n");
	FastReadInteger(inputVarible);
	if (inputVarible == 1)
		if (player.money >= 100)
		{
			player.money -= 100;
			int a, b, c;
			system("cls");
			for (float i = 1; i >= 0; i -= 0.01)
			{
				wprintf(L"1.[正在加载]%.2f", i);
				if (i - 0.01 > 0)
					wcout << "\r";
				Sleep(1);
			}
			a = rand() % 3 + 1;
			puts("");
			for (float i = 1; i >= 0; i -= 0.01)
			{
				wprintf(L"2.[正在加载]%.2f\r", i);
				if (i - 0.01 > 0)
					wcout << "\r";
				Sleep(1);
			}
			b = rand() % 3 + 1;
			puts("");
			for (float i = 1; i >= 0; i -= 0.01)
			{
				wprintf(L"3.[正在加载]%.2f\r", i);
				if (i - 0.01 > 0)
					wcout << "\r";
				Sleep(1);
			}
			c = rand() % 3 + 1;
			puts("");
			GameColoredPrint(L"您的抽奖结果是:【");
			wprintf(L"%c,%c,%c", s[a], s[b], s[c]);
			GameColoredPrint(L"】\n");
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
			wprintf(L"\n获得%d金币", p);
			player.money += p;
		}
		else
		{
			GameColoredPrint(L"\n金币不够\n");
		}
}
void house()
{
hnn:
	GameColoredPrint(L"\n===============================\n");
	GameColoredPrint(L"【探险家的小屋】:\n1.装备售出    2.抽奖     3.与房子的主人对话\n\n0.退出  (请选择:)\n");
	GameColoredPrint(L"===============================\n");
	FastReadInteger(inputVarible);
	switch (inputVarible)
	{
	case 1:
	{
	mai1:
		int n = jiazaic();
		if (n == 0)
		{
			GameColoredPrint(L"您没有可用装备...\n");
			goto hnn;
		}
		GameColoredPrint(L"您的可用装备:\n");
		for (int i = 1; i <= n; i++)
		{
			wprintf(L"%d.[%s]    ", i, canin[i].name);
			if (i % 3 == 0 && i + 1 <= n)
				puts("");
		}
		GameColoredPrint(L"0.退出\n");
	salec:
		FastReadInteger(inputVarible);
		if (inputVarible < 0 || inputVarible > n)
		{
			wcout << "choose error\n";
			goto salec;
		}
		else if (inputVarible == 0)
			goto hnn;
		else
			sale(canin[inputVarible]);
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
			DelayPrint(L"亲爱的");
			wprintf(L"[%s]\n\n", player.name);
			DelayPrint(L"你是第一次来到这里吧！\n给你一些装备，去冒险吧！\n");
			GameColoredPrint(L"\n[提示]:您获得了[破旧的小刀]*1[破木盾]*1\n\n");
			number_of_cloth(L"破旧的小刀", 1);
			number_of_cloth(L"破木盾", 1);
			WriteSave();
		}
		else
		{
			DelayPrint(L"亲爱的");
			wprintf(L"[%s]\n", player.name);
			DelayPrint(L"你又来了！随便看看吧\n");
		}
		Pause();
		goto hnn;
		break;
	}
	case 0:
		return;
	default:
	{
		wcout << "\n输入错误！\n";
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
	GameColoredPrint(L"\n欢迎来到游戏专卖店!\n	这里有应有尽有的游戏供您玩耍\n");
	GameColoredPrint(L"\n~~~~~~~~~~~~~~~~~~~~\n");
	GameColoredPrint(L"1.超级玛丽     2.泰拉瑞亚     3.沙盒2\n\n4.Minecraft     5.物理沙盘     6.元气骑士\n\n0.退出(请选择:)\n");
	GameColoredPrint(L"~~~~~~~~~~~~~~~~~~~~\n");
gnn:
	FastReadInteger(inputVarible);
	if (inputVarible < 0 || inputVarible > 6)
	{
		wcout << "\n输入错误！\n";
		goto gnn;
	}
	if (inputVarible == 0)
		return;
	int t;
	t = rand() % 3 + 1;
	switch (t)
	{
	case 1:
		DelayPrint(L"\n在一阵耀眼的光芒下,你遇见了:");
		break;
	case 2:
		DelayPrint(L"\n在天旋地转的眩晕下,你遇见了:");
		break;
	case 3:
		DelayPrint(L"\n只听'轰'的一声,你遇见了:");
		break;
	}
	int i;
	if (inputVarible == 1)
	{
		t = GenerateRandomNumber(1, 2);
		if (t == 1)
			currentEnemy = &ml;
		else
			currentEnemy = &mg;
	}
	else if (inputVarible == 2)
	{
		t = GenerateRandomNumber(1, 2);
		if (t == 1)
			currentEnemy = &king;
		else
			currentEnemy = &krous_eye;
	}
	else if (inputVarible == 3)
	{
		t = GenerateRandomNumber(1, 10);
		if (t < 3)
		{
			DelayPrint(L"一阵强烈的妖风吹来，你全身一抖...\n");
			currentEnemy = &God;
		}
		else
			currentEnemy = &Human;
	}
	else if (inputVarible == 4)
	{
		t = GenerateRandomNumber(1, 10);
		if (t < 4)
			currentEnemy = &pig;
		else if (t < 7)
			currentEnemy = &sheep;
		else
			currentEnemy = &steve;
	}
	else
		currentEnemy = &cho;
	currentEnemy->DisplayInfo();
funn:
	wprintf(L"[%s]向你发出了挑战,是否接受？？	(1.yes,2.no)\n", currentEnemy->name);
	FastReadInteger(inputVarible);
	if (inputVarible == 2)
		goto gnn0;
	if (inputVarible != 1)
	{
		wcout << "输入错误!\n";
		goto funn;
	}
	fight(); // 战斗函数
}
void magic_forest()
{
	GameColoredPrint(L"\nWelcome to the'Magic Forest'\n");
mnn:
	GameColoredPrint(L"======================================\n");
	GameColoredPrint(L"choose:1.观赏风景     2.静坐     3.随便看看\n\n0.退出\n");
	GameColoredPrint(L"======================================\n");
	FastReadInteger(inputVarible);
	switch (inputVarible)
	{
	case 1:
	{
		int sj = GenerateRandomNumber(1, 100);
		if (sj <= 70)
		{
			DelayPrint(L"\n啊~风景真好");
			GameColoredPrint(L"	经验+2;\n");
			player.xp += 2;
			goto mnn;
		}
		else
		{
			GameColoredPrint(L"\n你看见了[森林女王]，她朝你走来:\n\n");
			DelayPrint(L"是谁那么大胆?敢冒犯此地！\n");
			DelayPrint(L"	原来是亲爱的");
			wprintf(L"[%s]", player.name);
			DelayPrint(L"呀!\n");
		mqnn:
			GameColoredPrint(L"===================================\n");
			GameColoredPrint(L"你要做什么:\n1.对话     2.战斗     3.(null)\n\n0.退出\n");
			GameColoredPrint(L"===================================\n");
			FastReadInteger(inputVarible);
			switch (inputVarible)
			{
			case 1:
				break;
			case 2:
			{
				GameColoredPrint(L"[森林女王]接受了你的挑战!\n\n");
				currentEnemy = &slnw;
				int sao = fight();
				if (sao == 1)
				{
					GameColoredPrint(L"\n[森林女王]:");
					DelayPrint(L"\n都多久没有人能打败我啦,你胜利了,这些是给你的奖励：\n");
				}
				else if (sao == 0)
				{
					GameColoredPrint(L"\n[森林女王]:");
					DelayPrint(L"\n要继续加油呀!\n");
				}
				break;
			}
			case 3:
				break;
			case 0:
				goto mnn;
			default:
				wcout << "输入错误\n";
				goto mqnn;
			}
		}
		break;
	}
	case 2:
	{
		int id;
		GameColoredPrint(L"你只是静静地坐着...\n");
		int zuo = GenerateRandomNumber(1, 100);
		if (zuo >= 60)
		{
			GameColoredPrint(L"你不知不觉地睡着了\n\n");
			Pause();
			GameColoredPrint(L"在梦的幻境中,你遇见了:");
			int mon = GenerateRandomNumber(1, 3);
			switch (mon)
			{
			case 1:
				currentEnemy = &mzsw;
				break;
			case 2:
				currentEnemy = &smlr;
				break;
			case 3:
				currentEnemy = &ojld;
				break;
			}
		fuck:
			SetConsoleTextColor(14);
			wprintf(L"[%s]", currentEnemy->name);
			SetConsoleTextColor(15);
			GameColoredPrint(L"\nta向你发起了挑战,是否接受(1.yes,2.no)\n");
			currentEnemy->DisplayInfo();
			int bbb;
			FastReadInteger(bbb);
			if (bbb == 2)
				goto mnn;
			if (bbb != 1)
			{
				wcout << "输入错误\n";
				goto fuck;
			}
			GameColoredPrint(L"ta接受了你的挑战！\n");
			int ans = fight();
			if (ans == 1)
			{
				DelayPrint(L"\n你醒来了\n");
			}
			else
			{
				DelayPrint(L"\n挑战失败,你醒了\n");
			}
			goto mnn;
		}
		else
		{
			GameColoredPrint(L"		你好像感悟到了什么,[经验]+4\n");
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
		wcout << "输入错误!!!\n";
		goto mnn;
		break;
	}
}
/*****/
void mov()
{
	GameColoredPrint(L"\n-----------------------------------------------\n");
	SetConsoleTextColor(11);
	GameColoredPrint(L"1.探险家的小屋    2.游戏专卖店    3.祈愿求签\n\n");
	GameColoredPrint(L"4.魔法森林    5.冰雪平原    6.(NULL)\n\n");
	GameColoredPrint(L"7.深海古战场    8.云之顶峰    0.退出\n\n请选择：\n");
	SetConsoleTextColor(15);
	GameColoredPrint(L"-----------------------------------------------\n");
	FastReadInteger(inputVarible);
	switch (inputVarible)
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
		wcout << "输入错误\n";
		break;
	}
}
void SwitchItem()
{
	GameColoredPrint(L"\n++++++++++++++++++++++++++++++++++++\n");
	SetConsoleTextColor(14);
	GameColoredPrint(L"选择类型：\n1.治愈类     2.辅助类     3.buff类     0.退出\n");
	SetConsoleTextColor(15);
	GameColoredPrint(L"++++++++++++++++++++++++++++++++++++\n");
	FastReadInteger(inputVarible);
	switch (inputVarible)
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
		wcout << "\n输入错误";
		getch();
		wcout << "\r";
		break;
	}
}
void shop()
{
buy:
	GameColoredPrint(L"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	GameColoredPrint(L"【选择类别】\n");
	GameColoredPrint(L"1.宠物类     2.人物类     3.道具类     4.装备类\n\n0.退出\n");
	GameColoredPrint(L"~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	FastReadInteger(inputVarible);
	switch (inputVarible)
	{
	case 1:
	{
	bp:
		int l = PetArraySize(petInstance);
		wprintf(L"\n-----\n");
		for (i = 1; i <= l; i++)
		// 循环打出宠物名，添加选项
		{
			wcout << i << ":   " << petInstance[i].name << endl;
		}
		wcout << "0.退出     请选择：\n";
		wprintf(L"-----\n");
	buy_pet:
		FastReadInteger(inputVarible); // 选择：输出宠物属性，是否购买
		if (inputVarible == 0)
			goto buy;
		if (inputVarible < 1 || inputVarible > l)
		{
			wcout << "\n输入错误";
			goto buy_pet;
		}
		petInstance[inputVarible].sx();
		wcout << "\n是否购买？ 1.yes/2.no\n";
		int cc;
		FastReadInteger(cc);
		if (cc == 1)
		{

			if (PetArraySize(player.p_pet) == -1)
			{
				wcout << "\n抱歉，您的宠物已达到上限，无法进行购买..\n";
				goto buy;
			}
			else
				for (i = 1; i <= PetArraySize(player.p_pet); i++)
				{
					if (wcscmp(player.p_pet[i].name, petInstance[inputVarible].name) == 0)
					{
						wcout << "\n您已拥有此宠物!\n";
						goto buy;
					}
				}
			if (player.money < petInstance[inputVarible].money)
			{
				wcout << "\n抱歉，您钱币不足，无法进行购买..\n";
				goto buy;
			}
			else
			{
				player.money -= petInstance[inputVarible].money;
				player.p_pet[PetArraySize(player.p_pet) + 1] = petInstance[inputVarible];
				wcout << "\n成功获得宠物[" << petInstance[inputVarible].name << "]\n";
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
			wprintf(L"\n(1)人物技能     (2)其他     0.返回上一级\n");
			FastReadInteger(inputVarible);
			switch (inputVarible)
			{
			case 1:
				break;
			case 2:
				break;
			case 0:
				goto buy;
			default:
				wcout << "\n输入错误\n";
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
		wprintf(L"可供购买装备:\n");
		for (int i = 1; i <= l; i++)
		{
			wprintf(L"%d.(%s)     ", i, c_std[i].name);
			if (i % 3 == 0 && i + 1 <= l)
				puts("");
		}
		wprintf(L"0.退出\n");
	inc:
		FastReadInteger(inputVarible);
		if (inputVarible == 0)
			goto buy;
		if (inputVarible < 0 || inputVarible > l)
		{
			wcout << "choose error\n";
			goto inc;
		}
		c_std[inputVarible].sx();
		wprintf(L"是否选择购买？1.yes 其他键.no\n");
		int cc;
		FastReadInteger(cc);
		if (cc != 1)
			goto clo;
		if (player.money >= c_std[inputVarible].money)
		{
			player.money -= c_std[inputVarible].money;
			number_of_cloth(c_std[inputVarible].name, 1);
			GameColoredPrint(L"\n---购买成功---\n");
			goto buy;
		}
		else
		{
			wcout << "对不起，您的金币数量不足...\n";
			goto clo;
		}
	}
	case 0:
		return;
	default:
		wcout << "\n输入错误\n";
		goto buy;
		break;
	}
}
void plant()
{
	GameColoredPrint(L"\n==========================\n");
	int l = strpla(player.player_plan);
	for (int i = 1; i <= l; i++)
	{
		GameColoredPrint(L"\n----------------------------\n");
		wprintf(L"第【%d】条任务:%s\n", i, player.player_plan[i].name);
		GameColoredPrint(L"\n是否完成：");
		if (player.player_plan[i].finish == true)
			wcout << "Yes!\n";
		else
			wcout << "No!\n";
		wcout << "\n奖励：" << player.player_plan[i].money << endl;
		if (player.player_plan[i].get == false)
			wcout << "未领取\n";
		else
			wcout << "已领取\n";
		GameColoredPrint(L"----------------------------\n");
	}
	GameColoredPrint(L"==========================\n");
	// 循环输出任务;
	wcout << "请选择：(0.退出)\n";
pc:
	FastReadInteger(inputVarible);
	if (inputVarible < 0 || inputVarible > l)
	{
		wcout << "\n输入错误！！\n";
		goto pc;
	}
	else if (inputVarible == 0)
		return;
	else
	{
		if (player.player_plan[inputVarible].finish == false)
		{
			wcout << "\n此任务未完成\n";
			goto pc;
		}
		if (player.player_plan[inputVarible].get == false)
		{
			wcout << "\n领取成功！\n";
			player.player_plan[inputVarible].get = true;
			player.money += player.player_plan[inputVarible].money;
		}
		else
		{
			wcout << "\n您已领取！\n";
			goto pc;
		}
	}
	// 选择领取奖励
	// 完成即可领取
}
void about_pet()
{
sp:
	int l = PetArraySize(player.p_pet);
	if (l == 0)
	{
		wcout << "\n您并没有宠物..\n";
		return;
	}
	GameColoredPrint(L"\n~_~_~_~_~_~_~_~_~_~_~_~\n");
	for (int i = 1; i <= l; i++)
	{
		wcout << i << ": " << player.p_pet[i].name << "     ";
		if (i % 3 == 0 && i + 1 <= l)
			puts("\n");
	}
	wcout << "\n请选择(0.退出)\n";
	GameColoredPrint(L"\n~_~_~_~_~_~_~_~_~_~_~_~\n");
apc:
	FastReadInteger(inputVarible);
	if (inputVarible == 0)
		return;
	if (inputVarible < 0 || inputVarible > l)
	{
		wcout << "输入错误\n";
		goto apc;
	}
pnn:
	GameColoredPrint(L"\n----your pet----(^_^)\n");
	wprintf(L"【%s】:\n", player.p_pet[inputVarible].name);
	GameColoredPrint(L"1.恢复     2.升级     3.装备\n\n4.属性     5.放生     0.返回上一级\n");
	GameColoredPrint(L"---------------------\n");
	int cc;
pnn1:
	FastReadInteger(cc);
	switch (cc)
	{
	case 1:
	{
		if (player.p_pet[inputVarible].health == player.p_pet[inputVarible].max_health)
		{
			wcout << "\n[系统]:宠物'完好无损',无需恢复,自动返回上级\n";
			goto pnn;
		}
	pnn2:
		wcout << "\n[系统]:是否花费100金币恢复该宠物？1.yes/2.no\n       (按下按键即选择)\n";
		int x = getch() - '0';
		if (x != 1 && x != 2)
		{
			wcout << "choose erro\n";
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
				wcout << "\n钱不够\n";
				goto pnn1;
			}
			else
			{
				player.money -= 100;
				player.p_pet[inputVarible].health = player.p_pet[inputVarible].max_health;
				wcout << "\n您为宠物【氪金】成功\n";
				goto pnn;
			}
		}
		break;
	}
	case 2:
	{
		wprintf(L"该宠物拥有经验数：%lld\n该宠物升级需要经验数:%lld\n宠物等级：%lld\n", player.p_pet[inputVarible].xp, player.p_pet[inputVarible].max_xp, player.p_pet[inputVarible].level);
		GameColoredPrint(L"是否升级？1.yes/2.no\n");
		int cc;
	pnn3:
		FastReadInteger(cc);
		if (cc != 1 && cc != 2)
		{
			wcout << "\n输入错误\n";
			goto pnn3;
		}
		else if (cc == 1)
		{
			if (player.p_pet[inputVarible].xp < player.p_pet[inputVarible].max_xp)
			{
				wcout << "\n经验不足\n";
				goto pnn;
			}
			else
			{
				wcout << "\n升级成功\n";
				player.p_pet[inputVarible].level_up();
				player.p_pet[inputVarible].health = player.p_pet[inputVarible].max_health;
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
		player.p_pet[inputVarible].sx();
		break;
	}
	case 5:
	{
	pnn_:
		GameColoredPrint(L"\n是否放生您的宠物(请慎重!)1.yes/2.no\n");
		int dd;
		FastReadInteger(dd);
		if (dd != 1 && dd != 2)
		{
			wcout << "\n输入错误！！\n";
			goto pnn_;
		}
		if (dd == 1)
		{
			std::swap(player.p_pet[PetArraySize(player.p_pet)], player.p_pet[inputVarible]);
			player.p_pet[PetArraySize(player.p_pet)] = empity;
			GameColoredPrint(L"[系统]:该宠物放生成功");
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
		wcout << "\n输入错误\n";
		goto pnn1;
		break;
	}
	}
}
void change_cloths(Cloths &ac)
{
	if (wcscmp(ac.name, L"\0") == 0)
	{
		GameColoredPrint(L"\n此栏并没有任何装备\n	请选择你要替换的装备:\n");
	}
	else
	{
		ac.sx();
		GameColoredPrint(L"您要将[");
		wprintf(L"%s", ac.name);
		GameColoredPrint(L"]替换成什么:\n");
	}
	int sum = jiazaic();
	if (sum == 0)
	{
		wcout << "\n您一件装备也没有\n";
		wprintf(L"是否脱下此装备？？？1.yes 其它.no\n");
		FastReadInteger(inputVarible);
		if (inputVarible == 1)
		{
			player.attack -= ac.attack_up;
			player.defense -= ac.defense_up;
			for (int i = 1; i <= strclo(c_std); i++)
			{
				if (wcscmp(c_std[i].name, ac.name) == 0)
				{
					c_std[i].num++;
				}
			}
			ac = _empity;
			wprintf(L"成功脱下\n");
		}
		Pause();
		puts("\n");
		return;
	}
	SetConsoleTextColor(13);
	wprintf(L"\n================================\n");
	for (int i = 1; i <= sum; i++)
	{
		wprintf(L"%d.[%s] ", i, canin[i].name);
		if (i % 3 == 0 && i + 1 != sum)
			puts("");
	}
	wprintf(L"\n请选择:999.脱下此装备     (0.退出)\n");
	wprintf(L"================================\n");
	SetConsoleTextColor(15);
ccnn:
	FastReadInteger(inputVarible);
	if ((inputVarible < 0 || inputVarible > sum) && inputVarible != 999)
	{
		wcout << "\nchoose error\n";
		goto ccnn;
	}
	if (inputVarible == 0)
	{
		return;
	}
	else if (inputVarible != 999)
	{
		player.attack -= ac.attack_up;
		player.defense -= ac.defense_up;
		player.attack += canin[inputVarible].attack_up;
		player.defense += canin[inputVarible].defense_up;
		for (int i = 1; i <= strclo(c_std); i++)
		{
			if (wcscmp(c_std[i].name, ac.name) == 0)
			{
				c_std[i].num++;
			}
			if (wcscmp(c_std[i].name, canin[inputVarible].name) == 0)
			{
				c_std[i].num--;
			}
		}
		ac = canin[inputVarible];
	}
	else
	{
		player.attack -= ac.attack_up;
		player.defense -= ac.defense_up;
		for (int i = 1; i <= strclo(c_std); i++)
		{
			if (wcscmp(c_std[i].name, ac.name) == 0)
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
	GameColoredPrint(L"---------------\n");
	GameColoredPrint(L"你要做什么:\n1.切换装备     0.退出\n");
	GameColoredPrint(L"---------------\n");
	Cloths now;
	int jjj;
	FastReadInteger(inputVarible);
	switch (inputVarible)
	{
	case 1:
	{
	zbnn:
		wprintf(L"\n1.头部:[%s]	2.身体:[%s]\n\n3.腿部:[%s]	4.脚部:[%s]\n\n5.手部[%s]	6.肩膀[%s]\n0.退出\n", player.slot.head, player.slot.body, player.slot.leg, player.slot.foot, player.fight.hand, player.fight.arm);
		FastReadInteger(inputVarible);
		switch (inputVarible)
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
			wcout << "choose error!\n";
			goto zbnn;
			break;
		}
		break;
	}
	case 0:
		return;
	default:
		GameColoredPrint(L"输入错误\n");
		goto ms1;
	}
	goto zbnn;
}
void myself()
{
msn:
	GameColoredPrint(L"-------------------------------------\n");
	wprintf(L"[%s]你要做什么?\n", player.name);
	GameColoredPrint(L"1.查看基本属性     2.升级     3.恢复\n\n0.退出\n");
	GameColoredPrint(L"-------------------------------------\n");
	FastReadInteger(inputVarible);
	switch (inputVarible)
	{
	case 1:
		myself1();
		break;
	case 2:
	{
		wprintf(L"您拥有经验:[%lld]\n升级所需经验:[%lld]\n您的等级:[%lld]\n是否升级?(1.yes,2.no)", player.xp, player.max_xp, player.level);
	shit:
		int bbbb;
		FastReadInteger(bbbb);
		if (bbbb == 2)
			goto msn;
		if (bbbb != 1)
		{
			wcout << "输入错误!\n";
			goto shit;
		}
		if (player.xp < player.max_xp)
		{
			wcout << "经验不足\n";
			goto msn;
		}
		else
		{
			player.level_up();
			player.health = player.max_health;
			wcout << "\n升级成功！\n";
		}
		goto msn;
		break;
	}
	case 3:
	{
		if (player.health == player.max_health)
		{
			GameColoredPrint(L"您血量已满,无需恢复\n");
			goto msn;
		}
		int huafei = (player.max_health - player.health) / 2;
		wprintf(L"\n您的生命[%lld]\n生命上限[%lld]\n恢复至上限需要[%lld]金币\n", player.health, player.max_health, huafei);
		wprintf(L"\n请输入您想恢复的生命(0退出):");
		int xx;
		FastReadInteger(xx);
		if (xx == 0)
			goto msn;
		if (xx > player.max_health - player.health)
		{
			wcout << "这个值已经超过最高值!自动回满\n";
		}
		else
		{
			huafei = xx / 2;
		}
		Pause();
		if (player.money < huafei)
		{
			wcout << "\n金币不足       \n";
			goto msn;
		}
		else
		{
			player.health += xx;
			player.money -= huafei;
			wcout << "恢复成功         \r";
			goto msn;
		}
		break;
	}
	case 0:
		return;
	default:
		wcout << "choose error\n";
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
	wprintf(L"\n您现在时间:%4d/%02d/%02d %02d:%02d:%02d.%03d 星期%1d\n\n\n", sys2.wYear, sys2.wMonth, sys2.wDay, sys2.wHour, sys2.wMinute, sys2.wSecond, sys2.wMilliseconds, sys2.wDayOfWeek);
	if (sys.wDay != sys2.wDay)
	{
		wprintf(L"\n您获得[新的一天]奖励:1000金币，100经验,自动更新登录日期\n");
		player.money += 1000;
		player.xp += 100;
		wor.last = wor.now;
		WriteSave();
		Pause();
	}
	else
		wprintf(L"\n您没有登录奖励\n");
	wprintf(L"\n-----\n");
	wprintf(L"其它功能敬请期待...\n");
	wprintf(L"-----\n");
	Pause();
}
void start()
{
	wcout << "【" << player.name << "】要干什么？";
	GameColoredPrint(L"\n================================\n");
	SetConsoleTextColor(13);
	GameColoredPrint(L"1.移动    2.道具    3.查看个人属性    4.背包\n\n");
	GameColoredPrint(L"5.宠物    6.商店    7.神话专区    8.系统消息\n\n");
	GameColoredPrint(L"9.任务    10.功能\n\n");
	GameColoredPrint(L"11.版本更新    12.游戏版权    13.版本介绍    0.退出游戏\n");
	SetConsoleTextColor(15);
	GameColoredPrint(L"请选择:\n");
	GameColoredPrint(L"================================\n");
	FastReadInteger(inputVarible);
	switch (inputVarible)
	{
	case 1:
		mov();
		break;
	case 2:
		SwitchItem();
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
		plan();
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
		Exit();
		break;
	default:
		wcout << "输入错误\n";
		break;
	}
}
//********************************
int main()
{
	auto old_cp = GetConsoleOutputCP();
	printf("old_cp:%d\n", old_cp);
	// 设置中文环境
	SetConsoleOutputCP(CP_UTF8);

	auto new_cp = GetConsoleOutputCP();
	printf("new_cp:%d\n", new_cp);
	system("title Persistent Adventure 无尽の冒险");
	join();		// 146
	ReadSave(); // 读取存档
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
void DelayPrint(wchar_t *p)
{
	while (1)
	{
		if (*p != 0)
		{
			wprintf(L"%c", *p++);
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
void FastReadInteger(int &a)
{
	a = 0;
	bool c = false;
	wchar_t s;
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
	DelayPrint(L"");
	wprintf(L"按任意键继续喔~");
	getch();
	wcout << "\r";
}
void GameColoredPrint(const wchar_t p[])
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
		wprintf(L"%c", *p++);
		SetConsoleTextColor(15);
	}
}
int GenerateRandomNumber(int a, int b)
{
	// 随机函数，从数a~b之间随机取数
	return rand() % b + a;
}
void WriteSave()
{
	std::wofstream w;
	std::wofstream outfile;
	w.open("无尽の冒险（请勿删除否则导致游戏崩溃）.egame");
	w.write((const wchar_t *)(&player), sizeof(player));
	w.write((const wchar_t *)(&wor), sizeof(wor));
	w.write((const wchar_t *)(&c_std), sizeof(c_std));
	w.write((const wchar_t *)(&monster), sizeof(monster));
	w.close();
}
void ReadSave()
{
	std::wifstream r;
	r.open("无尽の冒险（请勿删除否则导致游戏崩溃）.egame");
	if (!r.is_open())
	{
		//          自定义人物
		zdy_player();
		return;
	}
	r.read((wchar_t *)(&player), sizeof(player));
	r.read((wchar_t *)(&wor), sizeof(wor));
	r.read((wchar_t *)(&c_std), sizeof(c_std));
	r.read((wchar_t *)(&monster), sizeof(monster));
	r.close();
}
void Exit()
{
	if (MessageBox(NULL, TEXT("是否要保存并退出游戏？"), TEXT("无尽の冒险"), MB_ICONQUESTION | MB_YESNO) == IDNO)
		return;
	WriteSave();
	DelayPrint(L"感谢各位玩家大大的支持！拜拜~");
	exit(0);
}
//...配置 ..........==============================
