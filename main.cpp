#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h> 
static GLfloat dx1 = 425.0, dy1 = -50.0, ds1 = 2;
static GLfloat dx2 = 425.0, dy2 = -85.0, ds2 = 4;
static GLfloat dx3 = 425.0, dy3 = -135.0, ds3 = 6;
static float flowerM = true;
static float flowerMS = 0;

static float road[2][3] = { {{80.0 / 255} ,{ 80.0 / 255 } ,{ 80.0 / 255 }} ,{{ 160.0 / 255 },{ 160.0 / 255 },{ 160.0 / 255 }}};
static float ground[2][3] = { { { 150.0 / 255 } ,{ 90.0 / 255 } ,{ 20.0 / 255 } } ,{ { 130.0 / 255 },{ 70.0 / 255 },{ 0.0 / 255 } } };
static float sky[2][3] = { { { 30.0 / 255 } ,{ 206.0 / 255 } ,{ 240.0 / 255 } } ,{ { 30.0 / 255 },{ 150.0 / 255 },{ 250.0 / 255 } } };

static int light = 0;
static int smoke = 0;

static float period = 0;
static int timeCount = 0;

static float firstCar[3] = { 220.0,220.0, 220.0 };
static float secondCar[3] = { 255.0,220.0,0 };
static float thirdCar[3] = { 0,180.0,255 };




void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(-330, 330, -170, 170.0);
}

void circle(float r, float x, float y, float quadrant) {
	glBegin(GL_POLYGON);
	for (float i = 0; i <= quadrant; i += 0.1) {
		glVertex2f(x + r * cos(i*3.14159265/180), y + r * sin(i*3.14159265/180));
	}
	glEnd();
}

void ellipse(float r1, float r2, float x, float y, float theta) {
	glBegin(GL_POLYGON);
	for (float i = 0; i <= 360; i += 1) {
		glVertex2f(x + (r1 * cos(i*3.14159265 / 180)*cos(theta*3.14159265 / 180) - r2 * sin(i*3.14159265 / 180)*sin(theta*3.14159265 / 180)), y + (r2 * sin(i*3.14159265 / 180)*cos(theta*3.14159265 / 180) + r1 * cos(i*3.14159265 / 180)*sin(theta*3.14159265 / 180)));
	}
	glEnd();
}


void flower(float r1, float r2, float x, float y, float height, float num, float rotate) {

	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(x, y - height);
	glEnd();

	for (float i = rotate; i <= 360 + rotate; i += 360 / num) {
		ellipse(r1, r2, x + r1 * cos(i*3.14159265 / 180), y + r1 * sin(i*3.14159265 / 180), i);
	}
}

void flower2(float r1, float r2, float x, float y, float height, float num, float rotate) {

	for (float i = rotate; i <= 360 + rotate; i += 360 / num) {
		ellipse(r1, r2, x + flowerMS, y, i);
	}

	glColor3f(255.0 / 255, 255.0 / 255, 40.0 / 255);
	circle(r1 / 2.25, x + flowerMS, y, 360);
	glLineWidth(4.0);
	glBegin(GL_LINES);
	glVertex2f(x + flowerMS, y - r1 + 2);
	glVertex2f(x , y - r1 - height);
	glEnd();

}

void garden(float r1, float r2, float x1, float x2, float y, float height, float num, float rotate) {

	srand(time(NULL));
	for (int i = x1; i <= x2; i += 35) {
		float c1 = (rand() % 255 + 50);
		float c2 = (rand() % 255 + 50);
		float c3 = (rand() % 255 + 50);
		height = rand() % 25 + 2 * r1;
		glColor3f(c1 / 255, c2 / 255, c3 / 255);
		flower2(r1, r2, i , y + height, height, num, rotate + 90);
	}
}


