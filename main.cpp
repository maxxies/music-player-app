#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

// Contains musics and their ID(Keys)
map<int,string>tracks = {
    {1,"Ambient Music Loop"},{2,"Vintage Analog Drum Machine Disco Beat"},{3,"Drum Beat"},{4,"Funky"},{5,"Groove Machine Electronic"},\
    {6,"Downtempo Music Loop"},{8,"Summer EDM House Music Loop"},{9,"Slow Trip Hop"},{10,"Rock and Roll"},{11,"Funk Beat"},
    {12,"Kick Snare and Claps"}
};
//Category musics
map<int,string>synth = {
    {1,"Ambient Music Loop"},{2,"Groove Machine Electronic"},\
    {3,"Downtempo Music Loop"},{4,"Summer EDM House Music Loop"}
};
map<int,string>drum = {
    {1,"Vintage Analog Drum Machine Disco Beat"},{2,"Drum Beat"},\
    {3,"Slow Trip Hop"},{4,"Funk Beat"},{5,"Kick Snare and Claps"}
};
map<int,string>background = {
    {1,"Funky"},{2,"Rock and Roll"}
};

//Class creates node for linked list implemented in the playlist
class MusicPlayList{
    public:
        string musicName;
        MusicPlayList *next;
};

//Class handles addition to linked list and deletion of the list
class LinkList{
    protected:
        MusicPlayList *head; //head pointer
    public:
        LinkList(){
            head  = NULL; //Head initially set to NULL
        }

        //method adds music to the playlist
        void addToPlayList(string name){
            MusicPlayList *temp = new MusicPlayList(); //New node for music
            temp->musicName= name;
            temp->next = NULL;
            //Music is added to the last part of the list to form a queue
            if(head != NULL){
                MusicPlayList *Last = new MusicPlayList();
                Last->next = head;
                while(Last->next != NULL){
                    Last = Last->next;
                }
                Last->next = temp;
            //adds music to the first position when none is present
            }else{
                head = temp;
            }
        }

        //method deletes linked list
        void deleteLinkedlist(){
            MusicPlayList *current = new MusicPlayList(); //new node to hold present present or current nodes
            current->next = head;
            MusicPlayList *Next = new MusicPlayList(); //new node to hold address of the next node
            Next->next = NULL;
            while(current->next != NULL){ //When linkedlist is not empty
                MusicPlayList *prev = new MusicPlayList(); //new node to hold immediate current node to be deleted
                prev = current;
                Next->next = current->next; //Node holds address of next node
                free(prev); //Immediate current node is deleted
                current->next = Next->next; //address of next node is made current node
            }
            head = NULL; //Sets head pointer to NULL
        }
};

//Class handles the music app
class Music: public LinkList{
    private:
        int userChoice;
    public:
        Music(int num){
            userChoice = num;
        }

        //method routes user to a music page they chose
        void routeToSelectedPages(){
            if(userChoice == 1){
                Music::musicCategoryPage();//Routes user to the all tracks page
            }
            else if(userChoice == 2){
                Music::allTracksPage();//Routes user to the category page
            }
            else{
                cout<<"Choice must be within available range. Try again."<<endl; //when invalid input is made
            }
        }

