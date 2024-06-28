/******************************************************************************
* File Name:   main.c
*
* Description:This file provides the following core peripheral self tests
*             for  PSoC6 MCU and XMC7000 MCU:
*             - CPU registers test
*             - Program Counter test
*             - WDT and WWDT test
*             - Clock test
*             - Interrupt test
*             - IO test
*             - Flash test (fletcher's test + CRC test)
*             - Config Registers test
*             - SRAM/Stack test (March test)
*             - Stack Overflow/ Underflow test
*             - FPU Test
*             - DMAC test
*             - DMA_W test
*             - IPC test
*             - Program flow test
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

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "self_test.h"

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function. It does...
*    1. Initialize the device and board peripherals and retarget-io for prints
*    2. Calls the test APIs for testing the followings:
*        - Program Counter
*        - CPU registers
*        - WDT and WWDT
*        - Clock
*        - Interrupt
*        - Flash
*        - IO
*        - Config Registers test
*        - SRAM/Stack test (March test)
*        - Stack Overflow test
*        - FPU test
*        - DMAC test
*        - DMA_W test
*        - IPC test
*        - Program flow test
*
* Parameters:
*  none
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* SelfTest API return status */
    uint8_t ret = 0u;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init_fc(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
            CYBSP_DEBUG_UART_CTS,CYBSP_DEBUG_UART_RTS,CY_RETARGET_IO_BAUDRATE);

    /* retarget-io init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    printf("****************** "
           "Class-B Safety Test for PSoC6: Core Peripheral Resources "
           "****************** \r\n\n");

    printf("------------------------------------------------------- \r\n");
    printf("| #   | IP under test                   | Test Status | \r\n");
    printf("------------------------------------------------------- \r\n");

    /* Start Up Test */
    Start_Up_Test();


    /* Program counter Test */
    ret = SelfTest_PC();
    PRINT_TEST_RESULT(ip_index++,"Program Counter Test",ret);


    /* CPU Registers Test*/
    ret = SelfTest_CPU_Registers();
    PRINT_TEST_RESULT(ip_index++,"CPU Register Test", ret);

    /* Program Flow Test*/
    ret = SelfTest_PROGRAM_FLOW();
    PRINT_TEST_RESULT(ip_index++,"Program Flow Test", ret);

    /* Watch Dog Timer Test */
    Wdt_Test();

    /* GPIO Test */
    IO_Test();

    /* FPU Test */
    FPU_Test();

#if !defined(CY_DEVICE_PSOC6ABLE2)
    /* DMAC Test */
    DMAC_Test();
#endif

    /* DMA DW Test */
    DMA_DW_Test();

    /* IPC Test */
    ret = SelfTest_IPC();
    PRINT_TEST_RESULT(ip_index++,"IPC Test", ret);

    /* Clock Test */
    Clock_Test();

    /* Interrupt Test */
    Interrupt_Test();

    /* SRAM Memory Test */
    SRAM_March_Test();

    /* Stack Memory Test */
    Stack_March_Test();

    /* Stack Overflow and Underflow Test */
    Stack_Memory_Test();

    /* Flash Test */
    Flash_Test();

    printf("------------------------------------------------------- \r\n\n");
    printf("END of the Core CPU Test.\r\n\n");
    printf("Total number of IPs covered in the Test      %d\r\n",--ip_index);
    for (;;)
    {
   
    }
}


/* [] END OF FILE */
