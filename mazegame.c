//Maze Game
//Pressing enter is required after each input
//gcc -o mazegame mazegame.c
// ./mazegame map.txt
#include <stdio.h>
#include <stdlib.h>

int l, w;

struct pastidx
{
    int p[2], s[2];
    char dirn;
    struct pastidx *next;
};

struct head
{
    int cnt;
    struct pastidx *start;
    struct pastidx *end;
};

typedef struct pastidx pastidx;
typedef struct head head;

void identify(head *h, int player[2], int snake[2], char prmv)
{
    pastidx *node = (pastidx *)malloc(sizeof(pastidx));
    if (node == NULL)
        return;
    node->p[0] = player[0];
    node->p[1] = player[1];
    node->s[0] = snake[0];
    node->s[1] = snake[1];
    node->dirn = prmv;
    node->next = NULL;
    h->cnt++;
    if (h->start == NULL)
    {
        h->start = h->end = node;
        return;
    }
    h->end->next = node;
    h->end = node;
}

char undo(head *h, int player[2], int snake[2])
{
    if (h->start == NULL && h->cnt <= 1)
        return '0';
    char ch = h->end->dirn;
    player[0] = h->end->p[0];
    player[1] = h->end->p[1];
    snake[0] = h->end->s[0];
    snake[1] = h->end->s[1];
    pastidx *temp = h->end;
    pastidx *node = h->start;
    while (node->next != NULL && node->next->next != NULL)
        node = node->next;
    if (node->next == NULL)
        h->start = h->end = NULL;
    else
    {
        node->next = NULL;
        h->end = node;
    }
    h->cnt--;
    free(temp);
    return ch;
}

void delall(head *h)
{
    pastidx *temp = h->start;
    while (h->start != NULL)
    {
        h->start = h->start->next;
        free(temp);
        temp = h->start;
    }
    if (h->start == NULL)
        h->end == NULL;
}

void printall(char maze[l][w])
{
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < w; j++)
            printf("%c", maze[i][j]);
        printf("\n");
    }
}

int statuscheck(int player[2], int snake[2])
{
    if (player[0] == snake[0] && player[1] == snake[1])
        return 1;
    return 0;
}

void snakego(int snake[2], int player[2], char maze[l][w])
{
	
	int x = snake[0];
    int y = snake[1];
	
	maze[x][y] = ' ';
    int num = 0;
    int dist = 1e8;

    //up
    if(maze[x-1][y] != 'O' && x-1 > 0){
        int diff = abs(player[0] - (x-1)) + abs(player[1] - (y));
        if(diff < dist){
            dist = diff;
            num = 1;
        }
    }

    //down
    if(maze[x+1][y] != 'O' && x+1 < 10){
        int diff = abs(player[0] - (x+1)) + abs(player[1] - (y));
        if(diff<dist){
            dist = diff;
            num = 2;
        }
    }

    //right
    if(maze[x][y+1] != 'O' && y+1 < 14){
        int diff = abs(player[0] - x) + abs(player[1] - (y+1));
        if(diff<dist){
            dist = diff;
            num = 3;
        }
    }

    //left
    if(maze[x][y-1] != 'O' && y-1 > 0){
        int diff = abs(player[0] - x) + abs(player[1] - (y-1));
        if(diff<dist){
            dist = diff;
            num = 4;
        }
    }

    if(num == 1){
        snake[0]--;
    }else if(num == 2){
        snake[0]++;
    }else if(num == 3){
        snake[1]++;
    }else{
        snake[1]--;
    }
    
    maze[snake[0]][snake[1]] = '~';
    
}

