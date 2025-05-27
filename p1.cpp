#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
using namespace sf;

// Struct for user records
struct User
{
    string name;
    int stage;
};

// Struct for image data (path and hidden words)
struct ImageData
{
    string imagePath;
    vector<string> hiddenWords;
};

// Function to load image data from a file
vector<ImageData> loadImageData(const string& filename)
{
    vector<ImageData> images;
    ifstream file(filename);
    if (file.is_open())
    {
        string path;
        while (file >> path)
        {
            ImageData image;
            image.imagePath = path;
            for (int i = 0; i < 6; ++i) 
            {
                string word;
                if (file >> word)
                {
                    image.hiddenWords.push_back(word);
                }
            }
            images.push_back(image);
        }
        file.close();
    }
    else
    {
        cerr << "Error: Could not open " << filename << "\n";
    }
    return images;
}

// Function to save user record to a file
void saveUserRecord(const string& filename, const User& user) {
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        file << user.name << " " << user.stage+1 << "\n";
        file.close();
    }
    else
    {
        cerr << "Error: Could not open " << filename << "\n";
    }
}

int main()
{
    // Initialize SFML window
    RenderWindow window(VideoMode(700, 700), "Secrete Word Game");

    // Load image data
    vector<ImageData> images = loadImageData("images.txt");
    if (images.empty()) 
    {
        cerr << "No images to display. Exiting...\n";
        return -1;
    }


    // Initialize user
    User user;
    cout << "Welcome to Secret Code Game!\n This game has 8 stages and each stage has 6 hidden codes in pictures\n You will get 80 seconds for each stage to find hidden secrete codes and enter it. \n If you want to quit please close window\n If you want to proceed Enter your name: ";
    cin >> user.name;
    user.stage = 0;

    // Game loop
    int currentImageIndex = 0;
    bool gameRunning = true;
    int correctGuessed = 0;

    Font font;
    if (!font.loadFromFile("fonts\\Roboto-Bold.ttf")) {
        cerr << "Error: Could not load font.\n";
        return -1;
    }

    Text userInputText("", font, 40);
    userInputText.setFillColor(Color::White);
    userInputText.setPosition(35, 620);

    Clock stageClock;
    Time timeLimit = seconds(80);

    string userInput;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b') { // Handle backspace
                    if (!userInput.empty())
                        userInput.pop_back();
                }
                else if (event.text.unicode == '\r') { // Handle enter
                    bool correct = false;
                    for (string& word : images[currentImageIndex].hiddenWords) {
                        if (userInput == word) {
                            correct = true;
                            correctGuessed++;
                            break;
                        }
                    }

                    if (correct) {
                        cout << "Correct!\n";
                        userInput.clear();

                        if (correctGuessed == 6) {
                            user.stage++;
                            currentImageIndex++;
                            correctGuessed = 0;
                            stageClock.restart();

                            if (currentImageIndex >= images.size()) {
                                gameRunning = false;
                                break;
                            }
                        }
                    }
                    else {
                        cout << "Incorrect. Game Over.\n";
                        Texture failureTexture;
                        if (failureTexture.loadFromFile("images\\Failure.jpg")) {
                            Sprite failureSprite(failureTexture);
                            window.clear();
                            window.draw(failureSprite);
                            window.display();
                            sleep(seconds(3));
                        }
                        gameRunning = false;
                        break;
                    }
                }
                else {
                    userInput += static_cast<char>(event.text.unicode);
                }
                userInputText.setString(userInput);
            }
        }

        if (!gameRunning) {
            break;
        }
        // Check timer
        if (stageClock.getElapsedTime() > timeLimit) {
            cout << "Time's up. Game Over.\n";
            Texture failureTexture;
            if (failureTexture.loadFromFile("images\\Failure.jpg")) {
                Sprite failureSprite(failureTexture);
                window.clear();
                window.draw(failureSprite);
                window.display();
                sleep(seconds(3));
            }
            break;
        }
        // Load current image
        Texture texture;
        if (!texture.loadFromFile(images[currentImageIndex].imagePath)) {
            cerr << "Error: Could not load image " << images[currentImageIndex].imagePath << "\n";
            return -1;
        }

        Sprite sprite(texture);

        // Render
        window.clear();
        window.draw(sprite);
        window.draw(userInputText);
        window.display();
    }

    // Save user record and exit
    saveUserRecord("users.txt", user);
    cout << "Thanks for playing, " << user.name << "! You Failed at stage: " << user.stage+1 << "\n";
    return 0;
}
