#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include <d3dcompiler.h>


GraphicsEngine* GraphicsEngine::sharedInstance = NULL;

GraphicsEngine* GraphicsEngine::GetInstance()
{
    if (sharedInstance == NULL)
    {
        sharedInstance = new GraphicsEngine(); 
    }

    return sharedInstance;
}

bool GraphicsEngine::Init()
{
    D3D_DRIVER_TYPE driverTypes[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    HRESULT res = 0;

    for (UINT i = 0; i < numDriverTypes;)
    {
        if (SUCCEEDED(res = D3D11CreateDevice(nullptr, driverTypes[i], nullptr, 0, 
            featureLevels, numFeatureLevels, D3D11_SDK_VERSION, 
            &d3dDevice, &featureLevel, &d3d11ImmContext)))
        {
            break;
        }
        
        i++; 
    }

    if (FAILED(res)) return false;

    immDeviceContext = new DeviceContext(d3d11ImmContext); 

    d3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
    dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
    dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

    return true;
}

bool GraphicsEngine::Release()
{
    if (vShader) vShader->Release();
    if (pShader) pShader->Release();

    if (vsBlob) vsBlob->Release();
    if (psBlob) psBlob->Release();

    dxgiFactory->Release();
    dxgiAdapter->Release();
    dxgiDevice->Release();

    immDeviceContext->Release();
    d3dDevice->Release();

    return true;
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
    return new SwapChain();
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
    return immDeviceContext;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
    return new VertexBuffer(); 
}

bool GraphicsEngine::CreateShaders()
{
    ID3DBlob* errblob = nullptr;
    D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &vsBlob, &errblob);
    D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &psBlob, &errblob);
    d3dDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vShader); 
    d3dDevice->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pShader); 
    return true;
}

bool GraphicsEngine::SetShaders()
{
    d3d11ImmContext->VSSetShader(vShader, nullptr, 0);
    d3d11ImmContext->PSSetShader(pShader, nullptr, 0);
    return true;
}

void GraphicsEngine::GetShaderBufferAndSize(void** bytecode, UINT* size)
{
    *bytecode = this->vsBlob->GetBufferPointer(); 
    *size = (UINT)this->vsBlob->GetBufferSize(); 
}