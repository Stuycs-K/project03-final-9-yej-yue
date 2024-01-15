#include "playlist.h"

struct lists* createPlaylist(char* playlistName, struct node* t, struct lists* n) {
    struct lists* playlist = calloc(sizeof(struct node*), 27);
    strcpy(playlist->pname, playlistName);
    playlist->song = t;
    playlist->next = n;
    return playlist;
}

struct lists* insertplaylist(struct lists* new, struct lists* existing){
    // struct lists* temp = new;
    if (existing != NULL){
        struct lists* prev = existing;
        struct lists* temp = existing;

        while (strcmp(temp->pname, new->pname)==-1){
            prev = temp;
            temp = temp->next;
            if (temp == NULL){
                prev -> next = new;
                new -> next = NULL;
                return prev;
            }
        }
        new->next = temp;
        if (existing != temp){
            prev->next = new;
            return existing;
        }
        return new;
    }
    else {
        return new;
    }
}

struct lists* findPlaylist(char* playlistName, struct lists* playlist) {
    struct lists* temp = playlist;
    while (temp != NULL){
        if (strcmp(temp->pname, playlistName)==0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}


void addSong2Playlist(struct node* song, char* playlistName, struct lists* playlist) {
    playlist = findPlaylist(playlistName, playlist);
    if (playlist != NULL) {
        playlist->song = insert_in_order(makesong(song-> name, song-> artist, NULL), playlist->song);
    } 
    else {
        err(errno, "playlist not found \n");
    }
    // playlist-> song = target->song;
}

void printPlaylist(char* playlistName, struct lists** playlist) {
    struct lists* temp = findPlaylist(playlistName, *playlist);
    struct node* tempsong = temp->song;
    int i = 0;
    while(tempsong != NULL) {
        printf("[%d] ", i);
        printsong(tempsong);
        i++;
        tempsong = tempsong->next;
    }
    printf("end of, palylist %s\n", (*playlist)->pname);
    printf("song %s\n", ((*playlist)->song)->name);
}

void printallplaylist(struct lists** playlist){
    struct lists* temp = *playlist;
    while(temp != NULL){
        struct node* tempsong = temp->song;
        printf("playlist %s\n", temp->pname);
        int i = 0;
        while(tempsong != NULL) {
            printf("[%d] ", i);
            printsong(tempsong);
            i++;
            tempsong = tempsong->next;
        }    
        temp = temp->next;
    }
    printf("end of, palylist %s\n", (*playlist)->pname);
    printf("song %s\n", ((*playlist)->song)->name);
}

void deletePlaylist(char* playlistName, struct lists* playlist) {
    struct lists* target = findPlaylist(playlistName, playlist);
    if (target != NULL) {
        target->song = free_list(target->song);
    } 
    else {
        err(errno, "playlist not found \n");
    }
}

struct lists* deletesong(struct lists** lib, char*plistname, char* name, char* singa){
    struct lists* temp = findPlaylist(plistname, *lib);
    if (temp != NULL){
        struct node* tempsong = temp->song;
        struct node* prev = tempsong;
        while(tempsong != NULL){
            if(strcmp(tempsong->name, name)==0){
                if(strcmp(tempsong->artist, singa)==0){
                    if (prev == tempsong){
                        prev = tempsong->next;
                    }
                    else prev->next = tempsong->next;
                    free(tempsong);
                }
            }
            else{
                prev = tempsong;
                tempsong=tempsong->next;
            }
        }
        return temp;
    }
}

void alphabetizePlaylists(char* playlistName, struct lists* playlist, struct node** library) {
    // struct lists* target = findPlaylist(playlistName, playlist);
    // if (target != NULL) {
    //     struct node* temp = *target;
    //     while (temp != NULL) {
    //         add_song(temp, library);
    //         temp = temp-> next;
    //     }
    //     *target = free_list(*target);
    // } 
    // else {
    //     err(errno, "playlist not found \n");
    // }
}