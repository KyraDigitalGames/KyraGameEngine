#ifndef KYRAGAMEENGINE_RENDERING_DIRECTX11_RENDERDEVICEDX11_HPP
#define KYRAGAMEENGINE_RENDERING_DIRECTX11_RENDERDEVICEDX11_HPP

#include <KyraGameEngine/Rendering/IRenderDevice.hpp>

#include <windows.h>
#include <d3d11.h>
#include <d3d10.h>
#include <dxgi.h>

// https://antongerdelan.net/opengl/d3d11.html

namespace kyra {
	
	class RenderDeviceDX11 : public IRenderDevice {
		
		IDXGISwapChain* m_Swapchain = nullptr;             
		ID3D11Device* m_Device = nullptr;                     
		ID3D11DeviceContext* m_DeviceContext = nullptr;           
		ID3D11RenderTargetView* m_Backbuffer = nullptr;  
		
		public:
		~RenderDeviceDX11() {
			    m_Swapchain->Release();
				m_Device->Release();
				m_DeviceContext->Release();
		}
		
		virtual bool create(const IWindow& window) final {
			
			D3D_FEATURE_LEVEL fl;
			HRESULT hr = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_HARDWARE,nullptr, 0, nullptr,0, D3D11_SDK_VERSION, &m_Device, &fl, &m_DeviceContext );
					
			DXGI_SWAP_CHAIN_DESC scd;
			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
			scd.BufferCount = 1;                                   
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      
			scd.OutputWindow = reinterpret_cast<HWND>(window.getHandle()); 
			scd.SampleDesc.Count = 1;                              
			scd.Windowed = TRUE;                                    

			IDXGIFactory* factory;
			hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&factory));
			factory->CreateSwapChain( m_Device, &scd, &m_Swapchain);
			if(!m_Swapchain) {
				return false;
			}
			factory->Release();
		
			ID3D11Texture2D *pBackBuffer;
			m_Swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			// use the back buffer address to create the render target
			KYRA_LOG_INFO(RenderDeviceDX11::create, "Create back buffer");			
			m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_Backbuffer);
			pBackBuffer->Release();

			// set the render target as the back buffer
			m_DeviceContext->OMSetRenderTargets(1, &m_Backbuffer, NULL);

			// Set the viewport
			KYRA_LOG_INFO(RenderDeviceDX11::create, "Create viewport");			
			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = 1280;
			viewport.Height = 720;

			m_DeviceContext->RSSetViewports(1, &viewport);
			
			return true;
		}
		
		virtual void beginDraw() final {
			float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
			m_DeviceContext->ClearRenderTargetView(m_Backbuffer, color);
		}
		
		virtual void endDraw() final {
			m_Swapchain->Present(0, 0);
		}
		
		
	};
	
	
	using RenderDevice = RenderDeviceDX11;
	
}

#endif