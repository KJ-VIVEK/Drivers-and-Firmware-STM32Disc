// /*
//  * I2C_STM32_DRIVER.c
//  *
//  *  Created on: Feb 24, 2021
//  *      Author: windows 10
//  */

// #include "STM32F407DISC.h"

// static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
// static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
// static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
// static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle);

// static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
// {
// 	pI2Cx->I2C_DR |= ( 1 << I2Cx_START);
// }



// static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
// {
// 	SlaveAddr = SlaveAddr << 1;
// 	SlaveAddr &= ~(1); //SlaveAddr is Slave address + r/nw bit=0
// 	pI2Cx->I2C_DR = SlaveAddr;
// }


// static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
// {
// 	SlaveAddr = SlaveAddr << 1;
// 	SlaveAddr |= 1; //SlaveAddr is Slave address + r/nw bit=1
// 	pI2Cx->I2C_DR = SlaveAddr;
// }


// static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle )
// {
// 	uint32_t dummy_read;
// 	//check for device mode
// 	if(pI2CHandle->pI2Cx->I2C_SR2 & ( 1 << I2Cx_MSL))
// 	{
// 		//device is in master mode
// 		if(pI2CHandle->TxRxState == I2C_BUSY_IN_RX)
// 		{
// 			if(pI2CHandle->RxSize  == 1)
// 			{
// 				//first disable the ack
// 				I2C_ManageAck(pI2CHandle->pI2Cx,DISABLE);

// 				//clear the ADDR flag ( read SR1 , read SR2)
// 				dummy_read = pI2CHandle->pI2Cx->I2C_SR1;
// 				dummy_read = pI2CHandle->pI2Cx->I2C_SR2;
// 				(void)dummy_read;
// 			}

// 		}
// 		else
// 		{
// 			//clear the ADDR flag ( read SR1 , read SR2)
// 			dummy_read = pI2CHandle->pI2Cx->I2C_SR1;
// 			dummy_read = pI2CHandle->pI2Cx->I2C_SR2;
// 			(void)dummy_read;

// 		}

// 	}
// 	else
// 	{
// 		//device is in slave mode
// 		//clear the ADDR flag ( read SR1 , read SR2)
// 		dummy_read = pI2CHandle->pI2Cx->I2C_SR1;
// 		dummy_read = pI2CHandle->pI2Cx->I2C_SR2;
// 		(void)dummy_read;
// 	}


// }


//  void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
// {
// 	pI2Cx->I2C_CR1 |= ( 1 << I2Cx_STOP);
// }


//  void I2C_SlaveEnableDisableCallbackEvents(I2C_RegDef_t *pI2Cx,uint8_t EnorDi)
//  {
// 	 if(EnorDi == ENABLE)
// 	 {
// 			pI2Cx->I2C_CR2 |= ( 1 << I2Cx_ITEVTEN);
// 			pI2Cx->I2C_CR2 |= ( 1 << I2Cx_ITBUFEN);
// 			pI2Cx->I2C_CR2 |= ( 1 << I2Cx_ITERREN);
// 	 }else
// 	 {
// 			pI2Cx->I2C_CR2 &= ~( 1 << I2Cx_ITEVTEN);
// 			pI2Cx->I2C_CR2 &= ~( 1 << I2Cx_ITBUFEN);
// 			pI2Cx->I2C_CR2 &= ~( 1 << I2Cx_ITERREN);
// 	 }

//  }


// void I2Cx_PeriCtrl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
// {
// 	if(EnOrDi == ENABLE)
// 	{
// 		pI2Cx->I2C_CR1 |= (1 << I2Cx_PE);
// 		//pI2cBaseAddress->CR1 |= I2C_CR1_PE_Bit_Mask;
// 	}else
// 	{
// 		pI2Cx->I2C_CR1 &= ~(1 << 0);
// 	}

// }

// void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
// {
// 	if(EnorDi == ENABLE)
// 	{
// 		if(pI2Cx == I2C1)
// 		{
// 			I2C1_PCLK_EN();
// 		}else if (pI2Cx == I2C2)
// 		{
// 			I2C2_PCLK_EN();
// 		}else if (pI2Cx == I2C3)
// 		{
// 			I2C3_PCLK_EN();
// 		}
// 	}
// 	else
// 	{
// 		if(pI2Cx == I2C1)
// 		{
// 			I2C1_PCLK_DI();
// 		}
// 		else if (pI2Cx == I2C2)
// 		{
// 			I2C2_PCLK_DI();
// 		}
// 		else if (pI2Cx == I2C3)
// 		{
// 			I2C3_PCLK_DI();
// 		}
// 	}

// }

// void I2C_Init(I2C_Handle_t *pI2CHandle)
// {
// 	uint32_t tempreg = 0 ;

// 	//enable the clock for the i2cx peripheral
// 	I2C_PeriClockControl(pI2CHandle->pI2Cx,ENABLE);

// 	//ack control bit
// 	tempreg |= pI2CHandle->I2C_Config.I2C_AckControl << 10;
// 	pI2CHandle->pI2Cx->I2C_CR1 = tempreg;

// 	//configure the FREQ field of CR2
// 	tempreg = 0;
// 	tempreg |= RCC_GetPCLK1Value() /1000000U ;
// 	pI2CHandle->pI2Cx->I2C_CR2 =  (tempreg & 0x3F);

//    //program the device own address
// 	tempreg = 0;
// 	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
// 	tempreg |= ( 1 << 14);
// 	pI2CHandle->pI2Cx->I2C_OAR1 = tempreg;

