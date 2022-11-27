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
**	Filename	: DBDefines.h
**	Author		: I.Ferguson
**	Version		: 1.000
**	Date		: 26-05-2015
**
** #$$@@$$# */

#pragma once
/**
 * This file defines the key strings used by the Archiver. This allows consistent
 * key names to be used in the application.
 */

//namespace simplearchive {

#define TABLE_ASSET_PROPERTIES		"AssetProperties"
#define TABLE_CAMERA_INFORMATION	"CameraInformation"
#define TABLE_MEDIA_PROPERTIES		"MediaProperties"
#define TABLE_COPYRIGHT_PROPERTIES	"CopyrightProperties"
#define TABLE_GPS_PROPERTIES		"GPSProperties"
#define ROW_BASIC_EXIF				"BasicMetadata"
#define ROW_EXTERNAL_EXIF			"ExternalExif"


#define TABLE_METADATA_PROPERTIES		"MetadataProperties"
#define TABLE_DERIVATIVE_METADATA		"DerivativeMetadata"
#define TABLE_METADATA_TEMPLATE			"MetadataTemplate"
#define TABLE_DERIVATIVE_TEMPLATE		"DerivativeTemplate"
#define TABLE_PRIMARY_INDEX				"PrimaryIndex"
#define TABLE_DERIVATIVE_INDEX			"DerivativeIndex"
#define TABLE_MASTER_INDEX				"MasterIndex"

#define TABLE_SYSTEM_HISTORY			"SystemHistory"
#define TABLE_IMAGE_HISTORY				"ImageHistory"

#define TABLE_HASH_TAG_INDEX			"HashTagIndex"

/*
 * These are used by BasicMetadata
 */
enum class BasicMetadataIndex {
	BM_FILENAME_IDX,
	BM_ORGINALNAME_IDX,
	BM_FILEPATH_IDX,
	BM_CRC_IDX,
	BM_MD5_IDX,
	BM_UUID_IDX,

	BM_MEDIATYPE_IDX,
	BM_FILESIZE_IDX,
	BM_DATEMODIFIED_IDX,
	BM_DATECREATE_IDX,
	BM_DATEADDED_IDX,

	BM_LABEL_IDX,
	BM_TITLE_IDX,
	BM_SUBJECT_IDX,
	BM_RATING_IDX,
	BM_RATINGPERCENT_IDX,
	BM_DESCRIPTION_IDX,
	BM_KEYWORDS_IDX,
	BM_VERSION_IDX,

	BM_COMMENT_IDX,
	BM_AUTHOR_IDX,
	BM_CAPTUREDATE_IDX,
	BM_SUBSETIMEORIGINAL_IDX,
	BM_COPYRIGHT_IDX,

	BM_WIDTH_IDX,
	BM_HEIGHT_IDX,
	BM_VIEWROTATION_IDX,
	BM_XRESOLUTION_IDX,
	BM_YRESOLUTION_IDX,
	BM_RESOLUTIONUNIT_IDX,

	BM_MAKER_IDX,
	BM_MODEL_IDX,
	BM_EXPOSURETIME_IDX,
	BM_APERTURE_IDX,
	BM_ISOSPEEDRATING_IDX,
	BM_EXPOSUREBIAS_IDX,
	BM_EXPOSUREPROGRAM_IDX,
	BM_SUBJECTDISTANCE_IDX,
	BM_FOCALLENGTH_IDX,
	BM_FOCALLENGTHIN35MM_IDX,
	BM_FLASH_IDX,
	BM_METERINGMODE_IDX,
	BM_DIGITALZOOM_IDX,

	BM_LIGHTSOURCE_IDX,
	BM_COLORSPACE_IDX,
	BM_WHITEBALANCE_IDX,
	BM_SCENECAPTURETYPE_IDX,
	BM_CONTRAST_IDX,
	BM_SATURATION_IDX,
	BM_SHARPNESS_IDX,
	BM_BRIGHTNESSVALUE_IDX,
	BM_SUBJECTDISTANCERANGE_IDX,
	BM_MAXAPERTURE_IDX,
	BM_COMPRESSION_IDX,
	BM_BITSPERSAMPLE_IDX,
	BM_COMPRESSEDBITSPERPIXEL_IDX,
	BM_FLASHENERGY_IDX,
	BM_EXIFVERSION_IDX,
	BM_SOFTWARE_IDX,
	BM_PHOTOMETRICINTERPRETATION_IDX,

