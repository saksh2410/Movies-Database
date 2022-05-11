#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <string.h>
#include <cstdio>

using namespace std;

class Movie
{

		int   movieId;
		char  name[50];
		char  leadActorName[50];
		char  directorName[50];
		int   releaseYear;
		float rating;
		char  language[20];

	public:
	void getData ()
	{
		cout <<"Movie ID     : ";
		cin >> movieId;
		cout <<"Name         : ";
		cin.ignore();
		gets(name);
		cout <<"Actor Name   : ";
		gets(leadActorName);
		cout <<"Director Name: ";
		gets(directorName);
		cout << "Release Year: ";
		cin >> releaseYear;
		cout << "Rating      : ";
		cin >> rating;
		cout << "Language    : ";
		cin.ignore();
		gets(language);
	}

	void display ()
	{
		cout << "\nMovie ID    : " << movieId;
		cout << "\nName        : " << name;
		cout << "\nLead Actor  : " << leadActorName;
		cout << "\nDirector    : " << directorName;
		cout << "\nRelease Year: " << releaseYear;
		cout << "\nRating      : " << rating;
		cout << "\nLanguage    : " << language<<endl;
	}

	int getMovieId ()
	{
		return movieId;
	}

	char* getName ()
	{
		return (name);
	}
	int getReleaseYear ()
	{
		return releaseYear;
	}

	float getRating ()
	{
		return rating;
	}
};


void create ()
{
	Movie m;
	int ctr = 1;
	char ans;
	fstream file;
	file.open ("movies.dat", ios::out | ios::binary);
	do
	{   cout << "Please Provide Movie Details ("<<ctr++ << ")"<<endl;
		m.getData ();
		file.write ((char*)&m, sizeof(m));
		cout << "\n\nDo you want to enter another Movie (y/n) - ";
		cin >> ans;
	} while (ans == 'y' || ans == 'Y');
	file.close ();
}


void showFile ()
{
	int ctr = 1;
	fstream file;
	Movie m;

	file.open ("movies.dat", ios::in | ios::binary);
	while (file.read ((char*)&m, sizeof(m)))
	{
		cout << "\n================ Movie (" << ctr++ << ") =================";
		m.display ();
	}
	file.close ();
}

void append ()
{
	char ans;
	fstream file;
	Movie m;

	file.open ("movies.dat", ios::app | ios::binary);
	do
	{
		m.getData ();
		file.write ((char*)&m, sizeof(m));
		cout << "\n\nDo you want to enter another Movie (y/n) - ";
		cin >> ans;
	}
	while (ans == 'y' || ans == 'Y');
	file.close ();
}




void insertAtFirst ()
{
	fstream file1,file2;
	Movie m;

	// open temp file in append mode and
	// write new movies directly to it
	file1.open ("movies.tmp", ios::out | ios::binary);
	m.getData ();
	file1.write ((char*)&m, sizeof(m));



	// now read movies in the original file
	// and append them into temp file
	file2.open ("movies.dat", ios::in | ios::binary);
	while (file2.read ((char*)&m, sizeof(m)))
	{
		file1.write ((char*)&m, sizeof (m));
	}
	file1.close ();
	file2.close ();

	remove ("movies.dat");
	rename ("movies.tmp", "movies.dat");
}


void insertAtNth ()
{
	int pos;
	cout << "Please enter the record at which you want to insert > ";
	cin >> pos;

	Movie m;
	int counter = 0;
	fstream file1, file2;
	file1.open ("movies.dat", ios::in | ios::binary);
	file2.open ("new-movies.dat", ios::out | ios::binary);
	while (file1.read ((char*)&m, sizeof(m)))
	{
		++counter;
		if (counter == pos)
		{
			Movie m2;
			m2.getData ();
			file2.write ((char*)&m2, sizeof (m2));
		}

		file2.write ((char*)&m, sizeof (m));
	}

	file1.close ();
	file2.close ();

	remove ("movies.dat");
	rename ("new-movies.dat", "movies.dat");
}




