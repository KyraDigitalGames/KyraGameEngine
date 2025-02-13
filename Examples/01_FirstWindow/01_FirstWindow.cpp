

#include <GLAD/glad.h>
#include <GLAD/glad_wgl.h>

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <fstream>

#include <KyraGameEngine/Window/WinAPI/WindowWinAPI.hpp>
#include <KyraGameEngine/RHI/AbstractSwapChain.hpp>
#include <KyraGameEngine/RHI/AbstractCommandBuffer.hpp>
#include <KyraGameEngine/RHI/AbstractTransferBuffer.hpp>
#include <KyraGameEngine/RHI/AbstractCopyPass.hpp>
#include <KyraGameEngine/RHI/AbstractRenderDevice.hpp>


namespace kyra {
   
  class SwapChainOpenGL : public AbstractSwapChain {
    
    HDC m_DeviceContext = NULL;
    HGLRC m_RenderContext = NULL;
    
    public:
    ~SwapChainOpenGL() {
      if(m_RenderContext) {
        wglDeleteContext(m_RenderContext);
      }
      if(m_DeviceContext) {
        DeleteDC(m_DeviceContext);
      }
    }
    
    bool init(const SwapChainDescriptor& descriptor) {
      
      m_DeviceContext = GetDC( reinterpret_cast<HWND>(descriptor.window->getHandle()));
      
      PIXELFORMATDESCRIPTOR pfd = {0};
      pfd.nSize = sizeof(pfd);
      pfd.nVersion = 1;
      pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
      pfd.iPixelType = PFD_TYPE_RGBA;
      pfd.cColorBits = 32;
      pfd.cDepthBits = 16;
      pfd.cStencilBits = 8;
      pfd.iLayerType = PFD_MAIN_PLANE;
      
      int pixelformat = ChoosePixelFormat(m_DeviceContext, &pfd);
      
      if(!SetPixelFormat(m_DeviceContext, pixelformat, &pfd)) {
        return false;
      }
      
      HGLRC temporaryContext = wglCreateContext(m_DeviceContext);
      wglMakeCurrent(m_DeviceContext, temporaryContext);
      
      if(!gladLoadWGLLoader((GLADloadproc)wglGetProcAddress, m_DeviceContext)) {
         wglDeleteContext(temporaryContext);
         return false;
      }
      
      if(!gladLoadGLLoader((GLADloadproc)wglGetProcAddress)) {
        wglDeleteContext(temporaryContext);
        return false;
      }
      
      int attributes[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
      };
      
      
      m_RenderContext =  wglCreateContextAttribsARB(m_DeviceContext, 0, attributes);
      wglMakeCurrent(m_DeviceContext, m_RenderContext);
      
      wglDeleteContext(temporaryContext);
      return true;
    }
    
    void bind() {
      
    }
    
    void unbind() {
      SwapBuffers(m_DeviceContext);
    }

    
  };
  
  class RenderPipelineOpenGL : public AbstractRenderPipeline {
    
    GLuint m_VAO = 0;
    GLuint m_ShaderProgram = 0;
    
    public:
    ~RenderPipelineOpenGL() {
      if(m_VAO) {
        glDeleteVertexArrays(1, &m_VAO);
      }
      if(m_ShaderProgram) {
        glDeleteProgram(m_ShaderProgram);
      }
    }
    
    bool init(const RenderPipelineDescriptor& descriptor) {
      
      if(m_VAO) {
        glDeleteVertexArrays(1, &m_VAO);
      }
      glGenVertexArrays(1, &m_VAO);
      
      if(m_ShaderProgram) {
        glDeleteProgram(m_ShaderProgram);
      }
      m_ShaderProgram = glCreateProgram();
      glAttachShader( m_ShaderProgram, descriptor.vertexShader->getId() );
      glAttachShader( m_ShaderProgram, descriptor.fragmentShader->getId() );
      glLinkProgram(m_ShaderProgram);
      
      return true;
    }
    
    void bind() {
      glBindVertexArray(m_VAO);
      glUseProgram(m_ShaderProgram);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
      glEnableVertexAttribArray(0);  
    }
        
  };
  
    
 
