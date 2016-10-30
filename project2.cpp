/*==================================================================================================
 PROGRAMMER:			Thomas Kroll, Nathan Kroll
 COURSE:				CSC 525/625
 MODIFIED BY:			Thomas Kroll:kroll001, Nathan Kroll:Kroll1483
 LAST MODIFIED DATE:	10/10/2016
 DESCRIPTION:			This program displays multiple objects on a 900x676 window.  The first thing
                        displayed is a pixel map, which is used as the background of this scene.
                        The pixel map is read from the file "pixel_map.txt" to be displayed.
                        Next the program displays a green Bitmap of tiny bushes (or broccoli)
                        randomly across the bottom of the screen.
                        Next is the (slightly creepy) stick figures, which are
                        composed of line segments, circles and partial circles.  The figures'
                        shields are made of a pattern filled polygon rendered on top of a solid
                        polygon. Lastly, the text "The Battle of Broccoli Fields" is written across
                        the top of the window.
 NOTE:					N/A
 FILES:					project1.cpp, pixel_map.txt (projProject.sln, ...)
 IDE/COMPILER:			MicroSoft Visual Studio 2013
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on myCPPproj.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
	4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <GL/glut.h>				// include GLUT library

class TextEditorWindow {
public:
	TextEditorWindow(int width, int height, const char title[]);

	void drawText(int x, int y, std::string text);

private:
	void setUpWindow(const char title[]);
	void setUpMenus();
	void setUpMouseEvents();
	void setUpKeyboardEvents();
	void setFont(int newFont);
	void setColor(float red, float green, float blue);
	int width;
	int height;
	int leftWorldX;
	int rightWorldX;
	int topWorldY;
	int lowerWorldY;
	float color[3];
	int font;
	std::vector<char> displayedText;
};

TextEditorWindow::TextEditorWindow(int width, int height, const char title[]) {
	this->width = width;
	this->height = height;
	this->leftWorldX = (width / 2) * -1;
	this->rightWorldX = (width / 2);
	this->topWorldY = (height / 2);
	this->lowerWorldY = (height / 2) * -1;
	setUpWindow(title);
}

void TextEditorWindow::setUpWindow(const char title[]) {
	glutInitWindowSize(width, height);				// specify a window size
	glutInitWindowPosition(leftWorldX, topWorldY);			// specify a window position
	glutCreateWindow(title);
	glClearColor(1, 1, 1, 0);			// specify a background color: white 
	gluOrtho2D(leftWorldX, rightWorldX, lowerWorldY, topWorldY);
}

//***********************************************************************************
// Window dimentions
const int windowX = 900;
const int windowY = 676;


//***********************************************************************************
void myInit()
{glClearColor(1, 1, 1, 0);			// specify a background clor: white 
 int x = windowX / 2;
 int y = windowY / 2;
 gluOrtho2D(-x, x, -y, y);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT);	// draw the background
    glFlush(); // flush out the buffer contents
}

#ifdef _WIN32
#else
#endif


int main()
{
    //====================================================================//
    // These lines are only here so I (Thomas) can work on this at home
    // since the only c++ compiler available to me is g++
    // (Visual Studio and Linux don't play well together)
    int argc = 1;
    char *argv[1] = {(char*)"Something"};
    glutInit(&argc, argv);
    //====================================================================//

	TextEditorWindow editorWindow(400, 400, "Text Editor Window");									// setting up


    glutDisplayFunc(myDisplayCallback);		// register a callback


    glutMainLoop();							// get into an infinite loop
}
