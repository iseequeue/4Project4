#include "system.hpp"

void System::initialize()
{

	int count = 0;
	for (auto i = 0U; i < sizex; i++)
	{
		for (auto j = 0U; j < sizey; j++)
		{
			if (count == sizex*sizey-1)
			{
				break;
			}

			if (i != sizex - 1)
			{
				if (j != 0)
				{
					m_links.push_back(Link(particle(count), particle(count + sizey-1), 0.5f));
				}

				m_links.push_back(Link(particle(count), particle(count + 1), 0.5f));

				m_links.push_back(Link(particle(count), particle(count + sizey), 0.5f));

				if (j != sizey - 1)
				{
					m_links.push_back(Link(particle(count), particle(count + sizey + 1), 0.5f));
				}
			}
			else 
			{ 
				m_links.push_back(Link(particle(count), particle(count + 1), 0.5f));
			}
			count++;

		}
	}

}

void System::push(const sf::Vector2f force) const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(force);
	}
}

void System::update() const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(0.25f);

		if (m_particles[i]->position().y + m_particles[i]->radius() > m_max_point.y)
		{
			m_particles[i]->set_y(m_max_point.y - m_particles[i]->radius());
		}

		if (m_particles[i]->position().y - m_particles[i]->radius() < m_min_point.y)
		{
			m_particles[i]->set_y(m_min_point.y + m_particles[i]->radius());
		}

		if (m_particles[i]->position().x + m_particles[i]->radius() > m_max_point.x)
		{
			m_particles[i]->set_x(m_max_point.x - m_particles[i]->radius());
		}

		if (m_particles[i]->position().x - m_particles[i]->radius() < m_min_point.x)
		{
			m_particles[i]->set_x(m_min_point.x + m_particles[i]->radius());
		}
	}

	for (auto i = 0U; i < std::size(m_links); ++i)
	{
		m_links[i].update();
	}


}