  class VertexBufferOpenGL : public AbstractVertexBuffer {
    
    GLuint m_Id = 0;
    std::size_t m_Size = 0;
    
    public:
    ~VertexBufferOpenGL() {
      if(m_Id) {
        glDeleteBuffers(1, &m_Id);
      }
    }
    
    bool init(const VertexBufferDescriptor& descriptor) {
      if(m_Id) {
        glDeleteBuffers(1, &m_Id);
      }
      glGenBuffers(1, &m_Id);
      glBindBuffer(GL_ARRAY_BUFFER, m_Id);
      glBufferData(GL_ARRAY_BUFFER, descriptor.size, nullptr, GL_DYNAMIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      return true;
    }
 
    std::size_t getSize() const {
      return m_Size;
    }
    
    void upload(std::size_t size, void* data) {
      glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }
 
    void bind() {
      glBindBuffer(GL_ARRAY_BUFFER, m_Id);
    }
          
  };
  
  
  class CommandBufferOpenGL : public AbstractCommandBuffer {
    
    RenderPipelineOpenGL* m_RenderPipeline = nullptr;
    VertexBufferOpenGL* m_VertexBuffer = nullptr;
    
    public:
    
    void bindVertexBuffer(AbstractVertexBuffer* vertexBuffer) {
      //if(m_VertexBuffer != vertexBuffer) {
        m_VertexBuffer = static_cast<VertexBufferOpenGL*>(vertexBuffer);
        m_VertexBuffer->bind(); 
      //}
    }
    
    void bindRenderPipeline(AbstractRenderPipeline* renderPipeline) {
      //if(m_RenderPipeline != renderPipeline) {
        m_RenderPipeline = static_cast<RenderPipelineOpenGL*>(renderPipeline);
        m_RenderPipeline->bind(); 
      //}
    }
    
    void draw(std::size_t offset, std::size_t count) {
      glDrawArrays(GL_TRIANGLES, offset, count);
    }
    
    void submit() {
    
    }
    
  };
  
  class RenderPassOpenGL : public AbstractRenderPass {
    
    AbstractRenderTarget* m_RenderTarget = nullptr;
    AbstractCommandBuffer* m_CommandBuffer = nullptr;
    
    public:
    
    
    bool init(const RenderPassDescriptor& renderPassDescriptor) {
      m_RenderTarget = renderPassDescriptor.target;
      return true;
    }
    
    void begin() {
      m_RenderTarget->bind();
      glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void end() {
      m_RenderTarget->unbind();
    }
    
  };
  
  class ShaderOpenGL : public AbstractShader {
    
    GLuint m_Id = 0;
    
    public:
    ~ShaderOpenGL() {
      if(m_Id) {
        glDeleteShader(m_Id);
      }
    }
    
    
    virtual bool init(const ShaderDescriptor& shaderDescriptor) {
      if(m_Id) {
        glDeleteShader(m_Id);
      }
      m_Id = glCreateShader( (shaderDescriptor.stage == ShaderStage::Vertex) ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
      glShaderSource(m_Id, 1, &shaderDescriptor.code, NULL);
      glCompileShader(m_Id);
      int success = 0;
      glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
      if(!success) {
        int length = 0;
        glGetShaderiv(m_Id, GL_INFO_LOG_LENGTH, &length );
        std::string error;
        error.resize(length);
        glGetShaderInfoLog(m_Id, length, NULL, error.data());
        std::ofstream errorFile;
        errorFile.open("KyraGameEngine.error.log");
        errorFile << "-- Failed to compile shader ---" << std::endl;
        errorFile << "[MESSAGE]" << std::endl;
        errorFile << error << std::endl;
        errorFile << "[SOURCE]" << std::endl;
        errorFile << shaderDescriptor.code << std::endl;
        errorFile.close();
        return false;
      }
      return true;
    }
    
    virtual std::size_t getId() const {
      return m_Id;
    }
    
  };
  
  
  class TransferBufferOpenGL : public AbstractTransferBuffer {
    
    std::vector<uint8_t> m_Data;
    
    public:
    
    bool init(const TransferBufferDescriptor& descriptor) {
      m_Data.resize(descriptor.size);
      return true;
    }

