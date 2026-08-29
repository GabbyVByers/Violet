
/*
 *   Source File [Mesh.cpp]
 */

#include "Violet.h"

namespace Vi {

	Mesh::Mesh(const Image& image) {
		if (!Window::created) { throw std::exception{}; }
		texture(image);
	}

	Mesh::~Mesh() {
		if (!Window::created) { throw std::exception{}; }
		if (vertex_buffer) { SDL_ReleaseGPUBuffer(Window::device, vertex_buffer); }
		if (gpu_texture) { SDL_ReleaseGPUTexture(Window::device, gpu_texture); }
	}

	void Mesh::upload(const Vertex* vertices, size_t count) {
		if (!Window::created) { throw std::exception{}; }
		if (vertex_buffer) { SDL_ReleaseGPUBuffer(Window::device, vertex_buffer); }
		num_vertices = count;

		SDL_GPUBufferCreateInfo vertex_buffer_info{
			.usage = SDL_GPU_BUFFERUSAGE_VERTEX,
			.size = static_cast<unsigned int>(sizeof(Vertex) * num_vertices),
		};

		vertex_buffer = SDL_CreateGPUBuffer(Window::device, &vertex_buffer_info);
		if (!vertex_buffer) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUTransferBufferCreateInfo transfer_buffer_info{
			.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			.size = static_cast<unsigned int>(sizeof(Vertex) * num_vertices),
		};

		SDL_GPUTransferBuffer* transfer_buffer = SDL_CreateGPUTransferBuffer(Window::device, &transfer_buffer_info);
		if (!transfer_buffer) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		void* transfer_buffer_beginning = SDL_MapGPUTransferBuffer(Window::device, transfer_buffer, false);
		if (!transfer_buffer_beginning) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		if (!SDL_memcpy(transfer_buffer_beginning, vertices, sizeof(Vertex) * num_vertices)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUCommandBuffer* command_buffer = SDL_AcquireGPUCommandBuffer(Window::device);
		if (!command_buffer) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUCopyPass* copy_pass = SDL_BeginGPUCopyPass(command_buffer);
		if (!copy_pass) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUTransferBufferLocation source_buffer_location{
			.transfer_buffer = transfer_buffer,
		};

		SDL_GPUBufferRegion destination_buffer_region{
			.buffer = vertex_buffer,
			.size = static_cast<unsigned int>(sizeof(Vertex) * num_vertices),
		};

		SDL_UploadToGPUBuffer(copy_pass, &source_buffer_location, &destination_buffer_region, true);
		SDL_EndGPUCopyPass(copy_pass);

		if (!SDL_SubmitGPUCommandBuffer(command_buffer)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_UnmapGPUTransferBuffer(Window::device, transfer_buffer);
		SDL_ReleaseGPUTransferBuffer(Window::device, transfer_buffer);
	}

	void Mesh::texture(const Image& image) {
		size_t buffer_size{};
		const uint8_t* pixels = image.ptr(buffer_size);
		const Vec2u image_size = image.size();
		unsigned int width = static_cast<unsigned int>(image_size.x);
		unsigned int height = static_cast<unsigned int>(image_size.y);

		SDL_GPUTextureCreateInfo texture_create_info{
			.type = SDL_GPU_TEXTURETYPE_2D,
			.format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM_SRGB,
			.usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
			.width = width,
			.height = height,
			.layer_count_or_depth = 1,
			.num_levels = 1,
			.sample_count = SDL_GPU_SAMPLECOUNT_1,
		};

		gpu_texture = SDL_CreateGPUTexture(Window::device, &texture_create_info);
		if (!gpu_texture) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUTransferBufferCreateInfo transfer_buffer_info{
			.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			.size = static_cast<unsigned int>(buffer_size),
		};

		SDL_GPUTransferBuffer* transfer_buffer = SDL_CreateGPUTransferBuffer(Window::device, &transfer_buffer_info);
		if (!transfer_buffer) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		void* transfer_buffer_beginning = SDL_MapGPUTransferBuffer(Window::device, transfer_buffer, false);
		if (!transfer_buffer_beginning) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		if (!SDL_memcpy(transfer_buffer_beginning, pixels, buffer_size)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUCommandBuffer* command_buffer = SDL_AcquireGPUCommandBuffer(Window::device);
		if (!command_buffer) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUCopyPass* copy_pass = SDL_BeginGPUCopyPass(command_buffer);
		if (!copy_pass) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUTextureTransferInfo texture_transfer_info {
			.transfer_buffer = transfer_buffer,
			.pixels_per_row = width,
			.rows_per_layer = height,
		};

		SDL_GPUTextureRegion destination_texture_region {
			.texture = gpu_texture,
			.w = width,
			.h = height,
			.d = 1,
		};

		SDL_UploadToGPUTexture(copy_pass, &texture_transfer_info, &destination_texture_region, false);
		SDL_EndGPUCopyPass(copy_pass);
		
		if (!SDL_SubmitGPUCommandBuffer(command_buffer)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_UnmapGPUTransferBuffer(Window::device, transfer_buffer);
		SDL_ReleaseGPUTransferBuffer(Window::device, transfer_buffer);
	}
}