void fense(float x1, float x2, float y, float offset) {


	for (float i = x1; i <= x2; i += 9 * offset) {	//draw fense 
		glBegin(GL_POLYGON);
		glVertex2f(i, y);
		glVertex2f(i + 4 * offset, y);
		glVertex2f(i + 4 * offset, y + 17 * offset);
		glVertex2f(i + 2 * offset, y + 19 * offset);
		glVertex2f(i, y + 17 * offset);
		glEnd();
	}

	for (float i = x1; i <= x2; i += 7.0 * offset) {	//draw line
		glBegin(GL_POLYGON);
		glVertex2f(i, y + 4 * offset);
		glVertex2f(i + 8 * offset, y + 4 * offset);
		glVertex2f(i + 8 * offset, y + 7 * offset);
		glVertex2f(i, y + 7 * offset);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(i, y + 11 * offset);
		glVertex2f(i + 8 * offset, y + 11 * offset);
		glVertex2f(i + 8 * offset, y + 14 * offset);
		glVertex2f(i, y + 14 * offset);
		glEnd();
	}
}

void car(float x, float y, float offset, float c1, float c2, float c3) {


	glColor3f(0.0 / 255, 0.0 / 255, 0.0 / 255);//เงา
	ellipse(72.5 * offset, 7.5 * offset, x, y - 45 * offset, 0);

	//car structure
	glColor3f(c1 / 255, c2 / 255, c3 / 255);
	glBegin(GL_POLYGON);
	glVertex2f(x - 75 * offset, y - 35 * offset);
	glVertex2f(x + 75 * offset, y - 35 * offset);
	glVertex2f(x + 75 * offset, y + 35 * offset);
	glVertex2f(x - 22.5 * offset, y + 35 * offset);
	glVertex2f(x - 32.5 * offset, y + 10 * offset);
	glVertex2f(x - 75 * offset, y);
	glVertex2f(x - 75 * offset, y - 35 * offset);
	glEnd();

	//car accessory
	glColor3f(190.0 / 255, 190.0 / 255, 190.0 / 255);//กันชนหน้า
	glBegin(GL_POLYGON);
	glVertex2f(x - 80 * offset, y - 35 * offset);
	glVertex2f(x - 50 * offset, y - 35 * offset);
	glVertex2f(x - 50 * offset, y - 22.5 * offset);
	glVertex2f(x - 80 * offset, y - 22.5 * offset);
	glEnd();

	glColor3f(150.0 / 255, 150.0 / 255, 150.0 / 255);//ท่อไอเสีย
	glBegin(GL_POLYGON);
	glVertex2f(x + 75 * offset, y - 35 * offset);
	glVertex2f(x + 75 * offset, y - 30 * offset);
	glVertex2f(x + 82.5 * offset, y - 30 * offset);
	glVertex2f(x + 82.5 * offset, y - 35 * offset);
	glEnd();

	if (smoke <= 7 && smoke > 0) {
		glColor4f(150.0 / 255, 150.0 / 255, 150.0 / 255 ,0.5);
		circle(10, x + 84.5 * offset, y - 32.5 * offset , 360);
	}
	else if (smoke <= 14) {
		glColor4f(150.0 / 255, 150.0 / 255, 150.0 / 255, 0.5);
		circle(10, x + 84.5 * offset, y - 32.5 * offset, 360);
		circle(15, x + 99.5 * offset, y - 32.5 * offset, 360);
	}
	else if (smoke <= 21) {
		glColor4f(150.0 / 255, 150.0 / 255, 150.0 / 255, 0.5);
		circle(10, x + 84.5 * offset, y - 32.5 * offset, 360);
		circle(15, x + 99.5 * offset, y - 32.5 * offset, 360);
		circle(20, x + 124.5 * offset, y - 32.5 * offset, 360);
	}

	glColor3f(190.0 / 255, 190.0 / 255, 190.0 / 255);//กันชนหลัง
	glBegin(GL_POLYGON);
	glVertex2f(x + 70 * offset, y - 35 * offset);
	glVertex2f(x + 77.5 * offset, y - 35 * offset);
	glVertex2f(x + 77.5 * offset, y - 22.5 * offset);
	glVertex2f(x + 70 * offset, y - 22.5 * offset);
	glEnd();

	glColor3f(210.0 / 255, 210.0 / 255, 210.0 / 255); //เส้นข้าง
	glBegin(GL_LINES);
	glVertex2f(x - 75 * offset, y - 9.75 * offset);
	glVertex2f(x + 75 * offset, y - 9.75 * offset);
	glEnd();

	glColor3f(180.0 / 255, 180.0 / 255, 180.0 / 255); //เส้นข้าง
	glBegin(GL_LINES);
	glVertex2f(x + 5 * offset, y - 35 * offset);
	glVertex2f(x + 5 * offset, y + 35 * offset);
	glEnd();

	glColor3f(160.0 / 255, 160.0 / 255, 160.0 / 255);//กระจกมองหลัง
	glBegin(GL_POLYGON);
	glVertex2f(x - 34 * offset, y + 2.5 * offset);
	glVertex2f(x - 34 * offset, y + 12.5 * offset);
	glVertex2f(x - 36.5 * offset, y + 12.5 * offset);
	glVertex2f(x - 36.5 * offset, y + 2.5 * offset);
	glEnd();

	glColor3f(160.0 / 255, 160.0 / 255, 160.0 / 255);//ที่เปิดประตู
	glBegin(GL_POLYGON);
	glVertex2f(x + 1.5 * offset, y - 15.0 * offset);
	glVertex2f(x + 1.5 * offset, y - 5.0 * offset);
	glVertex2f(x - 1.5 * offset, y - 5.0 * offset);
	glVertex2f(x - 1.5 * offset, y - 15.0 * offset);
	glEnd();

	if (light == 0) {
		glColor3f(240.0 / 255, 240.0 / 255, 240.0 / 255);//ไฟหน้า
		glBegin(GL_POLYGON);
		glVertex2f(x - 75 * offset, y - 22.5 * offset);
		glVertex2f(x - 75 * offset, y - 10 * offset);
		glColor3f(180.0 / 255, 180.0 / 255, 180.0 / 255);
		glVertex2f(x - 55 * offset, y - 10 * offset);
		glVertex2f(x - 55 * offset, y - 17.5 * offset);
		glVertex2f(x - 62.5 * offset, y - 22.5 * offset);
		glEnd();
	}
	else {
		glColor3f(240.0 / 255, 240.0 / 255, 0.0 / 255);//ไฟหน้า
		glBegin(GL_POLYGON);
		glVertex2f(x - 75 * offset, y - 22.5 * offset);
		glVertex2f(x - 75 * offset, y - 10 * offset);
		glColor3f(180.0 / 255, 180.0 / 255, 180.0 / 255);
		glVertex2f(x - 55 * offset, y - 10 * offset);
		glVertex2f(x - 55 * offset, y - 17.5 * offset);
		glVertex2f(x - 62.5 * offset, y - 22.5 * offset);
		glEnd();

		glColor4f(240.0 / 255, 240.0 / 255, 0.0 / 255,0.8);
		glBegin(GL_POLYGON);
		glVertex2f(x - 75 * offset, y - 22.5 * offset);
		glVertex2f(x - 75 * offset, y - 10 * offset);
		glColor4f(255.0 / 255, 255.0 / 255, 0.0 / 255,0.5);
		glVertex2f(x - 175 * offset, y - 45 * offset);
		glVertex2f(x - 125 * offset, y - 45 * offset);
		glEnd();

		ellipse(50 * offset, 12.5 * offset, x - 135 * offset, y - 45 * offset, 0);
	}

	glColor3f(180.0 / 255, 180.0 / 255, 180.0 / 255);//ไฟหลัง
	glBegin(GL_POLYGON);
	glVertex2f(x + 75 * offset, y - 22.5 * offset);
	glVertex2f(x + 75 * offset, y - 20 * offset);
	glColor3f(240.0 / 255, 240.0 / 255, 240.0 / 255);
	glVertex2f(x + 65 * offset, y - 20 * offset);
	glVertex2f(x + 65 * offset, y - 22.5 * offset);
	glEnd();
	glColor3f(240.0 / 255, 80.0 / 255, 50.0 / 255);
	glBegin(GL_POLYGON);
	glVertex2f(x + 75 * offset, y - 20 * offset);
	glVertex2f(x + 75 * offset, y - 10 * offset);
	glColor3f(240.0 / 255, 240.0 / 255, 240.0 / 255);
	glVertex2f(x + 65 * offset, y - 10 * offset);
	glVertex2f(x + 65 * offset, y - 20 * offset);
	glEnd();

	glLineWidth(2.5);//ตัดเส้นไฟหลัง
	glColor3f(150.0 / 255, 150.0 / 255, 150.0 / 255);
	glBegin(GL_LINES);
	glVertex2f(x + 75 * offset, y - 10 * offset);
	glVertex2f(x + 75 * offset, y - 22.5 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x + 75 * offset, y - 22.5 * offset);
	glVertex2f(x + 65 * offset, y - 22.5 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x + 65 * offset, y - 22.5 * offset);
	glVertex2f(x + 65 * offset, y - 10 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x + 65 * offset, y - 10 * offset);
	glVertex2f(x + 75 * offset, y - 10 * offset);
	glEnd();

	glLineWidth(2.5);//ตัดเส้นไฟหน้า
	glColor3f(150.0 / 255, 150.0 / 255, 150.0 / 255);
	glBegin(GL_LINES);
	glVertex2f(x - 75 * offset, y - 22.5 * offset);
	glVertex2f(x - 75 * offset, y - 10 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x - 75 * offset, y - 10 * offset);
	glVertex2f(x - 55 * offset, y - 10 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x - 55 * offset, y - 10 * offset);
	glVertex2f(x - 55 * offset, y - 17.5 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x - 55 * offset, y - 17.5 * offset);
	glVertex2f(x - 62.5 * offset, y - 22.5 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x - 62.5 * offset, y - 22.5 * offset);
	glVertex2f(x - 75 * offset, y - 22.5 * offset);
	glEnd();

	glColor3f(240.0 / 255, 240.0 / 255, 240.0 / 255);//กระจกหน้า
	glBegin(GL_POLYGON);
	glVertex2f(x - 45 * offset, y + 8 * offset);
	glVertex2f(x - 45 * offset, y + 3 * offset);
	glColor3f(180.0 / 255, 180.0 / 255, 180.0 / 255);
	glVertex2f(x - 22.5 * offset, y + 30 * offset);
	glVertex2f(x - 22.5 * offset, y + 35 * offset);
	glEnd();

	glColor3f(150.0 / 255, 150.0 / 255, 150.0 / 255); //ตัดเส้นกระจกหน้า
	glBegin(GL_LINES);
	glVertex2f(x - 45 * offset, y + 8 * offset);
	glVertex2f(x - 45 * offset, y + 3 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x - 45 * offset, y + 3 * offset);
	glVertex2f(x - 22.5 * offset, y + 30 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x - 22.5 * offset, y + 30 * offset);
	glVertex2f(x - 22.5 * offset, y + 35 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x - 22.5 * offset, y + 35 * offset);
	glVertex2f(x - 45 * offset, y + 8 * offset);
	glEnd();

	glColor3f(240.0 / 255, 240.0 / 255, 240.0 / 255);//กระจกข้าง
	glBegin(GL_POLYGON);
	glVertex2f(x - 17.5* offset, y + 30 * offset);
	glVertex2f(x - 32.5 * offset, y + 10.5 * offset);
	glVertex2f(x - 32.5 * offset, y + 3 * offset);
	glColor3f(180.0 / 255, 180.0 / 255, 180.0 / 255);
	glVertex2f(x, y + 3 * offset);
	glVertex2f(x, y + 30 * offset);
	glVertex2f(x, y + 30 * offset);
	glEnd();

	glColor3f(150.0 / 255, 150.0 / 255, 150.0 / 255); //ตัดเส้นกระจกข้าง
	glBegin(GL_LINES);
	glVertex2f(x - 17.5 * offset, y + 30 * offset);
	glVertex2f(x - 32.5 * offset, y + 10.5 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x - 32.5 * offset, y + 10.5 * offset);
	glVertex2f(x - 32.5 * offset, y + 3 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x - 32.5 * offset, y + 3 * offset);
	glVertex2f(x, y + 3 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x, y + 3 * offset);
	glVertex2f(x, y + 30 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x, y + 30 * offset);
	glVertex2f(x, y + 30 * offset);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(x , y + 30 * offset);
	glVertex2f(x - 17.5* offset, y + 30 * offset);
	glEnd();

	glColor3f(0 / 255, 0.0 / 255, 0.0 / 255);//ล้อรถ
	circle(20 * offset, x - 37.5 * offset, y - 35 * offset, 180);
	circle(20 * offset, x + 37.5 * offset, y - 35 * offset, 180);

	glColor3f(80.0 / 255, 80.0 / 255, 80.0 / 255);
	circle(17.5 * offset, x - 37.5 * offset, y - 35 * offset, 360);
	circle(17.5 * offset, x + 37.5 * offset, y - 35 * offset, 360);

	glColor3f(130.0 / 255, 130.0 / 255, 130.0 / 255);
	circle(12.5 * offset, x - 37.5 * offset, y - 35 * offset, 360);
	circle(12.5 * offset, x + 37.5 * offset, y - 35 * offset, 360);

	glColor3f(100.0 / 255, 100.0 / 255, 100.0 / 255);
	ellipse(12.5 * offset, 2 * offset, x - 37.5 * offset, y - 35 * offset, -dx1);
	ellipse(12.5 * offset, 2 * offset, x + 37.5 * offset, y - 35 * offset, -dx1);
	ellipse(12.5 * offset, 2 * offset, x - 37.5 * offset, y - 35 * offset, -dx1 + 90);
	ellipse(12.5 * offset, 2 * offset, x + 37.5 * offset, y - 35 * offset, -dx1 + 90);


}

