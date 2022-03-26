#pragma once

#include "drawer.h"

class MyDrawer : public Drawer {
	float rotation = 0;
public:
	virtual void PostUpdate() override {
		rotation += 1;
		if(rotation > 360)
			rotation = 0;
	}

	virtual void Draw() override {
		glTranslatef(0, 0, -4);
		glRotatef(rotation, 1.0, 1.0, 1.0);
		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUAD_STRIP);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, -1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, -1.0f);
		glEnd();
	}
};
