#include <ncurses.h>
#include <locale.h>
#include <string>
#include <time.h>


#define GYO 10
#define RETU 11

#define PATH 0
#define WALL 1
#define BOX 2
#define GOAL 3
#define GOALBOX 4
#define P1 4

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

bool push_box(int _x, int _y, int dir);

int px, py;
int goal_count;
int count;
int (*meiro)[RETU];
int stage = 1;
int meiro1[GYO][RETU] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 2, 3, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 2, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int meiro1BackUp[GYO][RETU] ={
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 2, 3, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 2, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int meiro2BackUp[GYO][RETU] = {
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
{1, 0, 0, 2, 3, 0, 0, 1, 3, 0, 1},
{1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1},
{1, 0, 0, 0, 2, 0, 0, 1, 0, 0, 1},
{1, 0, 0, 1, 1, 1, 0, 2, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
class Memory
{
public:
  int x, y;
  bool youPushBox;
  int pushDir;
public:
  Memory(int _x, int _y, bool _youPushBox, int _pushDir)
  {
    x = _x;
    y = _y;
    youPushBox = _youPushBox;
    pushDir = _pushDir;
  }
};

Memory * memoryStack[100];
int top = -1;

void save_action(int _x, int _y, bool _youPushBox, int _pushDir)
{
  Memory* memory = new Memory(_x, _y, _youPushBox, _pushDir);
  memoryStack[++top] = memory;
}

void back_to_save()
{
  meiro[py][px] = 0;
  px = memoryStack[top]->x;
  py = memoryStack[top]->y;
  if(memoryStack[top]->youPushBox)
  {
    int toX = px, toY = py, backDir = LEFT;
    switch(memoryStack[top]->pushDir)
    {
      case LEFT:
        backDir = RIGHT;
        toX-=2;
      break;
      case RIGHT:
        backDir = LEFT;
        toX+=2;
      break;
      case UP:
        backDir = DOWN;
        toY-=2;
      break;
      case DOWN:
        backDir = UP;
        toY+=2;
      break;
    }
    push_box(toX, toY, backDir);
  }
  delete(memoryStack[top--]);
}

void memory_clear()
{
  while(top > -1)
    delete(memoryStack[top--]);
}

bool push_box(int _x, int _y, int dir)
{
  int toX = _x, toY = _y;
  
  switch(dir)
  {
    case LEFT:
      toX--;
    break;
    case RIGHT:
      toX++;
    break;
    case UP:
      toY--;
    break;
    case DOWN:
      toY++;
    break;
  }
  if(meiro[_y][_x] == GOALBOX)
  {
    meiro[toY][toX] = BOX;
    meiro[_y][_x] = GOAL;
    count--;
    return true;
  }
  switch(meiro[toY][toX])
  {
    case PATH:
      meiro[toY][toX] = BOX;
      meiro[_y][_x] = PATH;
      return true;
    break;
    case GOAL:
      meiro[toY][toX] = GOALBOX;
      meiro[_y][_x] = PATH;
      count++;
      return true;
    break;
  }
  return false;
}


void play_start(void) 
{
	int x, y;
	count = 0;
	px = 1;
	py = 1;

  int (*targetLevel)[RETU] = NULL;
  switch(stage)
  {
  case 1:
    targetLevel = meiro1BackUp;
  break;
  case 2:
    targetLevel = meiro2BackUp;
  break;
  }
  
	for (y = 0; y < GYO; y++)
		for (x = 0; x < RETU; x++)
			meiro[y][x] = targetLevel[y][x];
  memory_clear();
}

void goal_count_check(void) 
{
	int x, y;
	goal_count = 0;
	for (y = 0; y < GYO; y++)
		for (x = 0; x < RETU; x++)
			if (meiro[y][x] == GOAL)
				goal_count++;
}

void draw_meiro(void) 
{
	int x, y;
	for (y = 0; y < GYO; y++) 
  {
		for (x = 0; x < RETU; x++) 
    {
			if (x == px && y == py) 
      {
				meiro[y][x] = P1;
				mvprintw(y, x * 2, "🍎"); // printf("O");
			} 
      else if (meiro[y][x] == PATH)
				mvprintw(y, x * 2, "  "); //
			else if (meiro[y][x] == WALL)
				mvprintw(y, x * 2, "️⬜️");
			else if (meiro[y][x] == BOX)
				mvprintw(y, x * 2, "️☆");
			else if (meiro[y][x] == GOAL)
				mvprintw(y, x * 2, "️★");
			else if (meiro[y][x] == GOALBOX)
				mvprintw(y, x * 2, "️✪");
		}
	}
	// mvprintw(GYO,0,"move: ← ↑ → ↓ restart: ESC");  // 🟩 🟩 🟩
	// 🟫🟫🟫 ❤️❤️❤️ 🍎🍎🍎🍎 ☆☆☆☆☆ ★★★★★ ✪✪✪✪✪
	mvprintw(GYO, 0, "move: ←↑→↓ restart: SPACE\n");
}

void key_input(void) 
{
	int key;
	key = getch();
  if (key == KEY_UP && (meiro[py - 1][px] == PATH || meiro[py - 1][px] == BOX))
  {
    save_action(px, py, false, UP);
    switch(meiro[py - 1][px])
    {
      case PATH:
        meiro[py][px] = 0;
        py--;
      break;
      case BOX:
        bool canPush = push_box(px, py-1, UP);
        if(!canPush) return; 
        
        memoryStack[top]->youPushBox = true;
        meiro[py][px] = 0;
        py--;
      break;
    }
  }
  else if (key == KEY_DOWN && (meiro[py + 1][px] == 0 || meiro[py + 1][px] == BOX))
  {
    save_action(px, py, false, DOWN);
    switch(meiro[py + 1][px])
    {
      case PATH:
        meiro[py][px] = 0;
        py++;
      break;
      case BOX:
        bool canPush = push_box(px, py+1, DOWN);
        if(!canPush) return; 
        
        memoryStack[top]->youPushBox = true;
        meiro[py][px] = 0;
        py++;
      break;
    }
  }
  else if (key == KEY_LEFT && (meiro[py][px - 1] == 0 || meiro[py][px - 1] == BOX))
  {
    save_action(px, py, false, LEFT);
    switch(meiro[py][px - 1])
    {
      case PATH:
        meiro[py][px] = 0;
        px--;
      break;
      case BOX:
        bool canPush = push_box(px-1, py, LEFT);
        if(!canPush) return; 
      
        memoryStack[top]->youPushBox = true;
        meiro[py][px] = 0;
        px--;
      break;
      
    }
  }
  else if (key == KEY_RIGHT && (meiro[py][px + 1] == 0 || meiro[py][px + 1] == BOX))
  {
    save_action(px, py, false, RIGHT);
    switch(meiro[py][px + 1])
    {
      case PATH:
        meiro[py][px] = 0; 
        px++;
      break;
      case BOX:
        bool canPush = push_box(px+1, py, RIGHT);
        if(!canPush) return; 
       
        memoryStack[top]->youPushBox = true;
        meiro[py][px] = 0; 
        px++;
      break;
    }
  }  
  else if (key == 'q')
  {
    if(top >= 0)
      back_to_save();
  }  
  else if (key == ' ')
    play_start();
  else
    key_input();
}

int main(void) 
{
	setlocale(LC_ALL, ""); // UTF 8 출력

	initscr(); // ncurses 초기화
	keypad(stdscr, TRUE);
	noecho();		 // Don't echo any keypresses
	curs_set(FALSE); // Don't display a cursor

	px = 1;
	py = 1;
	count = 0;

  meiro = meiro1;
  FILE* fp = fopen("BestTime.txt", "rt");
  if(fp == NULL)
    return -1;
  
  
  float bestTime = 0;
  clock_t start = 0, end = 0;

  fscanf(fp, "%f", &bestTime);
  
  fclose(fp);
  start = clock();
  
	goal_count_check();

	while (!(count == goal_count)) 
  {
    clear();

		draw_meiro();
    
   // mvprintw(GYO + 3, count, "z");
   // mvprintw(GYO + 3, goal_count, "z");
    
		key_input();

		refresh();
	}
  
	draw_meiro();
	mvprintw(GYO + 1, 0, " Sucess !!");

  getch();

  stage++;
  
	px = 1;
	py = 1;
	count = 0;
  memory_clear();
  play_start();
	goal_count_check();
  while (!(count == goal_count)) 
  {
    clear();

		draw_meiro();
    
   // mvprintw(GYO + 3, count, "z");
   // mvprintw(GYO + 3, goal_count, "z");
    
		key_input();

		refresh();
	}
  
  getch();
  
  end = clock();

  fp = fopen("BestTime.txt", "wt");
  if(fp == NULL)
    return -1;
  

  if(bestTime > (float)end - start)
    bestTime = (float)end - start;

  fprintf(fp, "%f", (float)bestTime);
  fflush(fp);
  
  fclose(fp);
  
	endwin();
	return 0;
}
