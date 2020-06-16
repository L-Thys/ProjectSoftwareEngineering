//
// Created by lotte on 15.06.20.
//

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stack>
#include "Metronet.h"

void simulation();

int main()
{
    const char *input = "CorrectInput.xml";
    Metronet* metronet=readFromXml(input);

    // text
    sf::Font font;
    font.loadFromFile("../SFML/font.ttf");
    sf::Text text;
    std::string string = "0 min 0 sec\n";
    metronet->stringGraphicalASCII(string);
    text.setString(string);
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(55.f,55.f);

    // window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Metronet");

    // background
    sf::RectangleShape background(sf::Vector2f(1600.f, 900.f));
    background.setFillColor(sf::Color(89, 89, 89));

    // view rectangle
    sf::RectangleShape viewRectangle(sf::Vector2f(1100.f, 850.f));
    viewRectangle.setFillColor(sf::Color(100, 100, 100));
    viewRectangle.setPosition(25.f,25.f);

    // buttons
    sf::Vector2f buttonSize = sf::Vector2f(200, 55);
    int buttonTextSize = 40;
    sf::Color buttonColor = sf::Color::White;
    buttonColor.a = 89;

    sf::RectangleShape startButton(buttonSize);
    startButton.setFillColor(buttonColor);
    sf::Vector2f startButtonPosition = sf::Vector2f(1150.f,50.f);
    startButton.setPosition(startButtonPosition);
    sf::Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString("Start");
    startButtonText.setCharacterSize(buttonTextSize);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(startButtonPosition.x+5,startButtonPosition.y+2);

    sf::RectangleShape stopButton(buttonSize);
    stopButton.setFillColor(buttonColor);
    sf::Vector2f stopButtonPosition = sf::Vector2f(1375.f,50.f);
    stopButton.setPosition(stopButtonPosition);
    sf::Text stopButtonText;
    stopButtonText.setFont(font);
    stopButtonText.setString("Stop");
    stopButtonText.setCharacterSize(buttonTextSize);
    stopButtonText.setFillColor(sf::Color::White);
    stopButtonText.setPosition(stopButtonPosition.x+5,stopButtonPosition.y+2);

    sf::RectangleShape resetButton(buttonSize);
    resetButton.setFillColor(buttonColor);
    sf::Vector2f resetButtonPosition = sf::Vector2f(1250.f,130.f);
    resetButton.setPosition(resetButtonPosition);
    sf::Text resetButtonText;
    resetButtonText.setFont(font);
    resetButtonText.setString("Reset");
    resetButtonText.setCharacterSize(buttonTextSize);
    resetButtonText.setFillColor(sf::Color::White);
    resetButtonText.setPosition(resetButtonPosition.x+5,resetButtonPosition.y+2);

    sf::RectangleShape previousButton(buttonSize);
    previousButton.setFillColor(buttonColor);
    sf::Vector2f previousButtonPosition = sf::Vector2f(1150.f,210.f);
    previousButton.setPosition(previousButtonPosition);
    sf::Text previousButtontext;
    previousButtontext.setFont(font);
    previousButtontext.setString("Vorige");
    previousButtontext.setCharacterSize(buttonTextSize);
    previousButtontext.setFillColor(sf::Color::White);
    previousButtontext.setPosition(previousButtonPosition.x+5,previousButtonPosition.y+2);

    sf::RectangleShape nextButton(buttonSize);
    nextButton.setFillColor(buttonColor);
    sf::Vector2f nextButtonPosition = sf::Vector2f(1375.f,210.f);
    nextButton.setPosition(nextButtonPosition);
    sf::Text nextButtonText;
    nextButtonText.setFont(font);
    nextButtonText.setString("Volgende");
    nextButtonText.setCharacterSize(buttonTextSize);
    nextButtonText.setFillColor(sf::Color::White);
    nextButtonText.setPosition(nextButtonPosition.x+5,nextButtonPosition.y+2);

    sf::Time refresh = sf::milliseconds(1000/30);

    std::stack<std::string> previousStack;
    std::stack<std::string> nextStack;
    int secondsSinceStart=0;
    int minutesSinceStart=0;

    bool start = false;
    bool next = false;
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int x =  event.mouseButton.x;
                        int y = event.mouseButton.y;
                        if(x>startButtonPosition.x && x<startButtonPosition.x+buttonSize.x
                            && y>startButtonPosition.y && y< startButtonPosition.y+buttonSize.y){
                            start=true;
                        }else if(x>stopButtonPosition.x && x<stopButtonPosition.x+buttonSize.x
                            && y>stopButtonPosition.y && y< stopButtonPosition.y+buttonSize.y){
                            start=false;
                        }else if(x>previousButtonPosition.x && x<previousButtonPosition.x+buttonSize.x
                            && y>previousButtonPosition.y && y< previousButtonPosition.y+buttonSize.y){
                            start=false;
                            if(!previousStack.empty()){
                                nextStack.push(text.getString());
                                text.setString(previousStack.top());
                                previousStack.pop();
                            }

                        }else if(x>nextButtonPosition.x && x<nextButtonPosition.x+buttonSize.x
                            && y>nextButtonPosition.y && y< nextButtonPosition.y+buttonSize.y){
                            start = false;
                            next = true;
                        }else if(x>resetButtonPosition.x && x<resetButtonPosition.x+buttonSize.x
                            && y>resetButtonPosition.y && y< resetButtonPosition.y+buttonSize.y){
                            delete metronet;
                            metronet = readFromXml(input);
                            clock.restart();
                            secondsSinceStart = 0;
                            minutesSinceStart = 0;
                            nextStack.empty();
                            previousStack.empty();
                            string = "0 min 0 sec\n";
                            metronet->stringGraphicalASCII(string);
                            text.setString(string);
                        }
                    }
                default:
                    break;
            }
        }
        if(start||next){
            if(clock.getElapsedTime()>=refresh||next){
                previousStack.push(text.getString());
                if(nextStack.empty()){
                    metronet->driveAutomaticaly(1);
                    std::ostringstream convert;   // stream used for the conversion to string
                    convert << minutesSinceStart << " min " << secondsSinceStart << " sec \n";
                    string = convert.str();
                    metronet->stringGraphicalASCII(string);
                    if(secondsSinceStart==59){
                        minutesSinceStart++;
                        secondsSinceStart =0;
                    }else secondsSinceStart++;
                    std::vector<Tram*> trams = metronet->getTrams();
                    for ( unsigned int j = 0; j < trams.size() ; ++j) {
                        std::ostringstream tram;   // stream used for the conversion to string
                        tram.clear();
                        tram << "Tram " << trams[j]->getLijn() << ": " << trams[j]->getPassengers() << " passagiers en " << trams[j]->getOpbrengst() << " euro opbrengst\n";
                        string += tram.str();
                    }
                    text.setString(string);
                }else{

                    text.setString(nextStack.top());
                    nextStack.pop();
                }

                clock.restart();
            }
            if(next) next = false;

        }

        window.clear();
        window.draw(background);
        window.draw(viewRectangle);
        window.draw(text);
        window.draw(startButton);
        window.draw(startButtonText);
        window.draw(stopButton);
        window.draw(stopButtonText);
        window.draw(previousButton);
        window.draw(previousButtontext);
        window.draw(nextButton);
        window.draw(nextButtonText);
        window.draw(resetButton);
        window.draw(resetButtonText);

        window.display();
    }
    delete metronet;
    return 0;
}

void simulation(){
    std::string string;
//    for(int i = 0; i<20;i++){
//        string= i;
//        text.setString(string);
//        sf::sleep(sf::milliseconds(50));
//    }
//    text.setString("hi");
    std::cout<< "hi";
}