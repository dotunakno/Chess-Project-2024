// #include <SFML/Graphics.hpp>

// int main() {
//     // Create a window with size 1000x1000
//     sf::RenderWindow window(sf::VideoMode(600, 600), "Chess Board");

//     // Load the first texture
//     sf::Texture boardTexture1;
//     if (!boardTexture1.loadFromFile("chess.com Assets/board.png")) {
//         return -1; // Error handling if file not found
//     }

//     // Load the second texture
//     sf::Texture boardTexture2;
//     if (!boardTexture2.loadFromFile("ChessAssets/Board.png")) {
//         return -1; // Error handling if file not found
//     }

//     // Create a sprite with the initial texture
//     sf::Sprite boardSprite(boardTexture1);

//     // Scale the initial texture to 600x600 and center it
//     boardSprite.setScale(
//         600.0f / boardTexture1.getSize().x,
//         600.0f / boardTexture1.getSize().y
//     );
//     boardSprite.setPosition(
//         (600 - 600) / 2.0f, // x position
//         (600 - 600) / 2.0f  // y position
//     );

//     bool usingFirstTexture = true; // Track which texture is currently being used

//     // Main loop
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//             // Check if the K key is pressed
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) {
//                 // Toggle between the two textures
//                 if (usingFirstTexture) {
//                     boardSprite.setTexture(boardTexture2, true);
                    
//                     // Scale board2.png to 600x600 and center it
//                     boardSprite.setScale(
//                         600.0f / boardTexture2.getSize().x,
//                         600.0f / boardTexture2.getSize().y
//                     );
//                 } else {
//                     boardSprite.setTexture(boardTexture1, true);
                    
//                     // Scale board.png to 600x600 and center it
//                     boardSprite.setScale(
//                         600.0f / boardTexture1.getSize().x,
//                         600.0f / boardTexture1.getSize().y
//                     );
//                 }
//                 usingFirstTexture = !usingFirstTexture; // Switch the flag
//             }
//         }

//         // Clear the window
//         window.clear();

//         // Draw the board as the centered background
//         window.draw(boardSprite);

//         // Display the window content
//         window.display();
//     }

//     return 0;
// }
