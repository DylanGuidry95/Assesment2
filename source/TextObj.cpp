#include "TextObj.h"
#include "DataBase.h"

bool ControlObject::selected = false;

void ControlObject::update()
	{
		double x, y;
		GetMouseLocation(x, y);
		y = g_h - y + m_h; // mouse and window Ys are inverted

		m_highlight = inside(x, y); // highlight

		if (!selected)	 // Mouse down
		{
			m_change = GetMouseButtonDown(0) && m_highlight;
			selected = m_change;
		}

		SColour col =
			m_change    ? SColour(255, 0, 0, 255) :
			selected    ? SColour(128, 128, 128, 255) :
			m_highlight ? SColour(255, 255, 0, 255) :
						  SColour(255, 255, 255, 255);

		DrawString((name + key).c_str(), m_x, m_y, col);


		if (!IsKeyDown(key) && m_selected) // Key Released
		{
			selected = false;
			m_selected = false;
		}

		if (m_change)
			for (int i = 32; i < 128; ++i)
				if (IsKeyDown(i))			// Key pressed down
				{
					ControlManager::changeKey((e_Controls)control, i);
					key = i;			
					m_change = false;
					m_selected = true;
				}
	}