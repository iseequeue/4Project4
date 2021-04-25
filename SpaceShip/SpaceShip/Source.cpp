#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <random>



namespace asteroids
{
    enum class Objects
    {
        asteroid,
        bullet,
        player,
        explosion
    };



    class Constants
    {
    public:

        explicit Constants(int width = sf::VideoMode::getDesktopMode().width, int height = sf::VideoMode::getDesktopMode().height,
            int am = 15, int del = 3, int br = 25, int sr = 15)
            : m_width(width), m_height(height), amount(am), delta_phi(del), big_rad(br), small_rad(sr)
        {   }

        const int m_width;
        const int m_height;

        const int big_rad;
        const int small_rad;

        static constexpr float deg_to_rad = 0.017453f;
        static const int myRand = 150;

        const int amount;
        const int delta_phi;
    };

    class Animation
    {
    public:

        explicit Animation(sf::Texture& t, int x, int y, int w, int h, int count, float speed) :
            m_frame(0), m_speed(speed)
        {
            for (int i = 0; i < count; i++)
            {
                m_frames.push_back(sf::IntRect(x + i * w, y, w, h));
            }

            m_sprite.setTexture(t);
            m_sprite.setOrigin(w / 2.0f, h / 2.0f);
            m_sprite.setTextureRect(m_frames[0]);
        }

        Animation& operator =(const Animation& other) = default;
      

        void update()
        {
            m_frame += m_speed;

            if (m_frame >= m_frames.size())
            {
                m_frame -= m_frames.size();
            }
            if (m_frames.size() > 0)
            {
                m_sprite.setTextureRect(m_frames[static_cast<int>(m_frame)]);
            }
        }
    public:
        bool isEnd() const
        {
            return (m_frame + m_speed >= m_frames.size());
        }

        sf::Sprite m_sprite;
    private:
        float m_frame;
        float m_speed;
        std::vector<sf::IntRect> m_frames;

    };


    class Entity : public Constants
    {
    public:
        explicit Entity(Objects o, Animation& a, float x, float y, float angle = 0.0, float radius = 1.0) :
            m_anim(a), m_x(x), m_y(y), m_angle(angle), m_r(radius), m_type(o), m_dx(0), m_dy(0)
        {  }

        virtual void update() {};

        void draw(sf::RenderWindow& app)
        {
            m_anim.m_sprite.setPosition(m_x, m_y);
            m_anim.m_sprite.setRotation(m_angle + 90);
            app.draw(m_anim.m_sprite);
        }

    public:
        Animation m_anim;

        float m_dx;
        float m_dy;
        float m_r;
        float m_angle;
        bool m_life;
        Objects m_type;
        float m_x;
        float m_y;
        static constexpr float spaceship_accelerate = 0.2f;
        static constexpr float spaceship_brake = 0.99f;
    };


    class Asteroid : public Entity
    {
    public:
        explicit Asteroid(std::mt19937 mersenne, std::uniform_real_distribution<float> uid, 
            Animation& a, float x, float y, float angle = 0.0, float radius = 1.0) :
            Entity(Objects::asteroid, a, x, y, angle, radius)
        {
            m_dx = uid(mersenne);       //goes to based class
            m_dy = uid(mersenne);     
        }

    private:
        virtual void update()
        {
            m_x += m_dx;
            m_y += m_dy;

            if (m_x > m_width) m_x = 0;
            if (m_x < 0) m_x = m_width * 1.0f;

            if (m_y > m_height) m_y = 0;
            if (m_y < 0) m_y = m_height * 1.0f;
        }
    };


    class Bullet : public Entity
    {
    public:

        explicit Bullet(Animation& a, float x, float y, float angle = 0.0, float radius = 1.0) :
            Entity(Objects::bullet, a, x, y, angle, radius)
        {   }

    private:
        virtual void  update()
        {
            m_dx = std::cos(m_angle * deg_to_rad) * bullet_velocity;
            m_dy = std::sin(m_angle * deg_to_rad) * bullet_velocity;

            m_x += m_dx;
            m_y += m_dy;

            if (m_x > m_width || m_x < 0.0 || m_y > m_height || m_y < 0.0)
            {
                m_life = false;
            }
        }
    private:
        const int bullet_velocity = 6;

    };


    class Player : public Entity
    {
    public:
       
        explicit Player(Animation& a, float x, float y, float angle = 0.0, float radius = 1.0f) :
            Entity(Objects::player, a, x, y, angle, radius), lives(9), score(0), thrust(true)
        {   }

        bool is_alive() { return (lives > 0); }

        void score_increase()
        {
            score++;
        }

        void live_decrease()
        {
            lives--;
        }

        const int maxSpeed = 15;
        bool thrust;
        int lives;
        int score;

    private:
        virtual void update()
        {
            if (thrust)
            {
                m_dx += std::cos(m_angle * deg_to_rad) * spaceship_accelerate;
                m_dy += std::sin(m_angle * deg_to_rad) * spaceship_accelerate;
            }
            else
            {
                m_dx *= spaceship_brake;
                m_dy *= spaceship_brake;
            }

            float speed = std::sqrt(m_dx * m_dx + m_dy * m_dy);
            if (speed > maxSpeed)
            {
                m_dx *= maxSpeed / speed;
                m_dy *= maxSpeed / speed;
            }

            m_x += m_dx;
            m_y += m_dy;

            if (m_x > m_width)
            {
                m_x = 0.0;
            }
            if (m_x < 0.0)
            {
                m_x = m_width * 1.0f;
            }

            if (m_y > m_height)
            {
                m_y = 0.0;
            }
            if (m_y < 0.0)
            {
                m_y = m_height * 1.0f;
            }
        }

    };


