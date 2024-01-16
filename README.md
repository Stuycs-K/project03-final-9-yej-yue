[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# music player

### jellen

Ellen Yu, Jennifer Ye
       
### Project Description:

Our project is meant to be a music player that can handle multiple clients. After the server and client connect, the server will inform the client and the client will input commands. The server forks for each client's command to allow proper running. We allocate memory for playlists and shared memory. Each client can then create playlists with this memory, add/delete songs from those playlists, view the playlists and overall library, and add songs to the queue. The changes made will be stored in shared memory that can be accessed in all processes. To ensure the shared memory is correct, we will use semaphores to have one process at a time. The clients can also exit the music player control audio playback with signals: play, pause, skip, and rewind songs. 

At the moment, we can't get the shared memory to align correctly because it is not the same playlist data after forking finishes as inside the fork. We've reverted to a music player without server/client instead. 
  
### Instructions:

To run the program, first make compile to compile each file. Then, run make server in one terminal and make client in another. The terminals should connect and in the client terminal, you can perform commands that will run in the server terminal. The instructions are printed into the terminal. 

Press 'm' to make a palylist, which will then ask for playlist name, base number of songs in playlist, and song names and artists. Pressing 'a' will add a song into a specific playlist, so the program will ask for a playlist name and song information. 'vplaylist' will ask for a playlist name for a specific playlist to print and 'vlib' will print out the entire music library, which shows you available songs to put into playlists or play. The 'd' command will delete a playlist or song, so you must tell the program which one you're deleting when prompted and the playlist/song info. 

To exit, press ctrl+c in each terminal. 
