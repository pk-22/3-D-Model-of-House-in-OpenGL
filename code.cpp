#include<GL/glut.h>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;
double w=1280,h=720; //Window dimensions
double view[3]={2,2,12.9}; //Camera Position
double look[3]={2,2,2}; //Where the camera is pointed initially
int flag=-1;
//Declaration of entities
void steps(void); 
void window(void);
void sgate(void);
void gate(void);
//Global Variables
double angle=0,speed=5,maino=0,romo=0,tro=0,mgo=0,sgo=0;
GLboolean redFlag = true, switchOne = false, switchTwo=false, switchLamp=false, amb1=true, diff1=true, spec1=true, amb2=true, diff2=true, spec2=true, amb3=true, diff3=true, spec3=true;
double windowHeight=800, windowWidth=600;
double eyeX=7.0, eyeY=2.0, eyeZ=15.0, refX = 0, refY=0,refZ=0;
double theta = 180.0, y = 1.36, z = 7.97888;
//declarating quadric objects
GLUquadricObj *Cylinder;
GLUquadricObj *Disk;

struct tm *newtime;
time_t ltime;

GLfloat angle1;

//initialisation
void myinit(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1*w/h,1*w/h,1,200.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//defining new quadric object
    Cylinder = gluNewQuadric();
	//to set drawing style
    gluQuadricDrawStyle( Cylinder, GLU_FILL);
	//to set automatic normals
    gluQuadricNormals( Cylinder,GLU_SMOOTH);


    Disk = gluNewQuadric();
    gluQuadricDrawStyle( Disk, GLU_FILL);
    gluQuadricNormals( Disk, GLU_SMOOTH);
	GLfloat gam[]={0.2,.2,.2,1};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,gam);

}


static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};



static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


void drawCube()
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    glBegin(GL_QUADS);
    
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
    }
    glEnd();
}

static GLfloat v_trapezoid[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.5, 3.0, 0.5}, //4
    {0.5, 3.0, 2.5}, //5
    {2.5, 3.0, 2.5}, //6
    {2.5, 3.0, 0.5}  //7
};

static GLubyte TquadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};

void drawTrapezoid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_emission[] = {difX, difY, difZ, 0.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    
    if(switchLamp==true){
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    } else {
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_trapezoid[TquadIndices[i][0]][0], v_trapezoid[TquadIndices[i][0]][1], v_trapezoid[TquadIndices[i][0]][2],
        v_trapezoid[TquadIndices[i][1]][0], v_trapezoid[TquadIndices[i][1]][1], v_trapezoid[TquadIndices[i][1]][2],
        v_trapezoid[TquadIndices[i][2]][0], v_trapezoid[TquadIndices[i][2]][1], v_trapezoid[TquadIndices[i][2]][2]);
        
        glVertex3fv(&v_trapezoid[TquadIndices[i][0]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][1]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][2]][0]);
        glVertex3fv(&v_trapezoid[TquadIndices[i][3]][0]);
    }
    glEnd();
}


//Drawing pyramid *************************
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};

void drawpyramid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
                    v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
                    v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}

void polygon(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(6,0);
    glVertex2f(5.8,1);
    glVertex2f(5.2,2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3,3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2,1);
    //glVertex2f(0,0);
    
    glEnd();
}

void polygonLine(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_LINE_STRIP);
    //glVertex2f(0,0);
    glVertex2f(6,0);
    glVertex2f(5.8,1);
    glVertex2f(5.2,2);
    glVertex2f(5, 2.2);
    glVertex2f(4, 2.8);
    glVertex2f(3,3);
    glVertex2f(2, 2.8);
    glVertex2f(1, 2.2);
    glVertex2f(0.8, 2);
    glVertex2f(0.2,1);
    glVertex2f(0,0);
    
    glEnd();
}

void drawSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    
    glutSolidSphere (3.0, 20, 16);
}


//set material property
void matprop(GLfloat amb[],GLfloat dif[],GLfloat spec[],GLfloat shi[])
{
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,amb);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dif);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,spec);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shi);
}