    uint8_t* map() {
      return m_Data.data();
    }
    
    void unmap() {
      
    }
    
    std::size_t getSize() {
      return m_Data.size();
    }
    
    uint8_t* getData() {
      return m_Data.data(); 
    }
        
    
  };
  
  class CopyPassOpenGL : public AbstractCopyPass {
    
    public:
    
    
    virtual void begin() {
      
    }
    
    virtual void upload(AbstractCommandBuffer* commandbuffer, AbstractTransferBuffer* source, AbstractVertexBuffer* target) {
        commandbuffer->bindVertexBuffer(target);
        static_cast<VertexBufferOpenGL*>(target)->upload(source->getSize(), source->getData() );   
    }
    
    virtual void end() {
      
    }
    
  };
  
  class RenderDeviceOpenGL : public AbstractRenderDevice {
    
    SwapChainOpenGL m_SwapChain;
    CommandBufferOpenGL m_CommandBuffer;
    
    public:
      
    virtual bool init(const RenderDeviceDescriptor& descriptor) {
      SwapChainDescriptor swapChainDescriptor;
      swapChainDescriptor.window = descriptor.window;
      return m_SwapChain.init(swapChainDescriptor);
    }
    
    virtual AbstractSwapChain* getSwapChain() {
      return &m_SwapChain;
    }
    
    virtual AbstractCommandBuffer* getCommandBuffer() {
      return &m_CommandBuffer;
    }

    std::unique_ptr<AbstractShader> createShader() {
      return std::make_unique<ShaderOpenGL>();
    }

    std::unique_ptr<AbstractRenderPass> createRenderPass() {
      return std::make_unique<RenderPassOpenGL>();
    }
    
    std::unique_ptr<AbstractCopyPass> createCopyPass() {
      return std::make_unique<CopyPassOpenGL>();
    }
    
    std::unique_ptr<AbstractRenderPipeline> createRenderPipeline() {
      return std::make_unique<RenderPipelineOpenGL>();
    }
    
    std::unique_ptr<AbstractTransferBuffer> createTransferBuffer() {
      return std::make_unique<TransferBufferOpenGL>();
    }
    
    
    std::unique_ptr<AbstractVertexBuffer> createVertexBuffer() {
      return std::make_unique<VertexBufferOpenGL>();
    }
    
  };
  
}

#include <iostream>

int main(int argc, char** argv) {
  
  std::cout << "Create Window" << std::endl;
   
  kyra::WindowDescriptor windowDescriptor;
  windowDescriptor.title = "Kyra Game Engine - First Window Example";
  windowDescriptor.width = 1280;
  windowDescriptor.height = 720;
  
  std::unique_ptr<kyra::AbstractWindow> window = std::make_unique<kyra::WindowWinAPI>();
  if(!window->init(windowDescriptor)) {
    return -1;
  }
  
  window->onClose.connect(nullptr, [&](){
    window->close();
  });
  
  window->onMouseMoved.connect(nullptr,[](int x, int y){
    std::cout << x << " " << y << std::endl;
  });
  
  std::cout << "Create RenderDevice" << std::endl;
  
  kyra::RenderDeviceDescriptor renderDeviceDescriptor;
  renderDeviceDescriptor.window = window.get();
  std::unique_ptr<kyra::AbstractRenderDevice> renderDevice = std::make_unique<kyra::RenderDeviceOpenGL>();
  if(!renderDevice->init(renderDeviceDescriptor)) {
    return -2;
  }
  
  std::cout << "Create Vertex Shader" << std::endl;
  
  std::string vertexShaderSource = "#version 330\n"
                                   "layout (location = 0) in vec2 aPos;\n"
                                   "void main() {\n"
                                   "gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                                   "}";
  
  kyra::ShaderDescriptor vertexShaderDescriptor;
  vertexShaderDescriptor.code = vertexShaderSource.c_str();
  vertexShaderDescriptor.size = vertexShaderSource.size();
  vertexShaderDescriptor.stage = kyra::ShaderStage::Vertex;
  
