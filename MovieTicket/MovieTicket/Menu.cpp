#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string.h>

using namespace std;

void staffLogin(string username, string password);
void menu();
void menuMovie();
void menuPurchase();
void addMovie();
void displayMovie();
void searchMoviebyID();
void filterMoviebyCategory();
void updateMovie();
void deleteMovie();
void sortMoviebyName();
void loadMovieRecord(int movieid, string moviename, string genre, string language, int numberofseats, string releasedate, string description);


void addTicketPurchase();
void viewTicketPurchase();
void sortPurchase();
void viewTicketPurchaseDetail();
void loadTicketPurchaseRecord(int ticketId, int movieId, string ticketType, string showtime, string ticketPrice, int quanity, int Total);


struct movie
{
	int movieid; //Movie ID Eg : 123
	string moviename; //Movie name
	string genre; //Genre
	string language; //Language
	int numberofseats; //Number of seats
	string releasedate; //Release Date
	string description; //Description
	movie* next;
};

struct movie* head = NULL;

void loadMovieRecord(int movieid, string moviename, string genre, string language, int numberofseats, string releasedate, string description)
{
	movie* newmovie = new movie;
	newmovie->movieid = movieid;
	newmovie->moviename = moviename;
	newmovie->genre = genre;
	newmovie->language = language;
	newmovie->numberofseats = numberofseats;
	newmovie->releasedate = releasedate;
	newmovie->description = description;
	newmovie->next = NULL;

	if (head == NULL)
	{
		head = newmovie;
	}
	else
	{
		newmovie->next = head; //Big O notation from O(N) become o(1)
		head = newmovie;
	}
}

void addMovie() {
	struct movie* newmovie = new struct movie;
	struct movie* checkID;
	checkID = head;
	cout << "Enter movie ID: ";
	cin >> newmovie->movieid; //read movie value

	while (checkID != NULL)//validate data
	{
		if (newmovie->movieid == checkID->movieid) {
			cout << "The movie ID is duplicated! Please re-enter the movie ID: ";
			cin >> newmovie->movieid;
			checkID = head;
			while (checkID != NULL) {
				if (newmovie->movieid == checkID->movieid) {
					cout << "The movie ID is duplicated! Please re-enter the movie ID: ";
					cin >> newmovie->movieid;
					checkID = head;
				}
				else {
					checkID = checkID->next;
				}
			}
		}
		else {
			checkID = checkID->next;
		}
	}


	cout << "Movie Name: "; //reading value
	cin.ignore();
	getline(cin, newmovie->moviename);
	while (checkID != NULL) //validation
	{
		if (newmovie->moviename == checkID->moviename) {
			cout << "The movie name is duplicated! Please re-enter the movie name: ";
			cin >> newmovie->moviename;
			checkID = head;
			while (checkID != NULL)
			{
				if (newmovie->moviename == checkID->moviename) {
					cout << "The movie name is duplicated! Please re-enter the movie name: ";
					cin.ignore();
					getline(cin, newmovie->moviename);
					checkID = head;
				}
				else {
					checkID = checkID->next;
				}
			}
		}
		else {
			checkID = checkID->next;

		}
	}

	cout << "Genre [Action, Comedy, Horror]: "; //reading value
	cin >> newmovie->genre;

	cout << "Language [Malay, English, Chinese, Tamil, Other]: ";
	cin >> newmovie->language;

	cout << "Seat Available: "; //reading value
	cin >> newmovie->numberofseats;
	while (newmovie->numberofseats < 1) { //validation
		cout << "Number of seats cannot be less than 1. Please try again. " << endl;
		cout << "Seat Available: ";
		cin >> newmovie->numberofseats;
	}

	cout << "Release Date (dd/mm/yy): ";
	cin >> newmovie->releasedate;

	cout << "Description: ";
	cin.ignore();
	getline(cin, newmovie->description);

	cout << endl;

	newmovie->next = head; //Big O notation from O(N) become o(1)
	head = newmovie;

}

