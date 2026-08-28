#pragma once

/*
 *   Header File [Violet.h]
 */

#include "SDL3/SDL.h"
#include <iostream>
#include <fstream>
#include <format>
#include <filesystem>
#include <limits>

namespace Vi {

	namespace Debug {
		template<typename... Args>
		void print(std::ostream& os, Args&&... args) {
			if constexpr (sizeof...(Args) > 0) {
				(os << ... << std::forward<Args>(args));
			}
		}
	}

	struct Color {
		float r{};
		float g{};
		float b{};
		float a{};
	};

	struct Vertex {
		float pos[3]{};
		float color[4]{};
		float uv[2]{};
	};

	class Window {
	public:

		Window(const char* title, int width, int height) {
			if (created) {
				Debug::print(std::cerr, "Window Already Created!\n");
				std::terminate();
			} created = true;

			constexpr int MIN_WIDTH{ 256 };
			constexpr int MIN_HEIGHT{ 128 };
			screen_width = std::max(width, MIN_WIDTH);
			screen_height = std::max(height, MIN_HEIGHT);

			if (!SDL_Init(SDL_INIT_VIDEO)) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			window = SDL_CreateWindow(title, screen_width, screen_height, SDL_WINDOW_RESIZABLE);
			if (!window) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, true, nullptr);
			if (!device) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			if (!SDL_ClaimWindowForGPUDevice(device, window)) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			if (!SDL_SetGPUSwapchainParameters(device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC)) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			if (!SDL_SetWindowMinimumSize(window, MIN_WIDTH, MIN_HEIGHT)) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			std::filesystem::path path = std::filesystem::current_path() / "Shaders";
			std::filesystem::path vertex_path = path / "vertex.spv";
			std::filesystem::path fragment_path = path / "fragment.spv";

			std::ifstream vertex_spv{ vertex_path, std::ios::binary };
			if (!vertex_spv) {
				Debug::print(std::cerr, "Couldn't Load: ");
				std::cerr << vertex_path.string() << std::endl;
				std::terminate();
			}

			std::ifstream fragment_spv{ fragment_path, std::ios::binary };
			if (!fragment_spv) {
				Debug::print(std::cerr, "Couldn't Load: ");
				std::cerr << fragment_path.string() << std::endl;
				std::terminate();
			}

			std::vector<uint8_t> vertex_code = {
				std::istreambuf_iterator<char>(vertex_spv),
				std::istreambuf_iterator<char>()
			};

			std::vector<uint8_t> fragment_code = {
				std::istreambuf_iterator<char>(fragment_spv),
				std::istreambuf_iterator<char>()
			};

			SDL_GPUShaderCreateInfo vertex_shader_create_info {
				.code_size = vertex_code.size(),
				.code = vertex_code.data(),
				.entrypoint = "main",
				.format = SDL_GPU_SHADERFORMAT_SPIRV,
				.stage = SDL_GPU_SHADERSTAGE_VERTEX,
				.num_uniform_buffers = 1,
			};

			SDL_GPUShaderCreateInfo fragment_shader_create_info {
				.code_size = fragment_code.size(),
				.code = fragment_code.data(),
				.entrypoint = "main",
				.format = SDL_GPU_SHADERFORMAT_SPIRV,
				.stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
				.num_samplers = 1,
			};

			SDL_GPUShader* vertex_shader_program = SDL_CreateGPUShader(device, &vertex_shader_create_info);
			if (!vertex_shader_program) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			SDL_GPUShader* fragment_shader_program = SDL_CreateGPUShader(device, &fragment_shader_create_info);
			if (!fragment_shader_program) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			SDL_GPUVertexAttribute position_attribute {
				.location = 0,
				.buffer_slot = 0,
				.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
				.offset = offsetof(Vertex, pos),
			};

			SDL_GPUVertexAttribute color_attribute {
				.location = 1,
				.buffer_slot = 0,
				.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
				.offset = offsetof(Vertex, color),
			};

			SDL_GPUVertexAttribute texcoords_attribute {
				.location = 2,
				.buffer_slot = 0,
				.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT2,
				.offset = offsetof(Vertex, uv),
			};

			std::vector<SDL_GPUVertexAttribute> vertex_attributes = {
				position_attribute,
				color_attribute,
				texcoords_attribute,
			};

			SDL_GPUVertexBufferDescription vertex_buffer_description {
				.pitch = sizeof(Vertex),
				.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
			};

