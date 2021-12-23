#include <windows.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <iostream>
#include <string>
#include <math.h>


static double x=0.0;
static double move=-60;
bool newModel=false;
bool sig_1=false;
bool sig_2=false;
bool sig_3=false;
bool goUp=false;
bool goDown=false;
float x1=11,x2=-11; //starting train location
static float y_1=0;
static float y_2=0;
void 
stroke_output(GLfloat x, GLfloat y, char *format,...)
{
va_list args;
char buffer[200], *p;
va_start(args, format);
vsprintf(buffer, format, args);
va_end(args);
glPushMatrix();
glTranslatef(-2.5, y, 0);
glScaled(0.003, 0.005, 0.005);
for (p = buffer; *p; p++)
 glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
glPopMatrix();
}
void track(){
glPushMatrix();
glScaled(100.8,0.1,0.1);
glutSolidCube(1);
glPopMatrix();
}
void mat(){
glPushMatrix();
glScaled(100,0.35,1);
glBegin(GL_POLYGON);
glVertex2f(-1,-1);
 
glVertex2f(1,-1);
glVertex2f(1,1);
glVertex2f(-1,1);
glEnd();
glPopMatrix();
}
void stripes(){
glPushMatrix();
glScaled(0.1,1.57,0.1);
glutSolidCube(.5);
glPopMatrix();
}
void tyre(){
glPushMatrix();
 
glScaled(0.5,0.5,0.5);
glutSolidTorus(0.1,0.3,20,20);
glPopMatrix();
}
void train(){
// engine
// chimni
glPushMatrix();
glTranslatef(-3.7,1.5,0);
//glutSolidSphere(0.5,20,20);
glScaled(0.2,3,0.2);
glRotatef(90,1,0,0);
glutSolidTorus(0.2,0.6,50,50);
glPopMatrix();

glPushMatrix();
glTranslatef(-3.5,1,0);
glColor3f(0.0,1,1);
glutSolidCube(1);
glPopMatrix();
glPushMatrix();
glTranslatef(-4.0,0.8,0.0);
glRotatef(-45,0,0,1);
glScaled(0.6,.6,.6);
glColor3d(1,1,0);
glutSolidTetrahedron();
glPopMatrix();
glPushMatrix();
glTranslatef(0.3,1.0,0);
glRotatef(135,0,0,1);
glScaled(3.2,0.1,0.1);
glutSolidCube(0.5);
glPopMatrix();

}
void signals(){
glPushMatrix();
glScaled(0.7,0.7,0.7);
glutSolidSphere(0.5,20,20);
glPopMatrix();
glPushMatrix();
glColor3f(0,1,1);
glScaled(1.0,1.3,0.3);
glutSolidCube(1.0);
glPopMatrix();

}
int angX,angY,angZ=0;
// Main Drawing 
void trainSimulation()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glLoadIdentity();
 glTranslatef(0.0f,0.0f,-13.0f);
glRotatef(angX,0,1,1);
glRotatef(angY,1,0,1);
glRotatef(angZ,1,1,0);

// track 1
glPushMatrix();
glTranslatef(0,-1.0,0);
glPushMatrix();
glTranslatef(0,3.7,-10);
track();
glPopMatrix();
glPushMatrix();
glTranslatef(0,3.5,-10);
mat();
glPopMatrix();
glPushMatrix();
glTranslatef(0,3,-10);
track();
glPopMatrix();
float j;

// Stripes
for(j=0;j<=50;j+=0.5){
glPushMatrix();
glColor3f(1,1,1);
glTranslatef(-10+j,3.4,-10);
stripes();
glPopMatrix();
}
glPopMatrix();
glPushMatrix();
//2nd track
glPushMatrix();
glTranslatef(0,0.8,-10);
track();
glPopMatrix();

glPushMatrix();
glTranslatef(0,0.5,-10);
mat();
glPopMatrix();
glPushMatrix();
glTranslatef(0,0,-10);
track();
glPopMatrix();
//2nd Stripes
for(j=0;j<=50;j+=0.5){
glPushMatrix();
glColor3f(1,1,1);
glTranslatef(-10+j,0.5,-10);
stripes();
glPopMatrix();
}
glPopMatrix();

// track 3
glPushMatrix();
glTranslatef(0,1.0,0);
//3rd track
glPushMatrix();
glTranslatef(0,-2.2,-10);
track();
glPopMatrix();
glPushMatrix();
glTranslatef(0,-2.5,-10);
glColor3f(1,0,0);
mat();
glPopMatrix();
glPushMatrix();
glTranslatef(0,-3,-10);
track();
glPopMatrix();

//3rd Stripes
for(j=0;j<=50;j+=0.5){
glPushMatrix();
glColor3f(1,1,1);
glTranslatef(-10+j,-2.5,-10);
stripes();
glPopMatrix();
}
glPopMatrix();
/*** Track ENDS ******/
glPushMatrix();

glPopMatrix();
glPushMatrix();
glTranslatef(-3.5,2.8,0);
if(sig_1 || sig_3){
glColor3f(1,1,0);
}

