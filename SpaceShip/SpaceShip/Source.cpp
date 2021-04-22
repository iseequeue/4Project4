#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <random>

enum class Objects
{
    asteroid,
    bullet,
    player,
    explosion
};

class System
{
public:

    System(int width = sf::VideoMode::getDesktopMode().width, int height = sf::VideoMode::getDesktopMode().height)
        : m_width(width), m_height(height)
    {   }

    void run();

    const int m_width;
    const int m_height;
    const double deg_to_rad = 0.017453;

private:
    int amount = 15;
    int delta_phi = 3;
};


class Animation: public System
{
private:
    double m_frame;
    double m_speed;
    std::vector<sf::IntRect> m_frames;
public:
    sf::Sprite m_sprite;
    Animation() = default;

    Animation(sf::Texture& t, int x, int y, int w, int h, int count, double speed):
        m_frame(0), m_speed(speed)
    {
        for (int i = 0; i < count; i++)
            m_frames.push_back(sf::IntRect(x + i * w, y, w, h));

        m_sprite.setTexture(t);
        m_sprite.setOrigin(w / 2, h / 2);
        m_sprite.setTextureRect(m_frames[0]);
    }

    Animation& operator =(const Animation& other)
    {
        m_frame = other.m_frame;
        m_speed = other.m_speed;
        m_sprite = other.m_sprite;
        m_frames = other.m_frames;

        return *this;
    }

    void update()
    {
        m_frame += m_speed;

        if (m_frame >= m_frames.size())
        {
            m_frame -= m_frames.size();
        }
        if (m_frames.size() > 0)
        {
            m_sprite.setTextureRect(m_frames[floor(m_frame)]);
        }
    }
public:
    bool isEnd() const
    {
        return (m_frame + m_speed >= m_frames.size());
    }

};


class Entity: public System
{
public:
    Animation m_anim;
    
    double m_dx;
    double m_dy;
    double m_r;
    double m_angle;
    bool m_life; 
    Objects m_name;
    double m_x;
    double m_y;
    const double frict1 = 0.2;
    const double frict2 = 0.99;

private:



public:

    Entity()
    {
        m_life = true;
    }

    Entity(Animation& a, int x, int y, double angle = 0.0, int radius = 1.0) :
        m_anim(a), m_x(x), m_y(y), m_angle(angle), m_r(radius)
    {  }

    void settings(Animation& a, int x, int y, double angle = 0.0, int radius = 1.0) 
    {
        m_anim = a;
        m_x = x; 
        m_y = y;
        m_angle = angle;
        m_r = radius;
    }

    virtual void update() {};

    void draw(sf::RenderWindow& app)
    {
        m_anim.m_sprite.setPosition(m_x, m_y);
        m_anim.m_sprite.setRotation(m_angle + 90);
        app.draw(m_anim.m_sprite);
    }

    virtual ~Entity() = default;
};


class Asteroid : public Entity
{
public:
    Asteroid()
    { 
        std::random_device rd;
        std::mt19937 mersenne(rd());

        std::uniform_int_distribution<int> uid(-4, 4);
        m_dx = uid(mersenne);
        m_dy = uid(mersenne);
        m_name = Objects::asteroid;
    }

    Asteroid(Animation& a, int x, int y, double angle = 0.0, int radius = 1.0) :
        Entity(a, x, y, angle, radius)
    {
        m_name = Objects::asteroid;
        std::random_device rd;
        std::mt19937 mersenne(rd());

        std::uniform_int_distribution<int> uid(-4, 4);
        m_dx = uid(mersenne);
        m_dy = uid(mersenne);
        m_name = Objects::asteroid;
    }

private:
    virtual void update() override
    {
        m_x += m_dx;
        m_y += m_dy;

        if (m_x > m_width) m_x = 0; 
        if (m_x < 0) m_x = m_width;
        
        if (m_y > m_height) m_y = 0; 
        if (m_y < 0) m_y = m_height;
    }

};


class Bullet : public Entity
{
public:
    Bullet()
    {
        m_name = Objects::bullet;
    }
    
    Bullet(Animation& a, int x, int y, double angle = 0.0, int radius = 1.0) :
        Entity(a, x, y, angle, radius)
    {
        m_name = Objects::bullet;
    }
private:
    virtual void  update() override
    {
        m_dx = std::cos(m_angle * deg_to_rad)*bullet_velocity;
        m_dy = std::sin(m_angle * deg_to_rad)* bullet_velocity;
       
        m_x += m_dx;
        m_y += m_dy;

        if (m_x > m_width || m_x < 0.0 || m_y > m_height || m_y < 0.0) 
            m_life = false;
    }
private:
    int bullet_velocity = 6;

};


class Player : public Entity
{
public:
    const int maxSpeed = 15;
    bool thrust;
    int lives;
    int score;

    Player()
    {
        lives = 9;
        score = 0;
        m_name = Objects::player;
    }

    Player(Animation& a, int x, int y, double angle = 0.0, int radius = 1.0):
        Entity(a, x, y, angle, radius)
    {
        lives = 9;
        score = 0;
        m_name = Objects::player;
    }

    const bool is_alive() { return (lives > 0); }

    void score_increase()
    {
        score++;
    }