void house(float x, float y, float offset) {

	glColor3f(200.0 / 255, 200.0 / 255, 200.0 / 255);//บ้านเทา
	glBegin(GL_POLYGON);
	glVertex2f(x - 50 * offset, y);
	glVertex2f(x, y);
	glVertex2f(x, y + 75 * offset);
	glVertex2f(x - 50 * offset, y + 45 * offset);
	glEnd();
	glColor3f(150.0 / 255, 150.0 / 255, 150.0 / 255);
	glBegin(GL_POLYGON);
	glVertex2f(x - 55 * offset, y + 40 * offset);
	glVertex2f(x + 5 * offset, y + 75 * offset);
	glVertex2f(x + 5 * offset, y + 78 * offset);
	glVertex2f(x - 55 * offset, y + 43 * offset);
	glEnd();

	glColor3f(90.0 / 255, 30.0 / 255, 0.0 / 255);//ประตูบ้านเทา
	glBegin(GL_POLYGON);
	glVertex2f(x - 5 * offset, y);
	glVertex2f(x - 25 * offset, y);
	glVertex2f(x - 25 * offset, y + 32.5 * offset);
	glVertex2f(x - 5 * offset, y + 32.5 * offset);
	glEnd();
	for (int i = 5; i <= 27.5; i += 7) {
		glColor3f(180.0 / 255, 180.0 / 255, 200.0 / 255);//ประตูบ้านเทา
		glBegin(GL_POLYGON);
		glVertex2f(x - 9 * offset, y + i * offset);
		glVertex2f(x - 21 * offset, y + i * offset);
		glColor3f(65.0 / 255, 75.0 / 255, 200.0 / 255);
		glVertex2f(x - 21 * offset, y + (i + 2.5) * offset);
		glVertex2f(x - 9 * offset, y + (i + 2.5) * offset);
		glEnd();
	}
	glColor3f(255.0 / 255, 255.0 / 255, 0.0 / 255);
	circle(1 * offset, x - 7 * offset, y + 15 * offset, 360);

	glColor3f(140.0 / 255, 70.0 / 255, 0 / 255);//บ้านไม้
	glBegin(GL_POLYGON);
	glVertex2f(x + 50 * offset, y);
	glVertex2f(x, y);
	glVertex2f(x, y + 60 * offset);
	glVertex2f(x + 50 * offset, y + 40 * offset);
	glEnd();
	glColor3f(220.0 / 255, 150.0 / 255, 50.0 / 255);
	glLineWidth(2.0);
	for (int i = 0; i <= 20; i += 4) {
		glBegin(GL_LINES);
		glVertex2f(x, y + (40 + i) * offset);
		glVertex2f(x + (20 - i) * 2.5 * offset, y + (40 + i)* offset);
		glEnd();
	}
	glColor3f(90.0 / 255, 20.0 / 255, 0.0 / 255);
	glBegin(GL_POLYGON);
	glVertex2f(x + 50 * offset, y + 40 * offset);
	glVertex2f(x + 50 * offset, y + 43 * offset);
	glVertex2f(x, y + 63 * offset);
	glVertex2f(x, y + 60 * offset);
	glEnd();

	glColor3f(0.0 / 255, 30.0 / 255, 50.0 / 255);//บ้านน้ำเงิน
	glBegin(GL_POLYGON);
	glVertex2f(x + 50 * offset, y);
	glVertex2f(x, y);
	glVertex2f(x, y + 45 * offset);
	glVertex2f(x + 50 * offset, y + 45 * offset);
	glEnd();
	glColor3f(200.0 / 255, 0.0 / 255, 0.0 / 255);
	glBegin(GL_POLYGON);
	glVertex2f(x - 10 * offset, y + 40 * offset);
	glVertex2f(x + 25 * offset, y + 58 * offset);
	glVertex2f(x + 60 * offset, y + 40 * offset);
	glEnd();

	glColor3f(150.0 / 255, 150.0 / 255, 150.0 / 255);//ประตูบ้านน้ำเงิน
	glBegin(GL_POLYGON);
	glVertex2f(x + 42 * offset, y);
	glVertex2f(x + 8 * offset, y);
	glVertex2f(x + 8 * offset, y + 35 * offset);
	glVertex2f(x + 42 * offset, y + 35 * offset);
	glEnd();
	glColor3f(120.0 / 255, 120.0 / 255, 120.0 / 255);
	glLineWidth(2.0);
	for (int i = 0; i <= 35; i += 5) {
		glBegin(GL_LINES);
		glVertex2f(x + 42 * offset, y + i * offset);
		glVertex2f(x + 8 * offset, y + i * offset);
		glEnd();
	}

}

