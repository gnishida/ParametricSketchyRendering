#pragma once

#include "Vertex.h"
#include <QString>
#include <QMap>
#include <vector>

class SketchyRenderingManager {
public:
	QMap<QString, std::vector<std::vector<Vertex> > > objects;

public:
	SketchyRenderingManager();

	void addObject(const QString& object_name, const std::vector<std::vector<Vertex> >& vertices);
	void renderAll();
	void render(const QString& object_name);
	float genRand();
};