			SDL_GPUColorTargetDescription color_target_description {
				.format = SDL_GetGPUSwapchainTextureFormat(device, window),
				.blend_state = {
					.src_color_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
					.dst_color_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
					.color_blend_op = SDL_GPU_BLENDOP_ADD,
					.src_alpha_blendfactor = SDL_GPU_BLENDFACTOR_SRC_ALPHA,
					.dst_alpha_blendfactor = SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
					.alpha_blend_op = SDL_GPU_BLENDOP_ADD,
					.enable_blend = true,
				},
			};

			SDL_GPUSamplerCreateInfo sampler_create_info {
				.min_filter = SDL_GPU_FILTER_NEAREST,
				.mag_filter = SDL_GPU_FILTER_NEAREST,
				.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
				.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
				.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
				.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
			};

			SDL_GPUTextureCreateInfo depth_texture_create_info {
				.type = SDL_GPU_TEXTURETYPE_2D,
				.format = SDL_GPU_TEXTUREFORMAT_D16_UNORM,
				.usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
				.width = static_cast<unsigned int>(screen_width),
				.height = static_cast<unsigned int>(screen_height),
				.layer_count_or_depth = 1,
				.num_levels = 1,
				.sample_count = SDL_GPU_SAMPLECOUNT_1
			};

			SDL_GPUGraphicsPipelineCreateInfo graphics_pipeline_create_info {
				.vertex_shader = vertex_shader_program,
				.fragment_shader = fragment_shader_program,
				.vertex_input_state = {
					.vertex_buffer_descriptions = &vertex_buffer_description,
					.num_vertex_buffers = 1,
					.vertex_attributes = vertex_attributes.data(),
					.num_vertex_attributes = static_cast<unsigned int>(vertex_attributes.size()),
				},
				.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
				.depth_stencil_state = {
					.compare_op = SDL_GPU_COMPAREOP_LESS_OR_EQUAL,
					.enable_depth_test = true,
					.enable_depth_write = true,
				},
				.target_info = {
					.color_target_descriptions = &color_target_description,
					.num_color_targets = 1,
					.depth_stencil_format = SDL_GPU_TEXTUREFORMAT_D16_UNORM,
					.has_depth_stencil_target = true,
				},
			};

			depth_texture = SDL_CreateGPUTexture(device, &depth_texture_create_info);
			if (!depth_texture) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			sampler = SDL_CreateGPUSampler(device, &sampler_create_info);
			if (!sampler) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			graphics_pipeline = SDL_CreateGPUGraphicsPipeline(device, &graphics_pipeline_create_info);
			if (!graphics_pipeline) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}

			SDL_ReleaseGPUShader(device, vertex_shader_program);
			SDL_ReleaseGPUShader(device, fragment_shader_program);
		}

		~Window() {
			SDL_ReleaseGPUSampler(device, sampler);
			SDL_ReleaseGPUTexture(device, depth_texture);
			SDL_ReleaseGPUGraphicsPipeline(device, graphics_pipeline);
			SDL_DestroyGPUDevice(device);
			SDL_DestroyWindow(window);
			SDL_Quit();
			created = false;
			screen_width = 0;
			screen_height = 0;
			window = nullptr;
			device = nullptr;
			sampler = nullptr;
			depth_texture = nullptr;
			graphics_pipeline = nullptr;
		}

		bool isOpen() {
			SDL_Event event{};
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
					return false;
				}
			} return true;
		}

		void clear(Color clear_color) {
			if (frame) {
				Debug::print(std::cerr, "Frame Already Cleared!\n");
				std::terminate();
			} frame = true;

			command_buffer = SDL_AcquireGPUCommandBuffer(device);
			if (!command_buffer) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}
			
			unsigned int width{}, height{};
			if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer, window, &swapchain_texture, &width, &height)) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}



		}

		void display() {
			if (!frame) {
				Debug::print(std::cerr, "No Displayable Frame!\n");
				std::terminate();
			} frame = false;

			SDL_EndGPURenderPass(render_pass);
			if (!SDL_SubmitGPUCommandBuffer(command_buffer)) {
				std::string s = std::format("SDL Error: {}\n", SDL_GetError());
				Debug::print(std::cerr, s);
				std::terminate();
			}
		}

	private:

		static inline bool created{};
		static inline int screen_width{};
		static inline int screen_height{};
		static inline SDL_Window* window{};
		static inline SDL_GPUDevice* device{};
		static inline SDL_GPUTexture* depth_texture{};
		static inline SDL_GPUSampler* sampler{};
		static inline SDL_GPUGraphicsPipeline* graphics_pipeline{};

		static inline bool frame{};
		static inline SDL_GPURenderPass* render_pass{};
		static inline SDL_GPUTexture* swapchain_texture{};
		static inline SDL_GPUCommandBuffer* command_buffer{};

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		void operator = (const Window&) = delete;
		void operator = (Window&&) = delete;
	};
}

