// Copyright (c) 2014, 임경현 (dlarudgus20)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "Includes.h"
#include "Lib.h"
#include "MainFunc.h"

char key[MAX_KEYNUM] = 
{
	'w', // up
	's', // down
	'a', // left
	'd', // right
	'c', // chitem
	'i', // useitem
};

char defaultkey[MAX_KEYNUM] = 
{
	'w', // up
	's', // down
	'a', // left
	'd', // right
	'c', // chitem
	'i', // useitem
};

FILE *in, *out;

char player[] = "※";
char defaultplayer[] = "※";

int x = 0, y = 0, star_x = 0, star_y = 0, moved = 0, score = 0, silver = 0, gold = 0;
bool g_over = false, ifmove = false, gamestart = false;
char ch;

void maininit()
{
	// If loadSettings error occurred
	if (loadSettings() == -1)
		saveSettings();
		
	ch = '\0';
}

void mainprint()
{
	clear();
	//system("title EatStar v0.0.5");
	
	printw("\n ★ Eat Star ★\n\n 최대한 적게 움직여서 화면의 숨겨진 별을 먹으세요!\n 한개의 별을 먹는데 200발자국 이상 움직이면 게임 오버!\n\n");
	printw(" a. 게임 시작\n b. 설정\n c. 정보\n d. 상점\n e. 끝내기\n");
	printw("\n\n ⓒ 2014 Naissoft.\n");
}

int loadscore()
{
	in = fopen("SCORE.NSIII", "rt");
	if (in == NULL)
		return -1;

	fscanf(in, "%d %d %d %d %d %d", &score, &star_x, &star_y, &moved, &x, &y);
	
	fclose(in);
	return 0;
}


int loadSettings()
{
	FILE *loadset = fopen("SETTINGS.NSIII", "rt");
	if (loadset == NULL)
	return -1;
	
	for (int i = 0; i < MAX_KEYNUM; i++)
		fscanf(loadset, "%c ", &key[i]);
	fscanf(loadset, "%s ", player);
	
	fclose(loadset);
	return 0;
}

void saveSettings()
{
	FILE *saveset = fopen("SETTINGS.NSIII", "wt");
	
	for (int i = 0; i < MAX_KEYNUM; i++)
		fprintf(saveset, "%c ", key[i]);
	fprintf(saveset, "%s ", player);
	
	fclose(saveset);
}

void setSettings()
{
	bool quit = false;
	
	do
	{	
		clear();
		printw("\n [ S E T T I N G ]\n\n\n ━━━━━━━━━━━━━━━━━\n a. 조작키 설정\n b. 그래픽\n c. 저장하고 나가기");
		
		switch (getch())
		{
		case 'a':
			clear();
			printw("\n a. 앞으로 이동 %c\n\n b. 뒤로 이동 %c\n\n c. 오른쪽으로 이동 %c\n\n d. 왼쪽으로 이동 %c\n\n e. 아이템 전환 %c\n\n f. 아이템 사용 %c\n\n q. 나가기\n\n", key[0], key[1], key[2], key[3], key[4], key[5]);
				
			switch (getch())
			{
				case 'a':
					clear();
					printw("앞으로 이동의 새 조작키를 입력하십시오 : ");
					setKeycheck(0);
					break;
				case 'b':
					clear();
					printw("뒤로 이동의 새 조작키를 입력하십시오 : ");
					setKeycheck(1);
					break;
				case 'c':
					clear();
					printw("오른쪽으로 이동의 새 조작키를 입력하십시오 : ");
					setKeycheck(2);
					break;
				case 'd':
					clear();
					printw("왼쪽으로 이동의 새 조작키를 입력하십시오 : ");
					setKeycheck(3);
					break;
				case 'e':
					clear();
					printw("아이템 전환의 새 조작키를 입력하십시오 : ");
					setKeycheck(4);
					break;
				case 'f':
					clear();
					printw("아이템 사용의 새 조작키를 입력하십시오 : ");
					setKeycheck(5);
					break;
				case 'q':
					break;
			}
			break;
		case 'c' :
			saveSettings(); 
			quit = true;
			break;
		}
	} while (!quit);
}
void keyproc()
{
	ch = getch();
	ifmove = TRUE;

	if (ch == key[0]) { // up
		if (y > MIN_Y) {
			y--;
			moved++;
		}
	}
	if (ch == key[1]) { // down
		if (y < MAX_Y) {
			y++;
			moved++;
		}
	}
	if (ch == key[2]) { // left
		if (x > MIN_X) {
			x--;
			moved++;
		}
	}
	if (ch == key[3]) { // right
		if (x < MAX_X) {
			x++;
			moved++;
		}
	}
}

void setstar()
{
	srand((unsigned)time(NULL));

	star_x = rand() % MAX_X + 1;
	star_y = rand() % MAX_Y + 1;
}

