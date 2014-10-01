#pragma once

#include <string>

class Track
{
	int trackId_;
	std::string title_;
public:
	Track(int trackId, std::string title) :
		trackId_(trackId),
		title_(title)
	{ };
	~Track() {};

	int getTrackId() const { return trackId_; };
	void setTrackId(int trackId) { trackId_ = trackId; };

	std::string getTitle() const { return title_; };
	void setTitle(std::string title) { title_ = title; };

};