    void live_decrease()
    {
        lives--;
    }

private:
    virtual void update() override 
    {
        if (thrust)
        {
            m_dx += std::cos(m_angle * deg_to_rad) * frict1;
            m_dy += std::sin(m_angle * deg_to_rad) * frict1;
        }
        else
        {
            m_dx *= frict2;
            m_dy *= frict2;
        }

        double speed = std::sqrt(m_dx * m_dx + m_dy * m_dy);
        if (speed > maxSpeed)
        {
            m_dx *= maxSpeed / speed;
            m_dy *= maxSpeed / speed;
        }

        m_x += m_dx;
        m_y += m_dy;

        if (m_x > m_width) 
            m_x = 0.0; 
        if (m_x < 0.0)
            m_x = m_width;

        if (m_y > m_height)
            m_y = 0.0;
        if (m_y < 0.0)
            m_y = m_height;
    }

};


bool isCollide(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    return (b->m_x - a->m_x) * (b->m_x - a->m_x) +
        (b->m_y - a->m_y) * (b->m_y - a->m_y) <
        (a->m_r + b->m_r) * (a->m_r + b->m_r);
}

void System::run()
{
    sf::Font font;

    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "error..." << std::endl;
    }

    sf::Text text;
    text.setFont(font); 
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red); 
    text.setPosition(50, 50);
    text.setRotation(2);

    sf::RenderWindow app(sf::VideoMode(m_width, m_height), "MyAsteroids");
    app.setFramerateLimit(60);

    sf::Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    sf::Sprite background(t2);

    Animation sPlayer        (t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go     (t1, 40, 40, 40, 40, 1, 0);
    Animation sExplosion     (t3, 0, 0, 256, 256, 48, 0.5);
    Animation sRock          (t4, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet        (t5, 0, 0, 32, 64, 16, 0.8);
    Animation sRock_small    (t6, 0, 0, 64, 64, 16, 0.2);
    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);


    std::list<std::shared_ptr<Entity>> entities; 

    for (int i = 0; i < amount; i++)
    {
        auto ptr_a = std::make_shared<Asteroid>(sRock, rand() % m_width, rand() % m_height, rand() % 360, 25);
        entities.push_back(ptr_a);
    }

    auto ptr_p = std::make_shared<Player>(sPlayer, 200, 200, 0, 20);
    entities.push_back(ptr_p);

    

    // main loop
    while (app.isOpen() && ptr_p->is_alive())
    {
        text.setString("Score: " + std::to_string(ptr_p->score) + "\nLives: " + std::to_string(ptr_p->lives));

        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Space)
                {
                    auto ptr_b = std::make_shared<Bullet>(sBullet, ptr_p->m_x, ptr_p->m_y, ptr_p->m_angle, 10);
                    entities.push_back(ptr_b);
                }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ptr_p->m_angle += delta_phi;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  ptr_p->m_angle -= delta_phi;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    ptr_p->thrust = true;
        else ptr_p->thrust = false;


        for (auto a : entities)
            for (auto b : entities)
            {
                if (a->m_name == Objects::asteroid && b->m_name == Objects::bullet)
                    if (isCollide(a, b))
                    {
                        a->m_life = false;
                        b->m_life = false;

                        auto ptr_e = std::make_shared<Entity>(sExplosion, a->m_x, a->m_y);
                        ptr_e->m_name = Objects::explosion;
                        entities.push_back(ptr_e);


                        for (int i = 0; i < 2; i++)
                        {
                            if (a->m_r == 15) 
                                continue;

                            auto ptr_e = std::make_shared<Asteroid>(sRock_small, a->m_x, a->m_y, rand() % 360, 15);
                            entities.push_back(ptr_e);
                        }

                        ptr_p->score_increase();

                    }

                if (a->m_name == Objects::player && b->m_name == Objects::asteroid)
                    if (isCollide(a, b))
                    {
                        b->m_life = false;

                        auto ptr_e = std::make_shared<Entity>(sExplosion_ship, a->m_x, a->m_y);

                        ptr_e->m_name = Objects::explosion;
                        entities.push_back(ptr_e);

                        ptr_p->settings(sPlayer, m_width / 2, m_height / 2, 0, 20);

                        ptr_p->m_dx = 0; 

                        ptr_p->m_dy = 0;

                        ptr_p->live_decrease();
                    }
            }


        if (ptr_p->thrust)  
            ptr_p->m_anim = sPlayer_go;
        else   
            ptr_p->m_anim = sPlayer;


        for (auto e : entities)
            if (e->m_name == Objects::explosion)
                if (e->m_anim.isEnd()) e->m_life = false;

        if (rand() % 150 == 0) // new generation
        {
            auto ptr_a = std::make_shared<Asteroid>(sRock, 0, rand() % m_height, rand() % 360, 25);
            entities.push_back(ptr_a);
        }

        for (auto i = entities.begin(); i != entities.end();)
        {
            std::shared_ptr<Entity> e(*i);

            e->update();

            e->m_anim.update();

            if (e->m_life == false)
                i = entities.erase(i); 
            else i++;
        }

        //draw
        app.draw(background);
        for (auto i : entities) i->draw(app);
        app.draw(text);
        app.display();
    }
}

int main()
{

    System system;
    system.run();
    

    return EXIT_SUCCESS;
}