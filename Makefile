default: public

public: FRC
	rm -rf public
	hugo --config config.toml,prodsite.toml

FRC:
