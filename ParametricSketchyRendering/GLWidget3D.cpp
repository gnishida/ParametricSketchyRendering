﻿#include <iostream>
#include "GLWidget3D.h"
#include "MainWindow.h"
#include <GL/GLU.h>
#include "GLUtils.h"

#define SQR(x)	((x) * (x))

GLWidget3D::GLWidget3D() {
}

/**
 * This event handler is called when the mouse press events occur.
 */
void GLWidget3D::mousePressEvent(QMouseEvent *e) {
	lastPos = e->pos();
}

/**
 * This event handler is called when the mouse release events occur.
 */
void GLWidget3D::mouseReleaseEvent(QMouseEvent *e) {
	updateGL();
}

/**
 * This event handler is called when the mouse move events occur.
 */
void GLWidget3D::mouseMoveEvent(QMouseEvent *e) {
	float dx = (float)(e->x() - lastPos.x());
	float dy = (float)(e->y() - lastPos.y());
	lastPos = e->pos();

	if (e->buttons() & Qt::LeftButton) {
		camera.changeXRotation(dy);
		camera.changeYRotation(dx);
	} else if (e->buttons() & Qt::RightButton) {
		camera.changeXYZTranslation(0, 0, -dy * camera.dz * 0.02f);
	} else if (e->buttons() & Qt::MidButton) {
		camera.changeXYZTranslation(-dx, dy, 0);
	}

	updateGL();
}

/**
 * This function is called once before the first call to paintGL() or resizeGL().
 */
void GLWidget3D::initializeGL() {
	glClearColor(0.443, 0.439, 0.458, 0.0);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	//static GLfloat lightPosition[4] = {0.0f, 0.0f, 100.0f, 0.0f};
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	std::vector<std::vector<Vertex> > vertices;
	glutils::drawBox(1, 1, 1, glm::vec4(1, 1, 1, 1), glm::mat4(), vertices);
	renderManager.addObject("test", vertices);
}

/**
 * This function is called whenever the widget has been resized.
 */
void GLWidget3D::resizeGL(int width, int height) {
	height = height?height:1;

	glViewport( 0, 0, (GLint)width, (GLint)height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width/(GLfloat)height, 0.1f, 10000);
	glMatrixMode(GL_MODELVIEW);
}

/**
 * This function is called whenever the widget needs to be painted.
 */
void GLWidget3D::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
   	camera.applyCamTransform();	

	renderManager.renderAll();
}

