//#include <SFML/Graphics.hpp>
//#include <ctime> // ctime
//#include <iostream>
//#include <list>
//#include <random> // лучше в алфавитном порядке
//using namespace sf; // это надо убрать
//
//// надо свое пр-во имен
//// надо разбиение на файлы
//// во всем коде надо проверить форматирование и code style
//// во всем коде надо проверить магические числа и сделать константы
//
//// глобальные константы остались
//auto W = VideoMode::getDesktopMode().width; // const
//auto H = VideoMode::getDesktopMode().height; // const
//
//float DEGTORAD = 0.017453f; // имя константы как имя макроса выглядит
//
//int modified_rand() { // эта функция не нужна, надо на месте
//    std::default_random_engine dre;
//    dre.seed(time(0));
//    std::uniform_int_distribution<int> id(0, RAND_MAX); // не надо так, надо на месте создавать и указывать нужное распределение
//    return (id(dre));
//}
//
//class Animation
//{
//private:
//    float Frame, speed; // имя с ББ, также лучше начинать с m_
//    std::vector<IntRect> frames; // нет include <vector>, остальные тоже надо проверить
//public:
//    Sprite sprite; // public?
//    Animation() {} // мы пишем = default, но он вообще нужен?
//
//    Animation(Texture& t, int x, int y, int w, int h, int count, float Speed)
//    {// списки инициализации?
//        Frame = 0;
//        speed = Speed;
//
//        for (int i = 0; i < count; i++)
//            frames.push_back(IntRect(x + i * w, y, w, h));
//
//        sprite.setTexture(t);
//        sprite.setOrigin(w / 2, h / 2);
//        sprite.setTextureRect(frames[0]);
//    }
//
//    void update()
//    {
//        Frame += speed;
//        int n = frames.size(); // auto n = ...
//        if (Frame >= n) Frame -= n; // форматирование, перенос строк
//        if (n > 0) sprite.setTextureRect(frames[int(Frame)]);// форматирование, перенос строк + приведение плохое
//    }
//public:
//    bool isEnd() // должна быть константной и возвращать константу
//    {
//        return Frame + speed >= frames.size();
//    }
//
//};
//
//
//class Entity
//{
//public:
//    Animation anim; // все публичное, непорядок
//    float x, y, dx, dy, R, angle; // R с ББ
//    bool life; // m_ везде
//    std::string name;
//
//    Entity() // списки инициализации?
//    {
//        life = 1;
//    }
//
//    // Эта функция делает работу конструктора, надо сделать конструктор
//    void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1) // для float 0.0f
//    {
//        anim = a;
//        x = X; y = Y;
//        angle = Angle;
//        R = radius;
//    }
//
//    // можно применить идиому NVI, или шаблонный метод для гибкости
//    virtual void update() {}; // = default
//
//    void draw(RenderWindow& app)
//    {
//        anim.sprite.setPosition(x, y);
//        anim.sprite.setRotation(angle + 90);
//        app.draw(anim.sprite);
//
//        CircleShape circle(R); // что за круг?
//        circle.setFillColor(Color(255, 0, 0, 170));
//        circle.setPosition(x, y);
//        circle.setOrigin(R, R);
//        //app.draw(circle);
//    }
//
//    virtual ~Entity() {}; // = default
//};
//
//
//class asteroid : public Entity // имя класса с ББ
//{
//public:
//    asteroid() // вот тут надо не остаток от деления, а нормально задать распределение от -4 до 4
//    { // далее надо рассмотреть вызов к-ра базового класса отсюда с передачей ему данных
//        dx = rand() % 8 - 4; // распределение на месте используем
//        dy = rand() % 8 - 4;
//        name = "asteroid"; // плохо такое имя, надо константу перечисления использовать
//    }
//private:
//    void update() // override?
//    {
//        x += dx;
//        y += dy;
//
//        if (x > W) x = 0;  if (x < 0) x = W;
//        if (y > H) y = 0;  if (y < 0) y = H;
//    }
//
//};
//
//
//class bullet : public Entity // имя класса с ББ
//{
//public:
//    bullet() // списки инициализации, вызов к-ра базового класса?
//    {
//        name = "bullet"; // плохо такое имя, надо константу перечисления использовать
//    }
//private:
//    void  update() // override?
//    {
//        dx = cos(angle * DEGTORAD) * 6; // std:: ...
//        dy = sin(angle * DEGTORAD) * 6; // std:: ...
//        // angle+=rand()%7-3;  /*try this*/
//        x += dx;
//        y += dy;
//
//        if (x > W || x<0 || y>H || y < 0) life = 0;
//    }
//
//};
//
//
//class player : public Entity // имя класса с ББ
//{
//public:
//    bool thrust; // публичные данные
//    int lives;
//    int score;
//
//    player() // списки инициализации, вызов к - ра базового класса ?
//    {
//        lives = 9;
//        score = 0;
//        name = "player"; // плохо такое имя, надо константу перечисления использовать
//    }
//
//    bool alive() { return (lives > 0); } // лучше is_alive, и она должна быть константной 
//
//    // разное форматирование фигурных скобок
//    void score_increase() {
//        score++;
//    }
//
//private:
//    void update() // override ?
//    {
//        if (thrust)
//        {
//            dx += cos(angle * DEGTORAD) * 0.2; // std:: ...
//            dy += sin(angle * DEGTORAD) * 0.2; // std:: ...
//        }
//        else
//        {
//            dx *= 0.99; // магичсекие числа
//            dy *= 0.99;
//        }
//
//        int maxSpeed = 15; // константа класса, а не так
//        float speed = sqrt(dx * dx + dy * dy); // std:: ...
//        if (speed > maxSpeed)
//        {
//            dx *= maxSpeed / speed;
//            dy *= maxSpeed / speed;
//        }
//
//        x += dx;
//        y += dy;
//
//        if (x > W) x = 0; if (x < 0) x = W;
//        if (y > H) y = 0; if (y < 0) y = H;
//    }
//
//};
//
//
//bool isCollide(Entity* a, Entity* b) // обычные указатели
//{
//    return (b->x - a->x) * (b->x - a->x) +
//        (b->y - a->y) * (b->y - a->y) <
//        (a->R + b->R) * (a->R + b->R);
//}
//
//
//int main() // в main очень много кода, а должно быть условно только создание эуземпляра класса Game а потом вызов run()
//{
//    srand(time(0)); // не нужно
//
//    Font font; // +
//    if (!font.loadFromFile("Font/ITCBLKAD.ttf")) // +
//    {
//        std::cout << "error..." << std::endl; // std::cerr
//    }
//
//    Text text; // +
//    text.setFont(font); // + 
//    text.setCharacterSize(24); // +
//    text.setFillColor(sf::Color::Red); // +
//    // а координаты? 0-0 по умолчанию?
//
//    RenderWindow app(VideoMode(W, H), "Asteroids!");
//    app.setFramerateLimit(60);
//
//    Texture t1, t2, t3, t4, t5, t6, t7;
//    t1.loadFromFile("images/spaceship.png");
//    t2.loadFromFile("images/background.jpg");
//    t3.loadFromFile("images/explosions/type_C.png");
//    t4.loadFromFile("images/rock.png");
//    t5.loadFromFile("images/fire_blue.png");
//    t6.loadFromFile("images/rock_small.png");
//    t7.loadFromFile("images/explosions/type_B.png");
//
//    t1.setSmooth(true);
//    t2.setSmooth(true);
//
//    Sprite background(t2);
//
//    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
//    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
//    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
//    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
//    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
//    Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
//    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);
//
//
//    std::list<Entity*> entities; // обычные указатели, простая стрктура данных
//
//    // так понимаю, код ниже не модернизировался, не буду его комментировать, все на тотальное переписывание
//
//    for (int i = 0; i < 15; i++)
//    {
//        asteroid* a = new asteroid();
//        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
//        entities.push_back(a);
//    }
//
//    player* p = new player();
//    p->settings(sPlayer, 200, 200, 0, 20);
//    entities.push_back(p);
//
//    text.setString("score: " + std::to_string(p->score) + "\nLifes: " + std::to_string(p->lives));
//
//
//    /////main loop/////
//    while (app.isOpen() && p->alive())
//    {
//        Event event;
//        while (app.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//                app.close();
//
//            if (event.type == Event::KeyPressed)
//                if (event.key.code == Keyboard::Space)
//                {
//                    bullet* b = new bullet();
//                    b->settings(sBullet, p->x, p->y, p->angle, 10);
//                    entities.push_back(b);
//                }
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle += 3;
//        if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle -= 3;
//        if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust = true;
//        else p->thrust = false;
//
//
//        for (auto a : entities)
//            for (auto b : entities)
//            {
//                if (a->name == "asteroid" && b->name == "bullet")
//                    if (isCollide(a, b))
//                    {
//                        a->life = false;
//                        b->life = false;
//
//                        Entity* e = new Entity();
//                        e->settings(sExplosion, a->x, a->y);
//                        e->name = "explosion";
//                        entities.push_back(e);
//
//
//                        for (int i = 0; i < 2; i++)
//                        {
//                            if (a->R == 15) continue;
//                            Entity* e = new asteroid();
//                            e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
//                            entities.push_back(e);
//                        }
//
//                        p->score_increase();
//
//                    }
//
//                if (a->name == "player" && b->name == "asteroid")
//                    if (isCollide(a, b))
//                    {
//                        b->life = false;
//
//                        Entity* e = new Entity();
//                        e->settings(sExplosion_ship, a->x, a->y);
//                        e->name = "explosion";
//                        entities.push_back(e);
//
//                        p->settings(sPlayer, W / 2, H / 2, 0, 20);
//                        p->dx = 0; p->dy = 0;
//                        p->lives--;
//                    }
//            }
//
//
//        if (p->thrust)  p->anim = sPlayer_go;
//        else   p->anim = sPlayer;
//
//
//        for (auto e : entities)
//            if (e->name == "explosion")
//                if (e->anim.isEnd()) e->life = 0;
//
//        if (rand() % 150 == 0)
//        {
//            asteroid* a = new asteroid();
//            a->settings(sRock, 0, rand() % H, rand() % 360, 25);
//            entities.push_back(a);
//        }
//
//        for (auto i = entities.begin(); i != entities.end();)
//        {
//            Entity* e = *i;
//
//            e->update();
//            e->anim.update();
//
//            if (e->life == false) { i = entities.erase(i); delete e; }
//            else i++;
//        }
//
//        //////draw//////
//        app.draw(background);
//        for (auto i : entities) i->draw(app);
//        app.display();
//    }
//
//    return 0;
//}