	BM_LATITUDE_IDX,
	BM_LONGITUDE_IDX,
	BM_GPSTIMESTAMP_IDX
};

/*
 * These are used by MetadataObject
 */

enum class MetadataObjectIndex {

	MD_TITLE_IDX,
	MD_ARTIST_IDX,
	MD_ALBUM_IDX,
	MD_ALBUM_ARTIST_IDX,
	MD_COMPOSER_IDX,
	MD_GENRE_IDX,
	MD_YEAR_IDX,
	MD_TRACK_IDX,
	MD_DISC_NUMBER_IDX,
	MD_COMPILATION_IDX,
	MD_RATING_IDX,
	MD_PLAY_COUNT_IDX,
	MD_COMMENTS_IDX,
	MD_ALBUM_ARTWORK_IDX,
	MD_TITLE_SORT_IDX,
	MD_ALBUM_SORT_IDX,
	MD_ALBUM_ARTIST_SORT_IDX,
	MD_ARTIST_SORT_IDX,
	MD_COMPOSER_SORT_IDX,
	MD_MEDIA_IDX,
	MD_DURATION_IDX,
	MD_SIZE_IDX,
	MD_BIT_RATE_IDX,
	MD_SAMPLE_RATE_IDX,
	MD_CHANNELS_IDX,
	MD_ID3_TAG_IDX,
	MD_ENCODED_WITH_IDX,
	MD_FORMAT_IDX,
	MD_DATE_MODIFIED_IDX,
	MD_DATE_ADDED_IDX,
	MD_LOCATION_IDX,
	MD_CRC_IDX,
	MD_SHA_IDX,

	/*
	MD_SEQUENCEID_IDX,	// *
	MD_FILENAME_IDX,
	MD_ORGINALNAME_IDX,
	MD_FILEPATH_IDX,
	MD_UUID_IDX,

	MD_MEDIATYPE_IDX,
	MD_SHA_IDX,
	MD_CRC_IDX,
	MD_FILESIZE_IDX,
	MD_DATECREATE_IDX,
	MD_DATEMODIFIED_IDX,
	MD_DATEADDED_IDX,
		// Description
	MD_DESCRIPTION_IDX,
	MD_LABEL_IDX,
	MD_TITLE_IDX,
	MD_SUBJECT_IDX,
	MD_RATING_IDX,
	MD_RATINGPERCENT_IDX,
	MD_TAGS_IDX,// template
	MD_KEYWORDS_IDX,// template
	MD_VERSION_IDX,// template
		// Origin
	MD_COMMENT_IDX,// template
	MD_AUTHOR_IDX,
	MD_CAPTUREDATE_IDX,
	MD_SUBSETIMEORIGINAL_IDX,
	MD_COPYRIGHT_IDX,
		// Image
	MD_WIDTH_IDX,
	MD_HEIGHT_IDX,
	MD_VIEWROTATION_IDX,
	MD_BITSPERSAMPLE_IDX,
	MD_XRESOLUTION_IDX,
	MD_YRESOLUTION_IDX,
	MD_RESOLUTIONUNIT_IDX,
	MD_COMPRESSION_IDX,
		// Camera
	MD_MAKER_IDX,
	MD_MODEL_IDX,
	MD_EXPOSURETIME_IDX,
	MD_APERTURE_IDX,
	MD_ISOSPEEDRATING_IDX,
	MD_EXPOSUREBIAS_IDX,
	MD_EXPOSUREPROGRAM_IDX,
	MD_SUBJECTDISTANCE_IDX,
	MD_FOCALLENGTH_IDX,
	MD_FOCALLENGTHIN35MM_IDX,
	MD_FLASH_IDX,
	MD_METERINGMODE_IDX,
	MD_DIGITALZOOM_IDX,
		// Advanced photo
	MD_LIGHTSOURCE_IDX,
	MD_COLORSPACE_IDX,
	MD_WHITEBALANCE_IDX,
	MD_SCENECAPTURETYPE_IDX,
	MD_CONTRAST_IDX,
	MD_SATURATION_IDX,
	MD_SHARPNESS_IDX,
	MD_BRIGHTNESSVALUE_IDX,
	MD_SUBJECTDISTANCERANGE_IDX,
	MD_MAXAPERTURE_IDX,
	MD_COMPRESSEDBITSPERPIXEL_IDX,
	MD_FLASHENERGY_IDX,
	MD_EXIFVERSION_IDX,
	MD_SOFTWARE_IDX,
	MD_PHOTOMETRICINTERPRETATION_IDX,
	MD_GPSTIMESTAMP_IDX,


		//	add(MTSchema(MTType::Text, DB_SENSINGMETHOD));

		// Location
	MD_LATITUDE_IDX,
	MD_LONGITUDE_IDX,
	MD_LOCATION_IDX,
	MD_SCENE_IDX,// template

		// IPTC
	MD_SOURCEURL_IDX,			// template
	MD_USAGERIGHTS_IDX,// template
	MD_COPYRIGHTURL_IDX,// template
	MD_HEADLINE_IDX,// template
	MD_CATEGORY_IDX,// template
	MD_SOURCE_IDX,// template
	MD_INSTRUCTIONS_IDX,// template

	MD_CREATOR_IDX,// template
	MD_JOBTITLE_IDX,// template
	MD_ADDRESS_IDX,// template
	MD_CITY_IDX,// template
	MD_STATE_IDX,// template
	MD_POSTALCODE_IDX,// template
	MD_COUNTRY_IDX,// template
	MD_PHONE_IDX,// template
	MD_EMAIL_IDX,// template
	MD_WEBSITE_IDX// template
	*/
};



