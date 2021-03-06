#ifndef _TITAN_COMMONFILESYSTEM_HH
#define _TITAN_COMMONFILESYSTEM_HH

#include "TiPrerequisites.h"
#include "TiFileSystem.h"

namespace Titan
{
	class _DllExport CommonFileSystem : public FileSystem
	{
	public:
		CommonFileSystem(const String& name, const String& type);

		~CommonFileSystem();

		void	load();

		void	unload(){};

		DataStreamPtr open(const String& filename);

		StringVectorPtr find(const String& wildcard, bool recursive);

		void	find(const String& wildcard, bool recursive, StringVectorPtr* nameArray, StringVectorPtr* relPathArray);
	protected:
		void	searchDir(const String& pattern, bool recursive, StringVectorPtr stringVector, StringVectorPtr pathVector);
	};


	class _DllExport CommonFileSystemFactory : public FileSystemFactory
	{
	public:
		CommonFileSystemFactory(): FileSystemFactory("CommonFileSystem")
		{}

		~CommonFileSystemFactory(){}; 

		FileSystem*		createInstance(const String& name, const String& type);

		void			destroyInstance(FileSystem* file) ;
	};
}
#endif