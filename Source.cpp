#include <GL/glut.h>
#include <cmath>
#include <vector>

using namespace std;

// To store the points clicked
struct Point {
    int x, y;
};

Point point1, point2;
bool point1Set = false;

// Function to implement the DDA algorithm
void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps;
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));  // Round the coordinates to integers
        x += xInc;
        y += yInc;
    }
    glEnd();
    glFlush();
}

// Function to handle mouse clicks
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        Point pt = { x, glutGet(GLUT_WINDOW_HEIGHT) - y }; // Adjust for window height

        if (!point1Set) {
            point1 = pt;
            point1Set = true;
        }
        else {
            point2 = pt;
            drawLineDDA(point1.x, point1.y, point2.x, point2.y);
            point1Set = false; // Reset for the next line
        }
    }
}

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glColor3f(1.0, 1.0, 1.0); // Set the drawing color to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // Set the coordinate system
}

// Main display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