enum class PrimaryIndexIndex {
	PI_SEQUENCEID_IDX,// template
	PI_SHORTIMAGEPATH_IDX,
	PI_FILENAME_IDX,
	PI_FILESIZE_IDX,
	PI_CRC_IDX,
	PI_MD5_IDX,
	PI_UUID_IDX,
	PI_VERSION_IDX,// template
	PI_DATEADDED_IDX,
	PI_DATABASEID_IDX,
};

enum class SystemHistoryIdx {
	SH_DATEADDED_IDX,
	SH_FILEPATH_IDX,
	SH_VERSION_IDX,
	SH_EVENT_IDX,
	SH_COMMENT_IDX
};

#define DB_TITLE "Title"
#define DB_ARTIST "Artist"
#define DB_ALBUM "Album"
#define DB_ALBUM_ARTIST "AlbumArtist"
#define DB_COMPOSER "Composer"
#define DB_GENRE "Genre"
#define DB_YEAR "Year"
#define DB_TRACK "Track"
#define DB_DISC_NUMBER "DiscNumber"
#define DB_COMPILATION "Compilation"
#define DB_RATING "Rating"
#define DB_PLAY_COUNT "PlayCount"
#define DB_COMMENTS "Comments"
#define DB_ALBUM_ARTWORK "AlbumArtwork"
#define DB_TITLE_SORT "TitleSort"
#define DB_ALBUM_SORT "AlbumSort"
#define DB_ALBUM_ARTIST_SORT "AlbumArtistSort"
#define DB_ARTIST_SORT "ArtistSort"
#define DB_COMPOSER_SORT "ComposeRSort"
#define DB_MEDIA "Media"
#define DB_DURATION "Duration"
#define DB_SIZE "Size"
#define DB_BIT_RATE "BitRate"
#define DB_SAMPLE_RATE "SampleRate"
#define DB_CHANNELS "Channels"
#define DB_ID3_TAG "Id3Tag"
#define DB_ENCODED_WITH "EncodedWith"
#define DB_FORMAT "Format"
#define DB_DATE_MODIFIED "DateModified"
#define DB_DATE_ADDED "DateAdded"
#define DB_LOCATION "Location"
#define DB_CRC "CRC"
#define DB_SHA "SHA"

