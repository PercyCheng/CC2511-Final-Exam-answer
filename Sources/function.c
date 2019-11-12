void delay(int time_expect) {
	word time;
	int counter = time_expect / 1000;
	FC321_Reset();
	do {
		FC321_GetTimeMS(&time);
	} while (time < time_expect);
}
void drawTheme() {
	Term1_MoveTo(3, 3);
	Term1_SetColor(clYellow, clBlack);
	Term1_SendStr("CC2511 Exam 2018");
	Term1_MoveTo(3, 4);
	Term1_SendStr("_____________________   Cheng Peng");
	Term1_MoveTo(3, 5);
	Term1_SetColor(clCyan, clBlack);
	Term1_SendStr("Prompt: ");
	Term1_MoveTo(13, 5);
}
void GUIStart() {
	Term1_MoveTo(3, 13);
	Term1_SendStr("Press 'm' for Monitoring mode");
	Term1_MoveTo(3, 14);
	Term1_SendStr("Press 'g' for Gaming mode");
	Term1_MoveTo(3, 15);
	Term1_SendStr("Press 'q' to quit");
}

void GUIMonitorMode(int x_measured, int x_smooth) {
	Term1_MoveTo(13, 5);
	Term1_EraseLine();
	Term1_SetColor(clWhite, clBlack);
	Term1_EraseLine();
	Term1_SendStr("Monitoring mode ");
	Term1_MoveTo(3, 9);
	Term1_SendStr("X smooth is :");
	Term1_SendNum(x_smooth);
	Term1_MoveTo(3, 8);
	Term1_SendStr("X measured is :");
	Term1_SendNum(x_measured);
	if (x_measured < x_smooth) {
		Green_SetRatio16(0);
		Blue_SetRatio16(0);
	} else if (x_measured >= x_smooth) {
		Green_SetRatio16(0);
		Blue_SetRatio16(65535 / 10);
	}
}
float calculateX_measured() {
	AD1_Measure(TRUE);
	AD1_GetValue16(&value);
	x_measured = (3.3 * value * 1000) / 65535.0;
	delay(monitorTime);
	return x_measured;
}
float calculateX_smooth( x_measured) {
	float a = 0.9;
	x_smooth = a * x_smooth + (1 - a) * x_measured;
	return x_smooth;
}
void GUIGamingMode(int a, int b, int r) {
	Term1_MoveTo(3, 6);
	Term1_SetColor(clWhite, clBlack);
	Term1_EraseLine();
	Term1_SendStr("Entering Gaming Mode");
	Term1_MoveTo(3, 8);
	Term1_SendStr("Equation is :");
	Term1_SendNum(a);
	Term1_SendStr(" - ");
	Term1_SendNum(r);
	Term1_SendStr(" = ");
	Term1_MoveTo(3, 9);
	Term1_SendStr("Please Enter Your Answer: ");
	delay(monitorTime);
}
int rand(void);
void srand(unsigned int seed);
int generateRandom(int min, int max) {
	int num;
	num = rand() % (max + 1 - min) + min;
	return num;
}

void cleanPromot() {
	Term1_MoveTo(13, 5);
	Term1_EraseLine();
	Term1_MoveTo(3, 6);
	Term1_EraseLine();
	Term1_MoveTo(3, 7);
	Term1_EraseLine();
	Term1_MoveTo(3, 8);
	Term1_EraseLine();
	Term1_MoveTo(3, 9);
	Term1_EraseLine();
	Term1_MoveTo(3, 10);
	Term1_EraseLine();
	Term1_MoveTo(3, 11);
	Term1_EraseLine();
	Term1_MoveTo(3, 6);
}

int calculatePWM(int score) {
	int pwm;
	if (score >= -5 && score <= 5) {
		pwm = sqrt(score * score) * 65535 / 5;
	} else {
		pwm = 65535;
	}
}
void setPWM(int score, int pwm) {
	if (score == 0) {
		Red_SetRatio16(0);
		Red_SetRatio16(0);
	} else if (score > 0) {
		Red_SetRatio16(0);
		Green_SetRatio16(pwm);
	} else if (score < 0) {
		Red_SetRatio16(pwm);
		Green_SetRatio16(0);
	}
}
void GUIWin() {
	Term1_MoveTo(3, 7);
	Term1_SendStr("You are winner!");
	Term1_MoveTo(3, 8);
	Term1_SendStr("Game finished!");
}