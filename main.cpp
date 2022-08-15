#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unistd.h>

using namespace std;

// Only one show per day and booking can be done for next day only

class Theatre {
    private:
       string TheatreName;
       int seats[20];
       vector <int> seatno; // check initilization
       int vacantseats;
    public:
        Theatre(){}
        Theatre(string strTheatre):TheatreName(strTheatre), seats{0},seatno(0),vacantseats(0) {}
        string GetTName() {
            return TheatreName;
        } 
        int* Getseats () {
          return seats;
        } 
        int CheckSeatAvailability(); 
        bool BookTicket(int numOfTikets, vector <int> seatno);                     
};

class Movies {
    private:
       string MovieName;
       vector <Theatre*> theatre;
    public:
        Movies() {}
        Movies(string strMveName, vector<Theatre *> vPtrTheatreList)
    	{
    		MovieName= strMveName;
    		theatre = vPtrTheatreList;
    	}
        vector <string> GetTheatrelist();
        vector <Theatre*> GetTheatrePointer () {
            return theatre;
        }
        string GetMName(){
               return MovieName;
        } 
        ~Movies() {
            for (int i = 0; i < theatre.size(); i++) {
                       delete theatre[i];
                }
        }                 
}; 

class Services {
    private:
        vector <Movies*> movies;
        int movieid;
        int theatreid;
    public:
        int pushMovies(Movies *obj)
        {
            movies.push_back(obj);
            return 0;
        }
        int ListTheatre();
        int ListMovies();
        int ShowSeatInfo(); 
        ~Services ()
        { 
             for (int i = 0; i < movies.size(); i++) {
                       delete movies[i];
                }
        }             
};


vector <string> Movies::GetTheatrelist(){
    int n;
    vector <string> Tlist;
    vector <Theatre*> Tobj;

   Tobj = GetTheatrePointer();
   n = Tobj.size();
  // cout << "theatrelist" << n;
    for (int i = 0; i < n; i++) {
       // cout << "list theatre" << theatre[i]->GetTName() << endl;
        Tlist.push_back(theatre[i]->GetTName()); 
    }
    return Tlist;
}

int Theatre:: CheckSeatAvailability () {
int emptyseats = 0;
    for(int i = 0;  i < 20; i++) {
        if (seats[i] == 0)
           emptyseats += 1;
        //else 
         //  emptyseats =  emptyseats - 1; 
    }
    vacantseats = emptyseats;
    return vacantseats;
}

bool Theatre:: BookTicket (int NumofTickets, vector <int> seatno) {

    for(int i = 0;  i < NumofTickets; i++)
           seats[seatno[i]] = 1; 
    return true;
}

int Services::ListMovies() {
    int n,ret = 0;

    n = movies.size();  
    //cout << "n =" << n << endl;
    if (n == 0) {
        cout << "\n\t No movies updated Movie" << endl;
        return 0;
    }
    cout << "Please select a Movie " << endl << endl;
    
    for (int i = 0; i < n; i++) {
        cout << i+1 << "\t" << movies[i]->GetMName() << endl;
    }
    cout << "Press any above number to selcet a Movie" << endl;
    cout << "To quit press 0" << endl;
    cin >> movieid;
    if (movieid == 0)
       ret = 0;
    else if(isdigit(movieid))
       ret = 0;
    else
       ret = 1;
    return ret;       
}

int Services::ListTheatre() {
    int ret = 0,n;
    vector <string> list;

    cout << "Please select Theatre" << endl << endl;
    list = movies[movieid -1]->GetTheatrelist();
    n = list.size();
    //cout << "n =" << n << endl;
    if( n == 0)
       return 0;
    for(int j = 0;j < n; j++)
       cout << j+1 << "\t" << list[j] << endl;
    cout << endl;
    cout << "Press any above number to selcet a Theatre" << endl;
    cout << "To quit press 0" << endl;
    cin >> theatreid;
    if (theatreid == 0)
       ret = 0;
    else
       ret = 1;
return ret;
}