// 	//CCR calculations
// 	uint16_t ccr_value = 0;
// 	tempreg = 0;
// 	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
// 	{
// 		//mode is standard mode
// 		ccr_value = (RCC_GetPCLK1Value() / ( 2 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
// 		tempreg |= (ccr_value & 0xFFF);
// 	}else
// 	{
// 		//mode is fast mode
// 		tempreg |= ( 1 << 15);
// 		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);
// 		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
// 		{
// 			ccr_value = (RCC_GetPCLK1Value() / ( 3 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
// 		}else
// 		{
// 			ccr_value = (RCC_GetPCLK1Value() / ( 25 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
// 		}
// 		tempreg |= (ccr_value & 0xFFF);
// 	}
// 	pI2CHandle->pI2Cx->I2C_CCR = tempreg;

// 	//TRISE Configuration
// 	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
// 	{
// 		//mode is standard mode

// 		tempreg = (RCC_GetPCLK1Value() /1000000U) + 1 ;

// 	}else
// 	{
// 		//mode is fast mode
// 		tempreg = ( (RCC_GetPCLK1Value() * 300) / 1000000000U ) + 1;

// 	}

// 	pI2CHandle->pI2Cx->I2C_TRISE = (tempreg & 0x3F);

// }


// void I2C_DeInit(I2C_RegDef_t *pI2Cx)
// {

// }


// uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName)
// {
// 	if(pI2Cx->I2C_SR1 & FlagName)
// 	{
// 		return FLAG_SET;
// 	}
// 	return FLAG_RESET;
// }



// void I2C_MasterTxData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr)
// {
// 	// 1. Generate the START condition
// 	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

// 	//2. confirm that start generation is completed by checking the SB flag in the SR1
// 	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
// 	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2Cx_SB_FLAG)   );

// 	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits )
// 	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx,SlaveAddr);

// 	//4. Confirm that address phase is completed by checking the ADDR flag in teh SR1
// 	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2Cx_ADDR_FLAG)   );

// 	//5. clear the ADDR flag according to its software sequence
// 	//   Note: Until ADDR is cleared SCL will be stretched (pulled to LOW)
// 	I2C_ClearADDRFlag(pI2CHandle);

// 	//6. send the data until len becomes 0

// 	while(Len > 0)
// 	{
// 		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2Cx_TxE_FLAG) ); //Wait till TXE is set
// 		pI2CHandle->pI2Cx->I2C_DR = *pTxbuffer;
// 		pTxbuffer++;
// 		Len--;
// 	}

// 	//7. when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
// 	//   Note: TXE=1 , BTF=1 , means that both SR and DR are empty and next transmission should begin
// 	//   when BTF=1 SCL will be stretched (pulled to LOW)

// 	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2Cx_TxE_FLAG) );

// 	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2Cx_BTF_FLAG) );


// 	//8. Generate STOP condition and master need not to wait for the completion of stop condition.
// 	//   Note: generating STOP, automatically clears the BTF
// 	if(Sr == I2C_DISABLE_SR )
// 		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

// }


// void I2C_MasterRxData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr)
// {

// 	//1. Generate the START condition
// 	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

// 	//2. confirm that start generation is completed by checking the SB flag in the SR1
// 	//   Note: Until SB is cleared SCL will be stretched (pulled to LOW)
// 	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2Cx_SB_FLAG)   );

// 	//3. Send the address of the slave with r/nw bit set to R(1) (total 8 bits )
// 	I2C_ExecuteAddressPhaseRead(pI2CHandle->pI2Cx,SlaveAddr);

// 	//4. wait until address phase is completed by checking the ADDR flag in teh SR1
// 	while( !  I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2Cx_ADDR_FLAG)   );


// 	//procedure to read only 1 byte from slave
// 	if(Len == 1)
// 	{
// 		//Disable Acking
// 		I2C_ManageAck(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);


// 		//clear the ADDR flag
// 		I2C_ClearADDRFlag(pI2CHandle);

// 		//wait until  RXNE becomes 1
// 		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2Cx_RxNE_FLAG) );

// 		//generate STOP condition
// 		if(Sr == I2C_DISABLE_SR )
// 			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

// 		//read data in to buffer
// 		*pRxBuffer = pI2CHandle->pI2Cx->I2C_DR;

// 	}


//     //procedure to read data from slave when Len > 1
// 	if(Len > 1)
// 	{
// 		//clear the ADDR flag
// 		I2C_ClearADDRFlag(pI2CHandle);

// 		//read the data until Len becomes zero
// 		for ( uint32_t i = Len ; i > 0 ; i--)
// 		{
// 			//wait until RXNE becomes 1
// 			while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2Cx_RxNE_FLAG) );

// 			if(i == 2) //if last 2 bytes are remaining
// 			{
// 				//Disable Acking
// 				I2C_ManageAck(pI2CHandle->pI2Cx,I2C_ACK_DISABLE);

// 				//generate STOP condition
// 				if(Sr == I2C_DISABLE_SR )
// 					I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

// 			}

// 			//read the data from data register in to buffer
// 			*pRxBuffer = pI2CHandle->pI2Cx->I2C_DR;

// 			//increment the buffer address
// 			pRxBuffer++;

// 		}

// 	}

// 	//re-enable ACKing
// 	if(pI2CHandle->I2C_Config.I2C_AckControl == I2C_ACK_ENABLE)
// 	{
// 		I2C_ManageAck(pI2CHandle->pI2Cx,I2C_ACK_ENABLE);
// 	}

// }


// void I2C_ManageAck(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
// {
// 	if(EnorDi == I2C_ACK_ENABLE)
// 	{
// 		//enable the ack
// 		pI2Cx->I2C_CR1 |= ( 1 << I2Cx_ACK);
// 	}else
// 	{
// 		//disable the ack
// 		pI2Cx->I2C_CR1 &= ~( 1 << I2Cx_ACK);
// 	}
// }