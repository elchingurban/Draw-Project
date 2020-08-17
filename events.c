#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <gl.h>
#include <GL/glut.h>
#include "lineStrip.h"

int window_width, window_height;

struct lineStrip *vertexList;
struct lineStrip *selectedVertex;
struct lineStrip **selectedEdge;

int mode = 0;
int vertices = 0; // number of vertices

//-------------------------------------------------------------
// Draws a red cross of size size pixels at point (x,y)
static void _drawRedCross(int x, int y, int size)
{
	// Let the current color be red
	glColor3ub(255, 0, 0);

	// Horizontal line
	glBegin(GL_LINE_STRIP);
	glVertex2i(x - size, y);
	glVertex2i(x + size, y);
	glEnd();

	// Vertical line
	glBegin(GL_LINE_STRIP);
	glVertex2i(x, y - size);
	glVertex2i(x, y + size);
	glEnd();
}

//-------------------------------------------------------------
// The call back function which is called each time that we need
// to draw everything again. All your drawings should be called
// in this function. Initially, we only draw a cross.

static void _display_CB() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, window_width, window_height, 0, -1, 1);

	glClear(GL_COLOR_BUFFER_BIT);

	// Let the current color be black
	glColor3ub(0, 0, 0);

	//Drawing two line segments
	struct lineStrip *temp = vertexList;

	glBegin(GL_LINE_STRIP);

	while(temp) {
		if(mode == 1 && selectedEdge) {
			if(selectedEdge[0] == temp) {
				glColor3ub(255, 0, 0);
			} else if(selectedEdge[1] == temp) {
				glColor3ub(0, 0, 0);
			}
		}
		glVertex2i(temp->v.x, temp->v.y);
		temp = temp->next;
	}
	glEnd();
	
	
	if(mode == 1 && selectedVertex) {
		_drawRedCross(selectedVertex->v.x, selectedVertex->v.y, 10);
	}

	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------------
// The call back function which is called each time that the
// graphical window is resized.

static void _reshape_CB(int largeur, int hauteur)
{
	window_width = largeur;
	window_height = hauteur;
	glViewport(0, 0, window_width, window_height);
}

static struct lineStrip *_select_vertex(struct vector mouse) {
	struct lineStrip *temp = vertexList;

	while(temp) {
		if(V_PtPtDistance(temp->v, mouse) < 5) {
			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

static struct lineStrip **_select_edge(struct vector mouse) {
	struct lineStrip **edge = (struct lineStrip **)malloc(2 * sizeof(struct lineStrip *));
	
	struct lineStrip *temp = vertexList;

	while(temp->next) {
		if(V_PtSegmentDistance(mouse, temp->v, temp->next->v) < 5) {
			edge[0] = temp;
			edge[1] = temp->next;
		}
		temp = temp->next;
	}

	return edge;
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a mouse button is pressed or released.

static void _mouse_CB(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {

		switch (button) {
			case GLUT_LEFT_BUTTON:
				if(mode == 0) {
					vertexList = append(V_new(x, y), vertexList);
					vertices++;
				} else if(mode == 1) {
					selectedVertex = _select_vertex(V_new(x, y));

					if(selectedVertex == NULL) {
						selectedEdge = _select_edge(V_new(x, y));
					} else 
						selectedEdge = NULL;
				}				
				break;
			case GLUT_RIGHT_BUTTON:
				break;
			case GLUT_MIDDLE_BUTTON:
				break;
		}
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------
// The call back function which is called each time that
// the mouse moves when being clicked.

static void _mouse_move_CB(int x, int y) {
	if(mode == 1 && selectedVertex) {
		selectedVertex->v = V_new(x, y);
		glutPostRedisplay();
	}
	// printf("Mouse position : (%d,%d)\n", x, y);
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a key (corresponding to an ascii code) on the keyboard is pressed.

static void _keyboard_CB(unsigned char key, int x, int y) {
	switch (key) {
	case 8:
		if(mode == 0) {
			vertexList = pop(vertexList);
			if(vertices != 0) {
				vertices--;
			}
		}
		else if(mode == 1 && selectedVertex != NULL) {
			vertexList = deleteElement(selectedVertex, vertexList);
			selectedVertex = selectedVertex->next;
			vertices--;
		}
		break;
	case 'n':
		mode = 0;
		break;
	case 'i':
		if(mode == 1 && selectedEdge) {
			float x_MidPoint = (selectedEdge[0]->v.x + selectedEdge[1]->v.x) / 2;
			float y_MidPoint = (selectedEdge[0]->v.y + selectedEdge[1]->v.y) / 2;

			vertexList = insert(V_new(x_MidPoint, y_MidPoint), selectedEdge[0], vertexList);
			vertices++;
			selectedVertex = selectedEdge[0]->next;

		}
	case 13:
		if(vertices >= 2) {
			mode = 1;
		}
		break;
	case 27:
		exit(0);
		break; // escape key
	default:
		printf("Unknown key : %d %c\n", key, key);
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a special key (arrows, function keys) is pressed.

static void _special_CB(int key, int x, int y) {
	if(mode == 1 && selectedVertex) {
		switch (key)
		{
			case GLUT_KEY_LEFT:
				selectedVertex->v.x -= 5;
			break;
			case GLUT_KEY_RIGHT:
				selectedVertex->v.x += 5;
			break;
			case GLUT_KEY_UP:
				selectedVertex->v.y -= 5;
			break;
			case GLUT_KEY_DOWN:
				selectedVertex->v.y += 5;
			break;
			case GLUT_KEY_F1:
				printf("F1 key.\n");
			break;
		default:
			fprintf(stderr, "Unknown special key.\n");
		}
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------

int main(int argc, char **argv) {
	if (argc != 3) {
		printf("\nUsage : %s <width> <height>\n\n", argv[0]);
		return 1;
	} else {
		// Reading the command line arguments
		window_width = atoi(argv[1]);
		window_height = atoi(argv[2]);

		int windowPosX = 100, windowPosY = 100;
		vertexList = newList();

		// Initializing GLUT (graphic window and events manager)
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(window_width, window_height);
		glutInitWindowPosition(windowPosX, windowPosY);
		glutCreateWindow(argv[0]);

		// Initializing OpenGL (drawing tool)
		glViewport(0, 0, window_width, window_height);
		glClearColor(255, 255, 255, 0);

		// Associating callback functions to each type of event
		glutDisplayFunc(_display_CB);
		glutReshapeFunc(_reshape_CB);
		glutKeyboardFunc(_keyboard_CB);
		glutSpecialFunc(_special_CB);
		glutMouseFunc(_mouse_CB);
		glutMotionFunc(_mouse_move_CB);

		// Starting the loop which waits for events.
		glutMainLoop();
	}
}