#define DB_DATEADDED					"DateAdded"
#define DB_FILENAME					"DateAdded"
#define DB_FILEPATH					"FilePath"
#define DB_EVENT					"DateAdded"
#define DB_VERSION					"Version"
#define DB_COMMENT					"Comment"

//namespace simplearchive {
/*
#define DB_SEQUENCEID					"SequenceId"	// Sequence ID of this index
#define DB_DATABASEID					"DatabaseId" // Sequence ID of linked database
#define DB_SHA							"Sha256"
#define DB_CRC							"Crc"
#define DB_FILENAME						"Filename"
#define DB_ORGINALNAME					"OrginalName"
#define DB_UUID							"Uuid"
#define DB_DESCRIPTION					"Description"
#define DB_APERTURE						"Aperture"
#define DB_CAPTUREDATE					"CaptureDate"
#define DB_COLORSPACE					"ColorSpace"
#define DB_COMPRESSION					"Compression"
#define DB_COPYRIGHT					"Copyright"
#define DB_COPYRIGHTURL					"CopyrightUrl"
#define DB_DATEADDED					"DateAdded"
#define DB_DATECREATE					"DateCreate"
#define DB_DATEMODIFIED					"DateModified"
#define DB_WHITEBALANCE					"WhiteBalance"
#define DB_DIGITALZOOM					"DigitalZoom"
#define DB_EXIFVERSION					"ExifVersion"
#define DB_EXPOSUREBIAS					"ExposureBias"
#define DB_EXPOSUREPROGRAM				"ExposureProgram"
#define DB_EXPOSURETIME					"ExposureTime"
#define DB_FILEPATH						"Filepath"
#define DB_FILESIZE						"FileSize"
#define DB_FLASH						"Flash"
#define DB_FOCALLENGTH					"FocalLength"
#define DB_GPSTIMESTAMP					"GpsTimeStamp"
#define DB_HEIGHT						"Height"
#define DB_ISOSPEEDRATING				"IsoSpeedRating"
#define DB_LABEL						"Label"
#define DB_LATITUDE						"Latitude"
#define DB_LIGHTSOURCE					"LightSource"
#define DB_LONGITUDE					"Longitude"
#define DB_MAKER						"Maker"
#define DB_MEDIATYPE					"MediaType"
#define DB_METERINGMODE					"MeteringMode"
#define DB_MODEL						"Model"
#define DB_RATING						"Rating"
#define DB_RESOLUTION					"Resolution"
#define DB_SAMPLECOLOR					"SampleColor"
#define DB_SENSINGMETHOD				"SensingMethod"
#define DB_SOFTWARE						"Software"
#define DB_SOURCEURL					"SourceUrl"
#define DB_USAGERIGHTS					"UsageRights"
#define DB_VIEWROTATION					"ViewRotation"
#define DB_WIDTH						"Width"
#define	DB_KEYWORDS						"Keywords"
#define	DB_TAGS							"Tags"
#define DB_HEADLINE						"Headline"
#define DB_CATEGORY						"Category"
#define DB_SOURCE						"Source"
#define DB_INSTRUCTIONS					"Instructions"
#define DB_SCENE						"Scene"
#define DB_CREATOR						"Creator"
#define DB_JOBTITLE						"JobTitle"
#define DB_ADDRESS						"Address"
#define DB_CITY							"City"
#define DB_STATE						"State"
#define DB_POSTALCODE					"PostalCode"
#define DB_COUNTRY						"Country"
#define DB_PHONE						"Phone"
#define DB_EMAIL						"Email"
#define DB_WEBSITE						"Website"
#define DB_TITLE						"Title"
#define DB_SUBJECT						"Subject"
#define DB_RATINGPERCENT				"RatingPercent"
#define DB_COMMENT						"Comment"
#define DB_AUTHOR						"Author"
#define DB_SUBSETIMEORIGINAL			"SubsetTimeOriginal"
#define DB_XRESOLUTION					"XResolution"
#define DB_YRESOLUTION					"YResolution"
#define DB_RESOLUTIONUNIT				"ResolutionUnit"
#define DB_SUBJECTDISTANCE				"SubjectDistance"
#define DB_FOCALLENGTHIN35MM			"FocalLenghtIn35mm"
#define DB_WHITESBALANCE				"WhitesBalance"
#define DB_SCENECAPTURETYPE				"SceneCaptureType"
#define DB_CONTRAST						"Contrast"
#define DB_SATURATION					"Saturation"
#define DB_SHARPNESS					"Sharpness"
#define DB_BRIGHTNESSVALUE				"BrightnessValue"
#define DB_SUBJECTDISTANCERANGE			"SubjectDistanceRange"
#define DB_MAXAPERTURE					"MaxAperture"
#define DB_BITSPERSAMPLE				"BitsPerSample"
#define DB_COMPRESSEDBITSPERPIXEL		"CompressedBitsPerPixel"
#define DB_FLASHENERGY					"FlashEnergy"
#define DB_PHOTOMETRICINTERPRETATION	"PhotometricInterpretation"
#define DB_LOCATION						"Location"
#define DB_VERSION						"Version"
#define DB_EDITOR						"EditorSoftware"
#define DB_VERSIONPATH					"VersionPath"
#define DB_EVENT						"Event"
#define DB_SHORTIMAGEPATH				"ShortPath"
#define DB_INDEXID						"IndexId"
*/
/*
keywords are used to find things via search engines; tags are used to find things within your own Archive.
So, you would use keywords to help label your article so when people search on Google, they hopefully use
the words in your archive(or in your archive keyword Metadata).
*/

