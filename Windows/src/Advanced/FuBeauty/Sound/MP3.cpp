#include "Mp3.h"
#include <uuids.h>

Mp3::Mp3()
{
	pigb = NULL;
	pimc = NULL;
	pimex = NULL;
	piba = NULL;
	pims = NULL;
	ready = false;
	duration = 0;
}

Mp3::~Mp3()
{
	Cleanup();
}

void Mp3::Cleanup()
{
	if (pimc)
		pimc->Stop();

	if (pigb)
	{
		pigb->Release();
		pigb = NULL;
	}

	if (pimc)
	{
		pimc->Release();
		pimc = NULL;
	}

	if (pimex)
	{
		pimex->Release();
		pimex = NULL;
	}

	if (piba)
	{
		piba->Release();
		piba = NULL;
	}

	if (pims)
	{
		pims->Release();
		pims = NULL;
	}
	ready = false;
}

bool Mp3::Load(std::string mp3Path)
{
	Cleanup();
	ready = false;
	if (SUCCEEDED(CoCreateInstance(CLSID_FilterGraph,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder,
		(void **)&this->pigb)))
	{
		pigb->QueryInterface(IID_IMediaControl, (void **)&pimc);
		pigb->QueryInterface(IID_IMediaEventEx, (void **)&pimex);
		pigb->QueryInterface(IID_IBasicAudio, (void**)&piba);
		pigb->QueryInterface(IID_IMediaSeeking, (void**)&pims);

		size_t size = mp3Path.length();
		wchar_t *buffer = new wchar_t[size + 1];
		MultiByteToWideChar(CP_ACP, 0, mp3Path.c_str(), size, buffer, size * sizeof(wchar_t));
		buffer[size] = 0; 
		HRESULT hr = pigb->RenderFile(buffer, NULL);
		delete buffer;
		buffer = NULL;
		if (SUCCEEDED(hr))
		{
			ready = true;
			sMp3Path = mp3Path;
			if (pims)
			{
				pims->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
				pims->GetDuration(&duration); // returns 10,000,000 for a second.
				duration = duration;
			}
		}
	}
	return ready;
}

bool Mp3::Play()
{
	if (ready&&pimc)
	{
		HRESULT hr = pimc->Run();
		return SUCCEEDED(hr);
	}
	return false;
}

bool Mp3::CirculationPlayCheck()
{
	if (ready&&pimex)
	{
		long event_code;
		LONG_PTR param1, param2;
		HRESULT hr = pimex->GetEvent(&event_code, &param1, &param2, 1);
		if (SUCCEEDED(hr) && event_code == 0x01/*EC_COMPLETE*/)
		{			
			this->Stop();
			this->Load(sMp3Path);
			this->Play();
		}
		pimex->FreeEventParams(event_code, param1, param2);
		return SUCCEEDED(hr);
	}
	return false;
}

bool Mp3::Pause()
{
	if (ready&&pimc)
	{
		HRESULT hr = pimc->Pause();
		return SUCCEEDED(hr);
	}
	return false;
}

bool Mp3::Stop()
{
	if (ready&&pimc)
	{
		HRESULT hr = pimc->Stop();
		return SUCCEEDED(hr);
	}
	return false;
}

bool Mp3::WaitForCompletion(long msTimeout, long* EvCode)
{
	if (ready&&pimex)
	{
		HRESULT hr = pimex->WaitForCompletion(msTimeout, EvCode);
		return *EvCode > 0;
	}

	return false;
}

bool Mp3::SetVolume(long vol)
{
	if (ready&&piba)
	{
		HRESULT hr = piba->put_Volume(vol);
		return SUCCEEDED(hr);
	}
	return false;
}

long Mp3::GetVolume()
{
	if (ready&&piba)
	{
		long vol = -1;
		HRESULT hr = piba->get_Volume(&vol);

		if (SUCCEEDED(hr))
			return vol;
	}

	return -1;
}

__int64 Mp3::GetDuration()
{
	return duration;
}

__int64 Mp3::GetCurrentPosition()
{
	if (ready&&pims)
	{
		__int64 curpos = -1;
		HRESULT hr = pims->GetCurrentPosition(&curpos);

		if (SUCCEEDED(hr))
			return curpos;
	}

	return -1;
}

bool Mp3::SetPositions(__int64* pCurrent, __int64* pStop, bool bAbsolutePositioning)
{
	if (ready&&pims)
	{
		DWORD flags = 0;
		if (bAbsolutePositioning)
			flags = AM_SEEKING_AbsolutePositioning | AM_SEEKING_SeekToKeyFrame;
		else
			flags = AM_SEEKING_RelativePositioning | AM_SEEKING_SeekToKeyFrame;

		HRESULT hr = pims->SetPositions(pCurrent, flags, pStop, AM_SEEKING_NoPositioning);

		if (SUCCEEDED(hr))
			return true;
	}

	return false;
}