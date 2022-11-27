#pragma once

#include <string>

class MusicMetadata
{
public:
// Details
	std::string m_title;
	std::string m_artist;
	std::string m_album;
	std::string m_albumArtist;
	std::string m_composer;
	std::string m_genre;
	int m_year;
	int m_track;
	int m_discNumber;
	std::string m_compilation;
	int m_rating;
	int m_playCount;
	std::string m_comments;
	// Artwork
	std::string m_albumArtwork;
	//Sorting

	// title = name{ Space Oddity }
	// sort as Space Oddity
	std::string m_titleSort;

	// album name{ Best of Bowie[UK] Disc 1 }
	// Sort as Best of Bowie[UK] Disc 1
	std::string m_albumSort;

	//Album artist name{ David Bowie }
	// sort as David Bowie
	std::string m_albumArtistSort;

	// Artist name{ David Bowie }
	// sort as David Bowie
	std::string m_artistSort;

	// Composer name{ David Bowie }
	// sort as David Bowie
	std::string m_composerSort;

	//File

	//Media MPEG audio file
	std::string m_media;
	//duration 5:14
	std::string m_duration;
	// size 12.6 Mb
	int m_size;
	// bit rate 320 kbps
	std::string m_bitRate;
	// sample rate 44.100 kHz
	std::string m_sampleRate;
	//channels Joint Stereo
	std::string m_channels;
	// id3 tag v2.3
	std::string m_id3Tag;
	// encoded with Unknown
	std::string m_encodedWith;
	//format MPEG - 1 Layer 3
	std::string m_format;
	// date modified 12 / 05 / 2013 16:33
	time_t m_dateModified;
	// date added 17 / 05 / 2013 00 : 43
	time_t m_dateAdded;
	// Location c : / Music//Macintosh HD/Users/iainferguson/Music/iTunes/iTunes Media/Music/David Bowie
	//						/Best of Bowie [UK] Disc 1/01 Space Oddity.mp3
	std::string m_location;
	std::string m_crc;
	std::string m_sha;
public:
	bool writeXMLFile(const char* path);
};

