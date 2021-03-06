// Copyright (c) 2015-2016 Vector 35 LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include "binaryninjaapi.h"

using namespace std;
using namespace BinaryNinja;


Platform::Platform(BNPlatform* platform)
{
	m_object = platform;
}


Platform::Platform(Architecture* arch, const string& name)
{
	m_object = BNCreatePlatform(arch->GetObject(), name.c_str());
}


Ref<Architecture> Platform::GetArchitecture() const
{
	return new CoreArchitecture(BNGetPlatformArchitecture(m_object));
}


string Platform::GetName() const
{
	char* str = BNGetPlatformName(m_object);
	string result = str;
	BNFreeString(str);
	return result;
}


void Platform::Register(const string& os, Platform* platform)
{
	BNRegisterPlatform(os.c_str(), platform->GetObject());
}


Ref<Platform> Platform::GetByName(const string& name)
{
	BNPlatform* platform = BNGetPlatformByName(name.c_str());
	if (!platform)
		return nullptr;
	return new Platform(platform);
}


vector<Ref<Platform>> Platform::GetList()
{
	size_t count;
	BNPlatform** list = BNGetPlatformList(&count);

	vector<Ref<Platform>> result;
	for (size_t i = 0; i < count; i++)
		result.push_back(new Platform(BNNewPlatformReference(list[i])));

	BNFreePlatformList(list, count);
	return result;
}


vector<Ref<Platform>> Platform::GetList(Architecture* arch)
{
	size_t count;
	BNPlatform** list = BNGetPlatformListByArchitecture(arch->GetObject(), &count);

	vector<Ref<Platform>> result;
	for (size_t i = 0; i < count; i++)
		result.push_back(new Platform(BNNewPlatformReference(list[i])));

	BNFreePlatformList(list, count);
	return result;
}


vector<Ref<Platform>> Platform::GetList(const string& os)
{
	size_t count;
	BNPlatform** list = BNGetPlatformListByOS(os.c_str(), &count);

	vector<Ref<Platform>> result;
	for (size_t i = 0; i < count; i++)
		result.push_back(new Platform(BNNewPlatformReference(list[i])));

	BNFreePlatformList(list, count);
	return result;
}


vector<Ref<Platform>> Platform::GetList(const string& os, Architecture* arch)
{
	size_t count;
	BNPlatform** list = BNGetPlatformListByOSAndArchitecture(os.c_str(), arch->GetObject(), &count);

	vector<Ref<Platform>> result;
	for (size_t i = 0; i < count; i++)
		result.push_back(new Platform(BNNewPlatformReference(list[i])));

	BNFreePlatformList(list, count);
	return result;
}


vector<std::string> Platform::GetOSList()
{
	size_t count;
	char** list = BNGetPlatformOSList(&count);

	vector<string> result;
	for (size_t i = 0; i < count; i++)
		result.push_back(list[i]);

	BNFreePlatformOSList(list, count);
	return result;
}


Ref<CallingConvention> Platform::GetDefaultCallingConvention() const
{
	BNCallingConvention* cc = BNGetPlatformDefaultCallingConvention(m_object);
	if (!cc)
		return nullptr;
	return new CoreCallingConvention(cc);
}


Ref<CallingConvention> Platform::GetCdeclCallingConvention() const
{
	BNCallingConvention* cc = BNGetPlatformCdeclCallingConvention(m_object);
	if (!cc)
		return nullptr;
	return new CoreCallingConvention(cc);
}


Ref<CallingConvention> Platform::GetStdcallCallingConvention() const
{
	BNCallingConvention* cc = BNGetPlatformStdcallCallingConvention(m_object);
	if (!cc)
		return nullptr;
	return new CoreCallingConvention(cc);
}


Ref<CallingConvention> Platform::GetFastcallCallingConvention() const
{
	BNCallingConvention* cc = BNGetPlatformFastcallCallingConvention(m_object);
	if (!cc)
		return nullptr;
	return new CoreCallingConvention(cc);
}


vector<Ref<CallingConvention>> Platform::GetCallingConventions() const
{
	size_t count;
	BNCallingConvention** list = BNGetPlatformCallingConventions(m_object, &count);

	vector<Ref<CallingConvention>> result;
	for (size_t i = 0; i < count; i++)
		result.push_back(new CoreCallingConvention(BNNewCallingConventionReference(list[i])));

	BNFreeCallingConventionList(list, count);
	return result;
}


Ref<CallingConvention> Platform::GetSystemCallConvention() const
{
	BNCallingConvention* cc = BNGetPlatformSystemCallConvention(m_object);
	if (!cc)
		return nullptr;
	return new CoreCallingConvention(cc);
}


void Platform::RegisterCallingConvention(CallingConvention* cc)
{
	BNRegisterPlatformCallingConvention(m_object, cc->GetObject());
}


void Platform::RegisterDefaultCallingConvention(CallingConvention* cc)
{
	BNRegisterPlatformDefaultCallingConvention(m_object, cc->GetObject());
}


void Platform::RegisterCdeclCallingConvention(CallingConvention* cc)
{
	BNRegisterPlatformCdeclCallingConvention(m_object, cc->GetObject());
}


void Platform::RegisterStdcallCallingConvention(CallingConvention* cc)
{
	BNRegisterPlatformStdcallCallingConvention(m_object, cc->GetObject());
}


void Platform::RegisterFastcallCallingConvention(CallingConvention* cc)
{
	BNRegisterPlatformFastcallCallingConvention(m_object, cc->GetObject());
}


void Platform::SetSystemCallConvention(CallingConvention* cc)
{
	BNSetPlatformSystemCallConvention(m_object, cc ? cc->GetObject() : nullptr);
}


Ref<Platform> Platform::GetRelatedPlatform(Architecture* arch)
{
	BNPlatform* platform = BNGetRelatedPlatform(m_object, arch->GetObject());
	if (!platform)
		return nullptr;
	return new Platform(platform);
}


void Platform::AddRelatedPlatform(Architecture* arch, Platform* platform)
{
	BNAddRelatedPlatform(m_object, arch->GetObject(), platform->GetObject());
}


Ref<Platform> Platform::GetAssociatedPlatformByAddress(uint64_t& addr)
{
	BNPlatform* platform = BNGetAssociatedPlatformByAddress(m_object, &addr);
	if (!platform)
		return nullptr;
	return new Platform(platform);
}
