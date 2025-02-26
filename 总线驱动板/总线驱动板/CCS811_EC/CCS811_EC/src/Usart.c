/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "Usart.h"

/*----------------------------------------  F U N C T I O N S  ----------------------------------------*/
/********************************************************************************************************
Function Name: UsartIOInit
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void UsartIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);


    // Configure USART Tx as alternate function push-pull
    GPIO_InitStructure.GPIO_Pin = UART_TX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(UART_GPIO, &GPIO_InitStructure);

    // Configure USART Rx as input floating
    GPIO_InitStructure.GPIO_Pin = UART_RX_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(UART_GPIO, &GPIO_InitStructure);
}

/********************************************************************************************************
Function Name: USARTConfig
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void UsartConfig(void)
{
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UARTx, &USART_InitStructure);
    USART_Cmd(UARTx, ENABLE);



    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/********************************************************************************************************
Function Name: UsartInit
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void UsartInit(void)
{
    UsartIOInit();
    UsartConfig();
}

/********************************************************************************************************
Function Name: SendData
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void SendData(u8 ch)
{
    USART_SendData(UARTx, (uint8_t) ch);
    while (USART_GetFlagStatus(UARTx, USART_FLAG_TXE) == RESET);
}
/********************************************************************************************************
Function Name: Send1Data
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
void Send1Data(u8 ch)
{
    USART_SendData(UARTx, (uint8_t) ch);
    while (USART_GetFlagStatus(UARTx, USART_FLAG_TXE) == RESET);
}
/********************************************************************************************************
Function Name: USART1_IRQHandler
Description  :
Inputs       : None
Outputs      : None
Notes        :
Revision     :
********************************************************************************************************/
u8  rece;
void USART1_IRQHandler(void)
{
    if(RESET != USART_GetITStatus(UARTx,USART_IT_RXNE))
    {
        rece = USART_ReceiveData(UARTx);
        USART_ClearITPendingBit(UARTx,USART_IT_RXNE);
    }
}
//===========================================  End Of File  ===========================================//

