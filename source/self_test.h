/******************************************************************************
* File Name:   self_test.h
*
* Description: This file is the public interface of self_test.c source file.
*
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2024, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef SELF_TEST_H_
#define SELF_TEST_H_

#include "SelfTest.h"

/*******************************************************************************
* Global Variables
*******************************************************************************/
extern uint16_t test_counter;
/*Index for IPs*/
extern uint8_t ip_index;

/*******************************************************************************
* Macros
*******************************************************************************/
#define MAX_INDEX_VAL (0xFFF0u)

#define CUSTOM_DELAY_VAL (500u)

#if COMPONENT_CAT1C
/* Enable WWDT self test for XMC devices*/
#define WWDT_SELF_TEST_ENABLE (0u)
#endif

/* Waiting time, in milliseconds, for proper start-up of ILO */
#define ILO_START_UP_TIME              (2U)

/* Print Test Result*/
#define PRINT_TEST_RESULT(index, test_name, status) \
    do { \
        if (OK_STATUS == ret) { \
            /* Process success */ \
            printf("| %-4d| %-32s| %-12s|\r\n",index,test_name,"SUCCESS"); \
        } \
        else if (PASS_COMPLETE_STATUS == ret) { \
            /* Process status */ \
            printf("| %-4d| %-32s| %-12s|\r\n",index,test_name,"SUCCESS"); \
            break; \
        } \
        else if (PASS_STILL_TESTING_STATUS == ret) { \
            /* Print test counter */ \
            printf("| %-4d| %-32s| %-12s|count=%d\r",index,test_name,"IN PROGRESS", test_counter); \
        } \
        else { \
            /* Process error */ \
        printf("| %-4d| %-32s| %-12s|\t\t",index,test_name,"ERROR"); \
        } \
    } while (0)

#if COMPONENT_CAT1A
    #define CLOCK_INTR_SRC CYBSP_CLOCK_TEST_TIMER_IRQ
    #define TIMER_INTR_SRC CYBSP_TIMER_IRQ
    #define DMAC_INPUT_TRIG_MUX TRIG_OUT_MUX_6_MDMA_TR_IN0
#elif COMPONENT_CAT1C
    #define CLOCK_INTR_SRC  ((NvicMux3_IRQn << 16) | CYBSP_CLOCK_TEST_TIMER_IRQ)
    #define TIMER_INTR_SRC  ((NvicMux3_IRQn << 16) | CYBSP_TIMER_IRQ)
    #define DMAC_INPUT_TRIG_MUX TRIG_OUT_MUX_3_MDMA_TR_IN0
#endif


#define PATTERN_BLOCK_SIZE (8u)

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void IO_Test(void);
void Clock_Test(void);
void Clock_Test_Init(void);
void Interrupt_Test(void);
void Interrupt_Test_Init(void);
void Flash_Test(void);
void Wdt_Test(void);
void FPU_Test(void);
#if (!defined(CY_DEVICE_PSOC6ABLE2)&& !defined (CY_DEVICE_SECURE))
    void DMAC_Test(void);
#endif
#if !defined (CY_DEVICE_SECURE)
    void DMA_DW_Test(void);
#endif
void Start_Up_Test(void);
void Stack_March_Test(void);
void SRAM_March_Test(void);
void Stack_Memory_Test(void);

#endif /* SELF_TEST_H_ */


/* [] END OF FILE */