//to create wall
void wall(double thickness)
{
	glPushMatrix();
	glTranslated(2,.5*thickness,2);
	glScaled(4.0,thickness,4.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

//to create compound wall
void wall2(double thickness)
{
	glPushMatrix();
	glTranslated(.8,.5*thickness*4,3.5);
	glScaled(1.6,thickness*4,7.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

//to create earth
void earth(void)
{
	GLfloat ambient[]={1,0,0,1};
	GLfloat specular[]={0,1,1,1};
	GLfloat diffuse[]={.5,.5,.5,1};
	GLfloat shininess[]={50};


	matprop(ambient,diffuse,specular,shininess);
	// GLfloat lightIntensity[]={.7,.7,.7,1};
	// GLfloat light_position[]={2,5,-3,0};
	// glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	// glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

	glPushMatrix();
	glTranslated(0,-.25,0);
	glScaled(10000,.5,1000000);
	glutSolidCube(1.0);
	glPopMatrix();
	glFlush();
}


void compound(void)
{

	GLfloat ambient[]={1,0,0,1};
	GLfloat specular[]={0,1,1,1};
	GLfloat diffuse[]={.7,1,.7,1};
	GLfloat shininess[]={50};


	matprop(ambient,diffuse,specular,shininess);
	// GLfloat lightIntensity[]={.7,.7,.7,1};
	// GLfloat light_position[]={2,6,1.5,0};
	// glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	// glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

	//left wall of compound
	glPushMatrix();
	glPushMatrix();
	glTranslated(-4,0,-1-.04);
	glRotated(90.0,0,0,1);
	wall2(0.08);
	glPopMatrix();
	//right wall of compound
	glPushMatrix();
	glTranslated(8,0,-1-.02);
	glRotated(90.0,0,0,1);
	wall2(0.08);

	glPopMatrix();
	//back wall of compound
	glPushMatrix();
	glTranslated(2,.8,-1);
	glRotated(-90,1,0,0);
	glScaled(12,.02*4,1.6);
	glutSolidCube(1.0);
	glPopMatrix();
	//front left wall of compound
	glPushMatrix();
	glTranslated(-3,.8,6-.08);
	glRotated(-90,1,0,0);
	glScaled(2,.02*4,1.6);
	glutSolidCube(1.0);
	glPopMatrix();
	//front middle wall of compound
	glPushMatrix();
	glTranslated(2.5,.8,6-.08);
	glRotated(-90,1,0,0);
	glScaled(6,.02*4,1.6);
	glutSolidCube(1.0);
	glPopMatrix();
	//front right wall of compound
	glPushMatrix();
	glTranslated(7,.8,6-.08);
	glRotated(-90,1,0,0);
	glScaled(2,.02*4,1.6);
	glutSolidCube(1.0);
	glPopMatrix();


	glPopMatrix();

	GLfloat ambient2[]={0,1,0,1};
	GLfloat specular2[]={1,1,1,1};
	GLfloat diffuse2[]={.2,.6,0.1,1};
	GLfloat shininess2[]={50};
	matprop(ambient2,diffuse2,specular2,shininess2);

	//floor
	glPushMatrix();
	glTranslated(-4,-0.05,-1);
	glScaled(3,3,1.7);
	wall(0.08);
	glPopMatrix();

	gate();
    sgate();

    glFlush();

}






void room()
{

	GLfloat	ambient1[]={1,0,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={0.5,0.5,0.5,1};
	GLfloat mat_shininess[]={50};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);

	glPushMatrix();
	glTranslated(.5,4,.5);
	//roof
	glPushMatrix();
	glTranslated(-.02*4,.7*3.9,-.02*4);
	glScaled(.6+.02,1.5,.5+.02+.1);
	wall(0.08);
	glPopMatrix();


	GLfloat ambient2[]={1,0,0,1};
	GLfloat specular2[]={1,1,1,1};
	GLfloat diffuse2[]={1,1,.7,1};
	GLfloat shininess1[]={50};


	matprop(ambient2,diffuse2,specular2,shininess1);


	//left wall
	glPushMatrix();
	glTranslated(0,0,-.02);
	glScaled(1,.7,.5);
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//right wall
	glPushMatrix();
	glTranslated(2.4,0,-.02);
	glScaled(1,.7,.5);
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//back wall
	glPushMatrix();
	glTranslated(-.08,0,0);
	glScaled(.62,.7,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//front wall
	glPushMatrix();
	glTranslated(-0.08,0,2);
	glScaled(.5,.7,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//wall above the room door
	glPushMatrix();
	glTranslated(1.9,.7*3,2);
	glScaled(.11,.7*.25,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();


	GLfloat	ambient[]={1,0.5,.5,1};
	GLfloat specular[]={1,1,1,1};
	GLfloat diffuse[]={1,0.5,0.5,1};

  	matprop(ambient,diffuse,specular,mat_shininess);
	//door
	glPushMatrix();
	glTranslated(2.3,0,(2-.05));
	glRotated(-tro,0,1,0);
	glTranslated(-2.3,0,-(2-.05));
	glPushMatrix();
	glTranslated(1.927,0,2);
	glScaled(.09,.525,1);
	glRotated(-90.0,1,0,0);
	wall(0.02);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.3,0,2-.05);
	glScaled(.6,.7,.8);
	glRotated(-90,1,0,0);
	gluCylinder(Cylinder, 0.05, 0.05, 3, 16, 16);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}
void tankwall(float thk)
{
	glTranslated(.5,.5*thk,.5);
	glScaled(1,thk,1);
	glutSolidCube(1);
}
void watertank(void)
{
	float thk=.04,hght=1,wdth=1,bdth=1;
	GLfloat	ambient1[]={.5,0,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={.5,.8,1,1};

	GLfloat mat_shininess[]={50};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	glPushMatrix();

	glTranslated(1.5,4+4*.7,1.5);
	glScaled(.8,.8,.8);
	//tank floor
	glPushMatrix();
	glScaled(wdth,1,bdth);
	tankwall(thk);
	glPopMatrix();
	//tank left wall
	glPushMatrix();

	glScaled(1,hght,bdth);
	glRotated(90.0,0,0,1);
	tankwall(thk);
	glPopMatrix();
	//tank right wall
	glPushMatrix();
	glTranslated(wdth,0,0);
	glScaled(1,hght,bdth);
	glRotated(90.0,0,0,1);
	tankwall(thk);
	glPopMatrix();
	//tank back wall
	glPushMatrix();
	glScaled(wdth,hght,1);
	glRotated(-90.0,1,0,0);
	tankwall(0.04);
	glPopMatrix();
	//tank front wall
	glPushMatrix();
	glTranslated(0,0,bdth);
	glScaled(wdth,hght,1);
	glRotated(-90.0,1,0,0);
	tankwall(0.04);
	glPopMatrix();
	//tank roof
	glPushMatrix();
	glTranslated(-thk,hght,0);
	glScaled(wdth*.8,1,bdth);
	tankwall(0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslated(wdth*.8-thk,hght,0);
	glScaled(wdth*.2+thk,1,bdth*.6);
	tankwall(0.04);
	glPopMatrix();
	glPopMatrix();

}

void terece(void)
{

	GLfloat	ambient1[]={1,0,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={0.5,0.5,0.5,1};
	GLfloat mat_shininess[]={50};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	glPushMatrix();
	glTranslated(0,4,0);
	glScaled(1,.1,1);

	//left wall
	glPushMatrix();
	glTranslated(0,0,-.02-.25);
	glScaled(1,1,.95);
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//right wall
	glPushMatrix();
	glTranslated(6+.12,0,-.02-.27);
	glScaled(1,1,1.1);
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//back wall
	glPushMatrix();
	glTranslated(-.08,0,-.21);
	glScaled(1.5+.05,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//front wall
	glPushMatrix();
	glTranslated(-.08,0,4+.11);
	glScaled(1.5+.05,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-.04,2,4);
	glScaled(.08,4,.1);
	glutSolidCube(1);
	glPopMatrix();

     glPopMatrix();
}




void fanwing(float winglen)
{
    glPushMatrix();

	glRotated(90,1,0,0);
	glRotated(90,0,1,0);
	glScaled(1,15,1);
	gluCylinder(Cylinder,.01,.01,1,4,1);
	glPopMatrix();
}
void fanbottom()
{
	glPushMatrix();

	glTranslated(1,3.2,1);
	glPushMatrix();
	glRotated(90,1,0,0);
	gluCylinder(Cylinder, .2, .2,.05, 128, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0.00025,0);
	glRotated(90,1,0,0);
	gluDisk(Disk,0,.2,32,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,-.05,0);
	glRotated(90,1,0,0);
	gluCylinder(Cylinder,.2,.15,.1,128,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,-.1,0);
	glRotated(90,1,0,0);
	gluDisk(Disk,0,.15,32,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.1,0.0,0);
	fanwing(.6);
	glPopMatrix();
	glPushMatrix();
	glRotated(120,0,1,0);
	glTranslated(.1,0,0);
	fanwing(.6);
	glPopMatrix();
	glPushMatrix();
	glRotated(240,0,1,0);
	glTranslated(0.1,0.0,0);
	fanwing(.6);
	glPopMatrix();
	glPopMatrix();
}
void fan(void)
{	glPushMatrix();
	glTranslated(2.5,1.9,0);
	glScaled(.5,.5,.5);
	GLfloat mat_ambient[]={.5,0,0,1};
	GLfloat mat_specular[]={0,1,1,0};
	GLfloat mat_diffuse[]={.8,1,.8,1};
	GLfloat mat_shininess[]={50};


	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);


if(flag==-1)
{
	glPushMatrix();
	fanbottom();
	glPopMatrix();
}
else

{

	angle+=speed;
	glPushMatrix();
	glTranslated(1,0,1);
	glRotated(angle,0,1,0);
	glTranslated(-1,0,-1);
	fanbottom();
	glPopMatrix();
}

	glPushMatrix();
	glTranslatef(1,3.3,1);
	glRotated(-90,1,0,0);
	gluCylinder(Cylinder, .1, 0.005, .25, 16, 16);
	glPopMatrix();
	glPushMatrix();

	glTranslatef(1,4,1);
	glRotated(90,1,0,0);
	gluCylinder(Cylinder, .006, 0.006, .6, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1,3.96,1);
	glRotated(90,1,0,0);
	gluCylinder(Cylinder, .1, 0.005, .25, 16, 16);
	glPopMatrix();
	glPopMatrix();
	if(flag==1)
		glutPostRedisplay();
}
void tableg(float llen,float lthk)
{
	glPushMatrix();
	glRotated(-90,1,0,0);
	gluCylinder(Cylinder,lthk,lthk,llen,32,32);
	glPopMatrix();
}
void table(float tabwid,float tablen,float tabthk,float llen,float lthk)
{
	glPushMatrix();
	glPushMatrix();
	glTranslated(0,llen,0);
	glScaled(tabwid,tabthk,tablen);
	glutSolidCube(1);
	glPopMatrix();
	float dist1=.95*tablen/2-lthk/2;
	float dist2=.95*tabwid/2-lthk/2;
	// front right leg
	glPushMatrix();
	glTranslated(dist2,0,dist1);
	tableg(llen,lthk);
	glPopMatrix();
	//back right leg
	glPushMatrix();
	glTranslated(dist2,0,-dist1);
	tableg(llen,lthk);
	glPopMatrix();
	//back left leg
	glPushMatrix();
	glTranslated(-dist2,0,-dist1);
	tableg(llen,lthk);
	glPopMatrix();
	//front left leg
	glPushMatrix();
	glTranslated(-dist2,0,dist1);
	tableg(llen,lthk);
	glPopMatrix();

	glPopMatrix();
}
void bed()
{
    //bed headboard
    glPushMatrix();
    glScalef(0.04, 0.5, 0.36);
    // glTranslatef(-2,-0.5,6.2);
    glTranslatef(100,-0.5,0.1);
    drawCube1(0.5,0.2,0.2,  0.25,0.1,0.1,100);
    glPopMatrix();
    
    //bed body
    glPushMatrix();
    glScalef(0.4, 0.2, 0.36); //1, 0.2, 0.9
    // glTranslatef(0,-0.5,6.2);
    glTranslatef(10,-0.5,0.1);
    drawCube1(0.824, 0.706, 0.549,   0.412,0.353,0.2745,100);
    glPopMatrix();
    
    //pillow right far
    //glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(4.3,0.5,0.15);
    glRotatef(22, 0,0,1);
    glScalef(0.04, 0.06, 0.112);
    drawCube1(0.627, 0.322, 0.176,  0.3135,0.161,0.088,100);
    glPopMatrix();
    
    //pillow left near
    //glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(4.3,0.5,0.65);
    glRotatef(22, 0,0,1);
    glScalef(0.04, 0.06, 0.112);
    drawCube1(0.627, 0.322, 0.176,  0.3135,0.161,0.088,100);
    glPopMatrix();
    
    //blanket
    //glColor3f(0.627, 0.322, 0.176);
    glPushMatrix();
    glTranslatef(4.5,0.5,0);
    //glRotatef(22, 0,0,1);
    glScalef(0.24, 0.02, 0.38);
    drawCube1(0.627, 0.322, 0.176,  0.3135,0.161,0.088,100);
    glPopMatrix();
    
    //blanket side left part
    //glColor3f(0.627, 0.322, 0.176);
    // glPushMatrix();
    // glTranslatef(1.4,-0.3,8.16);
    // //glRotatef(22, 0,0,1);
    // glScalef(0.5, 0.25, 0.05);
    // drawCube1(0.627, 0.322, 0.176,  0.3135,0.161,0.088);
    glPopMatrix();
}

void bedsideDrawer()
{
    //bedside drawer *************************************
      
      //side drawer
      glPushMatrix();
      glTranslatef(4.0,0.2,1.15); //0.5,-0.1,9
      glScalef(0.06, 0.2, 0.115);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
      
      //side drawer's drawer
      glPushMatrix();
      glTranslatef(4.15,0.3,1.2);
      glScalef(0.0005, 0.11, 0.09);
      drawCube1(0.3,0.2,0.2, 0.15,0.1,0.1);
      glPopMatrix();
      
      //side drawer's knob
      glPushMatrix();
      glTranslatef(4.2,0.45,1.3);
      glScalef(0.005, 0.01, 0.01);
      drawSphere(0.3, 0.1, 0.0,  0.15,0.05,0.0);
      glPopMatrix();
}
void mainDrawer()
{
    //bedside drawer *************************************
      
      //side drawer
       glPushMatrix();
      glTranslatef(0.03,-0.1,2.0); //0.5,-0.1,9
      glScalef(0.12, 0.3, 0.4);
      drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
      
}

void speaker1()
{
    //bedside drawer *************************************
      
      //side drawer
      glPushMatrix();
      glTranslatef(5.8,-0.1,2.3); //0.5,-0.1,9
      glScalef(0.02, 0.6, 0.02);
      drawCube1(0,0,0,  0.1,0.05,0.05);
      glPopMatrix();
      
}

void speaker2()
{
    //bedside drawer *************************************
      
      //side drawer
      glPushMatrix();
      glTranslatef(5.8,-0.1,3.8); //0.5,-0.1,9
      glScalef(0.02, 0.6, 0.02);
      drawCube1(0,0,0,  0.1,0.05,0.05);
      glPopMatrix();
      
}

void cupboard()
{
    //Cupboard/Almari ************************************************************
    glPushMatrix();
	glScalef(0.3, 1, 0.1);
	glTranslatef(14.3,0,-3.5);
        //cupboard
    glPushMatrix();
    glTranslatef(4,0,4.4);
    glScalef(0.5, 1, 0.5);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();
        
    //cupboard's 1st vertical stripline
    glPushMatrix();
    glTranslatef(4,1,5.9);
    glScalef(0.5, 0.01, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
        
    //cupboard's 2nd vertical stripline
    glPushMatrix();
    glTranslatef(4,0.5,5.9);
    glScalef(0.5, 0.01, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
        
    //cupboard's last stripline
    glPushMatrix();
    glTranslatef(4,0,5.9);
    glScalef(0.5, 0.01, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
        
    //cupboard's lst horizontal stripline
    glPushMatrix();
    glTranslatef(5.5,0,5.9);
    glScalef(0.01, 1, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
        
    //cupboard's right side horizontal stripline
    glPushMatrix();
    glTranslatef(4.75,1,5.9);
    glScalef(0.01, 0.67, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
    
    //cupboard's left side horizontal stripline
    glPushMatrix();
    glTranslatef(4,0,5.9);
    glScalef(0.01, 1, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
        
    //cupboard's handle right
    glPushMatrix();
    glTranslatef(5,1.4,5.9);
    glScalef(0.02, 0.18, 0.01);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
    
    //cupboard's handle right sphere
    glPushMatrix();
    glTranslatef(5.02,1.9,5.91);
    glScalef(0.02, 0.02, 0.01);
    drawSphere(0.2,0.1,0.1,  0.1, 0.05, 0.05,  10);
    glPopMatrix();
    
    //cupboard's handle left
    glPushMatrix();
    glTranslatef(4.5,1.4,5.9);
    glScalef(0.02, 0.18, 0.01);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
    
    //cupboard's handle left sphere
    glPushMatrix();
    glTranslatef(4.52,1.9,5.91);
    glScalef(0.02, 0.02, 0.01);
    drawSphere(0.2,0.1,0.1,  0.1, 0.05, 0.05,  10);
    glPopMatrix();
        
    //cupboard's drawer's 1st handle
    glPushMatrix();
    glTranslatef(4.5,0.7,5.9);
    glScalef(0.16, 0.02, 0.01);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();
        
    //cupboard's drawer's 2nd handle
    glPushMatrix();
    glTranslatef(4.5,0.25,5.9);
    glScalef(0.16, 0.02, 0.01);
    drawCube1(0.2,0.1,0.1,  0.1, 0.05, 0.05);
    glPopMatrix();

	glPopMatrix();
}

void television()
{
    //TV *****************************************
    glPushMatrix();
	glScalef(1,0.7,0.5);
	glTranslatef(6.85,0.6,0.4);
       //poster black
       glColor3f(0.0,0.0,0.0);
       glPushMatrix();
       glTranslatef(-1,1.4,4.6);
       glScalef(0.0001, .65, .8);
       drawCube1(0,0,0, 0,0,0, 10);
       glPopMatrix();
       
       //TV stand
       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,2.1,5.5);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, .02, .25);
    drawCube1(1.0,1.0,1.0,  1.0,1.0,1.0, 10);
       glPopMatrix();
       
       //TV stand
       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,2.1,6.2);
       glRotatef(-14, 1,0,0);
       glScalef(0.0001, .28, .02);
    drawCube1(1.0,1.0,1.0,  1.0,1.0,1.0, 10);
       glPopMatrix();
       
       //TV stand
       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,1.8,6);
       glRotatef(-14, 1,0,0);
       glScalef(0.0001, .29, .02);
    drawCube1(1.0,1.0,1.0,  1.0,1.0,1.0, 10);
       glPopMatrix();
       
       //TV stand
       glColor3f(1.0,1.0,1.0);
       glPushMatrix();
       glTranslatef(-0.9,2.1,5.5);
       glRotatef(23, 1,0,0);
       glScalef(0.0001, .25, .02);
       drawCube1(1.0,1.0,1.0,  1.0,1.0,1.0, 10);
       glPopMatrix();
	glPopMatrix();
}


void lamp1()
{
    //lamp base
    // glPushMatrix();
    // glTranslatef(0.0,0.6,3.25);
    // glScalef(0.07, 0.02, 0.07);
    // drawCube1(0,0,1,  0,0,0.5);
    // glPopMatrix();
    
    //lamp stand
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0.1,0.7,2.95);
    glScalef(0.01, 0.1, 0.01);
    drawCube1(1,0,0,  0.5,0.0,0.0);
    glPopMatrix();
        
    //lamp shade
    glColor3f(0.000, 0.000, 0.545);
    glPushMatrix();
    glTranslatef(0.0,1.0,2.82);
    glScalef(0.08, 0.09, 0.08);
    drawTrapezoid(0.000, 0.000, 0.545,  0,0,0.2725);
    //drawCube1(0.000, 0.000, 0.545,  0,0,0.2725);
    glPopMatrix();
}

// GLboolean amb3 = false, spec3 = false, diff3 = false, switchLamp = false;

void lampLight()
{
    //glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 3.5,1.7,-6.8, 1.0 };  //0.7, 4.5, 9.0
    
    //glEnable( GL_LIGHT2);
    
    if(amb3 == true){glLightfv( GL_LIGHT4, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT4, GL_AMBIENT, no_light);}
    
    if(diff3 == true){glLightfv( GL_LIGHT4, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT4, GL_DIFFUSE, no_light);}
    
    if(spec3 == true){glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT4, GL_SPECULAR, no_light);}

    glLightfv( GL_LIGHT4, GL_POSITION, light_position);
    GLfloat spot_direction[] = { 0, -1, 0 };
    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT4, GL_SPOT_CUTOFF, 35.0);
    glLightf(GL_LIGHT4,GL_SPOT_EXPONENT,1.5);
    //glPopMatrix();
}

void lightBulb1()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1.000, 1,1, 0.0};
    
    glPushMatrix();
    glTranslatef (3, 4, 3);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    if(switchOne == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void lightBulb2()
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};
    
    glPushMatrix();
    glTranslatef (5.1, 4, 1);
    glScalef(0.2, 0.2, 0.2);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    if(switchTwo == true){
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }else{
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    }
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();
}

void lamp()
{
	glPushMatrix();
	glTranslatef(3.5,0.7,-6.8);
	glScalef(0.9,0.35,0.9);
    //lamp base
    glPushMatrix();
    glTranslatef(.6,0.5,8.95);
    glScalef(0.07, 0.02, 0.07);
    drawCube1(0,0,1,  0,0,0.5);
    glPopMatrix();
    
    //lamp stand
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(.7,0.35,9.05);
    glScalef(0.01, 0.2, 0.01);
    drawCube1(1,0,0,  0.5,0.0,0.0);
    glPopMatrix();
        
    //lamp shade
    glColor3f(0.000, 0.000, 0.545);
    glPushMatrix();
    glTranslatef(.6,0.9,8.9);
    glScalef(0.08, 0.09, 0.08);
    drawTrapezoid(0.000, 0.000, 0.545,  0,0,0.2725);
    //drawCube1(0.000, 0.000, 0.545,  0,0,0.2725);
    glPopMatrix();

	glPopMatrix();
}

void lightOne()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 3, 2, 3, 1.0 }; //5 5 10
    
    //glEnable( GL_LIGHT0);
    
    if(amb1 == true){glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);}
    
    if(diff1 == true){glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);}
    
    if(spec1 == true){glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);}
   
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}

void lightTwo()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 0.9, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 5.1, 4, 1, 1.0 };
    
    //glEnable( GL_LIGHT5);
    
    if(amb2 == true){glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);}
    else{glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);}
    
    if(diff2 == true){glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);}
    else{glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);}
    
    if(spec2 == true){glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);}
    else{glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);}
    
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    glPopMatrix();
}