void searchMoviebyID() {
	movie* searchMovie = head;  //declaring pointer variable

	if (searchMovie == NULL) {    //validation to check if there is no record added
		cout << "No Record in the List!\n";
	}
	else {
		cout << "Enter Movie ID to search: " << endl;  //movie ID is searched
		int searchID; //variable to hold the search value entered by user
		cin >> searchID;
		bool found = false; //boolean variable 

		while (searchMovie != NULL) { //iterate through until pointer holds NULL value
			if (searchMovie->movieid == searchID) { //if match is found
				cout << string(150, '=');
				cout << "\n***Movie Searched***\n";
				cout << "Movie ID\tMovie Name\tGenre\t\tLanguage\tNo of Seats\tRelease date\t\tDescription\n";
				cout << "" << searchMovie->movieid <<
					"\t\t" << searchMovie->moviename <<
					"\t\t" << searchMovie->genre <<
					"\t\t" << searchMovie->language <<
					"\t\t" << searchMovie->numberofseats <<
					"\t\t" << searchMovie->releasedate <<
					"\t\t" << searchMovie->description << endl;
				cout << string(150, '=');
				cout << endl;
				found = true; //set boolean to true
			}
			searchMovie = searchMovie->next; //traverse through the linked list
		}
		if (found == false) //if no record with given search ID is found
		{
			cout << "No record with the ID given is found. Search again!\nPress [1] to search again, Press [2] to exit" << endl;
			int choice;
			cin >> choice;
			switch (choice) {
			case 1:
				searchMoviebyID(); //calling method again
				break;
			case 2:
				menuMovie(); // going back to main menu
				break;
			default:
				cout << "\nInvalid Selection!";
				menuMovie(); // invalidd choice brings to main menu
				break;
			}
		}
	}
}

void filterMoviebyCategory() {
	struct movie* movieFilter = head;

	if (movieFilter == NULL) {
		cout << "No Record in the List!\n";
	}
	else
	{
		displayMovie();
		string temp;
		bool found = false;
		cout << "Genre available are Action, Comedy and Horror " << endl;
		cout << "Enter Genre/Category to Filter Out: ";
		cin >> temp;

		while (movieFilter != NULL) {

			if (movieFilter->genre == temp) {
				cout << string(150, '=');
				cout << "\n***Movie Filtered from Category/Genre: " << temp << " ***\n";
				cout << "Movie ID\tMovie Name\tGenre\t\tLanguage\tNo of Seats\tRelease date\t\tDescription\n";
				cout << "" << movieFilter->movieid <<
					"\t\t" << movieFilter->moviename <<
					"\t\t" << movieFilter->genre <<
					"\t\t" << movieFilter->language <<
					"\t\t" << movieFilter->numberofseats <<
					"\t\t" << movieFilter->releasedate <<
					"\t\t" << movieFilter->description << endl;
				cout << string(150, '=');
				cout << endl;
				found = true;

			}
			movieFilter = movieFilter->next;
		}
		if (found == false) {
			cout << "No record availble with the genre/category typed!\nPress [1] to try again, Press [2] to exit" << endl;
			int choice;
			cin >> choice;

			switch (choice) {
			case 1:
				filterMoviebyCategory();
				break;
			case 2:
				menuMovie();
				break;
			default:
				cout << "\nInvalid Selection!";
				menuMovie();
				break;
			}

		}
	}
}

