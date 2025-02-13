add_library(KyraGameEngine STATIC ./Window/WinAPI/WindowWinAPI.cpp)
target_precompile_headers(KyraGameEngine PUBLIC ./RHI/AbstractCommandBuffer.hpp
                                                ./RHI/AbstractRenderPass.hpp
                                                ./RHI/AbstractRenderPipeline.hpp
                                                ./RHI/AbstractRenderTarget.hpp
                                                ./RHI/AbstractShader.hpp
                                                ./RHI/AbstractSwapChain.hpp
                                                ./RHI/AbstractTransferBuffer.hpp
                                                ./RHI/AbstractCopyPass.hpp
                                                ./RHI/AbstractRenderDevice.hpp)
target_include_directories(KyraGameEngine PUBLIC ${PROJECT_SOURCE_DIR}/Source)