  std::unique_ptr<kyra::AbstractShader> vertexShader = renderDevice->createShader();
  if(!vertexShader->init(vertexShaderDescriptor)) {
    return false;
  }
  
  std::cout << "Create Fragment Shader" << std::endl;
  
  std::string fragmentShaderSource = "#version 330\n"
                                   "out vec4 fragColor;\n"
                                   "void main() {\n"
                                   "fragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
                                   "}";
  
  kyra::ShaderDescriptor fragmentShaderDescriptor;
  fragmentShaderDescriptor.code = fragmentShaderSource.c_str();
  fragmentShaderDescriptor.size = fragmentShaderSource.size();
  fragmentShaderDescriptor.stage = kyra::ShaderStage::Fragment;
  
  std::unique_ptr<kyra::AbstractShader> fragmentShader = renderDevice->createShader();
  if(!fragmentShader->init(fragmentShaderDescriptor)) {
    return false;
  }
  
  std::cout << "Create Render Pipeline" << std::endl;
  
  kyra::RenderPipelineDescriptor renderPipelineDescriptor;
  renderPipelineDescriptor.vertexShader = vertexShader.get();
  renderPipelineDescriptor.fragmentShader = fragmentShader.get();
  std::unique_ptr<kyra::AbstractRenderPipeline> renderPipeline = renderDevice->createRenderPipeline();
  if(!renderPipeline->init(renderPipelineDescriptor)) {
    return -3;
  }
  
  std::cout << "Create Transferbuffer and upload data" << std::endl;
  
  struct Vertex {
    float pos[2];
  };
  
  kyra::VertexBufferDescriptor vertexBufferDescriptor;
  vertexBufferDescriptor.size = 6 * sizeof(Vertex);
  
  std::unique_ptr<kyra::AbstractVertexBuffer> vertexBuffer = renderDevice->createVertexBuffer();
  if(!vertexBuffer->init(vertexBufferDescriptor)) {
    return false;
  }
  
  kyra::TransferBufferDescriptor transferBufferDescriptor;
  transferBufferDescriptor.usage = kyra::TransferBufferUsage::Upload;
  transferBufferDescriptor.size  = 6 * sizeof(Vertex);
  
  std::unique_ptr<kyra::AbstractTransferBuffer> transferBuffer = renderDevice->createTransferBuffer();
  if(!transferBuffer->init(transferBufferDescriptor)) {
    return false;
  }
  
  Vertex* vertices = reinterpret_cast<Vertex*>(transferBuffer->map());
  vertices[0] = {0.f, 0.f};
  vertices[1] = {1.f, 0.f};
  vertices[2] = {1.f, 1.f};
  vertices[3] = {0.f, 0.f};
  vertices[4] = {0.f, 1.f};
  vertices[5] = {1.f, 1.f};
  transferBuffer->unmap();
  
  
  // We store the command buffer for later use
  
  kyra::AbstractCommandBuffer* commandBuffer = renderDevice->getCommandBuffer();  
  
  
  std::unique_ptr<kyra::AbstractCopyPass> copyPass = renderDevice->createCopyPass();
  copyPass->begin();
  copyPass->upload(commandBuffer, transferBuffer.get(), vertexBuffer.get());
  copyPass->end();
    
  
  std::cout << "Create the default render pass" << std::endl;
  
  kyra::RenderPassDescriptor renderPassDescriptor;
  renderPassDescriptor.target = renderDevice->getSwapChain();
  renderPassDescriptor.commandBuffer = commandBuffer;
  std::unique_ptr<kyra::AbstractRenderPass> renderPass = renderDevice->createRenderPass();
  if(!renderPass->init(renderPassDescriptor)) {
    return -4;
  }
  
  std::cout << "Run main loop" << std::endl;
    
  window->show();
  while(window->isOpen()) {
    window->processEvents();
    renderPass->begin();
    commandBuffer->bindVertexBuffer(vertexBuffer.get());
    commandBuffer->bindRenderPipeline(renderPipeline.get());
    commandBuffer->draw(0,6);
    renderPass->end();
    commandBuffer->submit();
  }
  
  window->onClose.disconnect(nullptr);
  window->onMouseMoved.disconnect(nullptr);
    
  return 0;
}