void updateMovie()
{
	movie* movieUpdate = head;
	if (movieUpdate == NULL) {
		cout << "No Record in the List!\n";
	}
	else
	{
		displayMovie();
		cout << "Enter Movie ID to update: " << endl;
		int searchID;
		cin >> searchID;
		bool found = false;
		while (movieUpdate != NULL)
		{
			if (movieUpdate->movieid == searchID)
			{
				found = true;
				cout << string(150, '=');
				cout << "\n***Movie Details***\n";
				cout << "Movie ID\tMovie Name\tGenre\t\tLanguage\tNo of Seats\tRelease date\t\tDescription\n";
				cout << "" << movieUpdate->movieid <<
					"\t\t" << movieUpdate->moviename <<
					"\t\t" << movieUpdate->genre <<
					"\t\t" << movieUpdate->language <<
					"\t\t" << movieUpdate->numberofseats <<
					"\t\t" << movieUpdate->releasedate <<
					"\t\t" << movieUpdate->description << endl;
				cout << string(150, '=');
				cout << endl;

				cout << "\nChoose a detail to update:\n";
				cout << "1. Movie Name" << endl;
				cout << "2. Genre" << endl;
				cout << "3. Language" << endl;
				cout << "4. Number of seats" << endl;
				cout << "5. Release date" << endl;
				cout << "6. Movie Description" << endl;
				cout << "7. Back to Menu" << endl;
				cout << "Choice:";
				int updateChoice;
				cin >> updateChoice;

				switch (updateChoice) {

				case 1:
					cout << "New Book Name: ";
					cin.ignore();
					getline(cin, movieUpdate->moviename);
					break;
				case 2:
					cout << "New Genre: ";
					cin >> movieUpdate->genre;
					break;
				case 3:
					cout << "New Language: ";
					cin >> movieUpdate->language;
					break;
				case 4:
					cout << "New Number of Seats: ";
					cin >> movieUpdate->numberofseats;
					while (movieUpdate->numberofseats <= 0) {
						cout << "Number of Seats cannot be less than 1. Please try again! " << endl;
						cout << "New Number of Seats: ";
						cin >> movieUpdate->numberofseats;
					}
					break;
				case 5:
					cout << "New Release Date:";
					cin >> movieUpdate->releasedate;
					break;
				case 6:
					cout << "New Movie Description: ";
					cin >> movieUpdate->description;
					break;
				case 7:
					menuMovie();
					break;
				default:
					cout << "Invalid Selection.\n" << endl;
					menuMovie();
				}
			}
			movieUpdate = movieUpdate->next;
		}

		if (found == false)
		{
			cout << "No record availble with the Movie ID entered.\nPress [1] to try again, Press [2] to exit" << endl;
			int choice;
			cin >> choice;

			switch (choice) {
			case 1:
				updateMovie();
				break;
			case 2:
				menuMovie();
			default:
				cout << "\nInvalid Selection!";
				menuMovie();
			}

		}
	}
}

void sortMoviebyName() {
	struct movie* movieSort = head;
	movie* index = NULL;

	string tempName, tempGenre, tempLanguage, tempRelease, tempDescription;
	int tempID, tempSeat;

	if (head == NULL) {
		cout << "No Record Found!";
	}
	else
	{
		while (movieSort != NULL)
		{
			index = movieSort->next;
			while (index != NULL) {
				if (movieSort->moviename > index->moviename) {
					tempID = movieSort->movieid;
					tempName = movieSort->moviename;
					tempGenre = movieSort->genre;
					tempLanguage = movieSort->language;
					tempSeat = movieSort->numberofseats;
					tempRelease = movieSort->releasedate;
					tempDescription = movieSort->description;

					movieSort->movieid = index->movieid;
					movieSort->moviename = index->moviename;
					movieSort->genre = index->genre;
					movieSort->language = index->language;
					movieSort->numberofseats = index->numberofseats;
					movieSort->releasedate = index->releasedate;
					movieSort->description = index->description;

					index->movieid = tempID;
					index->moviename = tempName;
					index->genre = tempGenre;
					index->language = tempLanguage;
					index->numberofseats = tempSeat;
					index->releasedate = tempRelease;
					index->description = tempDescription;
				}
				index = index->next;
			}
			movieSort = movieSort->next;
		}
	}
	displayMovie();
	cout << endl;
}