void sofa()
{

	glPushMatrix();
	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 1.000, 0.843, 0.000, 1.0 };
    GLfloat high_shininess[] = { 100.0 };
    GLfloat mat_emission[] = {1,1,1, 1.0};

	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    //sofa headboard
    glPushMatrix();
    glScalef(0.07, 0.5, 0.3);
    glTranslatef(60,-0.5,8.2);
	
    drawCube1(0.5,0.2,0.2,  0.25,0.1,0.1);
    glPopMatrix();
    //sofa side
    glPushMatrix();
    glScalef(0.11, 0.5, 0.04);
    glTranslatef(40,-0.5,60);
    drawCube1(0.5,0.2,0.2,  0.25,0.1,0.1);
    glPopMatrix();
	//sofa side
	glPushMatrix();
    glScalef(0.11, 0.5, 0.04);
    glTranslatef(40,-0.5,82.5);
    drawCube1(0.5,0.2,0.2,  0.25,0.1,0.1);
    glPopMatrix();
    
    //sofa body
    glPushMatrix();
    glScalef(0.11, 0.3, 0.3); //1, 0.2, 0.9
    glTranslatef(40,-0.5,8.2);
    drawCube1(0.824, 0.706, 0.549,   0.412,0.353,0.2745);
    glPopMatrix();
	glPopMatrix();
    
}

