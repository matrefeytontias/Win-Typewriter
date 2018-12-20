# Win-Typewriter
Ever felt tired of lame stupid computers with no physical feedback when you're typing ? Look no further !

Win-Typewriter is a state-of-the-art clean and fresh typewriter experience right on your Windows machine ! This amazing revolutionary software will open up your disk tray every 100 keys pressed. It's like you're back with your trusted Touchmaster 5, except even better because it's on your computer ! Legend has it that the number of keys pressed before your tray opens is customizable ! No way !

Made by Mattias Refeyton and Salomé Thirot, 'cause I mean, you gotta.

## Usage

You'll need MinGW-w64 with MSYS2 and gcc to compile this. Once you're set up, just type `make run` to enter the experience. Additionally, once the main software (`typewriter.exe`) is built, you can also run it with the number of keys you would like pressed between each tray opening as a parameter, like `typewriter.exe 250`. If you don't feel like doing it, you can also juust double-click the file like normal, and it will default to 100 keys.

If you ever feel like opting out of this enlightening endeavour, you simply have to press the `ESCAPE` key. Piece of cake !

## Implementation details

Under the hood, this uses the WinAPI low-level keyboard hooks to inject a callback from a DLL into the global hook chain. This callback then catches all key presses and increments a counter, opening up the disk tray when a certain amount is reached and reacting to the `ESCAPE` key accordingly.
