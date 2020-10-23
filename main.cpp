#include <iostream>
#include <list>
#include <iterator>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "files.h"

using namespace std;
list<Objects> objs;
void display (void);
void init(void);

int main(int argc, char** argv){
	File fileOpener;//In this object we will save all the info about the 3D object
    fileOpener.fileName("four_figs.obj");

    if(!fileOpener.open())//In the case the file can not be opened, we send an error message
        cout<<"Error: Can´t open the file";
    else//The file open correctly
    {
        objs = fileOpener.saveInfo();//We do everything related to saving the information
    }
 	glutInit(&argc, argv);
   	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   	glutInitWindowSize (350, 350); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (":: O B J E C T ::");
	init();
	glutDisplayFunc(display); 
	glutMainLoop();
	return 0;
}

void display (void){
	// Clear all pixels
	glClear (GL_COLOR_BUFFER_BIT);
	// Define color
	glColor3f (1.0, 1.0, 1.0);
	list <Objects> :: iterator it_Obj;
	list<Faces> :: iterator it_Faces;
	list<Vertex> :: iterator it_Vertex;
	for(it_Obj = objs.begin() ; it_Obj != objs.end() ; it_Obj++){//We run each object found in the file
		//it_Obj->showAll();
		for(it_Faces = it_Obj->faces.begin() ; it_Faces != it_Obj->faces.end() ; it_Faces++){
			//We pass through each face to draw the figure
			glBegin(GL_LINE_LOOP);
				for(it_Vertex = it_Faces->vertices.begin() ; it_Vertex != it_Faces->vertices.end() ; it_Vertex++){
			   		//We have to print based on the vertices of each face
				   	glVertex3d(it_Vertex->getX(), it_Vertex->getY(), it_Vertex->getZ());
				}
			glEnd();
			cout<< "\n\n";
		}
	} 
	// Start processing buffered OpenGL routines 
	glFlush ();
}

void init (void){
	// Select clearing (background) color
	glClearColor (0.0, 0.0, 0.0, 0.0);

	// Initialize viewing values
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);
		   
	// Rotate the whole scene so that three faces of the object are seen
	//glRotatef (120.0, 0.0, 1.0, 0.0);
	glRotatef (30.0, 1.0, 1.0, 1.0);
}
