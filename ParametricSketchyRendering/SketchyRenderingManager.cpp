#include "SketchyRenderingManager.h"
#include <QGLWidget>

SketchyRenderingManager::SketchyRenderingManager() {
}


void SketchyRenderingManager::addObject(const QString& object_name, const std::vector<std::vector<Vertex> >& vertices) {
	objects[object_name] = vertices;
}

void SketchyRenderingManager::renderAll() {
	for (auto it = objects.begin(); it != objects.end(); ++it) {
		render(it.key());
	}
}

void SketchyRenderingManager::render(const QString& object_name) {
	glLineWidth(5);
	for (int i = 0; i < objects[object_name].size(); ++i) {
		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		for (int j = 0; j < objects[object_name][i].size(); ++j) {
			glVertex3f(objects[object_name][i][j].position.x, objects[object_name][i][j].position.y, objects[object_name][i][j].position.z);
		}
		glEnd();
		
		glColor3f(0, 0, 0);
		for (int j = 0; j < objects[object_name][i].size(); ++j) {
			int next = (j + 1) % objects[object_name][i].size();

			// order two vertices p1, p2
			glm::vec3 p1 = objects[object_name][i][j].position;
			glm::vec3 p2 = objects[object_name][i][next].position;
			if (length(p1) > length(p2)) {
				std::swap(p1, p2);
			} else if (length(p1) == length(p2)) {
				if (p1.x > p2.x) {
					std::swap(p1, p2);
				} else if (p1.x == p2.x) {
					if (p1.y > p2.y) {
						std::swap(p1, p2);
					} else if (p1.y == p2.y) {
						if (p1.z > p2.z) {
							std::swap(p1, p2);
						}
					}
				}
			}

			// add noise to the vertices p1, p2
			int seed = glm::length(p1) * 10 + glm::length(p2) * 10 + p1.x * 100 + p1.y * 30 + p1.z * 10 + p2.x * 100 + p2.y * 30 + p2.z * 10;
			srand(seed);

			p1.x += (p1 - p2).x * 0.1 + genRand();
			p1.y += (p1 - p2).y * 0.1 + genRand();
			p1.z += (p1 - p2).z * 0.1 + genRand();
			p2.x += (p2 - p1).x * 0.1 + genRand();
			p2.y += (p2 - p1).y * 0.1 + genRand();
			p2.z += (p2 - p1).z * 0.1 + genRand();

			// add wiggle
			// ...


			glBegin(GL_LINES);
			glVertex3f(p1.x, p1.y, p1.z);
			glVertex3f(p2.x, p2.y, p2.z);
			glEnd();
		}
	}
}

float SketchyRenderingManager::genRand() {
	return ((float)rand() / RAND_MAX - 0.5f) * 0.05;
}
