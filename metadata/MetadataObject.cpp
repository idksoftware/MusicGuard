/*
imageContainer * MetadataObject.cpp
 *
 *  Created on: Jul 4, 2014
 *      Author: wzw7yn
 */
#include "tinyxml2.h"
#include "DBDefines.h"
#include "MetadataObject.h"
#include "tinyxml2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

using namespace tinyxml2;

namespace simplearchive {

MetadataSchema MetadataObject::m_tableSchema;
MetadataObject::MetadataObject() : MTRow(m_tableSchema) {}


MetadataObject::~MetadataObject() {
	//printf("+++ MetadataObject Deleting +++\n");
}



bool MetadataObject::fromXML(const char *path) {
	/*
	XMLDocument doc;
	XMLError err = doc.LoadFile(path);
	if (err != XMLError::XML_SUCCESS) {
		return false;
	}
	XMLElement* elementMetadata = doc.FirstChildElement("Metadata");

	XMLElement* elementFile = elementMetadata->FirstChildElement("File");
	XMLElement* element = elementFile->FirstChildElement("SequenceId");
	XMLNode* node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SEQUENCEID_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("Filename");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_FILENAME_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("OrginalName");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ORGINALNAME_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("Filepath");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_FILEPATH_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("Uuid");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_UUID_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("MediaType");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_MEDIATYPE_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("Sha256");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SHA_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("Crc");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CRC_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("FileSize");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_FILESIZE_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("DateCreate");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DATECREATE_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("DateModified");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DATEMODIFIED_IDX)).fromString(node->Value());
	element = elementFile->FirstChildElement("DateAdded");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DATEADDED_IDX)).fromString(node->Value());
	//	MD_KEYWORDS_IDX,// template
	
	XMLElement* elementDescription = elementMetadata->FirstChildElement("Description");
	element = elementDescription->FirstChildElement("Description");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DESCRIPTION_IDX)).fromString(node->Value());
	element = elementDescription->FirstChildElement("Label");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_LABEL_IDX)).fromString(node->Value());
	element = elementDescription->FirstChildElement("Title");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_TITLE_IDX)).fromString(node->Value());
	element = elementDescription->FirstChildElement("Subject");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SUBJECT_IDX)).fromString(node->Value());
	element = elementDescription->FirstChildElement("Rating");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_RATING_IDX)).fromString(node->Value());
	element = elementDescription->FirstChildElement("RatingPercent");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_RATINGPERCENT_IDX)).fromString(node->Value());
	element = elementDescription->FirstChildElement("Keywords");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_KEYWORDS_IDX)).fromString(node->Value());
	element = elementDescription->FirstChildElement("Version");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_VERSION_IDX)).fromString(node->Value());
	
	XMLElement* elementOrigin = elementMetadata->FirstChildElement("Origin");
	element = elementOrigin->FirstChildElement("Comment");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMMENT_IDX)).fromString(node->Value());
	element = elementOrigin->FirstChildElement("Author");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_AUTHOR_IDX)).fromString(node->Value());
	element = elementOrigin->FirstChildElement("CaptureDate");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CAPTUREDATE_IDX)).fromString(node->Value());
	element = elementOrigin->FirstChildElement("SubsetTimeOriginal");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SUBSETIMEORIGINAL_IDX)).fromString(node->Value());
	element = elementOrigin->FirstChildElement("Copyright");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COPYRIGHT_IDX)).fromString(node->Value());

	XMLElement* elementImage = elementMetadata->FirstChildElement("Image");
	element = elementImage->FirstChildElement("Width");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_WIDTH_IDX)).fromString(node->Value());
	element = elementImage->FirstChildElement("Height");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_HEIGHT_IDX)).fromString(node->Value());
	element = elementImage->FirstChildElement("ViewRotation");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_VIEWROTATION_IDX)).fromString(node->Value());
	element = elementImage->FirstChildElement("BitsPerSample");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_BITSPERSAMPLE_IDX)).fromString(node->Value());
	element = elementImage->FirstChildElement("XResolution");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_XRESOLUTION_IDX)).fromString(node->Value());
	element = elementImage->FirstChildElement("YResolution");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_YRESOLUTION_IDX)).fromString(node->Value());
	element = elementImage->FirstChildElement("ResolutionUnit");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_RESOLUTIONUNIT_IDX)).fromString(node->Value());
	element = elementImage->FirstChildElement("Compression");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMPRESSION_IDX)).fromString(node->Value());
	XMLElement* elementCamera = elementMetadata->FirstChildElement("Camera");
	element = elementCamera->FirstChildElement("Maker");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_MAKER_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("Model");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_MODEL_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("ExposureTime");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_EXPOSURETIME_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("Aperture");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_APERTURE_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("IsoSpeedRating");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ISOSPEEDRATING_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("ExposureBias");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_EXPOSUREBIAS_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("ExposureProgram");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_EXPOSUREPROGRAM_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("SubjectDistance");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SUBJECTDISTANCE_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("FocalLength");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_FOCALLENGTH_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("FocalLenghtIn35mm");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_FOCALLENGTHIN35MM_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("Flash");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_FLASH_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("MeteringMode");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_METERINGMODE_IDX)).fromString(node->Value());
	element = elementCamera->FirstChildElement("DigitalZoom");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_DIGITALZOOM_IDX)).fromString(node->Value());
	// Advanced photo
	XMLElement* elementAdvancedPhoto = elementMetadata->FirstChildElement("AdvancedPhoto");
	element = elementAdvancedPhoto->FirstChildElement("LightSource");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_LIGHTSOURCE_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("ColorSpace");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COLORSPACE_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("WhiteBalance");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_WHITEBALANCE_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("SceneCaptureType");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SCENECAPTURETYPE_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("Contrast");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CONTRAST_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("Saturation");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SATURATION_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("Sharpness");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SHARPNESS_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("BrightnessValue");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_BRIGHTNESSVALUE_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("SubjectDistanceRange");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SUBJECTDISTANCERANGE_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("MaxAperture");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_MAXAPERTURE_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("CompressedBitsPerPixel");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COMPRESSEDBITSPERPIXEL_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("FlashEnergy");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_FLASHENERGY_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("ExifVersion");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_EXIFVERSION_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("Software");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SOFTWARE_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("PhotometricInterpretation");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_PHOTOMETRICINTERPRETATION_IDX)).fromString(node->Value());
	element = elementAdvancedPhoto->FirstChildElement("GpsTimeStamp");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_GPSTIMESTAMP_IDX)).fromString(node->Value());

	XMLElement* elementLocation = elementMetadata->FirstChildElement("Location");
	element = elementLocation->FirstChildElement("Latitude");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_LATITUDE_IDX)).fromString(node->Value());
	element = elementLocation->FirstChildElement("Longitude");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_LONGITUDE_IDX)).fromString(node->Value());
	element = elementLocation->FirstChildElement("Location");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_LOCATION_IDX)).fromString(node->Value());
	element = elementLocation->FirstChildElement("Scene");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SCENE_IDX)).fromString(node->Value());

	XMLElement* elementIPTC = elementMetadata->FirstChildElement("IPTC");
	element = elementIPTC->FirstChildElement("SourceUrl");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SOURCEURL_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("UsageRights");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_USAGERIGHTS_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("CopyrightUrl");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COPYRIGHTURL_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Headline");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_HEADLINE_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Category");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CATEGORY_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Source");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_SOURCE_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Instructions");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_INSTRUCTIONS_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Creator");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CREATOR_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("JobTitle");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_JOBTITLE_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Address");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_ADDRESS_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("City");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_CITY_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("State");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_STATE_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("PostalCode");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_POSTALCODE_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Country");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_COUNTRY_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Phone");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_PHONE_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Email");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_EMAIL_IDX)).fromString(node->Value());
	element = elementIPTC->FirstChildElement("Website");
	node = element->FirstChild();
	if (node != nullptr) columnAt(static_cast<size_t>(MetadataObjectIndex::MD_WEBSITE_IDX)).fromString(node->Value());
	*/
	return true;
}

} /* namespace simplearchive */