void s_table()
{
    //sofa body
    glPushMatrix();
	
    glScalef(0.1, 0.25, 0.1); //1, 0.2, 0.9
    glTranslatef(50,-0.5,28);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
    glPopMatrix();

}

void carpet(){
	glPushMatrix();
    //glScalef(5, 0.1, 7);
    glTranslatef(4.0,0.2,2.15);
    glScalef(0.5, 0.01, 0.5);
    drawCube1(0.4, 0.1, 0.0,  0.20, 0.05, 0.0);
    glPopMatrix();
}

void wallshelf()
{

	glPushMatrix();
	glScalef(0.6,1,0.5);
	glTranslatef(-0.5,0.8,-3);
    //Wall Shelf **********************************************
      
      //wall shelf one
      glPushMatrix();
      glTranslatef(1.5,2.7,3);
      glScalef(0.4, 0.03, 0.2);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
      
      //wall shelf two
      glPushMatrix();
      glTranslatef(1,2.3,3);
      glScalef(0.4, 0.03, 0.2);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
      
      //wall shelf three
      glPushMatrix();
      glTranslatef(0.5,1.9,3);
      glScalef(0.4, 0.03, 0.2);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
      
      //wall shelf four
    glPushMatrix();
      glTranslatef(1,1.5,3);
      glScalef(0.4, 0.03, 0.2);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
      glPopMatrix();
      
      //wall shelf five
      glPushMatrix();
      glTranslatef(1.5,1.1,3);
      glScalef(0.4, 0.03, 0.2);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();
      
      //showpiece on the bottom shelf from left 1
      glPushMatrix();
      glTranslatef(1.5,1.2,3);
      glScalef(0.04, 0.06, 0.2);
      drawCube1(0.698,0.133,0.133,  0.349,0.0665,0.0665);
      glPopMatrix();
      
      //showpiece on the bottom shelf from left 2
      glPushMatrix();
      glTranslatef(2,1.2,3);
      glScalef(0.04, 0.06, 0.2);
      drawCube1(0.729,0.333,0.827,  0.3645,0.1665,0.4135);
      glPopMatrix();
      
      //showpiece on the bottom shelf from left 3 lower portion
      glPushMatrix();
      glTranslatef(2.5,1.2,3);
      glScalef(0.04, 0.06, 0.2);
      drawCube1(0.098,0.098,0.439,  0.049,0.049,0.2195);
      glPopMatrix();
      
      //showpiece on the bottom shelf from left 3 upper portion
      glPushMatrix();
      glTranslatef(2.51,1.35,3);
      glScalef(0.01, 0.05, 0.2);
      drawCube1(0.529,0.808,0.980,  0.2645,0.404,0.490);
      glPopMatrix();
      
      //showpiece on the top shelf  left 2
      glColor3f(0.502, 0.502, 0.000);
      glPushMatrix();
      glTranslatef(2.5,2.71,3);
      //glRotatef(22, 0,0,1);
      glScalef(0.05, 0.16, 0.01);
      drawCube1(0.502,0.502,0.000,  0.251,0.251,0);
      glPopMatrix();
      
      //showpiece on the top shelf left 1
      glPushMatrix();
      glTranslatef(1.8,2.71,3);
      glScalef(0.16, 0.1, 0.01);
      drawCube1(0,0,0.9,  0,0,0.45);
      glPopMatrix();
      
      //showpiece on 2nd shelf
      glColor3f(.416, 0.353, 0.804);
      glPushMatrix();
      glTranslatef(1.3,2.4,3);
      glScalef(0.16, 0.08, 0.01);
      drawCube1(.416,0.353,0.804,  0.208,0.1765,0.402);
      glPopMatrix();
      
      //showpiece on 3rd shelf left 1
      glPushMatrix();
      glTranslatef(0.4,1.9,3);
      glScalef(0.05, 0.16, 0.01);
      drawCube1(0.863,0.078,0.235,  0.4315,0.039,0.1175);
      glPopMatrix();
      
      //showpiece on 3rd shelf left 2
      glPushMatrix();
      glTranslatef(0.7,1.9,3);
      glScalef(0.05, 0.12, 0.01);
      drawCube1(0.780,0.082,0.522,  0.39,0.041,0.261);
      glPopMatrix();
      
      //showpiece on 3rd shelf left 3
      glColor3f(0.600, 0.196, 0.800);
      glPushMatrix();
      glTranslatef(1,1.9,3);
      glScalef(0.05, 0.09, 0.01);
      drawCube1(0.6,0.196,0.8,  0.3,0.098,0.4);
      glPopMatrix();
      
      //showpiece on 4th shelf
      glPushMatrix();
      glTranslatef(1.8,1.5,3);
      glScalef(0.2, 0.1, 0.2);
      drawpyramid(0.282,0.239,0.545,  0.141,0.1195,0.2725, 50);
      glPopMatrix();
      
      //showpiece on 4th shelf
      glPushMatrix();
      glTranslatef(1.4,1.5,3);
      glScalef(0.15, 0.1, 0.2);
      drawpyramid(0.251,0.878,0.816,  0.1255,0.439,0.408, 50);
      glPopMatrix();

	glPopMatrix();

}



