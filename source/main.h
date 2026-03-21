/*
 * main.h
 *
 *  Created on: Mar 14, 2026
 *      Author: VanTungDinh
 */

#ifndef MAIN_H_
#define MAIN_H_

#define SIZE_PRIVATE_STACK 				1024
#define SIZE_SCHEDULER_STACK			1024

#define SRAM_START						0x20000000
#define SIZE_SRAM						(128 * 1024)
#define SRAM_END						((SRAM_START) + (SIZE_SRAM))

#define TASK1_STACK_START				SRAM_END
#define TASK2_STACK_START				((TASK1_STACK_START) - (SIZE_PRIVATE_STACK))
#define TASK3_STACK_START				((TASK2_STACK_START) - (SIZE_PRIVATE_STACK))
#define TASK4_STACK_START				((TASK3_STACK_START) - (SIZE_PRIVATE_STACK))
#define IDLE_STACK_START				((TASK4_STACK_START) - (SIZE_PRIVATE_STACK))
#define SCHEDULER_STACK_START			((IDLE_STACK_START) - (SIZE_SCHEDULER_STACK))

#define TICK_HZ 						1000 // 1kHz <=> 1ms
#define HSI_CLK							16000000 // 16Mhz
#define SYSTICK_TIMER_CLK				HSI_CLK

#define MAX_TASK						5

#define DUMMY_XPSR						0x01000000
#define VALUE_LR						0xFFFFFFFD

#define BASE_SHCRS 						0xE000ED24

#define TASK_READY_STATE				0x00
#define TASK_BLOCKED_STATE				0xFF

#define INTERRUPT_DISABLE() 			do{__asm volatile("MOV R0, #0x1"); __asm volatile("MSR PRIMASK, R0");}while(0);
#define INTERRUPT_ENABLE() 				do{__asm volatile("MOV R0, #0x0"); __asm volatile("MSR PRIMASK, R0");}while(0);

void task1();
void task2();
void task3();
void task4();
void delay_func();
void init_private_stack();
void enable_processor_faults();
void init_systick_timer(uint32_t tick_hz);
void save_psp_value(uint32_t stack_address);
void task_delay(uint32_t tick_count);

__attribute__((naked)) void init_scheduler_stack(uint32_t scheduler_top_of_stack);
__attribute__((naked)) void switch_MSP_to_PSP();

uint32_t get_psp_value();

#endif /* MAIN_H_ */
