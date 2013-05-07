/* original source http://d.hatena.ne.jp/ichirin2501/20100224/1267016447 */

#import <stdio.h>
#import <stdlib.h>
#import <time.h>
#import <string.h>
#import <unistd.h>
#import <wchar.h>

#define N 60

void
init_world(int world[2][N+2][N+2])
{
  int i,j;
  /* seed to srand function */
  srand(time(NULL));

  /* fill world with random value */
  for (i=1; i<=N; i++) {
    for (j=1; j<=N; j++) {
      world[0][i][j] = rand()%2;
    }
  }
}

void
print_world(int world[2][N+2][N+2], int cycle)
{
  int i,j;
  const char symbol = '*';
 

  for (i=1; i<=N; i++) {
    for (j=1; j<=N; j++) {
      putchar(world[cycle][i][j]?symbol:' ');
     }
    puts("");
  }
}

void
update_world(int world[2][N+2][N+2], int cycle)
{
  int i,j,tmp;
  for (i=1; i<=N; i++) {
    for (j=1; j<=N; j++) {
      tmp = world[cycle][i+1>N?1:i+1][j          ] +
        world[cycle][i-1?:N     ][j          ] +
        world[cycle][i          ][j+1>N?1:j+1] +
        world[cycle][i          ][j-1?:N     ] +
        world[cycle][i+1>N?1:i+1][j+1>N?1:j+1] +
        world[cycle][i+1>N?1:i+1][j-1?:N     ] +
        world[cycle][i-1?:N     ][j+1>N?i:j+1] +
        world[cycle][i-1?:N     ][j-1?:N     ];

      if (world[cycle][i][j]) {
        world[cycle^1][i][j] = (tmp==2||tmp==3);
      } else {
        world[cycle^1][i][j] = (tmp==3);
      }
    }
  }
}

int
main()
{
  int world[2][N+2][N+2];
  int i,j,cycle,k,tmp;


  /* write 0 to world */
  memset(world, 0, sizeof(world));

  init_world(world);

  cycle = 0;
  /* main loop */
  for (k=0;;k++) {
    printf("\033[2J");
    printf("k:%d\n", k);

    print_world(world, cycle);

    puts("");
    sleep(1);

    update_world(world, cycle);

    cycle ^= 1;

  }

  return 0;

}



