#ifndef __JKD_OLED_H
#define __JKD_OLED_H

void jkd_OLED_Init(void);
void jkd_OLED_Clear(void);
void jkd_OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void jkd_OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif
