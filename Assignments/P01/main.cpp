            ///////////////////////////////////////////////////////////////////////////////
            //                   
            // Author:           Trevor Amann
            // Email:            trevor.amann9@gmail.com
            // Label:            P01
            // Title:            Game
            // Course:           CMPS 2143
            // Semester:         Spring 2021
            //
            // Description:
            //    The program is the start of our game. It is not fully functional yet but I do believe
            // I have made some good progress that I can move forward with.  
            //
            // Usage:
            //       Run the sfml-game after making the program and then use the up and down arrow keys to play. 
            //
            // Files:   main.cpp
            /////////////////////////////////////////////////////////////////////////////////



#include <SFML/Graphics.hpp>
#include <iostream>

//this part of my code is a bunch of definitions that make it easier to change variable values across 
//the whoel program. 
#define WINDOW_X 800
#define WINDOW_Y 600
#define OFFSET 0.5
#define DEBRIS_WIDTH_MIN 30
#define DEBRIS_WIDTH_MAX 60
#define DEBRIS_WIDTH_DELTA (DEBRIS_WIDTH_MAX - DEBRIS_WIDTH_MIN)
#define DEBRIS_HEIGHT_MIN 50
#define DEBRIS_HEIGHT_MAX 80
#define DEBRIS_HEIGHT_DELTA (DEBRIS_HEIGHT_MAX - DEBRIS_HEIGHT_MIN)
#define RADIUS 20 
#define STARTING_OFFSET 10
#define DEBRIS_OFFSET 0.05

//This is my player class that defines how the player will act. 
class Player: public sf::CircleShape {
    public:
        
        Player(){
            setRadius(RADIUS);
            setFillColor(sf::Color::Green);
            setPosition(0, WINDOW_Y/2.0);
        }
        Player(float r, const sf::Color &c, int x, int y){
            setRadius(r);
            setFillColor(c);
            setPosition(x,y);
        }
        void moveUp(){
            if(getPosition().y > 0){
                move(0.0, -OFFSET); 
            }
            
        }
        void moveDown(){
           if(getPosition().y < (WINDOW_Y - (int) 2*getRadius())){
               move(0.0, OFFSET);
           }
            
        }

        sf::FloatRect getBounds(){
            return this->getGlobalBounds();
        }
};

//this is my Debris class which defines how the debris acts and looks in the game. 
class Debris: public sf::RectangleShape {
    private:
        int width;
        int height;
        bool visible;

    public:
        
        Debris(){
            width = rand() % DEBRIS_WIDTH_DELTA + DEBRIS_WIDTH_MIN;
            height = rand() % DEBRIS_HEIGHT_DELTA + DEBRIS_HEIGHT_MIN;
            int y = rand() % WINDOW_Y;
            visible = true;
            setSize(sf::Vector2f(width, height)); 
            setFillColor(sf::Color::Yellow);
            setPosition(WINDOW_X + STARTING_OFFSET, y); 
        }
        Debris(int w, int h, const sf::Color &c, int x, int y){
            setSize(sf::Vector2f(w,h));
            setFillColor(c);
            setPosition(x,y);
            visible = true;
        }
        void moveLeft(){
            if(getPosition().x > -width){
                move(-DEBRIS_OFFSET, 0.0);
            }
            else{
                visible = false; 
            }
            
        }

        bool isVisible(){
            return visible;
        }

        sf::FloatRect getBounds(){
            return this->getGlobalBounds();
        }
            
        
};

//This is the score class that determines how the score is calculated when an event occurs. 
class Score{
    private:
        int score;
        
    public:
        Score(){
            score = 0;
        }
        Score& operator++(){
            score++;
            return *this;
        }
        Score operator++(int x){
            Score temp = *this;
            ++*this;
            return temp;
        }
        Score& operator--(){
            score--;
            return *this;
        }
        Score operator--(int x){
            Score temp = *this;
            --*this;
            return temp;
        }
        int getScore(){
            return score;
        }
        friend std::ostream& operator<<(std::ostream& os, const Score &s);

};