#define TABLE_METADATA			"metadata"
#define TABLE_ASSETPROPERTIES	"asset_properties"


/*
#define TABLE_METADATA			"metadata"
#define TABLE_ASSETPROPERTIES	"asset_properties"

#define DB_SEQUENCEID	   "SequenceId"
#define DB_MD5	           "Md5"
#define DB_CRC             "Crc"
#define DB_FILENAME        "Filename"
#define DB_ORGINALNAME     "OrginalName"
#define DB_UUID            "Uuid"
#define DB_DESCRIPTION	   "Description"
#define DB_APERTURE        "Aperture"
#define DB_CAPTUREDATE     "CaptureDate"
#define DB_COLORSPACE      "ColorSpace"
#define DB_COMPRESSION     "Compression"
#define DB_COPYRIGHT       "Copyright"
#define DB_COPYRIGHTURL    "CopyrightUrl"
#define DB_DATEADDED       "DateAdded"
#define DB_DATECREATE      "DateCreate"
#define DB_DATEMODIFIED    "DateModified"
#define DB_DEPTH           "Depth"
#define DB_DIGITALZOOM     "DigitalZoom"
#define DB_EXIFVERSION     "ExifVersion"
#define DB_EXPOSUREBIAS    "ExposureBias"
#define DB_EXPOSUREPROGRAM "ExposureProgram"
#define DB_EXPOSURETIME    "ExposureTime"
#define DB_FILEPATH        "Filepath"
#define DB_FILESIZE        "FileSize"
#define DB_FLASH           "Flash"
#define DB_FOCALLENGTH     "FocalLength"
#define DB_GPSTIMESTAMP    "GpsTimeStamp"
#define DB_HEIGHT          "Height"
#define DB_ISOSPEEDRATING  "IsoSpeedRating"
#define DB_LABEL           "Label"
#define DB_LATITUDE        "Latitude"
#define DB_LIGHTSOURCE     "LightSource"
#define DB_LONGITUDE       "Longitude"
#define DB_MAKER           "Maker"
#define DB_MEDIATYPE       "MediaType"
#define DB_METERINGMODE    "MeteringMode"
#define DB_MODEL           "Model"
#define DB_PAGE            "Page"
#define DB_PRINARYENCODING "PrimaryEncoding"
#define DB_RATING          "Rating"
#define DB_RESOLUTION      "Resolution"
#define DB_SAMPLECOLOR     "SampleColor"
#define DB_SENSINGMETHOD   "SensingMethod"
#define DB_SOFTWARE        "Software"
#define DB_SOURCEURL       "SourceUrl"
#define DB_USAGERIGHTS     "UsageRights"
#define DB_VIEWROTATION    "ViewRotation"
#define DB_WIDTH           "Width"
 */
