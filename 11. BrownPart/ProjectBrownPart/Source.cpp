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

int main()
{
	const int N = 31;
	const int f = 4; // field f*f

	const auto width = VideoMode::getDesktopMode().width;
	const auto height = VideoMode::getDesktopMode().height;


	RenderWindow application(VideoMode(width, height), "Particles");

	std::vector <std::shared_ptr<Particle>> particle;
	std::vector <std::shared_ptr<CircleShape>> circle;

	std::vector <std::vector<int>> field(f, std::vector<int>(f,0));



	particle.reserve(N);
	circle.reserve(N);

	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_real_distribution<float> uidx(0,width);
	std::uniform_real_distribution<float> uidy(0, height);

	std::uniform_real_distribution<float> uidv(-4.0f/10,4.0f/10);

	particle.push_back(std::make_shared<Particle>(width / 2, height / 2, 0.1f, 0.1f, 6.0f, 36.0f));
	circle.push_back(std::make_shared<CircleShape>(particle[0]->m_radius));
	circle[0]->setFillColor(Color::Magenta);


	for (auto i = 1U; i < N; i++)
	{
		particle.push_back(std::make_shared<Particle>(uidx(mersenne), uidy(mersenne), uidv(mersenne), uidv(mersenne), 1.0f, 6.0f));
		circle.push_back(std::make_shared<CircleShape>(particle[i]->m_radius));
		circle[i]->setFillColor(Color::Blue);
	}

	std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();

	const std::chrono::microseconds delay(50000);

	std::chrono::microseconds timer(0);

	double dx = 0.0005;
	while (application.isOpen())
	{
		for (auto i = 0u; i < f; i++)
		{
			for (auto j = 0u; j < f; j++)
			{
				field[i][j] = 0;
			}
		}

		timer += std::chrono::duration_cast <std::chrono::microseconds> (std::chrono::steady_clock::now() - time_point);

		time_point = std::chrono::steady_clock::now();

		Event event;

		while (application.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				application.close();
			}
		}

		;


		application.clear(Color::Black);

		for (auto i = 0U; i< particle.size(); i++)
		{
			for (auto j = i; j < particle.size(); j++)
			{
				if (i!=j)
					isCollide(particle[i], particle[j]);

			}
		}
		for (auto i = 0U; i<particle.size(); i++)
		{			
			circle[i]->setPosition(particle[i]->m_x - particle[i]->m_radius, particle[i]->m_y - particle[i]->m_radius);
			application.draw(*circle[i]);

			particle[i]->m_x += particle[i]->m_dx;
			particle[i]->m_y += particle[i]->m_dy;

			if (particle[i]->m_x + particle[i]->m_radius > width || particle[i]->m_x - particle[i]->m_radius < 0)
				particle[i]->m_dx = -particle[i]->m_dx;

			if (particle[i]->m_y + particle[i]->m_radius > height || particle[i]->m_y - particle[i]->m_radius < 0)
				particle[i]->m_dy = -particle[i]->m_dy;

			field[std::floor(particle[i]->m_x)/(width/f) ][std::floor(particle[i]->m_y) / (width / f)]++;
		}



		

		application.display();
	}

	system("pause");

	return EXIT_SUCCESS;
}