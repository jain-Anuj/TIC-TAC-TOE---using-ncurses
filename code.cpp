#include <ncurses.h>
#include <utility>
#include <random>
using namespace std;
bool gameover = false, player_turn;
char player_char, computer_char, game_board[][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
const int board_y = 10, board_x =20;
std::default_random_engine gen1;
std::uniform_int_distribution<int> dist1(1,9);
void setup()
{
  mvprintw(0,15,"T I C K -- T A C -- T O E -- G A M E");
  mvprintw(1,27,"FOR ONE PLAYER");

  mvprintw(4,15, "Select Your Character (X/O) - ");
  player_char = getch();
  computer_char = player_char == 'X'? 'O':'X';
  std::default_random_engine gen;
  std::uniform_int_distribution<int> dist(0,1);
  player_turn = dist(gen);
  if(player_turn)
  {
    mvprintw(5,15,"You will play first");
  }
  else
  {
    mvprintw(5,15,"Computer will play first");
  }
  move(board_y,board_x);
  int x,y;
  for(int i =0;i<=2;i++)
  {
    for(int j = 0;j<=2;j++)
    {
      printw("  %c  ",game_board[i][j]);
      if(j!=2)
      printw("|");
    }
    getyx(stdscr, y,x);
    if(i!=2)
    {
      mvprintw(y+1,board_x,"_____ _____ _____");
      move(y+3,board_x);
    }
  }

}
void draw()
{
  move(board_y,board_x);
  int x,y;
  for(int i =0;i<=2;i++)
  {
    for(int j = 0;j<=2;j++)
    {
      if(!isdigit(game_board[i][j]))
      printw("  %c  ",game_board[i][j]);
      else
      printw("     ",game_board[i][j]);
      if(j!=2)
      printw("|");
    }
    getyx(stdscr, y,x);
    if(i!=2)
    {
      mvprintw(y+1,board_x,"_____ _____ _____");
      move(y+3,board_x);
    }
  }
}
bool parse_input(char n,char ch)
{
  pair <int,int> parsed_input(-1,-1);
  switch (n) {
    case '1':
    parsed_input.first = 0;
    parsed_input.second = 0;
    break;
    case '2':
    parsed_input.first = 0;
    parsed_input.second = 1;
    break;
    case '3':
    parsed_input.first = 0;
    parsed_input.second = 2;
    break;
    case '4':
    parsed_input.first = 1;
    parsed_input.second = 0;
    break;
    case '5':
    parsed_input.first = 1;
    parsed_input.second = 1;
    break;
    case '6':
    parsed_input.first = 1;
    parsed_input.second = 2;
    break;
    case '7':
    parsed_input.first = 2;
    parsed_input.second = 0;
    break;
    case '8':
    parsed_input.first = 2;
    parsed_input.second = 1;
    break;
    case '9':
    parsed_input.first = 2;
    parsed_input.second = 2;
    break;
  }
  if(!isdigit(game_board[parsed_input.first][parsed_input.second]) )
  {
    return false;
  }
  game_board[parsed_input.first][parsed_input.second] = ch;
  return true;
}
bool parse_input(int n,char ch)
{
  pair <int,int> parsed_input(-1,-1);
  switch (n) {
    case 1:
    parsed_input.first = 0;
    parsed_input.second = 0;
    break;
    case 2:
    parsed_input.first = 0;
    parsed_input.second = 1;
    break;
    case 3:
    parsed_input.first = 0;
    parsed_input.second = 2;
    break;
    case 4:
    parsed_input.first = 1;
    parsed_input.second = 0;
    break;
    case 5:
    parsed_input.first = 1;
    parsed_input.second = 1;
    break;
    case 6:
    parsed_input.first = 1;
    parsed_input.second = 2;
    break;
    case 7:
    parsed_input.first = 2;
    parsed_input.second = 0;
    break;
    case 8:
    parsed_input.first = 2;
    parsed_input.second = 1;
    break;
    case 9:
    parsed_input.first = 2;
    parsed_input.second = 2;
    break;
  }
  if(!isdigit(game_board[parsed_input.first][parsed_input.second]))
  {
    return false;
  }
  game_board[parsed_input.first][parsed_input.second] = ch;
  return true;
}
void input()
{
  if(player_turn)
  {
    mvprintw(30,5,"Player Turn [%c] - ",player_char);
    char player_input;
    do
    {
      player_input = getch();

    }while(!parse_input(player_input,player_char));
  }
  else
  {

    int computer_input;
    do
    {
      computer_input = dist1(gen1);
    }while(!parse_input(computer_input,computer_char));
  }
  player_turn =!player_turn;
}
bool logic()
{
  for(int i =0;i<=2;i++)
  {
    if(game_board[i][0] == game_board[i][1] && game_board[i][0] == game_board[i][2])
    {
      return true;
    }
    if(game_board[0][i] == game_board[1][i] && game_board[0][i] == game_board[2][i])
    {
      return true;
    }
  }
  if(game_board[0][0] == game_board[1][1] && game_board[0][0] == game_board[2][2])
  return true;
  if(game_board[0][2] == game_board[1][1] && game_board[0][2] == game_board[2][0])
  return true;
  return false;
}
int main()
{

  initscr();
  setup();
  while(!gameover)
  {
    input();
    draw();
    gameover = logic();
  }
  if(!player_turn)
  mvprintw(board_y,50,"Game Over, Human won!");
  else
  mvprintw(board_y,50,"Game Over, Computer won!");
  getch();
  endwin();
  return 0;
}