void play(char maze[l][w], int snake[2], int player[2], int dst[2])
{
    char ch;
    int win = 0, lose = 0;
    head mem;
    mem.cnt = 0;
    mem.start = mem.end = NULL;
    identify(&mem, player, snake, '^');
    while (!win && !lose)
    {
        system("cls");
        printf("RULES OF GAME\n");
        printf("-------------\n");
        printf("Press enter after pressing one of these keys\n");
        printf("Press \'w\' to move up\n");
        printf("Press \'a\' to move left\n");
        printf("Press \'s\' to move down\n");
        printf("Press \'d\' to move right\n");
        printf("Press \'u\' to undo\n");
        printf("Press \'q\' to quit\n\n");
        printall(maze);
        printf("\n");
        fflush(stdin);
        scanf("%c", &ch);
        switch (ch)
        {
        case 'w':
        {
            if (maze[player[0] - 1][player[1]] == ' ' || maze[player[0] - 1][player[1]] == 'X')
            {
                if (maze[player[0] - 1][player[1]] == 'X')
                    win = 1;
                maze[player[0]][player[1]] = ' ';
                maze[player[0] - 1][player[1]] = '^';
                player[0]--;
                identify(&mem, player, snake, '^');
            }
            break;
        }
        case 'a':
        {
            if (maze[player[0]][player[1] - 1] == ' ' || maze[player[0]][player[1] - 1] == 'X')
            {
                if (maze[player[0]][player[1] - 1] == 'X')
                    win = 1;
                maze[player[0]][player[1]] = ' ';
                maze[player[0]][player[1] - 1] = '<';
                player[1]--;
                identify(&mem, player, snake, '<');
            }
            break;
        }
        case 's':
        {
            if (maze[player[0] + 1][player[1]] == ' ' || maze[player[0] + 1][player[1]] == 'X')
            {
                if (maze[player[0] + 1][player[1]] == 'X')
                    win = 1;
                maze[player[0]][player[1]] = ' ';
                maze[player[0] + 1][player[1]] = 'v';
                player[0]++;
                identify(&mem, player, snake, 'v');
            }
            break;
        }
        case 'd':
        {
            if (maze[player[0]][player[1] + 1] == ' ' || maze[player[0]][player[1] + 1] == 'X')
            {
                if (maze[player[0]][player[1] + 1] == 'X')
                    win = 1;
                maze[player[0]][player[1]] = ' ';
                maze[player[0]][player[1] + 1] = '>';
                player[1]++;
                identify(&mem, player, snake, '>');
            }
            break;
        }
        case 'u':
        {
            int px, py, sx, sy;
            px = player[0];
            py = player[1];
            sx = snake[0];
            sy = snake[1];
            char mz_val = undo(&mem, player, snake);
            if (mz_val != '0')
            {
                maze[px][py] = ' ';
                maze[player[0]][player[1]] = mz_val;
                maze[sx][sy] = ' ';
                maze[snake[0]][snake[1]] = '~';
            }
            break;
        }
        case 'q':
        {
            printf("Thank You\nSubmitted by: Anmol Singh(2K20/CO/80) & Anubhav Gupta(2K20/CO/85)");
            delall(&mem);
            exit(0);
        }
        default:
        {
            printf("Invalid Choice!!!");
            system("pause");
            break;
        }
        }
        snakego(snake, player, maze);
        if (statuscheck(player, snake))
            lose = 1;
    }
    system("cls");
    printall(maze);
    delall(&mem);
    if (win)
        printf("\nYou Win!\n");
    else
        printf("\nYou Lose! Try Again\n");
}

void startready(char *file_name)
{
    printf("Enter the input file\n");
    FILE *fp;
    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("%s File not found!!!\n");
        return;
    }
    int snake[2], player[2], dst[2];
    int x;
    fscanf(fp, "%d %d %d", &x, &l, &w);
    int obs[x - 3][2], n = 0;
    for (int i = 0; i < x; i++)
    {
        int t1, t2, t3;
        fscanf(fp, "%d %d %d", &t1, &t2, &t3);
        if (t3 == 0)
        {
            player[0] = t1;
            player[1] = t2;
        }
        else if (t3 == 1)
        {
            snake[0] = t1;
            snake[1] = t2;
        }
        else if (t3 == 2)
        {
            dst[0] = t1;
            dst[1] = t2;
        }
        else
        {
            obs[n][0] = t1;
            obs[n++][1] = t2;
        }
    }
    fclose(fp);

    
    char maze[l][w];
    maze[0][0] = maze[0][w - 1] = maze[l - 1][0] = maze[l - 1][w - 1] = '#';
    for (int i = 1; i < w - 1; i++)
        maze[0][i] = maze[l - 1][i] = '-';
    for (int i = 1; i < l - 1; i++)
        maze[i][0] = maze[i][w - 1] = '|';
    for (int i = 1; i < l - 1; i++)
        for (int j = 1; j < w - 1; j++)
            maze[i][j] = ' ';
   
    for (int i = 0; i < n; i++)
        maze[obs[i][0]][obs[i][1]] = 'O';
    maze[dst[0]][dst[1]] = 'X'; //Destination
    maze[snake[0]][snake[1]] = '~'; //Sanke Start
    maze[player[0]][player[1]] = '^'; //Player Start

    play(maze, snake, player, dst);
}

int main(int x, char *y[])
{
    if (x != 2)
    {
        printf("Invalid Arguments !\n");
        exit(1);
    }
    startready(y[x - 1]);
    return 0;
}
