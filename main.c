#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "user/lib/coroutine.h"

void Foo(void)
{
  static int i = 0;

  scrBegin;
  while(1)
  {
    printf("Foo %d\n", i++);
    scrReturnV;
  }

  scrFinishV;
}

void Bar(void)
{
  static int i = 0;
  
  scrBegin;
  while(1)
  {
    printf("Bar %d\n", i++);
    scrReturnV;
  }

  scrFinishV;
}

int main(void)
{
  printf("Coroutine start\n");

  for(int i = 0; i < 5; i++)
  {
    Foo();
    Bar();
    
    sleep(1);
  }
}