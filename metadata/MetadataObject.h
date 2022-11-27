/* **************************************************
**
**    III                DDD  KKK
**    III                DDD  KKK
**                       DDD  KKK
**    III   DDDDDDDDDDD  DDD  KKK            KKK
**    III  DDD           DDD  KKK            KKK
**    III  DDD           DDD  KKK           KKK
**    III  DDD           DDD  KKK        KKKKKK
**    III  DDD           DDD  KKK   KKKKKKKKK
**    III  DDD           DDD  KKK        KKKKKK
**    III  DDD           DDD  KKK           KKK
**    III  DDD           DDD  KKK            KKK
**    III   DDDDDDDDDDDDDDDD  KKK            KKK
**
**
**     SSS         FF
**    S           F   T
**     SSS   OO   FF  TTT W   W  AAA  R RR   EEE
**        S O  O  F   T   W W W  AAAA RR  R EEEEE
**    S   S O  O  F   T   W W W A   A R     E
**     SSS   OO  FFF   TT  W W   AAAA R      EEE
**
**    Copyright: (c) 2015 IDK Software Ltd
**
****************************************************
**
**	Filename	: CRegString.cpp
**	Author		: I.Ferguson
**	Version		: 1.000
**	Date		: 26-05-2015
**
** #$$@@$$# */
#pragma once

#include <string>
#include <vector>
#include <map>
#include "DBDefines.h"
#include "MetaType.h"
#include "FileInfo.h"




namespace simplearchive {


	class MetadataSchema : public MTTableSchema {
	public:
		MetadataSchema() noexcept : MTTableSchema(TABLE_METADATA_PROPERTIES) {

			add(MTSchema(MTType::Text, DB_TITLE));
			add(MTSchema(MTType::Text, DB_ARTIST));
			add(MTSchema(MTType::Text, DB_ALBUM));
			add(MTSchema(MTType::Text, DB_ALBUM_ARTIST));
			add(MTSchema(MTType::Text, DB_COMPOSER));
			add(MTSchema(MTType::Text, DB_GENRE));
			add(MTSchema(MTType::Text, DB_YEAR));
			add(MTSchema(MTType::Text, DB_TRACK));
			add(MTSchema(MTType::Text, DB_DISC_NUMBER));
			add(MTSchema(MTType::Text, DB_COMPILATION));
			add(MTSchema(MTType::Text, DB_RATING));
			add(MTSchema(MTType::Text, DB_PLAY_COUNT));
			add(MTSchema(MTType::Text, DB_COMMENTS));
			// Artwork
			add(MTSchema(MTType::Text, DB_ALBUM_ARTWORK));
			//Sorting

			// title = name{ Space Oddity }
			// sort as Space Oddity
			add(MTSchema(MTType::Text, DB_TITLE_SORT));


			// album name{ Best of Bowie[UK] Disc 1 }
			// Sort as Best of Bowie[UK] Disc 1
			add(MTSchema(MTType::Text, DB_ALBUM_SORT));

			//Album artist name{ David Bowie }
			// sort as David Bowie
			add(MTSchema(MTType::Text, DB_ALBUM_ARTIST_SORT));

			// Artist name{ David Bowie }
			// sort as David Bowie
			add(MTSchema(MTType::Text, DB_ARTIST_SORT));

			// Composer name{ David Bowie }
			// sort as David Bowie
			add(MTSchema(MTType::Text, DB_COMPOSER_SORT));

			//File

			//Media MPEG audio file
			add(MTSchema(MTType::Text, DB_MEDIA));
			//duration 5:14
			add(MTSchema(MTType::Text, DB_DURATION));
			// size 12.6 Mb
			add(MTSchema(MTType::Text, DB_SIZE));
			// bit rate 320 kbps
			add(MTSchema(MTType::Text, DB_BIT_RATE));
			// sample rate 44.100 kHz
			add(MTSchema(MTType::Text, DB_SAMPLE_RATE));
			//channels Joint Stereo
			add(MTSchema(MTType::Text, DB_CHANNELS));
			// id3 tag v2.3
			add(MTSchema(MTType::Text, DB_ID3_TAG));
			// encoded with Unknown
			add(MTSchema(MTType::Text, DB_ENCODED_WITH));
			//format MPEG - 1 Layer 3
			add(MTSchema(MTType::Text, DB_FORMAT));
			// date modified 12 / 05 / 2013 16:33
			add(MTSchema(MTType::Text, DB_DATE_MODIFIED));
			// date added 17 / 05 / 2013 00 : 43
			add(MTSchema(MTType::Text, DB_DATE_ADDED));
			// Location c : / Music//Macintosh HD/Users/iainferguson/Music/iTunes/iTunes Media/Music/David Bowie
			//						/Best of Bowie [UK] Disc 1/01 Space Oddity.mp3
			add(MTSchema(MTType::Text, DB_LOCATION));
			add(MTSchema(MTType::Text, DB_CRC));
			add(MTSchema(MTType::Text, DB_SHA));


		}
	};



	/**
	 * @brief Metadata Container
	 *
	 * This contains the metadata to be substituted during the template process.
	 * As each template is read the contents will be placed into this class. This class
	 * will be used for further substitutions by the Exif reading and user defined
	 * keyword substitutions.
	 */
	class MetadataObject : public MTRow {
		static MetadataSchema m_tableSchema;
		friend class MetadataTemplate;
	public:
		MetadataObject();
		MetadataObject(const MTRow& row) : MTRow(m_tableSchema) {

			for (unsigned int i = 0; i < row.size(); i++) {
				MTColumn& c1 = *at(i);
				MTColumn& c2 = *row.at(i);
				c1 = c2;
			}

		}
		virtual ~MetadataObject();
		bool fromXML(const char* path);
		
