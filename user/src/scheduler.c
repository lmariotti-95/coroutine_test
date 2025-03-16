#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "../lib/scheduler.h"

#ifndef NULL
#define NULL (void*)0
#endif

uint8_t Scheduler_init(cr_scheduler_ctx_t* ctx, uint16_t num_tasks)
{
  if(ctx == NULL) 
    return 1;

  if(num_tasks == 0) 
    return 1;

  cr_task_t* ptr = (cr_task_t*)malloc(num_tasks * sizeof(cr_task_t));

  if(ptr == NULL) 
    return 1;

  ctx->task_list = ptr;
  ctx->u16_max_task_cnt = num_tasks;
  ctx->u16_task_cnt = 0;

  return 0;
}

uint8_t Scheduler_add_task(cr_scheduler_ctx_t* ctx, void (*p_task)(void), uint16_t u16_priority)
{
  if(p_task == NULL)
    return 1;

  if(ctx->u16_task_cnt >= ctx->u16_max_task_cnt)
    return 1;

  uint16_t i = ctx->u16_task_cnt;
  ctx->task_list[i].p_task = p_task;
  ctx->task_list[i].u16_priority = u16_priority;
  ctx->task_list[i].u16_starvation = ctx->task_list[i].u16_priority;

  ctx->u16_task_cnt++;
  
  return 0;
}

void Scheduler_start(cr_scheduler_ctx_t* ctx)
{
  uint16_t i = 0;
  cr_task_t* cr_task;

  while(1)
  {
    cr_task = &ctx->task_list[i];

    if(cr_task->p_task != NULL)
    {
      if(cr_task->u16_starvation > 0)
      {
        cr_task->u16_starvation--;
      }
      else
      {
        cr_task->u16_starvation = cr_task->u16_priority;
        ctx->task_list[i].p_task();
      }
      
      usleep(1000);
    }
    
    i = (i + 1) % ctx->u16_task_cnt;
  }
}