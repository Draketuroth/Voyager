// Based on the following implementations:
// How to create a looping thread : http://www.cplusplus.com/forum/general/188452/
// Writing a simple file watcher : https://solarianprogrammer.com/2019/01/13/cpp-17-filesystem-write-file-watcher-monitor/

#ifndef VE_FILE_NOTIFIER_H
#define VE_FILE_NOTIFIER_H

#include <filesystem>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <string>
#include <functional>

#include "Voyager/Core/Log.h"
#include "Voyager/IO/Parsing.h"
#include "Voyager/Event/FileEvent.h"
#include "Voyager/Event/Dispatcher.h"

namespace VE 
{
	namespace IO
	{
		class FileNotifier
		{
		public:
			FileNotifier(std::string baseFolderPath, Core::Scope<Event::Dispatcher> dispatcher) : _baseFolderPath(baseFolderPath), _dispatcher(std::move(dispatcher))
			{
				// Store and record files from a base directory with their last modifiction time.
				for (auto& file : std::filesystem::recursive_directory_iterator(baseFolderPath))
				{
					_paths[file.path().string()] = std::filesystem::last_write_time(file);
				}

				// Start thread.
				thread = std::thread(&FileNotifier::execute, this);
			}

			void execute()
			{
				while (running)
				{
					// Halt this thread given a delay in milliseconds;
					using namespace std::literals;
					std::this_thread::sleep_for(200ms);

					// Check for files to be removed.
					auto it = _paths.begin();
					while (it != _paths.end())
					{
						if (!std::filesystem::exists(it->first))
						{
							VE::Event::FileDeletedEvent event(it->first);
							_dispatcher->post(event);

							it = _paths.erase(it);
						}
						else
						{
							it++;
						}
					}

					// Check if a file was created or modified.
					// That includes checking if the user removed the currently tracked folder.
					if (std::filesystem::exists(_baseFolderPath))
					{
						for (auto& file : std::filesystem::recursive_directory_iterator(_baseFolderPath))
						{
							auto currentLastWriteTime = std::filesystem::last_write_time(file);

							std::string currentPath = file.path().string();

							// Creation.
							if (!contains(currentPath))
							{
								_paths[currentPath] = currentLastWriteTime;

								VE::Event::FileCreatedEvent event(currentPath);
								_dispatcher->post(event);
							}
							// Modification.
							else
							{
								if (_paths[currentPath] != currentLastWriteTime)
								{
									_paths[currentPath] = currentLastWriteTime;

									VE::Event::FileModifiedEvent event(currentPath);
									_dispatcher->post(event);
								}
							}
						}
					}
					else
					{
						VE_CORE_WARN("Base folder was removed. Reset the application...");
					}
				}
			}

			bool contains(const std::string& key)
			{
				auto el = _paths.find(key);
				return el != _paths.end();
			}

			~FileNotifier() { running = false; thread.join(); }

		private:
			FileNotifier(const FileNotifier&) = delete;
			FileNotifier(FileNotifier&&) = delete;
			FileNotifier& operator= (FileNotifier) = delete;

		private:

			VE::Core::Scope<VE::Event::Dispatcher> _dispatcher;

			// Base folder path.
			std::string _baseFolderPath;

			// Time interval to check the base folder for changes.
			// std::chrono::duration<int, std::milli> _delay;
			std::unordered_map<std::string, std::filesystem::file_time_type> _paths;

			std::atomic<bool>running{ true };
			std::thread thread;
		};
	}
}

#endif