        //method handles the category page
        void musicCategoryPage(){
            //displays category page to user
            cout<<"\nGenres & Stations"<<endl;
            cout<<setfill('-')<<setw(40)<<"-"<<endl;
            cout<<" 01: Synth Loops\
                  \n 02: Drum Loops\
                  \n 03: Background Music"<<endl;
                    cout<<"Select category."<<endl;
                    cout<<">> ";
                //takes input from user
                int categoryChoice;
                while(!(cin>>categoryChoice)){
                    cout<<"\nChoice must be the number of desired category."<<endl;
                    cout<<">> ";
                    cin.clear();
                    cin.ignore(123,'\n');
                }
                int repeat;
                //Shows chosen category  to user
                switch(categoryChoice){
                    case 01:
                        //displays category to user
                        cout<<setfill('~')<<setw(20)<<endl;
                        cout<<"Synth Loops"<<endl;
                        for(auto i = synth.begin(); i != synth.end();i++){
                            cout<<" "<<i->first<<": "<<i->second<<endl;
                        }
                        Music::handlePlayMusic(synth,1); //handles music selection
                        break;
                    case 02:
                        //displays category to user
                        cout<<setfill('~')<<setw(20)<<endl;
                        cout<<"Drum Loops"<<endl;
                        for(auto i = drum.begin(); i != drum.end();i++){
                            cout<<" "<<i->first<<": "<<i->second<<endl;
                        }
                        Music::handlePlayMusic(drum,1);//handles music selection
                        break;
                    case 03:
                        //displays category selection to user
                        cout<<setfill('~')<<setw(20)<<endl;
                        cout<<"Background Music"<<endl;
                        for(auto i = background.begin(); i != background.end();i++){
                            cout<<" "<<i->first<<": "<<i->second<<endl;
                        }
                        Music::handlePlayMusic(background,1); //handles music selection
                        break;
                    default:
                        //when wrong selection is made
                        cout<<"Invalid choice"<<endl;
                        break;

                }
        }

        //method handles all track page
        void allTracksPage(){
            //displays all tracks to user
            cout<<"Tracks"<<endl;
            cout<<setfill('-')<<setw(40)<<"-"<<endl;
            for(auto i = tracks.begin(); i != tracks.end();i++){
                cout<<" "<<i->first<<": "<<i->second<<endl;
            }
            Music::handlePlayMusic(tracks,2); //handles music selection

        }

        //method handles play of music
        void playMusic(string name){
            int pos = name.find(".");
            cout<<"_-*-__-*-_ "<<name.substr(0,pos)<<" playing..."<<endl;
            PlaySound(TEXT(name.c_str()),NULL,SND_SYNC);
        }

