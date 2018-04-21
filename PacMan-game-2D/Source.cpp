//the sound is commented

#include<iostream>
#include<sstream>
#include<windows.h>
#include<random>
#include <fstream>
#include <string>

using namespace std;

char arrows[4];
bool rule = false;
HANDLE  hConsole;
string player_name;

int  cheker = 0, lives = 3, r = -1, t = 0, counter_of_points = 0, test = 0;
char level_btw = 'A', pac = 2, level = 'A', pac_direction, maps[32][39], start[18][43], level_shape[9][38];
ifstream map1("mapone.txt"), map2("maptwo.txt"), map3("mapthree.txt"), welc("welcome.txt");
ifstream level1("levelone.txt"), level2("leveltwo.txt"), level3("levelthree.txt");

int wall = 221, wall_of_map = 178, up = 24, down = 25, right1 = 26, left1 = 27, x1_direction_ofpac = 25, y1_direction_ofpac = 15, x3_direction_ofpac = 16, y3_direction_ofpac = 2;
int tim = 11, rotationA = 55, rotationB = 66, rotationC = 77, x_edge = 18, y_right_edge = 28, y_left_edge = 1, x1_enm1 = 17, x1_enm2 = 17, x1_enm3 = 19, x1_enm4 = 19, y1_enm1 = 12;
int y1_enm2 = 17, y1_enm3 = 12, y1_enm4 = 17, x3_enm1 = 10, x3_enm2 = 9, x3_enm3 = 17, x3_enm4 = 27, x3_enm5 = 27, y3_enm1 = 4, y3_enm2 = 25, y3_enm3 = 25, y3_enm4 = 4, y3_enm5 = 25, all_ghosts = -1;
int number_of_ghost_inlevel_one = 4, number_of_ghost_inlevel_three = 5, start_shape1 = 206, start_shape3 = 1, shape_of_pac = 2, start_shape2 = 219, tes = 1;
int rest = 0, rest_of_rotation = -1, number_of_lives = 3;