void deleteMovie()
{
	movie* current = head;

	if (current == NULL)
	{
		cout << "No Record in the List!\n";
	}
	else
	{
		cout << "Enter Movie ID to delete record:" << endl;
		int deleteID;
		cin >> deleteID;
		cout << endl;
		bool found = false;

		while (current != NULL) {
			if (head->movieid == deleteID) {
				cout << "Deleting movie record with ID " << deleteID << ".\nConfirmation to delete? [Y/N]\n";
				cout << "Choice:";
				char choice;
				cin >> choice;
				cout << endl;

				if (choice == 'Y' || choice == 'y') {
					movie* first = head;
					first = first->next;
					delete head;
					head = first;
					found = true;
					cout << "\nMovie ID " << deleteID << " is deleted.\n";
					break;
				}
				else {
					cout << "Movie is not Deleted!\n";
				}
				found = true;
				break;
			}
			else if (current->next->movieid == deleteID) {
				cout << "Deleting movie record with ID " << deleteID << ".\nConfirmation to delete? [Y/N]\n";
				char choice;
				cout << "Choice:";
				cin >> choice;
				cout << endl;

				if (choice == 'Y' || choice == 'y') {
					movie* before = current;
					movie* deleting = current->next;
					before->next = deleting->next;
					delete deleting;
					found = true;
					cout << "\nMovie ID " << deleteID << " is deleted.\n";
					break;
				}
				else {
					cout << "Movie not Deleted!\n";
				}
				found = true;
				break;
			}
			else {
				current = current->next;
			}
			if (found == false) {
				cout << "No record with the Movie ID entered is found!\nPress [1] to try again. Press [2] to exit" << endl;
				int choice;
				cin >> choice;
				switch (choice) {
				case 1:
					deleteMovie();
				case 2:
					menuMovie();
				default:
					cout << "\nInvalid Selection!";
					menuMovie();
				}
			}
		}
		if (found == false) {
			cout << "No record with the Movie ID entered is found!\nPress [1] to try again. Press [2] to exit" << endl;
			int choice;
			cin >> choice;
			switch (choice) {
			case 1:
				deleteMovie();
			case 2:
				menuMovie();
			default:
				cout << "\nInvalid Selection!";
				menuMovie();
			}
		}
	}

}

//display movie
void displayMovie()
{
	struct movie* temp;  //declaring pointer variable
	temp = head;

	if (temp == NULL) {     //validation to check if there is no record added
		cout << "No Record in the List!\n";
	}
	else {                             //display movie records
		cout << string(150, '=');
		cout << "\n***Movie List***\n";
		cout << "Movie ID\tMovie Name\tGenre\t\tLanguage\tNo of Seats\tRelease date\t\tDescription" << endl;

		while (temp != NULL) //iterate through until pointer holds NULL value
		{
			cout << "" << temp->movieid <<
				"\t\t" << temp->moviename <<
				"\t\t" << temp->genre <<
				"\t\t" << temp->language <<
				"\t\t" << temp->numberofseats <<
				"\t\t" << temp->releasedate <<
				"\t\t" << temp->description << endl;
			temp = temp->next; //traverse through the linked list
		}
		cout << string(150, '=');
		cout << endl;
	}

}

