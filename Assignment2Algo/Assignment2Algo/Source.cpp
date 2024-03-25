#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace sf;
using namespace std;

int GetFileLineCount() //do i even need this anymore?
{
        int number_of_lines = 0;
        string line;
        ifstream myfile("values.txt");

        while (std::getline(myfile, line))
            ++number_of_lines;

        return number_of_lines;
}


void merge(std::vector<int>& values, int start, int middle, int end) {

    vector<int> lArray(middle - start + 1);
    vector<int> rArray(end - middle);

    for (int i = 0; i < lArray.size(); ++i)
        lArray[i] = values[start + i];
    for (int i = 0; i < rArray.size(); ++i)
        rArray[i] = values[middle + 1 + i];
  
    
    int leftIndex = 0;
    int rightIndex = 0;
    int currentIndex = start;
    while (leftIndex < (int)lArray.size() && rightIndex < (int)rArray.size()) //why am i typecasting int...it wont run otherwise omg
    {//nvm figured it out. now im just leaving it there out of anger
        if (lArray[leftIndex] <= rArray[rightIndex]) 
        {
            values[currentIndex] = lArray[leftIndex];
            leftIndex++;
        }
        else 
        {
            values[currentIndex] = rArray[rightIndex];
            rightIndex++;
        }
        currentIndex++;
    }
    while (leftIndex < lArray.size()) 
        values[currentIndex++] = lArray[leftIndex++];
    while (rightIndex < rArray.size()) 
        values[currentIndex++] = rArray[rightIndex++];
} //so thats working. now to add visuals?
//future me: i CANNOT FIGURE VISUALS OUT. UGHH. Sorry mr. marker, dis ones a flop :(

void mergeSort(std::vector<int>& values, int start, int end) {
    // recursives hurt my brain.
    if (start < end) {
        mergeSort(values, start, (start + end) / 2);
        mergeSort(values, (start + end) / 2 + 1, end);

        merge(values, start, (start + end) / 2, end);
    }
}


int main()
{
    int length = GetFileLineCount();

    vector<int> toMerge;


    string line;
    int current;
    
    ifstream myFile("values.txt");
    if (myFile.is_open())
    {
        while (getline(myFile,line))
        {
            current = stoi(line);
            cout << current <<" ";
            toMerge.push_back(current);
        }

    }
    myFile.close();

    mergeSort(toMerge, 0, length - 1);
    cout << "now sorted\n";
    for (int i = 0 ; i < (int)toMerge.size(); i++)
    {
        cout << to_string(toMerge[i]);
    }
    
    /*
    Clock clock;
    RenderWindow window(sf::VideoMode(1500, 700), "Merge Sort");

    //cout << "Press Spacebar to start visuals";
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();

        for (int i = 0; i < (int)toMerge.size(); i++)
        {
           // window.draw(rects[i]);
        }
        window.display();
    }
    */
    return 0;
    
}