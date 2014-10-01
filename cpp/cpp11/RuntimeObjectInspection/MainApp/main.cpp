#include <iostream>
#include <vector>
#include "iterable_object.h"
#include "value_object.h"

using namespace std;

void dump(IObject &obj, int indent = 0)
{
	auto spaces = string(indent, ' ');
	cout << spaces << obj.toString() << endl;
	for (auto &property : obj.getProperties())
	{
		cout << spaces << "- " << property->getName() << ":" << endl;
		dump(*property->getValue(), indent + 2);
	}
}

int main()
{
	Object album("Album");
	album.push_back(new ValueObject<std::string>("Title", "Origin of symmetry"));
	album.push_back(new ValueObject<std::string>("Genre", "Rock"));
	album.push_back(new ValueObject<std::string>("Artist", "Muse"));
	album.push_back(new ValueObject<int>("Year", 2001));

	Object track1("Track");
	track1.push_back(new ValueObject<int>("TrackId", 1));
	track1.push_back(new ValueObject<std::string>("Title", "New Born"));

	Object track2("Track");
	track2.push_back(new ValueObject<int>("TrackId", 2));
	track2.push_back(new ValueObject<std::string>("Title", "Bliss"));

	Object tracks("Tracks");
	tracks.push_back(&track1);
	tracks.push_back(&track2);

	album.push_back(&tracks);

	dump(album);

	//for (auto &trk : album["Tracks"])
	//{

	//}

	try
	{
		cout << album["Year"].toString() << endl;
		cout << track2["Title"].toString() << endl;
	}
	catch (string &eMsg)
	{
		cout << eMsg << endl;
	}

	return 0;
}