		const char* getTitle() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_TITLE_IDX)).toString().c_str();
		}

		void setTitle(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_TITLE_IDX)).fromString(v);;
		}
		
		const char* getArtist() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ARTIST_IDX)).toString().c_str();
		}

		void setArtist(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ARTIST_IDX)).fromString(v);;
		}

		const char* getAlbum() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_IDX)).toString().c_str();
		}

		void setAlbum(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_IDX)).fromString(v);;
		}

		const char* getAlbumArtist() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_ARTIST_IDX)).toString().c_str();
		}

		void setAlbumArtist(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_ARTIST_IDX)).fromString(v);;
		}

		const char* getComposer() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMPOSER_IDX)).toString().c_str();
		}

		void setComposer(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMPOSER_IDX)).fromString(v);;
		}

		const char* getGenre() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_GENRE_IDX)).toString().c_str();
		}

		void setGenre(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_GENRE_IDX)).fromString(v);;
		}

		const char* getYear() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_YEAR_IDX)).toString().c_str();
		}

		void setYear(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_YEAR_IDX)).fromString(v);;
		}

		const char* getTrack() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_TRACK_IDX)).toString().c_str();
		}

		void setTrack(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_TRACK_IDX)).fromString(v);;
		}

		const char* getDiscNumber() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DISC_NUMBER_IDX)).toString().c_str();
		}

		void setDiscNumber(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DISC_NUMBER_IDX)).fromString(v);;
		}

		const char* getCompilation() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMPILATION_IDX)).toString().c_str();
		}

		void setCompilation(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMPILATION_IDX)).fromString(v);;
		}

		const char* getRating() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_RATING_IDX)).toString().c_str();
		}

		void setRating(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_RATING_IDX)).fromString(v);;
		}

		const char* getPlayCount() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_PLAY_COUNT_IDX)).toString().c_str();
		}

		void setPlayCount(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_PLAY_COUNT_IDX)).fromString(v);;
		}

		const char* getComments() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMMENTS_IDX)).toString().c_str();
		}

		void setComments(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMMENTS_IDX)).fromString(v);;
		}
			
		const char* getAlbumArtwork() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_ARTWORK_IDX)).toString().c_str();
		}

		void setAlbumArtwork(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_ARTWORK_IDX)).fromString(v);;
		}

		const char* getTitleSort() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_TITLE_SORT_IDX)).toString().c_str();
		}

		void setTitleSort(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_TITLE_SORT_IDX)).fromString(v);;
		}
			
		const char* getAlbumSort() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_SORT_IDX)).toString().c_str();
		}

		void setAlbumSort(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_SORT_IDX)).fromString(v);;
		}

		const char* getAlbumArtistSort() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_ARTIST_SORT_IDX)).toString().c_str();
		}

		void setAlbumArtistSort(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ALBUM_ARTIST_SORT_IDX)).fromString(v);;
		}
			
		const char* getArtistSort() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ARTIST_SORT_IDX)).toString().c_str();
		}

		void setArtistSort(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ARTIST_SORT_IDX)).fromString(v);;
		}

		const char* getComposerSort() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMPOSER_SORT_IDX)).toString().c_str();
		}

		void setComposerSort(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMPOSER_SORT_IDX)).fromString(v);;
		}

		const char* getSize() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SIZE_IDX)).toString().c_str();
		}

		void setSize(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SIZE_IDX)).fromString(v);;
		}

		const char* getBitRate() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_BIT_RATE_IDX)).toString().c_str();
		}

		void setBitRate(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_BIT_RATE_IDX)).fromString(v);;
		}
			
		const char* getSampleRate() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SAMPLE_RATE_IDX)).toString().c_str();
		}

		void setSampleRate(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SAMPLE_RATE_IDX)).fromString(v);;
		}

		const char* getChannels() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CHANNELS_IDX)).toString().c_str();
		}

		void setChannels(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CHANNELS_IDX)).fromString(v);;
		}

		const char* getId3Tag() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ID3_TAG_IDX)).toString().c_str();
		}

		void setId3Tag(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ID3_TAG_IDX)).fromString(v);;
		}

		const char* getEncodedWith() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ENCODED_WITH_IDX)).toString().c_str();
		}

		void setEncodedWith(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ENCODED_WITH_IDX)).fromString(v);;
		}
			
		const char* getFormat() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_FORMAT_IDX)).toString().c_str();
		}

		void setFormat(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_FORMAT_IDX)).fromString(v);;
		}

		const char* getDateModified() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DATE_MODIFIED_IDX)).toString().c_str();
		}

		void setDateModified(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DATE_MODIFIED_IDX)).fromString(v);;
		}

		const char* getDateAdded() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DATE_ADDED_IDX)).toString().c_str();
		}

		void setDateAdded(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DATE_ADDED_IDX)).fromString(v);;
		}

		const char* getLocation() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_LOCATION_IDX)).toString().c_str();
		}

		void setLocation(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_LOCATION_IDX)).fromString(v);;
		}
			
		const char* getCRC() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CRC_IDX)).toString().c_str();
		}

		void setCRC(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CRC_IDX)).fromString(v);;
		}

		const char* getSHA() const {
			return columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SHA_IDX)).toString().c_str();
		}

		void setSHA(const std::string& v) {
			columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SHA_IDX)).fromString(v);;
		}
			
	};
};
