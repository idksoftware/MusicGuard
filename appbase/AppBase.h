#pragma once

#include <memory>
#include <string>
#include <cstdlib>
#include <cstdarg>
#include <sstream>
#include <iomanip>
#include <string>
#include "SIAArgvParser.h"
#include "ExitCode.h"


namespace CommandLineProcessing {


//	typedef std::unique_ptr<DupDataFile> DupDataFile_Ptr;
	

	using ReturnCode = uint32_t;

	class AppBase
	{
	public:
		enum class MarkupLanguage {
			XML,
			JSON,
			HTML,
			HUMAN,
			CVS,
			Unknown
		};
	private:
		MarkupLanguage m_markupLanguage{ MarkupLanguage::HUMAN };
		bool m_configured;
		static ExitCode m_exitCode;
		
		static std::string m_appName;
	protected:
		std::shared_ptr<SIAArgvParser> m_argvParser;
		
		std::string  m_configPath;
		std::string  m_homePath;
		void setConfigured() { m_configured = true; };
		static ReturnCode m_returnCode;
		static std::string m_returnString;

		AppBase(const char* appName, std::shared_ptr<SIAArgvParser> argvParser) :
			m_argvParser(argvParser),
			m_configured(false)
		{
			m_appName = appName;
		}

	public:
		~AppBase();
		
		ExitCode RunApp(int argc, char **argv);
		bool initalise(int argc, char **argv);
		
		/// @brief This is the main application run function. All application processing starts here.
		bool Run();
		
		
		bool isConfiguratedOk() {
			return m_configured;
		}

		const char *getHomePath() {
			return m_homePath.c_str();
		}

		static MarkupLanguage toMarkupLanguageValid(const char* s) {
			std::string str = s;
			if (str.compare("XML")) {
				return MarkupLanguage::XML;
			}
			if (str.compare("JSON")) {
				return MarkupLanguage::JSON;
			}
			if (str.compare("HTML")) {
				return MarkupLanguage::HTML;
			}
			if (str.compare("HUMAN")) {
				return MarkupLanguage::HUMAN;
			}
			if (str.compare("CVS")) {
				return MarkupLanguage::CVS;
			}
			return MarkupLanguage::Unknown;
		}

		static const char *getFullErrorString() {
			std::stringstream str;
			switch (m_exitCode) {
			case ExitCode::Success:
				str << "Success:" << std::setw(4) << std::setfill('0') << m_returnCode << " - " << m_returnString;
				break;
			case ExitCode::Warnings:
				str << "Warnings:" << std::setw(4) << std::setfill('0') << m_returnCode << " - " << m_returnString;
				break;
			case ExitCode::Errors:
				str << "Errors:" << std::setw(4) << std::setfill('0') << m_returnCode << " - " << m_returnString;
				break;
			case ExitCode::Fatal:
				if (m_returnString.empty()) {
					m_returnString = "Failed to run application: " + m_appName;
				}
				str << "Fatal:" << std::setw(4) << std::setfill('0') << m_returnCode << " - " << m_returnString;
				break;
			}
			m_returnString = str.str();
			return m_returnString.c_str();
		}

		static int getError() {
			return m_returnCode;
		}

		static int getExitCode() {
			return (int)m_exitCode;
		}

		void setMarkupLanguage(MarkupLanguage ml) {
			m_markupLanguage = ml;
		}
		MarkupLanguage getarkupLanguage()
		{
			return m_markupLanguage;
		}

	protected:
		
		virtual bool initaliseConfig() = 0;
		virtual bool initaliseArgs(int argc, char **argv) = 0;
		virtual bool doRun() = 0;
		void setConfigPath(const char *configPath) {
			m_configPath = configPath;
		}

		static void setError(int err, const char *format, ...) {
			m_returnCode = err;
			//m_errorstring = str;
			char message[512];
			va_list args;
			va_start(args, format);
#ifdef _WIN32
			vsprintf_s(message, format, args);
#else
			vsprintf(message, format, args);
#endif
			m_returnString = message;
			va_end(args);
		}

		

		static const char *getErrorString() {
			return m_returnString.c_str();
		}
		static void setExitCode(ExitCode exitCode) {
			m_exitCode = exitCode;
		}
	};

}