void search ()
{
	int choice;


	// get user's option
	cout << "Search according to "<<endl;
	cout << "1. Id " << endl;
	cout << "2. Release Year "<<endl;
	cout << "3. Rating " << endl;
	cout << "4. Name " << endl;
	cin >> choice;


	fstream file;
	Movie m;
	int found = 0;

	switch (choice)
	{
		case 1:
			// search By Id
			file.open ("movies.dat", ios::in | ios::binary);
			int mId;
			cout << "Enter Movie Id to Search: ";
			cin >> mId;
			while (file.read((char*) &m, sizeof (m)))
			{
				if (m.getMovieId () == mId)
				{
					found++;
					cout << "Movie with Id = " << mId << " Found"<<endl;
					m.display ();
				}
			}

			if (found == 0)
				cout << "Movie with Id = " << mId << " Not Found" << endl;

			file.close ();
			break;
		case 2:
			//  searchByYear ();
			file.open ("movies.dat", ios::in | ios::binary);

			int movRelYear;
			cout << "Release Year to search: ";
			cin >> movRelYear;
			while (file.read((char*) &m, sizeof (m)))
			{
				if (m.getReleaseYear () == movRelYear)
				{
					found++;
					m.display ();
				}
			}

			// If no search result found, show message
			if (found == 0)
				cout << "No Movie was released in year " << movRelYear << endl;

			file.close ();
			break;
		case 3:
			// searchByRating ();
			file.open ("movies.dat", ios::in | ios::binary);

			float movRating;
			cout << "Find Movies with Rating >= ";
			cin >> movRating;
			while (file.read((char*) &m, sizeof (m)))
			{
				if (m.getRating () >= movRating)
				{
					found++;
					m.display ();
				}
			}

			// If no search result found, show message
			if (found == 0)
				cout << "No Movie had Ratings >= " << movRating << endl;

			file.close ();
			break;
		case 4:
			// searchByName ();
			// open the file stream
			file.open ("movies.dat", ios::in | ios::binary);

			char movName[50];
			cout << "Movie Name to search: ";
			cin.ignore();
			gets (movName);

			while (file.read((char*) &m, sizeof (m)))
			{
				if (strcmp(movName,m.getName())==0)
				{
					found++;
					m.display ();
				}
			}

			// If no search result found, show message
			if (found == 0)
				cout << "No Movie found for Name: (" << movName << ")" << endl;

			file.close ();
			break;
		default:
			cout << "Invalid Search Choice"<<endl;
			break;
	}
}

void editMovie ()
{
	Movie m;
	int recordNumber;
	int counter = 1;

	cout << "\nEnter Record Number to Edit - ";
	cin >> recordNumber;

	fstream file;
	fstream newFile;

	file.open ("movies.dat", ios::in | ios::binary);
	newFile.open ("new-movies.dat", ios::out | ios::binary);


	// read from one file and write to temp file
	while (file.read ((char*)&m, sizeof (m)))
	{
		// Read the Movie Again for specified Record
		if (counter++ == recordNumber)
		{
			cout << "Enter Updated Details "<<endl;
			m.getData ();
		}

		newFile.write ((char*)&m, sizeof(m));
	}

	// close both files
	newFile.close ();
	file.close ();

	remove ("movies.dat");
	rename ("new-movies.dat", "movies.dat");
	cout << "Done. "<<endl;
}


void sortByYear ()
{
	// open the file stream
	fstream file;
	file.open ("movies.dat", ios::in | ios::binary);


	int counter = 0;
	Movie m,tempMovie;
	Movie allMovies[50];
	while (file.read ((char*)&m, sizeof (m)))
		allMovies[counter++] = m;

	cout << "Sorting " << counter << " Movies by Release Year"<<endl;
	for (int i=0; i<counter-1; ++i)
	{
		for (int j=0; j<(counter-1)-i; ++j)
		{
			if (allMovies[j].getReleaseYear() > allMovies[j+1].getReleaseYear ())
			{
				tempMovie = allMovies[j];
				allMovies[j] = allMovies[j+1];
				allMovies[j+1] = tempMovie;
			}
		}
	}

	// close and delete the existing file
	file.close ();
	remove ("movies.dat");

	// write the sorted array back into the file
	file.open ("movies.dat", ios::out | ios::binary);
	for (int c=0; c<= (counter-1); c++)
		file.write ((char*)&allMovies[c], sizeof (allMovies[c]));

	// close the file
	file.close ();
	cout << "Done." <<endl;

	// show the sorted data
	showFile ();
}


void sortByRating ()
{
	// open the file stream
	fstream file;
	file.open ("movies.dat", ios::in | ios::binary);


	int counter = 0;
	Movie m,tempMovie;
	Movie allMovies[50];
	while (file.read ((char*)&m, sizeof (m)))
		allMovies[counter++] = m;

	cout << "Sorting " << counter << " Movies by Rating"<<endl;
	for (int i=0; i<counter-1; ++i)
	{
		for (int j=0; j<(counter-1)-i; ++j)
		{
			if (allMovies[j].getRating() > allMovies[j+1].getRating ())
			{
				tempMovie = allMovies[j];
				allMovies[j] = allMovies[j+1];
				allMovies[j+1] = tempMovie;
			}
		}
	}

	// close and delete the existing file
	file.close ();
	remove ("movies.dat");

	// write the sorted array back into the file
	file.open ("movies.dat", ios::out | ios::binary);
	for (int c=0; c<= (counter-1); c++)
		file.write ((char*)&allMovies[c], sizeof (allMovies[c]));

	// close the file
	file.close ();
	cout << "Done." <<endl;

	// show sorted data
	showFile ();
}