//Menu for Movie Management
void menuMovie() {
	int choice;
	cout << string(150, '=') << endl
		<< "Movie Management Menu" << endl
		<< "1. Add Movie" << endl
		<< "2. Display Movie List" << endl
		<< "3. Search Movie By Movie ID" << endl
		<< "4. Filter Movie By Genre/Category" << endl
		<< "5. Update Movie" << endl
		<< "6. Sort Movie" << endl
		<< "7. Delete Movie" << endl
		<< "8. Back to Main Menu" << endl
		<< "Choice: ";
	cin >> choice;
	cout << string(150, '=');
	cout << endl;
	switch (choice) {
	case 1:
		addMovie();
		cout << endl;
		menuMovie();
	case 2:
		displayMovie();
		cout << endl;
		menuMovie();
	case 3:
		searchMoviebyID();
		cout << endl;
		menuMovie();
	case 4:
		filterMoviebyCategory();
		cout << endl;
		menuMovie();
	case 5:
		updateMovie();
		cout << endl;
		menuMovie();
	case 6:
		sortMoviebyName();
		cout << endl;
		menuMovie();
	case 7:
		deleteMovie();
		cout << endl;
		menuMovie();
	case 8:
		menu();
	default:
		cout << "No choice selected \n" << endl;
		menuMovie();
	}
}

//DECLARING LINKED LIST FOR TRANSACTION
struct ticketInfo {
	string  ticketType, showtime, ticketPrice; //data members
	int quantity, ticketId, Total ,movieId ;
	ticketInfo* link; //next node pointer
};
struct ticketInfo* headPur = NULL; // head pointer initialisation

void loadTicketPurchaseRecord(int ticketId, int movieId, string ticketType, string showtime, string ticketPrice, int quanity, int Total)
{
	ticketInfo* newticket = new ticketInfo;
	newticket->ticketId = ticketId;
	newticket->movieId = movieId;
	newticket->ticketType = ticketType;
	newticket->showtime = showtime;
	newticket->ticketPrice = ticketPrice;
	newticket->quantity = quanity;
	newticket->Total = Total;
	newticket-> link = NULL;

	if (headPur == NULL)
	{
		headPur = newticket;
	}
	else
	{
		newticket->link = headPur; //Big O notation from O(N) become o(1)
		headPur = newticket;
	}
}






//FUNCTION TO ADD PURCHASE
void addTicketPurchase() {
		struct ticketInfo* newticket = new struct ticketInfo;
		struct ticketInfo* checkID;
		checkID = headPur;
		cout << "Enter ticket ID: ";
		cin >> newticket->ticketId; //read ticket value from user
	
		while (checkID != NULL)//validate data
		{
			if (newticket->ticketId == checkID->ticketId) {
				cout << "The ticket id already exist ! Please re-enter the ticket ID: ";
				cin >> newticket->ticketId;
				checkID = headPur;
				while (checkID != NULL) {
					if (newticket->ticketId == checkID->ticketId) {
						cout << "The ticket ID is duplicated! Please re-enter the ticket ID: ";
						cin >> newticket->ticketId;
						checkID = headPur;
					}
					else {
						checkID = checkID->link;
					}
				}
			}
			else {
				checkID = checkID->link;
			}
		}
	
	
		cout << "Movie ID: "; //reading value
		cin >> newticket->movieId;
		while (checkID != NULL) //validation
		{
			if (newticket->movieId== checkID->movieId) {
				cout << "The movie id is duplicated! Please retype id again: ";
				cin >> newticket->movieId;
				checkID = headPur;
				while (checkID != NULL)
				{
					if (newticket->movieId == checkID->movieId) {
						cout << "The movie id is duplicated! Please retype id again : ";
						cin >> newticket->movieId;
						checkID = headPur;
					}
					else {
						checkID = checkID->link;
					}
				}
			}
			else {
				checkID = checkID->link;
	
			}
		}
	
		cout << "Ticket Type [First, Second, Third]: "; //reading value
		cin >> newticket->ticketType;
	
		cout << "Showtime [9am, 12pm, 3pm, 8pm, 12am]: ";
		cin >> newticket->showtime;
	
		cout << "Quantity: "; //reading value
		cin >> newticket->quantity;
	
		cout << "Ticket Price: ";
		cin >> newticket->ticketPrice;
	
		cout << "Total: ";
    	cin >> newticket->Total;
	
		cout << endl;
	
		newticket->link = headPur; //Big O notation from O(N) become o(1)
		headPur = newticket;
	
	}

