#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdint.h>

typedef struct cr_task_t
{
  void (*p_task)(void);
  uint16_t u16_priority;    // Lower value = Highest priority
  uint16_t u16_starvation;
}cr_task_t;

typedef struct cr_scheduler_ctx_t
{
  cr_task_t* task_list;
  uint16_t u16_max_task_cnt;
  uint16_t u16_task_cnt;
}cr_scheduler_ctx_t;

uint8_t Scheduler_init(cr_scheduler_ctx_t* ctx, uint16_t num_tasks);
uint8_t Scheduler_add_task(cr_scheduler_ctx_t* ctx, void (*p_task)(void), uint16_t u16_priority);
void Scheduler_start(cr_scheduler_ctx_t* ctx);

#endif /* SCHEDULER_H_ */