void draw() {
	glColor3f(road[0][0] - 20.0 * period / 255, road[0][1] - 20.0 * period / 255, road[0][2] - 20.0 * period / 255);//ถนน
	glBegin(GL_POLYGON);
	glVertex2f(330, -170);
	glVertex2f(-330, -170);
	glColor3f(road[1][0] - 20.0 * period / 255, road[1][1] - 20.0 * period / 255, road[1][2] - 20.0 * period / 255);
	glVertex2f(-330, -80);
	glVertex2f(330, -80);
	glEnd();

	glColor3f(ground[0][0] - 20.0 * period / 255, ground[0][1] - 20.0 * period / 255, ground[0][2] - 20.0 * period / 255);//ดิน
	glBegin(GL_POLYGON);
	glVertex2f(330, -80);
	glVertex2f(-330, -80);
	glColor3f(ground[1][0] - 20.0 * period / 255, ground[1][1] - 20.0 * period / 255, ground[1][2] - 20.0 * period / 255);
	glVertex2f(-330, -20);
	glVertex2f(330, -20);
	glEnd();

	if (period == 0) {
		glColor3f(sky[0][0], sky[0][1], sky[0][2]);//ท้องฟ้า
		glBegin(GL_POLYGON);
		glVertex2f(330, -20);
		glVertex2f(-330, -20);
		glColor3f(sky[1][0], sky[1][1], sky[1][2]);
		glVertex2f(-330, 170);
		glVertex2f(330, 170);
		glEnd();
	}
	else if (period == 1) {
		glColor3f(245.0 / 255, 190.0 / 255, 0);
		glBegin(GL_POLYGON);
		glVertex2f(330, -20);
		glVertex2f(-330, -20);
		glColor3f(195.0 / 255, 105.0 / 255, 0);
		glVertex2f(-330, 170);
		glVertex2f(330, 170);
		glEnd();
	}
	else {
		glColor3f(25.0 / 255, 25.0 / 255, 112.0 / 255);//ท้องฟ้า
		glBegin(GL_POLYGON);
		glVertex2f(330, -20);
		glVertex2f(-330, -20);
		glColor3f(0.0 / 255, 0.0/255, 20.0/255);
		glVertex2f(-330, 170);
		glVertex2f(330, 170);
		glEnd();
	}

	house(150, -75, 2);

	garden(15, 10, -325, 40, -60, 30, 6, 90);

	glColor3f(240.0 / 255, 180.0 / 255, 180.0 / 255);
	fense(-330, 40, -75, 2);
	fense(255, 330, -75, 2);

	car(dx1, dy1,1 + (-dy1 - 50)*0.005, firstCar[0], firstCar[1], firstCar[2]);
	car(dx2, dy2, 1 + (-dy2 - 50)*0.005, secondCar[0], secondCar[1], secondCar[2]);
	car(dx3, dy3, 1 + (-dy3 - 50)*0.005, thirdCar[0], thirdCar[1], thirdCar[2]);


	if (dx1 <= -425) {
		dx1 = 425;
		dy1 = -(rand() % 25 + 50);
		ds1 = 2 + (rand() % 2 + 1);
		firstCar[0] = rand() % 255 + 50;
		firstCar[1] = rand() % 255 + 50;
		firstCar[2] = rand() % 255 + 50;
	}
	else
		dx1 -= ds1;

	if (dx2 <= -425) {
		dx2 = 425;
		dy2 = -(rand() % 25 + 85);
		ds2 = 4 + (rand() % 2 + 1);
		secondCar[0] = rand() % 255 + 50;
		secondCar[1] = rand() % 255 + 50;
		secondCar[2] = rand() % 255 + 50;
	}
	else
		dx2 -= ds2;

	if (dx3 <= -425) {
		dx3 = 425;
		dy3 = -(rand() % 25 + 135);
		ds3 = 6 + (rand() % 2 + 1);
		thirdCar[0] = rand() % 255 + 50;
		thirdCar[1] = rand() % 255 + 50;
		thirdCar[2] = rand() % 255 + 50;
	}
	else
		dx3 -= ds3;


	if (flowerM == true) {
		flowerMS-= 0.5;
		if (flowerMS< -10)
			flowerM = false;
	}
	else {
		flowerMS+=0.5;
		if (flowerMS >= 10)
			flowerM = true;
	}

	if (smoke >= 21) {
		smoke = 0;
	}
	else {
		smoke++;
	}

	timeCount++;
	if (timeCount == 180) {
		timeCount = 0;
		period++;
		light++;
		if (period > 2) {
			period = 0;
			light = 0;
		}
	}
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
	//glFlush();
	glutSwapBuffers(); // Swap the buffers.
}


void mouse(int button, int state, int x, int y)
{
	int i;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			for (i = 1; i <= 10; i++) {
				glutIdleFunc(display);
			}
		break;
	case GLUT_MIDDLE_BUTTON:
	default:
		break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("CG-HW1");
	glutDisplayFunc(display);
	init();
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}