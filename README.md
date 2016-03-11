
# Morse Tool (Graphical User Interface App)

***
### Project Website: http://akd92.github.io/Morse-Tool-GUI-Application/

***
The aim of this project is to design and offer a graphical frontend for my Morse Code Library libmorse.a. The output of this project will be a stand-alone application (exe) which can be used for conversion of morse code to other forms and vice versa.

This project uses my Morse Code Library "libmorse.a", hosted on my GitHub account under the name of repository "Morse-Code-Library"

***

### ScreenShots

<img src="https://github.com/AKD92/Morse-Tool-GUI-Application/raw/master/scrn_1.png">  <img src="https://github.com/AKD92/Morse-Tool-GUI-Application/raw/master/scrn_2.png">

***

The application of this project, "morsetool.exe" (can be found inside of "bin" directory) links statically with "libmorse.a" along with "libbst.a", "libstackqueue.a" and "liblinkedlist.a".

libbst.a is standard C implementation of Dictionary data structure using Binary Search Tree (BST), libstackqueue.a is standard C implementation of Stack and Queue data structure and liblinkedlist.a is standard C implementation of Linked List data structure, including both singly and doubly versions.

Graphical User Interface was built using IUP Interface library, which is a multiplatform C user interface toolkit, freely available.

This project is compiled using GCC 4.8 32 bit Windows port.

For more information, check the <a href = "http://akd92.github.io/Morse-Tool-GUI-Application/">Project Website</a>