//FUNCTION TO VIEW PURCHASE
void viewTicketPurchase() {
	struct ticketInfo* display_list;

	display_list = headPur;
	if (display_list == NULL) {
		cout << "No Record Exist in the List yet.!\n";
	}
	else {
		cout << "\n***Purchased List***\n";
		cout << "ticketId\tmovieId\tticketType\t showtime\tticketPrice\tquantity\t Total\n";
		while (display_list != NULL) {
			cout << "" << display_list->ticketId <<
				"\t \t" << display_list->movieId <<
				"\t \t" << display_list->ticketType <<
				"\t " << display_list->showtime <<
				"\t \t " << display_list->ticketPrice <<
				"\t \t \t" << display_list->quantity <<
				"\t " << display_list->Total << endl;

			display_list = display_list->link;
		}
		cout << endl;
	}
}

////FUNCTION TO SORT FOR PURCHASE ACCORDING TO TOTAL
void sortPurchase() {
	struct ticketInfo* sort_purch = headPur;
	ticketInfo* index = NULL;

	
		string tempticketType, tempshowtime ,tempticketPrice;
		int tempticketId, tempmovieId, tempquantity,  tempTotal;
	

	if (headPur == NULL) {
		cout << "No Record in the List Yet!";
	}
	else {
		while (sort_purch != NULL) {
			index = sort_purch->link;
			while (index != NULL) {
				if (sort_purch->Total > index->Total) {
					tempticketId = sort_purch->ticketId;
					tempmovieId = sort_purch->movieId;
					tempticketType = sort_purch->ticketType;
					tempshowtime = sort_purch->showtime;
					tempquantity = sort_purch->quantity;
					tempticketPrice = sort_purch->ticketPrice;
					tempTotal = sort_purch->Total;

					sort_purch->ticketId = index->ticketId;
					sort_purch->movieId = index->movieId;
					sort_purch->ticketType = index->ticketType;
					sort_purch->quantity = index->quantity;
					sort_purch->showtime = index->showtime;
					sort_purch->quantity = index->quantity;
					sort_purch->ticketPrice = index->ticketPrice;
					sort_purch->Total = index->Total;

					index->ticketId = tempticketId;
					index->movieId = tempmovieId;
					index->ticketType = tempticketType;
					index->showtime = tempshowtime;
					index->quantity = tempquantity;
					index->ticketPrice = tempticketPrice;
					index->Total = tempTotal;
				}
				index = index->link;
			}
			sort_purch = sort_purch->link;
		}
		cout << "Purchase List has been Sorted!\n";
		viewTicketPurchase();
		cout << endl;
	}
}

// 
////FUNCTION TO SEARCH FOR PURCHASE BY TICKET ID
void viewTicketPurchaseDetail() {
	struct ticketInfo* search = headPur;
	int tempticketID;
	bool flag;
	flag = false;

	if (search == NULL) {
		cout << " No Record in the List!";
	}
	else
	{
		cout << "Enter Ticket ID: " << endl;
		cin >> tempticketID;
		cout << "ticketId\tmovieId\tticketType\t showtime\tticketPrice\tquantity\t Total\n";
		
		while (search != NULL) {			
			if (search->ticketId == tempticketID) {
				cout << "" << search->ticketId <<
					"\t \t" << search->movieId <<
					"\t \t" << search->ticketType <<
					"\t " << search->showtime <<
					"\t \t " << search->quantity <<
					"\t \t \t" << search->Total <<
					"\t " << search->ticketPrice << endl;

				flag = true;
			}
			search = search->link;
		}
		if (flag==false)
		{
			cout << "No record found. Search again!\nPress [1] to search again, Press [2] to exit" << endl;
			int choice;
			cin >> choice;
			switch (choice) {
			case 1:
				viewTicketPurchaseDetail();
				break;
			case 2:
				menuPurchase();
			default:
				cout << "\nInvalid Selection!";
				menuPurchase();
			}
		}
	}
}
//
//PURCHASE MANAGEMENT MENU
void menuPurchase() {
	int choice;
	cout << "Ticket Purchase Menu" << endl
		<< "1. Add Ticket" << endl
		<< "2. View all Purchased Ticket list" << endl
		<< "3. Sort Purchase list by Total " << endl
		<< "4. Search Purchase Ticket by ID" << endl
		<< "5. Main Menu" << endl
		<< "Choice: ";
	cin >> choice;
	cout << endl;
	switch (choice) {
	case 1:
		addTicketPurchase();
		cout << endl;
		menuPurchase();
	case 2:
		viewTicketPurchase();
		cout << endl;
		menuPurchase();
	case 3:
		sortPurchase();
		cout << endl;
		menuPurchase();
	case 4:
		viewTicketPurchaseDetail();
		cout << endl;
		menuPurchase();
	case 5:
		menu();
	default:
		cout << "Invalid Selection!\n";
		menuPurchase();
	}
	
}

