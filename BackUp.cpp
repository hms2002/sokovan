// #include <ncurses.h>
// #include <locale.h>
// #include <string>
// #define GYO 10
// #define RETU 11

// #define BOX 3
// #define GOAL 4

// int (*meiro)[RETU];
// int meiro1[GYO][RETU] = {
// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };
// int meiro2[GYO][RETU] = {
// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1},
// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
// };

// int px, py;
// int p2x, p2y;
// int p1Flag;
// int goal_count;
// int count;

// void play_start(void) 
// {
// 	int x, y;
// 	count = 0;
// 	px = 1;
// 	py = 1;
// 	p2x = RETU - 2;
// 	p2y = GYO - 2;
//   p1Flag = 1;
// 	for (y = 0; y < GYO; y++)
// 		for (x = 0; x < RETU; x++)
// 			if (meiro[y][x] == 2)
// 				meiro[y][x] = 0;
// }

// void goal_count_check(void) 
// {
// 	int x, y;
// 	goal_count = 0;
// 	for (y = 0; y < GYO; y++)
// 		for (x = 0; x < RETU; x++)
// 			if (meiro[y][x] == 0)
// 				goal_count++;
// }

// void draw_meiro(void) 
// {
// 	int x, y;
// 	for (y = 0; y < GYO; y++) 
//   {
// 		for (x = 0; x < RETU; x++) 
//     {
// 			if (x == px && y == py) 
//       {
// 				meiro[y][x] = 2;
//         if(p1Flag == 1)
//   				count++;
// 				mvprintw(y, x * 2, "🍎"); // printf("O");
// 			} 
//       else if (x == p2x && y == p2y) 
//       {
// 				meiro[y][x] = 2;
//         if(p1Flag == 0)
//   				count++;
// 				mvprintw(y, x * 2, "🍎"); // printf("O");
// 			} 
//       else if (meiro[y][x] == 0)
// 				mvprintw(y, x * 2, "  "); //
// 			else if (meiro[y][x] == 1)
// 				mvprintw(y, x * 2, "️⬜️");
// 			else if (meiro[y][x] == 2)
// 				mvprintw(y, x * 2, "🔳");
// 		}
// 	}
// 	// mvprintw(GYO,0,"move: ← ↑ → ↓ restart: ESC");  // 🟩 🟩 🟩
// 	// 🟫🟫🟫 ❤️❤️❤️ 🍎🍎🍎🍎
// 	mvprintw(GYO, 0, "move: ←↑→↓ restart: SPACE change: r\n");
// }

// void key_input(void) 
// {
// 	int key;
// 	key = getch();

//   if(p1Flag == 1)
//   {
    
//   	if (key == KEY_UP && meiro[py - 1][px] == 0)
//   		py--;
//   	else if (key == KEY_DOWN && meiro[py + 1][px] == 0)
//   		py++;
//   	else if (key == KEY_LEFT && meiro[py][px - 1] == 0)
//   		px--;
//   	else if (key == KEY_RIGHT && meiro[py][px + 1] == 0)
//   		px++;
//   	else if (key == ' ')
//   		play_start();
//     else if(key == 'r')
//       p1Flag = (++p1Flag) % 2; // r 누르면 플레이어 바뀜
//   	else
//   		key_input();
//   }
//   else
//   {
//     if (key == KEY_UP && meiro[p2y - 1][p2x] == 0)
//   		p2y--;
//   	else if (key == KEY_DOWN && meiro[p2y + 1][p2x] == 0)
//   		p2y++;
//   	else if (key == KEY_LEFT && meiro[p2y][p2x - 1] == 0)
//   		p2x--;
//   	else if (key == KEY_RIGHT && meiro[p2y][p2x + 1] == 0)
//   		p2x++;
//   	else if (key == ' ')
//   		play_start();
//     else if(key == 'r')
//       p1Flag = (++p1Flag) % 2;
//   	else
//   		key_input();
//   }
// }

// int main2(void) 
// {
// 	setlocale(LC_ALL, ""); // UTF 8 출력

// 	initscr(); // ncurses 초기화
// 	keypad(stdscr, TRUE);
// 	noecho();		 // Don't echo any keypresses
// 	curs_set(FALSE); // Don't display a cursor

// 	px = 1;
// 	py = 1;
// 	p2x = RETU - 2;
// 	p2y = GYO - 2;
//   p1Flag = 1;
// 	count = 0;

//   meiro = meiro1;
  
// 	goal_count_check();

// 	while (!(count == goal_count - 1)) 
//   {
//     clear();

// 		draw_meiro();
    
//    // mvprintw(GYO + 3, count, "z");
//    // mvprintw(GYO + 3, goal_count, "z");
    
// 		key_input();

// 		refresh();
// 	}
  
// 	draw_meiro();
// 	mvprintw(GYO + 1, 0, " Sucess !!");

//   getch();

// 	px = 1;
// 	py = 1;
// 	p2x = RETU - 2;
// 	p2y = GYO - 2;
//   p1Flag = 1;
// 	count = 0;

//   meiro = meiro2;
  
// 	goal_count_check();

// 	while (!(count == goal_count - 1)) 
//   {
//     clear();

// 		draw_meiro();
    
//    // mvprintw(GYO + 3, count, "z");
//    // mvprintw(GYO + 3, goal_count, "z");
    
// 		key_input();

// 		refresh();
// 	}
  
  
// 	endwin();
// 	return 0;
// }