int Services:: ShowSeatInfo () {
        int availtickets,seats,blocktickets;
        char proceed,proceed1;
        bool result;
        int *seatarray;
        vector <int> vectorseats;
        vector <int> tempseats;
        //string tempMovie = " ";
        //string tempTheatre  = " ";
        vector <Theatre*> Tobject;
        //  n = sizeof(Tobj);

        Tobject = movies[movieid-1]->GetTheatrePointer();
        availtickets = Tobject[theatreid-1]->CheckSeatAvailability();
        cout << endl;

again:  cout << availtickets << " no of tickets are available" << endl;
        cout << "Please enter Number of tickets to book " << endl;
        cin >> blocktickets;
        if (blocktickets > availtickets) {
            cout << blocktickets <<"Tickets are not available" <<  endl;
            cout << "Do you want to continue y/n ?" << endl;
            cin >> proceed;
            if ( (proceed=='y') || (proceed=='Y') )
               goto again;
            else
               goto ret;
        }
        cout << "\n\t Avaiable seats" << endl << endl;
        seatarray = Tobject[theatreid-1]->Getseats();
        for(int i = 0;  i < 20; i++) {
            if (seatarray[i] == 0) {
                cout << "\t" << i+1 ;    
            } else 
                  cout << '\t' << 'X';
            if (i % 2)
                  cout << '\n';
                
        }
again1:    cout << "\nPlease select your :( " << blocktickets << ") seats " << endl;
            tempseats.clear();
        for(int j = 0 ; j < blocktickets; j++) {
            cin >> seats;
            tempseats.push_back(seats);
        }
        for (int j = 0 ; j < blocktickets; j++) { 
           // cout << "selected seats " << tempseats[j];
                if( seatarray[tempseats[j] - 1] == 0) {
                    vectorseats.push_back(tempseats[j]- 1);
                } else {
                  cout << "The selected seat is not available . Please try again !" << endl;
                  cout << "Do you want to continue y/n ?" << endl;
                  cin >> proceed1;
                  if ( (proceed1 == 'y') || (proceed1 == 'Y') )
                     goto again1;
                  else
                     goto ret;
                }
            }
        //}
        //cout << "seat verified" << endl;
       // tempMovie = movies[movieid - 1]->GetMName();
       // tempTheatre = Tobject[theatreid - 1]->GetTName();
        cout << "Booking " << blocktickets << " Tickets for " << movies[movieid -1]->GetMName() << " in " << Tobject[theatreid-1]->GetTName() << endl; 
        result = Tobject[theatreid - 1]->BookTicket(blocktickets,vectorseats);
        if(result == true)
           return 1;
   ret  : return 0;

}

int main()
{
    Services Book;
    
    static int trial = 0;
    vector <Theatre*> vTheatreObjlist;
    vector <Theatre *> vObjTheatre;
    vector <string> vTheatreNameList;
    string strTheatrename = " ";
    string strMoviename = " ";
    string strName = " ";
    char c;
    int i = 0, j = 0;

    if (trial == 0) {
        fstream Tfile,Mfile;
        Tfile.open("database1.csv",ios::in);
        if(!Tfile) {
            cout << "Database error" << endl; // verified
            Tfile.close();
            //goto bye;
            return 0;
        } else {     
                while( getline(Tfile, strTheatrename,',')) {
                        Theatre *Tobj =  new Theatre(strTheatrename);
                        vTheatreObjlist.push_back(Tobj);
                        //cout << "next loop "<< strTheatrename << endl;
                }
        } 
        Mfile.open("database.csv",ios::in);
        if(!Mfile) {
            cout << "Database error" << endl; // verified
            Mfile.close();
            return 0;   
        } else {       
                 while( getline(Mfile, strName)) {
                       int s = 0;
                     stringstream stringfile(strName) ;
                     //cout << "Movie " << strMoviename << endl; 
                      while( getline(stringfile, strName,',')) { 
                             if(s == 0) {
                                 strMoviename = strName;
                                 s = 1;
                             } else {
                                 //cout << "Theatre " << strName << endl;
                                 vTheatreNameList.push_back(strName);
                             }
                      }
                     for(int i = 0; i < vTheatreNameList.size(); i++) {
                         for(int j = 0; j < vTheatreObjlist.size(); j++) {
                             if(vTheatreObjlist[j]->GetTName() == vTheatreNameList[i]) {
                                 //cout << " list from main " << vTheatreNameList[i] << endl; 
                                 vObjTheatre.push_back(vTheatreObjlist[j]);
                             }
                         }
                     }
                 Movies *ptrMovieObj = new Movies(strMoviename,vObjTheatre);
                 Book.pushMovies(ptrMovieObj);
                   
              } 
        }                             
            Mfile.close();
            Tfile.close();
            trial = 1;
        }  
    while (1) {
        if (Book.ListMovies()) {
           if (Book.ListTheatre()) {
               if (Book.ShowSeatInfo()) {
                    cout<<"\n\n Tickets has been succcesfully booked for you !!!" ;
                    cout<<"\n\n THANK YOU !!!\n\n"; 
               } else {
                cout<<"\n\n Booking failed Please try again !!!";
               }
           } else
                break;
        } else {
          break;  
        }

        sleep(5);
    }
  //  bye:    
    cout<<"\nTHANK YOU !!!";   
    return 0;
}