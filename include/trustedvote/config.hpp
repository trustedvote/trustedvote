#ifndef TRUSTEDVOTE_CONFIG_HPP
#define TRUSTEDVOTE_CONFIG_HPP

#include <filesystem>

namespace trustedvote {

	class config final {
	public:
		static std::filesystem::path const default_json_file;

		static config load_json(std::filesystem::path const &path);
	};

}

#endif // TRUSTEDVOTE_CONFIG_HPP
