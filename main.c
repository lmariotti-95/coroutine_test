#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "user/lib/coroutine.h"
#include "user/lib/scheduler.h"

int println(char *str)
{
  return printf("%s\n", str);
}

void Foo(void)
{
  static int i = 0;

  scrBegin;
  while(1)
  {
    i = (i + 1) % 1000;
    //printf("Foo %d\n", i);
    println("Halt Foo");
    scrReturnV;
    println("Resume Foo");
  }

  scrFinishV;
}

void Bar(void)
{
  static uint16_t i = 0;
  
  scrBegin;
  while(1)
  {
    i = (i + 1) % 1000;
    //println("Bar %d", i);
    println("Halt Bar");
    scrReturnV;
    println("Resume Bar");
  }

  scrFinishV;
}

void Long_task(void)
{
  uint64_t u64_timer = UINT64_MAX;

  scrBegin;
  while(u64_timer--)
  {
    usleep(100000);
    println("Halt Long Task");
    scrReturnV;
    println("Resume Long Task");
  }

  scrFinishV;
}

int main(void)
{
  cr_scheduler_ctx_t cr_scheduler;
  uint8_t status = 0;

  status |= Scheduler_init(&cr_scheduler, 3);

  status |= Scheduler_add_task(&cr_scheduler, &Foo, 5);
  status |= Scheduler_add_task(&cr_scheduler, &Bar, 10);
  status |= Scheduler_add_task(&cr_scheduler, &Long_task, 1);

  if(status)
  {
    printf("Coroutine initialization failed\n");
    return EXIT_FAILURE;
  }

  printf("Coroutine start\n");
  Scheduler_start(&cr_scheduler);

  return EXIT_SUCCESS;
}