        //method handle selection of music
        void handlePlayMusic(map <int,string > &album , int page){
            //Asks user to choose the form to play music
            cout<<"\nSelect a choice"<<endl;
            cout<<"1: Play a track.\
                 \n2: Play multiple tracks.\
                 \n3: Play all tracks"<<endl;
            cout<<">> ";
            int playType;
            while(!(cin>>playType)){
                cout<<"\nChoice must be a number."<<endl;
                cout<<">> ";
                cin.clear();
                cin.ignore(123,'\n');
            }
            //When user wants a single track to be played
            if(playType == 1){
                int trackChoice;
                cout<<"Enter track number: "<<endl; //takes number of desired track
                cout<<">> ";
                while(!(cin>>trackChoice)){
                    cout<<"\nChoice must be a number."<<endl;
                    cout<<">> ";
                    cin.clear();
                    cin.ignore(123,'\n');
                }
                auto musicToPlay = album.find(trackChoice); //checks if number of track is available
                //executes when track is available
                if(musicToPlay != album.end()){
                    //asks for repeat type
                    int repeat;
                    cout<<"Select play type."<<endl;
                    cout<<"1: Repeat Off\
                            \n2: Repeat On\
                            \n3: Repeat Once"<<endl;
                    cout<<">> ";
                    while(!(cin>>repeat)){
                        cout<<"\nChoice must be a number."<<endl;
                        cout<<">> ";
                        cin.clear();
                        cin.ignore(123,'\n');
                    }
                        //Plays music once
                        if(repeat==1){
                            Music::playMusic(musicToPlay->second); //plays music
                            (page == 2) ? Music::allTracksPage() :  Music::musicCategoryPage(); //returns user back to music page
                        }
                        //Plays music repeatedly
                        else if(repeat == 2){
                            bool repeatSong = true;
                            Music::playMusic(musicToPlay->second); //plays music
                            while(repeatSong){
                                //asks user to stop playing music
                                char answer;
                                cout<<"Play: (Y/N)"<<endl;
                                cout<<">> ";
                                cin>>answer;
                                if(answer == 'Y' || answer == 'y'){
                                    Music::playMusic(musicToPlay->second);//plays same music
                                }
                                //ends play of music
                                else if(answer == 'N' || answer == 'n'){
                                    break;
                                }
                                else{
                                    cout<<"Invalid Choice\n"<<endl;
                                    break;                                }
                            }
                            (page == 2) ? Music::allTracksPage(): Music::musicCategoryPage(); //returns user to music page
                        }
                        //Plays music once after the default play
                        else if(repeat == 3){
                            int repeatAgain = 0;
                            while(repeatAgain != 2){
                                Music::playMusic(musicToPlay->second);//plays music
                            }
                           (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage();//returns user to music page
                        }
                        else{
                            cout<<"Choice not available\n";
                            (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage();//returns user to music page
                        }
                }else{
                    cout<<"Invalid choice\n"<<endl;
                   (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage(); //returns user to music page
                }
            }

            //when user wants to play from a custom playlist
            else if(playType == 2){
                    //gets total number of musics from user
                    int total;
                    cout<<"Enter total number of tracks to play."<<endl;
                    cout<<">> "; //Get array size from user
                    while(!(cin>>total)){ //checks whether input is a number
                        cout<<"Input must be a number."<<endl;
                        cout<<">> ";
                        cin.clear();
                        cin.ignore(123,'\n');
                    }
                    //Takes music number from the user based on the playlist size
                    for(int i = 0; i < total; i++){
                        int num;
                        cout<<"Enter choice: "<<endl;
                        cout<<">> ";
                        while(!(cin>>num)){ // checks if input is a number
                            cout<<"Input must be a number."<<endl;
                            cout<<">> ";
                            cin.clear();
                            cin.ignore(123,'\n');
                        }
                        auto musicToPlay = album.find(num);//checks if chosen music is available
                        //adds music to linkedlist for the playlist
                        if(musicToPlay != album.end()){
                            Music::addToPlayList(musicToPlay->second);

                        }
                        //Gives user another chance when music is not found
                        else{
                            cout<<"Invalid Choice. Try again"<<endl;
                            i--;
                        }
                    }
                    //asks for repeat type
                    int repeat;
                    cout<<"Select play type."<<endl;
                    cout<<"1: Repeat Off\
                                \n2: Repeat On\
                                \n3: Repeat Once"<<endl;
                    cout<<">> ";
                    while(!(cin>>repeat)){
                        cout<<"\nChoice must be a number."<<endl;
                        cout<<">> ";
                        cin.clear();
                        cin.ignore(123,'\n');
                    }
                    //displays playlist to user
                    cout<<"\nPlaylist"<<endl;
                    MusicPlayList *temp = head;
                    while(temp != NULL){
                        cout<<" ~ "<<temp->musicName<<endl;
                        temp = temp->next;
                    }
                    //plays music once
                    if(repeat==1){
                       MusicPlayList* temp = head;
                        while(temp != NULL){
                            Music::playMusic(temp->musicName);
                            temp = temp->next;
                        }
                        Music::deleteLinkedlist(); //deletes current playlist
                        (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage();//returns user  to music page
                    }
                    //plays music repeatedly
                    else if(repeat == 2){
                        bool repeatSong = true;
                        MusicPlayList* temp = head;
                        while(temp != NULL){
                            Music::playMusic(temp->musicName);
                            temp = temp->next;
                        }
                        while(repeatSong){
                            char answer;
                            cout<<"Play: (Y/N)"<<endl;
                            cout<<">> ";
                            cin>>answer;
                            //asks user to playlist play
                            if(answer == 'Y' || answer == 'y'){
                                MusicPlayList* temp = head;
                                    while(temp != NULL){
                                    Music::playMusic(temp->musicName);
                                    temp = temp->next;
                                }
                            }
                            else if(answer == 'N' || answer == 'n'){
                                    break;
                            }
                            else{
                                cout<<"Invalid Choice\n"<<endl;
                                break;                                }
                            }
                        Music::deleteLinkedlist(); //deletes current playlist
                        (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage();//returns user to music page

                    }
                    //plays music once after the default play
                    else if(repeat == 3){
                        int repeatAgain = 0;
                        while(repeatAgain != 2){
                            MusicPlayList* temp = head;
                            while(temp != NULL){
                                Music::playMusic(temp->musicName);
                                temp = temp->next;
                            }
                            repeatAgain++;
                        }
                        Music::deleteLinkedlist(); //deletes current playlist
                        (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage(); //returns user to music page
                    }else{
                        cout<<"Invalid choice\n"<<endl;
                        Music::deleteLinkedlist(); //deletes current playlist
                       (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage(); //returns user to music page
                    }
            }
            //when user wants to play all songs under selected choice
            else if(playType ==3){
                    //asks user for repeat type
                int repeat;
                cout<<"Select play type."<<endl;
                cout<<"1: Repeat Off\
                            \n2: Repeat On\
                            \n3: Repeat Once"<<endl;
                cout<<">> ";
                while(!(cin>>repeat)){
                    cout<<"\nChoice must be a number."<<endl;
                    cout<<">> ";
                    cin.clear();
                    cin.ignore(123,'\n');
                }
                //plays music once
                if(repeat==1){
                    //plays all music
                    for(auto i = album.begin(); i != album.end();i++){
                        Music::playMusic(i->second);
                    }
                    (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage(); //returns user to music page
                }
                //plays music repeatedly
                else if(repeat == 2){
                    bool repeatSong = true;
                    for(auto i = album.begin(); i != album.end();i++){
                        Music::playMusic(i->second);
                    }
                    while(repeatSong){
                        char answer;
                        cout<<"Play: (Y/N)"<<endl;
                        cout<<">> ";
                        cin>>answer;
                        //asks user to stop playing tracks after the first play
                        if(answer == 'Y' || answer == 'y'){
                            for(auto i = album.begin(); i != album.end();i++){
                                Music::playMusic(i->second);
                            }
                        }
                        else if(answer == 'N' || answer == 'n'){
                                break;
                        }
                        else{
                            cout<<"Invalid Choice\n"<<endl;
                            break;                                }
                        }
                    (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage();//returns user to music page
                }
                //plays music once after default play
                else if(repeat == 3){
                    int repeatAgain = 0;
                    while(repeatAgain != 2){
                        for(auto i = album.begin(); i != album.end();i++){
                            Music::playMusic(i->second);
                        }
                        repeatAgain++;
                    }
                    (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage();//returns user to music page
                }else{
                    cout<<"Invalid choice\n"<<endl;
                    (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage(); //returns user to music page
                }
            }
            else{
                cout<<"Invalid input\n"<<endl;
               (page == 2) ? Music::allTracksPage():  Music::musicCategoryPage();//returns user to music page
            }
        }
};

int main()
{
    //displays home page to user
    cout<<setfill('-')<<setw(40)<<"-"<<endl;
    cout<<"SEMNOS MUSIC"<<endl;
    cout<<setfill('-')<<setw(40)<<"-"<<endl;
    cout<<" What to do?\
        \n 1: Browse  available music categories.\
        \n 2: Checkout all tracks."<<endl;
    cout<<">> ";
    //asks user choose between music pages
    int choice;
    while(!(cin>>choice)){
        cout<<"\nChoice must be a number."<<endl;
        cout<<">> ";
        cin.clear();
        cin.ignore(123,'\n');
    }
    //opens music pages for user based on choice made
    Music music = Music(choice);
    music.routeToSelectedPages();

    return 0;
}
