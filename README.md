[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# music player

## jellen

Ellen Yu, Jennifer Ye

Broad description of project

(Optional) List of any required libraries. Include instructions on how to install the libraries
Instructions on how to install/use your project
       
### Project Description:

#### NEW: 
Unfortunately, because we couldn't get our server/client to work with the clients' playlists, we had to switch to using just a main file. This main file allows the user to use songs in our provided music library of 10 songs to make a playlist, add to a playlist, delete from a playlist, delete a playlist, play a song, add to a queue, play a queue, and clear a queue. Having used so many class concepts in our "old" project, our new project utilizes Working with files, Finding information about files (stat and such), Processes (fork, exec, etc.), and Signals, while our old one covered all of that and Shared memory, Semaphores, and Sockets.

#### OLD: 
Our project is meant to be a music player that can handle multiple clients. After the server and client connect, the server will inform the client and the client will input commands. The server forks for each client's command to allow proper running. We allocate memory for playlists and shared memory. Each client can then create playlists with this memory, add/delete songs from those playlists, view the playlists and overall library, and add songs to the queue. The changes made will be stored in shared memory that can be accessed in all processes. To ensure the shared memory is correct, we will use semaphores to have one process at a time. The clients can also exit the music player control audio playback with signals: play, pause, skip, and rewind songs. 

At the moment, we can't get the shared memory to align correctly because it is not the same playlist data after forking finishes as inside the fork. We've reverted to a music player without server/client instead. 
  
### Instructions:

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