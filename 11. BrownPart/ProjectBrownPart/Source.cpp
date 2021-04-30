#include <chrono>
#include <ctime>
#include <cstdint>
#include <memory>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>

#include <iostream>
using namespace sf;

class Particle
{
public:

	Particle(float x, float y, float dx, float dy, float mass, float radius) :
		m_x(x), m_y(y), m_dx(dx), m_dy(dy), m_mass(mass), m_radius(radius)
	{}

	float m_mass;
	float m_radius;
	float m_x, m_y;
	float m_dx, m_dy;

};

 void isCollide(std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2)
{
	 auto d = (p2->m_x - p1->m_x) * (p2->m_x - p1->m_x) + (p2->m_y - p1->m_y) * (p2->m_y - p1->m_y);
	 if (d <= (p1->m_radius + p2->m_radius) * (p1->m_radius + p2->m_radius))
	 {
		 auto v1x = ((p2->m_x - p1->m_x) * p1->m_dx + (p2->m_y - p1->m_y) * p1->m_dy)/d;
		 auto v1y = ((p1->m_y - p2->m_y) * p1->m_dx + (p2->m_x - p1->m_x) * p1->m_dy)/d;

		 auto v2x = ((p2->m_x - p1->m_x) * p2->m_dx + (p2->m_y - p1->m_y) * p2->m_dy)/d;
		 auto v2y = ((p1->m_y - p2->m_y) * p2->m_dx + (p2->m_x - p1->m_x) * p2->m_dy)/d;

		 auto v1x_new = ((p1->m_mass - p2->m_mass) * v1x + 2 * p2->m_mass * v2x) / (p1->m_mass + p2->m_mass);
		 auto v2x_new = (2 * p1->m_mass * v1x + (p2->m_mass - p1->m_mass) * v2x) / (p1->m_mass + p2->m_mass);

		 p1->m_dx = (p2->m_x - p1->m_x) * v1x_new + (p1->m_y - p2->m_y) * v1y;
		 p1->m_dy = (p2->m_y - p1->m_y) * v1x_new + (p2->m_x - p1->m_x) * v1y;

		 p2->m_dx = (p2->m_x - p1->m_x) * v2x_new + (p1->m_y - p2->m_y) * v2y;
		 p2->m_dy = (p2->m_y - p1->m_y) * v2x_new + (p2->m_x - p1->m_x) * v2y;

	 }
}

 class System
 {
 public:

	 System(std::size_t amount = 50, std::size_t fraction = 6, float width = VideoMode::getDesktopMode().width, 
		 float height = VideoMode::getDesktopMode().height) :
		 m_amount(amount), 
		 m_fraction(fraction), 
		 m_width(width),
		 m_height(height),
		 m_application(VideoMode(m_width, m_height), "Particles"),
		 mersenne(rd()),
		 uidx(0.0f, m_width),
		 uidy(0.0f, m_height),
		 uidv(-4.0f / 5, 4.0f / 5),
		 field(m_fraction, std::vector<int>(m_fraction, 0))

	 {
		 m_particle.reserve(m_amount);
		 m_circle.reserve(m_amount);

		 m_particle.push_back(std::make_shared<Particle>(width / 2, height / 2, 0.1f, 0.1f, 6.0f, 36.0f));

		 m_circle.push_back(std::make_shared<CircleShape>(m_particle[0]->m_radius));

		 m_circle[0]->setFillColor(Color::Magenta);

		 double x, y;

		 for (auto i = 1U; i < m_amount; i++)
		 {
			 x = uidx(mersenne);
			 y = uidy(mersenne);

			 while ((x + width / 2 + m_particle[0]->m_radius) * (x + width / 2 + m_particle[0]->m_radius) +
				 (y + height / 2 + m_particle[0]->m_radius) * (y + height / 2 + m_particle[0]->m_radius)
				 <= (m_particle[0]->m_radius + 10.0f) * (m_particle[0]->m_radius + 10.0f))
			 {
				 x = uidx(mersenne);
				 y = uidy(mersenne);
			 }
			 m_particle.push_back(std::make_shared<Particle>(x, y, uidv(mersenne), uidv(mersenne), 1.0f, 6.0f));

			 m_circle.push_back(std::make_shared<CircleShape>(m_particle[i]->m_radius));

			 m_circle[i]->setFillColor(Color::Blue);
		 }
	 }

	 void run();

	 const std::size_t m_amount;
	 const std::size_t m_fraction;

	 const float m_width;
	 const float m_height;

	 RenderWindow m_application;

	 std::vector <std::shared_ptr<Particle>> m_particle;
	 std::vector <std::shared_ptr<CircleShape>> m_circle;

	 std::vector <std::vector<int>> field;

	 std::random_device rd;
	 std::mt19937 mersenne;
	 std::uniform_real_distribution<float> uidx;
	 std::uniform_real_distribution<float> uidy;
	 std::uniform_real_distribution<float> uidv;
 };

 void System::run()
 {
	 std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();

	 const std::chrono::microseconds delay(50000);

	 std::chrono::microseconds timer(0);

	 while (m_application.isOpen())
	 {
		 timer += std::chrono::duration_cast <std::chrono::microseconds> (std::chrono::steady_clock::now() - time_point);

		 time_point = std::chrono::steady_clock::now();

		 Event event;

		 while (m_application.pollEvent(event))
		 {
			 if (event.type == Event::Closed)
			 {
				 m_application.close();
			 }
		 }

		 for (auto i = 0u; i < m_fraction; i++)
		 {
			 for (auto j = 0u; j < m_fraction; j++)
			 {
				 RectangleShape rectangle(Vector2f(m_width / m_fraction, m_height / m_fraction));

				 rectangle.setPosition(i * m_width / m_fraction, j * m_height / m_fraction);

				 rectangle.setFillColor(Color(std::abs(255 - field[i][j] * 20), 255, 255));

				 m_application.draw(rectangle);

				 field[i][j] = 0;
			 }
		 }


		 for (auto i = 0U; i < m_particle.size(); i++)
		 {
			 for (auto j = i; j < m_particle.size(); j++)
			 {
				 if (i != j)
					 isCollide(m_particle[i], m_particle[j]);
			 }
		 }

		 for (auto i = 0U; i < m_particle.size(); i++)
		 {
			 m_circle[i]->setPosition(m_particle[i]->m_x - m_particle[i]->m_radius, m_particle[i]->m_y - m_particle[i]->m_radius);

			 m_application.draw(*m_circle[i]);

			 m_particle[i]->m_x += m_particle[i]->m_dx;

			 m_particle[i]->m_y += m_particle[i]->m_dy;

			 if (m_particle[i]->m_x + m_particle[i]->m_radius > m_width || m_particle[i]->m_x - m_particle[i]->m_radius < 0)
			 {
				 m_particle[i]->m_dx = -m_particle[i]->m_dx;
			 }

			 if (m_particle[i]->m_y + m_particle[i]->m_radius > m_height || m_particle[i]->m_y - m_particle[i]->m_radius < 0)
			 {
				 m_particle[i]->m_dy = -m_particle[i]->m_dy;
			 }

			 field[static_cast<int>(m_particle[i]->m_x / (m_width / m_fraction))][static_cast<int>(m_particle[i]->m_y / (m_height / m_fraction))]++;
		 }

		 m_application.display();

	 }
 }

int main()
{
	System s;
	s.run();

	return EXIT_SUCCESS;
}