void print()
{
	if (ifmove)
	{
		clear();

		gotoxy(0, 0);
		printw("EatStar v0.0.5");

		gotoxy(x, y);
		printw("%s", player);

		starhint();

		printbox();

		gotoxy(3, 23);
		printw("%2d 발자국, 점수 %d ┃ ⓢ %08d  ⓖ %08d", moved, score, silver, gold);
	}
	gotoxy(0, 0);
	ifmove = false;
}

void printbox()
{
	int i;

	gotoxy(0, 22), printw("┏");
	for (i = 1; i < 77; i += 2) printw("━");
	gotoxy(78, 22), printw("┓");

	gotoxy(0, 23), printw("┃");
	gotoxy(78, 23), printw("┃");

	gotoxy(0, 24), printw("┗");
	for (i = 1; i < 77; i += 2) printw("━");
	gotoxy(78, 24), printw("┛");
}

int savescore()
{
	out = fopen("SCORE.NSIII", "wt");
	if (out == NULL)
		return -1;

	fprintf(out, "%d %d %d %d %d %d", score, star_x, star_y, moved, x, y);

	fclose(in);
	return 0;
}

void gameover()
{
	clear();
	printw(" 게임 오버!\n\n ━━━━━━━━━━\n %d점을 획득했습니다.\n", score);
	g_over = TRUE;
	printw("\n 메인 메뉴로 돌아갑니다. . .");
	usleep(1000);
}

void pausemenu()
{
	if (ch == 27)
	{
		savescore();
		clear();
		printw("\n [ P A U S E ]\n\n\n 점수 : %d점, %d 발자국\n\n %d 발자국 이동 가능\n\n ━━━━━━━━━━━━━━━━━\n a. 메인 메뉴로 (점수는 저장되었습니다).\n b. 돌아가기\n", score, moved, MAXMOVED - moved);

		switch (getch())
		{
		case 'a':
			g_over = TRUE;
			break;
		case 'b':
			return;
			break;
		default:
			return;
			break;
		}
	}
}

void starhint()
{
	gotoxy(72, 0);

	if (x + 5 >= star_x && y + 5 >= star_y && x - 5 <= star_x && y - 5 <= star_y)
	{
		printw("●●●●");
	}
	else if (x + 10 >= star_x && y + 10 >= star_y && x - 10 <= star_x && y - 10 <= star_y)
	{
		printw("○●●●");
	}
	else if (x + 15 >= star_x && y + 15 >= star_y && x - 15 <= star_x && y - 15 <= star_y)
	{
		printw("○○●●");
	}
	else if (x + 20 >= star_x && y + 20 >= star_y && x - 20 <= star_x && y - 20 <= star_y)
	{
		printw("○○○●");
	}
	else if (x + 30 >= star_x && y + 30 >= star_y && x - 30 <= star_x && y - 30 <= star_y)
	{
		printw("○○○○");
	}

	gotoxy(0, 0);
}

void printstar()
{
	gotoxy(star_x, star_y);
	printw("★");
}

void setKeycheck(int keynum)
{
	scanf(" %c", &key[keynum]);
	
	for (int i = 0; i < MAX_KEYNUM; i++)
		if (i != keynum)
			if (key[i] == key[keynum])
				key[keynum] = defaultkey[keynum];
}

void shop()
{
	int s_num, g_num;
	
	while (1)
	{
		clear();
		printw("\n [ S H O P ]\n\n\n ━━━━━━━━━━━━━━━━━\n a. 환전\n b. 아이템 구매\n c. 나가기");
		switch (getch())
		{
		case 'a':
			clear();
			printw("\n 1ⓢ = %d점, 1ⓖ = %dⓢ", S_CH, G_CH);
			printw("\n\n 현재 보유 금액 : %08d점, %08dⓢ, %08dⓖ", score, silver, gold);
			printw("\n\n 어떻게 환전하시겠습니까?\n a. 점수 -> ⓢ\n b. ⓢ -> ⓖ");
			switch (getch())
			{
				case 'a':
					printw("\n\n 환전할 ⓢ의 개수를 선택해 주십시오 :");
					scanf("%d", &s_num);
					if (score >= s_num * S_CH)
					{
						score -= s_num * S_CH;
						silver += s_num;
					}
					else printw(" 점수가 부족합니다!\n"), usleep(1000); 
					break;
				case 'b': 
					printw("\n\n 환전할 ⓖ의 개수를 선택해 주십시오 :");
					scanf("%d", &g_num);
					if (s_num >= g_num * G_CH)
					{
						silver -= g_num * G_CH;
						gold += g_num;
					}
					else printw(" ⓢ가 부족합니다!\n"), usleep(1000); 
					break;
			}
			break;
		case 'c':
			return;
			break;
		}
	}
}
