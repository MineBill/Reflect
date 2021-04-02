#pragma once

#include "Core/Core.h"
#include "ReflectStructs.h"
#include <string>
#include <fstream>
#include <unordered_map>
#include <tuple>

namespace Reflect
{
	/// <summary>
	/// Parse a single file. This should extract all the info like functions and variables.
	/// </summary>
	class FileParser
	{
	public:
		REFLECT_DLL FileParser();
		REFLECT_DLL ~FileParser();

		REFLECT_DLL void ParseDirectory(const std::string& directory);
		REFLECT_DLL std::ifstream OpenFile(const std::string& filePath);
		REFLECT_DLL void CloseFile(std::ifstream& file);

		REFLECT_DLL const FileParsedData& GetFileParsedData(int index) const { return m_filesParsed.at(index); }
		REFLECT_DLL const std::vector<FileParsedData>& GetAllFileParsedData() const { return m_filesParsed; }

	private:
		bool CheckExtension(const std::string& filePath, std::vector<const char*> extensions);
		bool CheckIfAutoGeneratedFile(const std::string& filePath);

		FileParsedData LoadFile(std::ifstream& file);

		void ParseFile(FileParsedData& fileData);

		bool ReflectContainerHeader(FileParsedData& fileData, const std::string& keyword, const ReflectType type);
		void ReflectContainer(FileParsedData& fileData);

		int FindEndOfConatiner(const FileParsedData& fileData);

		std::vector<ReflectFlags> ReflectFlags(FileParsedData& fileData);
		char FindNextChar(FileParsedData& fileData, const std::vector<char>& ingoreChars);

		bool RefectCheckForEndOfLine(const FileParsedData& fileData);
		bool ReflectTypeCheck(const std::string& type);
		void ReflectGetFunctionParameters(FileParsedData& fileData);

		std::tuple<std::string, std::string, bool> ReflectTypeAndName(FileParsedData& fileData, const std::vector<char>& endOfLineCharacters);
		void CheckForConst(FileParsedData& fileData, std::string& type, bool& typeFound, bool& isConst);

		int CountNumberOfSinceTop(const FileParsedData& fileData, int cursorStart, const char& character);

	private:
		std::vector<FileParsedData> m_filesParsed;
	};
}
