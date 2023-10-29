
#include "pch.h"
#include "Profiler.h"
#include <iomanip>

namespace Prime
{
	Profiler::Data* Profiler::s_Data = new Profiler::Data();

	void Profiler::BeginSession(const std::string& name, const std::string& filepath)
	{
		std::lock_guard lock(s_Data->Mutex);
		if (s_Data->CurrentSession)
		{
			PRIME_ERROR("Instrumentor::BeginSession('{0}') when session \
				'{1}' already open.", name, s_Data->CurrentSession->Name);
			InternalEndSession();
		}
		s_Data->OutputStream.open(filepath);

		if (s_Data->OutputStream.is_open())
		{
			s_Data->CurrentSession = new ProfilerSession({ name });
			WriteHeader();
		}
		else
		{
			PRIME_ERROR("Instrumentor could not open results file '{0}'.", filepath);
		}
	}

	void Profiler::EndSession()
	{
		std::lock_guard lock(s_Data->Mutex);
		InternalEndSession();
	}

	void Profiler::Shutdown()
	{
		EndSession();
		delete s_Data;
		s_Data = nullptr;
	}

	void Profiler::WriteProfile(const ProfilerResult& result)
	{
		std::stringstream json;

		json << std::setprecision(3) << std::fixed;
		json << ",{";
		json << "\"cat\":\"function\",";
		json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
		json << "\"name\":\"" << result.Name << "\",";
		json << "\"ph\":\"X\",";
		json << "\"pid\":0,";
		json << "\"tid\":" << result.ThreadID << ",";
		json << "\"ts\":" << result.Start.count();
		json << "}";

		std::lock_guard lock(s_Data->Mutex);
		if (s_Data->CurrentSession)
		{
			s_Data->OutputStream << json.str();
			s_Data->OutputStream.flush();
		}
	}

	void Profiler::WriteHeader()
	{
		s_Data->OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
		s_Data->OutputStream.flush();
	}

	void Profiler::WriteFooter()
	{
		s_Data->OutputStream << "]}";
		s_Data->OutputStream.flush();
	}

	void Profiler::InternalEndSession()
	{
		if (s_Data->CurrentSession)
		{
			WriteFooter();
			s_Data->OutputStream.close();
			delete s_Data->CurrentSession;
			s_Data->CurrentSession = nullptr;
		}
	}
}