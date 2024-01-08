#include "list.h"
#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

void err(int i, char* message) {
    if (i < 0){
        printf("error %s - %s \n", message, strerror(errno));
        exit(1);
    }
}

int main() {
    srand(time(NULL));
    struct node* a = makesong("the ride", "drake", NULL);
    a = insert_in_order(makesong("la tortura", "shakira", NULL), a);
    a = insert_in_order(makesong("el jefe", "shakira", NULL), a);
    a = insert_in_order(makesong("hyfr", "drake", NULL), a);
    a = insert_in_order(makesong("africa", "shakira", NULL), a);
    print_list(a);
    printf("find shakira song\n");
    if (find_song_by_artist("shakira", a) != NULL) printsong(find_song_by_artist("shakira", a));
    else printf("not found\n");
    printf("find adele song\n");
    if (find_song_by_artist("adele", a) != NULL) printsong(find_song_by_artist("adele", a));
    else printf("not found\n");
    printf("random song\n");
    printsong(rand_song(a));
    printf("finding hyfr by shakira\n");
    if (find_song("shakira", "hyfr", a) != NULL) printsong(find_song("shakira", "hyfr", a));
    else printf("not found\n");
    printf("finding hyfr by drake\n");
    if (find_song("drake", "hyfr", a) != NULL) printsong(find_song("drake", "hyfr", a));
    else printf("not found\n");
    free_list(a);

    struct node** b = makelib();
    add_song(makesong("habits", "tove lo", NULL), b);
    add_song(makesong("talking body", "tove lo", NULL), b);
    add_song(makesong("electric body", "asap rocky", NULL), b);
    add_song(makesong("all mine", "brent faiyaz", NULL), b);
    add_song(makesong("outside", "calvin harris", NULL), b);
    add_song(makesong("heartbeat", "childish gambino", NULL), b);
    add_song(makesong("les", "childish gambino", NULL), b);
    add_song(makesong("shot for me", "drake", NULL), b);
    add_song(makesong("search and rescue", "drake", NULL), b);
    add_song(makesong("bailando", "enrique iglesias", NULL), b);
    add_song(makesong("wiseman", "frank ocean", NULL), b);
    add_song(makesong("low life", "future", NULL), b);
    add_song(makesong("solo", "future", NULL), b);
    add_song(makesong("rockland", "gracie abrams", NULL), b);
    add_song(makesong("from eden", "hozier", NULL), b);
    add_song(makesong("replay", "iyaz", NULL), b);
    add_song(makesong("whatcha say", "jason derulo", NULL), b);
    add_song(makesong("what a life", "jhene aiko", NULL), b);
    add_song(makesong("father time", "kendrick lamar", NULL), b);
    add_song(makesong("moonlight", "kali uchis", NULL), b);
    add_song(makesong("she will", "lil wayne", NULL), b);
    add_song(makesong("margaret", "lana del rey", NULL), b);
    add_song(makesong("supercut", "lorde", NULL), b);
    add_song(makesong("the spins", "mac miller", NULL), b);
    add_song(makesong("say it right", "nelly furtado", NULL), b);
    add_song(makesong("night changes", "one direction", NULL), b);
    add_song(makesong("trance", "metro boomin", NULL), b);
    add_song(makesong("break from toronto", "partynextdoor", NULL), b);
    add_song(makesong("sure thing", "miguel", NULL), b);
    add_song(makesong("woo", "rihanna", NULL), b);
    add_song(makesong("bohemian rhapsody", "queen", NULL), b);
    add_song(makesong("kiss it better", "rihanna", NULL), b);
    add_song(makesong("fourth of july", "sufjan stevens", NULL), b);
    add_song(makesong("c u girl", "steve lacy", NULL), b);
    add_song(makesong("clean", "taylor swift", NULL), b);
    add_song(makesong("yes i'm changing", "tame impala", NULL), b);
    add_song(makesong("dj got us fallin in love", "usher", NULL), b);
    add_song(makesong("riptide", "vance joy", NULL), b);
    add_song(makesong("are you bored yet?", "wallows", NULL), b);
    add_song(makesong("jocelyn flores", "xxxtentacion", NULL), b);
    add_song(makesong("down in the dm", "yo gotti", NULL), b);
    add_song(makesong("turban", "yeat", NULL), b);
    add_song(makesong("pillowtalk", "zayn", NULL), b);
    add_song(makesong("immortal", "21 savage", NULL), b);
    add_song(makesong("prblms", "6LACK", NULL), b);
    print_lib(b);
    printf("finding yo gotti songs\n");
    if (search_artist("yo gotti", b) != NULL) printsong(search_artist("yo gotti", b));
    else printf("not found\n");
    printf("finding songs by anefon\n");
    if (search_artist("anefon", b) != NULL) printsong(search_artist("anefon", b));
    else printf("not found\n");
    printf("finding song 'solo' by future\n");
    if (search_song("future", "solo", b) != NULL) printsong(search_song("future", "solo", b));
    else printf("not found\n");
    printf("finding song 'a' by future\n");
    if (search_song("future", "a", b) != NULL) printsong(search_song("future", "a", b));
    else printf("not found\n");
    print_letter(b, 'f');
    print_artist(b, "tove lo");
    print_artist(b, "aog");
    shuffle(b, 5);
    printf("deleting prblms by 6LACK\n");
    print_list(delete_song(b, "prblms", "6LACK"));
    printf("deleting talking body by tove lo\n");
    print_list(delete_song(b, "talking body", "tove lo"));
    clear_lib(b);
    print_lib(b);
}