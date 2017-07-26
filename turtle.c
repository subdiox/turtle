// ID: 1W000000-X  望月義彦
// indent: space 4

/*
    main関数では、入力文字列のパースをしながらコマンド文字列を追加した後、出力ファイルに書き出している。
    logCommand関数では、現時点でのコマンド文字列に次のコマンド文字列を追加している。
    moveFunc関数では、moveコマンドが入力されたときのcurX、curYの移動処理後、logCommand関数を呼び出している。
    gotoFunc関数では、gotoコマンドが入力されたときのcurX、curYの移動処理後、logCommand関数を呼び出している。
    rightFunc関数では、rightコマンドが入力されたときのcurDirの変更処理をしている。
    leftFunc関数では、leftコマンドが入力されたときのcurDirの変更処理をしている。
    outputFile関数では、文字列をsvgファイルのテンプレートに埋め込み、output.svgを出力する処理をしている。
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 初期設定 (グローバル変数の宣言)
int curX = 250; // 現在のx座業
int curY = 250; // 現在のy座標
int curDir = 0; // 現在の方向 (0:上 | 1:右 | 2:下 | 3:左)
char curCommand[100000] = "M 250 250"; // 現時点でのコマンド文字列

// ログの出力によりコマンド文字列を生成
void logCommand(int x, int y)
{
    sprintf(curCommand, "%s L %d %d", curCommand, y, x);
}

// moveコマンド
void moveFunc(int n)
{
    if (curDir == 0)
    {
        curY -= n;
    }
    else if (curDir == 1)
    {
        curX += n;
    }
    else if (curDir == 2)
    {
        curY += n;
    }
    else if (curDir == 3)
    {
        curX -= n;
    }
    logCommand(curX, curY);
}

// gotoコマンド
void gotoFunc(int x, int y)
{
    curX = x;
    curY = y;
    logCommand(curX, curY);
}

// rightコマンド
void rightFunc()
{
    curDir ++;
    if (curDir == 4)
    {
        curDir = 0;
    }
}

// leftコマンド
void leftFunc()
{
    curDir --;
    if (curDir == -1)
    {
        curDir = 3;
    }
}

// ファイルに出力
void outputToFile(char *command)
{
    FILE *output;
    output = fopen("output.svg", "w");
    char content[100000];
    sprintf(content, "<svg width='500px' height='500px' xmlns='http://www.w3.org/2000/svg'>\n<path d='%s' stroke='red' fill='none' />\n</svg>", command);
    fprintf(output, "%s", content);
    fclose(output);
    printf("\nSVG File is exported: 'output.svg'\n");
}

int main(int argc, char **argv)
{
    int i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "repeat") == 0)
        {
            int n = atoi(argv[i + 1]);
            int j = i + 2;
            for (int loop = 0; loop < n; loop++)
            {
                int k = j;
                while (1)
                {
                    if (strcmp(argv[k], "move") == 0)
                    {
                        int n = atoi(argv[k + 1]);
                        printf("move(%d)\n", n);
                        moveFunc(n);
                        k += 2;
                    }
                    else if (strcmp(argv[k], "goto") == 0)
                    {
                        int x = atoi(argv[k + 1]);
                        int y = atoi(argv[k + 2]);
                        printf("goto(%d, %d)\n", x, y);
                        gotoFunc(x, y);
                        k += 3;
                    }
                    else if (strcmp(argv[k], "right") == 0)
                    {
                        printf("right\n");
                        rightFunc();
                        k += 1;
                    }
                    else if (strcmp(argv[k], "left") == 0)
                    {
                        printf("left\n");
                        leftFunc();
                        k += 1;
                    }
                    else if (strcmp(argv[k], "end") == 0)
                    {
                        i = k + 1;
                        break;
                    }
                }
            }
        }
        else if (strcmp(argv[i], "move") == 0)
        {
            int n = atoi(argv[i + 1]);
            printf("move(%d)\n", n);
            moveFunc(n);
            i += 2;
        }
        else if (strcmp(argv[i], "goto") == 0)
        {
            int x = atoi(argv[i + 1]);
            int y = atoi(argv[i + 2]);
            printf("goto(%d, %d)\n", x, y);
            gotoFunc(x, y);
            i += 3;
        }
        else if (strcmp(argv[i], "right") == 0)
        {
            printf("right\n");
            rightFunc();
            i += 1;
        }
        else if (strcmp(argv[i], "left") == 0)
        {
            printf("left\n");
            leftFunc();
            i += 1;
        }
    }
    outputToFile(curCommand);

    return 0;
}