void gotoxy(short x, short y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(hStdout, position);
}
class welcome_Maps_and_shapes
{
public:
	void arrows2(char(&arrows)[4])
	{
		arrows[0] = up;
		arrows[1] = down;
		arrows[2] = right1;
		arrows[3] = left1;
	}
	void chose_from_menu()
	{

		string Menu[4] = { "- Start Game  ", "- Instructions", "- Designers", "- Exit        " };
		int pointer = 0;
		welcome_shape();
		//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\pacman_beginning.wav"), NULL, SND_ASYNC);
		while (true)
		{
			for (int i = 0; i < 4; ++i)
			{
				if (i == pointer)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | 0);
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15 | 0);
				}
				gotoxy(1, i + 14);
				cout << Menu[i] << endl;
			}
			while (true)
			{

				if (GetAsyncKeyState(VK_UP) != 0)
				{
					pointer -= 1;
					if (pointer == -1)
					{
						pointer = 3;
					}
					break;
				}
				else if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					pointer += 1;
					if (pointer == 4)
					{
						pointer = 0;
					}
					break;
				}
				else if (GetAsyncKeyState(VK_RETURN) != 0)
				{
				//	PlaySound(NULL, NULL, SND_ASYNC);

					switch (pointer)
					{
					case 0:
					{
							  rule = true;
							  system("cls");
							  level_shap_change();
							  gotoxy(2, 4);
							  between_level_show();
							  cin.ignore();
							  getline(cin, player_name);
							  system("cls");
					}
						break;
					case 1:
					{
							  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | 0);
							  gotoxy(44, 4); cout << " Use " << arrows[0] << " : move PAC-MAN TO UP    " << endl;
							  gotoxy(44, 6); cout << " Use " << arrows[1] << " : move PAC-MAN TO DOWN   " << endl;
							  gotoxy(44, 8);  cout << " Use " << arrows[2] << " : move PAC-MAN TO RIGHT " << endl;
							  gotoxy(44, 10); cout << " Use " << arrows[3] << " : move PAC-MAN TO LEFT  " << endl;
							  gotoxy(44, 12); cout << " Eat Dots whithout Touch Ghosts " << endl;
							  gotoxy(44, 14); cout << " Eat Power Dots to Eat ghosts " << endl;
							  Sleep(7000);
							  system("cls");
							  welcome_shape();

					}
						break;
					case 2:
					{
							  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14 | 0);
							  gotoxy(44, 8);  cout << " - Amr Ayman Ayoub      --> SEC. 11" << endl;
							  gotoxy(44, 10);  cout << " - Mohamed Ahmed Ramzy  --> SEC. 13" << endl;
							  gotoxy(44, 12);  cout << " - Mohamed Fouad Ahmed  --> SEC. 14" << endl;
							  Sleep(2000);
							  system("cls");
							  welcome_shape();
					}
						break;
					case 3:
					{
							  exit(1);
					}
						break;
					}
					break;
				}
			}
			if (rule == true)
				break;
			Sleep(150);
		}
	}
	void welcome_shape(){
		system("color 0e");
		for (int i = 0; i<18; i++)
		{
			for (int j = 0; j < 43; j++)
			{
				welc >> start[i][j];
				if (start[i][j] == '+') start[i][j] = ' ';
				if (start[i][j] == '@') start[i][j] = start_shape1;
				if (start[i][j] == '#') start[i][j] = start_shape2;
				if (start[i][j] == '^') start[i][j] = start_shape3;
				cout << start[i][j];
			}
			cout << endl;
		}
	}
	void get_level_maps()
	{
		for (int i = 0; i < 32; i++)
		{
			for (int j = 0; j < 39; j++)
			{
				if (level == 'A') { map1 >> maps[i][j]; }
				else if (level == 'B'){ map2 >> maps[i][j]; }
				else if (level == 'C'){ map3 >> maps[i][j]; }
				if (maps[i][j] == '+'){ maps[i][j] = ' '; }
			}
		}
	}
	void Print_Of_map()
	{
		for (int i = 0; i<32; i++)
		{
			for (int j = 0; j<39; j++)
			{
				if (maps[i][j] == '$'){
					maps[i][j] = 221;
					SetConsoleTextAttribute(hConsole, 14);
				}
				else if (maps[i][j] == '#')
				{
					maps[i][j] = 178;
					SetConsoleTextAttribute(hConsole, 3);
				}
				else if (maps[i][j] == '.' || maps[i][j] == '-' || maps[i][j] == '|' || maps[i][j] == 'O')
				{
					SetConsoleTextAttribute(hConsole, 15);
				}
				else if ((maps[i][j] == '1'&&maps[i][j + 1] != '5') || maps[i][j] == '2' || maps[i][j] == '3' || maps[i][j] == '0')
				{
					SetConsoleTextAttribute(hConsole, 15);
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 10);
				}
				cout << maps[i][j];
			}
			cout << endl;
		}
	}
	void level_shap_change()
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 38; j++)
			{
				if (level_btw == 'A') { level1 >> level_shape[i][j]; }
				else if (level_btw == 'B'){ level2 >> level_shape[i][j]; }
				else if (level_btw == 'C'){ level3 >> level_shape[i][j]; }
				if (level_shape[i][j] == '+'){ level_shape[i][j] = ' '; }
			}
		}
	}
	void between_level_show()
	{
		system("color 4f");
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 38; j++)
			{
				if (level_shape[i][j] == '#') { level_shape[i][j] = 178; }
				cout << level_shape[i][j];
			}
			cout << endl;
		}
		for (int color_change = 0; color_change < 10; color_change++)
		{
			Sleep(200);
			if (color_change % 2 == 0)
				system("color 8e");
			if (color_change % 2 == 1)
				system("color 5a");
		}
		system("color 0e");
	}
	void face_organize(int x, int y)
	{
		if (t >0) {
			SetConsoleTextAttribute(hConsole, 14);
			gotoxy(y, x); cout << pac;
		}
		else if (t <= 0){
			SetConsoleTextAttribute(hConsole, 13);
			gotoxy(y, x); cout << "*";
		}
	}
};
class pacman
{
private:
	int xcor, ycor;
	char pacman_face;
	welcome_Maps_and_shapes face_show;
public:
	void Pacman()
	{
		SetConsoleTextAttribute(hConsole, 14);
		if (level == 'A' || level == 'B'){ xcor = x1_direction_ofpac, ycor = y1_direction_ofpac; }
		else if (level == 'C'){ xcor = x3_direction_ofpac, ycor = y3_direction_ofpac; };
		pacman_face = shape_of_pac;
		gotoxy(ycor, xcor); cout << pacman_face;
	}
	void space_organize(int &xcor, int &ycor)
	{
		gotoxy(ycor, xcor); cout << " ";
		maps[xcor][ycor] = ' ';
	}
	void super_position()
	{
		t = 11;
		if (level == 'A') { r = rotationA; }
		else if (level == 'B') { r = rotationB; }
		else if (level == 'C') { r = rotationC; }
	}
	void walk_throw_other_side(int &xcor, int &ycor)
	{
		gotoxy(ycor, xcor); cout << " ";
		maps[xcor][ycor] = ' ';
		if (ycor > xcor){ ycor = y_left_edge; }
		else
		{
			ycor = y_right_edge;
		}
		gotoxy(ycor, xcor); cout << pacman_face;
	}
	void insert_direction(){
		SetConsoleTextAttribute(hConsole, 14);
		if (GetAsyncKeyState(VK_LEFT))
		{
			if (maps[xcor][ycor - 1] != '²'){ pac_direction = 'l'; }
		}
		else if (GetAsyncKeyState(VK_RIGHT))
		{
			if (maps[xcor][ycor + 1] != '²'){ pac_direction = 'r'; }
		}
		else if (GetAsyncKeyState(VK_UP))

		{
			if (maps[xcor - 1][ycor] != '²'){ pac_direction = 'u'; }

		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (maps[xcor + 1][ycor] != '²'){ pac_direction = 'd'; }

		}
	}
	void pacman_move(int & x, int & y)
	{
		insert_direction();
		if (pac_direction == 'l'){
			if (xcor == x_edge &&  ycor == y_left_edge)
			{
				walk_throw_other_side(xcor, ycor);
			}
			else if ((maps[xcor][ycor - 1] == ' ') || (maps[xcor][ycor - 1] == '.') || (maps[xcor][ycor - 1] == 'O'))
			{
				if (maps[xcor][ycor - 1] == '.') {
					counter_of_points += 10;
					//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\pacman_chomp(1).wav"), NULL, SND_ASYNC);
				}
				else if (maps[xcor][ycor - 1] == 'O') { super_position(); }
				else if (maps[xcor][ycor - 1] == ' ') {
					//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\Pacman_Siren_Sound_Effect.wav"), NULL, SND_ASYNC);
				}
				space_organize(xcor, ycor);
				ycor--;
				gotoxy(ycor, xcor); cout << pacman_face;
			}
			else if (maps[xcor][ycor - 1] == '*')
			{
				test = tes;
				space_organize(xcor, ycor);
				ycor--;
				face_show.face_organize(xcor, ycor);
			}
		}
		else if (pac_direction == 'r'){
			if (ycor == y_right_edge && xcor == x_edge)
			{
				walk_throw_other_side(xcor, ycor);
			}
			else if ((maps[xcor][ycor + 1] == ' ') || (maps[xcor][ycor + 1] == '.') || (maps[xcor][ycor + 1] == 'O'))
			{
				if (maps[xcor][ycor + 1] == '.') {
					counter_of_points += 10;
					//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\pacman_chomp(1).wav"), NULL, SND_ASYNC);
				}
				else if (maps[xcor][ycor + 1] == 'O') { super_position(); }
				else if (maps[xcor][ycor + 1] == ' ') {
					//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\Pacman_Siren_Sound_Effect.wav"), NULL, SND_ASYNC);
				}
				space_organize(xcor, ycor);
				ycor++;
				gotoxy(ycor, xcor); cout << pacman_face;
			}
			else if (maps[xcor][ycor + 1] == '*')
			{
				test = tes;
				space_organize(xcor, ycor);
				ycor++;
				face_show.face_organize(xcor, ycor);
			}
		}
		else if (pac_direction == 'u'){
			if ((maps[xcor - 1][ycor] == ' ') || (maps[xcor - 1][ycor] == '.') || (maps[xcor - 1][ycor] == 'O'))
			{
				if (maps[xcor - 1][ycor] == '.'){
					counter_of_points += 10;
					//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\pacman_chomp(1).wav"), NULL, SND_ASYNC);
				}
				else if (maps[xcor - 1][ycor] == 'O'){ super_position(); }
				else if (maps[xcor - 1][ycor] == ' ') {
					//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\Pacman_Siren_Sound_Effect.wav"), NULL, SND_ASYNC);
				}
				space_organize(xcor, ycor);
				xcor--;
				gotoxy(ycor, xcor); cout << pacman_face;
			}
			else if (maps[xcor - 1][ycor] == '*')
			{
				test = tes;
				space_organize(xcor, ycor);
				xcor--;
				face_show.face_organize(xcor, ycor);
			}
		}
		else if (pac_direction == 'd'){
			if ((maps[xcor + 1][ycor] == ' ') || (maps[xcor + 1][ycor] == '.') || (maps[xcor + 1][ycor] == 'O'))
			{
				if (maps[xcor + 1][ycor] == '.') {
					counter_of_points += 10;
					//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\pacman_chomp(1).wav"), NULL, SND_ASYNC);
				}
				else if (maps[xcor + 1][ycor] == 'O'){ super_position(); }
				else if (maps[xcor + 1][ycor] == ' ') {
					//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\Pacman_Siren_Sound_Effect.wav"), NULL, SND_ASYNC);
				}
				space_organize(xcor, ycor);
				xcor++;
				gotoxy(ycor, xcor); cout << pacman_face;
			}
			else if (maps[xcor + 1][ycor] == '*')
			{
				test = tes;
				space_organize(xcor, ycor);
				xcor++;
				face_show.face_organize(xcor, ycor);
			}
		}
		x = xcor;
		y = ycor;
	}
};
class pacman_enemies{
private:
	char enemy, last;
	int xen, yen, enemy_dirction, probabilty, enemy_number;
public:
	void blocks_organize(int &xen, int&yen)
	{
		SetConsoleTextAttribute(hConsole, 13);
		last = maps[xen][yen];
		maps[xen][yen] = enemy;
		gotoxy(yen, xen); cout << enemy;
	}
	void ghost_walk_throw_other_side(int &xen, int &yen)
	{
		SetConsoleTextAttribute(hConsole, 13);
		gotoxy(yen, xen); cout << " ";
		if (yen > xen){ yen = y_left_edge; }
		else
		{
			yen = y_right_edge;
		}
		gotoxy(yen, xen); cout << enemy;
	}
	void set_position(pacman_enemies enemys[], int size_of_enemy, int variable)
	{
		SetConsoleTextAttribute(hConsole, 13);
		enemy = '*';
		if (level == 'A' || level == 'B') {
			for (int i = 0; i < 4; i++)
			{
				if (i == 0 && i == variable || i == 0 && variable == all_ghosts)
				{
					enemys[i].xen = x1_enm1;
					enemys[i].yen = y1_enm1;
					enemys[i].enemy = '*';
					enemys[i].last = ' ';
					gotoxy(enemys[i].yen, enemys[i].xen); cout << enemy;
				}
				if (i == 1 && i == variable || i == 1 && variable == all_ghosts)
				{
					enemys[i].xen = x1_enm2;
					enemys[i].yen = y1_enm2;
					enemys[i].enemy = '*';
					enemys[i].last = ' ';
					gotoxy(enemys[i].yen, enemys[i].xen); cout << enemy;
				}
				if (i == 2 && i == variable || i == 2 && variable == all_ghosts)
				{
					enemys[i].xen = x1_enm3;
					enemys[i].yen = y1_enm3;
					enemys[i].enemy = '*';
					enemys[i].last = ' ';
					gotoxy(enemys[i].yen, enemys[i].xen); cout << enemy;
				}
				if (i == 3 && i == variable || i == 3 && variable == all_ghosts)
				{
					enemys[i].xen = x1_enm4;
					enemys[i].yen = y1_enm4;
					enemys[i].enemy = '*';
					enemys[i].last = ' ';
					gotoxy(enemys[i].yen, enemys[i].xen); cout << enemy;
				}
			}
		}
		if (level == 'C') {
			for (int i = 0; i < 5; i++)
			{
				if (i == 0 && i == variable || i == 0 && variable == all_ghosts)
				{
					enemys[i].xen = x3_enm1;
					enemys[i].yen = y3_enm1;
					enemys[i].enemy = '*';
					enemys[i].last = ' ';
					gotoxy(enemys[i].yen, enemys[i].xen); cout << enemy;
				}
				if (i == 1 && i == variable || i == 1 && variable == all_ghosts)
				{
					enemys[i].xen = x3_enm2;
					enemys[i].yen = y3_enm2;
					enemys[i].enemy = '*';
					enemys[i].last = ' ';
					gotoxy(enemys[i].yen, enemys[i].xen); cout << enemy;
				}
				if (i == 2 && i == variable || i == 2 && variable == all_ghosts)
				{
					enemys[i].xen = x3_enm3;
					enemys[i].yen = y3_enm3;
					enemys[i].enemy = '*';
					enemys[i].last = ' ';
					gotoxy(enemys[i].yen, enemys[i].xen); cout << enemy;
				}
				if (i == 3 && i == variable || i == 3 && variable == all_ghosts)
				{
					enemys[i].xen = x3_enm4;
					enemys[i].yen = y3_enm4;
					enemys[i].enemy = '*';
					enemys[i].last = ' ';
					gotoxy(enemys[i].yen, enemys[i].xen); cout << enemy;
				}
				if (i == 4 && i == variable || i == 4 && variable == all_ghosts)
				{
					enemys[i].xen = x3_enm5;
					enemys[i].yen = y3_enm5;
					enemys[i].enemy = '*';
					enemys[i].last = ' ';
					gotoxy(enemys[i].yen, enemys[i].xen); cout << enemy;
				}
			}
		}
	}
	void enemy_move(int & x, int & y) {
		SetConsoleTextAttribute(hConsole, 15);
		if (enemy_dirction == 0 && (maps[xen][yen - 1] != '²' && maps[xen][yen - 1] != '*'))
		{
			if (xen == x_edge&& yen == y_left_edge)
			{
				ghost_walk_throw_other_side(xen, yen);
			}
			else if ((maps[xen][yen - 1] == ' ') || (maps[xen][yen - 1] == '.') || (maps[xen][yen - 1] == 'O') || (maps[xen][yen - 1] == '-') || (maps[xen][yen - 1] == '|'))
			{
				maps[xen][yen] = last;
				gotoxy(yen, xen); cout << last;
				yen--;
				blocks_organize(xen, yen);
			}
		}
		else if (enemy_dirction == 1 && (maps[xen][yen + 1] != '²' && maps[xen][yen + 1] != '*'))
		{
			if ((xen == x_edge) && (yen == y_right_edge))
			{
				ghost_walk_throw_other_side(xen, yen);
			}
			else if ((maps[xen][yen + 1] == ' ') || (maps[xen][yen + 1] == '.') || (maps[xen][yen + 1] == 'O') || (maps[xen][yen + 1] == '-') || (maps[xen][yen + 1] == '|'))
			{
				maps[xen][yen] = last;
				gotoxy(yen, xen); cout << last;
				yen++;
				blocks_organize(xen, yen);
			}
		}
		else if (enemy_dirction == 2 && (maps[xen - 1][yen] != '²' && maps[xen - 1][yen] != '*'))
		{
			if ((maps[xen - 1][yen] == ' ') || (maps[xen - 1][yen] == '.') || (maps[xen - 1][yen] == 'O') || (maps[xen - 1][yen] == '-') || (maps[xen - 1][yen] == '|'))
			{
				maps[xen][yen] = last;
				gotoxy(yen, xen); cout << last;
				xen--;
				blocks_organize(xen, yen);
			}
		}
		else if (enemy_dirction == 3 && (maps[xen + 1][yen] != '²' && maps[xen + 1][yen] != '*'))
		{
			if ((maps[xen + 1][yen] == ' ') || (maps[xen + 1][yen] == '.') || (maps[xen + 1][yen] == 'O') || (maps[xen + 1][yen] == '-') || (maps[xen + 1][yen] == '|'))
			{
				maps[xen][yen] = last;
				gotoxy(yen, xen); cout << last;
				xen++;
				blocks_organize(xen, yen);
			}
		}
		else
		{
			random_device rd;
			mt19937 gen(rd());
			uniform_int_distribution<> dis(0, 3);
			enemy_dirction = dis(gen);
		}
		x = xen;
		y = yen;
	}
};
class game_organize
{
private:
	int x_of_pac, y_of_pac, x_of_enemy, y_of_enemy, xenemy[5], yenemy[5], enemy_number;
	char emotion = 3;
	welcome_Maps_and_shapes map, stat;
	pacman pac;
	pacman_enemies enm[5], ghosts;
public:
	void display_level()
	{
		system("color 0e");
		map.get_level_maps();
		map.Print_Of_map();
		pac.Pacman();
		ghosts.set_position(enm, enemy_number, all_ghosts);
	}
	void indicators_show()
	{
		SetConsoleTextAttribute(hConsole, 15);
		gotoxy(9, 3); cout << counter_of_points;
		gotoxy(15, 1); cout << player_name;
		if (((r % 5 == 0 && t > 0 && level == 'A')) || ((r % 6 == 0 && t > 0 && level == 'B')) || ((r % 7 == 0 && t > 0 && level == 'C')))
		{
			t--; gotoxy(13, 4); if (t >= 10){ cout << t; }
			else { cout << t << " "; }
		}
		SetConsoleTextAttribute(hConsole, 12);
		if (lives == 3){ gotoxy(23, 3); cout << emotion << " " << emotion << " " << emotion; }
		if (lives == 2){ gotoxy(23, 3); cout << emotion << " " << emotion << "   "; }
		if (lives == 1){ gotoxy(23, 3); cout << emotion << "    "; }
	}
	void indicators_reset()
	{
		t = rest, r = rest_of_rotation;
		counter_of_points = rest;
		lives = number_of_lives;
		if (level == 'A') { level = 'B'; }
		else if (level == 'B') { level = 'C'; }
	}
	void speed_game(){
		if (r >= 0){ r--; }
		if (level == 'A'){ Sleep(180); }
		if (level == 'B') { Sleep(155); }
		if (level == 'C') { Sleep(130); }
	}
	void between_level_change()
	{
		Sleep(2000);
		system("CLS");
		if (level_btw == 'A') { level_btw = 'B'; }
		else if (level_btw == 'B') { level_btw = 'C'; }
		map.level_shap_change();
		if (level == 'A')
		{
			gotoxy(5, 2); cout << "Your score in Level 1 = " << counter_of_points << endl;
		}
		if (level == 'B')
		{
			gotoxy(5, 2); cout << "Your score in Level 2 = " << counter_of_points << endl;
		}
		indicators_reset();
		gotoxy(2, 4); map.between_level_show();
		//Sleep(2000);
		system("CLS");
	}
	void game_complete()
	{
		if (lives<1){
			gotoxy(5, 7);
			cout << "        ___       _______   _______   _______   ______ _  " << endl;
			cout << "       |***|     |*******| |*******| |*******| |****_**|  " << endl;
			cout << "       |***|     |***_***| |**_____| |****___| |***| |*|  " << endl;
			cout << "       |***|     |**| |**| |*|_____  |***|___  |***|_|*|_ " << endl;
			cout << "       |***|___  |**|_|**| |_____ *| |****___| |****__**|" << endl;
			cout << "       |*******| |*******|  _____|*| |***|___  |***|  |*|" << endl;
			cout << "       |*******| |*******| |*******| |*******| |***|  |*|" << endl;
			for (int color_change = 0; color_change < 10; color_change++)
			{
				Sleep(200);
				if (color_change % 2 == 0)
					system("color f4");
				if (color_change % 2 == 1)
					system("color 4f");
			}

		}
		else
		{
			gotoxy(5, 7);
			cout << "    _     _   __   __    _   __    _   _______   ______   " << endl;
			cout << "        |*| _ |*| |**| |**|  |*| |**|  |*| |*******| |******|  " << endl;
			cout << "        |*||*||*| |**| |***|_|*| |***|_|*| |****___| |***| ||  " << endl;
			cout << "        |*******| |**| |*******| |*******| |***|___  |***|_||_ " << endl;
			cout << "        |*******| |**| |**_****| |**_****| |***____| |****_***|" << endl;
			cout << "        |*******| |**| |*| |***| |*| |***| |***|___  |***|  |*|" << endl;
			cout << "        |**| |**| |**| |*|  |**| |*|  |**| |*******| |***|  |*|" << endl;

			for (int color_change = 0; color_change < 10; color_change++)
			{
				Sleep(200);
				if (color_change % 2 == 0)
					system("color f4");
				if (color_change % 2 == 1)
					system("color 4f");
			}

		}
		gotoxy(20, 20); cout << "Your score = " << counter_of_points << endl;

	}
	void the_game_of_pac()
	{
		enemy_number = number_of_ghost_inlevel_one;
		stat.arrows2(arrows);
		stat.chose_from_menu();
		display_level();
		while (lives > 0) {
			if (test == rest)
			{
				for (int i = 0; i < enemy_number; i++)
				{
					enm[i].enemy_move(x_of_enemy, y_of_enemy);
					xenemy[i] = x_of_enemy;
					yenemy[i] = y_of_enemy;
				}
			}
			for (int k = 0; k < enemy_number; k++)
			{
				if (x_of_pac == xenemy[k] && y_of_pac == yenemy[k])
				{
					if (r >= rest)
					{
						maps[xenemy[k]][yenemy[k]] = ' ';
						enm[k].set_position(enm, enemy_number, k);
						counter_of_points += 200;
					}
					else {
						//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\matelpac.wav"), NULL, SND_ASYNC);
						//PlaySound(TEXT("C:\\Users\\Mohamed Ramzy\\Desktop\\sound\\Pacman_Dies_Sound_Effect.wav"), NULL, SND_ASYNC);
						lives--; indicators_show(); pac_direction = ' '; pac.Pacman(); Sleep(2000);
					}
					stat.face_organize(x_of_pac, y_of_pac);
				}
			}
			test = rest;
			pac.insert_direction();
			pac.pacman_move(x_of_pac, y_of_pac);
			speed_game();
			indicators_show();
			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 39; j++)
				{
					if (maps[i][j] == '.') { cheker = 1; }
				}
			}
			if (((cheker == 0) && (level == 'A')) || ((cheker == 0) && (level == 'B')))
			{
				Sleep(2000);
				if (level == 'B'){ enemy_number = number_of_ghost_inlevel_three; }
				between_level_change();
				map.get_level_maps();
				display_level();
				cheker = 1;
				Sleep(2000);
				pac_direction = 'u';
			}
			if ((cheker == 0) && (level == 'C')){ break; }
			cheker = 0;
		}
		system("CLS");
		game_complete();
		while (1){ lives == number_of_lives; }
	}
};
int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	game_organize pacer;
	pacer.the_game_of_pac();
	//system("pause");
	//return 0;
}