/*
 * File:   lcd_16x2.c
 * Author: Wilson
 *
 * Created on 10 de Novembro de 2019, 09:46
 */

#include <xc.h>
#include "mcc.h"
#include "lcd_16x2.h"

void screen_1() {//min 125khz 250khz max 350

    char cont_screen;
    cont_screen++;

    if (cont_screen > 250) {

        cont_screen = 0;

        send_instruction_8bit(cursor_LxC_1x6); //cursor linha 2
        float data = 10.555;
        send_data_float(data);

        send_instruction_8bit(cursor_LxC_1x0); //cursor linha 2
        unsigned int ten = 10;
        send_data_un_int(ten);

        send_instruction_8bit(cursor_LxC_0x0);
        char text[] ="Wilson Queiroz";
        send_str(text);
        
        send_instruction_8bit(cursor_LxC_0x15);
        unsigned char ch = 8;
        send_data_char(ch);
        
        send_instruction_8bit(cursor_LxC_1x15);
    }
}

void send_data_float(float data) {
    char *buf;
    int status;
    buf = ftoa(data, &status);
    send_str(buf);
}

void send_data_char(unsigned char data) {
    char buf[10];
    itoa(buf, data, 10);
    send_str(buf);
}

void send_data_un_int(unsigned int data) {
    char buf[10];
    utoa(buf, data, 10);
    send_str(buf);
}

/*LCD srt*/
void send_str(unsigned char *data) {
    for (unsigned char i = 0; *data != 0; i++) {
        send_data_8bit(*data);
        data++;
    }
}

/*LCD Initialization*/
void CONFIG_lcd16x2(void) {
    /*
     * HD44780U
     * Initialization 4-Bit Interface
     */
    __delay_ms(40);
    //step 1 (0x03)   
    __delay_ms(15); //wait 15ms for 4.5V , wait 40ms for 2.7V 
    send_instruction_4bit(step_1);

    //step 2 (0x03)   
    __delay_ms(5);//wait
    send_instruction_4bit(step_2);

    //step 3 (0x03)
    __delay_us(100);//wait
    send_instruction_4bit(step_3);

    //step 4 (0x02)
    send_instruction_4bit(step_4);

    //step 5
    send_instruction_8bit(lcd_16x2_2lines_4bits_5x8dots);

    //step 6
    send_instruction_8bit(lcd_16x2_cursorincrement_onwhite);

    //step 7
    send_instruction_8bit(clear_lcd_16x2);

    //step 8
    send_instruction_8bit(lcd_16x2_lcdON_cursorON_blinkcursorON);

}

void send_instruction_8bit(unsigned char data) {
    
    start_instruction();
    //high
    D7_LCD = (unsigned) (data & 0x80) >> 7;
    D6_LCD = (unsigned) (data & 0x40) >> 6;
    D5_LCD = (unsigned) (data & 0x20) >> 5;
    D4_LCD = (unsigned) (data & 0x10) >> 4;

    E_write();
    //low
    D7_LCD = (unsigned) (data & 0x08) >> 3;
    D6_LCD = (unsigned) (data & 0x04) >> 2;
    D5_LCD = (unsigned) (data & 0x02) >> 1;
    D4_LCD = (unsigned) (data & 0x01);

    E_write();

}

void send_instruction_4bit(unsigned char data) {

    start_instruction();
    //low
    D7_LCD = (unsigned) (data & 0x08) >> 3;
    D6_LCD = (unsigned) (data & 0x04) >> 2;
    D5_LCD = (unsigned) (data & 0x02) >> 1;
    D4_LCD = (unsigned) (data & 0x01);

    E_write();
}

void send_data_8bit(unsigned char data) {
    
    start_data_8_bit();
    //high
    D7_LCD = (unsigned) (data & 0x80) >> 7;
    D6_LCD = (unsigned) (data & 0x40) >> 6;
    D5_LCD = (unsigned) (data & 0x20) >> 5;
    D4_LCD = (unsigned) (data & 0x10) >> 4;

    E_write();
    //low
    D7_LCD = (unsigned) (data & 0x08) >> 3;
    D6_LCD = (unsigned) (data & 0x04) >> 2;
    D5_LCD = (unsigned) (data & 0x02) >> 1;
    D4_LCD = (unsigned) (data & 0x01);

    E_write();
}

void E_write(void) {
    __delay_ms(1);
    E_LCD = 1;
    E_LCD = 0;
}

void start_instruction(void) {
    __delay_ms(1);
    RS_LCD = 0;
    RW_LCD = 0;
    E_LCD = 0;
}

void start_data_8_bit(void) {
    __delay_ms(1);
    RS_LCD = 1;
    RW_LCD = 0;
    E_LCD = 0;
}
