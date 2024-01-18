[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# music player

## jellen

Ellen Yu, Jennifer Ye

Broad description of project

(Optional) List of any required libraries. Include instructions on how to install the libraries
Instructions on how to install/use your project
       
### Project Description:

#### UPDATED (WORKING ORIGINAL PROGRAM):
Our project is a multiclient music player that mimics Spotify. Clients can create, modify, and view playlists as well as the queue. They can also play, skip, rewind, and pause songs using mpg123's built-in functions. We use linked lists for the playlists and queue, and with client-server connection, the user can interactively alter them. The server contains instructions and the client inputs commands and song/playlist information for the server to process through socket connection. We allocate memory for the lists and work with audio (mp3) files to play music. In our program, we implement signals to exit the music player and find the songs' information, which is found with stat.

#### NEW: 
Unfortunately, because we couldn't get our server/client to work with the clients' playlists, we had to switch to using just a main file. This main file allows the user to use songs in our provided music library of 10 songs to make a playlist, add to a playlist, delete from a playlist, delete a playlist, play a song, add to a queue, play a queue, and clear a queue. Having used so many class concepts in our "old" project, our new project utilizes Allocating memory, Working with files, Finding information about files (stat and such), Processes (fork, exec, etc.), and Signals, while our old one covered all of that and Shared memory, Semaphores, and Sockets. 

#### OLD: 
Our project is meant to be a music player that can handle multiple clients. After the server and client connect, the server will inform the client and the client will input commands. The server forks for each client's command to allow proper running. We allocate memory for playlists and shared memory. Each client can then create playlists with this memory, add/delete songs from those playlists, view the playlists and overall library, and add songs to the queue. The changes made will be stored in shared memory that can be accessed in all processes. To ensure the shared memory is correct, we will use semaphores to have one process at a time. The clients can also exit the music player control audio playback with signals: play, pause, skip, and rewind songs. 

At the moment, we can't get the shared memory to align correctly because it is not the same playlist data after forking finishes as inside the fork. We've reverted to a music player without server/client instead. 
  
### Instructions:

#### UPDATED (WORKING ORIGINAL PROGRAM) - relatively same instructions:

To run the program, first make compile to compile each file. Then, run make server in one terminal and make client in another. The terminals should connect and in the client terminal, you can perform commands that will run in the server terminal. The instructions are printed into the terminal.
To run the main.c program (without server/client connection), use make run. 

In the server/client program, the commands are:
- type 'm' to make a playlist, which will then ask for playlist name, base number of songs in playlist, and song names and artists
- type 'a' to add a song into a specific playlist, so the program will ask for a playlist name and song information. 
- type 'vplaylist' will ask for a playlist name for a specific playlist to print 
- type 'vlib' will print out the entire music library, which shows you available songs to put into playlists or play. 
- type 'd' command will delete a playlist or song, so you must tell the program whether you're deleting a playlist or song when prompted and the playlist/song info. 
- type 'q' command will ask the client for a name to the song in the library, and it will then add that song to the queue
- type 'v' command will print the current numbered queue in the server
- type 'p' command will play the current numbered queue from server 
- type 'play' command will prompt the the client to enter a song they'd like to play right now, so that the server will play the song
- type 'c' command will clear the queue 

In the main.c program (without server/client connection):
- type 'vlib' to view the entire library of songs at your disposure
- type 'mplaylist' to make a new playlist
- type 'vplaylist' to view a specific playlist
- type 'add2playlist' to add to a specified playlist
- type 'deletefromplaylist' to specify a song to delete from a specific playlist
- type 'deleteplaylist' to delete a specific playlist
- type 'playsong' to specify a song to play out loud
- type 'add2queue' to add songs to play in a queue
- type 'vqueue' to view all the songs currently in the queue
- type 'playqueue' to play all the songs in the queue
- type 'clearqueue' to clear all the songs in the queue

Signal (SIGINT) or ctrl+c quits the music player, allowing the user to exit the music player, returning to the original terminal. Signal (SIGQUIT) or ctrl+\ prints out the music folder's files' data for the user to see. 

#### NEW: 
In order to play the actual music, we had to install mpg123 through Homebrew. To do so, enter the following two commands in your terminal:
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

brew install mpg123
```

To run the program, first make compile to compile each file necessary to run the main file. After, do make run in your terminal, which will prompt the user with "enter a command: " after printing out further instructions for the user to actually use our program. All of the user commands prompt the user for more information before completing the task. The instructions are as follows: 

    // 'vlib' to view the entire library of songs at your disposure
    // 'mplaylist' to make a new playlist
    // 'vplaylist' to view a specific playlist
    // 'add2playlist' to add to a specified playlist
    // 'deletefromplaylist' to specify a song to delete from a specific playlist
    // 'deleteplaylist' to delete a specific playlist
    // 'playsong' to specify a song to play out loud
    // 'add2queue' to add songs to play in a queue
    // 'vqueue' to view all the songs currently in the queue
    // 'playqueue' to play all the songs in the queue
    // 'clearqueue' to clear all the songs in the queue

Signal (SIGINT) or ctrl+c quits the music player, allowing the user to exit the music player, returning to the original terminal. Signal (SIGQUIT) or ctrl+\ prints out the music folder's files' data for the user to see. 

#### OLD: 
To run the program, first make compile to compile each file. Then, run make server in one terminal and make client in another. The terminals should connect and in the client terminal, you can perform commands that will run in the server terminal. The instructions are printed into the terminal. 

Press 'm' to make a playlist, which will then ask for playlist name, base number of songs in playlist, and song names and artists. Pressing 'a' will add a song into a specific playlist, so the program will ask for a playlist name and song information. 'vplaylist' will ask for a playlist name for a specific playlist to print and 'vlib' will print out the entire music library, which shows you available songs to put into playlists or play. The 'd' command will delete a playlist or song, so you must tell the program which one you're deleting when prompted and the playlist/song info. 

To exit, press ctrl+c (SIGINT) in each terminal.

### BUGS:
- can only play and interact with songs we downloaded with our code
- we don't check if the user's song request is within our library (for queue, nothing plays)
we were unable to check if the user's song request was within our library; instead, our code just pretends like that song exists and doesn't throw an error or anything when that song is requested to be played or added to a queue (nothing plays because there is no such song in our library)
- after SIGQUIT is used, the user needs to press enter for the prompt enter a command: to show up again 
- deleting a playlist after deleting all the songs will result in an error (double free)