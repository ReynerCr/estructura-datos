//gotoxy.h
#include <windows.h>

void gotoxy( int column, int line )
{
  COORD coord;
  if (column < 0 && line >= 0)
  {
  	column = 70;
	line = line - 1;
  }
  else if (column > 70 && line >= 0) {
  	column = 0;
  	line = line + 1;
  }
  coord.X = column;
  coord.Y = line;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),
    coord
  );
}

int wherex()
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD                      result;
  if (!GetConsoleScreenBufferInfo(
         GetStdHandle( STD_OUTPUT_HANDLE ),
         &csbi
         ))
    return -1;
  return result.X;
}

int wherey()
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  COORD                      result;
  if (!GetConsoleScreenBufferInfo(
         GetStdHandle( STD_OUTPUT_HANDLE ),
         &csbi
         ))
    return -1;
  return result.Y;
}

COORD getCoord()
{
	COORD xy;
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO p;
	GetConsoleScreenBufferInfo(hcon, &p);
	xy = p.dwCursorPosition;
	return xy;
}
