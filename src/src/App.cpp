#include "App.h"

void App::Run()
{
	Initialise();
	m_window.setFramerateLimit(m_framerate_limit);
	while(m_window.isOpen())
	{
		
		m_window.clear(m_background_color);
		m_input_handler.HandleInput();
		m_renderer.Render(m_window);
		//m_input_bar.Draw(m_window);
		m_window.display();
	}
}

void App::Initialise()
{
	SetDefaultContextSettings();
	
	//m_solver.Solve(m_grid.solution);
}

void App::SetDefaultContextSettings()
{
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 8;
	settings.sRgbCapable = true;
}
