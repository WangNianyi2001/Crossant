#pragma once

#include "drawer.h"

class MyDrawer : public Drawer {
	float rotation = 0;
public:
	MyDrawer() {
		SetClearColor(Color3f{ .1f, .1f, .1f });
	}

	virtual void PostUpdate() override {
		rotation += 1;
		if(rotation > 360)
			rotation = 0;
	}

	virtual void Draw() override {
		glTranslatef(0, 0, -4);
		glRotatef(rotation, 1, 1, 1);
		// Color makes no effect after enabling lighting
		// glColor3f(.3f, .1f, .05f);
		glutSolidTorus(0.275, 0.85, 128, 128);
	}
};
