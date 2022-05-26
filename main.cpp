#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>

#define SpeedAnt 1
#define SizeBar 4000
#define AmountAnt 30

typedef struct{
    int x;
    int id;
    int direction;
    bool state;
}Ant;

void MoveAnt(Ant *ant){
    ant->x+=ant->direction*SpeedAnt;
}
bool compareAnts(Ant i1, Ant i2){
    return (i1.x<i2.x);
}

std::vector<Ant> createAnt(){
    std::vector<Ant> ants;
    srand(time(NULL));
    for(int i=0;i<AmountAnt;i++){
        Ant ant;
        ant.x=rand()%SizeBar;
        int d=rand()%2;
        if(d==0)d=-1;
        ant.direction=d;
        ant.state=1;
        ants.push_back(ant);
    }
    sort(ants.begin(),ants.end(),compareAnts);
    for(int i=0;i<AmountAnt;i++){
        ants[i].id=i;
    }
    return ants;
}

std::vector<Ant> frame(std::vector<Ant> ants){
    for(int i=0;i<ants.size();i++){
        int d=ants[i].direction;
        int x=ants[i].x;
        if((i==0 && d==-1)||(i==ants.size()-1 && d==1)) continue;
        if(((abs(ants[i+d].x-x)==1) || (abs(ants[i+d].x-x)==0)) && ants[i+d].state){
            ants[i].direction=ants[i].direction*-1;
        }     
    }
    for(int i=0;i<ants.size();i++){
        printf("%d   %d   %d\n",ants[i].id,ants[i].x,ants[i].direction);
        if(ants[i].x<=0 || ants[i].x>SizeBar-1){
            ants[i].state=0;
            continue;
        }else MoveAnt(&ants[i]);
    }/*
    bool  ok=0;
    while(ok!=1){
        ok=1;
        for(int i=0;i<ants.size();i++){
            if(ants[i].x<=0 || ants[i].x>SizeBar-1){
                //ants.erase(ants.begin()+i);
                ok=0;
                break;
            }
        }
    }*/
    return ants;
}

int main()
{
    std::vector<Ant> antsV=createAnt();
    std::vector<sf::CircleShape> antsG;
    for(int i=0;i<AmountAnt;i++){
        sf::CircleShape ant(5);
        ant.setPosition(antsV[i].x+100,150);
        ant.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        antsG.push_back(ant);
    }
    sf::CircleShape ant(5);
    float position=100;
    ant.setPosition(position,250);
    ant.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

    sf::RenderWindow window(sf::VideoMode(1000, 400), "SFML works!");
    sf::RectangleShape bar(sf::Vector2f(800,50));
    sf::Font font;
    font.loadFromFile("arial.ttf");
    // Create a text
    sf::Text text("0.00",font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    bar.setFillColor(sf::Color::Green);
    sf::Clock Clock;
    sf::Time Time = Clock.getElapsedTime();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        bar.setPosition(100,175);
        window.draw(bar);
        sf::Time Time2 = Clock.getElapsedTime()-Time;
        
        window.draw(text);
        
        antsV=frame(antsV);
        bool stateGame=0;
        for(int i=0;i<AmountAnt;i++){
            antsG[i].setPosition(antsV[i].x/(SizeBar/800)+100,150);
            if(antsV[i].state && !stateGame) stateGame=1;
        }
        if(stateGame){
            text.setString(std::to_string(Time2.asSeconds()));
            position+=1/(SizeBar/800.0);
        }
        for(int i=0;i<AmountAnt;i++){
            window.draw(antsG[i]);
        }
        ant.setPosition(position,250);
        window.draw(ant);
        window.display();
    }

    return 0;
}