//main menu
void menu()
{
	int choice;
	cout << string(150, '=') << endl
		<< "APU MOVIE TICKET MANAGEMENT SYSTEM MENU" << endl
		<< "1. Movie Management" << endl
		<< "2. Ticket Management" << endl
		<< "3. Exit" << endl
		<< "Choice: ";
	cin >> choice;
	cout << string(150, '=');
	cout << endl;
	switch (choice) {
	case 1:
		menuMovie();
	case 2:
		menuPurchase();
	case 3:
		exit(0);
	default:
		cout << "No choice selected";
		menu();
	}
}

void staffLogin(string username, string password)
{
	if (username == "shar" and password == "123")
	{
		cout << "Welcome " << username << endl;
		cout << endl;
		menu();
	}
	else
	{
		cin.ignore();
		cout << "Wrong credentials is typed! Please try again!" << endl;
		cout << "Username: ";
		getline(cin, username);
		cout << "Password: ";
		getline(cin, password);
		staffLogin(username, password);
	}
}


int main()
{
	//Initialize movie data
	string movielist[3][7] =
	{
		{"1", "Sing 2", "Comedy","English","80","30/12/21","Sing for lives"},
		{"2", "SAO", "Action","Other","60","13/01/22","Adventure of Asuna"},
		{"3", "Scream","Horror","English","80","20/01/22","Murder by Ghostface"}
	};

	head = NULL;


	for (int i = 0; i < 3; i++)
	{
		int id = stoi(movielist[i][0]);
		int seat = stoi(movielist[i][4]);
		loadMovieRecord(id, movielist[i][1], movielist[i][2], movielist[i][3], seat, movielist[i][5], movielist[i][6]);
		
	}

	//Initialize ticket purchase data
	string ticketpurchaselist[3][7] =
	{
		{"1", "1", "First","9am","RM10","2","20"},
		{"2", "2", "Second","3pm","RM8","5","40"},
		{"3", "3","Third","8pm","RM5","4","20"}
	};

	headPur = NULL;

	for (int i = 0; i < 3; i++)
	{
		int ticketid = stoi(ticketpurchaselist[i][0]);
		int movieid = stoi(ticketpurchaselist[i][1]);
		int quantity = stoi(ticketpurchaselist[i][5]);
		int total = stoi(ticketpurchaselist[i][6]);
		loadTicketPurchaseRecord(ticketid, movieid, ticketpurchaselist[i][2], ticketpurchaselist[i][3], ticketpurchaselist[i][4], quantity, total);

	}

	cout << "Welcome to APU MOVIE TICKET MANAGEMENT SYSTEM" << endl;
	string username;
	string password;
	cout << "Username: ";
	getline(cin, username);
	cout << "Password: ";
	getline(cin, password);
	staffLogin(username, password);
	return 0;
}

