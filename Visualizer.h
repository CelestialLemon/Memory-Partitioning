#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Color.h"

float boxSize = 50.0f, boxSpacing = 6.0f;
const int numOfColors = 10;


Color* SetColors(Color* colors)
{
    colors[0] = Color(220, 20, 60); //crimson
    colors[1] = Color(255, 127, 80); //coral
    colors[2] = Color(255, 140, 0); //dark orange
    colors[3] = Color(255, 215, 0); //gold
    colors[4] = Color(124, 252, 0); //lawn green
    colors[5] = Color(135, 206, 235); //sky blue
    colors[6] = Color(46, 139, 87); //sea green
    colors[7] = Color(138, 43, 226); //blue violet
    colors[8] = Color(192, 0, 192); //purple
    colors[9] = Color(255, 20, 147); //deep pink

    return colors;

}



void Visualize(int numOfBoxes, int rowSize, int numOfPartitions, int* partitionSizes, int* partitionOccupied)
{
    
    sf::RenderWindow window(sf::VideoMode(960, 960), "SFML works!", sf::Style::Default);
    Color* colors = new Color[numOfColors];
    colors = SetColors(colors);
    srand(time(0));
    


    std::vector<sf::RectangleShape> rects(numOfBoxes);
    
    int boxesRendered = 0;
    for (int i = 0; i < numOfPartitions; i++)
    {
        Color randomColor = colors[rand() % numOfColors];
        Color randomColorDim = Color(randomColor.r / 2, randomColor.g / 2, randomColor.b / 2);

        int occupiedBoxesRemaining = partitionOccupied[i];
        for (int j = 0; j < partitionSizes[i]; j++)
        {
            float posX = boxSpacing + ((boxesRendered % rowSize) * (boxSize + boxSpacing));
            float posY = boxSpacing + ((boxesRendered / rowSize) * (boxSize + boxSpacing));
            rects[boxesRendered].setPosition(sf::Vector2f(posX, posY));
            rects[boxesRendered].setSize(sf::Vector2f(boxSize, boxSize));
            
            if (occupiedBoxesRemaining > 0)
            {
                
                rects[boxesRendered].setFillColor(sf::Color(randomColor.r, randomColor.g
                    , randomColor.b));
                occupiedBoxesRemaining--;
            }
            else
            {
                rects[boxesRendered].setFillColor(sf::Color(randomColorDim.r, randomColorDim.g
                    , randomColorDim.b));
            }

            boxesRendered++;
        }
    }

    printf("Total partitioned blocks : %d\n", boxesRendered);
    printf("Total un-partitioned blocks : %d\n", numOfBoxes - boxesRendered);

    while (boxesRendered < numOfBoxes)
    {
        float posX = boxSpacing + ((boxesRendered % rowSize) * (boxSize + boxSpacing));
        float posY = boxSpacing + ((boxesRendered / rowSize) * (boxSize + boxSpacing));
        rects[boxesRendered].setPosition(sf::Vector2f(posX, posY));
        rects[boxesRendered].setSize(sf::Vector2f(boxSize, boxSize));
        rects[boxesRendered].setFillColor(sf::Color(100, 100, 100));
        boxesRendered++;
    }

    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                printf("New window width : %d, new window height : %d\n", evnt.size.width, evnt.size.height);
                break;

            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }

        window.clear();
        for (int i = 0; i < numOfBoxes; i++)
        {
            window.draw(rects[i]);
        }
        window.display();

    }

}

//vector overloaded function
void Visualize(int numOfBoxes, int rowSize, int numOfPartitions, std::vector<int> partitionSizes, std::vector<int> partitionOccupied)
{

    sf::RenderWindow window(sf::VideoMode(960, 960), "SFML works!", sf::Style::Default);
    Color* colors = new Color[numOfColors];
    colors = SetColors(colors);
    srand(time(0));



    std::vector<sf::RectangleShape> rects(numOfBoxes);

    int boxesRendered = 0;
    for (int i = 0; i < numOfPartitions; i++)
    {
        Color randomColor = colors[rand() % numOfColors];
        Color randomColorDim = Color(randomColor.r / 2, randomColor.g / 2, randomColor.b / 2);

        int occupiedBoxesRemaining = partitionOccupied[i];
        for (int j = 0; j < partitionSizes[i]; j++)
        {
            float posX = boxSpacing + ((boxesRendered % rowSize) * (boxSize + boxSpacing));
            float posY = boxSpacing + ((boxesRendered / rowSize) * (boxSize + boxSpacing));
            rects[boxesRendered].setPosition(sf::Vector2f(posX, posY));
            rects[boxesRendered].setSize(sf::Vector2f(boxSize, boxSize));

            if (occupiedBoxesRemaining > 0)
            {

                rects[boxesRendered].setFillColor(sf::Color(randomColor.r, randomColor.g
                    , randomColor.b));
                occupiedBoxesRemaining--;
            }
            else
            {
                rects[boxesRendered].setFillColor(sf::Color(randomColorDim.r, randomColorDim.g
                    , randomColorDim.b));
            }

            boxesRendered++;
        }
    }

    printf("Total partitioned blocks : %d\n", boxesRendered);
    printf("Total un-partitioned blocks : %d\n", numOfBoxes - boxesRendered);

    while (boxesRendered < numOfBoxes)
    {
        float posX = boxSpacing + ((boxesRendered % rowSize) * (boxSize + boxSpacing));
        float posY = boxSpacing + ((boxesRendered / rowSize) * (boxSize + boxSpacing));
        rects[boxesRendered].setPosition(sf::Vector2f(posX, posY));
        rects[boxesRendered].setSize(sf::Vector2f(boxSize, boxSize));
        rects[boxesRendered].setFillColor(sf::Color(100, 100, 100));
        boxesRendered++;
    }

    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                printf("New window width : %d, new window height : %d\n", evnt.size.width, evnt.size.height);
                break;

            }
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }

        window.clear();
        for (int i = 0; i < numOfBoxes; i++)
        {
            window.draw(rects[i]);
        }
        window.display();

    }

}