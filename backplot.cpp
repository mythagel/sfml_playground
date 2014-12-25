#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

struct vector_2 {
    double x = 0.0;
    double y = 0.0;

    vector_2() = default;
    vector_2(double x, double y)
     : x(x), y(y) {
    }
};
struct vector_3 {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    vector_3() = default;
    vector_3(double x, double y, double z)
     : x(x), y(y), z(z) {
    }
};


int main() {
    double fov = 120.0;
    double zNear = 0.1;
    double zFar = 100.0f;

    vector_3 eye{0,0,10};
    vector_3 center;
    vector_3 up{0,0,1};

    sf::Window window(sf::VideoMode(800, 600), "SFML Basic");
    window.setVerticalSyncEnabled(true);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.f);

    // Reshape
    {
        auto x = window.getSize().x;
        auto y = window.getSize().y;
        auto aspect = x/y;

        glViewport(0, 0, x, y);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fov, aspect, zNear, zFar);
        glMatrixMode(GL_MODELVIEW);
    }


    for(bool running = true; running; ) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::Resized: {
                    auto x = event.size.width;
                    auto y = event.size.height;
                    auto aspect = x/y;

                    glViewport(0, 0, x, y);
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    gluPerspective(fov, aspect, zNear, zFar);
                    glMatrixMode(GL_MODELVIEW);
                    break;
                }
                case sf::Event::KeyPressed: {
                    std::cout << "key: " << event.key.code << "\n";
                    std::cout << "control:" << event.key.control << "\n";
                    std::cout << "alt:" << event.key.alt << "\n";
                    //if (event.key.code == sf::Keyboard::Escape)
                    break;
                }
                case sf::Event::MouseWheelMoved: {
                    std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
                    std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
                    std::cout << "mouse y: " << event.mouseWheel.y << std::endl;
                    break;
                }
                case sf::Event::MouseButtonPressed: {
                    if (event.mouseButton.button == sf::Mouse::Right) {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    }
                    break;
                }
                case sf::Event::MouseMoved: {
                    std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                    std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                    break;
                }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);

        glTranslatef(1.5f, 0.0f, -7.0f);
        glLineWidth(10.0);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
            glVertex3f(0,0,-1);
            glVertex3f(10,0,-1);
            glVertex3f(10,10,-1);
            glVertex3f(0,10,-1);
        glEnd();

        glFlush();

        window.display();
    }

    return 0;
}