std::ostream& operator<<(std::ostream& os, const Score &s){
    return os << s.score;
}

//This is my game text class that I still have work to finish but am struggling to get the text to appear. 
class GameText: public sf::Text{
    private:
    
    public:
    GameText(){
        sf::Font font;
        font.loadFromFile("Keyboard.ttf");
        setString("");
        setFont(font);
        setFillColor(sf::Color::Red);
        setPosition(0,0);
    }
    GameText(const sf::String &string) {
        sf::Font font;
        font.loadFromFile("Keyboard.ttf");
        setString(string);
        setFont(font);
        setFillColor(sf::Color::Red);
        setPosition(0,0);
    }
    void setText(const sf::String &string){
        setString(string);
    }


};

//I used the intersection logic from the follwoing website.
//https://github.com/SFML/SFML/blob/master/include/SFML/Graphics/Rect.inl
bool collisionDetected(sf::FloatRect obj1, sf::FloatRect obj2){
    bool collision = false;
    float obj1left = obj1.left;
    float obj1top = obj1.top;
    float obj1bottom = obj1.top - obj1.height;
    float obj1right = obj1.left - obj1.width;
    float obj1minx = std::min(obj1left, obj1right);
    float obj1maxx = std::max(obj1left, obj1right);
    float obj1miny = std::min(obj1top, obj1bottom);
    float obj1maxy = std::max(obj1top, obj1bottom);

    float obj2left = obj2.left;
    float obj2top = obj2.top;
    float obj2bottom = obj2.top - obj2.height;
    float obj2right = obj2.left - obj2.width;
    float obj2minx = std::min(obj2left, obj2right);
    float obj2maxx = std::max(obj2left, obj2right);
    float obj2miny = std::min(obj2top, obj2bottom);
    float obj2maxy = std::max(obj2top, obj2bottom);

    float interleft = std::max(obj1minx, obj2minx);
    float intertop = std::max(obj1miny, obj2miny);
    float interright = std::min(obj1maxx, obj2maxx);
    float interbottom = std::min(obj1maxy, obj2maxy);

    std::cout << intertop << "," << interbottom << "," << interleft << "," << interright << std::endl;

    //if ((diff_top < obj1.height || diff_bot < obj1.height) && (diff_left < obj1.width || diff_right < obj1.width)) {
    //    collision = true;
    //}
    
    //if(obj1right > obj2left && obj1left < obj2right){
    //    if(obj1top < obj2bottom && obj1bottom > obj2top){
    //        collision = true;
    //    }
    //}

    if((interleft < interright) && (intertop < interbottom)){
        collision = true;
    }

    return collision;
}

//This is the main of our function which opens the sfml window and displays a player and debris. 
//I am currently working on how to get the text to work properly. Also in main we implement our
//code and define what the events are so we can make sure we call our classes and functions. 
int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Ball Game!");
    Player player1;
    Debris *debris1 = NULL; 
    bool collision = false;
    Score score1; 
    GameText gmetxt;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            player1.moveUp();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            player1.moveDown();
        }
        if(debris1 == NULL){
            debris1 = new Debris();
            collision = false; 
        }
        else{
            if(debris1->isVisible()){
                debris1->moveLeft(); 
                if(collisionDetected(player1.getBounds(),debris1->getBounds()) == true){
                    if(collision == false){ //this makes sure you only count the collision once
                        score1--;
                        collision = true;
                    }
                }
            }
            else{
                delete debris1; 
                if(collision == false){
                    score1++;
                }
                 
                debris1 = NULL;
            }
        }
        //gmetxt.setString(std::to_string(score1.getScore()));
        window.clear();
        window.draw(player1);
        //window.draw(gmetxt);
        if(debris1 != NULL)
            window.draw(*debris1);
        window.display();
        std::cout << score1 << std::endl; 

    }


    return 0;
}
