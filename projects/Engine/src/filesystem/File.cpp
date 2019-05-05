#include "filesystem/File.h"

#include <fstream>

File::File()
{
	mData = "";
	mPath = "";
}

File::~File()
{
	
}

void File::write(const char* aData)
{
	mData += aData;
}

void File::write(const std::string& aData)
{
	mData += aData;
}

void File::save(const EFileSaveMode& aMode) const
{
	if(mPath == "")
	{
		// LOG ERROR
		return;
	}

	std::ofstream stream;
	int32_t saveMode = std::ios::out;

	if(/*exists*/ false)
	{
		if(aMode == EFileSaveMode::Truncate)
		{
			saveMode |= std::ios::trunc;
		}
		else
		{
			saveMode |= std::ios::app;
		}
	}

#if defined(PRIMAL_PLATFORM_WINDOWS)
	stream.open(mPath.c_str(), saveMode);
#elif defined(PRIMAL_PLATFORM_LINUX)
	stream.open(mPath.c_str(), (std::_Ios_Openmode)saveMode);
#endif

	stream << mData.c_str();
	stream.close();
}

std::string File::data() const
{
	return mData;
}

size_t File::size() const
{
	return mData.size();
}