void countNumberOfMovies ()
{
	// open the file stream
	fstream file;
	file.open ("movies.dat", ios::in | ios::binary);


	int counter = 0;
	Movie m,tempMovie;
	Movie allMovies[50];
	while (file.read ((char*)&m, sizeof (m)))
		allMovies[counter++] = m;

	cout << "Found " << counter << " Movie Record(s)" << endl;
	file.close ();
}


void deleteFirstRecord ()
{
	Movie m;
	fstream file1, file2;
	file1.open ("movies.dat", ios::in | ios::binary);
	file2.open ("new-movies.dat", ios::out | ios::binary);

	file1.read ((char*)&m, sizeof(m));
	while (file1.read ((char*)&m, sizeof(m)))
	{
		file2.write ((char*)&m, sizeof (m));
	}

	file1.close ();
	file2.close ();

	remove ("movies.dat");
	rename ("new-movies.dat", "movies.dat");

}



void deleteLastRecord ()
{
	Movie m;
	fstream file1, file2;
	file1.open ("movies.dat", ios::in | ios::binary);
	file1.seekg(0, ios::end);

	int lp = file1.tellg();
	int size = sizeof (m);
	int noOfMovies = lp/size;


	file2.open ("new-movies.dat", ios::out | ios::binary);
	int counter = 0;

	file1.seekg (0);
	while (file1.read ((char*)&m, sizeof(m)))
	{
		++counter;
		if (counter != noOfMovies)
			file2.write ((char*)&m, sizeof (m));
		else
			cout << "Deleted Last Record"<< endl;
	}

	file1.close ();
	file2.close ();

	remove ("movies.dat");
	rename ("new-movies.dat", "movies.dat");
}



void deleteNthRecord ()
{
	int pos;
	cout << "Please enter the record which you want to delete > ";
	cin >> pos;


	Movie m;
	fstream file1, file2;
	file1.open ("movies.dat", ios::in | ios::binary);


	file2.open ("new-movies.dat", ios::out | ios::binary);
	int counter = 0;

	while (file1.read ((char*)&m, sizeof(m)))
	{
		++counter;
		if (counter != pos)
		{
			file2.write ((char*)&m, sizeof (m));
		} else
		{
			cout << "Deleted Record " << endl;
		}
	}

	file1.close ();
	file2.close ();

	remove ("movies.dat");
	rename ("new-movies.dat", "movies.dat");
}


void deleteMovieId ()
{
	int mId;
	cout << "Please enter the Movie Id which you want to delete > ";
	cin >> mId;


	Movie m;
	fstream file1, file2;
	file1.open ("movies.dat", ios::in | ios::binary);


	file2.open ("new-movies.dat", ios::out | ios::binary);
	int counter = 0;

	while (file1.read ((char*)&m, sizeof(m)))
	{
		++counter;
		if (m.getMovieId () != mId)
		{
			file2.write ((char*)&m, sizeof (m));
		} else
		{
			cout << "Deleted: " << mId;
		}
	}

	file1.close ();
	file2.close ();

	remove ("movies.dat");
	rename ("new-movies.dat", "movies.dat");
}

int main ()
{
	int choice;
	char showMenu;

	do
	{
		system("cls");
		cout << "Menu ..." << endl;
		cout << "1. Create Movies and Store them in File" << endl;
		cout << "2. Read all Movies from the file"<< endl;
		cout << "3. Insert Movies at the end of File"<<endl;
		cout << "4. Insert Record at the start of File"<< endl;
		cout << "5. Insert a Movie at Nth position of File" << endl;
		cout << "6. Search Movie"<<endl;
		cout << "7. Edit Movie"<<endl;
		cout << "8. Sort by Release Year " << endl;
		cout << "9. Sort by Rating " << endl;
		cout << "10. Count Total Records"<< endl;
		cout << "11. Delete First Record" << endl;
		cout << "12. Delete Last Record" << endl;
		cout << "13. Delete at Nth Record" << endl;
		cout << "14. Delete on the basis of Movie Id"<< endl;
		cout << "\nEnter your choice: ";
		cin >> choice;

		switch (choice)
		{
			case 1:
				create ();
				break;
			case 2:
				showFile ();
				break;
			case 3:
				append ();
				break;
			case 4:
				insertAtFirst ();
				break;
			case 5:
				insertAtNth ();
				break;
			case 6:
				search ();
				break;
			case 7:
				editMovie ();
				break;
			case 8:
				sortByYear ();
				break;
			case 9:
				sortByRating ();
				break;
			case 10:
				countNumberOfMovies ();
				break;
			case 11:
				deleteFirstRecord ();
				break;
			case 12:
				deleteLastRecord ();
				break;
			case 13:
				deleteNthRecord ();
				break;
			case 14:
				deleteMovieId ();
				break;
			default:
				cout << "Invalid Choice"<< endl;
				break;
		}

		cout << "\nDo you want to go back to Main Menu (y/n) ";
		cin >> showMenu;
	} while (showMenu == 'y');

	cout << "\n\nThank you !!!!"<< endl;
	getch ();
	return 0;
}
