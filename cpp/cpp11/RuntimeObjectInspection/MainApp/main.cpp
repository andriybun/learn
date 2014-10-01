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
	album.add(new ValueObject<std::string>("Title", "Origin of symmetry"));
	album.add(new ValueObject<std::string>("Genre", "Rock"));
	album.add(new ValueObject<std::string>("Artist", "Muse"));
	album.add(new ValueObject<int>("Year", 2001));

	Object track1("Track");
	track1.add(new ValueObject<int>("TrackId", 1));
	track1.add(new ValueObject<std::string>("Title", "New Born"));

	Object track2("Track");
	track2.add(new ValueObject<int>("TrackId", 2));
	track2.add(new ValueObject<std::string>("Title", "Bliss"));

	Object tracks("Tracks");
	tracks.add(&track1);
	tracks.add(&track2);
	album.add(&tracks);
	
	dump(album);
	try
	{
		auto trks = &album["Tracks"];
		dump(trks[0]);
	}
	catch (string &eMsg)
	{
		cout << eMsg << endl;
	}
	

	//for (auto &trk : album["Tracks"])
	//{

	//}

	//try
	//{
	//	cout << album["Year"].toString() << endl;
	//	cout << track2["Title"].toString() << endl;
	//}
	//catch (string &eMsg)
	//{
	//	cout << eMsg << endl;
	//}

	return 0;
}