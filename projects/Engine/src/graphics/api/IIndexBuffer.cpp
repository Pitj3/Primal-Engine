#include "graphics/api/IIndexBuffer.h"

IIndexBuffer::IIndexBuffer(IGraphicsContext* aContext)
{
	mSize = 0;
	mData = nullptr;
	mContext = aContext;
}

uint32_t IIndexBuffer::getCount() const
{
	// TODO: Take the actual type of the buffer
	return mSize / sizeof(uint16_t);
}