void cleg(float cllen,float clwid)
{
	glRotated(90,1,0,0);
	gluCylinder(Cylinder,clwid,clwid,cllen,32,32);

}
void chair(float cblen,float cbwid,float cbthk,float cllen,float clwid)
{
	GLfloat	ambient1[]={.5,1,.5,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={0.5,0.5,0.5,1};
	GLfloat mat_shininess[]={50};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	glPushMatrix();
	glTranslated(0,cllen,0);
	//chair base
	glPushMatrix();
	glScaled(cblen,cbthk,cbwid);
	glutSolidCube(1);
	glPopMatrix();
	float dist=cblen/2-clwid/2;
	//chair legs
	glPushMatrix();
	glTranslated(dist,0,dist);
	cleg(cllen,clwid);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-dist,0,dist);
	cleg(cllen,clwid);
	glPopMatrix();
	glPushMatrix();
	glTranslated(-dist,0,-dist);
	cleg(cllen,clwid);
	glPopMatrix();
	glPushMatrix();
	glTranslated(dist,0,-dist);
	cleg(cllen,clwid);
	glPopMatrix();
	//base pipes
	glPushMatrix();
	glTranslated(-.085,-clwid/2,cbwid/3);
    glRotated(90,0,1,0);
	gluCylinder(Cylinder,-clwid,clwid,cblen,32,32);
   	glPopMatrix();
	glPushMatrix();
	glTranslated(-.085,clwid/2,-cbwid/3);
    glRotated(90,0,1,0);
	gluCylinder(Cylinder,clwid,clwid,cblen,32,32);
   	glPopMatrix();
	//back support pipes
	glPushMatrix();
	glTranslated(-.085,-clwid/2,cbwid/3);
    glRotated(-90,1,0,0);
	gluCylinder(Cylinder,clwid,clwid,cllen,32,32);
   	glPopMatrix();
	glPushMatrix();
	glTranslated(-.085,-clwid/2,-cbwid/3);
    glRotated(-90,1,0,0);
	gluCylinder(Cylinder,clwid,clwid,cllen,32,32);
   	glPopMatrix();
	//back support
	glPushMatrix();
	glTranslated(-cblen/2,cllen/2+cblen/2,0);
	glRotated(90,0,0,1);
	glScaled(cblen,.01,cbwid);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
}


