#pragma once

#include <glew.h>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include "Camera.h"
#include <QVector2D>
#include <vector>
#include "SketchyRenderingManager.h"

using namespace std;

class MainWindow;

class GLWidget3D : public QGLWidget {
private:
	Camera camera;
	QPoint lastPos;
	SketchyRenderingManager renderManager;

public:
	GLWidget3D();

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();    
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
};

