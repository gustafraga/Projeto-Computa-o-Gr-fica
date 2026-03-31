#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Objeto {
    string tipo;
    int n;
    vector<float> coords;
    float r, g, b;
};

vector<Objeto> objetos;

void carregarArquivo() {
    ifstream file("data/dados.dat");

    if (!file.is_open()) {
        cout << "Erro ao abrir arquivo!" << endl;
        return;
    }

    string tipo;

    while (file >> tipo) {
        if (tipo == "POLYGON") {
            Objeto obj;
            obj.tipo = tipo;

            file >> obj.n;

            for (int i = 0; i < obj.n * 2; i++) {
                float val;
                file >> val;
                obj.coords.push_back(val);
            }

            file >> obj.r >> obj.g >> obj.b;

            objetos.push_back(obj);
        }
    }

    file.close();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &obj : objetos) {
        glColor3f(obj.r, obj.g, obj.b);

        if (obj.tipo == "POLYGON") {
            glBegin(GL_POLYGON);

            for (int i = 0; i < obj.coords.size(); i += 2) {
                glVertex2f(obj.coords[i], obj.coords[i + 1]);
            }

            glEnd();
        }
    }

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    carregarArquivo();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Projeto OpenGL 2D");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