void study_table()
{
	glPushMatrix();
	glTranslatef(-3.85,0,-3.2);
	glScalef(0.7,1.2,0.7);
    //Study table ************************************************
        
        //study table left body
        glPushMatrix();
        glTranslatef(5.9,0,4.6);
        glScalef(0.2, 0.2, 0.2);
        drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
        glPopMatrix();
        
        //study table right body
        glPushMatrix();
        glTranslatef(7,0,4.6);
        glScalef(0.2, 0.2, 0.2);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
        glPopMatrix();
        
   
        
        //study table upper body
        glPushMatrix();
        glTranslatef(5.9,0.6,4.6);
        glScalef(0.57, 0.1, 0.2);
    drawCube1(0.545, 0.271, 0.075,  0.2725,0.1355,0.0375);
        glPopMatrix();
        
        //study table upper body bottom stripe
        glPushMatrix();
        glTranslatef(5.9,0.6,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.57, 0.01, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();
        
        //study table upper body upper stripe
        glPushMatrix();
        glTranslatef(5.9,0.9,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.57, 0.01, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();
        
        //study table upper body handle
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(6.5,0.75,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.16, 0.02, 0.0001);
        drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();
        
        //study table left body handle
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(6.4,0.1,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.02, 0.13, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();
        
        //study table right body handle
        glColor3f(0.2,0.1,0.1);
        glPushMatrix();
        glTranslatef(7.1,0.1,5.2);
        //glRotatef(22, 0,0,1);
        glScalef(0.02, 0.13, 0.0001);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
        glPopMatrix();
	glPopMatrix();
}

void study_chair(){

	glPushMatrix();
	glTranslatef(0,0,-0.03);
    glPushMatrix();
    glScalef(0.1, 0.05, 0.1);
    glTranslatef(8,11,6.0);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

	glPushMatrix();
    glScalef(0.1, 0.45, 0.01);
    glTranslatef(8,0,90);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

	glPushMatrix();
    glScalef(0.1, 0.22, 0.01);
    glTranslatef(8,0,60);
    drawCube1(0.2,0.1,0.1,  0.1,0.05,0.05);
    glPopMatrix();

	glPopMatrix();
}


void diningtable()
{


	glPushMatrix();
	glTranslated(3,0,1);
	glScaled(1.5,1.5,1.5);
	table(.3,.5,.025,.4,.005);
	//front left chair
	glPushMatrix();
	glTranslated(-.1,0,.1);
	chair(.15,.15,.02,.3,.005);
	glPopMatrix();
	//back left chair
	glPushMatrix();
	glTranslated(-.1,0,-.1);
	chair(.15,.15,.02,.3,.005);
	glPopMatrix();
	//front right chair
	glPushMatrix();
	glTranslated(.1,0,.1);
	glRotated(180,0,1,0);
	chair(.15,.15,.02,.3,.005);
	glPopMatrix();
	//back right chair
	glPushMatrix();
	glTranslated(.1,0,-.1);
	glRotated(180,0,1,0);
	chair(.15,.15,.02,.3,.005);
	glPopMatrix();
	//back chair
	glPushMatrix();
	glTranslated(0,0,-.27);
	glRotated(-90,0,1,0);
	chair(.15,.15,.02,.3,.005);
	glPopMatrix();
	//front chair
	glPushMatrix();
	glTranslated(0,0,.27);
	glRotated(90,0,1,0);
	chair(.15,.15,.02,.3,.005);
	glPopMatrix();


	glPopMatrix();

}



void steps(void)
{
    int i;
	GLfloat	ambient1[]={1,0,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={0.5,0.5,0.5,1};
	GLfloat mat_shininess[]={50};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	glPushMatrix();
	glTranslated(-.25,.1,.2);
	for(i=0;i<19;i++)
	{	glPushMatrix();
		glTranslated(0,i*.2,i*.2);
		glScaled(.4,.2,.3);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glRotated(-45,1,0,0);
	glTranslated(-.45,.3,2.7);
	glScaled(.04,1,5.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.45,4,3.6);
	glScaled(.04,.8,.75);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-.25,4,3.96);
	glScaled(.4,.8,.04);
	glutSolidCube(1);
	glPopMatrix();
}

void sleg(float len,float thk)
{
	glScaled(thk,len,thk);
	glutSolidCube(1);

}
void solar(void)
{
	GLfloat	ambient1[]={.1,.1,.1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={1,1,1,1};
	GLfloat mat_shininess[]={50};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	GLfloat lightIntensity[]={.7,.7,.7,1};
	GLfloat light_position[]={-20,4,60,0};
	glLightfv(GL_LIGHT2,GL_POSITION,light_position);
	glLightfv(GL_LIGHT2,GL_DIFFUSE,lightIntensity);
	glEnable(GL_LIGHT2);
	//base
	glPushMatrix();
	glTranslated(4,4,3);
	glPushMatrix();
	glTranslated(0.4,.4,0);
	glScaled(1,.8,1);
	glutSolidCube(1);
	glPopMatrix();
	GLfloat	ambient2[]={.7,.7,.7,1};
	GLfloat specular2[]={1,1,1,1};
	GLfloat diffuse2[]={1,1,1,1};

  	matprop(ambient2,diffuse2,specular2,mat_shininess);

	glPushMatrix();
	glTranslated(0,.8,0);
	glPushMatrix();
	glTranslated(.6,.6,0);
	gluCylinder(Cylinder,.1,.1,.4,32,32);
	glPopMatrix();
	GLfloat	ambient3[]={1,0,.2,1};
	GLfloat specular3[]={1,1,1,1};
	GLfloat diffuse3[]={1,0,.5,1};
	GLfloat mat_shininess3[]={50};

  	matprop(ambient3,diffuse3,specular3,mat_shininess3);
	glPushMatrix();
	glTranslated(.6,.6,0);
	gluDisk(Disk,0,.1,32,32);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.6,.6,0.4);
	gluDisk(Disk,0,.1,32,32);
	glPopMatrix();

	GLfloat	ambient4[]={0,0,0,1};
	GLfloat specular4[]={1,1,1,1};
	GLfloat diffuse4[]={0,0,0,1};
	GLfloat mat_shininess4[]={50};

  	matprop(ambient4,diffuse4,specular4,mat_shininess4);
	glPushMatrix();
	glTranslated(.5,.3,.05);
	sleg(.6,.01);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.7,.3,.05);
	sleg(.6,.01);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.5,.3,.35);
	sleg(.6,.01);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.7,.3,.35);
	sleg(.6,.01);
	glPopMatrix();

	glPushMatrix();
	glRotated(45,0,0,1);
	glTranslated(.3,.015,.2);
	glScaled(.6,.03,.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.4,.21,0);
	sleg(.425,.01);
	glPopMatrix();

	glPushMatrix();
	glTranslated(.4,.21,.4);
	sleg(.425,.01);
	glPopMatrix();
	glPushMatrix();

	glTranslated(.4,.4,0);
	glRotated(30,0,0,1);
	glRotated(90,0,1,0);
	gluCylinder(Cylinder,.01,.01,.2,32,32);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
}

void myclock()
{


	GLfloat mat_ambient[]={.4,.8,.4,1};
	GLfloat mat_specular[]={1,1,1,1};
	GLfloat mat_diffuse[]={0.4,.8,.4,1};
	GLfloat mat_shininess[]={50};
	matprop(mat_ambient,mat_diffuse,mat_specular,mat_shininess);


	int hour_ticks , sec_ticks;
	glPushMatrix();
	glTranslated(2,3.2,-.02);
	glScaled(.03,.06,.03);



	glPushMatrix(); // Draw clock face
	glTranslatef( 0, 0, 1.0);
	gluDisk(Disk, 0, 7, 32, 16);

	glPopMatrix();
	GLfloat mat_ambien[]={1,0,0,1};
	matprop(mat_ambien,mat_diffuse,mat_specular,mat_shininess);

	glPushMatrix();
	glTranslatef( 0, 0, 1.95);
	gluDisk(Disk, 0, .8, 32, 16);

	glPopMatrix();

	GLfloat	ambient[]={0,0,0,1};
	GLfloat specular[]={1,1,1,1};
	GLfloat diffuse[]={0,0,0,1};
  	matprop(ambient,diffuse,specular,mat_shininess);
	// Draw hour hand
	glPushMatrix();
	glColor3f(1.0, 0.5, 0.5);
	glTranslatef( 0, 0, 1.5);
	glRotatef( -(360/12) * (newtime->tm_hour+newtime->tm_min/60.0), 0.0, 0.0, 1.0);

	glRotatef( -90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.45, 0, 4, 16, 16);
	glPopMatrix();
	GLfloat	ambient1[]={0,0,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={0,0,1,1};
  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	// Draw minute hand
	glPushMatrix();
	glColor3f(1.0, 0.5, 1.0);
	glTranslatef( 0, 0, 1.25);
	glRotatef( -(360/60) * newtime->tm_min, 0.0, 0.0, 1.0);

	glRotatef(-90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.4, 0, 6, 16, 16);
	glPopMatrix();

	GLfloat	ambient2[]={1,0,0,1};
	GLfloat specular2[]={1,1,1,1};
	GLfloat diffuse2[]={1,0,0,1};
  	matprop(ambient2,diffuse2,specular2,mat_shininess);
	// Draw second hand
	glPushMatrix();
	glTranslatef( 0, 0, 1);
	glRotatef(-(360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
	glRotatef( -90, 1.0, 0.0, 0.0);
	gluCylinder(Cylinder, 0.3, 0, 6, 16, 16);
	glPopMatrix();



	GLfloat	ambient3[]={1,1,1,1};
	GLfloat specular3[]={1,1,1,1};
	GLfloat diffuse3[]={1,0,1,1};
  	matprop(ambient3,diffuse3,specular3,mat_shininess);

	for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
	  {
		glPushMatrix();// Draw next arm axis.
        glTranslatef(0.0, 0.0, 1);
		glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);
		glTranslatef( 6.0, 0.0, 0.0);
		glutSolidCube(.8);
		glPopMatrix();
	}

	for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
	 {
   	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.1);
	glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
	glTranslatef(6.0, 0.0, 0.0);
	glutSolidCube(0.25);
	glPopMatrix();
	}


  glPopMatrix();

}
void window(void)
{
	int i;
	GLfloat lightIntensity[]={.7,.7,.7,1};
	GLfloat light_position[]={-20,4,-60,0};
	glLightfv(GL_LIGHT1,GL_POSITION,light_position);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,lightIntensity);

	glEnable(GL_LIGHT1);

	glPushMatrix();
	glTranslated(3.185,1,3.95);
	//left edge of window
	glPushMatrix();
	glTranslated(.02,1,.02);
	glScaled(.04,2.2,.04);
	glutSolidCube(1);
	glPopMatrix();
	//right edge
	glPushMatrix();
	glTranslated(1.6+.02,1,0.02);
	glScaled(.04,2.2,.04);
	glutSolidCube(1);
	glPopMatrix();
	//top edge
	glPushMatrix();
	glTranslated(.9,2+.02,0.02);
	glScaled(1.8,.04,.04);
	glutSolidCube(1);
	glPopMatrix();
	//bottom edge
	glPushMatrix();
	glTranslated(.8,.02,0.02);
	glScaled(1.8,.04,.04);
	glutSolidCube(1);
	glPopMatrix();

	for(i=1;i<=3;i++)
	{

	glPushMatrix();
	glTranslated(.4*i,0,0);

	glRotated(-90,1,0,0);
	gluCylinder(Cylinder,.01,.01,2,32,32);
	glPopMatrix();
	}

	for(i=1;i<=3;i++)
	{
	glPushMatrix();
	glTranslated(.1+.4*i,0,0);

	glRotated(-90,1,0,0);
	gluCylinder(Cylinder,.01,.01,2,32,32);
	glPopMatrix();
	}

	for(i=1;i<=4;i++)
	{
	glPushMatrix();
	glTranslated(0,.4*i,0);

	glRotated(90,0,1,0);
	gluCylinder(Cylinder,.03,.03,1.6,32,32);
	glPopMatrix();
	}

	glPopMatrix();


}
void gate(void)
{
	int i;
	GLfloat	ambient1[]={1,.5,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={.5,.5,.5,1};
	GLfloat mat_shininess[]={120};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	glPushMatrix();
	//if flag mgo=1 the open the main gate
	if(mgo==1)
		glTranslated(1.5,0,0);
	glTranslated(-1.3,0,6);
	//top frame of the main gate
	glPushMatrix();
	glTranslated(0,1.5,0);
	glScaled(1.7,.04,.04);
	glutSolidCube(1);
	glPopMatrix();
	//bottom frame of main gate
	glPushMatrix();
	glTranslated(0,.05,0);
	glScaled(1.7,.04,.04);
	glutSolidCube(1);
	glPopMatrix();
	//left frame of the main gate
	glPushMatrix();
	glTranslated(-.8,.75,0);
	glScaled(.04,1.5,.04);
	glutSolidCube(1);
	glPopMatrix();
	//right frame of the main gate
	glPushMatrix();
	glTranslated(.8,.75,0);
	glScaled(.04,1.5,.04);
	glutSolidCube(1);
	glPopMatrix();
	//horizantal pipes of the main gate
	for(i=1;i<=3;i++)
	{
	glPushMatrix();
	glTranslated(-.85,.4*i,0);
	glRotated(90,0,1,0);
	gluCylinder(Cylinder,.02,.02,1.7,32,32);
	glPopMatrix();
	}
	//vertical strips of the main gate
	for(i=1;i<=5;i++)
	{
	glPushMatrix();
	glTranslated(-.9+.3*i,.75,0);
	glScaled(.2,1.5,.02);
	glutSolidCube(1);
	glPopMatrix();
	}

	glPopMatrix();

}
 void sgate(void )
 {
	 int i;
	GLfloat ambient1[]={1,.5,1,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={.5,.5,.5,1};
	GLfloat mat_shininess[]={120};

  	matprop(ambient1,diffuse1,specular1,mat_shininess);
	glPushMatrix();
	//to open the sub gate
	glTranslated(5.75-.25,.05,6);
	glRotated(sgo,0,1,0);
	glTranslated(-5.75+.25,-.05,-6);
	//to translate sub gate to required position
	glTranslated(5.75,.05,6);
	//top edge of the sub gate
	glPushMatrix();
	glTranslated(0,1.5,0);
	glScaled(.5,.08,.08);
	glutSolidCube(1);
	glPopMatrix();
	//bottom edge of the sub gate
	glPushMatrix();
	glTranslated(0,.05,0);
	glScaled(.5,.08,.08);
	glutSolidCube(1);
	glPopMatrix();
	//left edge of the sub gate
	glPushMatrix();
	glTranslated(-.25,.85,0);
	glScaled(.04,1.7,.04);
	glutSolidCube(1);
	glPopMatrix();
	//right edge of the sub gate
	glPushMatrix();
	glTranslated(.25,.8,0);
	glScaled(.04,1.6,.04);
	glutSolidCube(1);
	glPopMatrix();
	//vertical pipes of the sub gate
	for(i=1;i<=4;i++)
	{
	glPushMatrix();
	glTranslated(-.25+.1*i,0,0);
	glRotated(-90,1,0,0);
	gluCylinder(Cylinder,.01,.01,1.5,32,32);
	glPopMatrix();
	}
	//horizantal pipes of the sub gate
	for( i=1;i<=4;i++)
	{
	glPushMatrix();
	glTranslated(-.25,.05+.3*i,0);
	glRotated(90,0,1,0);
	gluCylinder(Cylinder,.02,.02,.5,32,32);
	glPopMatrix();
	}
	glPopMatrix();
}
void text_rdr()
{
    // glBegin(GL_LINE_STRIP);
    // for (int i = 0; i < edge + 1; i++)
    // {
    //     glVertex2d(X_coordinate[i % edge], Y_coordinate[i % edge]);
    // }
    // glEnd();
    glColor3f(1, 1, 1);
    string str1 = "Use w to translate up by a factor of 10";
    string str2 = "Use s to translate down by a factor of 10";
    string str3 = "Use a to translate left by a factor of 10";
    string str4 = "Use d to translate right by a factor of 10";
    string str5 = "Use +, - to scale by a factor of 0.1";
    string str6 = "To rotate move mouse horizontally(hold left-click)";
    glRasterPos2f(-100, 720);
    for (int i = 0; i < str1.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str1[i]);
    }
    glRasterPos2f(-100, 690);
    for (int i = 0; i < str2.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str2[i]);
    }
    glRasterPos2f(-100, 660);
    for (int i = 0; i < str3.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str3[i]);
    }
    glRasterPos2f(-100, 630);
    for (int i = 0; i < str4.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str4[i]);
    }
    glRasterPos2f(-100, 600);
    for (int i = 0; i < str5.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str5[i]);
    }
    glRasterPos2f(-100, 570);
    for (int i = 0; i < str6.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str6[i]);
    }
    glFlush();
}
 void house(void)
{
	GLfloat mat_ambient[]={1,0,0,1};
	GLfloat mat_specular[]={1,1,1,1};
	GLfloat mat_diffuse[]={1,1,.7,1};
	GLfloat mat_shininess[]={50};

	matprop(mat_ambient,mat_diffuse,mat_specular,mat_shininess);


	GLfloat lightIntensity4[]={.7,.7,.7,.7};
	GLfloat light_position4[]={3,1,.5,1};
	glLightfv(GL_LIGHT6,GL_POSITION,light_position4);
	glLightfv(GL_LIGHT6,GL_DIFFUSE,lightIntensity4);
	glEnable(GL_LIGHT6);


	glPushMatrix();
	glTranslated(0,.15,0);
	//roof
    glPushMatrix();
	glTranslated(-.02*4,3.9,-.01*4-.25);
	glScaled(1.5+.05,1.5,1.1);
	wall(0.08);
	glPopMatrix();


	GLfloat ambient2[]={1,0,0,1};
	GLfloat specular2[]={1,1,1,1};
	GLfloat diffuse2[]={.7,1,0.8,1};
	GLfloat shininess[]={50};
		matprop(ambient2,diffuse2,specular2,shininess);

	//floor
	glPushMatrix();
	glTranslated(-.02*3,-0.05,-.01*4);
	glScaled(1.5+.01,1.5,1);
	wall(0.08);
	glPopMatrix();


	GLfloat ambient1[]={1,0,0,1};
	GLfloat specular1[]={1,1,1,1};
	GLfloat diffuse1[]={1,1,.7,1};
	GLfloat shininess1[]={50};
	matprop(ambient1,diffuse1,specular1,shininess1);

	//left wall
	glPushMatrix();
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//right wall
	glPushMatrix();
	glTranslated(6,0,0);
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//back wall
	glPushMatrix();
	glTranslated(-.08,0,0);
	glScaled(1.5+.02,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//room vertical wall
	glPushMatrix();
	glTranslated(4,0,0);
	glScaled(1,1,.5);
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//room horizantal wall
	glPushMatrix();
	glTranslated(4.4,0,2);
	glScaled(.4,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//wall above the room door
	glPushMatrix();
	glTranslated(4,3,2);
	glScaled(.11,.25,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();


	//left room horizantal wall
	glPushMatrix();
	glTranslated(0,0,2);
	glScaled(.4,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//lroom vertical wall
	glPushMatrix();
	glTranslated(1.6,0,0);
	glScaled(1,1,.35);
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//entrance room right wall
	glPushMatrix();
	glTranslated(1.6,0,2.59);
	glScaled(1,1,.35);
	glRotated(90.0,0,0,1);
	wall(0.08);
	glPopMatrix();
	//wall above main door
	glPushMatrix();
	glTranslated(-0.02,3,4);
	glScaled(.13,.27,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//wall right to the main door
	glPushMatrix();
	glTranslated(.48,0,4);
	glScaled(.68,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//wall right to the window
	glPushMatrix();
	glTranslated(4.8,0,4);
	glScaled(.3,1,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//wall below the window
	glPushMatrix();
	glTranslated(3.2,0,4);
	glScaled(.4,.25,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();
	//wall above the window
	glPushMatrix();
	glTranslated(3.2,3.03,4);
	glScaled(.4,.25,1);
	glRotated(-90.0,1,0,0);
	wall(0.08);
	glPopMatrix();




	room();
	watertank();
	terece();
	steps();
	window();
	fan();
    bed();
	text_rdr();
	lightOne();
    lightTwo();
	lamp();	
    //lampLight();
	// sphericalObject();
    lightBulb1();
    lightBulb2();

	speaker1();
	speaker2();
	sofa();
	s_table();
	carpet();
	cupboard();
	mainDrawer();
	television();
	lamp1();
	study_table();
	study_chair();
	wallshelf();
	bedsideDrawer();
    diningtable();
	myclock();
	solar();

	GLfloat	ambient[]={1,0.5,.5,1};
	GLfloat specular[]={1,1,1,1};
	GLfloat diffuse[]={1,.5,.5,1};
  	matprop(ambient,diffuse,specular,mat_shininess);
	//main door
	glPushMatrix();
	glTranslated(0,0,4);
	glRotated(maino,0,1,0);
	glTranslated(0,0,-4);
	glPushMatrix();
	glTranslated(0,0,4);
	glScaled(.12,.75,1);
	glRotated(-90.0,1,0,0);
	wall(0.04);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0,4);
	glScaled(.5,1,.2);
	glRotated(-90,1,0,0);
	gluCylinder(Cylinder, 0.05, 0.05, 3, 16, 16);
	glPopMatrix();
	glPopMatrix();
	//bolow room door
	glPushMatrix();
	glTranslated(4,0,(2-.025));
	glRotated(romo,0,1,0);
	glTranslated(-4,0,-(2-.025));
	glPushMatrix();
	glTranslated(4,0,2);
	glScaled(.099,.75,1);
	glRotated(-90.0,1,0,0);
	wall(0.01);
	glPopMatrix();

	glPushMatrix();
	glTranslated(4.01,0,2-.025);
	glScaled(.5,1,.6);
	glRotated(-90,1,0,0);
	gluCylinder(Cylinder, 0.05, 0.05, 3, 16, 16);
	glPopMatrix();

	glPopMatrix();
    glPopMatrix();
	glFlush();
}


void display(void)
{
	time(&ltime); // Get time
	newtime = localtime(&ltime); // Convert to local time
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	gluLookAt(view[0],view[1],view[2],look[0],look[1],look[2],0.0,1.0,0.0);
	earth();
    compound();
	house();
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();

}

void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	//to move the camera along -ve x axis
	case 'a':
				view[0]-=.1;
				glutPostRedisplay();
	break;
	//to move the camera along +ve x axis

	case 'd':
				view[0]+=.1;
				glutPostRedisplay();
	break;
	//to move the camera along +ve y axis

	case 'q':
				view[1]+=.1;
				glutPostRedisplay();
	break;
	//to move the camera along -ve y axis

	case 'e':
				if(view[1]>1.9)
				view[1]-=.1;
				glutPostRedisplay();
	break;
	//to move the camera along -ve z axis

	case 'w':
				view[2]-=.1;
				glutPostRedisplay();
	break;
	//to move the camera along +ve z axis
	case 's':
				view[2]+=.1;
				glutPostRedisplay();

	break;
	//to run and stop the fan
	case 'F':
	case 'f':
				flag*=-1;
				glutPostRedisplay();
	break;
	case '3': //to turn on and off light one
        if(switchLamp == false)
        {
            switchLamp = true; amb3=true; diff3=true; spec3=true;
            glEnable( GL_LIGHT4);
			break;
        }
        else if(switchLamp == true)
        {
            switchLamp = false; amb3=false; diff3=false; spec3=false;
            glDisable( GL_LIGHT4);
			break;
        }
	//turn on/off ambient light 1
	case '4': 
            if(amb1 == false) {amb1=true; break;}
            else{amb1=false; break;}
    case '5':
            if(diff1 == false) {diff1=true; break;}
            else{diff1=false; break;}
    case '6':
            if(spec1 == false) {spec1=true; break;}
            else{spec1=false; break;}
    //turn on/off ambient light 2
	case '7':
            if(amb2 == false) {amb2=true; break;}
            else{amb2=false; break;}
    case '8':
            if(diff2 == false) {diff2=true; break;}
            else{diff2=false; break;}
    case '9':
            if(spec2 == false) {spec2=true; break;}
            else{spec2=false; break;}
	//to open and close the main door
	case 'm':
	case 'M':
				if(maino==0)
				  maino=85;
				else
					maino=0;
	break;
	//to open and close the below room door
	case 'O':
	case 'o':
				if(romo==0)
				  romo=75;
				else
					romo=0;
	break;
	//to open and close the above room door
	case 'p':
	case 'P':
				if(tro==0)
				  tro=70;
				else
					tro=0;
	break;
	//to open and close the main gate
	case 'g':
	case 'G':
				if(mgo==0)
				  mgo=1;
				else
					mgo=0;
	break;
	//to open and close the sub gate
	case 'h':
	case 'H':
				if(sgo==0)
				  sgo=50;
				else
					sgo=0;
	break;
	//inside view
	case 'i':
	case 'I':
				view[0]=2.8;
				view[1]=2;
				view[2]=4.8;
				look[0]=2.8;
				look[1]=2;
				look[2]=1;
	break;
	//top view
	case 'T':
	case 't':
				view[0]=6;
				view[1]=12;
				view[2]=10;
				look[0]=2;
				look[1]=4;
				look[2]=2;
	break;
	//front view
	case 'j':
	case 'J':
				view[0]=2;
				view[1]=2;
				view[2]=12.9;
				look[0]=3;
				look[1]=2;
				look[2]=3;
	break;
	//back view
	case 'k':
	case 'K':
				view[0]=1;
				view[1]=6;
				view[2]=-7;
				look[0]=2;
				look[1]=4;
				look[2]=2;
	break;

	}


}

void mySpecialKeyFunc( int key, int x, int y )
{
	switch ( key ) {
	case GLUT_KEY_UP:
		if ( speed < 25.0) {
			speed+=5;
		}
		break;
	case GLUT_KEY_DOWN:
		if (speed>0) {
			speed-=5;
		}
		break;
	}
}


void main_menu(int m)
{
	switch(m)
	{
	case 1:

		exit(0);

	}
}


void fan_menu(int m)
{
	switch(m)
	{
	case 1:

		flag*=-1;
			glutPostRedisplay();
			break;
	case 2:if ( speed < 30.0) {
			speed+=5;
		}
		break;
	case 3:
		if (speed>0) {
			speed-=5;
		}
		break;

	}
}


void door_menu(int m)
{
	switch(m)
	{
	case 1:
				if(maino==0)
				  maino=85;
				else
					maino=0;
				break;

	case 2:

				if(romo==0)
				  romo=75;
				else
					romo=0;
				break;
	case 3:
				if(tro==0)
				  tro=90;
				else
					tro=0;
				break;
	}
}


void gate_menu(int m)
{
	switch(m)
	{

	case 1:
				if(mgo==0)
				  mgo=1;
				else
					mgo=0;
				break;
	case 2:
				if(sgo==0)
				  sgo=50;
				else
					sgo=0;
				break;
	}
}

void house_view(int m)
{
	switch(m)
	{
	case 1:
		view[0]=2.8;
		view[1]=2;
		view[2]=4.8;
		look[0]=2.8;
		look[1]=2;
		look[2]=1;
	break;
	case 2:
		view[0]=6;
		view[1]=12;
		view[2]=10;
		look[0]=2;
		look[1]=8;
		look[2]=2;
		break;
	case 3:
		view[0]=2;
		view[1]=2;
		view[2]=12.9;
		look[0]=3;
		look[1]=2;
		look[2]=3;
		break;
	case 4:
		view[0]=1;
		view[1]=6;
		view[2]=-7;
		look[0]=2;
		look[1]=4;
		look[2]=2;
		break;
	}
}

void menu()
{


	int sub_menu1=glutCreateMenu(fan_menu);
	glutAddMenuEntry("on/off fan(s)",1);
	glutAddMenuEntry("speed up(up arrow)",2);
	glutAddMenuEntry("speed down(down arrow)",3);

	int sub_menu2=glutCreateMenu(door_menu);
	glutAddMenuEntry("main door(q)",1);
	glutAddMenuEntry("ground floor room door(o)",2);
	glutAddMenuEntry("1st floor room door(p)",3);

	int sub_menu3=glutCreateMenu(gate_menu);
	glutAddMenuEntry("main gate(g)",1);
	glutAddMenuEntry("sub gate(h)",2);

	int sub_menu4=glutCreateMenu(house_view);
	glutAddMenuEntry("front view(j)",3);
	glutAddMenuEntry("top view(t)",2);
	glutAddMenuEntry("inside view(i)",1);
	glutAddMenuEntry("back view(k)",4);

	glutCreateMenu(main_menu);
	glutAddMenuEntry("quit",1);
	glutAddSubMenu("fan menu",sub_menu1);
	glutAddSubMenu("open/close door",sub_menu2);
	glutAddSubMenu("open/close gate",sub_menu3);
	glutAddSubMenu("house view",sub_menu4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



int main(int argc,char**argv)
{
	glutInit(&argc,argv);//to initialize the glut library
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(w,h);
	glutInitWindowPosition(0,0);
	glutCreateWindow("3D Modelling of the House");
	myinit();
	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(mySpecialKeyFunc);
	menu();
	glutFullScreen();//to see o/p in full screen on monitor
	glShadeModel(GL_SMOOTH);//smooth shaded
	glEnable(GL_DEPTH_TEST);//to remove hidden surface
	glEnable(GL_NORMALIZE);//to make normal vector to unit vector
	glEnable(GL_LIGHTING);
	GLfloat lightIntensity[]={.7,.7,.7,1};
	GLfloat light_position[]={2,5,-3,0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
	// glEnable(GL_LIGHT0);
	glClearColor(0,.3,.8,0);
	glViewport(0,0,w,h);
	glutMainLoop();
	return 0;
}