else{
glColor3f(1,0,0);
}
signals();
glPopMatrix();
glPushMatrix();
glTranslatef(3.5,-2.8,0);
if(sig_2 || sig_3){
glColor3f(1,1,0);
}
else{
glColor3f(1,0,0);
}
signals();
glPopMatrix();
 
/*** Train Construction ****/
glPushMatrix();
if(x1<=5 && goUp){
if(y_1<=1.9){
y_1+=0.01;
glRotatef(-10,0,0,1);
}
glTranslatef(x1,y_1,-10);
}
else {
glTranslatef(x1,y_1,-10);
}
glColor3f(1,1,0);
train();
glPopMatrix();
//move second Train 

glPushMatrix();
if(x2>=-5 && goDown){
if(y_2>=-2.1){
y_2-=0.01;
glRotatef(-10,0,0,1);
}
glTranslatef(x2,y_2,-10);
}
else {
glTranslatef(x2,y_2,-10);
}
glRotatef(180,0,1,0);
train();
glPopMatrix();
 glFlush();
 glutSwapBuffers();
}
 
void p()
{
if(sig_1){ 
if(x2>=-11 && x2<=-4)
{
goUp=true;
}
x1-=0.01;
}else{
goUp=false; }
if(sig_2){

if(x1<=11 && x1>=4){
goDown=true;
}x2+=0.01;
}else {goDown=false;}
if(sig_3){
goUp=true;
goDown=true;
x1-=0.01;
x2+=0.01;
}
trainSimulation();
 }
void P(){
}

void doInit() 
{
 /* Background and foreground color */
 glClearColor(0.2,0.2,0.8,0.0);
 glColor3f(.0,1.0,1.0);
 glViewport(0,0,640,480);
/* Select the projection matrix and reset it then
 setup our view perspective */
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(30.0f,(GLfloat)640/(GLfloat)480,0.1f,200.0f); 
 /* Select the modelview matrix, which we alter with rotatef() */
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 glClearDepth(2.0f);
glEnable(GL_COLOR_MATERIAL);
 glEnable(GL_DEPTH_TEST);

 glDepthFunc(GL_LEQUAL);
}
void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glTranslatef(0.0f,0.0f,-13.0f);
stroke_output(-2.0, 1.7, "Welcome");
stroke_output(-2.0, 1.0, "p--> Start the Simulation");
stroke_output(-2.0, -1.1, "q--> quit");
GLfloat mat_ambient[]={0.0f,1.0f,2.0f,1.0f};
GLfloat mat_diffuse[]={0.0f,1.5f,.5f,1.0f};
GLfloat mat_specular[]={5.0f,1.0f,1.0f,1.0f};
GLfloat mat_shininess[]={50.0f};
glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
 
GLfloat lightIntensity[]={3.7f,0.7f,0.7f,1.0f}; 
GLfloat light_position[]={0.0f,3.0f,2.0f,0.0f};
glLightfv(GL_LIGHT0,GL_POSITION,light_position);
glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
glFlush();
glutSwapBuffers();
 }
void menu(int id)
{
switch(id)
{
case 1:glutIdleFunc(P);
break;

case 2: glutIdleFunc(p);
break;
break;
case 5:exit(0);
break;
}
glFlush();
glutSwapBuffers();
glutPostRedisplay();
}
void mykey(unsigned char key,int x,int y)
{
if(key=='p')
{
glutIdleFunc(p);
}
if(key=='x')
{

angX++;
glutIdleFunc(p);
}
if(key=='y')
{
angY++;
glutIdleFunc(p);
}
if(key=='z')
{
angZ++;
glutIdleFunc(p);
}
if(key=='X')
{
angX--;
glutIdleFunc(p);
}
if( key=='Y')
{
angY--;

glutIdleFunc(p);
}
if(key=='Z')
{
angZ--;
glutIdleFunc(p);
}
if(key=='1'){
sig_1=!sig_1;
}
if(key=='2')
{
sig_2=!sig_2;
}

if(key=='3')
{
sig_1=false;
sig_2=false;
sig_3=!sig_3;
}
if(key=='P')
{
glutIdleFunc(P);
}
if(key=='r'){
x1=11;
x2=-11;
y_1=0;
y_2=0;
 
angX=angY=angZ=0;
}
if(key=='q'||key=='Q')
{
exit(0);
}
}
int main(int argc, char *argv[]) 
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
 glutInitWindowSize(1000,480);
 glutInitWindowPosition(0,0);
 glutCreateWindow("Pyramid");

 glutDisplayFunc(display);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glShadeModel(GL_SMOOTH);
glEnable(GL_DEPTH_TEST);
glEnable(GL_NORMALIZE);
glutKeyboardFunc(mykey);
glutCreateMenu(menu);
 glutAddMenuEntry("Start 'p'",2);
glutAddMenuEntry("Reverse The Simulation 'P'",1);
glutAddMenuEntry("Quit 'q'",5);
glutAttachMenu(GLUT_RIGHT_BUTTON);
doInit();
 glutMainLoop();
return 0; 
}
