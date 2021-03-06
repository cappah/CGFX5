#pragma once

#include "renderDevice.hpp"
#include "texture.hpp"

class RenderTarget
{
public:
	RenderTarget(RenderDevice& deviceIn) :
		device(&deviceIn),
		deviceId(0) {}

	// TODO: Ensure texture isn't compressed. Otherwise, render target creation fails.
	FORCEINLINE RenderTarget(RenderDevice& deviceIn,
			Texture& texture, uint32 width, uint32 height,
			enum RenderDevice::FramebufferAttachment attachment
				= RenderDevice::ATTACHMENT_COLOR,
			uint32 attachmentNumber = 0, uint32 mipLevel = 0) :
		device(&deviceIn),
		deviceId(device->createRenderTarget(texture.getId(), width, height,
					attachment, attachmentNumber, mipLevel)) {}
	FORCEINLINE RenderTarget(RenderDevice& deviceIn,
			Texture& texture,
			enum RenderDevice::FramebufferAttachment attachment
				= RenderDevice::ATTACHMENT_COLOR,
			uint32 attachmentNumber = 0, uint32 mipLevel = 0) :
		device(&deviceIn),
		deviceId(device->createRenderTarget(texture.getId(),
					texture.getWidth(), texture.getHeight(),
					attachment, attachmentNumber, mipLevel)) {}
	FORCEINLINE ~RenderTarget()
	{
		deviceId = device->releaseRenderTarget(deviceId);
	}

	FORCEINLINE uint32 getId();
private:
	RenderDevice* device;
	uint32 deviceId;

	NULL_COPY_AND_ASSIGN(RenderTarget);
};

FORCEINLINE uint32 RenderTarget::getId()
{
	return deviceId;
}


