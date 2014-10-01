#pragma once

#include <string>
#include <vector>
#include "track.h"

class Album
{
	std::string title_;
	int year_;
	std::string genre_;
	std::string artist_;
	std::vector<Track> tracks_;
public:
	Album() {};
	~Album() {};

	std::string getTitle() const { return title_; };
	void setTitle(std::string title) { title_ = title; };

	int getYear() const { return year_; };
	void setYear(int year) { year_ = year; };

	std::string getGenre() const { return genre_; };
	void setGenre(std::string genre) { genre_ = genre; };

	std::string getArtist() const { return artist_; };
	void setArtist(std::string artist) { artist_ = artist; };

	std::vector<Track> &getTracks() { return tracks_; };
};

