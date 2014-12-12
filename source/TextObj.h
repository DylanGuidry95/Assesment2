#pragma once
#include <string>
#include "AIE.h"
#include "Decl.h"
class ControlObject
{
public:
	float m_x, m_y, m_w, m_h;
	
	int control;
	std::string name; // name of control
	char key;         // button for the control
	
	bool m_highlight; // mouse over, make it shine
	bool m_change;	  // Means this obj is currently changing
	bool m_selected;  // selection is made, but the key hasn't been released yet
			
	
	static bool selected; // static to ensure only one can be selected
						  // released when m_selected is false

	ControlObject(std::string name, int control, char key, float x, float y, float w, float h)
		: name(name + ":\t"), m_change(false), m_highlight(false), control(control),		
		key(key), m_x(x), m_y(y), m_h(h), m_w(w), m_selected(false)
	{

	}

	bool inside(float a_x, float a_y)
	{
		return (a_x > m_x && a_x < m_x + m_w &&
			a_y > m_y && a_y < m_y + m_h);
	}

	void update();
};

/*
	Mouse Over
	Mouse Down
	Key Down
	Key Up
	Ensure unique selection
*/