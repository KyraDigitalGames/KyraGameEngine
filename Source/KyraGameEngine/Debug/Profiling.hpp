#ifndef KYRAGAMEENGINE_DEBUG_PROFILING_HPP
#define KYRAGAMEENGINE_DEBUG_PROFILING_HPP


#include <vector>
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <string>

namespace kyra {

	struct FunctionEntry {
		std::string name;
		int calls;
		float totalTime;
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	};

	class Profiler {

		static std::unordered_map<std::string, FunctionEntry> m_FunctionEntries;

	public:

		static void startFunction(const char* functionName) {
			FunctionEntry& entry = m_FunctionEntries[functionName];
			entry.calls++;
			entry.name = functionName;
			entry.startTime = std::chrono::high_resolution_clock::now();
		}

		static void endFunction(const char* functionName) {
			FunctionEntry& entry = m_FunctionEntries[functionName];
			auto now = std::chrono::high_resolution_clock::now();
			entry.totalTime += std::chrono::duration<float, std::milli>(now - entry.startTime).count();
		}

		static void print() {
			std::vector<FunctionEntry> entries;
			entries.reserve(m_FunctionEntries.size());
			for (auto& entry : m_FunctionEntries) {
				entries.emplace_back(entry.second);
			}
			



			std::ofstream profilingOutput("KyraProfilingOutput.txt");

			std::sort(entries.begin(), entries.end(), [](const FunctionEntry& entryA, const FunctionEntry& entryB) {
				return entryA.calls > entryB.calls;
			});

			profilingOutput << "Most Calls:\n";
			profilingOutput << "----------------------------------------\n";
			profilingOutput << "Function Name\tCalls\tTotal Time (ms)\tAverage Time (ms)\n";
			for (const auto& entry : entries) {
				const std::string& functionName = entry.name;
				float averageTime = entry.totalTime / entry.calls;
				profilingOutput << functionName << "\t" << entry.calls << "\t" << entry.totalTime << "\t" << averageTime << "\n";
			}
			profilingOutput << "----------------------------------------\n\n";

			std::sort(entries.begin(), entries.end(), [](const FunctionEntry& entryA, const FunctionEntry& entryB) {
				return entryA.totalTime > entryB.totalTime;
			});


			profilingOutput << "Total Time:\n";
			profilingOutput << "----------------------------------------\n";
			profilingOutput << "Function Name\tCalls\tTotal Time (ms)\tAverage Time (ms)\n";
			for (const auto& entry : entries) {
				const std::string& functionName = entry.name;
				float averageTime = entry.totalTime / entry.calls;
				profilingOutput << functionName << "\t" << entry.calls << "\t" << entry.totalTime << "\t" << averageTime << "\n";
			}
			profilingOutput << "----------------------------------------\n";

			std::sort(entries.begin(), entries.end(), [](const FunctionEntry& entryA, const FunctionEntry& entryB) {
				return (entryA.totalTime / entryA.calls) > (entryB.totalTime / entryB.calls);
			});

			profilingOutput << "Highest average:\n";
			profilingOutput << "----------------------------------------\n";
			profilingOutput << "Function Name\tCalls\tTotal Time (ms)\tAverage Time (ms)\n";
			for (const auto& entry : entries) {
				const std::string& functionName = entry.name;
				float averageTime = entry.totalTime / entry.calls;
				profilingOutput << functionName << "\t" << entry.calls << "\t" << entry.totalTime << "\t" << averageTime << "\n";
			}
			profilingOutput << "----------------------------------------\n";



			profilingOutput.close();
		}
	};

	class FunctionProfiler {

		const char* m_FunctionName;

	public:
		FunctionProfiler(const char* functionName) : m_FunctionName(functionName) {
			Profiler::startFunction(functionName);
		}
		~FunctionProfiler() {
			Profiler::endFunction(m_FunctionName);
		}

	};


}

#define KYRA_PROFILE_FUNCTION() kyra::FunctionProfiler kyra_internal_function_profiler(__FUNCTION__);
#define KYRA_PROFILE_PRINT() kyra::Profiler::print();

#endif