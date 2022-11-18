#include <bits/stdc++.h>
using namespace std;

#define dist 50.0000

//Latitude and Longitude of Person
#define lat1d 12.9611159
#define lon1d 77.6362214

#define pi 3.14159265358979323846
#define earth_radius 6371.0

ifstream cafe_list ("cafes.txt");
ofstream out ("output.txt");

double degtorad(double deg)
{
	return ( deg * pi / 180);
}

double distanceBetween(double lat2d, double lon2d)
{				
	double lat1, lon1, lat2, lon2,
		delta_lon, central_ang;

	lat1 = degtorad(lat1d);
	lon1 = degtorad(lon1d);
	lat2 = degtorad(lat2d);
	lon2 = degtorad(lon2d);

	delta_lon = lon2 - lon1;
	
	// math formula
	central_ang = acos ( sin(lat1) *
				sin(lat2) + cos(lat1) *
				cos(lat2) * cos(delta_lon) );
					
	return (earth_radius * central_ang);
}

class FileHandling
{
public:
	long long length, i, j, x, y, m,
				n, f, fi, id[100000];
	
	char latitude[1000],
		longitude[1000],
		id_string[1000], name[1000];
	
	double lat2d, lon2d;
	
	// each line of .txt as string
	string line;

	// check if cafe is near
	void isNear()
	{
		if (distanceBetween(lat2d, lon2d) <= dist)
		{
			//write this differently******************************************
			// Converting id to int format.
			id[i] = atoll(id_string);
			i++;
			out << "user_id: " << id[i - 1] <<
				", name: " << name << endl;
		}
	}

	// Function to read various attributes
	// like latitude, longitude, name , id,
	// etc, from customers.json file. simplistic
	// approach is used to get JSON attributes.
	void file_handler()
	{					
		if (cafe_list.is_open())
		{
			
			while (getline(cafe_list, line))
			{
				
				f = 0; x = 0; y = 0; fi = 0; m = 0, n = 0;
				length = line.size();

				for (j = 0; j < length; j++)
				{
					
					if (line[j] == '"')
						f++;

					else if (line[j] == ':')
						fi++;
						
					// latitude of the location.	
					if (f == 3)
					{
						j++;

						while (line[j] != '"')
						{
							latitude[x] = line[j];
							x++; j++;
						}

						j--; latitude[x] = '\0';
					}
					
					// longitude of the location.
					else if (f == 13)
					{
						j++;

						while (line[j] != '"')
						{
							longitude[y] = line[j];
							y++; j++;
						}

						j--; longitude[y] = '\0';
					}
					
					// To get id of the cafe.
					if (fi == 2)
					{
						j += 2;

						while (line[j] != ',')
						{
							id_string[m] = line[j];
							m++; j++;
						}

						j--; id_string[m] = '\0';
						fi++;
					}
					
					// name of the cafe.
					else if (fi == 4)
					{
						j += 2;

						while (line[j] != ',')
						{
							name[n] = line[j];
							n++; j++;
						}

						j--; name[n] = '\0';
						fi++; f += 2;
					}
				}

				// Converting latitude and longitude
				// in string to float.
				lat2d = atof(latitude);
				lon2d = atof(longitude);
				isNear();
			}
		}
		
		cafe_list.close();
		
		out.close();
	}
};

int main()
{
	// Creating object for file handling
	FileHandling obj;
	
	// reading and finding nearby cafes
	obj.file_handler();

	return 0;
}
