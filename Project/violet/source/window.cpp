
/*
 *   Source File [Violet.cpp]
 */

#include "Violet.h"

namespace Vi {

	Window::Window(const char* title, int width, int height) {
		if (created) {
			throw std::exception{};
		} created = true;

		constexpr size_t MIN_WIDTH{ 256 };
		constexpr size_t MIN_HEIGHT{ 128 };
		dimensions = {
			std::max(static_cast<size_t>(width), MIN_WIDTH),
			std::max(static_cast<size_t>(height), MIN_HEIGHT),
		};

		if (!SDL_Init(SDL_INIT_VIDEO)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		window = SDL_CreateWindow(title, static_cast<int>(dimensions.x), static_cast<int>(dimensions.y), SDL_WINDOW_RESIZABLE);
		if (!window) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, true, nullptr);
		if (!device) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		if (!SDL_ClaimWindowForGPUDevice(device, window)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		if (!SDL_SetGPUSwapchainParameters(device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		if (!SDL_SetWindowMinimumSize(window, MIN_WIDTH, MIN_HEIGHT)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		std::filesystem::path current_path = std::filesystem::current_path() / "shaders";
		std::filesystem::path vertex_path = current_path / "vertex.spv";
		std::filesystem::path fragment_path = current_path / "fragment.spv";

		std::ifstream vertex_spv{ vertex_path, std::ios::binary };
		if (!vertex_spv) {
			std::string path = vertex_path.string();
			std::cerr << std::format("Couldn't Load: {}\n", path);
			throw std::exception{};
		}

		std::ifstream fragment_spv{ fragment_path, std::ios::binary };
		if (!fragment_spv) {
			std::string path = vertex_path.string();
			std::cerr << std::format("Couldn't Load: {}\n", path);
			throw std::exception{};
		}

		std::vector<uint8_t> vertex_code = {
			std::istreambuf_iterator<char>(vertex_spv),
			std::istreambuf_iterator<char>()
		};

		std::vector<uint8_t> fragment_code = {
			std::istreambuf_iterator<char>(fragment_spv),
			std::istreambuf_iterator<char>()
		};

		SDL_GPUShaderCreateInfo vertex_shader_create_info{
			.code_size = vertex_code.size(),
			.code = vertex_code.data(),
			.entrypoint = "main",
			.format = SDL_GPU_SHADERFORMAT_SPIRV,
			.stage = SDL_GPU_SHADERSTAGE_VERTEX,
			.num_uniform_buffers = 1,
		};

		SDL_GPUShaderCreateInfo fragment_shader_create_info{
			.code_size = fragment_code.size(),
			.code = fragment_code.data(),
			.entrypoint = "main",
			.format = SDL_GPU_SHADERFORMAT_SPIRV,
			.stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
			.num_samplers = 1,
		};

		SDL_GPUShader* vertex_shader_program = SDL_CreateGPUShader(device, &vertex_shader_create_info);
		if (!vertex_shader_program) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUShader* fragment_shader_program = SDL_CreateGPUShader(device, &fragment_shader_create_info);
		if (!fragment_shader_program) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_GPUVertexAttribute position_attribute{
			.location = 0,
			.buffer_slot = 0,
			.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
			.offset = offsetof(Vertex, pos),
		};

		SDL_GPUVertexAttribute color_attribute{
			.location = 1,
			.buffer_slot = 0,
			.format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
			.offset = offsetof(Vertex, color),
		};

		SDL_GPUVertexAttribute texcoords_attribute{
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

		SDL_GPUVertexBufferDescription vertex_buffer_description{
			.pitch = sizeof(Vertex),
			.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
		};

		SDL_GPUColorTargetDescription color_target_description{
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

		SDL_GPUSamplerCreateInfo sampler_create_info{
			.min_filter = SDL_GPU_FILTER_NEAREST,
			.mag_filter = SDL_GPU_FILTER_NEAREST,
			.mipmap_mode = SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
			.address_mode_u = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
			.address_mode_v = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
			.address_mode_w = SDL_GPU_SAMPLERADDRESSMODE_REPEAT,
		};

		SDL_GPUTextureCreateInfo depth_texture_create_info{
			.type = SDL_GPU_TEXTURETYPE_2D,
			.format = SDL_GPU_TEXTUREFORMAT_D16_UNORM,
			.usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
			.width = static_cast<unsigned int>(dimensions.x),
			.height = static_cast<unsigned int>(dimensions.y),
			.layer_count_or_depth = 1,
			.num_levels = 1,
			.sample_count = SDL_GPU_SAMPLECOUNT_1
		};

		SDL_GPUGraphicsPipelineCreateInfo graphics_pipeline_create_info{
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
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		sampler = SDL_CreateGPUSampler(device, &sampler_create_info);
		if (!sampler) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		graphics_pipeline = SDL_CreateGPUGraphicsPipeline(device, &graphics_pipeline_create_info);
		if (!graphics_pipeline) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		SDL_ReleaseGPUShader(device, vertex_shader_program);
		SDL_ReleaseGPUShader(device, fragment_shader_program);
	}

	Window::~Window() {
		if (frame) {
			SDL_EndGPURenderPass(render_pass);
			if (!SDL_SubmitGPUCommandBuffer(command_buffer)) {
				std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
				throw std::exception{};
			}
		}
		
		SDL_ReleaseGPUSampler(device, sampler);
		SDL_ReleaseGPUTexture(device, depth_texture);
		SDL_ReleaseGPUGraphicsPipeline(device, graphics_pipeline);
		SDL_DestroyGPUDevice(device);
		SDL_DestroyWindow(window);
		SDL_Quit();

		created = {};
		dimensions = {};
		window = {};
		device = {};
		depth_texture = {};
		sampler = {};
		graphics_pipeline = {};

		frame = {};
		minimized = {};
		render_pass = {};
		swapchain_texture = {};
		command_buffer = {};
	}

	void Window::vsync(bool vsync) {

		throw std::exception{ "KILL!" };

		if (vsync) {
			if (!SDL_SetGPUSwapchainParameters(device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC)) {
				std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
				throw std::exception{};
			} return;
		}

		if (SDL_WindowSupportsGPUPresentMode(device, window, SDL_GPU_PRESENTMODE_IMMEDIATE)) {
			if (!SDL_SetGPUSwapchainParameters(device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_IMMEDIATE)) {
				std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
				throw std::exception{};
			} return;
		}

		if (SDL_WindowSupportsGPUPresentMode(device, window, SDL_GPU_PRESENTMODE_MAILBOX)) {
			if (!SDL_SetGPUSwapchainParameters(device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_MAILBOX)) {
				std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
				throw std::exception{};
			} return;
		}

		if (!SDL_SetGPUSwapchainParameters(device, window, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}
	}

	bool Window::isOpen() {
		SDL_Event event{};
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
				return false;
			}
		} return true;
	}

	void Window::clear(Color clear_color) {
		if (frame) {
			throw std::exception{};
		} frame = true;

		command_buffer = SDL_AcquireGPUCommandBuffer(device);
		if (!command_buffer) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		unsigned int width{}, height{};
		if (!SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer, window, &swapchain_texture, &width, &height)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}

		minimized = false;
		if ((width == 0) || (height == 0)) {
			minimized = true;
			if (!SDL_SubmitGPUCommandBuffer(command_buffer)) {
				std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
				throw std::exception{};
			} return;
		}

		unsigned int curr_width = static_cast<unsigned int>(dimensions.x);
		unsigned int curr_height = static_cast<unsigned int>(dimensions.y);
		const bool reconstruct_depth_texture = (width != curr_width) || (height != curr_height);
		dimensions = { width, height };

		if (reconstruct_depth_texture) {
			SDL_ReleaseGPUTexture(device, depth_texture);
			depth_texture = nullptr;

			SDL_GPUTextureCreateInfo depth_texture_create_info{
				.type = SDL_GPU_TEXTURETYPE_2D,
				.format = SDL_GPU_TEXTUREFORMAT_D16_UNORM,
				.usage = SDL_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET,
				.width = width,
				.height = height,
				.layer_count_or_depth = 1,
				.num_levels = 1,
				.sample_count = SDL_GPU_SAMPLECOUNT_1
			};

			depth_texture = SDL_CreateGPUTexture(device, &depth_texture_create_info);
			if (!depth_texture) {
				std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
				throw std::exception{};
			}
		}

		SDL_GPUColorTargetInfo color_target_info{
			.texture = swapchain_texture,
			.clear_color = {
				.r = clear_color.r,
				.g = clear_color.g,
				.b = clear_color.b,
				.a = clear_color.a,
			},
			.load_op = SDL_GPU_LOADOP_CLEAR,
			.store_op = SDL_GPU_STOREOP_STORE,
		};

		SDL_GPUDepthStencilTargetInfo depth_stencil_target_info{
			.texture = depth_texture,
			.clear_depth = 1,
			.load_op = SDL_GPU_LOADOP_CLEAR,
			.store_op = SDL_GPU_STOREOP_DONT_CARE,
			.stencil_load_op = SDL_GPU_LOADOP_DONT_CARE,
			.stencil_store_op = SDL_GPU_STOREOP_DONT_CARE,
			.cycle = true
		};

		render_pass = SDL_BeginGPURenderPass(command_buffer, &color_target_info, 1, &depth_stencil_target_info);
		if (!render_pass) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		} SDL_BindGPUGraphicsPipeline(render_pass, graphics_pipeline);
	}

	void Window::draw(const Mesh& mesh) {
		if (!frame) { throw std::exception{}; }
		if (!mesh.vertex_buffer) { throw std::exception{}; }
		if (!mesh.gpu_texture) { throw std::exception{}; }
		if (minimized) { return; }

		double width = static_cast<double>(dimensions.x);
		double height = static_cast<double>(dimensions.y);
		double aspect_ratio = width / height;

		Matrix model = Matrix::model(mesh.scale, mesh.position, mesh.quaternion);
		Matrix view = Matrix::view(Camera::position, Camera::quaternion);
		Matrix project = Matrix::project(Camera::fov, aspect_ratio);
		Matrix mvp = project * view * model;
		//Matrix mvp = Matrix::identity();
		SDL_PushGPUVertexUniformData(command_buffer, 0, mvp.columnmajor(), sizeof(float[16]));

		SDL_GPUBufferBinding buffer_binding {
			.buffer = mesh.vertex_buffer,
		};

		SDL_GPUTextureSamplerBinding texture_binding {
			.texture = mesh.gpu_texture,
			.sampler = sampler,
		};

		SDL_BindGPUVertexBuffers(render_pass, 0, &buffer_binding, 1);
		SDL_BindGPUFragmentSamplers(render_pass, 0, &texture_binding, 1);
		SDL_DrawGPUPrimitives(render_pass, mesh.num_vertices, 1, 0, 0);
	}

	void Window::display() {
		if (!frame) {
			throw std::exception{};
		} frame = false;
		if (minimized) { return; }

		SDL_EndGPURenderPass(render_pass);
		if (!SDL_SubmitGPUCommandBuffer(command_buffer)) {
			std::cerr << std::format("SDL Error: {}\n", SDL_GetError());
			throw std::exception{};
		}
	}
}