    bool isCollide(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        return (b->m_x - a->m_x) * (b->m_x - a->m_x) + (b->m_y - a->m_y) * (b->m_y - a->m_y) <
            (a->m_r + b->m_r) * (a->m_r + b->m_r);
    }

    class System : public Constants
    {
    public:

        explicit System():
            sPlayer        (t1, 40, 0, 40, 40, 1, 0), 
            sPlayer_go     (t1, 40, 40, 40, 40, 1, 0), 
            sExplosion     (t3, 0, 0, 256, 256, 48, 0.5f),
            sRock          (t4, 0, 0, 64, 64, 16, 0.2f),
            sBullet        (t5, 0, 0, 32, 64, 16, 0.8f),
            sRock_small    (t6, 0, 0, 64, 64, 16, 0.2f),
            sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5f),

            app(sf::VideoMode(m_width, m_height), "MyAsteroids"),
            ptr_p(std::make_shared<Player>(sPlayer, 200, 200, 0, 20)),
            mersenne(rd()),
            uid0(-4.0f, 4.0f),
            uid1(0, m_width),
            uid2(0, m_height),
            uid3(0, 360)


        {  
            t1.loadFromFile("images/spaceship.png");
            t2.loadFromFile("images/background.jpg");
            t3.loadFromFile("images/explosions/type_C.png");
            t4.loadFromFile("images/rock.png");
            t5.loadFromFile("images/fire_blue.png");
            t6.loadFromFile("images/rock_small.png");
            t7.loadFromFile("images/explosions/type_B.png");

            if (!font.loadFromFile("arial.ttf"))
            {
                std::cerr << "error..." << std::endl;
            }

            text.setFont(font);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::Red);
            text.setPosition(50, 50);

            app.setFramerateLimit(60);

            t1.setSmooth(true);
            t2.setSmooth(true);

            for (int i = 0; i < amount; i++)
            {
                entities.push_back(std::make_shared<Asteroid>(mersenne, uid0, sRock, uid1(mersenne), uid2(mersenne), uid3(mersenne), big_rad));
            }
            entities.push_back(ptr_p);
        }

        void run();

        void vsAst_Bul(std::shared_ptr<Entity> a, std::shared_ptr<Entity>);

        void vsPl_Ast(std::shared_ptr<Entity> a, std::shared_ptr<Entity>);

        void global_update();

        Animation sPlayer, sPlayer_go, sExplosion, sRock, sBullet, sRock_small, sExplosion_ship;
        sf::Texture t1, t2, t3, t4, t5, t6, t7;
        sf::Font font;
        sf::Text text;
        sf::RenderWindow app;

        std::list<std::shared_ptr<Entity>> entities;
        std::shared_ptr<Player> ptr_p;

        std::random_device rd;
        std::mt19937 mersenne;
        std::uniform_real_distribution<float> uid0;
        std::uniform_int_distribution<int> uid1;
        std::uniform_int_distribution<int> uid2;
        std::uniform_int_distribution<int> uid3;

       
    };

    void System::vsAst_Bul(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        if (isCollide(a, b))
        {
            a->m_life = false;
            b->m_life = false;

            entities.push_back(std::make_shared<Entity>(Objects::explosion, sExplosion, a->m_x, a->m_y));


            for (int i = 0; i < 2; i++)
            {
                if (a->m_r == small_rad)
                {
                    continue;
                }

                entities.push_back(std::make_shared<Asteroid>(mersenne, uid0, sRock_small, a->m_x, a->m_y, uid3(mersenne), small_rad));
            }

            ptr_p->score_increase();

        }
    }

    void System::vsPl_Ast(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
    {
        if (isCollide(a, b))
        {
            b->m_life = false;

            entities.push_back(std::make_shared<Entity>(Objects::explosion, sExplosion, a->m_x, a->m_y));

            ptr_p->m_anim = sPlayer;
            ptr_p->m_x = uid1(mersenne);
            ptr_p->m_x = uid2(mersenne);
            ptr_p->m_angle = uid3(mersenne);

            ptr_p->m_dx = 0;
            ptr_p->m_dy = 0;
            ptr_p->live_decrease();
        }
    }

    void System::global_update()
    {
        if (ptr_p->thrust)             // player movement
        {
            ptr_p->m_anim = sPlayer_go;
        }
        else
        {
            ptr_p->m_anim = sPlayer;
        }

        for (auto e : entities)          // explosions
        {
            if (e->m_type == Objects::explosion)
            {
                if (e->m_anim.isEnd()) e->m_life = false;
            }
        }

        if (uid3(mersenne) % myRand == 0) // new asteroid generation
        {

            entities.push_back(std::make_shared<Asteroid>(mersenne, uid0, sRock, 0, uid2(mersenne), uid3(mersenne), big_rad));
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
    }



    void System::run()
    {
       sf::Sprite background(t2);

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
                        entities.push_back(std::make_shared<Bullet>(sBullet, ptr_p->m_x, ptr_p->m_y, ptr_p->m_angle, 10));
                    }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ptr_p->m_angle += delta_phi;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  ptr_p->m_angle -= delta_phi;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    ptr_p->thrust = true;
            else ptr_p->thrust = false;


            for (auto a : entities)
                for (auto b : entities)
                {
                    if (a->m_type == Objects::asteroid && b->m_type == Objects::bullet)
                    {
                        vsAst_Bul(a, b);
                    }
                       
                    if (a->m_type == Objects::player && b->m_type == Objects::asteroid)
                    {
                        vsPl_Ast(a, b);
                    }
                }

            global_update();       

            //draw
            app.draw(background);
            for (auto i : entities) i->draw(app);
            app.draw(text);
            app.display();
        }
    }
}

int main()
{

    asteroids::System system;
    system.run();
    

    return EXIT_SUCCESS;
}