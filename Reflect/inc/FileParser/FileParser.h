#pragma once

#include "Core/Defines.h"
#include "ReflectStructs.h"

#include <string>
#include <fstream>
#include <unordered_map>
#include <tuple>

namespace Reflect
{
	struct ReflectAddtionalOptions;

	/// <summary>
	/// Parse a single file. This should extract all the info like functions and variables.
	/// </summary>
	class FileParser
	{
	public:
		REFLECT_API FileParser();
		REFLECT_API ~FileParser();

		REFLECT_API void ParseDirectory(const std::string& directory, const ReflectAddtionalOptions* additionalOptions);
		REFLECT_API void SetIgnoreStrings(const std::vector<std::string>& ignoreStrings);

		REFLECT_API const FileParsedData& GetFileParsedData(int index) const { return m_filesParsed.at(index); }
		REFLECT_API const std::vector<FileParsedData>& GetAllFileParsedData() const { return m_filesParsed; }

		REFLECT_API const std::string& GetDirectoryParsed(int index) const { return m_directoriesParsed.at(index); }
		REFLECT_API const std::vector<std::string>& GetAllDirectoriesParsed() const { return  m_directoriesParsed; }

	private:
		std::ifstream OpenFile(const std::string& filePath);
		void CloseFile(std::ifstream& file);

		bool CheckExtension(const std::string& filePath, std::vector<const char*> extensions);
		bool CheckIfAutoGeneratedFile(const std::string& filePath);

		FileParsedData LoadFile(std::ifstream& file);


		bool ParseFile(FileParsedData& fileData);
		bool ReflectContainerHeader(FileParsedData& fileData, const std::string& keyword, const EReflectType type);
		void ReflectContainer(FileParsedData& fileData);
		void GetAllCPPIncludes(FileParsedData& fileData);

		int FindEndOfConatiner(const FileParsedData& fileData);
		std::vector<std::string> ReflectFlags(FileParsedData& fileData);

		char FindNextChar(FileParsedData& fileData, const std::vector<char>& ignoreChars);
		char FindNextChar(FileParsedData const& fileData, int& cursor, const std::vector<char>& ignoreChars);
		char FindNextChar(FileParsedData& fileData, char charToFind);

		std::string FindNextWord(FileParsedData& fileData, const std::vector<char>& endChars);
		bool IsWordReflectKey(std::string_view view);

		bool CheckForTypeAlias(std::string_view view);
		bool CheckForVisibility(std::string_view view);
		bool CheckForConstructor(FileParsedData& fileData, ReflectContainerData& container, std::string_view view);
		bool CheckForIgnoreWord(FileParsedData& fileData, std::string_view view);
		bool CheckForOperatorFunction(FileParsedData& fileData, std::string_view view);
		bool CheckForComments(FileParsedData& fileData, std::string& line);
		bool CheckForFriends(FileParsedData& fileData, std::string_view view);

		void GetReflectNameAndReflectValueTypeAndReflectModifer(std::string& str, std::string& name, EReflectValueType& valueType, EReflectValueModifier& modifer);

		ReflectFunctionData GetFunction(FileParsedData& fileData, const std::vector<std::string>& flags);
		ReflectMemberData GetMember(FileParsedData& fileData, const std::vector<std::string>& flags);

		void SkipFunctionBody(FileParsedData& fileData);

		EReflectType CheckForReflectType(FileParsedData& data);

		bool CheckForEndOfFile(FileParsedData& fileData, int cursor);
		EReflectValueType CheckForRefOrPtr(std::string_view view);
		EReflectValueModifier CheckForMemberModifers(std::string_view view);

		std::string GetFunctionLine(const FileParsedData& fileData, int& endCursor);
		std::vector<ReflectTypeNameData> ReflectGetFunctionParameters(const FileParsedData& fileData, std::string_view view);

		void CheckStringViewBounds(const FileParsedData& fileData, int cursor, std::string_view view);
		int CountNumberOfSinceTop(const FileParsedData& fileData, int cursorStart, const char& character);

		std::string PrettyString(std::string str);
		ReflectContainerData* FindReflectContainerData(std::string_view containerName);

	private:
		std::vector<FileParsedData> m_filesParsed;
		std::vector<std::string> m_filesToRemove;
		std::vector<std::string> m_ignoreStrings;
		std::vector<std::string> m_directoriesParsed;
		const ReflectAddtionalOptions* m_options;
	};
}
