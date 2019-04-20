#ifndef TRUSTEDVOTE_CHAIN_HPP
#define TRUSTEDVOTE_CHAIN_HPP

namespace trustedvote::chain {

	class params {
	public:
		params() noexcept;
		params(params const &other) noexcept;
		virtual ~params();

		params &operator=(params const &other) noexcept;
	};

}

#endif // TRUSTEDVOTE_CHAIN_HPP
