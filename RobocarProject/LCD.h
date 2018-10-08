/*
 * LCD.h
 *
 * Created: 2016/1/18 23:35:09
 *  Author: Drim
 */ 


#ifndef LCD_H_
#define LCD_H_



namespace LCD
{

	enum {LINE1=0, LINE2=64, FOLLOW=254, STATUS=255};

	void print(unsigned char position, const char *s);
	void print(unsigned char position, char *s);
	
	void printS2(int numberL,int numberR);
	void itos(int i, char *b, unsigned char digit);
	unsigned int mod10(int *p);
	void itosbinary(unsigned int i, char *b, unsigned char digit);
	unsigned int mod2(unsigned int *p) ;


}



#endif /* LCD_H_ */