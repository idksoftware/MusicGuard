#include "MusicMetadata.h"
#include "WriteXML.h"
#include <sstream>
#include <iostream>
#include <fstream>

bool MusicMetadata::writeXMLFile(const char* path) {
	/*
	std::ofstream xmlFile;
	xmlFile.open(path);
	xmlFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
		<< "<Group>\n";
	//<< writeTag("GroupName", group.getName());

	
		xmlFile << "<MusicTrack>\n"
			<< writeTag("SequenceId", sideCarItem.getSequenceId().c_str())
			<< writeTag("Filename", sideCarItem.getFilename().c_str())
			<< writeTag("Filepath", sideCarItem.getFilepath().c_str())
			<< writeTag("UniqueId", sideCarItem.getUniqueId().c_str())
			<< writeTag("Sha256", sideCarItem.getSha().c_str())
			<< writeTag("Crc", sideCarItem.getCrc().c_str())

			m_title;
		m_artist;
		m_album;
		m_albumArtist;
		m_composer;
		m_genre;
		m_year;
		m_track;
		m_discNumber;
		m_compilation;
		m_rating;
		m_playCount;
		m_comments;
		// Artwork
		m_albumArtwork;
		//Sorting

		m_titleSort;

		m_albumSort;

		m_albumArtistSort;

		m_artistSort;

		m_composerSort;

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

			<< "</MusicTrack>\n";

	}
	xmlFile << "<Group>\n";


	xmlFile.close();
	*/
	return true;

}
